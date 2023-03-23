/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_SRC_PARSER_H_INCLUDED
# define YY_YY_SRC_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    INTCONST = 258,                /* INTCONST  */
    REALCONST = 259,               /* REALCONST  */
    STRING = 260,                  /* STRING  */
    IDENT = 261,                   /* IDENT  */
    ASSIGN = 262,                  /* ASSIGN  */
    PLUS = 263,                    /* PLUS  */
    MINUS = 264,                   /* MINUS  */
    MUL = 265,                     /* MUL  */
    DIV = 266,                     /* DIV  */
    MOD = 267,                     /* MOD  */
    EQ = 268,                      /* EQ  */
    NEQ = 269,                     /* NEQ  */
    INC = 270,                     /* INC  */
    DEC = 271,                     /* DEC  */
    GT = 272,                      /* GT  */
    LT = 273,                      /* LT  */
    GTE = 274,                     /* GTE  */
    LTE = 275,                     /* LTE  */
    UMINUS = 276,                  /* UMINUS  */
    AND = 277,                     /* AND  */
    OR = 278,                      /* OR  */
    NOT = 279,                     /* NOT  */
    IF = 280,                      /* IF  */
    ELSE = 281,                    /* ELSE  */
    WHILE = 282,                   /* WHILE  */
    FOR = 283,                     /* FOR  */
    FUNCTION = 284,                /* FUNCTION  */
    RETURN = 285,                  /* RETURN  */
    BREAK = 286,                   /* BREAK  */
    CONTINUE = 287,                /* CONTINUE  */
    LOCAL = 288,                   /* LOCAL  */
    TRUE = 289,                    /* TRUE  */
    FALSE = 290,                   /* FALSE  */
    NIL = 291,                     /* NIL  */
    LBRACE = 292,                  /* LBRACE  */
    RBRACE = 293,                  /* RBRACE  */
    LCBRACE = 294,                 /* LCBRACE  */
    RCBRACE = 295,                 /* RCBRACE  */
    LPAR = 296,                    /* LPAR  */
    RPAR = 297,                    /* RPAR  */
    SEMI = 298,                    /* SEMI  */
    COMMA = 299,                   /* COMMA  */
    COLON = 300,                   /* COLON  */
    DCOLON = 301,                  /* DCOLON  */
    DOT = 302,                     /* DOT  */
    DDOT = 303                     /* DDOT  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 7 "src/parser.y"

    int intVal;
    double doubleVal;
    char *stringVal;

#line 118 "src/parser.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_SRC_PARSER_H_INCLUDED  */
