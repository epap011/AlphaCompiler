all:
	make analyzer.c analyzer
analyzer.c: scanner.l
	flex -o $@ -i scanner.l
analyzer: analyzer.c
	gcc -o $@ $<