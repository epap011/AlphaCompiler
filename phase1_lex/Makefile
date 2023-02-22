all: scanner.c scanner.o token.o scanner
	rm -f *.o

scanner.c: scanner.l
	flex -o $@ -i scanner.l

scanner.o: scanner.c
	gcc -c $<

token.o: token.c
	gcc -c $<

scanner: scanner.o token.o
	gcc -o $@ $^

clean:
	rm -f scanner scanner.c