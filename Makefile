PROJECT = cg50-sdl2

BUILD_DIR=build-sh4
SRC_DIR=src

CC = sh4eb-linux-musl-gcc
CFLAGS = -O2 -g -static
#Recompile if file includes header that changed
CFLAGS += -MMD -MP
#Assembly listing for each source file
CFLAGS += -Wa,-aghlns=$(BUILD_DIR)/$(notdir $<).lst
#Silence warning for assembly files re non-executable stack
CFLAGS += -z noexecstack
C_FILES=$(wildcard $(SRC_DIR)/*.c)
ASM_FILES=$(wildcard $(SRC_DIR)/*.S)
OBJS=$(C_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
OBJS_ASM=$(ASM_FILES:$(SRC_DIR)/%.S=$(BUILD_DIR)/%.o)

DEPS=$(OBJS:.o=.d)

run: $(BUILD_DIR)/$(PROJECT)
	./$(BUILD_DIR)/$(PROJECT)

debug: $(BUILD_DIR)/$(PROJECT)
	qemu-sh4eb-static -g 2345 ./$(BUILD_DIR)/$(PROJECT) &
	gdb-multiarch --quiet -x gdb-options.txt ./$(BUILD_DIR)/$(PROJECT)

log: $(BUILD_DIR)/$(PROJECT)
	-./$(BUILD_DIR)/$(PROJECT)
	cat log.txt
	ls -l log.txt | awk '{print "Log file size: " $$5}'

compile: $(BUILD_DIR)/$(PROJECT)
	#Compile only

$(BUILD_DIR)/$(PROJECT): $(OBJS) $(OBJS_ASM)
	$(CC) -o $(BUILD_DIR)/$(PROJECT) $^ $(CFLAGS)

$(OBJS): $(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $< 

$(OBJS_ASM): $(BUILD_DIR)/%.o: $(SRC_DIR)/%.S
	$(CC) $(CFLAGS) -c -o $@ $< 

.PHONY: clean
clean:
	rm -f $(BUILD_DIR)/*

-include $(DEPS)
