#ifndef SCOPE_SPACE_H_
#define SCOPE_SPACE_H_

enum scopespace_t{ programvar, functionlocal, formalarg };     //phase 3   

enum scopespace_t currScopeSpace();
unsigned int currScopeOffset();
void incCurrScopeOffset();
void enterScopeSpace();
void exitScopeSpace();

#endif