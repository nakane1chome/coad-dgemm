MACHINE=$(shell uname -m)

CXX=gcc

CFLAGS = -O3
ifeq (${MACHINE},x86_64)
CFLAGS+=  -mavx2
endif
ifeq (${MACHINE},aarch64)
CFLAGS+= 
endif

LDLIBS = 
LINK.o = cc $(LDFLAGS) $(TARGET_ARCH)

SRCS=${wildcard *.c}
OBJS=${SRCS:%.c=%.o}

TARGET=test

${TARGET} : ${OBJS}

clean:
	rm -f ${TARGET} *.o


info :
	@echo ${MACHINE}
