#include <string.h>
#include "symbol_table.h"
#include "yacc_util.h"
#include "manage_parser.h"
#include "quad.h"

#define RED   "\x1b[31m"
#define GRN   "\x1b[32m"
#define YEL   "\x1b[33m"
#define BLU   "\x1b[34m"
#define MAG   "\x1b[35m"
#define CYN   "\x1b[36m"
#define RESET "\x1b[0m"

#define FUNC 0
#define VAR  1

#define NUM_OF_LIB_FUNC 12

int formal_flag = 0;    //Usage: if a function is already declared (or is a built-in ), we don't want to insert it in the symbol table and wee need this flag to skip the formal arguments as well
extern FILE * out_file;
int error_flag = 0;    //If we have ANY error, we dont produce quad/binary files

extern unsigned formal_counter;
extern Stack *formal_stack;

char lib_functions[NUM_OF_LIB_FUNC][19] = {
    "print",
    "input",
    "objectmemberkeys",
    "objecttotalmembers",
    "objectcopy",
    "totalarguments",
    "argument",
    "typeof",
    "strtonum",
    "sqrt",
    "cos",
    "sin"
};

void insert_lib_functions(SymbolTable * symTable){

    for(int i = 0; i < NUM_OF_LIB_FUNC; i++) {   
        char* name     = strdup(lib_functions[i]);    
        Symbol* symbol = symbol_create(name, 0, 0, LIBFUNC, 0,libraryfunc_s,-1,-1);
        symbol_table_insert(symTable, symbol);
    }
}

//Move to another file?
const char* str_type(enum SymbolType type){
    switch (type){
        case USERFUNC:  return "user function";
        case LIBFUNC:   return "library function";
        case GLOBAL:    return "global variable";
        case FORMAL:    return "formal variable";
        case _LOCAL:    return "local variable";    
        
        default:       return "INVALID";
    }
}

void symbol_table_print(SymbolTable* symTable){

    for(int i = 0; i < symTable->scope_size; i++){
        Symbol* current_symbol = symTable->first_symbol_scopes[i];
        if(current_symbol == NULL) continue;

        fprintf(out_file,"\n-------- Scope #%d --------\n\n", i);

        while(current_symbol != NULL){
            if(current_symbol->type == var_s)
                fprintf(out_file," "YEL"%-18s"RESET" "BLU"["RESET"%-16s"BLU"]"RESET" (line: "GRN"%-2d"RESET") (scope "GRN"%-2d"RESET") (space   : "GRN"%-2d"RESET") (offset "GRN"%-2d"RESET") \n", current_symbol->name, str_type(current_symbol->symbol_type), current_symbol->line, current_symbol->scope, current_symbol->space, current_symbol->offset);
            else
                fprintf(out_file," "YEL"%-18s"RESET" "BLU"["RESET"%-16s"BLU"]"RESET" (line: "GRN"%-2d"RESET") (scope "GRN"%-2d"RESET") (iaddress: "GRN"%-2d"RESET") (totalLocals "GRN"%-2d"RESET") \n", current_symbol->name, str_type(current_symbol->symbol_type), current_symbol->line, current_symbol->scope, current_symbol->iaddress, current_symbol->totalLocals);
            current_symbol = current_symbol->next_symbol_of_same_scope;
        }
    }
    fprintf(out_file,"\n\n");
}

void increase_scope(unsigned int* scope){
    (*scope)++;
}

void decrease_scope(unsigned int* scope){
    (*scope)--;
}

//Checks if a function with that name is already declared (also checks if it is a library function)
void check_if_declared(SymbolTable* symTable, const char* id, unsigned int scope){
    if(id[0] == '_') return; //If it is an unonymous function, don't check
    
    Symbol* tmp_symbol = symbol_table_scope_lookup(symTable, id, scope);

    if(tmp_symbol != NULL){
        formal_flag = 1;
        return;
    }
    
    if(is_id_built_in_function(id))
        formal_flag = 1;
        
}

int is_id_built_in_function(const char* id){
    for(int i = 0; i < NUM_OF_LIB_FUNC; i++){
        if(strcmp(id, lib_functions[i]) == 0){
            return 1;
        }
    }
    return 0;
}

Symbol* manage_funcdef(SymbolTable* symTable, char* id, unsigned int scope, unsigned int line){

   if(is_id_built_in_function(id)) {
        fprintf(out_file,RED"Error:"RESET" Cannot shadow library function \""YEL"%s"RESET"\" (line: "GRN"%d"RESET") \n", id, line);
        error_flag = 1;
        return NULL;
   }
   
   Symbol* tmp_symbol = symbol_table_scope_lookup(symTable, id, scope);

    if(tmp_symbol != NULL){
        if(tmp_symbol->symbol_type == LIBFUNC)
            fprintf(out_file,RED"Error:"RESET" Cannot shadow library function \""YEL"%s"RESET"\" (line: "GRN"%d"RESET") \n", id, line);
        else
            fprintf(out_file,RED"Error:"RESET" Function \""YEL"%s"RESET"\" already declared in scope "GRN"%d"RESET" (line: "GRN"%d"RESET") \n", id, scope,line);

        error_flag = 1;
        return NULL;
    }

    char* name     = strdup(id);
    Symbol* symbol = symbol_create(name, scope, line, USERFUNC, FUNC, programfunc_s, -1, -1);
    
    //phase 3 quad number
    symbol->iaddress    = nextQuadLabel() +1; //+1 because a jump quad is created before funcstart quad

    symbol_table_insert(symTable, symbol);
    return symbol;
}

void manage_formal_id(SymbolTable* symTable, const char* id, unsigned int scope, unsigned int line){

    if(formal_flag)
        return;
         
    if(is_id_built_in_function(id)) {
            fprintf(out_file,RED"Error:"RESET" Cannot declare variable \""YEL"%s"RESET"\", a library function exist with that name (line: "GRN"%d"RESET") \n", id, line);
            error_flag = 1;
            return;
        }

    if(symbol_table_scope_lookup(symTable, id, scope) != NULL){
        fprintf(out_file,RED"Error:"RESET" Formal variable \""YEL"%s"RESET"\" already declared in function (line: "GRN"%d"RESET")\n", id, line);
        error_flag = 1;
        return;
    } 

    char* name     = strdup(id);
    Symbol* symbol = symbol_create(name, scope, line, FORMAL, VAR, var_s, currScopeSpace(), currScopeOffset());
    incCurrScopeOffset();
    
    symbol_table_insert(symTable, symbol);

    if(!formal_stack)
        formal_stack = new_stack();

    formal_counter++;
    push(formal_stack, symbol);

}

