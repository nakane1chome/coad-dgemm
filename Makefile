
CXX=gcc

CFLAGS = -O3  -mavx2
LDLIBS = 
LINK.o = cc $(LDFLAGS) $(TARGET_ARCH)

SRCS=${wildcard *.c}
OBJS=${SRCS:%.c=%.o}

TARGET=test

${TARGET} : ${OBJS}

clean:
	rm -f ${TARGET} *.o
