SRC_DIR  = src
BIN_DIR  = bin
OBJ_DIR  = obj
UTIL_DIR = util
EXEC_DIR = src/executions
LIB_DIR  = libfuncs_util

#Compiler, Compiler flags and C Pre Processor Flags
CC       = gcc
CFLAGS   = -Wall
MATHFLAGS = -lm
CPPFLAGS = -Ilib -Iutil -Isrc

#File names (no extension)
MAIN     	= avm
BINPARSE 	= parse_binfile
STACK	 	= avm_stack
TABLES	   	= avm_tables
EXEC_ARITH 	= execute_arith
EXEC_RELOP 	= execute_relop
EXEC_FUNCS 	= execute_funcs
EXEC_TABLES = execute_tables
LIBFUNCS  	= libfuncs

#---< Final Targets >---#

avm: $(MAIN).o $(BINPARSE).o $(STACK).o $(TABLES).o $(EXEC_ARITH).o $(EXEC_RELOP).o $(EXEC_FUNCS).o $(EXEC_TABLES).o $(LIBFUNCS).o | $(BIN_DIR) 
	 $(CC) $(CFLAGS) $(CPPFLAGS) -o $(BIN_DIR)/$@ $(OBJ_DIR)/*.o $(MATHFLAGS)

#---< Object Targets >---#
$(MAIN).o: $(SRC_DIR)/$(MAIN).c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ -o $(OBJ_DIR)/$@

$(BINPARSE).o: $(UTIL_DIR)/$(BINPARSE).c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ -o $(OBJ_DIR)/$@

$(STACK).o: $(UTIL_DIR)/$(STACK).c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ -o $(OBJ_DIR)/$@	

$(TABLES).o: $(UTIL_DIR)/$(TABLES).c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ -o $(OBJ_DIR)/$@	

$(EXEC_ARITH).o: $(EXEC_DIR)/$(EXEC_ARITH).c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ -o $(OBJ_DIR)/$@	

$(EXEC_RELOP).o: $(EXEC_DIR)/$(EXEC_RELOP).c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ -o $(OBJ_DIR)/$@	

$(EXEC_FUNCS).o: $(EXEC_DIR)/$(EXEC_FUNCS).c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ -o $(OBJ_DIR)/$@	

$(EXEC_TABLES).o: $(EXEC_DIR)/$(EXEC_TABLES).c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ -o $(OBJ_DIR)/$@

$(LIBFUNCS).o: $(LIB_DIR)/$(LIBFUNCS).c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ -o $(OBJ_DIR)/$@		

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR) 