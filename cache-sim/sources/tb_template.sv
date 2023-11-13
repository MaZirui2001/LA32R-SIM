`timescale 1ns / 1ps
module cache_tb();

localparam TOTAL_WORD_NUM       = %d;
localparam TOTAL_TEST_NUM       = %d;

// cache test
reg [31:0]  i_addr_rom   [TOTAL_TEST_NUM];
reg [31:0]  d_addr_rom   [TOTAL_TEST_NUM];
reg [31:0]  data_ram     [TOTAL_WORD_NUM];
reg [4:0]   mem_type_rom [TOTAL_TEST_NUM];
reg [31:0]  wdata_rom    [TOTAL_TEST_NUM];
reg [31:0]  i_test_index = 0;
reg [31:0]  d_test_index = 0;

reg clk = 1'b1, rstn = 1'b0;

initial #5 rstn = 1'b1; 
always #1 clk = ~clk;

// generate data_ram
initial begin
    for(integer i = 0; i < TOTAL_WORD_NUM; i++)begin
        data_ram[i] = i;
    end
end
initial begin
/* SPLIT */
end
// for icache 
wire            i_rvalid_pipe;
wire            icache_miss_pipe;
wire    [31:0]  i_raddr_pipe;
wire    [31:0]  i_rdata_pipe;

// icache_debug
reg             i_rvalid_ff;
reg     [31:0]  i_raddr_ff;
reg             i_error_reg;
reg             i_pass_reg;
wire    [31:0]  i_correct_data;

// // for dcache
wire    [31:0]  d_addr_pipe;
wire    [4:0]   d_mem_type_pipe;
wire    [31:0]  d_wdata_pipe;
wire            dcache_miss_pipe;
wire    [31:0]  d_rdata_pipe;

// dcache_debug
reg     [4:0]   d_mem_type_ff1, d_mem_type_ff2;
reg     [31:0]  d_wdata_ff1, d_wdata_ff2;
reg     [31:0]  d_addr_ff1, d_addr_ff2;
reg             d_error_reg;
reg             d_pass_reg;
wire    [31:0]  d_correct_data;


// arbiter with main mem
wire    [31:0]  araddr;
wire            arvalid;
wire            arready;
wire    [7:0]   arlen;
wire    [2:0]   arsize;
wire    [1:0]   arburst;
wire    [31:0]  rdata;
wire    [1:0]   rresp;
wire            rvalid;
wire            rready;
wire            rlast;
wire    [31:0]  awaddr;
wire            awvalid;
wire            awready;
wire    [7:0]   awlen;
wire    [2:0]   awsize;
wire    [1:0]   awburst;
wire    [31:0]  wdata;
wire    [3:0]   wstrb;
wire            wvalid;
wire            wready;
wire            wlast;
wire    [1:0]   bresp;
wire            bvalid;
wire            bready;

assign i_raddr_pipe     = i_addr_rom[i_test_index];
assign i_correct_data   = data_ram[i_raddr_ff >> 2];
assign i_rvalid_pipe    = 1'b1;

// simulate IF1-IF2 register i_rvalid_ff && i_raddr_ff
always @(posedge clk) begin
    if(!rstn) begin
        i_rvalid_ff <= 0;
        i_raddr_ff <= 0;
    end
    else if(!icache_miss_pipe)begin
        i_rvalid_ff <= i_rvalid_pipe;
        i_raddr_ff <= i_raddr_pipe;
    end
end
// update i_test_index
always @(posedge clk) begin
    if(!rstn) begin
        i_test_index <= 0;
        i_pass_reg <= 0;
    end
    else if (i_test_index >= (TOTAL_TEST_NUM / 2-1)) begin
        i_test_index <= (TOTAL_TEST_NUM / 2-1);
        i_pass_reg <= 1;
    end
    else if(!(i_rvalid_ff && icache_miss_pipe) && !i_error_reg) begin
        i_test_index <= i_test_index + 1;
    end
end
// update i_error 
always @(posedge clk) begin
    if(!rstn) begin
        i_error_reg <= 0;
    end
    else if(i_error_reg) begin
        i_error_reg <= 1;
    end
    else if(i_rvalid_ff && !icache_miss_pipe) begin
        i_error_reg <= !(i_rdata_pipe  == i_correct_data);
    end
end

assign d_addr_pipe           = d_addr_rom[d_test_index];
wire [31:0] d_rdata_raw      = data_ram[d_addr_ff2 >> 2] >> (8 * (d_addr_ff2[1:0]));
wire [31:0] rmask            = (1 << (8 * (1 << (d_mem_type_ff2[1:0])))) - 1;
assign d_correct_data        = d_rdata_raw & rmask | {32{!d_mem_type_ff2[2] & d_rdata_raw[8 * (1 << (d_mem_type_ff2[1:0])) - 1]}} & ~rmask;
assign d_mem_type_pipe       = mem_type_rom[d_test_index];
wire [3:0] wmask             = ((1 << (1 << d_mem_type_ff2[1:0])) - 1) << d_addr_ff2[1:0];
assign d_wdata_pipe          = wdata_rom[d_test_index];

// simulate EX-MEM register
always @(posedge clk) begin
    if(!rstn) begin
        d_addr_ff1      <= 0;
        d_mem_type_ff1  <= 0;
        d_wdata_ff1     <= 0;
        d_addr_ff2      <= 0;
        d_mem_type_ff2  <= 0;
        d_wdata_ff2     <= 0;

    end
    else if(!dcache_miss_pipe)begin
        d_addr_ff1      <= d_addr_pipe;
        d_mem_type_ff1  <= d_mem_type_pipe;
        d_wdata_ff1     <= d_wdata_pipe;
        d_addr_ff2      <= d_addr_ff1;
        d_mem_type_ff2  <= d_mem_type_ff1;
        d_wdata_ff2     <= d_wdata_ff1;
    end
end
// update d_test_index
always @(posedge clk) begin
    if(!rstn) begin
        d_test_index    <= TOTAL_TEST_NUM / 2;
        d_pass_reg      <= 0;
    end
    else if (d_test_index >= (TOTAL_TEST_NUM-1)) begin
        d_test_index    <= (TOTAL_TEST_NUM-1);
        d_pass_reg      <= 1;
    end
    else if(!(|d_mem_type_ff2[4:3] && dcache_miss_pipe) && !d_error_reg) begin
        d_test_index    <= d_test_index + 1;
    end
end
// update data_ram
wire [31:0] wdata_debug = d_wdata_ff2 << (8 * (d_addr_ff2[1:0]));
always @(posedge clk) begin
    if(d_mem_type_ff2[4] && !dcache_miss_pipe) begin
        // data_ram[d_addr_ff2 >> 2] <= d_wdata_ff2;
        for(integer i = 0; i < 4; i++) begin
            if(wmask[i])
                data_ram[d_addr_ff2 >> 2][i * 8 +: 8] <= wdata_debug[i * 8 +: 8];
        end
    end
end
// // update d_error 
always @(posedge clk) begin
    if(!rstn) begin
        d_error_reg <= 0;
    end
    else if(d_error_reg) begin
        d_error_reg <= 1;
    end
    else if(d_mem_type_ff2[3] && !dcache_miss_pipe) begin
        d_error_reg <= !(d_rdata_pipe  == d_correct_data);
    end
end


// mem unit
Cache_Top  Cache_Top_inst (
    .clock                  (clk),
    .reset                  (!rstn),
    .io_i_addr_pipe         (i_raddr_pipe),
    .io_i_rvalid_pipe       (i_rvalid_pipe),
    .io_cache_miss_RM       (icache_miss_pipe),
    .io_rdata_RM            (i_rdata_pipe),

    .io_d_addr_pipe         (d_addr_pipe),
    .io_mem_type_pipe       (d_mem_type_pipe),
    .io_wdata_pipe          (d_wdata_pipe),
    .io_cache_miss_MEM      (dcache_miss_pipe),
    .io_rdata_MEM           (d_rdata_pipe),
    
    .io_araddr              (araddr),
    .io_arburst             (arburst),
    .io_arid                (arid),
    .io_arlen               (arlen),
    .io_arready             (arready),
    .io_arsize              (arsize),
    .io_arvalid             (arvalid),
    .io_awaddr              (awaddr),
    .io_awburst             (awburst),
    .io_awid                (awid),
    .io_awlen               (awlen),
    .io_awready             (awready),
    .io_awsize              (awsize),
    .io_awvalid             (awvalid),
    .io_bid                 (bid),
    .io_bready              (bready),
    .io_bresp               (bresp),
    .io_bvalid              (bvalid),
    .io_rdata               (rdata),
    .io_rid                 (rid),
    .io_rlast               (rlast),
    .io_rready              (rready),
    .io_rresp               (rresp),
    .io_rvalid              (rvalid),
    .io_wdata               (wdata),
    .io_wlast               (wlast),
    .io_wready              (wready),
    .io_wstrb               (wstrb),
    .io_wvalid              (wvalid)
);
main_mem main_memory(
    .s_aclk         (clk ),
    .s_aresetn      (rstn ),
    .s_axi_araddr   (araddr ),
    .s_axi_arburst  (arburst ),
    .s_axi_arid     (4'b0),
    .s_axi_arlen    (arlen ),
    .s_axi_arready  (arready ),
    .s_axi_arsize   (arsize ),
    .s_axi_arvalid  (arvalid ),
    .s_axi_awaddr   (awaddr ),
    .s_axi_awburst  (awburst ),
    .s_axi_awid     (4'b0),
    .s_axi_awlen    (awlen ),
    .s_axi_awready  (awready ),
    .s_axi_awsize   (awsize ),
    .s_axi_awvalid  (awvalid ),
    .s_axi_bid      (),
    .s_axi_bready   (bready ),
    .s_axi_bresp    (bresp ),
    .s_axi_bvalid   (bvalid ),
    .s_axi_rdata    (rdata ),
    .s_axi_rid      (),
    .s_axi_rlast    (rlast ),
    .s_axi_rready   (rready ),
    .s_axi_rresp    (rresp ),
    .s_axi_rvalid   (rvalid ),
    .s_axi_wdata    (wdata ),
    .s_axi_wlast    (wlast ),
    .s_axi_wready   (wready ),
    .s_axi_wstrb    (wstrb ),
    .s_axi_wvalid   (wvalid )
);
endmodule