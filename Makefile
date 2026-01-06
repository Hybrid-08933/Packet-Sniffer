TARGET_EXEC := sniffer

BUILD_DIR := ./build
SRC_DIRS := ./src

# Find all the C files
SRCS := $(shell find $(SRC_DIRS) -name '*.c' -or -name '*.s')

# Prepand BUILD_DIR and replace .c with .o to every source file
OBJS := $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRCS))

# Replace .o with .d
DEPS := $(OBJS:.o=.d)

# Every folder in SRC_DIRS will need to be passed to GCC so that it can find header files
INC_DIRS := $(shell find $(SRC_DIRS) -type d)
# Add a prefix to INC_DIRS, So moduleA would become -ImoduleA, GCC understands this -I flag
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# The -MMD and -MP flags together generate Makefiles for us
# These files will have .d instead of .o as the output.
CPPFLAGS := $(INC_FLAGS) -MMD -MP

# The compiler
CC := gcc

# Compiler Flags
CFLAGS := -Wall -Wextra -g

# Linker flags
LDFLAGS :=

# The final build step
$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# Build step for C sources
$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@


.PHONY: clean
clean:
	rm -r $(BUILD_DIR)

# Include the .d Makefiles. The - at the front suppresses the errors of missing
# Makefiles. Initially, all the .d files will be missing, and we don't want those
# errors to show up.
-include $(DEPS)
