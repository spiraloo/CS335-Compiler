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

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
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
    NEWLINE = 258,                 /* NEWLINE  */
    ENDMARKER = 259,               /* ENDMARKER  */
    NAME = 260,                    /* NAME  */
    INDENT = 261,                  /* INDENT  */
    DEDENT = 262,                  /* DEDENT  */
    NUMBER = 263,                  /* NUMBER  */
    STRING = 264,                  /* STRING  */
    KEYWORD_FALSE = 265,           /* KEYWORD_FALSE  */
    KEYWORD_NONE = 266,            /* KEYWORD_NONE  */
    KEYWORD_TRUE = 267,            /* KEYWORD_TRUE  */
    KEYWORD_AND = 268,             /* KEYWORD_AND  */
    KEYWORD_ASSERT = 269,          /* KEYWORD_ASSERT  */
    KEYWORD_BREAK = 270,           /* KEYWORD_BREAK  */
    KEYWORD_CLASS = 271,           /* KEYWORD_CLASS  */
    KEYWORD_CONTINUE = 272,        /* KEYWORD_CONTINUE  */
    KEYWORD_DEF = 273,             /* KEYWORD_DEF  */
    KEYWORD_ELIF = 274,            /* KEYWORD_ELIF  */
    KEYWORD_ELSE = 275,            /* KEYWORD_ELSE  */
    KEYWORD_FOR = 276,             /* KEYWORD_FOR  */
    KEYWORD_FROM = 277,            /* KEYWORD_FROM  */
    KEYWORD_GLOBAL = 278,          /* KEYWORD_GLOBAL  */
    KEYWORD_IF = 279,              /* KEYWORD_IF  */
    KEYWORD_IN = 280,              /* KEYWORD_IN  */
    KEYWORD_NONLOCAL = 281,        /* KEYWORD_NONLOCAL  */
    KEYWORD_NOT = 282,             /* KEYWORD_NOT  */
    KEYWORD_OR = 283,              /* KEYWORD_OR  */
    KEYWORD_RAISE = 284,           /* KEYWORD_RAISE  */
    KEYWORD_RETURN = 285,          /* KEYWORD_RETURN  */
    KEYWORD_WHILE = 286,           /* KEYWORD_WHILE  */
    OP_POWER = 287,                /* OP_POWER  */
    OP_INT_DIVIDE_EQUALS = 288,    /* OP_INT_DIVIDE_EQUALS  */
    OP_POWER_EQUALS = 289,         /* OP_POWER_EQUALS  */
    OP_RIGHT_SHIFT_EQUALS = 290,   /* OP_RIGHT_SHIFT_EQUALS  */
    OP_LEFT_SHIFT_EQUALS = 291,    /* OP_LEFT_SHIFT_EQUALS  */
    OP_XOR_EQUALS = 292,           /* OP_XOR_EQUALS  */
    OP_OR_EQUALS = 293,            /* OP_OR_EQUALS  */
    OP_AND_EQUALS = 294,           /* OP_AND_EQUALS  */
    OP_MOD_EQUALS = 295,           /* OP_MOD_EQUALS  */
    OP_DIVIDE_EQUALS = 296,        /* OP_DIVIDE_EQUALS  */
    OP_MULTIPLY_EQUALS = 297,      /* OP_MULTIPLY_EQUALS  */
    OP_MINUS_EQUALS = 298,         /* OP_MINUS_EQUALS  */
    OP_PLUS_EQUALS = 299,          /* OP_PLUS_EQUALS  */
    OP_NOT_EQUALS = 300,           /* OP_NOT_EQUALS  */
    OP_EQUALS = 301,               /* OP_EQUALS  */
    OP_RIGHT_SHIFT = 302,          /* OP_RIGHT_SHIFT  */
    OP_LEFT_SHIFT = 303,           /* OP_LEFT_SHIFT  */
    OP_INT_DIVIDE = 304,           /* OP_INT_DIVIDE  */
    OP_GREATER_THAN_EQUALS = 305,  /* OP_GREATER_THAN_EQUALS  */
    OP_LESS_THAN_EQUALS = 306,     /* OP_LESS_THAN_EQUALS  */
    OP_ARROW = 307                 /* OP_ARROW  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 106 "parser.y"

    char* str;
    class TreeNode* ptr;
    int num;    

#line 122 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
