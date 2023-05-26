typedef char* (*tostring_func_t)(avm_memcell*);

void avm_dec_top(void);
unsigned avm_get_envvalue(unsigned i);
void avm_push_envvalue(unsigned val);
void amv_callsaveenvironment(void);

char* avm_tostring(avm_memcell* m);

char* number_tostring(avm_memcell* m);
char* string_tostring(avm_memcell* m);
char* bool_tostring(avm_memcell* m);
char* table_tostring(avm_memcell* m);
char* userfunc_tostring(avm_memcell* m);
char* libfunc_tostring(avm_memcell* m);
char* nil_tostring(avm_memcell* m);
char* undef_tostring(avm_memcell* m);

unsigned avm_totalactuals(void);
avm_memcell* avm_getactual(unsigned i);
void libfunc_print(void);

//void avm_registerlibfunc(char* id, library_func_t addr);
void avm_calllibfunc(char* id);
void avm_push_table_arg(avm_table* t);
void avm_call_functor(avm_table* t);