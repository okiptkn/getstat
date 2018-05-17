OBJ       = getstat
PREFIX   ?= /usr/local
SUBPREFIX = ${PREFIX}/bin
CC        = gcc

LIBS      = -lX11 -lmpdclient
CFLAGS   += -std=c99 -pedantic -Wall -Wextra

${OBJ}: ${OBJ}.c ${OBJ}.h
	@${CC} ${CFLAGS} ${LIBS} -o ${OBJ} ${OBJ}.c
	@strip ${OBJ}

install:
	install -Dm755 ${OBJ} ${DESTDIR}${SUBPREFIX}/${OBJ}

uninstall:
	rm -f ${SUBPREFIX}/${OBJ}

clean:
	rm -f ${OBJ}

.PHONY: all clean install uninstall
