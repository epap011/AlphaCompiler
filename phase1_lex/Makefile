all: scanner.c scanner

scanner.c: scanner.l
	flex -o $@ -i scanner.l

scanner: scanner.c
	gcc -o $@ $<

clean:
	rm -f scanner scanner.c *.o