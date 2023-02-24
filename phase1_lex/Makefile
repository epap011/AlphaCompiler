#Compiler
CC = gcc

#compiler flags
CFLAGS = -Wall

#File names (no extension)
SCANNER_FILE = scanner
BYHAND_FILE  = byhand_lex

#Targets
SCANNER_TARGET = scanner
BYHAND_TARGET  = bonus

all: $(SCANNER_FILE).c $(SCANNER_FILE).o $(SCANNER_TARGET) token.o 
	rm -f *.o

$(SCANNER_TARGET): $(SCANNER_FILE).o token.o
	$(CC) $(CFLAGS) -o $@ $^

$(BYHAND_TARGET): $(BYHAND_FILE).o
	$(CC) $(CFLAGS) -o $@ $^

$(SCANNER_FILE).o: $(SCANNER_FILE).c
	$(CC) $(CFLAGS) -c $<

$(BYHAND_FILE).o: $(BYHAND_FILE).c
	$(CC) $(CFLAGS) -c $<

token.o: token.c
	$(CC) $(CFLAGS) -c $<

$(SCANNER_FILE).c: $(SCANNER_FILE).l
	flex -o $@ -i $(SCANNER_FILE).l

clean:
	rm -f *.o $(SCANNER_TARGET) $(SCANNER_FILE).c $(BYHAND_TARGET)