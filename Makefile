CC := gcc
CFLAGS := -Wall -Wextra

SRC_DIR := ./src
TESTS_DIR := ./tests
BUILD_DIR := ./build

SRCS := $(wildcard ${SRC_DIR}/*.c)
HEADERS := $(wildcard ${SRC_DIR}/*.h)
OBJECTS := $(subst ${SRC_DIR},${BUILD_DIR},$(patsubst %.c,%.o,${SRCS}))
FILES := ${SRCS} ${HEADERS}

.PHONY: all clean
all: clean scheduler debug check
	@echo target 'all'
	@echo ${FILES}

scheduler: ${FILES} ${OBJECTS}
	@echo target 'scheduler'
	mkdir -p ${BUILD_DIR}
	${CC} ${CFLAGS} ${OBJECTS} -o ${BUILD_DIR}/$@

#debug: ${FILES} ${OBJECTS}
debug:
	@echo target 'debug'
#	${CC} -c ${CFLAGS} $^ -o $@

check:
	@echo target 'check'

clean:
	@echo target 'clean'
	rm -f ${BUILD_DIR}/*

${BUILD_DIR}/%.o: ${SRC_DIR}/%.c
	${CC} -c ${CFLAGS} $< -o $@
