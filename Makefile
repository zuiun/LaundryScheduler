CC := gcc
CFLAGS := -Wall -Wextra
CFLAGS_EX :=
CFLAGS_REL := -O3 -g
CFLAGS_DEB := -Og -g3 -fno-omit-frame-pointer

SRC_DIR := ./src
TESTS_DIR := ./tests
BUILD_DIR := ./build

SRCS := $(wildcard ${SRC_DIR}/*.c)
HDRS := $(wildcard ${SRC_DIR}/*.h)
OBJS := $(subst ${SRC_DIR},${BUILD_DIR},$(patsubst %.c,%.o,${SRCS}))
FILES := ${SRCS} ${HDRS}
PROG := scheduler

.PHONY: all build release debug check clean
release: CFLAGS_EX := ${CFLAGS_REL}
debug: CFLAGS_EX := ${CFLAGS_DEB}

# Default target
all: clean release
	@echo ${FILES}

# Compile, potentially extra flags
build: ${FILES} ${OBJS}
	mkdir -p ${BUILD_DIR}
	${CC} ${CFLAGS} ${CFLAGS_EX} ${OBJS} -o ${BUILD_DIR}/${PROG}

# Compile with release flags
release: build

# Compile with debug flags
debug: build

# Compile and run tests
check: release

# Remove build files
clean:
	@echo target 'clean'
	rm -f ${BUILD_DIR}/*

# Compile object (BULID_DIR) from source (SRC_DIR)
${BUILD_DIR}/%.o: ${SRC_DIR}/%.c
	${CC} -c ${CFLAGS} $< -o $@
