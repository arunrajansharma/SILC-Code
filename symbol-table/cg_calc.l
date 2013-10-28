%{
/*LEX program for parsing expressions and generating code.*/	

	#include "y.tab.h"
	#include<stdlib.h>
	#include<stdio.h>
      
	
%}


number  [0-9]+
alpha   [a-z]+
	

%%
"DECLEND"   { return  DECLEND ;}

[\n]       { return END;}
" "             ;
"+"		{
			yylval.ptr = malloc(sizeof(struct node));			
			yylval.ptr->node_type = PLUS;			
			return P;
		}
		
"-"		{
			yylval.ptr = malloc(sizeof(struct node));			
			yylval.ptr->node_type = MINUS;			
			return M;
		}
"*"		{
			yylval.ptr = malloc(sizeof(struct node));			
			yylval.ptr->node_type = MUL;			
			return S;
		}
"/"		{
			yylval.ptr = malloc(sizeof(struct node));
			yylval.ptr->node_type = DIV;			
			return D;
		}
"%"            {        yylval.ptr = malloc(sizeof(struct node ));
                        yylval.ptr->node_type = MOD;
                        return R;
                 }
"read"          {       yylval.ptr = malloc(sizeof(struct node));
			yylval.ptr->node_type = READ_NODE;			
			return READ;
                
                }
"write"        {        yylval.ptr = malloc(sizeof(struct node));
			yylval.ptr->node_type = WRITE_NODE;			
			return WRITE;

               }
\^		{
			yylval.ptr = malloc(sizeof(struct node));
			yylval.ptr->node_type = POW;			
			return C;
		}

{alpha}        {        
                      
                        yylval.ptr = malloc(sizeof(struct node));
                        yylval.ptr->id=malloc(sizeof(yytext)); 
                        strcpy(yylval.ptr->id,yytext);
                        yylval.ptr->node_type = VAR;
                        yylval.ptr->left = NULL;
	 	        yylval.ptr->right = NULL;
		        return ID;
		 }	
		 
"="              {     yylval.ptr = malloc(sizeof(struct node));
		       yylval.ptr->node_type = ASSIGN;
                       yylval.ptr->left = NULL;
	 	       yylval.ptr->right = NULL;
		       return ASSIGN_OP;
		 }


		  
{number}	 {
			yylval.ptr = malloc(sizeof(struct node));
			yylval.ptr->val = atoi(yytext);
			yylval.ptr->node_type = NUM;
			yylval.ptr->left = NULL;
			yylval.ptr->right = NULL;
			return NUMBER;
		 }

[\(\)] 	return *yytext;

.	yyerror("ERROR");
%%
