CC=gcc
all : test.o prtfmt.a
	$(CC) -o test test.o prtfmt.a
prtfmt : prtfmt.o
	ar rscv prtfmt.a prtfmt.o
test.o : test.c
	$(CC) -c test.c
prtfmt.o : prtfmt.c
	$(CC) -c prtfmt.c
clean :
	rm -f prtfmt.o test.o
