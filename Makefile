PROG      = getstat
CONF      = config
CC        = gcc
PREFIX   ?= /usr/local
SUBPREFIX = ${PREFIX}/bin

LIBS      = -lX11 -lmpdclient
CFLAGS   += -std=c99 -pedantic -Wall -Wextra

${PROG}: ${PROG}.c ${CONF}.h
	@${CC} ${CFLAGS} ${LIBS} -o ${PROG} ${PROG}.c
	@strip ${PROG}

install:
	install -Dm755 ${PROG} ${DESTDIR}${SUBPREFIX}/${PROG}

uninstall:
	rm -f ${SUBPREFIX}/${PROG}

clean:
	rm -f ${PROG}

.PHONY: all clean install uninstall