void flip_formal_offsets(){

    if(!formal_stack){
        formal_stack = new_stack();
        return;
    }

    unsigned t_formal_counter = formal_counter;
    for(int i=0; i<formal_counter; i++){
        Symbol* tmp_symbol = (Symbol*)pop(formal_stack);
        tmp_symbol->offset = tmp_symbol->offset - (--t_formal_counter) +i;
    }

    formal_counter = 0;

}

expr* manage_func_call(expr* lvalue, expr* elist, unsigned int scope, unsigned int line) {

    expr* func = emit_if_tableitem(lvalue,scope,line);
    Stack* elist_s = new_stack();
    expr* temp=elist;
    while(temp){
        push(elist_s,temp);
        temp = temp->next;
    }
    while( (temp = (expr*)pop(elist_s)) )
        emit(param,NULL,NULL,temp,-1,line);
    emit(call,NULL,NULL,func,-1,line);
    expr* result = new_expr(var_e);
    result->sym = symbol_create(str_int_merge("_t",anonym_var_cnt++), scope, line, scope == 0 ? GLOBAL : _LOCAL, VAR, var_s, currScopeSpace(), currScopeOffset());
    incCurrScopeOffset();
    emit(getretval,NULL,NULL,result,-1,line);
    
    return result;
}

int hide_symbol_on_scope(SymbolTable* symTable, const char* id, unsigned int scope) {
    Symbol* tmp_symbol = symbol_table_scope_lookup(symTable, id, scope);
    if(tmp_symbol != NULL) {
        tmp_symbol->is_active = 0;
        //must decrement anonym_var_counter when hiding a hidden var symbol
        return 1;
    }

    return 0;
}

void manage_return(int line, int flag, expr* retval, Stack *retstack){
    if(!flag){
        fprintf(out_file,RED"Error:"RESET" \""YEL"return"RESET"\" should be part of a function (line: "GRN"%d"RESET")\n", line);
        error_flag = 1;
    }
    else{
        emit(ret, retval ? retval : NULL, NULL, NULL, -1, line);
        //Because of multiple returns in multiple funcdefs, a stack of stacks is required (funcdefs x returns).
        unsigned int *curr = malloc(sizeof(unsigned int));
        void *ret_s = pop(retstack);
        push(ret_s,curr);
        push(retstack,ret_s);
        *curr=nextQuadLabel();
        emit(jump, NULL, NULL, NULL, -1, line);
    }
}

void manage_program (int debug, FILE* out) {
    if(debug) fprintf(out, MAG "Detected :" RESET"program stmtList \n");
}

//Gia ta 3 teleutaia emits sta boolops kai to patching twn listwn
void short_circuit_emits(expr* result, unsigned int line, unsigned int scope){
    
    if(result == NULL)
        return;

    int patch_success=0;
    
    patch_success += patch_panoklist(result->truelist, nextQuadLabel());
    patch_success += patch_panoklist(result->falselist, nextQuadLabel()+2);

    if(patch_success){
        Symbol* tmp_symbol = symbol_table_insert(symTable, symbol_create(str_int_merge("_t",anonym_var_cnt++), scope, line, scope == 0 ? GLOBAL : _LOCAL, VAR, var_s, currScopeSpace(), currScopeOffset()));
        incCurrScopeOffset();
        result->sym = tmp_symbol;

        emit(assign, new_const_bool(1), NULL, result, -1, line);
        emit(jump, NULL, NULL, NULL, nextQuadLabel()+2, line);
        emit(assign, new_const_bool(0), NULL, result, -1, line);
    }
}

stmt_t* manage_stmt_expr(int debug, FILE* out) {
    if(debug) fprintf(out, MAG "Detected :" RESET"expr;"CYN" ->"RESET" stmt \n");

    return make_stmt();
}

stmt_t* manage_stmt_ifstmt(int debug, FILE* out, stmt_t* ifstmt) {
    if(debug) fprintf(out, MAG "Detected :" RESET"ifstmt"CYN" ->"RESET" stmt \n");
    return ifstmt;
}

stmt_t* manage_stmt_whilestmt(int debug, FILE* out) {
    if(debug) fprintf(out, MAG "Detected :" RESET"whilestmt"CYN" ->"RESET" stmt \n");
    return make_stmt();
}

stmt_t* manage_stmt_forstmt(int debug, FILE* out) {
    if(debug) fprintf(out, MAG "Detected :" RESET"forstmt"CYN" ->"RESET" stmt \n");
    return make_stmt();
}

stmt_t* manage_stmt_returnstmt(int debug, FILE* out) {
    if(debug) fprintf(out, MAG "Detected :" RESET"returnstmt"CYN" ->"RESET" stmt \n");
    return make_stmt();
}

stmt_t* manage_stmt_block     (int debug, FILE* out) {
    if(debug) fprintf(out, MAG "Detected :" RESET"block"CYN" ->"RESET" stmt \n");
    return NULL;
}

stmt_t* manage_stmt_break(int debug, FILE* out, int line, int flag){
    if(debug) fprintf(yyout, MAG "Detected :" RESET"BREAK ;"CYN""RESET"-> stmt \n");
    if(!flag){
        fprintf(out_file,RED"Error:"RESET" \""YEL"break; "RESET"\" should be part of a for/while loop (line: "GRN"%d"RESET")\n", line);
        error_flag = 1;
    }
    return NULL;
}

stmt_t* manage_stmt_continue(int debug, FILE* out, int line, int flag){
    if(debug) fprintf(yyout, MAG "Detected :" RESET"CONTINUE"CYN""RESET"-> while;\n");
    if(!flag){
        fprintf(out_file,RED"Error:"RESET" \""YEL"continue"RESET"\" should be part of a for/while loop (line: "GRN"%d"RESET")\n", line);
        error_flag = 1;
    }
    return NULL;
}

stmt_t* manage_stmt_funcdef   (int debug, FILE* out) {
    if(debug) fprintf(out, MAG "Detected :" RESET"funcdef"CYN" ->"RESET" stmt \n");
    return make_stmt();
}

stmt_t* manage_stmt_semicolon (int debug, FILE* out) {
    if(debug) fprintf(out, MAG "Detected :" RESET";"CYN""RESET" -> stmt \n");
    return make_stmt();
}

void manage_expr_assignexpr(int debug, FILE* out) {
    if(debug) fprintf(yyout, MAG "Detected :" RESET"assignexpr"CYN" ->"RESET" expr \n");
}

void manage_expr_term(int debug, FILE* out) {
    if(debug) fprintf(yyout, MAG "Detected :" RESET"term"CYN" ->"RESET" expr \n");
}

/**Arithmetic / relop expressions here**/

