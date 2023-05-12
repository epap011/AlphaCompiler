#include "scope_space.h"
#include <assert.h>

unsigned int programVarOffset    = 0;
unsigned int functionLocalOffset = 0;
unsigned int formalArgOffset     = 0;
unsigned int scopeSpaceCounter   = 1;

enum scopespace_t currScopeSpace(){
    
    if(scopeSpaceCounter == 1)
        return programvar;
    else if (scopeSpaceCounter % 2 == 0)
        return formalarg;
    else
        return functionlocal;
}

unsigned int currScopeOffset(){

    switch (currScopeSpace())
    {
    case programvar : return programVarOffset;
    case functionlocal : return functionLocalOffset;
    case formalarg : return formalArgOffset;
    default: assert(0);
    }
}

void incCurrScopeOffset(){
    
    switch (currScopeSpace())
    {
    case programvar : ++programVarOffset; break;
    case functionlocal : ++functionLocalOffset; break;
    case formalarg : ++formalArgOffset; break;
    default: assert(0);
    }
}

void enterScopeSpace(){
    ++scopeSpaceCounter;
}

void exitScopeSpace(){
    assert(scopeSpaceCounter > 1);
    scopeSpaceCounter-=2;
}

void resetFormalArgsOffset(){
    formalArgOffset = 0;
}

void resetFunctionLocalsOffset(){
    functionLocalOffset = 0;
}

void restoreCurrScopeOffset(unsigned int n){
    switch (currScopeSpace())
    {
    case programvar     :  programVarOffset = n; break;
    case functionlocal  : functionLocalOffset = n; break;
    case formalarg      : formalArgOffset = n; break;
    default: assert(0);
    }

}