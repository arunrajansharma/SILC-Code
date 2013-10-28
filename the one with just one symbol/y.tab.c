#ifndef lint
static const char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20120115

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)

#define YYPREFIX "yy"

#define YYPURE 0

#line 2 "cg_calc.y"
	/* Yacc program for generating code for an expression (using expression syntax tree)  */

/*Node type constants*/
#define PLUS 22
#define MINUS 33
#define MUL 44
#define DIV 55
#define REM 66
#define NEG 77
#define POW 88
#define NUM 99
#define MOD 98
#define VOID 103


/*Header files */
#include<stdio.h>
#include<stdlib.h> 

/*Global file pointer */
FILE *fp;

/*Data structure of a binary tree (which will be used to implement the expression syntax tree)*/
struct node
{
	int node_type;
	int val;
        char * id;
	struct node *left;
	struct node *right;
};

int regcount = -1;

/*To report an error */
void yyerror(char *);

/*To make a node in the tree*/
struct node* makenode(struct node *parent,struct node *left, struct node*right);

/*To recursively descend the tree and calculate the value of the expression*/
void calculate(struct node *t);

/*To calculate the static binding of single variable*/
int variable_binding(char *x);


#line 52 "cg_calc.y"
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
#line 80 "y.tab.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

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
#define YYERRCODE 256
static const short yylhs[] = {                           -1,
    0,    4,    2,    2,    3,    3,    3,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,
};
static const short yylen[] = {                            2,
    1,    1,    2,    0,    4,    5,    5,    3,    3,    3,
    3,    3,    3,    2,    3,    1,    1,
};
static const short yydefred[] = {                         0,
    0,    0,    0,    0,    2,    0,    1,    0,    0,    0,
    3,    0,   16,    0,   17,    0,    0,    0,    0,   14,
    0,    0,    0,    0,    0,    0,    0,    0,    5,    6,
   13,    0,    0,    0,    0,    0,   11,    7,
};
static const short yydgoto[] = {                          4,
   17,    5,    6,    7,
};
static const short yysindex[] = {                      -246,
  -24,  -19, -250,    0,    0, -246,    0, -244,  -40,  -40,
    0,  -15,    0,  -40,    0,  -40,  -38, -254, -231,    0,
  -30,  -40,  -40,  -40,  -40,  -40,  -40, -228,    0,    0,
    0, -249, -249, -262, -262, -232,    0,    0,
};
static const short yyrindex[] = {                        34,
    0,    0,    0,    0,    0,   34,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   -8,   -5,  -23,  -18,  -13,    0,    0,
};
static const short yygindex[] = {                         0,
   15,   29,    0,    0,
};
#define YYTABLESIZE 255
static const short yytable[] = {                         16,
   26,   27,   28,   29,   22,   23,   24,   25,   26,   27,
   31,   24,   25,   26,   27,    8,   10,   10,    1,    2,
    9,    3,   12,   12,   18,   19,   30,   15,   20,   38,
   21,   27,    8,    4,   11,    9,   32,   33,   34,   35,
   36,   37,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   13,    0,    0,   14,
   22,   23,   24,   25,   26,   27,    0,   15,   22,   23,
   24,   25,   26,   27,   10,   10,   10,   10,   10,   12,
   12,   12,   12,   12,   15,   15,   15,   15,   15,    8,
    8,    8,    9,    9,    9,
};
static const short yycheck[] = {                         40,
  263,  264,   41,  258,  259,  260,  261,  262,  263,  264,
   41,  261,  262,  263,  264,   40,  267,   41,  265,  266,
   40,  268,   41,  268,   10,   41,  258,   41,   14,  258,
   16,  264,   41,    0,    6,   41,   22,   23,   24,   25,
   26,   27,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  257,   -1,   -1,  260,
  259,  260,  261,  262,  263,  264,   -1,  268,  259,  260,
  261,  262,  263,  264,  258,  259,  260,  261,  262,  258,
  259,  260,  261,  262,  258,  259,  260,  261,  262,  258,
  259,  260,  258,  259,  260,
};
#define YYFINAL 4
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 272
#if YYDEBUG
static const char *yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,"'('","')'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"NUMBER","END","P","M",
"S","D","C","R","READ","WRITE","ASSIGN_OP","ID","LT","GT","EQ","UMINUS",
};
static const char *yyrule[] = {
"$accept : start",
"start : program",
"program : stmts",
"stmts : stmt stmts",
"stmts :",
"stmt : ID ASSIGN_OP expr END",
"stmt : READ '(' ID ')' END",
"stmt : WRITE '(' expr ')' END",
"expr : expr P expr",
"expr : expr M expr",
"expr : expr S expr",
"expr : expr R expr",
"expr : expr D expr",
"expr : '(' expr ')'",
"expr : M expr",
"expr : expr C expr",
"expr : NUMBER",
"expr : ID",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  500
#endif
#endif

#define YYINITSTACKSIZE 500

typedef struct {
    unsigned stacksize;
    short    *s_base;
    short    *s_mark;
    short    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;
#line 115 "cg_calc.y"

#include "lex.yy.c"

struct node *makenode(struct node *parent,struct node *left, struct node*right)
{
	parent->left=left;
	parent->right=right;

	return parent;
}

void res_reg(int no_reg)	
{
	regcount = regcount + no_reg;
}

void free_reg(int no_reg)
{
	regcount = regcount - no_reg;
}

int use_reg(int regno)
{
	return regcount-regno+1;
}

int variable_binding(char * a)
{  
	char x = *a;
	int y = 0;
   	y = (int)x;
  	return(y-97);
}

void calculate(struct node *t)
{

	if(t!=NULL)
	{
		int ret;
                if(t->node_type==VOID)
                {  
			calculate(t->left); 
	                calculate(t->right);
                }
		else if(t->node_type==PLUS)
		{	
			calculate(t->left);
			calculate(t->right);
 			fprintf(fp,"\nADD R%d,R%d",use_reg(2), use_reg(1));
			free_reg(1);		
		
		}
		else if(t->node_type==MINUS)
		{
			if(t->right == NULL)
			{	
				calculate(t->left);
				res_reg(1);
				fprintf(fp,"\nMOV R%d,-1",use_reg(1));
				fprintf(fp,"\nMUL R%d,R%d",use_reg(2),use_reg(1));
				free_reg(1);
			}
			else
			{
				calculate(t->left);
				calculate(t->right);
				fprintf(fp,"\nSUB R%d,R%d",use_reg(2), use_reg(1));
				free_reg(1);
			}
		}
		else if(t->node_type==MUL)
		{
			calculate(t->left);
			calculate(t->right);
			fprintf(fp,"\nMUL R%d,R%d",use_reg(2), use_reg(1));
			free_reg(1);
		}
                else if(t->node_type==MOD)
		{
			calculate(t->left);
			calculate(t->right);
			fprintf(fp,"\nMOD R%d,R%d",use_reg(2), use_reg(1));
			free_reg(1);
		}
		else if(t->node_type==DIV)
		{
			calculate(t->left);
			calculate(t->right);
			fprintf(fp,"\nDIV R%d,R%d",use_reg(2), use_reg(1));
			free_reg(1);
		}
		else if(t->node_type==REM)
		{
			calculate(t->left);
			calculate(t->right);
			fprintf(fp,"\nMOD R%d,R%d",use_reg(2), use_reg(1));
			free_reg(1);
		}
		else if(t->node_type==NUM)
		{
			ret = t->val;
			res_reg(1);
			fprintf(fp,"\nMOV R%d,%d",use_reg(1), ret);		
		}
                else if (t->node_type == VAR)
                {    
		        int mptr = variable_binding(t->id);
                        res_reg(3);
			fprintf(fp,"\nMOV R%d,BP",use_reg(2));
			fprintf(fp,"\nMOV R%d,%d",use_reg(1),mptr);
			fprintf(fp,"\nADD R%d,R%d",use_reg(2),use_reg(1));
			fprintf(fp,"\nMOV R%d,[R%d]",use_reg(3),use_reg(2));
			free_reg(2);		
               	}
                else if (t->node_type == ASSIGN)
                {  
			int mptr = variable_binding(t->left->id);
                        res_reg(2);
			fprintf(fp,"\nMOV R%d,BP",use_reg(2));
			fprintf(fp,"\nMOV R%d,%d",use_reg(1),mptr);
			fprintf(fp,"\nADD R%d,R%d",use_reg(2),use_reg(1));
			free_reg(1);
			calculate(t->right);
                   	fprintf(fp,"\nMOV [R%d],R%d",use_reg(2),use_reg(1));
                   	free_reg(2);
                }
           	else if(t->node_type == WRITE_NODE)
                {  	
			calculate(t->left);
                    	fprintf(fp,"\nOUT R%d",use_reg(1));
                }
           	else if(t->node_type == READ_NODE)
                {    
			res_reg(1);			
			fprintf(fp,"\nIN R%d",use_reg(1));
                      	int mptr = variable_binding(t->left->id);
                        res_reg(2);
			fprintf(fp,"\nMOV R%d,BP",use_reg(1));
			fprintf(fp,"\nMOV R%d,%d",use_reg(2),mptr);
			fprintf(fp,"\nADD R%d,R%d",use_reg(1),use_reg(2));
			fprintf(fp,"\nMOV [R%d],R%d",use_reg(1),use_reg(3));
			free_reg(3);
                }
              
		
	}
	
	
}

void yyerror(char *s)
{
	fprintf(stderr, "%s\n", s);
}
int yywrap(void)
{
	return 1;	
}
	
int main()
{
	yyparse();
	return 0;
}

#line 459 "y.tab.c"

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = data->s_mark - data->s_base;
    newss = (short *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return -1;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return -1;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack)) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    yyerror("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 1:
#line 72 "cg_calc.y"
	{		
			                                fp = fopen("sil.asm","a");
							fprintf(fp,"START");
							fprintf(fp,"\nMOV SP,0");
							fprintf(fp,"\nMOV BP,0");
                                                        calculate(yystack.l_mark[0].ptr);
							
							fprintf(fp,"\nHALT");                                                          
							fclose(fp);
							exit(1);
					   	}
break;
case 2:
#line 85 "cg_calc.y"
	{yyval.ptr=yystack.l_mark[0].ptr; }
break;
case 3:
#line 88 "cg_calc.y"
	{  
								struct node * t1 = malloc(sizeof(struct node));
			                                        t1->node_type = VOID;
                	                                     	yyval.ptr=makenode(t1,yystack.l_mark[-1].ptr,yystack.l_mark[0].ptr); 
							}
break;
case 4:
#line 93 "cg_calc.y"
	{  yyval.ptr= NULL;}
break;
case 5:
#line 96 "cg_calc.y"
	{    yyval.ptr=makenode(yystack.l_mark[-2].ptr,yystack.l_mark[-3].ptr,yystack.l_mark[-1].ptr);}
break;
case 6:
#line 97 "cg_calc.y"
	{    yyval.ptr=makenode(yystack.l_mark[-4].ptr,yystack.l_mark[-2].ptr,NULL); }
break;
case 7:
#line 98 "cg_calc.y"
	{    yyval.ptr=makenode(yystack.l_mark[-4].ptr,yystack.l_mark[-2].ptr,NULL);}
break;
case 8:
#line 101 "cg_calc.y"
	{yyval.ptr=makenode(yystack.l_mark[-1].ptr,yystack.l_mark[-2].ptr,yystack.l_mark[0].ptr);	}
break;
case 9:
#line 102 "cg_calc.y"
	{yyval.ptr=makenode(yystack.l_mark[-1].ptr,yystack.l_mark[-2].ptr,yystack.l_mark[0].ptr);	}
break;
case 10:
#line 103 "cg_calc.y"
	{yyval.ptr=makenode(yystack.l_mark[-1].ptr,yystack.l_mark[-2].ptr,yystack.l_mark[0].ptr);	}
break;
case 11:
#line 104 "cg_calc.y"
	{yyval.ptr=makenode(yystack.l_mark[-1].ptr,yystack.l_mark[-2].ptr,yystack.l_mark[0].ptr); }
break;
case 12:
#line 105 "cg_calc.y"
	{yyval.ptr=makenode(yystack.l_mark[-1].ptr,yystack.l_mark[-2].ptr,yystack.l_mark[0].ptr);	}
break;
case 13:
#line 106 "cg_calc.y"
	{yyval.ptr=yystack.l_mark[-1].ptr;			}
break;
case 14:
#line 107 "cg_calc.y"
	{yyval.ptr=makenode(yystack.l_mark[-1].ptr,yystack.l_mark[0].ptr,NULL);}
break;
case 15:
#line 108 "cg_calc.y"
	{yyval.ptr=makenode(yystack.l_mark[-1].ptr,yystack.l_mark[-2].ptr,yystack.l_mark[0].ptr);	}
break;
case 16:
#line 109 "cg_calc.y"
	{yyval.ptr=yystack.l_mark[0].ptr;}
break;
case 17:
#line 110 "cg_calc.y"
	{yyval.ptr=yystack.l_mark[0].ptr;}
break;
#line 747 "y.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (short) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    yyerror("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
