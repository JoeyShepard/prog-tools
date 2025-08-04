PROJECT = cg50-sdl2

BUILD_DIR=build-sh4
SRC_DIR=src

CC = sh4eb-linux-musl-gcc
CFLAGS = -O2 -g -static
CFLAGS += -MMD -MP
CFLAGS += -Wa,-aghlns=$(BUILD_DIR)/$(notdir $<).lst
C_FILES=$(wildcard $(SRC_DIR)/*.c)
OBJS=$(C_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

DEPS=$(OBJS:.o=.d)

run: $(BUILD_DIR)/$(PROJECT)
	./$(BUILD_DIR)/$(PROJECT)

debug: $(BUILD_DIR)/$(PROJECT)
	gdbserver localhost:2345 ./$(BUILD_DIR)/$(PROJECT) &
	gdb ./$(BUILD_DIR)/$(PROJECT) -x gdb-options.txt

log: $(BUILD_DIR)/$(PROJECT)
	-./$(BUILD_DIR)/$(PROJECT)
	cat log.txt
	ls -l log.txt | awk '{print "Log file size: " $$5}'

compile: $(BUILD_DIR)/$(PROJECT)
	#Compile only

$(BUILD_DIR)/$(PROJECT): $(OBJS)
	$(CC) -o $(BUILD_DIR)/$(PROJECT) $^ $(CFLAGS)

$(OBJS): $(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $< 

.PHONY: clean
clean:
	rm -f $(BUILD_DIR)/*

-include $(DEPS)
