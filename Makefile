PROJECT = cg50-sdl2
CC = gcc
CFLAGS = -O3 $(shell sdl2-config --cflags)
CFLAGS += -MMD -MP
#CFLAGS += -Wa,-aghlns=$<.lst
LIBS = -O3 $(shell sdl2-config --libs)
BUILD_DIR=sdl2
SRC_DIR=src
C_FILES=$(wildcard $(SRC_DIR)/*.c)
OBJS=$(C_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS=$(OBJS:.o=.d)

all: $(BUILD_DIR)/$(PROJECT)
	./$(BUILD_DIR)/$(PROJECT)

$(BUILD_DIR)/$(PROJECT): $(OBJS)
	$(CC) -o $(BUILD_DIR)/$(PROJECT) $^ $(CLFAGS) $(LIBS)

$(OBJS): $(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $< 

.PHONY: clean
clean:
	rm -f $(BUILD_DIR)/*

-include $(DEPS)
