#define NUMBER 257
#define END 258
#define DECLEND 259
#define P 260
#define M 261
#define S 262
#define D 263
#define C 264
#define R 265
#define ID 266
#define ASSIGN_OP 267
#define UMINUS 268
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union 
{
	struct node *ptr;
	
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
extern YYSTYPE yylval;
