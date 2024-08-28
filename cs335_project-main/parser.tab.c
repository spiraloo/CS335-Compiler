/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

    #include <cstdio> 
    #include <cstring>
    #include <iostream>
    #include <fstream>
    #include <vector>
    #include <stdio.h>
    #include "x86.hpp"
    using namespace std;
    extern vector<string> class_names;
    extern "C" int yylex();
    extern "C" int yylineno;
    void yyerror(const char* s);
    extern "C" FILE* yyin;
    TreeNode* root = nullptr;
    SymbolTable* globalTable = new SymbolTable(ST_Type::st_top , 1, nullptr, STentry_Type::ste_none,"globalTable");
    
    SymbolTable* currentTable = globalTable;
    bool verbose = false;
    bool type_expect = false;
    vector<string> type_expect_list;
    int size_of_type(STentry* entry){
    if (entry->get_type() == STentry_Type::ste_class_obj) {
        if (find(class_names.begin(), class_names.end(), entry->get_class_obj_name()) != class_names.end()) {
            SymbolTable* class_entry = (SymbolTable*)globalTable->lookup(entry->get_class_obj_name())->get_nested_table();
            return class_entry->get_size();
        }
    }
    else {
        return sizeofdatatype(entry->get_type());
    }
}
    void find_type(STentry* entry, bool is_return_type)
    {
        if(type_expect_list.size() == 0)
        {
            printf("Line %d:Type Error : No type for the parameter %s \n",entry->get_lineno(), entry->get_name());
            exit(1);
        }
        int i =0;
        if(type_expect_list[0] == "NAME (list)")
        {
            if(is_return_type)
                currentTable->set_is_list(true);
            else
                entry->set_is_list(true);
            i = 1;
        }
        if(type_expect_list[i] == "NAME (int)")
        {
            if(is_return_type)
                currentTable->set_return_type(STentry_Type::ste_integer);
            else
                entry->set_type(STentry_Type::ste_integer);
        }
        else if(type_expect_list[i] == "NAME (float)")
        {
            if(is_return_type)
                currentTable->set_return_type(STentry_Type::ste_float);
            else
                entry->set_type(STentry_Type::ste_float);
        }
        else if(type_expect_list[i] == "NAME (bool)")
        {
            if(is_return_type)
                currentTable->set_return_type(STentry_Type::ste_bool);
            else
                entry->set_type(STentry_Type::ste_bool);
        }
        else if(type_expect_list[i] == "NAME (str)")
        {
            if(is_return_type)
                currentTable->set_return_type(STentry_Type::ste_str);
            else
                entry->set_type(STentry_Type::ste_str);
        }
        else if (type_expect_list[i] == "KEYWORD (None)")
        {
            if(is_return_type)
                currentTable->set_return_type(STentry_Type::ste_none);
            else
                entry->set_type(STentry_Type::ste_none);
        }
        else if(find(class_names.begin(), class_names.end(), type_expect_list[i]) != class_names.end())
        {
            if(is_return_type)
            {
                currentTable->set_return_type(STentry_Type::ste_class_obj);
                currentTable->set_class_obj_name(type_expect_list[i]);
            }
            else
            {
                entry->set_type(STentry_Type::ste_class_obj);
                entry->set_class_obj_name(type_expect_list[i]);
            }
        }
        else
        {
            cout << "Line " << entry->get_lineno() << ":Type Error : Invalid type for " << entry->get_name() << endl;
            exit(1);
        }
        return;
        
    }

