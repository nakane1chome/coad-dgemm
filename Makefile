MACHINE=$(shell uname -m)

CXX=g++

CXXFLAGS = -O3
ifeq (${MACHINE},x86_64)
CXXFLAGS+=  -mavx2
endif
ifeq (${MACHINE},aarch64)
CXXFLAGS+= 
endif

LDLIBS = 
LINK.o = g++ $(LDFLAGS) $(TARGET_ARCH)

SRCS=${wildcard *.cpp}
OBJS=${SRCS:%.cpp=%.o}

TARGET=test

${TARGET} : ${OBJS}

clean:
	rm -f ${TARGET} *.o


info :
	@echo ${MACHINE}
