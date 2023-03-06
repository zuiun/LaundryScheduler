CC := gcc
CFLAGS := -Wall -Wextra
CFLAGS_EX :=
CFLAGS_REL := -O3 -g -DNDEBUG
CFLAGS_DBG := -g3 -fno-omit-frame-pointer

SRC_DIR := ./src
TESTS_DIR := ./tests
BLD_DIR := ./build

SRCS := $(wildcard ${SRC_DIR}/*.c)
HDRS := $(wildcard ${SRC_DIR}/*.h)
OUTS := $(patsubst %.tst,%.out,$(wildcard ${TESTS_DIR}/*.tst))
OBJS := $(patsubst ${SRC_DIR}/%.c,${BLD_DIR}/%.o,${SRCS})
FILES := ${SRCS} ${HDRS}
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

check: release ${OUTS}

clean:
	rm -f ${BLD_DIR}/*
	rm -f ${TESTS_DIR}/*.out

directory:
	mkdir -p ${BLD_DIR}

print:
	@echo ${FILES} ${OBJS} ${OUTS}

${BLD_DIR}/%.o: ${SRC_DIR}/%.c
	${CC} -c ${CFLAGS} ${CFLAGS_EX} $< -o $@

${TESTS_DIR}/%.out:
	@echo
	${BLD_DIR}/${PROG} file $(patsubst %.out,%.tst,$@) > /dev/null
	-cmp $@ $(patsubst %.out,%.chk,$@)
