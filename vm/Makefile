BIN_DIR  = bin
OBJ_DIR  = obj
UTIL_DIR = util

#Compiler, Compiler flags and C Pre Processor Flags
CC       = gcc
CFLAGS   = -Wall
CPPFLAGS = -Ilib -Iutil -Isrc

#File names (no extension)
MAIN     = avm
BINPARSE = parse_binfile
STACK	 = avm_stack
TABLES	 = avm_tables

#---< Final Targets >---#

avm: $(MAIN).o $(BINPARSE).o $(STACK).o $(TABLES).o| $(BIN_DIR) 
	 $(CC) $(CFLAGS) $(CPPFLAGS) -o $(BIN_DIR)/$@ $(OBJ_DIR)/*.o

#---< Object Targets >---#
$(MAIN).o: $(MAIN).c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ -o $(OBJ_DIR)/$@

$(BINPARSE).o: $(UTIL_DIR)/$(BINPARSE).c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ -o $(OBJ_DIR)/$@

$(STACK).o: $(UTIL_DIR)/$(STACK).c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ -o $(OBJ_DIR)/$@	

$(TABLES).o: $(UTIL_DIR)/$(TABLES).c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ -o $(OBJ_DIR)/$@	

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR)