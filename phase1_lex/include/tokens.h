/*Compilation parameters*/

//Enable to print \n instead of actual newlines.
#define DISABLE_NEWLINE_PRINTING

extern FILE* yyout;
extern FILE* yyin;

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

struct alpha_token_t {
    unsigned int numline;
    unsigned int numToken;
    char         *content;
    enum type    tType;
    enum subtype sType;
    struct alpha_token_t *next;
};

typedef struct alpha_token_t alpha_token_t;

struct TokenList{
    alpha_token_t *head;
    alpha_token_t *tail;
};

typedef struct line_stack{
    int line;
    struct line_stack *next;
} line_stack;

typedef struct {
    line_stack *top;
} line_stack_top;

typedef struct TokenList TokenList;

void insert_token(TokenList *tokenList, int numline, int numToken, char *content, enum type tType, enum subtype sType);
const char* str_type(enum type s);
const char* str_subtype(enum subtype s);
enum subtype get_subtype(enum type s, char *str);
void print_list(TokenList *tokenList, FILE *yyout);
int alpha_yylex(void* yylval);