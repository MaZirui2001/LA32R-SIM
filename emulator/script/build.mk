.DEFUALT_GOAL := app

SCALA_SRCS = $(WORK_DIR)

# CC = gcc
# CXX = g++
# LD = $(CXX)

# INC_PATH = $(WORK_DIR)/include
# INCLUDE = $(addprefix -I, $(INC_PATH))

# CFLAGS = -O3 -MMD -Wall -Werror $(INCLUDE) 
# LDFLGAS = -O3

# OBJS = $(addprefix $(TAR_DIR)/, $(addsuffix .o, $(basename $(SRCS))))

# LIBS += -lSDL2 -ldl -pie

$(BINARY): FORCE
	@make -s -C ../LA32R-pipeline-scala
	@echo "$(COLOR_DBLUE)[VERILATE]$(COLOR_NONE) $(notdir $(BUILD_DIR))/VCPU"
	@mkdir -p $(BUILD_DIR)
	@verilator $(VFLAGS) $(CSRCS) $(CINC_PATH) $(VERILOG_TOP)
	@make -s -C $(BUILD_DIR) -f $(REWRITE)
	
FORCE:

# $(TAR_DIR)/%.o: %.c
# 	@mkdir -p $(dir $@) && echo "$(COLOR_DBLUE)[CC]$(COLOR_NONE) $<"
# 	@$(CC) $(CFLAGS) -c $< -o $@

# $(TAR_DIR)/%.o: %.cc
# 	@mkdir -p $(dir $@) && echo "$(COLOR_DBLUE)[CXX]$(COLOR_NONE) $<"
# 	@$(CXX) $(CFLAGS) -c $< -o $@

app: $(BINARY)
	

ARGS = 
run: $(BINARY)
	@echo "$(COLOR_YELLOW)[RUN]$(COLOR_NONE) build/$(notdir $<)"
	@$(BINARY) $(IMG) $(ARGS)

gdb: $(BINARY)
	@echo "$(COLOR_YELLOW)[GDB]$(COLOR_NONE) build/$(notdir $<)"
	@gdb $(SIM_PATH) $(BINARY) $(IMG)

clean:
	rm -rf $(BUILD_DIR)


