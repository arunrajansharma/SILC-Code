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
     BOOLEAN_NUMBER = 259,
     P = 260,
     M = 261,
     S = 262,
     D = 263,
     C = 264,
     R = 265,
     READ = 266,
     WRITE = 267,
     ASSIGN_OP = 268,
     ID = 269,
     WHILE = 270,
     DO = 271,
     ENDWHILE = 272,
     AND = 273,
     OR = 274,
     NOT = 275,
     IF = 276,
     THEN = 277,
     ENDIF = 278,
     ELSE = 279,
     DECL = 280,
     ENDDECL = 281,
     INT = 282,
     BOOL = 283,
     RETURN = 284,
     MAIN = 285,
     BEG = 286,
     END = 287,
     RELOP = 288,
     UMINUS = 289
   };
#endif
/* Tokens.  */
#define NUMBER 258
#define BOOLEAN_NUMBER 259
#define P 260
#define M 261
#define S 262
#define D 263
#define C 264
#define R 265
#define READ 266
#define WRITE 267
#define ASSIGN_OP 268
#define ID 269
#define WHILE 270
#define DO 271
#define ENDWHILE 272
#define AND 273
#define OR 274
#define NOT 275
#define IF 276
#define THEN 277
#define ENDIF 278
#define ELSE 279
#define DECL 280
#define ENDDECL 281
#define INT 282
#define BOOL 283
#define RETURN 284
#define MAIN 285
#define BEG 286
#define END 287
#define RELOP 288
#define UMINUS 289




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 2068 of yacc.c  */
#line 195 "cg_calc.y"

	struct node *ptr;
	



/* Line 2068 of yacc.c  */
#line 125 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


