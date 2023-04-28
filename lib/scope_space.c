#include "scope_space.h"
#include <assert.h>

unsigned int programVarOffset    = 0;
unsigned int functionLocalOffset = 0;
unsigned int formalArgOffset     = 0;
unsigned int scopeSpaceCounter   = 0;

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

void inccurrScopeOffset(){
    
    switch (currScopeSpace())
    {
    case programvar : ++programVarOffset; break;
    case functionlocal : ++functionLocalOffset; break;
    case formalarg : ++formalArgOffset; break;
    default: assert(0);
    }
}

void enterscopespace(){
    ++scopeSpaceCounter;
}

void exitscopespace(){
    assert(scopeSpaceCounter > 1);
    scopeSpaceCounter -= 2;
}