%{
/*LEX program for parsing expressions and generating code.*/	

	#include "y.tab.h"
	#include<stdlib.h>
	#include<stdio.h>
	#define PLUS 22
	#define MINUS 33
	#define MUL 44
	#define DIV 55
	#define REM 66
	#define NEG 77
	#define POW 88
	#define NUM 99
	
%}


number  [0-9]+
op 	[-|+|*|/]	

%%

" "  		;
[\n]		return END;
"+"		{
			yylval.ptr->node_type = PLUS;			
			return P;
		}
		
"-"		{
			yylval.ptr->node_type = MINUS;			
			return M;
		}
"*"		{
			yylval.ptr->node_type = MUL;			
			return S;
		}
"/"		{
			yylval.ptr->node_type = DIV;			
			return D;
		}
\%		{
			yylval.ptr->node_type = REM;			
			return R;
		}
\^		{
			yylval.ptr->node_type = POW;			
			return C;
		}
{number}	{
			yylval.ptr->num = atoi(yytext);
			yylval.ptr->node_type = NUM;
			return NUMBER;
		}

[\(\)] 	return *yytext;

.	yyerror("ERROR");
%%
