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
LLIST	    = linked_list
SYMTABLE    = symbol_table
MANAGE 	    = manage_parser
QUAD		= quad
EXPRESSION	= expression
SCOPE_SPACE = scope_space
PANOKLIST	= panoklist
TCGENERATOR = target_code_generator

#---< Final Targets >---#
# exe target is the final product of the phase 2
scarser: $(PARSER).o $(MANAGE).o $(MAIN).o $(LLIST).o $(SYMTABLE).o $(SCANNER).o $(STACK).o $(YACC_UTIL).o $(QUAD).o $(EXPRESSION).o $(SCOPE_SPACE).o $(PANOKLIST).o $(TCGENERATOR).o | $(BIN_DIR) 
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

$(LLIST).o: $(LIB_DIR)/$(LLIST).c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ -o $(OBJ_DIR)/$@

$(SYMTABLE).o: $(LIB_DIR)/$(SYMTABLE).c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ -o $(OBJ_DIR)/$@

$(MANAGE).o: $(UTIL_DIR)/$(MANAGE).c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ -o $(OBJ_DIR)/$@

$(QUAD).o: $(UTIL_DIR)/$(QUAD).c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ -o $(OBJ_DIR)/$@	

$(EXPRESSION).o: $(UTIL_DIR)/$(EXPRESSION).c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ -o $(OBJ_DIR)/$@	
	
$(PANOKLIST).o: $(LIB_DIR)/$(PANOKLIST).c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ -o $(OBJ_DIR)/$@	

$(SCOPE_SPACE).o: $(LIB_DIR)/$(SCOPE_SPACE).c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ -o $(OBJ_DIR)/$@	

$(TCGENERATOR).o: $(UTIL_DIR)/$(TCGENERATOR).c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ -o $(OBJ_DIR)/$@

#---< produce scanner.c from scanner.l
$(SRC_DIR)/$(SCANNER).c: $(SRC_DIR)/$(SCANNER).l
	flex -o $@ -i $^

#---< produce parcer.c & parser.h(optional) from parser.y
$(SRC_DIR)/$(PARSER).c: $(SRC_DIR)/$(PARSER).y
	bison  -Wother --defines  --output=$@ $^

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR) $(SRC_DIR)/$(SCANNER).c $(SRC_DIR)/$(PARSER).c $(SRC_DIR)/$(PARSER).h out_file.txt