expr* manage_arith_relop_emits(expr* expr1, expr* expr2, unsigned int scope, unsigned int line, enum iopcode op){
    expr* result;
    if ( (expr1->type == var_e || expr1->type == constnum_e || expr1->type == constbool_e) &&
         (expr2->type == var_e || expr2->type == constnum_e || expr1->type == constbool_e) ){ //check if arithmetic operands are variables or constants
        result = new_lvalue_expr(symbol_table_insert(symTable, symbol_create(str_int_merge("_t",anonym_var_cnt++), scope, line, scope == 0 ? GLOBAL : _LOCAL, VAR, var_s, currScopeSpace(), currScopeOffset())));
        incCurrScopeOffset();
        emit(op, expr1, expr2, result, -1, line);
        return result;
    }
    return NULL;
}

expr* manage_arithop_emits(expr* expr1, expr* expr2, unsigned int scope, unsigned int line, enum iopcode op) {
    expr* result = NULL;

    if (check_arith(expr1, out_file,line,"arithmetic") == 0 && check_arith(expr2, out_file,line,"arithmetic") == 0) {
        
        Symbol* tmp_symbol = symbol_table_insert(symTable, symbol_create(str_int_merge("_t",anonym_var_cnt++), scope, line, scope == 0 ? GLOBAL : _LOCAL, VAR, var_s, currScopeSpace(), currScopeOffset()));
        incCurrScopeOffset();

        if(expr1->type == constnum_e && expr2->type == constnum_e) {
            result = new_expr(constnum_e);

            if(op == add) result->numConst = expr1->numConst + expr2->numConst;
            else if(op == sub) result->numConst = expr1->numConst - expr2->numConst;
            else if(op == mul) result->numConst = expr1->numConst * expr2->numConst;
            else if(op == i_div) result->numConst = expr1->numConst / expr2->numConst;
            else result->numConst = (int)expr1->numConst % (int)expr2->numConst;
        }
        else {
            result = new_expr(arithexpr_e);
        }
        result->sym = tmp_symbol;
        
        emit(op, expr1, expr2, result, -1, line);
    }

    return result;
}

expr* manage_relop_emits(expr* expr1, expr* expr2, unsigned int scope, unsigned int line, enum iopcode op) {
    expr* result = NULL;
    
    expr1->boolConst  = convert_to_bool(expr1);
    expr2->boolConst  = convert_to_bool(expr2);

    //An DEN exoume kati apo ta (==,!=) kai parallila toulaxiston ena apo ta 2 expr einai boolean, tote einai error.
    //p.x den mporeis na peis 3 > true. Alla 3 == true mporeis na to peis.
    if (op != if_eq && op != if_noteq) {
       
        int check = 0; //xrisimopoioume metavliti apla gia na petaei kai gia ta 2 expr ta error an uparxei auto to case
        check += check_arith(expr1, out_file,line,"relational");
        check += check_arith(expr2, out_file,line,"relational");
        if(check){printf("Tha fas seg an tuposeis ta quads!!!!\n"); return NULL;}
    }

    result = new_expr(boolexpr_e);

    //Ta apotelesmata boolean ekfrasewn den pairnoun (pleon) hidden_var san tis arithmitikes,
    //dioti h ekvash tous katalhgei se truelist/falselist, kai sto telos ginetai short_circuit_emits.
    
    result->firstQuad = nextQuadLabel();
    result->truelist=new_panoklist(nextQuadLabel());
    result->falselist=new_panoklist(nextQuadLabel()+1);
    emit(op, expr1, expr2, NULL, nextQuadLabel()+2, line);
    emit(jump, NULL, NULL, NULL, nextQuadLabel()+3, line);

    return result;
}

expr* manage_term_not_expr(int debug, FILE* out, expr* expr1, unsigned int scope, unsigned int line) {
    if(debug) fprintf(out, MAG "Detected :" RESET"NOT expr"CYN" ->"RESET" term \n");

    if(expr1 == NULL) return NULL;

    //Creation of new expression with hidden var, is unnecessary.
    linked_list* tmp;
    expr1->boolConst = convert_to_bool(expr1);

    expr* temp;
    
    if(!(expr1->truelist)){
        temp=new_expr(boolexpr_e);
        //Quads are emitted ONLY if expression doesn't have truelist/falselist.
        //Lists are also created, and linked in an opposite way (true->false, false->true).
        temp->falselist = new_panoklist(nextQuadLabel()); //falselist linked to true
        temp->truelist = new_panoklist(nextQuadLabel()+1); //truelist linked to false
        emit(if_eq, expr1, new_const_bool(1), NULL, -1, line);
        emit(jump,NULL,NULL,NULL, -1 ,line);
        return temp;
    }
    else{
        //If expression has truelist/falselist, then we just need to swap them.
        tmp = expr1->truelist;
        expr1->truelist = expr1->falselist;
        expr1->falselist = tmp;
        return expr1;
    }
}

expr* manage_boolop_bypass(expr* expr1, expr* expr2, unsigned int scope, unsigned int line, enum iopcode op) {
    expr* result = new_expr(boolexpr_e);
    if(!(expr1->truelist)){
        //emits for expr1
            //Create truelist and falselist for e1 if not exists
            //Also shift quads of expr2, so that they are placed after expr1's quads.
            if(op == and){
                expr1->firstQuad = expr2->firstQuad;    //expr1 takes expr2's place in the quad array
                shiftQuads(expr2->firstQuad, 2);        //shift expr2's quads by 2, to make space for expr1's quads
                expr2->firstQuad += 2;
                emit_target(if_eq, expr1, new_const_bool(1), NULL, expr1->firstQuad, -1, line); 
                emit_target(jump, NULL, NULL, NULL, (expr1->firstQuad+1), -1, line);
            } else 
            if(op == or){
                expr1->firstQuad = expr2->firstQuad;
                shiftQuads(expr2->firstQuad, 2);
                expr2->firstQuad += 2;
                emit_target(if_eq, expr1, new_const_bool(1), NULL, expr1->firstQuad, -1, line);
                emit_target(jump, NULL, NULL, NULL, (expr1->firstQuad+1), -1, line);
            } 
            expr1->truelist  = new_panoklist(expr1->firstQuad);
            expr1->falselist = new_panoklist(expr1->firstQuad+1);
            shift_panoklist(expr2->truelist, 2, expr1->firstQuad);  //shift truelist/falselist, if labels are less than expr2's previous firstQuad
            shift_panoklist(expr2->falselist, 2, expr1->firstQuad);
        }
        //else if expr1 exists (has truelist/falselist) (?)

            //Merge lists for result (e) 
    if(op == and){
        patch_panoklist(expr1->truelist, expr2->firstQuad);
        result->truelist = expr2->truelist;
        result->falselist = merge_panoklist(expr1->falselist, expr2->falselist);
    }else
    if(op == or){
        patch_panoklist(expr1->falselist, expr2->firstQuad);
        result->truelist = merge_panoklist(expr1->truelist, expr2->truelist);
        result->falselist = expr2->falselist;
    }
    
    return result;
}

