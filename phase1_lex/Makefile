#Directory folder names
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

#Compiler, Compiler flags and Includes
CC       = gcc
CFLAGS   = -Wall
CPPFLAGS = -Iinclude

#File names (no extension)
SCANNER_FILE_NAME = scanner
BYHAND_FILE_NAME  = byhand
TOKEN_FILE_NAME	  = token

#Targets names (only for make)
SCANNER_TARGET = flex
BYHAND_TARGET  = byhand

#all: $(SCANNER_FILE_NAME).c $(SCANNER_FILE_NAME).o $(SCANNER_TARGET) token.o 
#	rm -f *.o

###################### T A R G E T S###################################
$(SCANNER_TARGET): $(BIN_DIR) $(SCANNER_FILE_NAME).o $(TOKEN_FILE_NAME).o
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$(SCANNER_FILE_NAME) $(OBJ_DIR)/$(SCANNER_FILE_NAME).o $(OBJ_DIR)/$(TOKEN_FILE_NAME).o

$(BYHAND_TARGET): $(BIN_DIR) $(BYHAND_FILE_NAME).o $(TOKEN_FILE_NAME).o 
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$(SCANNER_FILE_NAME) $(OBJ_DIR)/$(BYHAND_FILE_NAME).o $(OBJ_DIR)/$(TOKEN_FILE_NAME).o 
#######################################################################

##################### O B J E C T - F I L E S #########################
$(SCANNER_FILE_NAME).o: $(SRC_DIR)/$(SCANNER_FILE_NAME).c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ -o $(OBJ_DIR)/$@

$(BYHAND_FILE_NAME).o: $(SRC_DIR)/$(BYHAND_FILE_NAME).c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ -o $(OBJ_DIR)/$@

$(TOKEN_FILE_NAME).o: $(SRC_DIR)/$(TOKEN_FILE_NAME).c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ -o $(OBJ_DIR)/$@
#######################################################################

$(SRC_DIR)/$(SCANNER_FILE_NAME).c: $(SRC_DIR)/$(SCANNER_FILE_NAME).l
	flex -o $@ -i $^

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR) $(SRC_DIR)/$(SCANNER_FILE_NAME).c