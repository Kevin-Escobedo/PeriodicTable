CC=g++
CFLAGS=-std=c++17 -Wpedantic -Wall -Werror -Wextra -Weffc++ -Wzero-as-null-pointer-constant
OPTIMIZE=-O2

FILES=Database.h Database.cpp PeriodicDatabase.h PeriodicDatabase.cpp main.cpp
LIBRARIES=-l sqlite3

TARGET=periodic

all: ${TARGET}
${TARGET}: ${FILES}
	${CC} ${CFLAGS} ${OPTIMIZE} ${FILES} ${LIBRARIES} -o ${TARGET}

run: ${TARGET}
	valgrind ./${TARGET}

clean:
	/bin/rm -f ${TARGET}

