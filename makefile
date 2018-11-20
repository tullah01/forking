all: forking.o
	gcc -o out forking.o

forking.o: forking.c
	gcc -c forking.c

run:
	./out

clean: 
	rm out
	rm *.o
