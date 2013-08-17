%{
/*LEX program for parsing expressions and generating code.*/	

	#include "y.tab.h"
	#include<stdlib.h>
	#include<stdio.h>
	
%}


number  [0-9]+
op 	[-|+|*|/]	

%%

" "  		;
[\n]		return END;
{op}		return *yytext;
\%		return *yytext;
\^		return *yytext;
{number}	{
			yylval.val=atoi(yytext);
			return NUMBER;
		}
[\(\)] 	return *yytext;
.	yyerror("ERROR");
%%
