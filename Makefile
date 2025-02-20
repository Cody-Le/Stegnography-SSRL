
CC = gcc
# for extension, change exe to out to use it in Linux
EXT = exe
# for clean, change del to rm
CLEAN = del

all: encode decode

encode: encode.o utility.o image.o 
	$(CC) -o encode.$(EXT) encode.o utility.o image.o 

decode: decode.o utility.o image.o
	$(CC) -o decode.$(EXT) decode.o utility.o image.o

image.o: image.c image.h
	$(CC) -c image.c image.h

utility.o: utility.c utility.h
	$(CC) -c utility.c

encode.o: encode.c encode.h utility.o image.o
	$(CC) -c encode.c encode.h

decode.o: decode.c utility.o image.o
	$(CC) -c decode.c




run_decode: decode
	./decode.$(EXT)


clean:
	$(CLEAN) *.out
	$(CLEAN) *.exe
	$(CLEAN) *.o
	$(CLEAN) *.h.gch