expr* manage_boolop_emits(expr* expr1, expr* expr2, unsigned int scope, unsigned int line, enum iopcode op, unsigned int M_label) {
    if(expr1 == NULL || expr2 == NULL) return NULL;
    
    unsigned int M_label_final = M_label;
    expr* result = NULL;

    expr1->boolConst = convert_to_bool(expr1);
    expr2->boolConst = convert_to_bool(expr2);

    //Must maintain the order of the quads, because of short-circuit evaluation.
    //Sometimes the grammar evaluates the second expression first, and then the first.
    //If expr1 has quads chronologically after expr2, then we must swap them, and patch them the other way.
    //Also, we should shift the 2nd expression's quads, so that they are after the 1st expression's quads.

    //first, the condition to figure out if this is happening
    if(!expr1->truelist && expr2->truelist){
          return manage_boolop_bypass(expr1, expr2, scope, line, op);
    }
    else if (expr1->truelist && expr2->truelist && *(int*)(expr1->truelist->head->data) > *(int*)(expr2->truelist->head->data)){
        //swap expr
        expr* temp = expr1;
        expr1 = expr2;
        expr2 = temp;
    }
    
    result = new_expr(boolexpr_e);

    if(!(expr1->truelist)){
    //emits for expr1
        //Create truelist and falselist for e1 if not exists
        if(op == and){
            result->firstQuad = nextQuadLabel();
            emit(if_eq, expr1, new_const_bool(1), NULL, -1, line); 
            emit(jump, NULL, NULL, NULL, -1, line);
        } else 
        if(op == or){
            result->firstQuad = nextQuadLabel();
            emit(if_eq, expr1, new_const_bool(1), NULL, -1, line);
            emit(jump, NULL, NULL, NULL, -1, line);
        } 
        expr1->truelist  = new_panoklist(nextQuadLabel()-2);
        expr1->falselist = new_panoklist(nextQuadLabel()-1);
    }
   
   //Create truelist and falselist for e2 if nonexistent.
   //Emits for expr2 are ONLY created if truelist/falselist do not exist.
    if(!(expr2->truelist)){
        expr2->truelist  = new_panoklist(nextQuadLabel());
        expr2->falselist = new_panoklist(nextQuadLabel()+1);
        //M_label == the next emit's label, whenever we create quads.
        M_label_final = nextQuadLabel();
        emit(if_eq, expr2, new_const_bool(1), NULL, -1, line); //se auto to emit prepei na lifthei ipopsi to const bool kai tws 2 expr
        emit(jump, NULL, NULL, NULL, -1, line);
    }

    //Merge lists for result (e) 
    if(op == and){
        patch_panoklist(expr1->truelist, M_label_final);
        result->truelist = expr2->truelist;
        result->falselist = merge_panoklist(expr1->falselist, expr2->falselist);
    }else
    if(op == or){
        patch_panoklist(expr1->falselist, M_label_final);
        result->truelist = merge_panoklist(expr1->truelist, expr2->truelist);
        result->falselist = expr2->falselist;
    }
    
    return result;
}

expr* manage_expr_plus_expr(int debug, FILE* out, expr* expr1, expr* expr2, unsigned int scope, unsigned int line) {
    if(debug) fprintf(out, MAG "Detected :" RESET"expr + expr"CYN" ->"RESET" expr \n");

    return manage_arithop_emits(expr1, expr2, scope, line, add);
}

expr* manage_expr_mul_expr(int debug, FILE* out, expr* expr1, expr* expr2, unsigned int scope, unsigned int line) {
    if(debug) fprintf(out, MAG "Detected :" RESET"expr * expr"CYN" ->"RESET" expr \n");
    
    return manage_arithop_emits(expr1, expr2, scope, line, mul);
}

expr* manage_expr_minus_expr(int debug, FILE* out, expr* expr1, expr* expr2, unsigned int scope, unsigned int line) {
    if(debug) fprintf(out, MAG "Detected :" RESET"expr - expr"CYN" ->"RESET" expr \n");

    return manage_arithop_emits(expr1, expr2, scope, line, sub);
}

expr* manage_expr_div_expr(int debug, FILE* out, expr* expr1, expr* expr2, unsigned int scope, unsigned int line) {
    if(debug) fprintf(out, MAG "Detected :" RESET"expr / expr"CYN" ->"RESET" expr \n");

    return manage_arithop_emits(expr1, expr2, scope, line, i_div);
}

expr* manage_expr_mod_expr(int debug, FILE* out, expr* expr1, expr* expr2, unsigned int scope, unsigned int line) {
    if(debug) fprintf(out, MAG "Detected :" RESET"expr MOD expr"CYN" ->"RESET" expr \n");
 
    return manage_arithop_emits(expr1, expr2, scope, line, mod);
}

expr* manage_expr_eq_expr(int debug, FILE* out, expr* expr1, expr* expr2, unsigned int scope, unsigned int line) {
    if(debug) fprintf(out, MAG "Detected :" RESET"expr == expr"CYN" ->"RESET" expr \n");

    return manage_relop_emits(expr1, expr2, scope, line, if_eq);
}

expr* manage_expr_neq_expr(int debug, FILE* out, expr* expr1, expr* expr2, unsigned int scope, unsigned int line) {
    if(debug) fprintf(out, MAG "Detected :" RESET"expr != expr"CYN" ->"RESET" expr \n");
    
    return manage_relop_emits(expr1, expr2, scope, line, if_noteq);
}

expr* manage_expr_gt_expr(int debug, FILE* out, expr* expr1, expr* expr2, unsigned int scope, unsigned int line) {
    if(debug) fprintf(out, MAG "Detected :" RESET"expr > expr"CYN" ->"RESET" expr \n");
   
    return manage_relop_emits(expr1, expr2, scope, line, if_greater);
}

expr* manage_expr_lt_expr(int debug, FILE* out, expr* expr1, expr* expr2, unsigned int scope, unsigned int line) {
    if(debug) fprintf(out, MAG "Detected :" RESET"expr < expr"CYN" ->"RESET" expr \n");
   
    return manage_relop_emits(expr1, expr2, scope, line, if_less);
}

expr* manage_expr_gte_expr(int debug, FILE* out, expr* expr1, expr* expr2, unsigned int scope, unsigned int line) {
    if(debug) fprintf(out, MAG "Detected :" RESET"expr >= expr"CYN" ->"RESET" expr \n");
  
    return manage_relop_emits(expr1, expr2, scope, line, if_greatereq);
}

expr* manage_expr_lte_expr(int debug, FILE* out, expr* expr1, expr* expr2, unsigned int scope, unsigned int line) {
    if(debug) fprintf(out, MAG "Detected :" RESET"expr <= expr"CYN" ->"RESET" expr \n");
    
    return manage_relop_emits(expr1, expr2, scope, line, if_lesseq);
}