#line 177 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_NEWLINE = 3,                    /* NEWLINE  */
  YYSYMBOL_ENDMARKER = 4,                  /* ENDMARKER  */
  YYSYMBOL_NAME = 5,                       /* NAME  */
  YYSYMBOL_INDENT = 6,                     /* INDENT  */
  YYSYMBOL_DEDENT = 7,                     /* DEDENT  */
  YYSYMBOL_NUMBER = 8,                     /* NUMBER  */
  YYSYMBOL_STRING = 9,                     /* STRING  */
  YYSYMBOL_KEYWORD_FALSE = 10,             /* KEYWORD_FALSE  */
  YYSYMBOL_KEYWORD_NONE = 11,              /* KEYWORD_NONE  */
  YYSYMBOL_KEYWORD_TRUE = 12,              /* KEYWORD_TRUE  */
  YYSYMBOL_KEYWORD_AND = 13,               /* KEYWORD_AND  */
  YYSYMBOL_KEYWORD_ASSERT = 14,            /* KEYWORD_ASSERT  */
  YYSYMBOL_KEYWORD_BREAK = 15,             /* KEYWORD_BREAK  */
  YYSYMBOL_KEYWORD_CLASS = 16,             /* KEYWORD_CLASS  */
  YYSYMBOL_KEYWORD_CONTINUE = 17,          /* KEYWORD_CONTINUE  */
  YYSYMBOL_KEYWORD_DEF = 18,               /* KEYWORD_DEF  */
  YYSYMBOL_KEYWORD_ELIF = 19,              /* KEYWORD_ELIF  */
  YYSYMBOL_KEYWORD_ELSE = 20,              /* KEYWORD_ELSE  */
  YYSYMBOL_KEYWORD_FOR = 21,               /* KEYWORD_FOR  */
  YYSYMBOL_KEYWORD_FROM = 22,              /* KEYWORD_FROM  */
  YYSYMBOL_KEYWORD_GLOBAL = 23,            /* KEYWORD_GLOBAL  */
  YYSYMBOL_KEYWORD_IF = 24,                /* KEYWORD_IF  */
  YYSYMBOL_KEYWORD_IN = 25,                /* KEYWORD_IN  */
  YYSYMBOL_KEYWORD_NONLOCAL = 26,          /* KEYWORD_NONLOCAL  */
  YYSYMBOL_KEYWORD_NOT = 27,               /* KEYWORD_NOT  */
  YYSYMBOL_KEYWORD_OR = 28,                /* KEYWORD_OR  */
  YYSYMBOL_KEYWORD_RAISE = 29,             /* KEYWORD_RAISE  */
  YYSYMBOL_KEYWORD_RETURN = 30,            /* KEYWORD_RETURN  */
  YYSYMBOL_KEYWORD_WHILE = 31,             /* KEYWORD_WHILE  */
  YYSYMBOL_OP_POWER = 32,                  /* OP_POWER  */
  YYSYMBOL_OP_INT_DIVIDE_EQUALS = 33,      /* OP_INT_DIVIDE_EQUALS  */
  YYSYMBOL_OP_POWER_EQUALS = 34,           /* OP_POWER_EQUALS  */
  YYSYMBOL_OP_RIGHT_SHIFT_EQUALS = 35,     /* OP_RIGHT_SHIFT_EQUALS  */
  YYSYMBOL_OP_LEFT_SHIFT_EQUALS = 36,      /* OP_LEFT_SHIFT_EQUALS  */
  YYSYMBOL_OP_XOR_EQUALS = 37,             /* OP_XOR_EQUALS  */
  YYSYMBOL_OP_OR_EQUALS = 38,              /* OP_OR_EQUALS  */
  YYSYMBOL_OP_AND_EQUALS = 39,             /* OP_AND_EQUALS  */
  YYSYMBOL_OP_MOD_EQUALS = 40,             /* OP_MOD_EQUALS  */
  YYSYMBOL_OP_DIVIDE_EQUALS = 41,          /* OP_DIVIDE_EQUALS  */
  YYSYMBOL_OP_MULTIPLY_EQUALS = 42,        /* OP_MULTIPLY_EQUALS  */
  YYSYMBOL_OP_MINUS_EQUALS = 43,           /* OP_MINUS_EQUALS  */
  YYSYMBOL_OP_PLUS_EQUALS = 44,            /* OP_PLUS_EQUALS  */
  YYSYMBOL_OP_NOT_EQUALS = 45,             /* OP_NOT_EQUALS  */
  YYSYMBOL_OP_EQUALS = 46,                 /* OP_EQUALS  */
  YYSYMBOL_OP_RIGHT_SHIFT = 47,            /* OP_RIGHT_SHIFT  */
  YYSYMBOL_OP_LEFT_SHIFT = 48,             /* OP_LEFT_SHIFT  */
  YYSYMBOL_OP_INT_DIVIDE = 49,             /* OP_INT_DIVIDE  */
  YYSYMBOL_OP_GREATER_THAN_EQUALS = 50,    /* OP_GREATER_THAN_EQUALS  */
  YYSYMBOL_OP_LESS_THAN_EQUALS = 51,       /* OP_LESS_THAN_EQUALS  */
  YYSYMBOL_OP_ARROW = 52,                  /* OP_ARROW  */
  YYSYMBOL_53_ = 53,                       /* ':'  */
  YYSYMBOL_54_ = 54,                       /* ','  */
  YYSYMBOL_55_ = 55,                       /* ';'  */
  YYSYMBOL_56_ = 56,                       /* '.'  */
  YYSYMBOL_57_ = 57,                       /* '('  */
  YYSYMBOL_58_ = 58,                       /* ')'  */
  YYSYMBOL_59_ = 59,                       /* '['  */
  YYSYMBOL_60_ = 60,                       /* ']'  */
  YYSYMBOL_61_ = 61,                       /* '+'  */
  YYSYMBOL_62_ = 62,                       /* '-'  */
  YYSYMBOL_63_ = 63,                       /* '*'  */
  YYSYMBOL_64_ = 64,                       /* '/'  */
  YYSYMBOL_65_ = 65,                       /* '%'  */
  YYSYMBOL_66_ = 66,                       /* '&'  */
  YYSYMBOL_67_ = 67,                       /* '|'  */
  YYSYMBOL_68_ = 68,                       /* '^'  */
  YYSYMBOL_69_ = 69,                       /* '~'  */
  YYSYMBOL_70_ = 70,                       /* '<'  */
  YYSYMBOL_71_ = 71,                       /* '>'  */
  YYSYMBOL_72_ = 72,                       /* '='  */
  YYSYMBOL_YYACCEPT = 73,                  /* $accept  */
  YYSYMBOL_file_input = 74,                /* file_input  */
  YYSYMBOL_file_input1 = 75,               /* file_input1  */
  YYSYMBOL_file_input2 = 76,               /* file_input2  */
  YYSYMBOL_funcdef = 77,                   /* funcdef  */
  YYSYMBOL_78_1 = 78,                      /* $@1  */
  YYSYMBOL_funcdef1 = 79,                  /* funcdef1  */
  YYSYMBOL_80_2 = 80,                      /* $@2  */
  YYSYMBOL_81_3 = 81,                      /* $@3  */
  YYSYMBOL_parameters = 82,                /* parameters  */
  YYSYMBOL_parameters1 = 83,               /* parameters1  */
  YYSYMBOL_typedargslist = 84,             /* typedargslist  */
  YYSYMBOL_typedargslist1 = 85,            /* typedargslist1  */
  YYSYMBOL_typedargslist2 = 86,            /* typedargslist2  */
  YYSYMBOL_tfpdef = 87,                    /* tfpdef  */
  YYSYMBOL_tfpdef1 = 88,                   /* tfpdef1  */
  YYSYMBOL_89_4 = 89,                      /* $@4  */
  YYSYMBOL_stmt = 90,                      /* stmt  */
  YYSYMBOL_simple_stmt = 91,               /* simple_stmt  */
  YYSYMBOL_simple_stmt3 = 92,              /* simple_stmt3  */
  YYSYMBOL_simple_stmt2 = 93,              /* simple_stmt2  */
  YYSYMBOL_small_stmt = 94,                /* small_stmt  */
  YYSYMBOL_expr_stmt = 95,                 /* expr_stmt  */
  YYSYMBOL_expr_stmt1 = 96,                /* expr_stmt1  */
  YYSYMBOL_97_5 = 97,                      /* $@5  */
  YYSYMBOL_98_6 = 98,                      /* $@6  */
  YYSYMBOL_expr_stmt2 = 99,                /* expr_stmt2  */
  YYSYMBOL_expr_stmt3 = 100,               /* expr_stmt3  */
  YYSYMBOL_testlist_star_expr = 101,       /* testlist_star_expr  */
  YYSYMBOL_testlist_star_expr2 = 102,      /* testlist_star_expr2  */
  YYSYMBOL_testlist_star_expr1 = 103,      /* testlist_star_expr1  */
  YYSYMBOL_augassign = 104,                /* augassign  */
  YYSYMBOL_flow_stmt = 105,                /* flow_stmt  */
  YYSYMBOL_break_stmt = 106,               /* break_stmt  */
  YYSYMBOL_continue_stmt = 107,            /* continue_stmt  */
  YYSYMBOL_return_stmt = 108,              /* return_stmt  */
  YYSYMBOL_testlist2 = 109,                /* testlist2  */
  YYSYMBOL_raise_stmt = 110,               /* raise_stmt  */
  YYSYMBOL_raise_stmt1 = 111,              /* raise_stmt1  */
  YYSYMBOL_raise_stmt2 = 112,              /* raise_stmt2  */
  YYSYMBOL_global_stmt = 113,              /* global_stmt  */
  YYSYMBOL_global_stmt1 = 114,             /* global_stmt1  */
  YYSYMBOL_nonlocal_stmt = 115,            /* nonlocal_stmt  */
  YYSYMBOL_nonlocal_stmt1 = 116,           /* nonlocal_stmt1  */
  YYSYMBOL_assert_stmt = 117,              /* assert_stmt  */
  YYSYMBOL_assert_stmt1 = 118,             /* assert_stmt1  */
  YYSYMBOL_compound_stmt = 119,            /* compound_stmt  */
  YYSYMBOL_if_stmt = 120,                  /* if_stmt  */
  YYSYMBOL_if_stmt1 = 121,                 /* if_stmt1  */
  YYSYMBOL_if_stmt2 = 122,                 /* if_stmt2  */
  YYSYMBOL_while_stmt = 123,               /* while_stmt  */
  YYSYMBOL_while_stmt1 = 124,              /* while_stmt1  */
  YYSYMBOL_for_stmt = 125,                 /* for_stmt  */
  YYSYMBOL_for_stmt1 = 126,                /* for_stmt1  */
  YYSYMBOL_suite = 127,                    /* suite  */
  YYSYMBOL_suite1 = 128,                   /* suite1  */
  YYSYMBOL_test = 129,                     /* test  */
  YYSYMBOL_test1 = 130,                    /* test1  */
  YYSYMBOL_or_test = 131,                  /* or_test  */
  YYSYMBOL_or_test1 = 132,                 /* or_test1  */
  YYSYMBOL_and_test = 133,                 /* and_test  */
  YYSYMBOL_and_test1 = 134,                /* and_test1  */
  YYSYMBOL_not_test = 135,                 /* not_test  */
  YYSYMBOL_comparison = 136,               /* comparison  */
  YYSYMBOL_comparison1 = 137,              /* comparison1  */
  YYSYMBOL_comp_op = 138,                  /* comp_op  */
  YYSYMBOL_expr = 139,                     /* expr  */
  YYSYMBOL_expr1 = 140,                    /* expr1  */
  YYSYMBOL_xor_expr = 141,                 /* xor_expr  */
  YYSYMBOL_xor_expr1 = 142,                /* xor_expr1  */
  YYSYMBOL_and_expr = 143,                 /* and_expr  */
  YYSYMBOL_and_expr1 = 144,                /* and_expr1  */
  YYSYMBOL_shift_expr = 145,               /* shift_expr  */
  YYSYMBOL_shift_expr1 = 146,              /* shift_expr1  */
  YYSYMBOL_shift_expr2 = 147,              /* shift_expr2  */
  YYSYMBOL_arith_expr = 148,               /* arith_expr  */
  YYSYMBOL_arith_expr1 = 149,              /* arith_expr1  */
  YYSYMBOL_arith_expr2 = 150,              /* arith_expr2  */
  YYSYMBOL_term = 151,                     /* term  */
  YYSYMBOL_term1 = 152,                    /* term1  */
  YYSYMBOL_term2 = 153,                    /* term2  */
  YYSYMBOL_factor = 154,                   /* factor  */
  YYSYMBOL_factor1 = 155,                  /* factor1  */
  YYSYMBOL_power = 156,                    /* power  */
  YYSYMBOL_power1 = 157,                   /* power1  */
  YYSYMBOL_atom_expr = 158,                /* atom_expr  */
  YYSYMBOL_atom_expr1 = 159,               /* atom_expr1  */
  YYSYMBOL_atom = 160,                     /* atom  */
  YYSYMBOL_atom1 = 161,                    /* atom1  */
  YYSYMBOL_atom2 = 162,                    /* atom2  */
  YYSYMBOL_testlist_comp = 163,            /* testlist_comp  */
  YYSYMBOL_testlist_comp1 = 164,           /* testlist_comp1  */
  YYSYMBOL_testlist_comp2 = 165,           /* testlist_comp2  */
  YYSYMBOL_trailer = 166,                  /* trailer  */
  YYSYMBOL_trailer1 = 167,                 /* trailer1  */
  YYSYMBOL_subscriptlist = 168,            /* subscriptlist  */
  YYSYMBOL_subscriptlist1 = 169,           /* subscriptlist1  */
  YYSYMBOL_subscriptlist2 = 170,           /* subscriptlist2  */
  YYSYMBOL_subscript = 171,                /* subscript  */
  YYSYMBOL_subscript1 = 172,               /* subscript1  */
  YYSYMBOL_subscript2 = 173,               /* subscript2  */
  YYSYMBOL_exprlist = 174,                 /* exprlist  */
  YYSYMBOL_exprlist1 = 175,                /* exprlist1  */
  YYSYMBOL_exprlist2 = 176,                /* exprlist2  */
  YYSYMBOL_testlist = 177,                 /* testlist  */
  YYSYMBOL_testlist3 = 178,                /* testlist3  */
  YYSYMBOL_testlist1 = 179,                /* testlist1  */
  YYSYMBOL_classdef = 180,                 /* classdef  */
  YYSYMBOL_181_7 = 181,                    /* $@7  */
  YYSYMBOL_classdef1 = 182,                /* classdef1  */
  YYSYMBOL_arglist_class = 183,            /* arglist_class  */
  YYSYMBOL_arglist_class1 = 184,           /* arglist_class1  */
  YYSYMBOL_argument_class = 185,           /* argument_class  */
  YYSYMBOL_arglist = 186,                  /* arglist  */
  YYSYMBOL_arglist2 = 187,                 /* arglist2  */
  YYSYMBOL_arglist1 = 188,                 /* arglist1  */
  YYSYMBOL_argument = 189,                 /* argument  */
  YYSYMBOL_argument1 = 190                 /* argument1  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   306

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  73
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  118
/* YYNRULES -- Number of rules.  */
#define YYNRULES  222
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  298

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   307


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    65,    66,     2,
      57,    58,    63,    61,    54,    62,    56,    64,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    53,    55,
      70,    72,    71,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    59,     2,    60,    68,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    67,     2,    69,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   179,   179,   192,   193,   198,   201,   204,   204,   240,
     246,   249,   246,   264,   271,   274,   281,   300,   303,   308,
     311,   393,   424,   424,   434,   437,   440,   444,   451,   458,
     464,   467,   475,   478,   481,   484,   487,   491,   641,   645,
     641,   661,   665,   668,   671,   677,   680,   695,   701,   704,
     707,   710,   718,   723,   728,   733,   738,   743,   748,   753,
     758,   763,   768,   773,   779,   782,   785,   788,   792,   796,
     800,   808,   811,   815,   822,   825,   831,   834,   841,   850,
     853,   862,   872,   875,   884,   893,   896,   902,   905,   908,
     911,   914,   918,   929,   932,   942,   945,   954,   964,   967,
     976,   989,   992,  1002,  1005,  1015,  1018,  1024,  1029,  1032,
    1042,  1047,  1050,  1058,  1063,  1066,  1074,  1082,  1086,  1097,
    1100,  1113,  1118,  1123,  1128,  1133,  1139,  1146,  1157,  1160,
    1175,  1186,  1189,  1204,  1215,  1218,  1233,  1244,  1247,  1259,
    1264,  1271,  1283,  1286,  1299,  1304,  1310,  1321,  1324,  1336,
    1341,  1346,  1351,  1358,  1364,  1367,  1372,  1377,  1383,  1394,
    1397,  1404,  1410,  1413,  1419,  1427,  1435,  1443,  1446,  1449,
    1456,  1459,  1463,  1466,  1469,  1472,  1479,  1485,  1488,  1491,
    1494,  1502,  1508,  1516,  1524,  1530,  1533,  1540,  1543,  1547,
    1550,  1558,  1563,  1571,  1574,  1580,  1583,  1586,  1593,  1596,
    1599,  1602,  1610,  1616,  1619,  1623,  1626,  1634,  1634,  1658,
    1661,  1669,  1674,  1677,  1684,  1703,  1709,  1712,  1716,  1719,
    1727,  1753,  1756
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "NEWLINE", "ENDMARKER",
  "NAME", "INDENT", "DEDENT", "NUMBER", "STRING", "KEYWORD_FALSE",
  "KEYWORD_NONE", "KEYWORD_TRUE", "KEYWORD_AND", "KEYWORD_ASSERT",
  "KEYWORD_BREAK", "KEYWORD_CLASS", "KEYWORD_CONTINUE", "KEYWORD_DEF",
  "KEYWORD_ELIF", "KEYWORD_ELSE", "KEYWORD_FOR", "KEYWORD_FROM",
  "KEYWORD_GLOBAL", "KEYWORD_IF", "KEYWORD_IN", "KEYWORD_NONLOCAL",
  "KEYWORD_NOT", "KEYWORD_OR", "KEYWORD_RAISE", "KEYWORD_RETURN",
  "KEYWORD_WHILE", "OP_POWER", "OP_INT_DIVIDE_EQUALS", "OP_POWER_EQUALS",
  "OP_RIGHT_SHIFT_EQUALS", "OP_LEFT_SHIFT_EQUALS", "OP_XOR_EQUALS",
  "OP_OR_EQUALS", "OP_AND_EQUALS", "OP_MOD_EQUALS", "OP_DIVIDE_EQUALS",
  "OP_MULTIPLY_EQUALS", "OP_MINUS_EQUALS", "OP_PLUS_EQUALS",
  "OP_NOT_EQUALS", "OP_EQUALS", "OP_RIGHT_SHIFT", "OP_LEFT_SHIFT",
  "OP_INT_DIVIDE", "OP_GREATER_THAN_EQUALS", "OP_LESS_THAN_EQUALS",
  "OP_ARROW", "':'", "','", "';'", "'.'", "'('", "')'", "'['", "']'",
  "'+'", "'-'", "'*'", "'/'", "'%'", "'&'", "'|'", "'^'", "'~'", "'<'",
  "'>'", "'='", "$accept", "file_input", "file_input1", "file_input2",
  "funcdef", "$@1", "funcdef1", "$@2", "$@3", "parameters", "parameters1",
  "typedargslist", "typedargslist1", "typedargslist2", "tfpdef", "tfpdef1",
  "$@4", "stmt", "simple_stmt", "simple_stmt3", "simple_stmt2",
  "small_stmt", "expr_stmt", "expr_stmt1", "$@5", "$@6", "expr_stmt2",
  "expr_stmt3", "testlist_star_expr", "testlist_star_expr2",
  "testlist_star_expr1", "augassign", "flow_stmt", "break_stmt",
  "continue_stmt", "return_stmt", "testlist2", "raise_stmt", "raise_stmt1",
  "raise_stmt2", "global_stmt", "global_stmt1", "nonlocal_stmt",
  "nonlocal_stmt1", "assert_stmt", "assert_stmt1", "compound_stmt",
  "if_stmt", "if_stmt1", "if_stmt2", "while_stmt", "while_stmt1",
  "for_stmt", "for_stmt1", "suite", "suite1", "test", "test1", "or_test",
  "or_test1", "and_test", "and_test1", "not_test", "comparison",
  "comparison1", "comp_op", "expr", "expr1", "xor_expr", "xor_expr1",
  "and_expr", "and_expr1", "shift_expr", "shift_expr1", "shift_expr2",
  "arith_expr", "arith_expr1", "arith_expr2", "term", "term1", "term2",
  "factor", "factor1", "power", "power1", "atom_expr", "atom_expr1",
  "atom", "atom1", "atom2", "testlist_comp", "testlist_comp1",
  "testlist_comp2", "trailer", "trailer1", "subscriptlist",
  "subscriptlist1", "subscriptlist2", "subscript", "subscript1",
  "subscript2", "exprlist", "exprlist1", "exprlist2", "testlist",
  "testlist3", "testlist1", "classdef", "$@7", "classdef1",
  "arglist_class", "arglist_class1", "argument_class", "arglist",
  "arglist2", "arglist1", "argument", "argument1", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-206)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-217)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -206,    34,   176,  -206,  -206,  -206,    13,  -206,    39,  -206,
      45,  -206,    49,    13,    58,    13,     5,     6,    13,  -206,
    -206,  -206,  -206,  -206,  -206,    81,  -206,  -206,  -206,  -206,
    -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,    24,
    -206,  -206,  -206,  -206,  -206,    12,  -206,  -206,  -206,  -206,
      57,  -206,    32,  -206,  -206,  -206,    65,  -206,  -206,  -206,
      46,     2,  -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,
    -206,  -206,  -206,  -206,  -206,    13,  -206,  -206,    13,    79,
      13,  -206,    82,    99,    56,    13,  -206,    71,    84,    86,
      78,  -206,    13,    93,   129,    94,    13,  -206,    95,   129,
    -206,   195,  -206,    13,    85,  -206,     8,  -206,   130,    13,
      13,  -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,    13,
      98,     1,    43,   135,  -206,  -206,    97,  -206,   101,   156,
     157,  -206,  -206,   161,  -206,    18,  -206,   142,  -206,  -206,
    -206,  -206,  -206,    13,  -206,  -206,  -206,   109,  -206,   129,
     115,  -206,  -206,   111,   103,  -206,   129,  -206,  -206,  -206,
     104,  -206,   129,  -206,   275,    89,  -206,  -206,   118,  -206,
     105,  -206,  -206,   119,  -206,  -206,  -206,  -206,    13,  -206,
      13,  -206,  -206,    83,  -206,   158,  -206,   216,    13,   123,
    -206,   129,    13,  -206,    13,    13,  -206,   127,   131,  -206,
    -206,  -206,    74,    19,   132,  -206,  -206,  -206,   143,   129,
    -206,  -206,  -206,  -206,   178,  -206,  -206,  -206,  -206,  -206,
    -206,  -206,  -206,  -206,  -206,    10,    15,  -206,  -206,  -206,
      40,    19,  -206,   163,  -206,   192,   129,   129,  -206,   103,
     129,  -206,   146,  -206,   148,  -206,  -206,  -206,  -206,  -206,
    -206,    19,  -206,    35,  -206,  -206,  -206,  -206,  -206,   159,
    -206,  -206,  -206,   206,    16,     9,  -206,    -5,  -206,  -206,
    -206,   144,  -206,   168,  -206,   -13,   162,   154,  -206,  -206,
      13,  -206,  -206,   173,  -206,  -206,   -13,  -206,  -206,   174,
    -206,    25,  -206,  -206,    -4,  -206,  -206,  -206
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,   119,     1,     6,     2,   119,    68,     0,    69,
       0,   128,     0,   119,     0,   119,   119,   119,   119,     4,
      90,     5,    25,    30,    32,    45,    33,    64,    65,    66,
      67,    34,    35,    36,    26,    87,    88,    89,    50,   108,
     111,   114,   117,   128,    91,    85,   207,     7,   200,   131,
       0,    79,     0,    82,   116,    73,    76,    70,   205,    72,
       0,     0,    63,    62,    61,    60,    59,    58,    57,    56,
      55,    54,    53,    52,    38,   119,    37,    42,   119,    48,
     119,   107,   110,   113,   118,   119,    84,   209,     0,   198,
     127,   134,   119,    78,   119,    81,   119,    75,   204,   119,
      29,   119,    27,   119,    45,    41,    49,    47,     0,   119,
     119,   126,   123,   124,   125,   121,   122,   120,    86,   119,
       0,     0,     0,   128,   197,   129,   130,   137,     0,     0,
       0,   103,    93,     0,    77,   119,   202,    98,    28,    31,
      39,    46,    51,   119,   112,   115,   214,     0,   212,   119,
      24,    14,    13,     0,    17,    10,   119,     8,   201,   132,
     133,   142,   119,    80,   119,    95,    83,   206,     0,    97,
      43,   109,   210,   211,   208,    22,    21,    15,   119,    19,
     119,     9,   135,   136,   147,   101,   105,   119,   119,     0,
      92,   119,   119,    40,   119,   119,    18,    16,     0,   140,
     139,   138,   141,     0,     0,   100,   104,   106,     0,   119,
      99,    44,   213,    23,     0,    11,   144,   145,   143,   166,
     167,   174,   171,   169,   170,   119,   119,   155,   156,   157,
     146,     0,   154,   159,   162,   168,   119,   119,    96,    17,
     119,   179,     0,   173,     0,   152,   149,   150,   151,   148,
     153,     0,   158,   161,   175,   102,    94,    20,    12,   178,
     164,   165,   160,     0,   119,   119,   163,   119,   176,   183,
     185,   221,   181,     0,   218,   119,   193,     0,   189,   180,
     119,   220,   184,   217,   195,   192,   119,   191,   182,   187,
     222,   119,   215,   194,   119,   186,   219,   190
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,
    -206,  -206,   -22,  -206,    21,  -206,  -206,  -149,     0,  -206,
    -206,   128,  -206,  -206,  -206,  -206,  -206,   134,   166,  -206,
    -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,
    -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,
    -206,  -206,  -206,  -206,   -98,  -206,    -6,  -206,   164,  -206,
     139,  -206,   -12,  -206,  -206,  -206,   -39,  -206,  -206,  -206,
    -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,
    -206,  -205,  -206,  -206,  -206,  -206,  -206,  -206,    23,  -206,
    -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,   -58,  -206,
     -36,  -206,  -206,  -206,   -53,  -206,  -206,  -206,  -206,  -206,
    -206,  -206,    59,  -206,  -206,  -206,   -40,  -206
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,     2,    19,    20,    88,   157,   180,   240,   122,
     152,   153,   179,   197,   154,   176,   195,    21,   131,   102,
      61,    23,    24,    76,   103,   170,   193,    77,    25,   107,
      79,    78,    26,    27,    28,    29,    57,    30,    55,    97,
      31,    93,    32,    95,    33,    86,    34,    35,   165,   190,
      36,   169,    37,   205,   132,   187,    38,    81,    39,    82,
      40,    83,    41,    42,    43,   117,    48,    49,    90,    91,
     126,   127,   160,   161,   201,   183,   184,   218,   202,   203,
     249,   230,   231,   232,   252,   233,   253,   234,   242,   235,
     243,   268,   259,   266,   272,   277,   295,   289,   278,   287,
     285,    50,   124,    89,    59,   136,    98,    44,    87,   120,
     147,   173,   148,   273,   292,   283,   274,   281
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      45,   137,    22,    54,    84,   100,   150,    52,   -74,   -71,
      56,    58,    60,  -119,    15,   186,  -119,  -119,  -119,  -119,
    -119,  -203,    15,    15,   219,   105,   250,   220,   221,   222,
     223,   224,    15,    15,     3,    15,    15,    15,   207,   128,
      15,  -196,    15,    15,    46,    15,   262,  -196,    80,   275,
      47,   174,    15,  -177,    51,  -177,  -188,   101,   181,   151,
     -74,   -71,   275,    53,   185,  -119,    85,  -119,  -172,  -119,
    -119,  -203,    58,  -203,   270,  -172,   225,  -119,   226,   118,
     227,   228,    92,  -216,   158,    94,    58,    96,   229,   245,
     134,   263,   264,   210,   265,   155,   156,   140,   145,    99,
     142,   111,   112,   246,   247,   248,   113,   114,   188,   189,
     109,   238,   110,   146,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,   115,   116,   119,   167,
     199,   200,   130,   106,    74,   216,   217,   171,   255,   256,
     123,   121,   258,     6,     7,   125,     9,   129,   133,   135,
     143,   149,    12,    75,   162,    14,    15,    75,    16,    17,
    -199,   163,   168,   164,    22,   159,   166,   172,   175,   177,
     182,   191,   196,   194,   198,   178,   209,   192,   204,     4,
       5,   214,   208,   150,   215,   236,   211,    22,   146,   213,
       6,     7,     8,     9,    10,   251,   237,    11,   138,    12,
      13,   254,    14,    15,   260,    16,    17,    18,   261,     6,
       7,   269,     9,   267,   288,   286,   280,   257,    12,   241,
     241,    14,    15,   206,    16,    17,   282,   291,   294,   139,
       6,     7,     8,     9,    10,   239,   297,    11,   141,    12,
      13,   104,    14,    15,   108,    16,    17,    18,   144,   244,
     293,   296,     0,   212,     0,     0,     0,     0,   271,   276,
       0,   279,     0,     0,     0,     0,     0,     0,     0,   284,
       0,     0,     0,     0,   290,     0,     0,     0,     0,     0,
     284,     0,     0,     0,     0,   271,     0,     0,   276,     6,
       7,     8,     9,    10,     0,     0,    11,     0,    12,    13,
       0,    14,    15,     0,    16,    17,    18
};

