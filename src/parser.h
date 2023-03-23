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
    ASSIGN = 262,                  /* "="  */
    PLUS = 263,                    /* "+"  */
    MINUS = 264,                   /* "-"  */
    MUL = 265,                     /* "*"  */
    DIV = 266,                     /* "/"  */
    MOD = 267,                     /* "%"  */
    EQ = 268,                      /* "=="  */
    NEQ = 269,                     /* "!="  */
    INC = 270,                     /* "++"  */
    DEC = 271,                     /* "--"  */
    GT = 272,                      /* ">"  */
    LT = 273,                      /* "<"  */
    GTE = 274,                     /* ">="  */
    LTE = 275,                     /* "<="  */
    LBRACE = 276,                  /* "["  */
    RBRACE = 277,                  /* "]"  */
    LCBRACE = 278,                 /* "{"  */
    RCBRACE = 279,                 /* "}"  */
    LPAR = 280,                    /* "("  */
    RPAR = 281,                    /* ")"  */
    SEMI = 282,                    /* ";"  */
    COMMA = 283,                   /* ","  */
    COLON = 284,                   /* ":"  */
    DCOLON = 285,                  /* "::"  */
    DOT = 286,                     /* "."  */
    DDOT = 287,                    /* ".."  */
    UMINUS = 288,                  /* UMINUS  */
    AND = 289,                     /* AND  */
    OR = 290,                      /* OR  */
    NOT = 291,                     /* NOT  */
    IF = 292,                      /* IF  */
    ELSE = 293,                    /* ELSE  */
    WHILE = 294,                   /* WHILE  */
    FOR = 295,                     /* FOR  */
    FUNCTION = 296,                /* FUNCTION  */
    RETURN = 297,                  /* RETURN  */
    BREAK = 298,                   /* BREAK  */
    CONTINUE = 299,                /* CONTINUE  */
    LOCAL = 300,                   /* LOCAL  */
    TRUE = 301,                    /* TRUE  */
    FALSE = 302,                   /* FALSE  */
    NIL = 303                      /* NIL  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 7 "src/parser.y"

    int intVal;
    double realVal;
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
