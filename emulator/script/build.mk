

SIMU_DIR = $(abspath $(WORK_DIR)/../simulator)
SIMUISO = $(SIMU_DIR)/build/simulator-so

SCALA_DIR = $(abspath $(WORK_DIR)/../LA32R-pipeline-scala)

SCALA_SRCS := $(shell find $(SCALA_DIR)/src/main/scala -name "*.scala")
CSRCS := $(shell find $(WORK_DIR)/src -name "*.cc")

VERILOG := $(shell find $(SCALA_DIR)/verilog -name "*.sv")

all: $(BINARY) 

$(SIMUISO):
	@echo "$(COLOR_YELLOW)[Make DIFF]$(COLOR_NONE) $(notdir $(SIMU_DIR))/build/simulator-so"
	@make -s -C $(SIMU_DIR)

$(VERILOG): $(SCALA_SRCS)
	@make -s -C $(SCALA_DIR) verilog

$(BINARY): $(VERILOG) $(CSRCS)
	@echo "$(COLOR_DBLUE)[VERILATE]$(COLOR_NONE) $(notdir $(BUILD_DIR))/VCPU"
	@mkdir -p $(BUILD_DIR)
	@verilator $(VFLAGS) $(CSRCS) $(CINC_PATH) $(VERILOG_TOP)
	@make -s -C $(BUILD_DIR) -f $(REWRITE)



ARGS = 
run: $(BINARY) $(SIMUISO)
	@echo "$(COLOR_YELLOW)[RUN]$(COLOR_NONE) build/$(notdir $<)"
	$(BINARY) $(IMG) $(SIMUISO) $(ARGS)

gdb: $(BINARY)
	@echo "$(COLOR_YELLOW)[GDB]$(COLOR_NONE) build/$(notdir $<)"
	gdb --args  $(BINARY) $(IMG) $(SIMUISO) $(ARGS)

clean:
	rm -rf $(BUILD_DIR)

