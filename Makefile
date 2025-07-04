PROJECT = cg50-sdl2

BUILD_DIR=sdl2
SRC_DIR=src

CC = gcc
CFLAGS = -O3 $(shell sdl2-config --cflags)
CFLAGS += -MMD -MP
CFLAGS += -g
CFLAGS += -Wa,-aghlns=$(BUILD_DIR)/$(notdir $<).lst
LIBS = -O3 $(shell sdl2-config --libs)
C_FILES=$(wildcard $(SRC_DIR)/*.c)
OBJS=$(C_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
#Compile C files needing __attribute__((musttail)) separately with containerized gcc 15
C_FILES_GCC15=$(wildcard $(SRC_DIR)/custom/gcc-15/*.c)
OBJS_GCC15=$(C_FILES_GCC15:$(SRC_DIR)/custom/gcc-15/%.c=$(BUILD_DIR)/%.o)

DEPS=$(OBJS:.o=.d)
DEPS+=$(OBJS_GCC15:.o=.d)

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

$(BUILD_DIR)/$(PROJECT): $(OBJS) $(OBJS_GCC15)
	$(CC) -o $(BUILD_DIR)/$(PROJECT) $^ $(CLFAGS) $(LIBS)

$(OBJS): $(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $< 

$(OBJS_GCC15): $(BUILD_DIR)/%.o: $(SRC_DIR)/custom/gcc-15/%.c
	gcc-15 $(CFLAGS) -c -o $@ $< 

.PHONY: clean
clean:
	rm -f $(BUILD_DIR)/*

-include $(DEPS)
