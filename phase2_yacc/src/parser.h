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

#ifndef YY_YY_PHASE2_YACC_SRC_PARSER_H_INCLUDED
# define YY_YY_PHASE2_YACC_SRC_PARSER_H_INCLUDED
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
    ASSIGN = 258,                  /* ASSIGN  */
    PLUS = 259,                    /* PLUS  */
    MINUS = 260,                   /* MINUS  */
    MUL = 261,                     /* MUL  */
    DIV = 262,                     /* DIV  */
    MOD = 263,                     /* MOD  */
    EQ = 264,                      /* EQ  */
    NEQ = 265,                     /* NEQ  */
    INC = 266,                     /* INC  */
    DEC = 267,                     /* DEC  */
    GT = 268,                      /* GT  */
    LT = 269,                      /* LT  */
    GTE = 270,                     /* GTE  */
    LTE = 271,                     /* LTE  */
    UMINUS = 272,                  /* UMINUS  */
    AND = 273,                     /* AND  */
    OR = 274,                      /* OR  */
    NOT = 275,                     /* NOT  */
    IF = 276,                      /* IF  */
    ELSE = 277,                    /* ELSE  */
    WHILE = 278,                   /* WHILE  */
    FOR = 279,                     /* FOR  */
    FUNCTION = 280,                /* FUNCTION  */
    RETURN = 281,                  /* RETURN  */
    BREAK = 282,                   /* BREAK  */
    CONTINUE = 283,                /* CONTINUE  */
    LOCAL = 284,                   /* LOCAL  */
    TRUE = 285,                    /* TRUE  */
    FALSE = 286,                   /* FALSE  */
    NIL = 287,                     /* NIL  */
    LBRACE = 288,                  /* LBRACE  */
    RBRACE = 289,                  /* RBRACE  */
    LCBRACE = 290,                 /* LCBRACE  */
    RCBRACE = 291,                 /* RCBRACE  */
    LPAR = 292,                    /* LPAR  */
    RPAR = 293,                    /* RPAR  */
    SEMI = 294,                    /* SEMI  */
    COMMA = 295,                   /* COMMA  */
    COLON = 296,                   /* COLON  */
    DCOLON = 297,                  /* DCOLON  */
    DOT = 298,                     /* DOT  */
    DDOT = 299,                    /* DDOT  */
    IDENT = 300,                   /* IDENT  */
    STRING = 301,                  /* STRING  */
    INTCONST = 302,                /* INTCONST  */
    REALCONST = 303                /* REALCONST  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 12 "phase2_yacc/src/parser.y"



#line 116 "phase2_yacc/src/parser.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PHASE2_YACC_SRC_PARSER_H_INCLUDED  */
