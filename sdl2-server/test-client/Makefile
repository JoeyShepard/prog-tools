PROJECT=test-client

BUILD_DIR=build
SRC_DIR=src

CC = sh4eb-linux-musl-gcc
CFLAGS += -MMD -MP
CFLAGS += -g
CFLAGS += -static
CFLAGS += -Wa,-aghlns=$(BUILD_DIR)/$(notdir $<).lst
C_FILES=$(wildcard $(SRC_DIR)/*.c)
OBJS=$(C_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

DEPS=$(OBJS:.o=.d)

run: $(BUILD_DIR)/$(PROJECT)
	./$(BUILD_DIR)/$(PROJECT)

debug: $(BUILD_DIR)/$(PROJECT)
	gdbserver localhost:2345 ./$(BUILD_DIR)/$(PROJECT) &
	gdb ./$(BUILD_DIR)/$(PROJECT) -x gdb-options.txt

compile: $(BUILD_DIR)/$(PROJECT)
	#Compile only

$(BUILD_DIR)/$(PROJECT): $(OBJS)
	$(CC) -o $(BUILD_DIR)/$(PROJECT) $^ $(CFLAGS) $(LIBS)

$(OBJS): $(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $< 

.PHONY: clean
clean:
	rm -f $(BUILD_DIR)/*

-include $(DEPS)

