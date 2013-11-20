%{
/* LEX program for building a lexical analyzer for expressions */	

	#include "y.tab.h"
	#include<stdlib.h>
	#include<stdio.h>
	#define PLUS 22
	#define MINUS 33
	#define MUL 44
	#define DIV 55
	#define NEG 77
	#define POW 88
	#define NUM 99
	
%}


number  [0-9]+
op 	[-|+|*|/]	

%%
[\t]+         { }
[\n]		return END;
"+"		{
			yylval.ptr = malloc(sizeof(struct node));			
			yylval.ptr->node_type = PLUS;			
			return P;
		}
		
"-"		{
			yylval.ptr = malloc(sizeof(struct node));			
			yylval.ptr->node_type = MINUS;			
			return S;
		}
"*"		{
			yylval.ptr = malloc(sizeof(struct node));			
			yylval.ptr->node_type = MUL;			
			return M;
		}
"/"		{
			yylval.ptr = malloc(sizeof(struct node));
			yylval.ptr->node_type = DIV;			
			return D;
		}
"%"            {       yylval.ptr = malloc(sizeof(struct node ));
                        yylval.ptr->node_type = MOD;
                       return R;
                 }
\^		{
			yylval.ptr = malloc(sizeof(struct node));
			yylval.ptr->node_type = POW;			
			return C;
		}
{number}	{
			yylval.ptr = malloc(sizeof(struct node));
			yylval.ptr->val = atoi(yytext);
			yylval.ptr->node_type = NUM;
			yylval.ptr->P1 = NULL;
			yylval.ptr->P2 = NULL;
			return NUMBER;
		}

[\(\)] 	return *yytext;

.	yyerror("ERROR");
%%
