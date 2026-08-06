PROJECT = test

BUILD_DIR=build
SRC_DIR=src

CC = gcc
CFLAGS = -O2
#Silence warning for assembly files re non-executable stack
CFLAGS += -z noexecstack
C_FILES=$(wildcard $(SRC_DIR)/*.c)
ASM_FILES=$(wildcard $(SRC_DIR)/*.S)
OBJS=$(C_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
OBJS_ASM=$(ASM_FILES:$(SRC_DIR)/%.S=$(BUILD_DIR)/%.o)

#Convert C to ASM with GCC 15.1 using musttail
MANUAL_DIR=$(SRC_DIR)/manual
MANUAL_ASM_DIR=$(MANUAL_DIR)/asm
MANUAL_FLAGS = -O2 -S
MANUAL_C_FILES=$(wildcard $(MANUAL_DIR)/*.c)
MANUAL_ASM_FILES=$(MANUAL_C_FILES:$(MANUAL_DIR)/%.c=$(MANUAL_ASM_DIR)/%.s)
OBJS_MANUAL=$(MANUAL_ASM_FILES:$(MANUAL_ASM_DIR)/%.s=$(BUILD_DIR)/%.o)

run: $(BUILD_DIR)/$(PROJECT)
	./$(BUILD_DIR)/$(PROJECT)

$(BUILD_DIR)/$(PROJECT): $(OBJS) $(OBJS_ASM) $(OBJS_MANUAL)
	#Link all object files
	#Debug: $(MANUAL_C_FILES)
	$(CC) -o $(BUILD_DIR)/$(PROJECT) $^ $(CFLAGS)

$(OBJS): $(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	#Generate object files for C files
	$(CC) $(CFLAGS) -c -o $@ $< 

$(OBJS_ASM): $(BUILD_DIR)/%.o: $(SRC_DIR)/%.S
	#Generate object files for hand-written assembly files
	$(CC) $(CFLAGS) -c -o $@ $< 

$(MANUAL_ASM_FILES): $(MANUAL_ASM_DIR)/%.s: $(MANUAL_DIR)/%.c
	#Generate assembly files from C files but no object file
	$(CC) $(MANUAL_FLAGS) -o $@ $< 

$(OBJS_MANUAL): $(BUILD_DIR)/%.o: $(MANUAL_ASM_DIR)/%.s
    #Generate object files from assembly files generated from C
	$(CC) $(CFLAGS) -c -o $@ $< 

.PHONY: clean
clean:
	rm -f $(BUILD_DIR)/*
	rm -f $(MANUAL_ASM_DIR)/*

