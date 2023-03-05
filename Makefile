CC := gcc
CFLAGS := -Wall -Wextra
CFLAGS_EX :=
CFLAGS_REL := -O3 -g -DNDEBUG
CFLAGS_DBG := -g3 -fno-omit-frame-pointer

SRC_DIR := ./src
TESTS_DIR := ./tests
BLD_DIR := ./build

# Add tester.c when ready
SRCS := auxiliary.c scheduler.c priority_queue.c
HDRS := auxiliary.h scheduler.h priority_queue.h
OBJS := $(patsubst %.c,%.o,$(foreach SRC,${SRCS},${BLD_DIR}/${SRC}))
FILES := $(foreach SRC,${SRCS},${SRC_DIR}/${SRC}) $(foreach HDR,${HDRS},${SRC_DIR}/${HDR})
PROG := scheduler

.PHONY: all build release debug check clean

# Default target
all: release print

build: ${FILES} directory ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o ${BLD_DIR}/${PROG}

release: CFLAGS_EX := ${CFLAGS_REL}
release: clean build

debug: CFLAGS_EX := ${CFLAGS_DBG}
debug: clean build

check: release
	${BLD_DIR}/${PROG} file

clean:
	rm -f ${BLD_DIR}/*

directory:
	mkdir -p ${BLD_DIR}

print:
	@echo ${FILES} ${OBJS}

${BLD_DIR}/%.o: ${SRC_DIR}/%.c
	${CC} -c ${CFLAGS} ${CFLAGS_EX} $< -o $@
