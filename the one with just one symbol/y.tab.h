#define NUMBER 257
#define END 258
#define P 259
#define M 260
#define S 261
#define D 262
#define C 263
#define R 264
#define READ 265
#define WRITE 266
#define ASSIGN_OP 267
#define ID 268
#define LT 269
#define GT 270
#define EQ 271
#define UMINUS 272
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
