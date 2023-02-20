enum type{
    STRING,
    INTCONST,
    REALCONST,
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
    DDOT
};


struct alpha_token_t {
    unsigned int numline;
    unsigned int numToken;
    char         *content;
    enum type    tType;
    enum subtype sType;
    struct alpha_token_t *next;
    struct alpha_token_t *head;
    struct alpha_token_t *tail;
};

typedef struct alpha_token_t alpha_token_t;

void insert_token(alpha_token_t *tokenList, int numline,int numToken, char *content, enum type tType);