TARGET = bin
CC = gcc
CFLAGA = -g -DDEBUG -lpthread
SRCFILES = $(wildcard *.c)
OBJS = $(patsubst %.c,%.o,${SRCFILES})

${TARGET}:${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o ${TARGET}
%.o : %.c
	${CC} ${CFLAGS} -c $<
clean:
	@echo "rm project ..."
	-rm -rf ${TARGET} ${OBJS}
	@echo "rm complete ..."

.PHONY:clean
