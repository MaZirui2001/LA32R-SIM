.DEFUALT_GOAL := app

CC = gcc
CXX = g++
LD = $(CXX)

WORK_DIR = $(shell pwd)
BUILD_DIR = $(WORK_DIR)/build
TAR_DIR = $(BUILD_DIR)/obj

BINARY = $(BUILD_DIR)/simulator

INC_PATH = $(WORK_DIR)/include
INCLUDE = $(addprefix -I, $(INC_PATH))

CFLAGS = -O3 -MMD -Wall -Werror $(INCLUDE) 
LDFLGAS = -O3

OBJS = $(addprefix $(TAR_DIR)/, $(addsuffix .o, $(basename $(SRCS))))

LIBS += -lSDL2 -ldl -pie


$(TAR_DIR)/%.o: %.c
	@mkdir -p $(dir $@) && echo "$(COLOR_DBLUE)[CC]$(COLOR_NONE) $<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(TAR_DIR)/%.o: %.cc
	@mkdir -p $(dir $@) && echo "$(COLOR_DBLUE)[CXX]$(COLOR_NONE) $<"
	@$(CXX) $(CFLAGS) -c $< -o $@

app: $(BINARY)

$(BINARY): $(OBJS)
	@mkdir -p $(dir $@) && echo "$(COLOR_YELLOW)[LD]$(COLOR_NONE) build/$(notdir $@)"
	@$(LD) $(LDFLGAS)  $^ -o $@ $(LIBS)

ARGS = 
run: $(BINARY)
	@echo "$(COLOR_YELLOW)[RUN]$(COLOR_NONE) build/$(notdir $<)"

	@$(BINARY) $(IMG) $(ARGS)

clean:
	rm -rf $(BUILD_DIR)


