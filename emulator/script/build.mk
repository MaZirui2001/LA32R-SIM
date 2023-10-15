.DEFUALT_GOAL := app
SCALA_SRCS = $(WORK_DIR)
SIMU_DIR = $(abspath $(WORK_DIR)/../simulator)
SIMUISO = $(SIMU_DIR)/build/simulator-so


# CC = gcc
# CXX = g++
# LD = $(CXX)

# INC_PATH = $(WORK_DIR)/include
# INCLUDE = $(addprefix -I, $(INC_PATH))

# CFLAGS = -O3 -MMD -Wall -Werror $(INCLUDE) 
# LDFLGAS = -O3

# OBJS = $(addprefix $(TAR_DIR)/, $(addsuffix .o, $(basename $(SRCS))))

# LIBS += -lSDL2 -ldl -pie

$(SIMUISO):
	@echo "$(COLOR_YELLOW)[Make DIFF]$(COLOR_NONE) $(notdir $(SIMU_DIR))/build/simulator-so"
	@make -s -C $(SIMU_DIR)

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

app: $(BINARY) $(SIMUISO)
	

ARGS = 
run: $(BINARY) $(SIMUISO)
	@echo "$(COLOR_YELLOW)[RUN]$(COLOR_NONE) build/$(notdir $<)"
	$(BINARY) $(IMG) $(SIMUISO) $(ARGS)

gdb: $(BINARY)
	@echo "$(COLOR_YELLOW)[GDB]$(COLOR_NONE) build/$(notdir $<)"
	@gdb $(SIM_PATH) $(BINARY) $(IMG)

clean:
	rm -rf $(BUILD_DIR)


