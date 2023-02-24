#Compiler
CC = gcc

#compiler flags
CFLAGS = -Wall

#File names (no extension)
SCANNER = scanner
BYHAND  = byhand_lex

all: $(SCANNER).c $(SCANNER).o $(SCANNER) token.o 
	rm -f *.o

scanner: $(SCANNER).o token.o
	$(CC) $(CFLAGS) -o $@ $^

bonus: $(BYHAND).o
	$(CC) $(CFLAGS) -o $@ $^

$(SCANNER).o: $(SCANNER).c
	$(CC) $(CFLAGS) -c $<

$(BYHAND).o: $(BYHAND).c
	$(CC) $(CFLAGS) -c $<

token.o: token.c
	$(CC) $(CFLAGS) -c $<

$(SCANNER).c: $(SCANNER).l
	flex -o $@ -i $(SCANNER).l

clean:
	rm -f *.o $(SCANNER) $(SCANNER).c $(BYHAND)