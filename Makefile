BIN_DIR = /usr/bin
TARGET = hitorkill
CXX = gcc
SRCS = main.c
INSTALL = /usr/bin/install -c -D

all: build

build: ${SRCS}
	${CXX} ${SRCS} -o ${TARGET}

install: build
	${INSTALL} ${TARGET} ${BIN_DIR}/${TARGET}

clean:
	rm -f ${TARGET}