static const yytype_int16 yycheck[] =
{
       6,    99,     2,    15,    43,     3,     5,    13,     3,     3,
      16,    17,    18,     5,    27,   164,     8,     9,    10,    11,
      12,     3,    27,    27,     5,    78,   231,     8,     9,    10,
      11,    12,    27,    27,     0,    27,    27,    27,   187,    92,
      27,    54,    27,    27,     5,    27,   251,    60,    24,    53,
       5,   149,    27,    58,     5,    60,    60,    55,   156,    58,
      55,    55,    53,     5,   162,    57,    54,    59,    58,    61,
      62,    53,    78,    55,    58,    60,    57,    69,    59,    85,
      61,    62,    25,    58,   123,    53,    92,    22,    69,    49,
      96,    56,    57,   191,    59,    52,    53,   103,   110,    53,
     106,    45,    46,    63,    64,    65,    50,    51,    19,    20,
      28,   209,    13,   119,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    70,    71,    57,   135,
      47,    48,     3,    54,    53,    61,    62,   143,   236,   237,
      54,    57,   240,    14,    15,    67,    17,    54,    54,    54,
      20,    53,    23,    72,    53,    26,    27,    72,    29,    30,
      25,     5,    20,     6,   164,    68,     5,    58,    53,    58,
      66,    53,   178,    54,   180,    72,    53,    72,    20,     3,
       4,    54,   188,     5,    53,    53,   192,   187,   194,   195,
      14,    15,    16,    17,    18,    32,    53,    21,     3,    23,
      24,     9,    26,    27,    58,    29,    30,    31,    60,    14,
      15,     5,    17,    54,    60,    53,    72,   239,    23,   225,
     226,    26,    27,     7,    29,    30,    58,    54,    54,   101,
      14,    15,    16,    17,    18,   214,   294,    21,   104,    23,
      24,    75,    26,    27,    80,    29,    30,    31,   109,   226,
     286,   291,    -1,   194,    -1,    -1,    -1,    -1,   264,   265,
      -1,   267,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   275,
      -1,    -1,    -1,    -1,   280,    -1,    -1,    -1,    -1,    -1,
     286,    -1,    -1,    -1,    -1,   291,    -1,    -1,   294,    14,
      15,    16,    17,    18,    -1,    -1,    21,    -1,    23,    24,
      -1,    26,    27,    -1,    29,    30,    31
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    74,    75,     0,     3,     4,    14,    15,    16,    17,
      18,    21,    23,    24,    26,    27,    29,    30,    31,    76,
      77,    90,    91,    94,    95,   101,   105,   106,   107,   108,
     110,   113,   115,   117,   119,   120,   123,   125,   129,   131,
     133,   135,   136,   137,   180,   129,     5,     5,   139,   140,
     174,     5,   129,     5,   135,   111,   129,   109,   129,   177,
     129,    93,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    53,    72,    96,   100,   104,   103,
      24,   130,   132,   134,   139,    54,   118,   181,    78,   176,
     141,   142,    25,   114,    53,   116,    22,   112,   179,    53,
       3,    55,    92,    97,   101,   177,    54,   102,   131,    28,
      13,    45,    46,    50,    51,    70,    71,   138,   129,    57,
     182,    57,    82,    54,   175,    67,   143,   144,   177,    54,
       3,    91,   127,    54,   129,    54,   178,   127,     3,    94,
     129,   100,   129,    20,   133,   135,   129,   183,   185,    53,
       5,    58,    83,    84,    87,    52,    53,    79,   139,    68,
     145,   146,    53,     5,     6,   121,     5,   129,    20,   124,
      98,   129,    58,   184,   127,    53,    88,    58,    72,    85,
      80,   127,    66,   148,   149,   127,    90,   128,    19,    20,
     122,    53,    72,    99,    54,    89,   129,    86,   129,    47,
      48,   147,   151,   152,    20,   126,     7,    90,   129,    53,
     127,   129,   185,   129,    54,    53,    61,    62,   150,     5,
       8,     9,    10,    11,    12,    57,    59,    61,    62,    69,
     154,   155,   156,   158,   160,   162,    53,    53,   127,    87,
      81,   129,   161,   163,   161,    49,    63,    64,    65,   153,
     154,    32,   157,   159,     9,   127,   127,    85,   127,   165,
      58,    60,   154,    56,    57,    59,   166,    54,   164,     5,
      58,   129,   167,   186,   189,    53,   129,   168,   171,   129,
      72,   190,    58,   188,   129,   173,    53,   172,    60,   170,
     129,    54,   187,   173,    54,   169,   189,   171
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    73,    74,    75,    75,    76,    76,    78,    77,    79,
      80,    81,    79,    82,    83,    83,    84,    85,    85,    86,
      86,    87,    89,    88,    88,    90,    90,    91,    92,    92,
      93,    93,    94,    94,    94,    94,    94,    95,    97,    98,
      96,    96,    96,    99,    99,   100,   100,   101,   102,   102,
     103,   103,   104,   104,   104,   104,   104,   104,   104,   104,
     104,   104,   104,   104,   105,   105,   105,   105,   106,   107,
     108,   109,   109,   110,   111,   111,   112,   112,   113,   114,
     114,   115,   116,   116,   117,   118,   118,   119,   119,   119,
     119,   119,   120,   121,   121,   122,   122,   123,   124,   124,
     125,   126,   126,   127,   127,   128,   128,   129,   130,   130,
     131,   132,   132,   133,   134,   134,   135,   135,   136,   137,
     137,   138,   138,   138,   138,   138,   138,   139,   140,   140,
     141,   142,   142,   143,   144,   144,   145,   146,   146,   147,
     147,   148,   149,   149,   150,   150,   151,   152,   152,   153,
     153,   153,   153,   154,   154,   155,   155,   155,   156,   157,
     157,   158,   159,   159,   160,   160,   160,   160,   160,   160,
     160,   160,   161,   161,   162,   162,   163,   164,   164,   165,
     165,   166,   166,   166,   167,   167,   168,   169,   169,   170,
     170,   171,   171,   172,   172,   173,   173,   174,   175,   175,
     176,   176,   177,   178,   178,   179,   179,   181,   180,   182,
     182,   183,   184,   184,   185,   186,   187,   187,   188,   188,
     189,   190,   190
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     0,     2,     1,     1,     0,     5,     2,
       0,     0,     6,     2,     1,     2,     3,     0,     2,     0,
       4,     2,     0,     3,     0,     1,     1,     3,     2,     1,
       0,     3,     1,     1,     1,     1,     1,     2,     0,     0,
       5,     2,     1,     0,     2,     0,     3,     3,     0,     1,
       0,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     0,     1,     2,     0,     2,     0,     2,     3,     0,
       3,     3,     0,     3,     3,     0,     2,     1,     1,     1,
       1,     1,     6,     0,     5,     0,     3,     5,     0,     3,
       7,     0,     3,     1,     4,     1,     2,     2,     0,     4,
       2,     0,     3,     2,     0,     3,     2,     1,     2,     0,
       3,     1,     1,     1,     1,     1,     1,     2,     0,     3,
       2,     0,     3,     2,     0,     3,     2,     0,     3,     1,
       1,     2,     0,     3,     1,     1,     2,     0,     3,     1,
       1,     1,     1,     2,     1,     1,     1,     1,     2,     0,
       2,     2,     0,     2,     3,     3,     1,     1,     1,     1,
       1,     1,     0,     1,     1,     2,     3,     1,     0,     0,
       3,     2,     3,     2,     2,     1,     3,     0,     1,     0,
       3,     2,     2,     0,     2,     1,     0,     3,     0,     1,
       0,     3,     3,     1,     0,     0,     3,     0,     6,     0,
       3,     2,     0,     3,     1,     3,     1,     0,     0,     3,
       2,     0,     2
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* file_input: file_input1 ENDMARKER  */
#line 179 "parser.y"
                                   {
                                    TreeNode* node2 = new TreeNode((yyvsp[0].str));
                                    (yyval.ptr) = new TreeNode("file_input");
                                    (yyval.ptr)->addChild((yyvsp[-1].ptr));
                                    (yyval.ptr)->addChild(node2);
                                    if (verbose){
                                    printf("parsing done successfully\n");
                                    }
                                    root = (yyval.ptr);
                                    // globalTable->print_table();
                                    // cout << "--table printed--" << endl;
                                    return 0;
                                    }
#line 1629 "parser.tab.c"
    break;

  case 3: /* file_input1: %empty  */
#line 192 "parser.y"
              {(yyval.ptr) = nullptr;}
#line 1635 "parser.tab.c"
    break;

  case 4: /* file_input1: file_input1 file_input2  */
#line 193 "parser.y"
                                      {
                                        (yyval.ptr) = new TreeNode("file_input1");
                                        (yyval.ptr)->addChild((yyvsp[-1].ptr));
                                        (yyval.ptr)->addChild((yyvsp[0].ptr));
                                    }
#line 1645 "parser.tab.c"
    break;

  case 5: /* file_input2: stmt  */
#line 198 "parser.y"
                   {
                    (yyval.ptr) = (yyvsp[0].ptr);
                    }
#line 1653 "parser.tab.c"
    break;

  case 6: /* file_input2: NEWLINE  */
#line 201 "parser.y"
                      {
                    (yyval.ptr) = new TreeNode((yyvsp[0].str));
             }
#line 1661 "parser.tab.c"
    break;

  case 7: /* $@1: %empty  */
#line 204 "parser.y"
                           {
                /*we have to check if the name of the function already exists then error */
                 if (currentTable->lookup(string((yyvsp[0].str)))!=NULL){
                   cout <<"Line "<< yylineno << ":Name Error : Re-definition of name " << string((yyvsp[0].str)) << " is not allowed. Previous defined at line "<< currentTable->lookup(string((yyvsp[0].str)))->get_lineno() << endl;
                   exit(1);
                 }
                 SymbolTable* newTable = new SymbolTable(ST_Type::st_function, yylineno, currentTable, STentry_Type::ste_none, string((yyvsp[0].str)));            
                 STentry* entry = new STentry((yyvsp[0].str), STentry_Type::ste_func_def, yylineno, (void*)newTable);   
                 currentTable->insert(string((yyvsp[0].str)), entry);
                 currentTable = newTable;
                 currentTable-> set_param(true);
}
#line 1678 "parser.tab.c"
    break;

  case 8: /* funcdef: KEYWORD_DEF NAME $@1 parameters funcdef1  */
#line 216 "parser.y"
                    {
                        TreeNode* node1 = new TreeNode((yyvsp[-4].str));
                        TreeNode* node2 = new TreeNode((yyvsp[-3].str));
                        (yyval.ptr) = new TreeNode("funcdef");
                        (yyval.ptr)->setlineno(yylineno);
                        (yyval.ptr)->addChild(node1);
                        (yyval.ptr)->addChild(node2);
                        (yyval.ptr)->addChild((yyvsp[-1].ptr));
                        (yyval.ptr)->addChild((yyvsp[0].ptr));
                        /*we have to end the scope of the function here as the function has ended*/
                        string function_name = "";
                        //if it is a method of a class then we also have to add the class_name in the begiining of the function name
                        if (currentTable->get_parent()->get_type() == ST_Type :: st_class ){
                            function_name += clean_string(currentTable->get_parent()->get_name());
                            function_name += "_";
                        }
                         function_name = function_name + node2->original_value;
                        for(auto it : currentTable->get_params()){
                            //appending the function names.
                            function_name = function_name + "_" + type_to_string(it->get_type());
                        }
                        currentTable->set_function_name(function_name);
                        currentTable = currentTable->get_parent();
                    }
#line 1707 "parser.tab.c"
    break;

  case 9: /* funcdef1: ':' suite  */
#line 240 "parser.y"
                     {
                        TreeNode* node1 = new TreeNode((yyvsp[-1].str));
                        (yyval.ptr) = new TreeNode("funcdef1");
                        (yyval.ptr)->addChild(node1);
                        (yyval.ptr)->addChild((yyvsp[0].ptr));
                    }
#line 1718 "parser.tab.c"
    break;

  case 10: /* $@2: %empty  */
#line 246 "parser.y"
                   {
            type_expect = true;
        }
#line 1726 "parser.tab.c"
    break;

  case 11: /* $@3: %empty  */
#line 249 "parser.y"
                 {
            type_expect = false;
            find_type(NULL, true);
            type_expect_list.clear();
        }
#line 1736 "parser.tab.c"
    break;

  case 12: /* funcdef1: OP_ARROW $@2 test ':' $@3 suite  */
#line 253 "parser.y"
                {
                            TreeNode* node1 = new TreeNode((yyvsp[-5].str));
                            TreeNode* node4 = new TreeNode((yyvsp[-2].str));
                            (yyval.ptr) = new TreeNode("funcdef1");
                            (yyval.ptr)->addChild(node1);
                            (yyval.ptr)->addChild((yyvsp[-3].ptr));
                            (yyval.ptr)->addChild(node4);
                            (yyval.ptr)->addChild((yyvsp[0].ptr));
                        }
#line 1750 "parser.tab.c"
    break;

  case 13: /* parameters: '(' parameters1  */
#line 264 "parser.y"
                             {
                                TreeNode* node1 = new TreeNode((yyvsp[-1].str));
                                (yyval.ptr) = new TreeNode("parameters");
                                (yyval.ptr)->addChild(node1);
                                (yyval.ptr)->addChild((yyvsp[0].ptr));
                            
        }
#line 1762 "parser.tab.c"
    break;

  case 14: /* parameters1: ')'  */
#line 271 "parser.y"
                  {
                    (yyval.ptr) =  new TreeNode((yyvsp[0].str));
                }
#line 1770 "parser.tab.c"
    break;

  case 15: /* parameters1: typedargslist ')'  */
#line 274 "parser.y"
                                {
                                TreeNode* node1 = new TreeNode((yyvsp[0].str));
                                (yyval.ptr) = new TreeNode("parameters1");
                                (yyval.ptr)->addChild((yyvsp[-1].ptr));
                                 (yyval.ptr)->addChild(node1);
                }
#line 1781 "parser.tab.c"
    break;

  case 16: /* typedargslist: tfpdef typedargslist1 typedargslist2  */
#line 281 "parser.y"
                                                       {
                                                                        (yyval.ptr) = new TreeNode("typedargslist");
                                                                        (yyval.ptr)->addChild((yyvsp[-2].ptr));
                                                                        (yyval.ptr)->addChild((yyvsp[-1].ptr));
                                                                        (yyval.ptr)->addChild((yyvsp[0].ptr));
                                                                    }
#line 1792 "parser.tab.c"
    break;

  case 17: /* typedargslist1: %empty  */
#line 300 "parser.y"
                                {   
                                    (yyval.ptr) =nullptr;
                                }
#line 1800 "parser.tab.c"
    break;

  case 18: /* typedargslist1: '=' test  */
#line 303 "parser.y"
                               {
                                    TreeNode* node1 = new TreeNode((yyvsp[-1].str));
                                    (yyval.ptr) = new TreeNode("typedargslist1");
                                    (yyval.ptr)->addChild(node1);
                                }
#line 1810 "parser.tab.c"
    break;

  case 19: /* typedargslist2: %empty  */
#line 308 "parser.y"
                                {    
                                    (yyval.ptr) = nullptr;
                                }
#line 1818 "parser.tab.c"
    break;

  case 20: /* typedargslist2: typedargslist2 ',' tfpdef typedargslist1  */
#line 311 "parser.y"
                                                            {
                                                                TreeNode* node2 = new TreeNode((yyvsp[-2].str));
                                                                (yyval.ptr) = new TreeNode("typedargslist2");
                                                                (yyval.ptr)->addChild((yyvsp[-3].ptr));
                                                                (yyval.ptr)->addChild(node2);
                                                                (yyval.ptr)->addChild((yyvsp[-1].ptr));
                                                                (yyval.ptr)->addChild((yyvsp[0].ptr));
                                                            }
#line 1831 "parser.tab.c"
    break;

  case 21: /* tfpdef: NAME tfpdef1  */
#line 393 "parser.y"
                       {
                            TreeNode* node1 = new TreeNode((yyvsp[-1].str));
                            (yyval.ptr) = new TreeNode("tfpdef");
                            (yyval.ptr)->addChild(node1);
                            (yyval.ptr)->addChild((yyvsp[0].ptr));
                            /*this tfpdef is a parameter of the function so we have to add it to the symbol table and params*/
                            if (currentTable->lookup(string((yyvsp[-1].str)))!=NULL){
                                cout <<"Line "<< yylineno << ":Name Error : Re-definition of name" << string((yyvsp[-1].str)) << " is not allowed. Previous defined at line "<< currentTable->lookup(string((yyvsp[-1].str)))->get_lineno() << endl;
                                exit(1);
                            }
                            STentry* entry = new STentry(string((yyvsp[-1].str)), STentry_Type::ste_none, yylineno, NULL);
                            currentTable->insert(string((yyvsp[-1].str)), entry);
                            if ((yyvsp[0].ptr) == nullptr){
                                /*implies we dont have a type for the parameter which is error if the parameter is not self*/\
                                if (string((yyvsp[-1].str)) != "NAME (self)"){
                                    printf("Line %d:Type Error : No type for the parameter %s \n",entry->get_lineno(), (yyvsp[-1].str));
                                    exit(1);
                                }
                                else {
                                    /*implies we have a type for the parameter to be handled for now let it be*/

                                }
                            }
                            else {
                                /*implies we have a type for the parameter*/
                                find_type(entry, false);
                                type_expect_list.clear();
                                currentTable->push_param(entry);
                                
                            }
                        }
#line 1867 "parser.tab.c"
    break;

  case 22: /* $@4: %empty  */
#line 424 "parser.y"
             {
        type_expect = true;
}
#line 1875 "parser.tab.c"
    break;

  case 23: /* tfpdef1: ':' $@4 test  */
#line 427 "parser.y"
     {
                        TreeNode* node1 = new TreeNode((yyvsp[-2].str));
                        (yyval.ptr) = new TreeNode("tfpdef1");
                        (yyval.ptr)->addChild(node1);
                        (yyval.ptr)->addChild((yyvsp[0].ptr));
                        type_expect = false;
                    }
#line 1887 "parser.tab.c"
    break;

  case 24: /* tfpdef1: %empty  */
#line 434 "parser.y"
              {
                     (yyval.ptr) = nullptr;
            }
#line 1895 "parser.tab.c"
    break;

  case 25: /* stmt: simple_stmt  */
#line 437 "parser.y"
                      {
                            (yyval.ptr) = (yyvsp[0].ptr);
                        }
#line 1903 "parser.tab.c"
    break;

  case 26: /* stmt: compound_stmt  */
#line 440 "parser.y"
                        {
                            (yyval.ptr) = (yyvsp[0].ptr);
                        }
#line 1911 "parser.tab.c"
    break;

  case 27: /* simple_stmt: small_stmt simple_stmt2 simple_stmt3  */
#line 444 "parser.y"
                                                   {
                                                        (yyval.ptr) = new TreeNode("simple_stmt");
                                                        (yyval.ptr)->addChild((yyvsp[-2].ptr));
                                                        (yyval.ptr)->addChild((yyvsp[-1].ptr));
                                                        (yyval.ptr)->addChild((yyvsp[0].ptr));
                                                    
            }
#line 1923 "parser.tab.c"
    break;

  case 28: /* simple_stmt3: ';' NEWLINE  */
#line 451 "parser.y"
                           {
                           TreeNode* node1 = new TreeNode((yyvsp[-1].str));
                            TreeNode* node2 = new TreeNode((yyvsp[0].str));
                            (yyval.ptr) = new TreeNode("simple_stmt3");
                            (yyval.ptr)->addChild(node1);
                            (yyval.ptr)->addChild(node2); 
                }
#line 1935 "parser.tab.c"
    break;

  case 29: /* simple_stmt3: NEWLINE  */
#line 458 "parser.y"
                          {
                            TreeNode* node1 = new TreeNode((yyvsp[0].str));
                            (yyval.ptr) = new TreeNode("simple_stmt3");
                            (yyval.ptr)->addChild(node1);
                        
                }
#line 1946 "parser.tab.c"
    break;

  case 30: /* simple_stmt2: %empty  */
#line 464 "parser.y"
                    {
                        (yyval.ptr) = nullptr;
                    }
#line 1954 "parser.tab.c"
    break;

  case 31: /* simple_stmt2: simple_stmt2 ';' small_stmt  */
#line 467 "parser.y"
                                            {
                                                TreeNode* node2 = new TreeNode((yyvsp[-1].str));
                                                (yyval.ptr) = new TreeNode("simple_stmt2");
                                                (yyval.ptr)->addChild((yyvsp[-2].ptr));
                                                (yyval.ptr)->addChild(node2);
                                                (yyval.ptr)->addChild((yyvsp[0].ptr));
                                            }
#line 1966 "parser.tab.c"
    break;

  case 32: /* small_stmt: expr_stmt  */
#line 475 "parser.y"
                        {
                            (yyval.ptr) = (yyvsp[0].ptr);
                        }
#line 1974 "parser.tab.c"
    break;

  case 33: /* small_stmt: flow_stmt  */
#line 478 "parser.y"
                          {
                            (yyval.ptr) = (yyvsp[0].ptr);
                        }
#line 1982 "parser.tab.c"
    break;

  case 34: /* small_stmt: global_stmt  */
#line 481 "parser.y"
                           {
                                (yyval.ptr) = (yyvsp[0].ptr);
                            }
#line 1990 "parser.tab.c"
    break;

  case 35: /* small_stmt: nonlocal_stmt  */
#line 484 "parser.y"
                             {
                                (yyval.ptr) = (yyvsp[0].ptr);
                            }
#line 1998 "parser.tab.c"
    break;

  case 36: /* small_stmt: assert_stmt  */
#line 487 "parser.y"
                            {
                                (yyval.ptr) = (yyvsp[0].ptr);
                            }
#line 2006 "parser.tab.c"
    break;

  case 37: /* expr_stmt: testlist_star_expr expr_stmt1  */
#line 491 "parser.y"
                                          {
                            if ((yyvsp[0].ptr) == nullptr){
                                (yyval.ptr) = (yyvsp[-1].ptr);
                            }
                            else if ((yyvsp[0].ptr)->children[0]->value == "DELIMITER (:)"){
                                (yyval.ptr) = (yyvsp[0].ptr);
                                (yyval.ptr)->children[0]->addChildFront((yyvsp[-1].ptr));
                                // cout << "ha mai colon!!" <<endl;
                                /*we have to first get the name of the variable*/
                                TreeNode* temp = (yyvsp[-1].ptr);
                                // string name = getFirstTerminalValue(temp);
                                vector<TreeNode*> values;
                                getAllTerminalValue(temp, values);
                                for (auto it : values){
                                    cout << it->value << endl;
                                }
                                string name = values[0]->value;
                                //if name is self then values[2] will have the attribute name
                                if (name == "NAME (self)"){
                                    //this is an attribute of the class
                                    string attr_name = values[2]->value;
                                    //whenever we are in a class our specification says we are definitely inside a method so we have to add the attribute to the symbol table of the class not the function
                                    SymbolTable* classTable;
                                    if (currentTable->get_type() == ST_Type::st_function){
                                        //we are in a function so we have to go to the parent of the function to get the class symbol table
                                        classTable = currentTable->get_parent();
                                    }
                                    else {
                                        classTable = currentTable;
                                    }
                                    if (classTable->lookup(attr_name) != NULL){
                                        cout <<"Line "<< yylineno << ":Name Error : Re-definition of name " << attr_name << " is not allowed. Previous defined at line "<< classTable->lookup(attr_name)->get_lineno() << endl;
                                        exit(1);
                                    }
                                    STentry* entry = new STentry(attr_name, STentry_Type::ste_none, yylineno, NULL);
                                    classTable->insert(attr_name, entry);
                                    find_type(entry, false);
                                    entry->set_offset(classTable->get_offset());
                                    if (entry->get_is_list()== true){
                                        vector<TreeNode*> values1;
                                        getAllTerminalValue((yyvsp[0].ptr)->children[1], values1);
                                        int size = (values1.size() - 2)/2+1;
                                        entry->set_width(size*size_of_type(entry));
                                        classTable->set_offset(classTable->get_offset() + entry->get_width());
                                        classTable->set_size(classTable->get_size()+ entry->get_width());
                                        values1.clear();
                                    }
                                    else {
                                        classTable->set_offset(classTable->get_offset() + size_of_type(entry));
                                        classTable->set_size(classTable->get_size()+ size_of_type(entry));
                                    }
                                    
                                    type_expect_list.clear();
                                }
                                else {
                                    if(currentTable->lookup(name) != NULL){
                                        cout <<"Line "<< yylineno << ":Name Error : Re-definition of name " << name << " is not allowed. Previous defined at line "<< currentTable->lookup(name)->get_lineno() << endl; 
                                        exit(1);
                                    }
                                    STentry* entry = new STentry(name, STentry_Type::ste_none, yylineno, NULL);
                                    currentTable->insert(name, entry);
                                    // cout << name << endl;
                                    // for(int i=0; i<type_expect_list.size(); i++){
                                    //     cout << type_expect_list[i] << endl;
                                    // }
                                    find_type(entry, false);
                                    entry->set_offset(currentTable->get_offset());
                                    if (entry->get_is_list()== true){
                                        vector<TreeNode*> values1;
                                        getAllTerminalValue((yyvsp[0].ptr)->children[1], values1);
                                        int size = (values1.size() - 2)/2+1;
                                        entry->set_width(size*size_of_type(entry));
                                        currentTable->set_offset(currentTable->get_offset() + entry->get_width());
                                        values1.clear();
                                    }
                                    else {
                                        currentTable->set_offset(currentTable->get_offset() + size_of_type(entry));
                                    }
                                    type_expect_list.clear();
                                    }
                                    values.clear();
                                }
                            else {
                                    (yyval.ptr) = (yyvsp[0].ptr);
                                    (yyval.ptr)->addChildFront((yyvsp[-1].ptr));
                                    if ((yyval.ptr)->value == "DELIMITER (:)") {
                                        TreeNode* temp = (yyvsp[-1].ptr);
                                        // string name = getFirstTerminalValue(temp);
                                        vector<TreeNode*> values;
                                        getAllTerminalValue(temp, values);
                                        string name = values[0]->value;
                                        if (name == "NAME (self)"){
                                            //this is an attribute of the class
                                            string attr_name = values[2]->value;
                                            //whenever we are in a class our specification says we are definitely inside a method so we have to add the attribute to the symbol table of the class not the function
                                            SymbolTable* classTable;
                                            if (currentTable->get_type() == ST_Type::st_function){
                                                //we are in a function so we have to go to the parent of the function to get the class symbol table
                                                classTable = currentTable->get_parent();
                                            }
                                            else {
                                                classTable = currentTable;
                                            }
                                            if (classTable->lookup(attr_name) != NULL){
                                                cout <<"Line "<< yylineno << ":Name Error : Re-definition of name " << attr_name << " is not allowed. Previous defined at line "<< classTable->lookup(attr_name)->get_lineno() << endl;
                                                exit(1);
                                            }
                                            STentry* entry = new STentry(attr_name, STentry_Type::ste_none, yylineno, NULL);
                                            classTable->insert(attr_name, entry);
                                            find_type(entry, false);
                                            entry->set_offset(classTable->get_offset());
                                            if (entry->get_is_list()== true){
                                                //error case as list will always be statically defined and initialised
                                                cout << "Line " << yylineno << ":Type Error : List cannot be defined in this way" << endl;
                                                exit(1);
                                            }
                                            else {
                                                classTable->set_offset(classTable->get_offset() + size_of_type(entry));
                                                classTable->set_size(classTable->get_size()+ size_of_type(entry));
                                            }
                                            type_expect_list.clear();
                                        }
                                        else {
                                            if(currentTable->lookup(name) != NULL){
                                                cout <<"Line "<< yylineno << ":Name Error : Re-definition of name " << name << " is not allowed. Previous defined at line "<< currentTable->lookup(name)->get_lineno() << endl;
                                                exit(1);
                                            }
                                            STentry* entry = new STentry(name, STentry_Type::ste_none, yylineno, NULL);
                                            currentTable->insert(name, entry);
                                            // cout << name << endl;
                                            // for(int i=0; i<type_expect_list.size(); i++){
                                            //     cout << type_expect_list[i] << endl;
                                            // }
                                            find_type(entry, false);
                                            entry->set_offset(currentTable->get_offset());
                                            if (entry->get_is_list()== true){
                                                //error case as list will always be statically defined and initialised
                                                cout << "Line " << yylineno << ":Type Error : List cannot be defined in this way" << endl;
                                                exit(1);
                                            }
                                            else {
                                                currentTable->set_offset(currentTable->get_offset() + size_of_type(entry));
                                            }
                                            type_expect_list.clear();
                                            }
                                        values.clear();
                                }
                            }
                            
                        }
#line 2161 "parser.tab.c"
    break;

  case 38: /* $@5: %empty  */
#line 641 "parser.y"
                 {
                /*here we are expecting a type as a name*/
                type_expect = true;
        }
#line 2170 "parser.tab.c"
    break;

  case 39: /* $@6: %empty  */
#line 645 "parser.y"
             {
        /* this test is the type of the variable */
        type_expect = false;
        }
#line 2179 "parser.tab.c"
    break;

  case 40: /* expr_stmt1: ':' $@5 test $@6 expr_stmt2  */
#line 649 "parser.y"
                   {
                            if ((yyvsp[0].ptr) == nullptr){
                                (yyval.ptr) = new TreeNode((yyvsp[-4].str));
                                (yyval.ptr)->addChild((yyvsp[-2].ptr));
                            }
                            else {
                                TreeNode* node1 = new TreeNode((yyvsp[-4].str));
                                node1->addChild((yyvsp[-2].ptr));
                                (yyval.ptr) = (yyvsp[0].ptr);
                                (yyvsp[0].ptr)->addChildFront(node1);
                            }
                    }
#line 2196 "parser.tab.c"
    break;

  case 41: /* expr_stmt1: augassign testlist  */
#line 661 "parser.y"
                             {
                                (yyval.ptr)=(yyvsp[-1].ptr);
                                (yyval.ptr)->addChild((yyvsp[0].ptr));
                            }
#line 2205 "parser.tab.c"
    break;

  case 42: /* expr_stmt1: expr_stmt3  */
#line 665 "parser.y"
                    {
                        (yyval.ptr) = (yyvsp[0].ptr);
                    }
#line 2213 "parser.tab.c"
    break;

  case 43: /* expr_stmt2: %empty  */
#line 668 "parser.y"
             {
                (yyval.ptr) = nullptr;
            }
#line 2221 "parser.tab.c"
    break;

  case 44: /* expr_stmt2: '=' test  */
#line 671 "parser.y"
                       {
                    (yyval.ptr) = new TreeNode((yyvsp[-1].str));
                    (yyval.ptr)->setlineno(yylineno);
                    (yyval.ptr)->setType("assign");
                    (yyval.ptr)->addChild((yyvsp[0].ptr));
                     }
#line 2232 "parser.tab.c"
    break;

  case 45: /* expr_stmt3: %empty  */
#line 677 "parser.y"
                  {
                    (yyval.ptr) = nullptr;
                }
#line 2240 "parser.tab.c"
    break;

  case 46: /* expr_stmt3: '=' testlist_star_expr expr_stmt3  */
#line 680 "parser.y"
                                                 {
                                                    (yyval.ptr) = new TreeNode((yyvsp[-2].str));
                                                    (yyval.ptr)->setlineno(yylineno);  
                                                    (yyval.ptr)->setType("assign");
                                                    if((yyvsp[0].ptr) != nullptr)
                                                    {
                                                        (yyvsp[0].ptr)->addChildFront((yyvsp[-1].ptr));
                                                        (yyval.ptr)->addChild((yyvsp[0].ptr));
                                                    }
                                                    else
                                                    {
                                                        (yyval.ptr)->addChild((yyvsp[-1].ptr));
                                                    }
                                                }
#line 2259 "parser.tab.c"
    break;

  case 47: /* testlist_star_expr: test testlist_star_expr1 testlist_star_expr2  */
#line 695 "parser.y"
                                                                  {
                                                                    (yyval.ptr) = new TreeNode("testlist_star_expr");
                                                                    (yyval.ptr)->addChild((yyvsp[-2].ptr));
                                                                    (yyval.ptr)->addChild((yyvsp[-1].ptr));
                                                                    (yyval.ptr)->addChild((yyvsp[0].ptr));                                         
                    }
#line 2270 "parser.tab.c"
    break;

  case 48: /* testlist_star_expr2: %empty  */
#line 701 "parser.y"
                      {
                        (yyval.ptr) = nullptr;
                    }
#line 2278 "parser.tab.c"
    break;

  case 49: /* testlist_star_expr2: ','  */
#line 704 "parser.y"
                          {
                            (yyval.ptr) = new TreeNode((yyvsp[0].str));
                    }
#line 2286 "parser.tab.c"
    break;

  case 50: /* testlist_star_expr1: %empty  */
#line 707 "parser.y"
                           {
                            (yyval.ptr) = nullptr;
                        }
#line 2294 "parser.tab.c"
    break;

  case 51: /* testlist_star_expr1: testlist_star_expr1 ',' test  */
#line 710 "parser.y"
                                                     {
                                                        TreeNode* node2 = new TreeNode((yyvsp[-1].str));
                                                        (yyval.ptr) = new TreeNode("testlist_star_expr1");
                                                        (yyval.ptr)->addChild((yyvsp[-2].ptr));
                                                        (yyval.ptr)->addChild(node2);
                                                        (yyval.ptr)->addChild((yyvsp[0].ptr));
                                                    }
#line 2306 "parser.tab.c"
    break;

  case 52: /* augassign: OP_PLUS_EQUALS  */
#line 718 "parser.y"
                              {
                                (yyval.ptr) = new TreeNode((yyvsp[0].str));
                                (yyval.ptr)->setlineno(yylineno);
                                (yyval.ptr)->setType("augassign");
                            }
#line 2316 "parser.tab.c"
    break;

  case 53: /* augassign: OP_MINUS_EQUALS  */
#line 723 "parser.y"
                               {
                                    (yyval.ptr) = new TreeNode((yyvsp[0].str));
                                    (yyval.ptr)->setlineno(yylineno);  
                                    (yyval.ptr)->setType("augassign");
                                }
#line 2326 "parser.tab.c"
    break;

  case 54: /* augassign: OP_MULTIPLY_EQUALS  */
#line 728 "parser.y"
                                  {
                                       (yyval.ptr) = new TreeNode((yyvsp[0].str));
                                       (yyval.ptr)->setlineno(yylineno);  
                                       (yyval.ptr)->setType("augassign");
                                    }
#line 2336 "parser.tab.c"
    break;

  case 55: /* augassign: OP_DIVIDE_EQUALS  */
#line 733 "parser.y"
                                 {
                                    (yyval.ptr) = new TreeNode((yyvsp[0].str));
                                    (yyval.ptr)->setlineno(yylineno);  
                                    (yyval.ptr)->setType("augassign");
                                }
#line 2346 "parser.tab.c"
    break;

  case 56: /* augassign: OP_MOD_EQUALS  */
#line 738 "parser.y"
                               {
                                    (yyval.ptr) = new TreeNode((yyvsp[0].str));
                                    (yyval.ptr)->setlineno(yylineno);  
                                    (yyval.ptr)->setType("augassign");
                                }
#line 2356 "parser.tab.c"
    break;

  case 57: /* augassign: OP_AND_EQUALS  */
#line 743 "parser.y"
                                 {
                                    (yyval.ptr) = new TreeNode((yyvsp[0].str));
                                    (yyval.ptr)->setlineno(yylineno);  
                                    (yyval.ptr)->setType("augassign");
                                }
#line 2366 "parser.tab.c"
    break;

  case 58: /* augassign: OP_OR_EQUALS  */
#line 748 "parser.y"
                              {
                                   (yyval.ptr) = new TreeNode((yyvsp[0].str));
                                   (yyval.ptr)->setlineno(yylineno);  
                                   (yyval.ptr)->setType("augassign");
                                }
#line 2376 "parser.tab.c"
    break;

  case 59: /* augassign: OP_XOR_EQUALS  */
#line 753 "parser.y"
                              {
                                   (yyval.ptr) = new TreeNode((yyvsp[0].str));
                                   (yyval.ptr)->setlineno(yylineno);  
                                   (yyval.ptr)->setType("augassign");
                                }
#line 2386 "parser.tab.c"
    break;

  case 60: /* augassign: OP_LEFT_SHIFT_EQUALS  */
#line 758 "parser.y"
                                    {
                                       (yyval.ptr) = new TreeNode((yyvsp[0].str));
                                       (yyval.ptr)->setlineno(yylineno);  
                                       (yyval.ptr)->setType("augassign");
                                    }
#line 2396 "parser.tab.c"
    break;

  case 61: /* augassign: OP_RIGHT_SHIFT_EQUALS  */
#line 763 "parser.y"
                                     {
                                      (yyval.ptr) = new TreeNode((yyvsp[0].str));
                                      (yyval.ptr)->setlineno(yylineno);  
                                      (yyval.ptr)->setType("augassign");
                                    }
#line 2406 "parser.tab.c"
    break;

  case 62: /* augassign: OP_POWER_EQUALS  */
#line 768 "parser.y"
                                {
                                    (yyval.ptr) = new TreeNode((yyvsp[0].str));
                                    (yyval.ptr)->setlineno(yylineno);  
                                    (yyval.ptr)->setType("augassign");
                                }
#line 2416 "parser.tab.c"
    break;

  case 63: /* augassign: OP_INT_DIVIDE_EQUALS  */
#line 773 "parser.y"
                                     {
                                      (yyval.ptr) = new TreeNode((yyvsp[0].str));
                                      (yyval.ptr)->setlineno(yylineno);  
                                      (yyval.ptr)->setType("augassign");
                                    }
#line 2426 "parser.tab.c"
    break;

  case 64: /* flow_stmt: break_stmt  */
#line 779 "parser.y"
                          {
                            (yyval.ptr) = (yyvsp[0].ptr);
                        }
#line 2434 "parser.tab.c"
    break;

  case 65: /* flow_stmt: continue_stmt  */
#line 782 "parser.y"
                          {
                               (yyval.ptr) = (yyvsp[0].ptr);
                            }
#line 2442 "parser.tab.c"
    break;

  case 66: /* flow_stmt: return_stmt  */
#line 785 "parser.y"
                         {
                               (yyval.ptr) = (yyvsp[0].ptr);
                            }
#line 2450 "parser.tab.c"
    break;

  case 67: /* flow_stmt: raise_stmt  */
#line 788 "parser.y"
                         {
                                 (yyval.ptr) = (yyvsp[0].ptr);
                            }
#line 2458 "parser.tab.c"
    break;

  case 68: /* break_stmt: KEYWORD_BREAK  */
#line 792 "parser.y"
                              {
                                 (yyval.ptr) = new TreeNode((yyvsp[0].str));
                            }
#line 2466 "parser.tab.c"
    break;

  case 69: /* continue_stmt: KEYWORD_CONTINUE  */
#line 796 "parser.y"
                                    {
                                        (yyval.ptr) = new TreeNode((yyvsp[0].str));
                                    }
#line 2474 "parser.tab.c"
    break;

  case 70: /* return_stmt: KEYWORD_RETURN testlist2  */
#line 800 "parser.y"
                                       {
                                            TreeNode* node1 = new TreeNode((yyvsp[-1].str));
                                            (yyval.ptr) = new TreeNode("return_stmt");
                                            (yyval.ptr)->setlineno(yylineno);
                                            (yyval.ptr)->addChild(node1);
                                            (yyval.ptr)->addChild((yyvsp[0].ptr));

            }
#line 2487 "parser.tab.c"
    break;

  case 71: /* testlist2: %empty  */
#line 808 "parser.y"
           {
                (yyval.ptr) = nullptr;
            }
#line 2495 "parser.tab.c"
    break;

  case 72: /* testlist2: testlist  */
#line 811 "parser.y"
                   {
                        (yyval.ptr) = (yyvsp[0].ptr);
        }
#line 2503 "parser.tab.c"
    break;

  case 73: /* raise_stmt: KEYWORD_RAISE raise_stmt1  */
#line 815 "parser.y"
                                       {
                                            TreeNode* node1 = new TreeNode((yyvsp[-1].str));
                                            (yyval.ptr) = new TreeNode("raise_stmt");
                                            (yyval.ptr)->addChild(node1);
                                            (yyval.ptr)->addChild((yyvsp[0].ptr));
                                        
            }
#line 2515 "parser.tab.c"
    break;

  case 74: /* raise_stmt1: %empty  */
#line 822 "parser.y"
              {
                (yyval.ptr) = nullptr;
            }
#line 2523 "parser.tab.c"
    break;

  case 75: /* raise_stmt1: test raise_stmt2  */
#line 825 "parser.y"
                               {
                                    (yyval.ptr) = new TreeNode("raise_stmt1");
                                    (yyval.ptr)->addChild((yyvsp[-1].ptr));
                                    (yyval.ptr)->addChild((yyvsp[0].ptr));
                                }
#line 2533 "parser.tab.c"
    break;

  case 76: /* raise_stmt2: %empty  */
#line 831 "parser.y"
              {
                (yyval.ptr) = nullptr;
            }
#line 2541 "parser.tab.c"
    break;

  case 77: /* raise_stmt2: KEYWORD_FROM test  */
#line 834 "parser.y"
                                {
                                    TreeNode* node1 = new TreeNode((yyvsp[-1].str));
                                    (yyval.ptr) = new TreeNode("raise_stmt2");
                                    (yyval.ptr)->addChild(node1);
                                    (yyval.ptr)->addChild((yyvsp[0].ptr));
                                
        }
#line 2553 "parser.tab.c"
    break;

  case 78: /* global_stmt: KEYWORD_GLOBAL NAME global_stmt1  */
#line 842 "parser.y"
                                                {  
                                                    TreeNode* node1 = new TreeNode((yyvsp[-2].str));
                                                    TreeNode* node2 = new TreeNode((yyvsp[-1].str));
                                                    (yyval.ptr) = new TreeNode("global_stmt");
                                                    (yyval.ptr)->addChild(node1);
                                                    (yyval.ptr)->addChild(node2);
                                                    (yyval.ptr)->addChild((yyvsp[0].ptr));
                                                }
#line 2566 "parser.tab.c"
    break;

  case 79: /* global_stmt1: %empty  */
#line 850 "parser.y"
                                      {
                                        (yyval.ptr) = nullptr;
                                        }
#line 2574 "parser.tab.c"
    break;

  case 80: /* global_stmt1: global_stmt1 ',' NAME  */
#line 853 "parser.y"
                                       {
                                            TreeNode* node2 = new TreeNode((yyvsp[-1].str));
                                            TreeNode* node3 = new TreeNode((yyvsp[0].str));
                                            (yyval.ptr) = new TreeNode("global_stmt1");
                                            (yyval.ptr)->addChild((yyvsp[-2].ptr));
                                            (yyval.ptr)->addChild(node2);
                                            (yyval.ptr)->addChild(node3);
                                        }
#line 2587 "parser.tab.c"
    break;

  case 81: /* nonlocal_stmt: KEYWORD_NONLOCAL NAME nonlocal_stmt1  */
#line 863 "parser.y"
                                                {  
                                                    TreeNode* node1 = new TreeNode((yyvsp[-2].str));
                                                    TreeNode* node2 = new TreeNode((yyvsp[-1].str));
                                                    (yyval.ptr) = new TreeNode("nonlocal_stmt");
                                                    (yyval.ptr)->addChild(node1);
                                                    (yyval.ptr)->addChild(node2);
                                                    (yyval.ptr)->addChild((yyvsp[0].ptr));

                                                }
#line 2601 "parser.tab.c"
    break;

  case 82: /* nonlocal_stmt1: %empty  */
#line 872 "parser.y"
                                               {
                                                    (yyval.ptr) = nullptr;
                                                }
#line 2609 "parser.tab.c"
    break;

  case 83: /* nonlocal_stmt1: nonlocal_stmt1 ',' NAME  */
#line 875 "parser.y"
                                                {
                                                    TreeNode* node2 = new TreeNode((yyvsp[-1].str));
                                                    TreeNode* node3 = new TreeNode((yyvsp[0].str));
                                                    (yyval.ptr) = new TreeNode("nonlocal_stmt1");
                                                    (yyval.ptr)->addChild((yyvsp[-2].ptr));
                                                    (yyval.ptr)->addChild(node2);
                                                    (yyval.ptr)->addChild(node3);
                                                    }
#line 2622 "parser.tab.c"
    break;

  case 84: /* assert_stmt: KEYWORD_ASSERT test assert_stmt1  */
#line 884 "parser.y"
                                               {
                                            TreeNode* node1 = new TreeNode((yyvsp[-2].str));
                                            (yyval.ptr) = new TreeNode("assert_stmt");
                                            (yyval.ptr)->addChild(node1);
                                            (yyval.ptr)->addChild((yyvsp[-1].ptr));
                                            (yyval.ptr)->addChild((yyvsp[0].ptr));
                                        
            }
#line 2635 "parser.tab.c"
    break;

  case 85: /* assert_stmt1: %empty  */
#line 893 "parser.y"
               {
                    (yyval.ptr) = nullptr;
                }
#line 2643 "parser.tab.c"
    break;

  case 86: /* assert_stmt1: ',' test  */
#line 896 "parser.y"
                       {
                            TreeNode* node1 = new TreeNode((yyvsp[-1].str));
                            (yyval.ptr) = new TreeNode("assert_stmt1");
                            (yyval.ptr)->addChild(node1);
                            (yyval.ptr)->addChild((yyvsp[0].ptr));
                        }
#line 2654 "parser.tab.c"
    break;

  case 87: /* compound_stmt: if_stmt  */
#line 902 "parser.y"
                           {
                            (yyval.ptr) = (yyvsp[0].ptr);
                        }
#line 2662 "parser.tab.c"
    break;

  case 88: /* compound_stmt: while_stmt  */
#line 905 "parser.y"
                          {
                            (yyval.ptr) = (yyvsp[0].ptr);
                            }
#line 2670 "parser.tab.c"
    break;

  case 89: /* compound_stmt: for_stmt  */
#line 908 "parser.y"
                            {
                                (yyval.ptr) = (yyvsp[0].ptr);
                            }
#line 2678 "parser.tab.c"
    break;

  case 90: /* compound_stmt: funcdef  */
#line 911 "parser.y"
                          {
                                (yyval.ptr) = (yyvsp[0].ptr);
                            }
#line 2686 "parser.tab.c"
    break;

  case 91: /* compound_stmt: classdef  */
#line 914 "parser.y"
                            {
                                (yyval.ptr) = (yyvsp[0].ptr);
                            }
#line 2694 "parser.tab.c"
    break;

  case 92: /* if_stmt: KEYWORD_IF test ':' suite if_stmt1 if_stmt2  */
#line 918 "parser.y"
                                                       {
                                                            TreeNode* node1 = new TreeNode((yyvsp[-5].str));
                                                            TreeNode* node3 = new TreeNode((yyvsp[-3].str));
                                                            (yyval.ptr) = new TreeNode("if_stmt");
                                                            (yyval.ptr)->addChild(node1);
                                                            (yyval.ptr)->addChild((yyvsp[-4].ptr));
                                                            (yyval.ptr)->addChild(node3);
                                                            (yyval.ptr)->addChild((yyvsp[-2].ptr));
                                                            (yyval.ptr)->addChild((yyvsp[-1].ptr));
                                                            (yyval.ptr)->addChild((yyvsp[0].ptr));
                                                        }
#line 2710 "parser.tab.c"
    break;

  case 93: /* if_stmt1: %empty  */
#line 929 "parser.y"
               {
                    (yyval.ptr) = nullptr;
                }
#line 2718 "parser.tab.c"
    break;

  case 94: /* if_stmt1: if_stmt1 KEYWORD_ELIF test ':' suite  */
#line 932 "parser.y"
                                                  {
                                                    TreeNode* node2 = new TreeNode((yyvsp[-3].str));
                                                    TreeNode* node4 = new TreeNode((yyvsp[-1].str));
                                                    (yyval.ptr) = new TreeNode("if_stmt1");
                                                    (yyval.ptr)->addChild((yyvsp[-4].ptr));
                                                    (yyval.ptr)->addChild(node2);
                                                    (yyval.ptr)->addChild((yyvsp[-2].ptr));
                                                    (yyval.ptr)->addChild(node4);
                                                    (yyval.ptr)->addChild((yyvsp[0].ptr));
                                                }
#line 2733 "parser.tab.c"
    break;

  case 95: /* if_stmt2: %empty  */
#line 942 "parser.y"
                   {
                        (yyval.ptr) = nullptr;
                    }
#line 2741 "parser.tab.c"
    break;

  case 96: /* if_stmt2: KEYWORD_ELSE ':' suite  */
#line 945 "parser.y"
                                   {
                                        TreeNode* node1 = new TreeNode((yyvsp[-2].str));
                                        TreeNode* node2 = new TreeNode((yyvsp[-1].str));
                                        (yyval.ptr) = new TreeNode("if_stmt2");
                                        (yyval.ptr)->addChild(node1);
                                        (yyval.ptr)->addChild(node2);
                                        (yyval.ptr)->addChild((yyvsp[0].ptr));
                                    }
#line 2754 "parser.tab.c"
    break;

  case 97: /* while_stmt: KEYWORD_WHILE test ':' suite while_stmt1  */
#line 954 "parser.y"
                                                       {
                                                            TreeNode* node1 = new TreeNode((yyvsp[-4].str));
                                                            TreeNode* node3 = new TreeNode((yyvsp[-2].str));
                                                            (yyval.ptr) = new TreeNode("while_stmt");
                                                            (yyval.ptr)->addChild(node1);
                                                            (yyval.ptr)->addChild((yyvsp[-3].ptr));
                                                            (yyval.ptr)->addChild(node3);
                                                            (yyval.ptr)->addChild((yyvsp[-1].ptr));
                                                            (yyval.ptr)->addChild((yyvsp[0].ptr));
                                                    }
#line 2769 "parser.tab.c"
    break;

  case 98: /* while_stmt1: %empty  */
#line 964 "parser.y"
                    {
                        (yyval.ptr) = nullptr;
                    }
#line 2777 "parser.tab.c"
    break;

  case 99: /* while_stmt1: KEYWORD_ELSE ':' suite  */
#line 967 "parser.y"
                                       {
                                            TreeNode* node1 = new TreeNode((yyvsp[-2].str));
                                            TreeNode* node2 = new TreeNode((yyvsp[-1].str));
                                            (yyval.ptr) = new TreeNode("while_stmt1");
                                            (yyval.ptr)->addChild(node1);
                                            (yyval.ptr)->addChild(node2);
                                            (yyval.ptr)->addChild((yyvsp[0].ptr));
                                        }
#line 2790 "parser.tab.c"
    break;

  case 100: /* for_stmt: KEYWORD_FOR exprlist KEYWORD_IN testlist ':' suite for_stmt1  */
#line 976 "parser.y"
                                                                          {
                                                                            TreeNode* node1 = new TreeNode((yyvsp[-6].str));
                                                                            TreeNode* node3 = new TreeNode((yyvsp[-4].str));
                                                                            TreeNode* node5 = new TreeNode((yyvsp[-2].str));
                                                                            (yyval.ptr) = new TreeNode("for_stmt");
                                                                            (yyval.ptr)->addChild(node1);
                                                                            (yyval.ptr)->addChild((yyvsp[-5].ptr));
                                                                            (yyval.ptr)->addChild(node3);
                                                                            (yyval.ptr)->addChild((yyvsp[-3].ptr));
                                                                            (yyval.ptr)->addChild(node5);
                                                                            (yyval.ptr)->addChild((yyvsp[-1].ptr));
                                                                            (yyval.ptr)->addChild((yyvsp[0].ptr));
                                                                        }
#line 2808 "parser.tab.c"
    break;

  case 101: /* for_stmt1: %empty  */
#line 989 "parser.y"
              {
                    (yyval.ptr) = nullptr;
                }
#line 2816 "parser.tab.c"
    break;

  case 102: /* for_stmt1: KEYWORD_ELSE ':' suite  */
#line 992 "parser.y"
                                   {
                                        TreeNode* node1 = new TreeNode((yyvsp[-2].str));
                                        TreeNode* node2 = new TreeNode((yyvsp[-1].str));
                                        (yyval.ptr) = new TreeNode("for_stmt1");
                                        (yyval.ptr)->addChild(node1);
                                        (yyval.ptr)->addChild(node2);
                                        (yyval.ptr)->addChild((yyvsp[0].ptr));
                                    }
#line 2829 "parser.tab.c"
    break;

  case 103: /* suite: simple_stmt  */
#line 1002 "parser.y"
                    {
                        (yyval.ptr) = (yyvsp[0].ptr);
                    }
#line 2837 "parser.tab.c"
    break;

  case 104: /* suite: NEWLINE INDENT suite1 DEDENT  */
#line 1005 "parser.y"
                                     {
                                        TreeNode* node1 = new TreeNode((yyvsp[-3].str));
                                        TreeNode* node2 = new TreeNode((yyvsp[-2].str));
                                        TreeNode* node4 = new TreeNode((yyvsp[0].str));
                                        (yyval.ptr) = new TreeNode("suite");
                                        (yyval.ptr)->addChild(node1);
                                        (yyval.ptr)->addChild(node2);
                                        (yyval.ptr)->addChild((yyvsp[-1].ptr));
                                        (yyval.ptr)->addChild(node4);
                                    }
#line 2852 "parser.tab.c"
    break;

  case 105: /* suite1: stmt  */
#line 1015 "parser.y"
                 {
                    (yyval.ptr) = (yyvsp[0].ptr);
                }
#line 2860 "parser.tab.c"
    break;

  case 106: /* suite1: suite1 stmt  */
#line 1018 "parser.y"
                        {
                            (yyval.ptr) = new TreeNode("suite1");
                            (yyval.ptr)->addChild((yyvsp[-1].ptr));
                            (yyval.ptr)->addChild((yyvsp[0].ptr));
                        }
#line 2870 "parser.tab.c"
    break;

  case 107: /* test: or_test test1  */
#line 1024 "parser.y"
                      {
                        (yyval.ptr) = new TreeNode("test");
                        (yyval.ptr)->addChild((yyvsp[-1].ptr));
                        (yyval.ptr)->addChild((yyvsp[0].ptr));
                    }
#line 2880 "parser.tab.c"
    break;

  case 108: /* test1: %empty  */
#line 1029 "parser.y"
         {  
            (yyval.ptr) = nullptr;
            }
#line 2888 "parser.tab.c"
    break;

  case 109: /* test1: KEYWORD_IF or_test KEYWORD_ELSE test  */
#line 1032 "parser.y"
                                             {
                                                TreeNode* node1 = new TreeNode((yyvsp[-3].str));
                                                TreeNode* node3 = new TreeNode((yyvsp[-1].str));
                                                (yyval.ptr) = new TreeNode("test1");
                                                (yyval.ptr)->addChild(node1);
                                                (yyval.ptr)->addChild((yyvsp[-2].ptr));
                                                (yyval.ptr)->addChild(node3);
                                                (yyval.ptr)->addChild((yyvsp[0].ptr));
                                                }
#line 2902 "parser.tab.c"
    break;

  case 110: /* or_test: and_test or_test1  */
#line 1042 "parser.y"
                              {
                                (yyval.ptr) = new TreeNode("or_test");
                                (yyval.ptr)->addChild((yyvsp[-1].ptr));
                                (yyval.ptr)->addChild((yyvsp[0].ptr));
                            }
#line 2912 "parser.tab.c"
    break;

  case 111: /* or_test1: %empty  */
#line 1047 "parser.y"
             {
                (yyval.ptr) = nullptr;
            }
#line 2920 "parser.tab.c"
    break;

  case 112: /* or_test1: or_test1 KEYWORD_OR and_test  */
#line 1050 "parser.y"
                                        {
                                            TreeNode* node2 = new TreeNode((yyvsp[-1].str));
                                            (yyval.ptr) = new TreeNode("or_test1");
                                            (yyval.ptr)->addChild((yyvsp[-2].ptr));
                                            (yyval.ptr)->addChild(node2);
                                            (yyval.ptr)->addChild((yyvsp[0].ptr));
                                        }
#line 2932 "parser.tab.c"
    break;

  case 113: /* and_test: not_test and_test1  */
#line 1058 "parser.y"
                             {
                                (yyval.ptr) = new TreeNode("and_test");
                                (yyval.ptr)->addChild((yyvsp[-1].ptr));
                                (yyval.ptr)->addChild((yyvsp[0].ptr));                            
                            }
#line 2942 "parser.tab.c"
    break;

  case 114: /* and_test1: %empty  */
#line 1063 "parser.y"
           {
                (yyval.ptr) = nullptr;    
            }
#line 2950 "parser.tab.c"
    break;

  case 115: /* and_test1: and_test1 KEYWORD_AND not_test  */
#line 1066 "parser.y"
                                         {
                                            TreeNode* node2 = new TreeNode((yyvsp[-1].str));
                                            (yyval.ptr) = new TreeNode("and_test1");
                                            (yyval.ptr)->addChild((yyvsp[-2].ptr));
                                            (yyval.ptr)->addChild(node2);
                                            (yyval.ptr)->addChild((yyvsp[0].ptr));
                                        }
#line 2962 "parser.tab.c"
    break;

  case 116: /* not_test: KEYWORD_NOT not_test  */
#line 1074 "parser.y"
                               { 
                                    TreeNode* node1 = new TreeNode((yyvsp[-1].str));
                                    // $$->setlineno(yylineno);
                                    (yyval.ptr) = new TreeNode("not_test");
                                    (yyval.ptr)->setlineno(yylineno);
                                    (yyval.ptr)->addChild(node1);
                                    (yyval.ptr)->addChild((yyvsp[0].ptr));
                                }
#line 2975 "parser.tab.c"
    break;

  case 117: /* not_test: comparison  */
#line 1082 "parser.y"
                        {
                            (yyval.ptr) = (yyvsp[0].ptr);
                        }
#line 2983 "parser.tab.c"
    break;

  case 118: /* comparison: comparison1 expr  */
#line 1086 "parser.y"
                             {
                                if((yyvsp[-1].ptr) != nullptr)
                                {
                                    (yyval.ptr) = (yyvsp[-1].ptr);
                                    (yyval.ptr)->addChild((yyvsp[0].ptr));
                                }
                                else
                                {
                                    (yyval.ptr) = (yyvsp[0].ptr);
                                }
                            }
#line 2999 "parser.tab.c"
    break;

  case 119: /* comparison1: %empty  */
#line 1097 "parser.y"
             {
                (yyval.ptr) = nullptr;
            }
#line 3007 "parser.tab.c"
    break;

  case 120: /* comparison1: comparison1 expr comp_op  */
#line 1100 "parser.y"
                                       {
                                        (yyval.ptr) = (yyvsp[0].ptr);
                                        if((yyvsp[-2].ptr) != nullptr)
                                        {
                                            (yyval.ptr)->addChild((yyvsp[-2].ptr));
                                            (yyvsp[-2].ptr)->addChild((yyvsp[-1].ptr));
                                        }
                                        else
                                        {
                                            (yyval.ptr)->addChild((yyvsp[-1].ptr));
                                        }
                                    }
#line 3024 "parser.tab.c"
    break;

  case 121: /* comp_op: '<'  */
#line 1113 "parser.y"
              {
                (yyval.ptr) = new TreeNode((yyvsp[0].str));
                (yyval.ptr)->setlineno(yylineno);  
                (yyval.ptr)->setType("relop");
            }
#line 3034 "parser.tab.c"
    break;

  case 122: /* comp_op: '>'  */
#line 1118 "parser.y"
             {
                (yyval.ptr) = new TreeNode((yyvsp[0].str));
                (yyval.ptr)->setlineno(yylineno);  
                (yyval.ptr)->setType("relop");
            }
#line 3044 "parser.tab.c"
    break;

  case 123: /* comp_op: OP_EQUALS  */
#line 1123 "parser.y"
                    {
                        (yyval.ptr) = new TreeNode((yyvsp[0].str));
                        (yyval.ptr)->setlineno(yylineno);  
                        (yyval.ptr)->setType("relop");
                    }
#line 3054 "parser.tab.c"
    break;

  case 124: /* comp_op: OP_GREATER_THAN_EQUALS  */
#line 1128 "parser.y"
                                 {
                                    (yyval.ptr) = new TreeNode((yyvsp[0].str));
                                    (yyval.ptr)->setlineno(yylineno);  
                                    (yyval.ptr)->setType("relop");
                                }
#line 3064 "parser.tab.c"
    break;

  case 125: /* comp_op: OP_LESS_THAN_EQUALS  */
#line 1133 "parser.y"
                              {
                                    (yyval.ptr) = new TreeNode((yyvsp[0].str));
                                    (yyval.ptr)->setlineno(yylineno);  
                                    (yyval.ptr)->setType("relop");

                                }
#line 3075 "parser.tab.c"
    break;

  case 126: /* comp_op: OP_NOT_EQUALS  */
#line 1139 "parser.y"
                        {
                            (yyval.ptr) = new TreeNode((yyvsp[0].str));
                            (yyval.ptr)->setlineno(yylineno);  
                             (yyval.ptr)->setType("relop");

                        }
#line 3086 "parser.tab.c"
    break;

  case 127: /* expr: expr1 xor_expr  */
#line 1146 "parser.y"
                      {
                        if((yyvsp[-1].ptr) != nullptr)
                        {
                            (yyval.ptr) = (yyvsp[-1].ptr);
                            (yyval.ptr)->addChild((yyvsp[0].ptr));
                        }
                        else
                        {
                            (yyval.ptr) = (yyvsp[0].ptr);
                        }
                    }
#line 3102 "parser.tab.c"
    break;

  case 128: /* expr1: %empty  */
#line 1157 "parser.y"
        {
            (yyval.ptr) = nullptr;
        }
#line 3110 "parser.tab.c"
    break;

  case 129: /* expr1: expr1 xor_expr '|'  */
#line 1160 "parser.y"
                             {
                                (yyval.ptr) = new TreeNode((yyvsp[0].str));
                                (yyval.ptr)->setlineno(yylineno);  
                                (yyval.ptr)->setType("binary_op");
                                if((yyvsp[-2].ptr) != nullptr)
                                {
                                    (yyval.ptr)->addChild((yyvsp[-2].ptr));
                                    (yyvsp[-2].ptr)->addChild((yyvsp[-1].ptr));
                                }
                                else
                                {
                                    (yyval.ptr)->addChild((yyvsp[-1].ptr));
                                }
                            }
#line 3129 "parser.tab.c"
    break;

  case 130: /* xor_expr: xor_expr1 and_expr  */
#line 1175 "parser.y"
                              {
                                if((yyvsp[-1].ptr) != nullptr)
                                {
                                    (yyval.ptr) = (yyvsp[-1].ptr);
                                    (yyval.ptr)->addChild((yyvsp[0].ptr));
                                }
                                else
                                {
                                    (yyval.ptr) = (yyvsp[0].ptr);
                                }
                            }
#line 3145 "parser.tab.c"
    break;

  case 131: /* xor_expr1: %empty  */
#line 1186 "parser.y"
            {
                (yyval.ptr) = nullptr;
            }
#line 3153 "parser.tab.c"
    break;

  case 132: /* xor_expr1: xor_expr1 and_expr '^'  */
#line 1189 "parser.y"
                                    {
                                        (yyval.ptr) = new TreeNode((yyvsp[0].str));
                                        (yyval.ptr)->setlineno(yylineno);  
                                        (yyval.ptr)->setType("binary_op");
                                        if((yyvsp[-2].ptr) != nullptr)
                                        {
                                            (yyval.ptr)->addChild((yyvsp[-2].ptr));
                                            (yyvsp[-2].ptr)->addChild((yyvsp[-1].ptr));
                                        }
                                        else
                                        {
                                            (yyval.ptr)->addChild((yyvsp[-1].ptr));
                                        }
                                    }
#line 3172 "parser.tab.c"
    break;

  case 133: /* and_expr: and_expr1 shift_expr  */
#line 1204 "parser.y"
                               {
                                    if((yyvsp[-1].ptr) != nullptr)
                                    {
                                        (yyval.ptr) = (yyvsp[-1].ptr);
                                        (yyval.ptr)->addChild((yyvsp[0].ptr));
                                    }
                                    else
                                    {
                                        (yyval.ptr) = (yyvsp[0].ptr);
                                    }
                                }
#line 3188 "parser.tab.c"
    break;

  case 134: /* and_expr1: %empty  */
#line 1215 "parser.y"
           {
                (yyval.ptr) = nullptr;
            }
#line 3196 "parser.tab.c"
    break;

  case 135: /* and_expr1: and_expr1 shift_expr '&'  */
#line 1218 "parser.y"
                                       {
                                        (yyval.ptr) = new TreeNode((yyvsp[0].str));
                                        (yyval.ptr)->setlineno(yylineno);  
                                        (yyval.ptr)->setType("binary_op");
                                        if((yyvsp[-2].ptr) != nullptr)
                                        {
                                            (yyval.ptr)->addChild((yyvsp[-2].ptr));
                                            (yyvsp[-2].ptr)->addChild((yyvsp[-1].ptr));
                                        }
                                        else
                                        {
                                            (yyval.ptr)->addChild((yyvsp[-1].ptr));
                                        }
                                    }
#line 3215 "parser.tab.c"
    break;

  case 136: /* shift_expr: shift_expr1 arith_expr  */
#line 1233 "parser.y"
                                    {
                                        if((yyvsp[-1].ptr) != nullptr)
                                        {
                                            (yyval.ptr) = (yyvsp[-1].ptr);
                                            (yyval.ptr)->addChild((yyvsp[0].ptr));
                                        }
                                        else
                                        {
                                            (yyval.ptr) = (yyvsp[0].ptr);
                                        }
                                    }
#line 3231 "parser.tab.c"
    break;

  case 137: /* shift_expr1: %empty  */
#line 1244 "parser.y"
              {
                (yyval.ptr) = nullptr;
            }
#line 3239 "parser.tab.c"
    break;

  case 138: /* shift_expr1: shift_expr1 arith_expr shift_expr2  */
#line 1247 "parser.y"
                                                {
                                                    (yyval.ptr) = (yyvsp[0].ptr);
                                                    if((yyvsp[-2].ptr) != nullptr)
                                                    {
                                                        (yyval.ptr)->addChild((yyvsp[-2].ptr));
                                                        (yyvsp[-2].ptr)->addChild((yyvsp[-1].ptr));
                                                    }
                                                    else
                                                    {
                                                        (yyval.ptr)->addChild((yyvsp[-1].ptr));
                                                    }
                                                }
#line 3256 "parser.tab.c"
    break;

  case 139: /* shift_expr2: OP_LEFT_SHIFT  */
#line 1259 "parser.y"
                           {
                                (yyval.ptr) = new TreeNode((yyvsp[0].str));
                                (yyval.ptr)->setlineno(yylineno);  
                                (yyval.ptr)->setType("binary_op");
                            }
#line 3266 "parser.tab.c"
    break;

  case 140: /* shift_expr2: OP_RIGHT_SHIFT  */
#line 1264 "parser.y"
                             {
                                (yyval.ptr) = new TreeNode((yyvsp[0].str));
                                (yyval.ptr)->setlineno(yylineno);  
                                (yyval.ptr)->setType("binary_op");
                            }
#line 3276 "parser.tab.c"
    break;

  case 141: /* arith_expr: arith_expr1 term  */
#line 1271 "parser.y"
                             {
                                if((yyvsp[-1].ptr) != nullptr)
                                {
                                    (yyval.ptr) = (yyvsp[-1].ptr);
                                    (yyval.ptr)->addChild((yyvsp[0].ptr));
                                }
                                else
                                {
                                    (yyval.ptr) = (yyvsp[0].ptr);
                                }
                                
                            }
#line 3293 "parser.tab.c"
    break;

  case 142: /* arith_expr1: %empty  */
#line 1283 "parser.y"
             {
                (yyval.ptr) = nullptr;
            }
#line 3301 "parser.tab.c"
    break;

  case 143: /* arith_expr1: arith_expr1 term arith_expr2  */
#line 1286 "parser.y"
                                           {

                                            (yyval.ptr) = (yyvsp[0].ptr);
                                            if((yyvsp[-2].ptr) != nullptr)
                                            {
                                                (yyval.ptr)->addChild((yyvsp[-2].ptr));
                                                (yyvsp[-2].ptr)->addChild((yyvsp[-1].ptr));
                                            }
                                            else
                                            {
                                                (yyval.ptr)->addChild((yyvsp[-1].ptr));
                                            }
                                        }
#line 3319 "parser.tab.c"
    break;

  case 144: /* arith_expr2: '+'  */
#line 1299 "parser.y"
                 {
                    (yyval.ptr) = new TreeNode((yyvsp[0].str));
                    (yyval.ptr)->setlineno(yylineno);
                    (yyval.ptr)->setType("binary_op");
                }
#line 3329 "parser.tab.c"
    break;

  case 145: /* arith_expr2: '-'  */
#line 1304 "parser.y"
                 {
                    (yyval.ptr) = new TreeNode((yyvsp[0].str));
                    (yyval.ptr)->setlineno(yylineno);
                    (yyval.ptr)->setType("binary_op");
                }
#line 3339 "parser.tab.c"
    break;

  case 146: /* term: term1 factor  */
#line 1310 "parser.y"
                   {
                        if((yyvsp[-1].ptr) != nullptr)
                        {
                            (yyval.ptr) = (yyvsp[-1].ptr);
                            (yyval.ptr)->addChild((yyvsp[0].ptr));
                        }
                        else
                        {
                            (yyval.ptr) = (yyvsp[0].ptr);
                        }
                    }
#line 3355 "parser.tab.c"
    break;

  case 147: /* term1: %empty  */
#line 1321 "parser.y"
        {
            (yyval.ptr) = nullptr;
        }
#line 3363 "parser.tab.c"
    break;

  case 148: /* term1: term1 factor term2  */
#line 1324 "parser.y"
                             {
                                (yyval.ptr) = (yyvsp[0].ptr);
                                if((yyvsp[-2].ptr) != nullptr)
                                {
                                    (yyval.ptr)->addChild((yyvsp[-2].ptr));
                                    (yyvsp[-2].ptr)->addChild((yyvsp[-1].ptr));
                                }
                                else
                                {
                                    (yyval.ptr)->addChild((yyvsp[-1].ptr));
                                }
                            }
#line 3380 "parser.tab.c"
    break;

  case 149: /* term2: '*'  */
#line 1336 "parser.y"
          { 
            (yyval.ptr) = new TreeNode((yyvsp[0].str));
            (yyval.ptr)->setlineno(yylineno);            
            (yyval.ptr)->setType("binary_op");
        }
#line 3390 "parser.tab.c"
    break;

  case 150: /* term2: '/'  */
#line 1341 "parser.y"
            {
            (yyval.ptr) = new TreeNode((yyvsp[0].str));
            (yyval.ptr)->setlineno(yylineno);  
            (yyval.ptr)->setType("binary_op");
        }
#line 3400 "parser.tab.c"
    break;

  case 151: /* term2: '%'  */
#line 1346 "parser.y"
            { 
            (yyval.ptr) = new TreeNode((yyvsp[0].str));
            (yyval.ptr)->setlineno(yylineno);  
            (yyval.ptr)->setType("binary_op");
        }
#line 3410 "parser.tab.c"
    break;

  case 152: /* term2: OP_INT_DIVIDE  */
#line 1351 "parser.y"
                       {
            (yyval.ptr) = new TreeNode((yyvsp[0].str));
            (yyval.ptr)->setlineno(yylineno);  
            (yyval.ptr)->setType("binary_op");
        }
#line 3420 "parser.tab.c"
    break;

  case 153: /* factor: factor1 factor  */
#line 1358 "parser.y"
                       {
                        (yyval.ptr) = new TreeNode("factor");
                        (yyval.ptr)->setlineno(yylineno);
                        (yyval.ptr)->addChild((yyvsp[-1].ptr));
                        (yyval.ptr)->addChild((yyvsp[0].ptr));
                    }
#line 3431 "parser.tab.c"
    break;

  case 154: /* factor: power  */
#line 1364 "parser.y"
                {
                    (yyval.ptr) = (yyvsp[0].ptr);
                }
#line 3439 "parser.tab.c"
    break;

  case 155: /* factor1: '+'  */
#line 1367 "parser.y"
             {
                (yyval.ptr) = new TreeNode((yyvsp[0].str));
                (yyval.ptr)->setlineno(yylineno);  
                (yyval.ptr)->setType("unary_op");
            }
#line 3449 "parser.tab.c"
    break;

  case 156: /* factor1: '-'  */
#line 1372 "parser.y"
            {
            (yyval.ptr) = new TreeNode((yyvsp[0].str));
            (yyval.ptr)->setlineno(yylineno);  
            (yyval.ptr)->setType("unary_op");
        }
#line 3459 "parser.tab.c"
    break;

  case 157: /* factor1: '~'  */
#line 1377 "parser.y"
             {
            (yyval.ptr) = new TreeNode((yyvsp[0].str));
            (yyval.ptr)->setlineno(yylineno);  
            (yyval.ptr)->setType("unary_op");
        }
#line 3469 "parser.tab.c"
    break;

  case 158: /* power: atom_expr power1  */
#line 1383 "parser.y"
                        { 
                            if((yyvsp[0].ptr) != nullptr)
                            {
                                (yyval.ptr) = (yyvsp[0].ptr);
                                (yyvsp[0].ptr)->addChildFront((yyvsp[-1].ptr));
                            }
                            else
                            {
                                (yyval.ptr) = (yyvsp[-1].ptr);
                            }
                        }
#line 3485 "parser.tab.c"
    break;

  case 159: /* power1: %empty  */
#line 1394 "parser.y"
        {
            (yyval.ptr) = nullptr;
        }
#line 3493 "parser.tab.c"
    break;

  case 160: /* power1: OP_POWER factor  */
#line 1397 "parser.y"
                          {
                            (yyval.ptr) = new TreeNode((yyvsp[-1].str));
                            (yyval.ptr)->setlineno(yylineno);  
                            (yyval.ptr)->setType("binary_op");
                            (yyval.ptr)->addChild((yyvsp[0].ptr));
                        }
#line 3504 "parser.tab.c"
    break;

  case 161: /* atom_expr: atom atom_expr1  */
#line 1404 "parser.y"
                           {
                                (yyval.ptr) = new TreeNode("atom_expr");
                                (yyval.ptr)->setlineno(yylineno);
                                (yyval.ptr)->addChild((yyvsp[-1].ptr));
                                (yyval.ptr)->addChild((yyvsp[0].ptr));
                            }
#line 3515 "parser.tab.c"
    break;

  case 162: /* atom_expr1: %empty  */
#line 1410 "parser.y"
             {
                (yyval.ptr) = nullptr;
            }
#line 3523 "parser.tab.c"
    break;

  case 163: /* atom_expr1: atom_expr1 trailer  */
#line 1413 "parser.y"
                                 {
                                    (yyval.ptr) = new TreeNode("atom_expr1");
                                    (yyval.ptr)->addChild((yyvsp[-1].ptr));
                                    (yyval.ptr)->addChild((yyvsp[0].ptr));
                                }
#line 3533 "parser.tab.c"
    break;

  case 164: /* atom: '(' atom1 ')'  */
#line 1419 "parser.y"
                     {
                        TreeNode* node1 = new TreeNode((yyvsp[-2].str));
                        TreeNode* node3 = new TreeNode((yyvsp[0].str));
                        (yyval.ptr) = new TreeNode("atom");
                        (yyval.ptr)->addChild(node1);
                        (yyval.ptr)->addChild((yyvsp[-1].ptr));
                        (yyval.ptr)->addChild(node3);
                    }
#line 3546 "parser.tab.c"
    break;

  case 165: /* atom: '[' atom1 ']'  */
#line 1427 "parser.y"
                        {
                            TreeNode* node1 = new TreeNode((yyvsp[-2].str));
                            TreeNode* node3 = new TreeNode((yyvsp[0].str));
                            (yyval.ptr) = new TreeNode("atom");
                            (yyval.ptr)->addChild(node1);
                            (yyval.ptr)->addChild((yyvsp[-1].ptr));
                            (yyval.ptr)->addChild(node3);
                        }
#line 3559 "parser.tab.c"
    break;

  case 166: /* atom: NAME  */
#line 1435 "parser.y"
               {
                    (yyval.ptr) = new TreeNode((yyvsp[0].str));
                    if(type_expect == true)
                    {
                        type_expect_list.push_back(string((yyvsp[0].str)));
                    }
                    
                }
#line 3572 "parser.tab.c"
    break;

  case 167: /* atom: NUMBER  */
#line 1443 "parser.y"
                 {
                    (yyval.ptr) = new TreeNode((yyvsp[0].str));
                }
#line 3580 "parser.tab.c"
    break;

  case 168: /* atom: atom2  */
#line 1446 "parser.y"
                {
                    (yyval.ptr) = (yyvsp[0].ptr);
                }
#line 3588 "parser.tab.c"
    break;

  case 169: /* atom: KEYWORD_NONE  */
#line 1449 "parser.y"
                       {
                            (yyval.ptr) = new TreeNode((yyvsp[0].str));
                            if(type_expect == true)
                            {
                                type_expect_list.push_back(string((yyvsp[0].str)));
                            }
                        }
#line 3600 "parser.tab.c"
    break;

  case 170: /* atom: KEYWORD_TRUE  */
#line 1456 "parser.y"
                       {
                            (yyval.ptr) = new TreeNode((yyvsp[0].str));
                        }
#line 3608 "parser.tab.c"
    break;

  case 171: /* atom: KEYWORD_FALSE  */
#line 1459 "parser.y"
                        {
                            (yyval.ptr) = new TreeNode((yyvsp[0].str));

                        }
#line 3617 "parser.tab.c"
    break;

  case 172: /* atom1: %empty  */
#line 1463 "parser.y"
        {
            (yyval.ptr) = nullptr;
        }
#line 3625 "parser.tab.c"
    break;

  case 173: /* atom1: testlist_comp  */
#line 1466 "parser.y"
                        {
                            (yyval.ptr) = (yyvsp[0].ptr);
                        }
#line 3633 "parser.tab.c"
    break;

  case 174: /* atom2: STRING  */
#line 1469 "parser.y"
               {
                (yyval.ptr) = new TreeNode((yyvsp[0].str));
            }
#line 3641 "parser.tab.c"
    break;

  case 175: /* atom2: atom2 STRING  */
#line 1472 "parser.y"
                       {
                            TreeNode* node2 = new TreeNode((yyvsp[0].str));
                            (yyval.ptr) = new TreeNode("atom2");
                            (yyval.ptr)->addChild((yyvsp[-1].ptr));
                            (yyval.ptr)->addChild(node2);
                        }
#line 3652 "parser.tab.c"
    break;

  case 176: /* testlist_comp: test testlist_comp2 testlist_comp1  */
#line 1479 "parser.y"
                                                   {
                                                        (yyval.ptr) = new TreeNode("testlist_comp");
                                                        (yyval.ptr)->addChild((yyvsp[-2].ptr));
                                                        (yyval.ptr)->addChild((yyvsp[-1].ptr));
                                                        (yyval.ptr)->addChild((yyvsp[0].ptr));
                }
#line 3663 "parser.tab.c"
    break;

  case 177: /* testlist_comp1: ','  */
#line 1485 "parser.y"
                      {
                    (yyval.ptr) = new TreeNode((yyvsp[0].str));
                }
#line 3671 "parser.tab.c"
    break;

  case 178: /* testlist_comp1: %empty  */
#line 1488 "parser.y"
                  {
                    (yyval.ptr) = nullptr;
                }
#line 3679 "parser.tab.c"
    break;

  case 179: /* testlist_comp2: %empty  */
#line 1491 "parser.y"
                 {
                    (yyval.ptr) = nullptr;
                }
#line 3687 "parser.tab.c"
    break;

  case 180: /* testlist_comp2: testlist_comp2 ',' test  */
#line 1494 "parser.y"
                                          {
                                            TreeNode* node2 = new TreeNode((yyvsp[-1].str));
                                            (yyval.ptr) = new TreeNode("testlist_comp2");
                                            (yyval.ptr)->addChild((yyvsp[-2].ptr));
                                            (yyval.ptr)->addChild(node2);
                                            (yyval.ptr)->addChild((yyvsp[0].ptr));
                                        }
#line 3699 "parser.tab.c"
    break;

  case 181: /* trailer: '(' trailer1  */
#line 1502 "parser.y"
                       {
                        TreeNode* node1 = new TreeNode((yyvsp[-1].str));
                        (yyval.ptr) = new TreeNode("trailer");
                        (yyval.ptr)->addChild(node1);
                        (yyval.ptr)->addChild((yyvsp[0].ptr));
                    }
#line 3710 "parser.tab.c"
    break;

  case 182: /* trailer: '[' subscriptlist ']'  */
#line 1508 "parser.y"
                                {
                                    TreeNode* node1 = new TreeNode((yyvsp[-2].str));
                                    TreeNode* node3 = new TreeNode((yyvsp[0].str));
                                    (yyval.ptr) = new TreeNode("trailer");
                                    (yyval.ptr)->addChild(node1);
                                    (yyval.ptr)->addChild((yyvsp[-1].ptr));
                                    (yyval.ptr)->addChild(node3);
                                }
#line 3723 "parser.tab.c"
    break;

  case 183: /* trailer: '.' NAME  */
#line 1516 "parser.y"
                   {
                    TreeNode* node1 = new TreeNode((yyvsp[-1].str));
                    node1->setType("binary_op");
                    TreeNode* node2 = new TreeNode((yyvsp[0].str));
                    (yyval.ptr) = new TreeNode("trailer");
                    (yyval.ptr)->addChild(node1);
                    (yyval.ptr)->addChild(node2);
                }
#line 3736 "parser.tab.c"
    break;

  case 184: /* trailer1: arglist ')'  */
#line 1524 "parser.y"
                       {
                            TreeNode* node2 = new TreeNode((yyvsp[0].str));
                            (yyval.ptr) = new TreeNode("trailer1");
                            (yyval.ptr)->addChild((yyvsp[-1].ptr));
                            (yyval.ptr)->addChild(node2);
                        }
#line 3747 "parser.tab.c"
    break;

  case 185: /* trailer1: ')'  */
#line 1530 "parser.y"
              {
               (yyval.ptr) = new TreeNode((yyvsp[0].str));
            }
#line 3755 "parser.tab.c"
    break;

  case 186: /* subscriptlist: subscript subscriptlist2 subscriptlist1  */
#line 1533 "parser.y"
                                                       {
                                                            (yyval.ptr) = new TreeNode("subscriptlist");
                                                            (yyval.ptr)->addChild((yyvsp[-2].ptr));
                                                            (yyval.ptr)->addChild((yyvsp[-1].ptr));
                                                            (yyval.ptr)->addChild((yyvsp[0].ptr));
                                                        
                }
#line 3767 "parser.tab.c"
    break;

  case 187: /* subscriptlist1: %empty  */
#line 1540 "parser.y"
                  {
                    (yyval.ptr) = nullptr;
                }
#line 3775 "parser.tab.c"
    break;

  case 188: /* subscriptlist1: ','  */
#line 1543 "parser.y"
                      {
                        (yyval.ptr) = new TreeNode((yyvsp[0].str));
                    
                }
#line 3784 "parser.tab.c"
    break;

  case 189: /* subscriptlist2: %empty  */
#line 1547 "parser.y"
                 {
                    (yyval.ptr) = nullptr;
                }
#line 3792 "parser.tab.c"
    break;

  case 190: /* subscriptlist2: subscriptlist2 ',' subscript  */
#line 1550 "parser.y"
                                               {
                                                TreeNode* node2 = new TreeNode((yyvsp[-1].str));
                                                (yyval.ptr) = new TreeNode("subscriptlist2");
                                                (yyval.ptr)->addChild((yyvsp[-2].ptr));
                                                (yyval.ptr)->addChild(node2);
                                                (yyval.ptr)->addChild((yyvsp[0].ptr));
                                            }
#line 3804 "parser.tab.c"
    break;

  case 191: /* subscript: test subscript1  */
#line 1558 "parser.y"
                            {
                                (yyval.ptr) = new TreeNode("subscript");
                                (yyval.ptr)->addChild((yyvsp[-1].ptr));
                                (yyval.ptr)->addChild((yyvsp[0].ptr));
                            }
#line 3814 "parser.tab.c"
    break;

  case 192: /* subscript: ':' subscript2  */
#line 1563 "parser.y"
                             {
                                TreeNode* node1 = new TreeNode((yyvsp[-1].str));
                                (yyval.ptr) = new TreeNode("subscript");
                                (yyval.ptr)->addChild(node1);
                                (yyval.ptr)->addChild((yyvsp[0].ptr));
                            
            }
#line 3826 "parser.tab.c"
    break;

  case 193: /* subscript1: %empty  */
#line 1571 "parser.y"
             {
                (yyval.ptr) = nullptr;
            }
#line 3834 "parser.tab.c"
    break;

  case 194: /* subscript1: ':' subscript2  */
#line 1574 "parser.y"
                             {
                                TreeNode* node1 = new TreeNode((yyvsp[-1].str));
                                (yyval.ptr) = new TreeNode("subscript1");
                                (yyval.ptr)->addChild(node1);
                                (yyval.ptr)->addChild((yyvsp[0].ptr));
            }
#line 3845 "parser.tab.c"
    break;

  case 195: /* subscript2: test  */
#line 1580 "parser.y"
                  {
                    (yyval.ptr) = (yyvsp[0].ptr);
            }
#line 3853 "parser.tab.c"
    break;

  case 196: /* subscript2: %empty  */
#line 1583 "parser.y"
              {
                (yyval.ptr) = nullptr;
            }
#line 3861 "parser.tab.c"
    break;

  case 197: /* exprlist: expr exprlist2 exprlist1  */
#line 1586 "parser.y"
                                     {
                                            (yyval.ptr) = new TreeNode("exprlist");
                                            (yyval.ptr)->addChild((yyvsp[-2].ptr));
                                            (yyval.ptr)->addChild((yyvsp[-1].ptr));
                                            (yyval.ptr)->addChild((yyvsp[0].ptr));
                                        
            }
#line 3873 "parser.tab.c"
    break;

  case 198: /* exprlist1: %empty  */
#line 1593 "parser.y"
            {
                (yyval.ptr) = nullptr;
            }
#line 3881 "parser.tab.c"
    break;

  case 199: /* exprlist1: ','  */
#line 1596 "parser.y"
                 {
                    (yyval.ptr) = new TreeNode((yyvsp[0].str));
                }
#line 3889 "parser.tab.c"
    break;

  case 200: /* exprlist2: %empty  */
#line 1599 "parser.y"
            {
                (yyval.ptr) = nullptr;
            }
#line 3897 "parser.tab.c"
    break;

  case 201: /* exprlist2: exprlist2 ',' expr  */
#line 1602 "parser.y"
                                 {
                                    TreeNode* node2 = new TreeNode((yyvsp[-1].str));
                                    (yyval.ptr) = new TreeNode("exprlist2");
                                    (yyval.ptr)->addChild((yyvsp[-2].ptr));
                                    (yyval.ptr)->addChild(node2);
                                    (yyval.ptr)->addChild((yyvsp[0].ptr));
                                }
#line 3909 "parser.tab.c"
    break;

  case 202: /* testlist: test testlist1 testlist3  */
#line 1610 "parser.y"
                                    {
                                            (yyval.ptr) = new TreeNode("testlist");
                                            (yyval.ptr)->addChild((yyvsp[-2].ptr));
                                            (yyval.ptr)->addChild((yyvsp[-1].ptr));
                                            (yyval.ptr)->addChild((yyvsp[0].ptr));
                                        }
#line 3920 "parser.tab.c"
    break;

  case 203: /* testlist3: ','  */
#line 1616 "parser.y"
                {
                (yyval.ptr)  = new TreeNode((yyvsp[0].str));
            }
#line 3928 "parser.tab.c"
    break;

  case 204: /* testlist3: %empty  */
#line 1619 "parser.y"
              {
                (yyval.ptr) = nullptr;
            
            }
#line 3937 "parser.tab.c"
    break;

  case 205: /* testlist1: %empty  */
#line 1623 "parser.y"
             {
                (yyval.ptr) = nullptr;
            }
#line 3945 "parser.tab.c"
    break;

  case 206: /* testlist1: testlist1 ',' test  */
#line 1626 "parser.y"
                                 {
                                    TreeNode* node2 = new TreeNode((yyvsp[-1].str));
                                    (yyval.ptr) = new TreeNode("testlist1");
                                    (yyval.ptr)->addChild((yyvsp[-2].ptr));
                                    (yyval.ptr)->addChild(node2);
                                    (yyval.ptr)->addChild((yyvsp[0].ptr));
                                }
#line 3957 "parser.tab.c"
    break;

  case 207: /* $@7: %empty  */
#line 1634 "parser.y"
                              {
                        if (currentTable->lookup(string((yyvsp[0].str)))!=NULL){
                            cout <<"Line "<< yylineno << ":Name Error : Re-definition of name " << string((yyvsp[0].str)) << " is not allowed. Previous defined at line "<< currentTable->lookup(string((yyvsp[0].str)))->get_lineno() << endl;
                            exit(1);
                        }
                        SymbolTable* newTable = new SymbolTable(ST_Type::st_class,yylineno, currentTable,STentry_Type::ste_none,string((yyvsp[0].str)));
                        STentry* entry = new STentry(string((yyvsp[0].str)), STentry_Type::ste_class_def, yylineno, (void*)newTable);
                        currentTable->insert(string((yyvsp[0].str)), entry);
                        class_names.push_back(string((yyvsp[0].str)));
                        currentTable = newTable;
                }
#line 3973 "parser.tab.c"
    break;

  case 208: /* classdef: KEYWORD_CLASS NAME $@7 classdef1 ':' suite  */
#line 1645 "parser.y"
                      {
            TreeNode* node1 = new TreeNode((yyvsp[-5].str));
            TreeNode* node2 = new TreeNode((yyvsp[-4].str));
            TreeNode* node3 = new TreeNode((yyvsp[-1].str));
            (yyval.ptr) = new TreeNode("classdef");
            (yyval.ptr)->setlineno(yylineno);
            (yyval.ptr)->addChild(node1);
            (yyval.ptr)->addChild(node2);
            (yyval.ptr)->addChild((yyvsp[-2].ptr));
            (yyval.ptr)->addChild(node3);
            (yyval.ptr)->addChild((yyvsp[0].ptr));
            currentTable = globalTable;
            }
#line 3991 "parser.tab.c"
    break;

  case 209: /* classdef1: %empty  */
#line 1658 "parser.y"
            {
            (yyval.ptr) = nullptr;
            }
#line 3999 "parser.tab.c"
    break;

  case 210: /* classdef1: '(' arglist_class ')'  */
#line 1661 "parser.y"
                           {
                        TreeNode* node1 = new TreeNode((yyvsp[-2].str));
                        TreeNode* node2 = new TreeNode((yyvsp[0].str));
                        (yyval.ptr) = new TreeNode("classdef1");
                        (yyval.ptr)->addChild(node1);
                        (yyval.ptr)->addChild((yyvsp[-1].ptr));
                        (yyval.ptr)->addChild(node2);
                    }
#line 4012 "parser.tab.c"
    break;

  case 211: /* arglist_class: argument_class arglist_class1  */
#line 1669 "parser.y"
                                              {
                                                (yyval.ptr) = new TreeNode("arglist_class");
                                                (yyval.ptr)->addChild((yyvsp[-1].ptr));
                                                (yyval.ptr)->addChild((yyvsp[0].ptr));
            }
#line 4022 "parser.tab.c"
    break;

  case 212: /* arglist_class1: %empty  */
#line 1674 "parser.y"
                 {
                    (yyval.ptr) = nullptr;
                }
#line 4030 "parser.tab.c"
    break;

  case 213: /* arglist_class1: arglist_class1 ',' argument_class  */
#line 1677 "parser.y"
                                                    {
                                    TreeNode* node2 = new TreeNode((yyvsp[-1].str));
                                    (yyval.ptr) = new TreeNode("arglist_class1");
                                    (yyval.ptr)->addChild((yyvsp[-2].ptr));
                                    (yyval.ptr)->addChild(node2);
                                    (yyval.ptr)->addChild((yyvsp[0].ptr));
                }
#line 4042 "parser.tab.c"
    break;

  case 214: /* argument_class: test  */
#line 1684 "parser.y"
                      {
                (yyval.ptr) = (yyvsp[0].ptr);
                TreeNode* temp = (yyvsp[0].ptr);
                // string name = getFirstTerminalValue(temp);
                vector<TreeNode*> values;
                getAllTerminalValue(temp, values);
                string name = values[0]->value;
                values.clear();
               // this argument is a class to be inherited in my current class
                if (globalTable->lookup(name) == NULL){
                    cout <<"Line "<< yylineno << ":Name Error : Class " << name << " is not defined" << endl;
                    exit(1);
                }
                //copy the symbol table of the class to the current class
                SymbolTable* parentClass = (SymbolTable*)globalTable->lookup(name)->get_nested_table();
                // cout << "offset of currentTable is "  << currentTable->get_offset() << endl; 
                currentTable->copySymbolTable(parentClass);
                // cout << "offset of currentTable is "  << currentTable->get_offset() << endl;
}
#line 4066 "parser.tab.c"
    break;

  case 215: /* arglist: argument arglist1 arglist2  */
#line 1703 "parser.y"
                                    {
                                (yyval.ptr) = new TreeNode("arglist");
                                (yyval.ptr)->addChild((yyvsp[-2].ptr));
                                (yyval.ptr)->addChild((yyvsp[-1].ptr));
                                (yyval.ptr)->addChild((yyvsp[0].ptr));
        }
#line 4077 "parser.tab.c"
    break;

  case 216: /* arglist2: ','  */
#line 1709 "parser.y"
              {
                (yyval.ptr) = new TreeNode((yyvsp[0].str));
            }
#line 4085 "parser.tab.c"
    break;

  case 217: /* arglist2: %empty  */
#line 1712 "parser.y"
         {
            (yyval.ptr) = nullptr;
        
        }
#line 4094 "parser.tab.c"
    break;

  case 218: /* arglist1: %empty  */
#line 1716 "parser.y"
          {
            (yyval.ptr) = nullptr;
        }
#line 4102 "parser.tab.c"
    break;

  case 219: /* arglist1: arglist1 ',' argument  */
#line 1719 "parser.y"
                                {
                                    TreeNode* node2 = new TreeNode((yyvsp[-1].str));
                                    (yyval.ptr) = new TreeNode("arglist1");
                                    (yyval.ptr)->addChild((yyvsp[-2].ptr));
                                    (yyval.ptr)->addChild(node2);
                                    (yyval.ptr)->addChild((yyvsp[0].ptr));
                                }
#line 4114 "parser.tab.c"
    break;

  case 220: /* argument: test argument1  */
#line 1727 "parser.y"
                          {
                                // $$ = new TreeNode("argument");
                                // $$->addChild($1);
                                // $$->addChild($2);
                                if ((yyvsp[0].ptr) == nullptr){
                                    (yyval.ptr) = (yyvsp[-1].ptr);
                                }
                                else {
                                    // TreeNode* node1 = new TreeNode($1);
                                    (yyval.ptr) = (yyvsp[0].ptr);
                                    (yyvsp[0].ptr)->addChildFront((yyvsp[-1].ptr));
                                }
                            }
#line 4132 "parser.tab.c"
    break;

  case 221: /* argument1: %empty  */
#line 1753 "parser.y"
            {
                (yyval.ptr) =nullptr;
        }
#line 4140 "parser.tab.c"
    break;

  case 222: /* argument1: '=' test  */
#line 1756 "parser.y"
                  {
                    // TreeNode* node1 = new TreeNode($1);
                    // $$ = new TreeNode("argument1");
                    // $$->addChild(node1);
                    // $$->addChild($2);
                    (yyval.ptr) = new TreeNode((yyvsp[-1].str));
                    (yyval.ptr)->setType("assign");
                    (yyval.ptr)->setlineno(yylineno);
                    (yyval.ptr)->addChild((yyvsp[0].ptr));
                    
                }
#line 4156 "parser.tab.c"
    break;


#line 4160 "parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 1798 "parser.y"


void print_options(){
	cout<<"Usage: parser [OPTIONS] file...\n\n";
	cout<<"Options:\n";
	cout<<"\t--help\t\t\tDisplay available options\n";
	cout<<"\t-output <file>\t\tdump the dot script generated in <file> \n";
    cout<<"\t-input <file>\t\tRead the input from <file>\n";
    cout <<"\t-verbose \t\tTo enable verbose\n";
    cout<<"\tIf no output file is specified automatic parser_tree.dot is generated\n";
    cout<<"\tIf no input file is specified, the program will give error\n";
    cout<<"\tIf multiple input file are specified it will process the first file or throw error\n";
	cout<<"\n\n";
}
void print_error(){
	cout<<"\033[1;31mError Found\033[0m"<<endl;
}
void yyerror(const char *error) 
{
    printf("ERROR:%s at line number: %d\n", error, yylineno);
    exit(0);
}
int main(int argc, char* argv[]) {
    string output_file_name,input_file_name;
    FILE* input_file;
    if (argc < 2) {
        print_error();
        cout<<"Too few arguments\n";
        print_options();
        return 0;
    }

    for(int i = 1; i<argc; i++){
		if(!strcmp(argv[i], "--help")){
			print_options();
			return 0;
		}
	}
    for(int i = 1; i<argc; i++){
        if(!strcmp(argv[i], "-output")){
            output_file_name = argv[i+1];
            i++;
        }
        else if(!strcmp(argv[i], "-input")){
            input_file_name = argv[i+1];
            input_file = fopen(argv[i+1], "r");
            i++;
        }
        else if (!strcmp(argv[i],"-verbose")){
            verbose = true;
        }
		else{
            print_error();
            cout<<"Invalid argument\n";
            print_options();
            return 0;
        }
	}
    
    if (!input_file) {
        perror("fopen");
        return 1;
    }
    yyin = input_file;
    if (verbose){
        cout<<"Parsing the file :" << input_file_name <<endl;
    }

    initializeGlobalSymbolTable();
    yyparse();
    
    if(output_file_name.empty()){
        output_file_name = "parser_tree.dot";
    }
    if (verbose) {
        cout << "Starting to clean the AST" << endl;
    }
    cleanParseTree(root); 
    /* createParentAST(root); */
    /* root->printTree(root); */
    if (verbose) {
        cout << "AST cleaned successfully" << endl;
        cout << "Starting to create the dot file" << endl;
    }
    ofstream dotFile(output_file_name.c_str());
    dotFile << "digraph ParseTree {" << endl;
    createParseTreeDot(root, dotFile);
    if (verbose){
        cout << "Dot file created successfully" << endl;
    }
    dotFile << "}" << endl;
    dotFile.close();
    
    // print symbol table
    ofstream outfile("symbol_table.csv");
    if (outfile.is_open()) {
        outfile << "Name," << "Line No.," << "Type," <<  "is_list," << "class_obj_name,"  << "nested_table," << "Offset," << "Width" << endl;
        globalTable->print_table_csv(outfile);
        outfile.close();
        cout << "CSV file generated successfully." << endl;
    } 
    else {
        cout << "Unable to open file for writing." << endl;
    }

    if(verbose)
        cout << "generating 3AC..." << endl;
    generate_3ac(root, globalTable);
    updatelineofquads();
    /* cout << "traversal stats..." << endl;  */

    // traverse_AST(root);
    // print_quads_global();
    print_quads_to_file("quads_output.txt");
    // x86 codegen
    codegen* gen = new codegen();
    gen->gen_global();
    gen->gen_text();
    gen->print_code("asm.s");
    delete root;
    fclose(input_file);
    return 0;
}
