compile: cipher.o decrypt.o
cipher.o: cipher.c
	gcc -o cipher cipher.c 
decrypt.o: decrypt.c 
	gcc -o decrypt decrypt.c

test: test1 test2
test1: 
	./cipher 1 5 data.txt data.out
test2:
	./cipher 2 5 data.out data.bak

