CC       = gcc --std=gnu99
SRC      = string_st.c 
OBJ      = ${SRC:.c=.o}
LIBS     = 
CFLAGS   = -Wall -g -ggdb
CDFLAGS  = -Wall -g -ggdb
LDFLAGS  = ${LIBS}
TEST     = testString
TESTDEB  = testStringDeb
TESTSRC  = testString.c
TESTOBJ  = ${TESTSRC:.c=.o}

all: ${TEST}

%.o: %.c
	${CC} -c ${CFLAGS} $<

${TEST}: ${OBJ} ${TESTOBJ}
	${CC} -o $@ ${OBJ} ${TESTOBJ} ${LDFLAGS}

test: ${TEST}
	./${TEST}

static: ${OBJ}
	ar rcs string_st.a ${OBJ}

clean:
	rm -f ${TEST} ${OBJ} ${TESTOBJ}

.PHONY: all test clean