expr* manage_expr_and_expr(int debug, FILE* out, expr* expr1, expr* expr2, unsigned int M_label, unsigned int scope, unsigned int line) {
    if(debug) fprintf(out, MAG "Detected :" RESET"expr AND expr"CYN" ->"RESET" expr \n");
 
    return manage_boolop_emits(expr1, expr2, scope, line, and, M_label);
}

expr* manage_expr_or_expr(int debug, FILE* out, expr* expr1, expr* expr2, unsigned int M_label, unsigned int scope, unsigned int line) {
    if(debug) fprintf(out, MAG "Detected :" RESET"expr OR expr"CYN" ->"RESET" expr \n");
    
    return manage_boolop_emits(expr1, expr2, scope, line, or, M_label); 
}
/**End of Arithmetic / relop**/

void manage_term_lpar_expr_rpar(int debug, FILE* out) {
    if(debug) fprintf(out, MAG "Detected :" RESET"( expr )"CYN" ->"RESET" term \n");
}

expr* manage_term_uminus_expr(int debug, FILE* out, expr* u_expr, unsigned int scope, unsigned int line) {
    if(debug) fprintf(out, MAG "Detected :" RESET"UMINUS expr"CYN" ->"RESET" term \n");
    
    if(check_arith(u_expr,out_file, line,"arithmetic")) return NULL;  //An fas kana seg check edw an kai den nomizw :)

    expr *result = new_expr(arithexpr_e);
    result->sym = symbol_table_insert(symTable, symbol_create(str_int_merge("_t",anonym_var_cnt++), scope, line, scope == 0 ? GLOBAL : _LOCAL, VAR, var_s, currScopeSpace(), currScopeOffset()));
    incCurrScopeOffset();
    result->numConst = u_expr->numConst;
    emit(uminus, u_expr, NULL, result, -1, line);

    return result;

}



/*Start of ++ --*/

//This is unused since we have check arith_() now
int check_lvalue(SymbolTable* symTable, const char* id, unsigned int scope, unsigned int line){
    
    for (int i = 0; i <= scope; i++){   //we need to check all scopes 
        Symbol *tmp_symbol = symbol_table_scope_lookup(symTable, id, i);
        if(tmp_symbol != NULL && (tmp_symbol->symbol_type == USERFUNC || tmp_symbol->symbol_type == LIBFUNC)){
            fprintf(out_file,RED "Error:" RESET " Cannot apply arithmetic operation on function \"" YEL "%s" RESET "\" (line: " GRN "%d" RESET ")\n", id, line);
            error_flag = 1;
            return 1;
        }
        else        
            return 0;
    }
    return 0;
}

expr* manage_term_plusplus_lvalue(int debug, FILE* out, SymbolTable* symTable, expr* lvalue, unsigned int scope, unsigned int line) {
    if(debug) fprintf(out, MAG "Detected :" RESET"++lvalue"CYN" ->"RESET" term \n");
    
    if(lvalue != NULL) {
        if(check_arith(lvalue,out_file, line,"arithmetic")) 
            return NULL;
    }

    expr * term;
    if(lvalue->type == tableitem_e){
       term = emit_if_tableitem(lvalue, scope, line);
       emit(add, term, new_const_num(1), term, -1, line);
       emit(tablesetelem, lvalue->index, term, lvalue, -1, line);
    }
    else{
        emit(add, lvalue, new_const_num(1), lvalue, -1, line);
        term = new_expr(arithexpr_e);
        term->sym = symbol_table_insert(symTable, symbol_create(str_int_merge("_t",anonym_var_cnt++), scope, line, scope == 0 ? GLOBAL : _LOCAL, VAR, var_s, currScopeSpace(), currScopeOffset()));
        incCurrScopeOffset();
        emit(assign, lvalue, NULL, term, -1, line);
    }

    return term;
}

expr* manage_term_lvalue_plusplus(int debug, FILE* out, SymbolTable* symTable, expr* lvalue, unsigned int scope, unsigned int line) {
    if(debug) fprintf(out, MAG "Detected :" RESET"lvalue++"CYN" ->"RESET" term \n");
    
    if(lvalue != NULL) {
        if(check_arith(lvalue,out_file, line,"arithmetic")) 
            return NULL;
    }

    expr* term = new_expr(var_e);
    term->sym = symbol_table_insert(symTable, symbol_create(str_int_merge("_t",anonym_var_cnt++), scope, line, scope == 0 ? GLOBAL : _LOCAL, VAR, var_s, currScopeSpace(), currScopeOffset()));
    incCurrScopeOffset();

    if(lvalue->type == tableitem_e){
        expr * val = emit_if_tableitem(lvalue, scope, line);
        emit(assign, val, NULL, term, -1, line);
        emit(add, val, new_const_num(1), val, -1, line);
        emit(tablesetelem, lvalue->index, val, lvalue, -1, line);
    }
    else{
        emit(assign, lvalue, NULL, term, -1, line);
        emit(add, lvalue, new_const_num(1), lvalue, -1, line);  
    }
    return term;
    
}

expr* manage_term_minusminus_lvalue(int debug, FILE* out, SymbolTable* symTable, expr* lvalue, unsigned int scope, unsigned int line) {
    if(debug) fprintf(out, MAG "Detected :" RESET"--lvalue"CYN" ->"RESET" term \n");
    
    if(lvalue != NULL) {
        if(check_arith(lvalue,out_file, line,"arithmetic")) 
            return NULL;
    }

    expr * term;
    if(lvalue->type == tableitem_e){
       term = emit_if_tableitem(lvalue, scope, line);
       emit(sub, term, new_const_num(1), term, -1, line);
       emit(tablesetelem, lvalue->index, term, lvalue, -1, line);
    }
    else{
        emit(sub, lvalue, new_const_num(1), lvalue, -1, line);
        term = new_expr(arithexpr_e);
        term->sym = symbol_table_insert(symTable, symbol_create(str_int_merge("_t",anonym_var_cnt++), scope, line, scope == 0 ? GLOBAL : _LOCAL, VAR, var_s, currScopeSpace(), currScopeOffset()));
        incCurrScopeOffset();
        emit(assign, lvalue, NULL, term, -1, line);
    }

    return term;
}

expr* manage_term_lvalue_minusminus(int debug, FILE* out, SymbolTable* symTable, expr* lvalue, unsigned int scope, unsigned int line) {
    if(debug) fprintf(out, MAG "Detected :" RESET"lvalue--"CYN" ->"RESET" term \n");
    
    if(lvalue != NULL) {
        if(check_arith(lvalue,out_file, line, "arithmetic")) 
            return NULL;
    }

    expr* term = new_expr(var_e);
    term->sym = symbol_table_insert(symTable, symbol_create(str_int_merge("_t",anonym_var_cnt++), scope, line, scope == 0 ? GLOBAL : _LOCAL, VAR, var_s, currScopeSpace(), currScopeOffset()));
    incCurrScopeOffset();

    if(lvalue->type == tableitem_e){
        expr * val = emit_if_tableitem(lvalue, scope, line);
        emit(assign, val, NULL, term, -1, line);
        emit(sub, val, new_const_num(1), val, -1, line);
        emit(tablesetelem, lvalue->index, val, lvalue, -1, line);
    }
    else{
        emit(assign, lvalue, NULL, term, -1, line);
        emit(sub, lvalue, new_const_num(1), lvalue, -1, line);  
    }
    return term;
}
/*End of ++ --*/

