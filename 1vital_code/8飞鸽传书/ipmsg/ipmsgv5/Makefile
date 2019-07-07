#makefile
FLAGS = -g -DDEBUG
TARGET = ipmsg
CC = gcc
SRC_FILES = $(wildcard *.c)
OBJS = $(patsubst %.c, %.o, $(SRC_FILES))


${TARGET}: ${OBJS}
	${CC} ${FLAGS} $^ -o $@ -lpthread


%.o : %.c
	${CC} ${FLAGS} -c $<

.PHONY:clean
clean:
	@echo "rm project ..."
	-rm -rf ${OBJS} ${TARGET}
	@echo "rm complete ..."
