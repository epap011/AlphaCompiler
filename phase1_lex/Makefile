all:
	make scanner.c scanner
scanner.c: scanner.l
	flex -o $@ -i scanner.l
scanner: scanner.c
	gcc -o $@ $<