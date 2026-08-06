PROJECT = prog-tools

BUILD_DIR=build-sh4
INCLUDE_DIR=include
SRC_DIR=src
TESTS_DIR=tests
UNITY_DIR=unity

CC = sh4eb-linux-musl-gcc
CFLAGS = -O2 -g -static -I$(INCLUDE_DIR) -I$(UNITY_DIR)
#Recompile if file includes header that changed
CFLAGS += -MMD -MP
#Silence warning for assembly files re non-executable stack
CFLAGS += -z noexecstack

#Convert certain C files to ASM with GCC 15.1 using musttail
PRIM_FLAGS = -O2 -S -I$(INCLUDE)
PRIM_C_FILES = src/forth-primitives.c src/forth-locals.c src/forth-check.c
PRIM_ASM_FILES=$(PRIM_C_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.s)
OBJS_PRIM=$(PRIM_ASM_FILES:$(BUILD_DIR)/%.s=$(BUILD_DIR)/%.o)

#Source files
C_FILES=$(filter-out $(PRIM_C_FILES), $(wildcard $(SRC_DIR)/*.c))
ASM_FILES=$(wildcard $(SRC_DIR)/*.S)
OBJS=$(C_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
OBJS_ASM=$(ASM_FILES:$(SRC_DIR)/%.S=$(BUILD_DIR)/%.o)

#Test files
TEST_FILES=$(wildcard $(TESTS_DIR)/*.c)
OBJS_TEST=$(TEST_FILES:$(TESTS_DIR)/%.c=$(BUILD_DIR)/%.o)
PROGS_TEST=$(TEST_FILES:$(TESTS_DIR)/%.c=$(BUILD_DIR)/%)
OBJS_TEST_COMBINED=$(filter-out $(BUILD_DIR)/main.o, $(OBJS)) $(OBJS_ASM) $(OBJS_PRIM) $(BUILD_DIR)/unity.o

#For recompiling when headers have changed
DEPS=$(OBJS:.o=.d)

run: $(BUILD_DIR)/$(PROJECT)
	./$(BUILD_DIR)/$(PROJECT)

tests: $(PROGS_TEST)
	@#@$(foreach test,$^,./$(test);)
	./test-runner.py $^

debug_old: $(BUILD_DIR)/$(PROJECT)
	qemu-sh4eb-static -g 2345 ./$(BUILD_DIR)/$(PROJECT) &
	gdb-multiarch --quiet -x gdb-options.txt ./$(BUILD_DIR)/$(PROJECT)

debug: $(BUILD_DIR)/$(PROJECT)
	qemu-sh4eb-static -g 2345 ./$(BUILD_DIR)/$(PROJECT)

log: $(BUILD_DIR)/$(PROJECT)
	-./$(BUILD_DIR)/$(PROJECT)
	cat log.txt
	ls -l log.txt | awk '{print "Log file size: " $$5}'

compile: $(BUILD_DIR)/$(PROJECT)
	#Compile only

$(BUILD_DIR)/$(PROJECT): $(OBJS) $(OBJS_ASM) $(OBJS_PRIM)
	$(CC) -o $(BUILD_DIR)/$(PROJECT) $^ $(CFLAGS)

$(OBJS): $(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(LIST_FLAGS) -c -o $@ $< 

$(OBJS_ASM): $(BUILD_DIR)/%.o: $(SRC_DIR)/%.S
	$(CC) $(CFLAGS) -c -o $@ $< 

$(PRIM_ASM_FILES): $(BUILD_DIR)/%.s: $(SRC_DIR)/%.c
	$(CC) $(PRIM_FLAGS) -o $@ $< 

$(OBJS_PRIM): $(BUILD_DIR)/%.o: $(BUILD_DIR)/%.s
	$(CC) $(CFLAGS) -c -o $@ $< 

#Unit tests
$(OBJS_TEST): $(BUILD_DIR)/%.o: $(TESTS_DIR)/%.c
	$(CC) $(CFLAGS) $(LIST_FLAGS) -c -o $@ $< 

$(BUILD_DIR)/unity.o: $(UNITY_DIR)/unity.c
	$(CC) $(CFLAGS) $(LIST_FLAGS) -c -o $@ $< 

$(PROGS_TEST): $(OBJS_TEST_COMBINED) $(OBJS_TEST)
	$(CC) -o $@ $(OBJS_TEST_COMBINED) $@.o $(CFLAGS)

.PHONY: clean
clean:
	rm -f $(BUILD_DIR)/*

-include $(DEPS)
