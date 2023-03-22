#Directory folder names
PHASE_1_SRC_DIR = phase1_lex/src
PHASE_2_SRC_DIR = phase2_yacc/src

OBJ_DIR  = obj
BIN_DIR  = bin
LIB_DIR  = lib
UTIL_DIR = util

#Compiler, Compiler flags and C Pre Processor Flags
CC       = gcc
CFLAGS   = -Wall
CPPFLAGS = -Ilib -Iutil -Iphase2_yacc/src

#File names (no extension)
SYNTAX      = syntax_analyzer
LEXICAL     = lexical_analyzer
SCANNER     = scanner
BYHAND      = byhand
PARSER	    = parser

STACK 	    = stack
ALPHA_LIST  = alpha_token_list
YACC_UTIL   = yacc_util
ALPHA_TYPES = alpha_types

#---< Final Targets >---#
# exe target is the final product of the phase 2
exe: $(PARSER).o $(SYNTAX).o $(SCANNER).o $(STACK).o $(YACC_UTIL).o | $(BIN_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $(BIN_DIR)/$@ $(OBJ_DIR)/*.o

bison: $(PHASE_2_SRC_DIR)/$(PARSER).c | $(OBJ_DIR)

flex: $(PHASE_1_SRC_DIR)/$(SCANNER).c | $(OBJ_DIR)

#---< Object Targets >---#
$(LEXICAL).o: $(PHASE_1_SRC_DIR)/$(LEXICAL).c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ -o $(OBJ_DIR)/$@

$(SYNTAX).o: $(PHASE_2_SRC_DIR)/$(SYNTAX).c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ -o $(OBJ_DIR)/$@

$(SCANNER).o: $(PHASE_1_SRC_DIR)/$(SCANNER).c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ -o $(OBJ_DIR)/$@

$(ALPHA_LIST).o: $(LIB_DIR)/$(ALPHA_LIST).c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ -o $(OBJ_DIR)/$@

$(STACK).o: $(LIB_DIR)/$(STACK).c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ -o $(OBJ_DIR)/$@

$(YACC_UTIL).o: $(UTIL_DIR)/$(YACC_UTIL).c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ -o $(OBJ_DIR)/$@

$(ALPHA_TYPES).o: $(LIB_DIR)/$(ALPHA_TYPES).c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ -o $(OBJ_DIR)/$@

$(PARSER).o: $(PHASE_2_SRC_DIR)/$(PARSER).c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ -o $(OBJ_DIR)/$@

#---< produce scanner.c from scanner.l
$(PHASE_1_SRC_DIR)/$(SCANNER).c: $(PHASE_1_SRC_DIR)/$(SCANNER).l
	flex -o $@ -i $^

#---< produce parcer.c & parser.h(optional) from parser.y
$(PHASE_2_SRC_DIR)/$(PARSER).c: $(PHASE_2_SRC_DIR)/$(PARSER).y
	bison --defines  --output=$@ $^

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR) $(PHASE_1_SRC_DIR)/$(SCANNER).c $(PHASE_2_SRC_DIR)/$(PARSER).c $(PHASE_2_SRC_DIR)/$(PARSER).h