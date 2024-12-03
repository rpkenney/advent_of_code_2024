all: part1 part2

part1: part1.o radixsort.o file.o
	gcc -Wall part1.o radixsort.o file.o -o part1 -lm

part2: part2.o radixsort.o file.o
	gcc -Wall part2.o radixsort.o file.o -o part2 -lm

part1.o: part1.c radixsort.h file.h
	gcc -Wall -c part1.c -o part1.o

part2.o: part2.c radixsort.h file.h
	gcc -Wall -c part2.c -o part2.o


radixsort.o: radixsort.c radixsort.h
	gcc -Wall -c radixsort.c -o radixsort.o

file.o: file.c file.h
	gcc -Wall -c file.c -o file.o


clean:
	rm -f part1 part2 *.o
