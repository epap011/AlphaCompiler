SRC_DIR  = src
BIN_DIR  = bin
OBJ_DIR  = obj
UTIL_DIR = util
EXEC_DIR = src/executors
LIB_DIR  = src/libfuncs

#Compiler, Compiler flags and C Pre Processor Flags
CC       = gcc
CFLAGS   = -Wall -g
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
HELPERS		= avm_helpers

LIBFUNCS_SRC := $(wildcard src/libfuncs/*.c)
LIBFUNCS_OBJ := $(patsubst src/libfuncs/%.c, obj/%.o, $(LIBFUNCS_SRC))

EXECUTORS_SRC := $(wildcard src/executors/*.c)
EXECUTORS_OBJ := $(patsubst src/executors/%.c, obj/%.o, $(EXECUTORS_SRC))

#---< Final Targets >---#

alpha: $(MAIN).o $(BINPARSE).o $(STACK).o $(TABLES).o $(EXECUTORS_OBJ) $(LIBFUNCS).o $(HELPERS).o $(LIBFUNCS_OBJ) | $(BIN_DIR) 
	 $(CC) $(CFLAGS) $(CPPFLAGS) -o $(BIN_DIR)/$@ $(OBJ_DIR)/*.o $(MATHFLAGS)

#---< Object Targets >---#
$(MAIN).o: $(SRC_DIR)/$(MAIN).c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ -o $(OBJ_DIR)/$@

$(BINPARSE).o: $(UTIL_DIR)/$(BINPARSE).c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ -o $(OBJ_DIR)/$@

$(STACK).o: $(SRC_DIR)/stack/$(STACK).c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ -o $(OBJ_DIR)/$@	

$(TABLES).o: $(SRC_DIR)/tables/$(TABLES).c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ -o $(OBJ_DIR)/$@	

$(EXECUTORS_OBJ): $(OBJ_DIR)/%.o: $(EXEC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(LIBFUNCS).o: $(LIB_DIR)/$(LIBFUNCS).c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ -o $(OBJ_DIR)/$@

$(HELPERS).o: $(UTIL_DIR)/$(HELPERS).c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ -o $(OBJ_DIR)/$@

$(LIBFUNCS_OBJ): $(OBJ_DIR)/%.o: $(LIB_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR) 