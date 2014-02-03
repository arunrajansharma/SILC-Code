/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     NUMBER = 258,
     END = 259,
     START = 260,
     P = 261,
     M = 262,
     S = 263,
     D = 264,
     C = 265,
     R = 266,
     READ = 267,
     WRITE = 268,
     ASSIGN_OP = 269,
     ID = 270,
     WHILE = 271,
     DO = 272,
     ENDWHILE = 273,
     IF = 274,
     THEN = 275,
     ENDIF = 276,
     ELSE = 277,
     DECL = 278,
     ENDDECL = 279,
     INT = 280,
     BOOL = 281,
     RELOP = 282,
     UMINUS = 283
   };
#endif
/* Tokens.  */
#define NUMBER 258
#define END 259
#define START 260
#define P 261
#define M 262
#define S 263
#define D 264
#define C 265
#define R 266
#define READ 267
#define WRITE 268
#define ASSIGN_OP 269
#define ID 270
#define WHILE 271
#define DO 272
#define ENDWHILE 273
#define IF 274
#define THEN 275
#define ENDIF 276
#define ELSE 277
#define DECL 278
#define ENDDECL 279
#define INT 280
#define BOOL 281
#define RELOP 282
#define UMINUS 283




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 2068 of yacc.c  */
#line 129 "cg_calc.y"

	struct node *ptr;
	



/* Line 2068 of yacc.c  */
#line 113 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


