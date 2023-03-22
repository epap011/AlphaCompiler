#ifndef ALPHA_TYPES_H
#define ALPHA_TYPES_H

enum type{
    STRING,
    NUMBER,
    IDENT,
    OPERATOR,
    KEYWORD,
    PUNCTUATION,
    COMMENT,
    UNDEFCHR
};

enum subtype{
    /*Operators*/
    ASSIGN,
    PLUS,
    MINUS,
    MUL,
    SLASH,
    MOD,
    EQ,
    NEQ,
    INC,
    DEC,
    GT,
    LT,
    GTE,
    LTE,
    /*Keywords*/
    IF,
    ELSE,
    WHILE,
    FOR,
    FUNCTION,
    RETURN,
    BREAK,
    CONTINUE,
    AND,
    NOT,
    OR,
    LOCAL,
    TRUE,
    FALSE,
    NIL,
    /*Punctuation*/
    LBRACE,
    RBRACE,
    LCBRACE,
    RCBRACE,
    LPAR,
    RPAR,
    SEMI,
    COMMA,
    COLON,
    DCOLON,
    DOT,
    DDOT,
    /*Numbers*/
    INTCONST,
    REALCONST,
    /*Comments*/
    LINECOMM,
    BLOCKCOMM,
    NESTCOMM,
    /*Invalid value*/
    NOSTYPE
};

const char* str_type(enum type s);
const char* str_subtype(enum subtype s);
enum subtype get_subtype(enum type s, char *str);

#endif /* ALPHA_TYPES_H */