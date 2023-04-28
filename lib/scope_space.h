#ifndef SCOPE_SPACE_H
#define SCOPE_SPACE_H

enum scopespace_t{ programvar, functionlocal, formalarg };     //phase 3   

unsigned int programVarOffset    = 0;
unsigned int functionLocalOffset = 0;
unsigned int formalArgOffset     = 0;
unsigned int scopeSpaceCounter   = 0;


enum scopespace_t currScopeSpace();
unsigned int currScopeOffset();
void incCurrOffset();
void enterScopeSpace();
void exitScopeSpace();

#endif /* SCOPE_SPACE_H */