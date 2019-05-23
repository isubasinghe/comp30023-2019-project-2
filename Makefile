CC	=	gcc

CFLAGS	=	-O3 -Wall -Werror -pedantic -std=gnu99
EXE = crack
OBJ = main.o dt_hashtable.o pwcrack.o bitreader.o sha256.o pwgen.o

all: $(EXE)

debug: CFLAGS = -Wall -Werror -pedantic -lpthread -std=gnu99 -O0 -g -DDEBUG

main.o: dt_hashtable.o sha256.o bitreader.o pwcrack.o pwgen.o
pwcrack.o: pwcrack.h bitreader.h
pwgen.o: pwgen.h
bitreader.o: bitreader.h dt_hashtable.o
dt_hashtable.o: dt_hashtable.h
sha256.o: sha256.h



debug: $(OBJ)
	$(CC) -o $(EXE) $(OBJ) $(CFLAGS)

	
$(EXE): $(OBJ)
		$(CC) -o $(EXE) $(OBJ) $(CFLAGS)

.PHONY: clean cleanly

clean:
	rm -rf $(OBJ)