void manage_term_primary(int debug, FILE* out) {
    if(debug) fprintf(out, MAG "Detected :" RESET"primary"CYN" ->"RESET" term \n");
}

expr* manage_assignexpr_lvalue_assign_expr(int debug, FILE* out, SymbolTable* symTable, expr* lvalue, expr* expr1, unsigned int scope, unsigned int line) {
    if(debug) fprintf(out, MAG "Detected :" RESET"lvalue = expr"CYN" ->"RESET" assignexpr \n");
    if(lvalue != NULL) {
        if(is_id_built_in_function(lvalue->sym->name)){
            fprintf(out_file,RED"Error:"RESET" Cannot assign to a library function \""YEL"%s"RESET"\" (line: "GRN"%d"RESET") \n", lvalue->sym->name, line);
            error_flag = 1;
            return NULL;
        }

        for(int i = scope; i >= 0; i--) {
            Symbol* tmp_symbol = symbol_table_scope_lookup(symTable, lvalue->sym->name, i); 
            if(tmp_symbol != NULL){
                if( tmp_symbol->symbol_type == USERFUNC) {
                    fprintf(out_file,RED"Error:"RESET" Cannot assign to a function \""YEL"%s"RESET"\" (line: "GRN"%d"RESET") \n", lvalue->sym->name, line);
                    error_flag = 1;
                    return NULL;
                }
                else{
                    
                    if(lvalue->type == tableitem_e){
                        emit(tablesetelem, lvalue->index, expr1, lvalue, -1, line);
                        return emit_if_tableitem(lvalue, scope, line);
                    }
                    else{
                        emit(assign, expr1, NULL, lvalue, -1, line);
                        //Creating an extra hidden var to store lvalue (FAQ : 18)
                        expr* result;
                        result = new_lvalue_expr(symbol_table_insert(symTable, symbol_create(str_int_merge("_t",anonym_var_cnt++), scope, line, scope == 0 ? GLOBAL : _LOCAL, VAR, var_s, currScopeSpace(), currScopeOffset())));
                        incCurrScopeOffset();
                        emit(assign, lvalue, NULL, result, -1, line);

                        lvalue->hidden_var = result; //making the lvalue point to the hidden var (to find it when we need it)

                        return result;  //if something breaks change this to lvalue
                    }
                }
            }
        }
    }
    return NULL;
}

expr* manage_primary_lvalue(int debug, FILE* out, expr* lvalue, unsigned int scope, unsigned int line) {
    if(debug) fprintf(out, MAG "Detected :" RESET"lvalue"CYN" ->"RESET" primary \n");

    return emit_if_tableitem(lvalue, scope, line);
}

void manage_primary_call(int debug, FILE* out) {
    if(debug) fprintf(out, MAG "Detected :" RESET"call"CYN" ->"RESET" primary \n");
}

void manage_primary_objectdef(int debug, FILE* out) {
    if(debug) fprintf(out, MAG "Detected :" RESET"objectdef"CYN" ->"RESET" primary \n");
}

expr* manage_primary_lpar_funcdef_rpar(int debug, FILE* out, Symbol* funcdef_s) {
    if(debug) fprintf(out, MAG "Detected :" RESET"( funcdef )"CYN" ->"RESET" primary \n");

    if(funcdef_s){
        expr* funcdef_e = new_expr(programfunc_e);
        funcdef_e->sym = funcdef_s;
        return funcdef_e;
    }
    return NULL;
}

void manage_primary_const(int debug, FILE* out) {
    if(debug) fprintf(out, MAG "Detected :" RESET"const"CYN" ->"RESET" primary \n");
}

expr* manage_lvalue_ident(int debug, FILE* out, SymbolTable* symTable, char* id, enum SymbolType type, unsigned int scope, unsigned int line, ScopeStackList *tail) {
    
    if(debug) fprintf(out, MAG "Detected :" RESET"%s"CYN" ->"RESET" IDENT"CYN" ->"RESET" lvalue \n",id);

    Symbol* sym = symbol_table_scope_lookup(symTable, id, scope); //check current scope
    if(sym != NULL) {
        return new_lvalue_expr(sym);
    }

    //flag purpose: check if a variable with the same name is declared in a higher scope
    int flag = 0;
    ScopeStackList* tmp = tail;
    if(scope > 0) { //check all other scopes except global
        for(int i = scope - 1; i > 0; i--) {
            Symbol* tmp_symbol = symbol_table_scope_lookup(symTable, id, i);
            
            if(tmp != NULL) flag = tmp->flag;
            
            if(tmp_symbol != NULL && tmp_symbol->is_variable) {
                if(flag == 1){
                    fprintf(out_file,RED"Error:"RESET" Variable \""YEL"%s"RESET"\" is not accessible (line: "GRN"%d"RESET")\n", id, line);        
                    error_flag = 1;
                    return NULL;
                }
                else {
                    return new_lvalue_expr(tmp_symbol);
                }
            }
            if(tmp != NULL) tmp = tmp->prev;
        }
    }

    sym = symbol_table_scope_lookup(symTable, id, 0);//check global scope
    if(sym != NULL) return new_lvalue_expr(sym);  

    char* name     = strdup(id);
    Symbol* symbol = symbol_create(name, scope, line, type, VAR, var_s, currScopeSpace(), currScopeOffset());
    incCurrScopeOffset();
    symbol_table_insert(symTable, symbol);

    return new_lvalue_expr(symbol);
}

expr* manage_lvalue_local_ident(int debug, FILE* out, SymbolTable* symTable, char* id, unsigned int scope, unsigned int line) {
    if(debug) fprintf(out, MAG "Detected :" RESET"local \"%s\""CYN" ->"RESET" LOCAL IDENT"CYN" ->"RESET" lvalue \n", id);

    Symbol* sym = symbol_table_scope_lookup(symTable, id, scope);
    if(sym != NULL) return new_lvalue_expr(sym);

    if(is_id_built_in_function(id)) {
        fprintf(out_file,RED"Error:"RESET" Cannot declare (shadow) Variable with library function name \""YEL"%s"RESET"\" (line: "GRN"%d"RESET") \n", id,line);
        error_flag = 1;
        return NULL;
    }

    char* name     = strdup(id);
    Symbol* symbol = symbol_create(name, scope, line, scope == 0 ? GLOBAL : _LOCAL, VAR, var_s, currScopeSpace(), currScopeOffset());
    incCurrScopeOffset();

    symbol_table_insert(symTable, symbol);

    return new_lvalue_expr(symbol);
}

