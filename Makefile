PROJECT = cg50-sdl2
CC = gcc
CFLAGS = -O3 $(shell sdl2-config --cflags)
CFLAGS += $(shell pkg-config x11 --cflags)
CFLAGS += $(shell pkg-config xtst --cflags)
CFLAGS += -MMD -MP
CFLAGS += -g
#CFLAGS += -Wa,-aghlns=$<.lst
LIBS = -O3 $(shell sdl2-config --libs)
LIBS += $(shell pkg-config x11 --libs)
LIBS += $(shell pkg-config xtst --libs)
BUILD_DIR=sdl2
SRC_DIR=src
C_FILES=$(wildcard $(SRC_DIR)/*.c)
OBJS=$(C_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS=$(OBJS:.o=.d)

run: $(BUILD_DIR)/$(PROJECT)
	./$(BUILD_DIR)/$(PROJECT)

debug: $(BUILD_DIR)/$(PROJECT)
	gdbserver localhost:2345 ./$(BUILD_DIR)/$(PROJECT) &
	gdb ./$(BUILD_DIR)/$(PROJECT) -x gdb-options.txt

$(BUILD_DIR)/$(PROJECT): $(OBJS)
	$(CC) -o $(BUILD_DIR)/$(PROJECT) $^ $(CLFAGS) $(LIBS)

$(OBJS): $(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $< 

.PHONY: clean
clean:
	rm -f $(BUILD_DIR)/*

-include $(DEPS)
