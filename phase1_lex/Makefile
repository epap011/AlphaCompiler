#Compiler
CC = gcc

#compiler flags
CFLAGS = -Wall

#File names (no extension)
SCANNER = scanner
BYHAND  = byhand_lex

#Targets
SCANNER_TARGET = scanner
BYHAND_TARGET  = bonus

all: $(SCANNER).c $(SCANNER).o $(SCANNER) token.o 
	rm -f *.o

$(SCANNER_TARGET): $(SCANNER).o token.o
	$(CC) $(CFLAGS) -o $@ $^

$(BYHAND_TARGET): $(BYHAND).o
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
	rm -f *.o $(SCANNER_TARGET) $(SCANNER).c $(BYHAND_TARGET)