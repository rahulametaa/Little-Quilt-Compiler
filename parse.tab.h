/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

#ifndef YY_YY_PARSE_TAB_H_INCLUDED
# define YY_YY_PARSE_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    A = 258,
    B = 259,
    TURN = 260,
    SEW = 261,
    HDROW = 262,
    TLROWS = 263,
    HDCOL = 264,
    TLCOLS = 265,
    COMMA = 266,
    OB = 267,
    CB = 268,
    LET = 269,
    FUN = 270,
    VAL = 271,
    ID = 272,
    IN = 273,
    END = 274,
    ASSIGN = 275
  };
#endif
/* Tokens.  */
#define A 258
#define B 259
#define TURN 260
#define SEW 261
#define HDROW 262
#define TLROWS 263
#define HDCOL 264
#define TLCOLS 265
#define COMMA 266
#define OB 267
#define CB 268
#define LET 269
#define FUN 270
#define VAL 271
#define ID 272
#define IN 273
#define END 274
#define ASSIGN 275

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 19 "lq2.y" /* yacc.c:1909  */

  char *name;
  class AST *ast;
  class DECL_AST *decl_ast;
  class FPARAM_AST *fparam_ast;
  class APARAM_AST *aparam_ast;

#line 102 "parse.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSE_TAB_H_INCLUDED  */
