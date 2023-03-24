SRC_DIR  = src
OBJ_DIR  = obj
BIN_DIR  = bin
LIB_DIR  = lib
UTIL_DIR = util

#Compiler, Compiler flags and C Pre Processor Flags
CC       = gcc
CFLAGS   = -Wall
CPPFLAGS = -Ilib -Iutil -Isrc

#File names (no extension)
MAIN        = main
SCANNER     = scanner
BYHAND      = byhand
PARSER	    = parser

STACK 	    = stack
ALPHA_LIST  = alpha_token_list
YACC_UTIL   = yacc_util
ALPHA_TYPES = alpha_types

#---< Final Targets >---#
# exe target is the final product of the phase 2
scarser: $(PARSER).o $(MAIN).o $(SCANNER).o $(STACK).o $(YACC_UTIL).o | $(BIN_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $(BIN_DIR)/$@ $(OBJ_DIR)/*.o

#---< Object Targets >---#
$(MAIN).o: $(SRC_DIR)/$(MAIN).c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ -o $(OBJ_DIR)/$@

$(SCANNER).o: $(SRC_DIR)/$(SCANNER).c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ -o $(OBJ_DIR)/$@

$(ALPHA_LIST).o: $(LIB_DIR)/$(ALPHA_LIST).c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ -o $(OBJ_DIR)/$@

$(STACK).o: $(LIB_DIR)/$(STACK).c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ -o $(OBJ_DIR)/$@

$(YACC_UTIL).o: $(UTIL_DIR)/$(YACC_UTIL).c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ -o $(OBJ_DIR)/$@

$(ALPHA_TYPES).o: $(LIB_DIR)/$(ALPHA_TYPES).c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ -o $(OBJ_DIR)/$@

$(PARSER).o: $(SRC_DIR)/$(PARSER).c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ -o $(OBJ_DIR)/$@

#---< produce scanner.c from scanner.l
$(SRC_DIR)/$(SCANNER).c: $(SRC_DIR)/$(SCANNER).l
	flex -o $@ -i $^

#---< produce parcer.c & parser.h(optional) from parser.y
$(SRC_DIR)/$(PARSER).c: $(SRC_DIR)/$(PARSER).y
	bison -Wother --defines  --output=$@ $^

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR) $(SRC_DIR)/$(SCANNER).c $(SRC_DIR)/$(PARSER).c $(SRC_DIR)/$(PARSER).h