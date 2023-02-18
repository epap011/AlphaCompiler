analyzer: analyzer.c
	gcc -o $@ $<
analyzer.c: %.l
	flex -o $@ -i $<