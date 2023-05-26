typedef char* (*tostring_func_t)(avm_memcell*);

void avm_dec_top(void);
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

void avm_calllibfunc(char* id);
void avm_push_table_arg(avm_table* t);
void avm_call_functor(avm_table* t);