expr* manage_lvalue_global_ident(int debug, FILE* out, SymbolTable* symTable, char* id, unsigned int scope, unsigned int line) {
    if(debug) fprintf(out, MAG "Detected :" RESET"::%s"CYN" ->"RESET" ::IDENT"CYN" ->"RESET" lvalue \n", id);

    Symbol* sym =  symbol_table_scope_lookup(symTable, id, 0);
    if(sym != NULL) return new_lvalue_expr(sym);
    fprintf(out_file,RED"Error:"RESET" Variable \""YEL"%s"RESET"\" doesn't exist in global scope (line: "GRN"%d"RESET") \n", id, line);
    error_flag = 1;

    return NULL;
}

expr* manage_lvalue_member(int debug, FILE* out, expr* member) {
    if(debug) fprintf(out, MAG "Detected :" RESET"member"CYN" ->"RESET" lvalue \n");
    return member;
}

expr* manage_memeber_lvalue_dot_ident(int debug, FILE* out, expr* lvalue, char* name, unsigned int scope, unsigned int line, int* normalcall_skip) {
    if(debug) fprintf(out, MAG "Detected :" RESET"lvalue .IDENT"CYN" ->"RESET" member \n");
    *normalcall_skip = 0;


    return new_member_item(lvalue, name, scope, line);
}

void manage_memeber_lvalue_lbr_expr_rbr(int debug, FILE* out, expr* lvalue, expr* expr_list, expr** tableitem, unsigned int scope, unsigned int line) {
    if(debug) fprintf(out, MAG "Detected :" RESET"lvalue [ expr ]"CYN" ->"RESET" member \n");
    
    lvalue = emit_if_tableitem(lvalue,scope,line);
    (*tableitem) = new_expr(tableitem_e);
    (*tableitem)->sym = lvalue->sym;
    (*tableitem)->index = expr_list;
    
}

expr* manage_member_call_dot_ident(int debug, FILE* out, expr* call, char* id, int* normalcall_skip) {
    if(debug) fprintf(out, MAG "Detected :" RESET"call . IDENT"CYN" ->"RESET" member \n");
    *normalcall_skip = 0;
    
    //keep in mind that this expression has only the name of the symbol and nothing else
    expr* e_for_name = (expr*)malloc(sizeof(expr));
    e_for_name->sym  = (Symbol*)malloc(sizeof(Symbol));
    e_for_name->sym->name = id;
    
    return e_for_name;
}

void manage_member_call_lbr_expr_rbr(int debug, FILE* out, expr* call, expr* expr1, expr** tableitem, unsigned int scope, unsigned int line) {
    if(debug) fprintf(out, MAG "Detected :" RESET"call [ expr ]"CYN" ->"RESET" member \n");
    
    call = emit_if_tableitem(call,scope,line);
    (*tableitem) = new_expr(tableitem_e);
    (*tableitem)->sym = call->sym;
    (*tableitem)->index = expr1;
    
}

expr* manage_call_call_lpar_elist_rpar  (int debug, FILE* out, unsigned int scope, unsigned int line, expr* lvalue, expr* elist) {
    if(debug) fprintf(yyout, MAG "Detected :" RESET"call ( elist )"CYN" ->"RESET" call \n");

    if(lvalue)
        return manage_func_call(lvalue, elist, scope, line);
    return NULL;
}

expr* manage_call_lvalue_callsuffix(int debug, FILE* out, SymbolTable* symTable, expr* lvalue, int* normalcall_skip, unsigned int scope, unsigned int line, callexpr* c_expr) {
    if(debug) fprintf(out, MAG "Detected :" RESET"lvalue callsuffix"CYN" ->"RESET" call \n");
    if(!(*normalcall_skip)) {
        if(lvalue) {
            lvalue = emit_if_tableitem(lvalue,scope,line);
            if(c_expr->method){
                expr *temp,*t = lvalue;
                lvalue = emit_if_tableitem(new_member_item(t,c_expr->name,scope,line),scope,line);
                temp = c_expr->elist;
                if (!c_expr->elist)
                    c_expr->elist = t;
                else{
                    c_expr->elist=t;
                    t->next=temp;
                }
            }
            return manage_func_call(lvalue, c_expr->elist, scope, line);
        }
    }
    *normalcall_skip = 0;
    return NULL;
}

expr* manage_call_lpar_funcdef_rpar_lpar_elist_rpar(int debug, FILE* out, unsigned int scope, unsigned int line, Symbol *funcdef, expr* elist) {
    if(debug) fprintf(out, MAG "Detected :" RESET"( funcdef ) ( elist )"CYN" ->"RESET" call \n");

    expr* func = new_expr(programfunc_e);
    func->sym = funcdef;
    return manage_func_call(func, elist, scope, line);
}

callexpr* manage_callsuffix_normcall  (int debug, FILE* out, callexpr* c_expr) {
    if(debug) fprintf(out, MAG "Detected :" RESET"normcall"CYN" ->"RESET" callsuffix \n");
    //probably unnecessary
    return c_expr;
}

callexpr* manage_callsuffix_methodcall(int debug, FILE* out, callexpr* c_expr) {
    if(debug) fprintf(out, MAG "Detected :" RESET"methodcall"CYN" ->"RESET" callsuffix \n");
    //probably unnecessary
    return c_expr;
}

callexpr* manage_normcall_lpar_elist_rpar(int debug, FILE* out, unsigned int method, expr* elist, char* name) {
    if(debug) fprintf(out, MAG "Detected :" RESET"( elist )"CYN" ->"RESET" normcall \n");        

    return new_callexpr(0,elist,name);
}

callexpr* manage_methodcall_ddot_ident_lpar_elist_rpar(int debug, FILE* out, int* normalcall_skip, unsigned int method, expr* elist, char* name) {
    if(debug) fprintf(out, MAG "Detected :" RESET".. IDENT ( elist )"CYN" ->"RESET" methodcall \n");

    *normalcall_skip = 0;
    
    return new_callexpr(1,elist,name);
}

expr* manage_comexpropt_empty(int debug, FILE* out) {
    if(debug) fprintf(out, MAG "Detected :" RESET"com_expr_opt"YEL" (empty) "RESET"\n");
    return NULL;
}

expr* manage_comexpropt_comma_expr_comexpropt(int debug, FILE* out, expr* expr1, expr* com_expr_opt) {
    if(debug) fprintf(out, MAG "Detected :" RESET"COMMA expr com_expr_opt \n");
    expr1->next = com_expr_opt;
    return expr1;
}

