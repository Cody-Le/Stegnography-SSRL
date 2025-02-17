
CC = gcc

encode: encode.o utility.o image.o
	$(CC) -o encode.out encode.o utility.o image.o

decode: decode.o utility.o image.o
	$(CC) -o decode.out decode.o utility.o image.o

image.o: image.c image.h
	$(CC) -c image.c

utility.o: utility.c utility.h
	$(CC) -c utility.c

encode.o: encode.c utility.o image.o
	$(CC) -c encode.c

decode.o: decode.c utility.o image.o
	$(CC) -c decode.c

run_encode: encode
	./encode.out hello


run_decode: decode
	./decode.out


clean:
	rm *.o *.out *~
