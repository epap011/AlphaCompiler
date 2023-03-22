#Directory folder names
PHASE_1_SRC_DIR = phase1_lex/src
PHASE_2_SRC_DIR = phase2_yacc/src

OBJ_DIR = obj
BIN_DIR = bin
LIB_DIR = lib

#Compiler, Compiler flags and C Pre Processor Flags
CC       = gcc
CFLAGS   = -Wall
CPPFLAGS = -Ilib

#File names (no extension)
MAIN        = main
SCANNER     = scanner
BYHAND      = byhand
PARSER	    = parser

STACK 	    = stack
ALPHA_LIST  = alpha_token_list
UTILITIES   = utilities
ALPHA_TYPES = alpha_types

#---< FLEX / BISON FINAL >---#
exe: $(MAIN).o $(PARSER).o $(SCANNER).o $(ALPHA_LIST).o $(STACK).o $(UTILITIES).o $(ALPHA_TYPES).o | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $(OBJ_DIR)/*.o

#---< PHASE 1 Targets >---#
flex:  $(MAIN).o $(SCANNER).o $(ALPHA_LIST).o $(STACK).o $(UTILITIES).o $(ALPHA_TYPES).o | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $(OBJ_DIR)/*.o

#---< Phase 1 Objects >---#
$(MAIN).o: $(PHASE_1_SRC_DIR)/$(MAIN).c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ -o $(OBJ_DIR)/$@

$(SCANNER).o: $(PHASE_1_SRC_DIR)/$(SCANNER).c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ -o $(OBJ_DIR)/$@

$(ALPHA_LIST).o: $(LIB_DIR)/$(ALPHA_LIST).c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ -o $(OBJ_DIR)/$@

$(STACK).o: $(LIB_DIR)/$(STACK).c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ -o $(OBJ_DIR)/$@

$(UTILITIES).o: $(LIB_DIR)/$(UTILITIES).c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ -o $(OBJ_DIR)/$@

$(ALPHA_TYPES).o: $(LIB_DIR)/$(ALPHA_TYPES).c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ -o $(OBJ_DIR)/$@

#---< Phase 2 Objects >---#
$(PARSER).o: $(PHASE_2_SRC_DIR)/$(PARSER).c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ -o $(OBJ_DIR)/$@

#---< produce scanner.c from scanner.l
$(PHASE_1_SRC_DIR)/$(SCANNER).c: $(PHASE_1_SRC_DIR)/$(SCANNER).l
	flex -o $@ -i $^

#---< produce parcer.c & parser.h(optional) from parser.y
$(PHASE_2_SRC_DIR)/$(PARSER).c: $(PHASE_2_SRC_DIR)/$(PARSER).y
	bison -o $@ -d $^

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR) $(PHASE_1_SRC_DIR)/$(SCANNER).c