expr* manage_objectdef_lbrace_indexed_rbrace(int debug, FILE* out, expr* indexed, unsigned int scope, unsigned int line) {
    if(debug) fprintf(out, MAG "Detected :" RESET"[ indexed ]"CYN" ->"RESET" objectdef \n");

    expr* t = new_expr(newtable_e);
    //create new temp
    t->sym = symbol_table_insert(symTable, symbol_create(str_int_merge("_t",anonym_var_cnt++), scope, line, scope == 0 ? GLOBAL : _LOCAL, VAR, var_s, currScopeSpace(), currScopeOffset()));
    incCurrScopeOffset();

    emit(tablecreate, NULL, NULL, t, -1, line);
    for(; indexed; indexed = indexed->next)
        emit(tablesetelem, indexed, indexed->index, t, -1, line);

    return t;
}

expr* manage_objectdef_lbrace_elist_rbrace(int debug, FILE* out, expr* elist, unsigned int scope, unsigned int line) {
    if(debug) fprintf(out, MAG "Detected :" RESET"[ elist ]"CYN" ->"RESET" objectdef \n");

    expr* t = new_expr(newtable_e);
    //create new temp
    t->sym = symbol_table_insert(symTable, symbol_create(str_int_merge("_t",anonym_var_cnt++), scope, line, scope == 0 ? GLOBAL : _LOCAL, VAR, var_s, currScopeSpace(), currScopeOffset()));
    incCurrScopeOffset();

    emit(tablecreate, NULL, NULL, t, -1, line);
    for(int i = 0; elist; elist = elist->next)
        emit(tablesetelem, new_const_num(i++), elist, t, -1, line);
    
    return t;
}

expr* manage_elist_empty(int debug, FILE* out) {
    if(debug) fprintf(out, MAG "Detected :" RESET"elist"YEL" (empty)"RESET"\n");
    return NULL;
}

expr* manage_elist_expr(int debug, FILE* out) {
    if(debug) fprintf(out, MAG "Detected :" RESET"expr"CYN" ->"RESET" elist \n");

    return NULL;
}

expr* manage_elist_elist_comma_exp(int debug, FILE* out, expr* expr1, expr* com_expr_opt) {
    if(debug) fprintf(out, MAG "Detected :" RESET"elist , expr"CYN" ->"RESET" elist \n");
    
    expr* list_head = expr1;
    
    while(expr1->next != NULL)
        expr1 = expr1->next;
    
    expr1->next = com_expr_opt;
    
    return list_head;
}

expr* manage_indexed_indexedelem_comindexedelemopt(int debug, FILE* out, expr* indexedelem, expr* com_indexedelem_opt) {
    if(debug) fprintf(out, MAG "Detected :" RESET"indexedelem com_indexedelem_opt"CYN" ->"RESET" indexed \n");

    indexedelem->next = com_indexedelem_opt;
    return indexedelem;
}

expr* manage_indexedele_lcbrace_expr_colon_expr_rcbrace(int debug, FILE* out, expr* index, expr* value) {
    if(debug) fprintf(out, MAG "Detected :" RESET"{ expr : expr }"CYN" ->"RESET" indexedelem \n");
    
    index->index = value;

    return index;
}

expr* manage_comindexedelemopt_empty(int debug, FILE* out) {
    if(debug) fprintf(out, MAG "Detected :" RESET"com_indexedelem_opt "YEL"(empty)"RESET"\n");
    return NULL;
}

expr* manage_comindexedelemopt_comma_indexedelem_comindexedelemopt(int debug, FILE* out, expr* indexedelem, expr* com_indexedelem_opt) {
    if(debug) fprintf(out, MAG "Detected :" RESET", indexedelem com_indexedelem_opt \n");

    indexedelem->next = com_indexedelem_opt;
    return indexedelem;
}

expr* manage_stmtList_empty(int debug, FILE* out) {
    if(debug) fprintf(out, MAG "Detected :" RESET"stmtList"YEL" (empty)"RESET":\n");
    return NULL;
}

expr* manage_stmtList_stmt(int debug, FILE* out) {
    if(debug) fprintf(out, MAG "Detected :" RESET"stmt"CYN" ->"RESET" stmtList \n");
    return NULL;
}

expr* manage_stmtList_stmt_stmtList(int debug, FILE* out) {
    if(debug) fprintf(out, MAG "Detected :" RESET"stmt stmtList"CYN" ->"RESET" stmtList \n");
    return NULL;
}

stmt_t* manage_ifstmt(int debug, FILE* out, int ifprefix, stmt_t* stmt, unsigned int scope, unsigned int line) {
    if(debug) fprintf(out, MAG "Detected :" RESET"IF ( expr ) stmt"CYN"-> "RESET"ifstmt  \n");

    patchLabel(ifprefix, nextQuadLabel());
    return stmt;
}

stmt_t* manage_ifstmt_else(int debug, FILE* out, int ifprefix, stmt_t* stmt1, int elseprefix, stmt_t* stmt2, unsigned int scope, unsigned int line) {
    if(debug) fprintf(out, MAG "Detected :" RESET"IF ( expr ) stmt ELSE stmt"CYN"-> "RESET"ifstmt \n");

    patchLabel(ifprefix, elseprefix+1);
    patchLabel(elseprefix, nextQuadLabel());

    stmt_t *stmt     = make_stmt();
    stmt->break_list = merge_list(stmt1->break_list, stmt2->break_list);
    stmt->cont_list  = merge_list(stmt1->cont_list , stmt2->cont_list);
    return stmt;
}

int manage_ifprefix(int debug, FILE* out, expr* expr1, unsigned int scope, unsigned int line) {

    if(debug) fprintf(out, MAG "Detected :" RESET"ifprefix\n");

    expr* true_expr = new_expr(constbool_e);
    true_expr->boolConst = 1;
    
    emit(if_eq, expr1, true_expr, NULL, nextQuadLabel()+2, line);
    emit(jump, NULL, NULL, NULL, -1, line);

    return nextQuadLabel()-1;
}

int manage_elseprefix (int debug, FILE* out, unsigned int scope, unsigned int line) {
    if(debug) fprintf(out, MAG "Detected :" RESET"elseprefix\n");
    
    emit(jump, NULL, NULL, NULL, -1, line);
    return nextQuadLabel()-1;
}

int convert_to_bool(expr* expr) {
    switch(expr->type) {
        case constbool_e:
            return expr->boolConst;
        case conststring_e:
            if(strcmp(expr->strConst, "") == 0) return 0;
            else return 1;
        case constnum_e:
            if(expr->numConst == 0) return 0;
            else return 1;
        case nil_e:
            return 0;
        case newtable_e:
            return 1;
        case programfunc_e:
            return 1;
        case libraryfunc_e:
            return 1;
        default:
            return -1;
    }
}