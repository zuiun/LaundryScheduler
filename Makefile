CC := gcc
CFLAGS := -Wall -Wextra
CFLAGS_EX :=
CFLAGS_REL := -O3 -g
CFLAGS_DBG := -Og -g3 -fno-omit-frame-pointer

SRC_DIR := ./src
TESTS_DIR := ./tests
BLD_DIR := ./build

SRCS := scheduler.c
HDRS := constants.h
OBJS := $(patsubst %.c,%.o,$(foreach SRC,${SRCS},${BLD_DIR}/${SRC}))
FILES := $(foreach SRC,${SRCS},${SRC_DIR}/${SRC}) $(foreach HDR,${HDRS},${SRC_DIR}/${HDR})
PROG := scheduler

.PHONY: all build release debug check clean

# Default target
all: clean check print

build: ${FILES} directory ${OBJS}
	${CC} ${CFLAGS} ${CFLAGS_EX} ${OBJS} -o ${BLD_DIR}/${PROG}

release: CFLAGS_EX := ${CFLAGS_REL}
release: build

debug: CFLAGS_EX := ${CFLAGS_DBG}
debug: build

check: release
	${BLD_DIR}/${PROG} test

clean:
	rm -f ${BLD_DIR}/*

directory:
	mkdir -p ${BLD_DIR}

print:
	@echo ${FILES} ${OBJS}

${BLD_DIR}/%.o: ${SRC_DIR}/%.c
	${CC} -c ${CFLAGS} $< -o $@
