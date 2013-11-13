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
	#define VAR 100  
	#define ASSIGN 101
        #define MOD 102	
        #define VOID 103
	#define CONDITIONAL_LT 104
	#define CONDITIONAL_GT 105
	#define CONDITIONAL_EQ 106 
        #define READ_NODE 145
        #define WRITE_NODE 150
     
%}


number  [0-9]+
alpha   [a-z]+
	

%%


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
\^		{
			yylval.ptr = malloc(sizeof(struct node));
			yylval.ptr->node_type = POW;			
			return C;
		}
"read"         {        yylval.ptr = malloc(sizeof(struct node));
			yylval.ptr->node_type = READ_NODE;			
			return READ;
                
               }
"write"        {        yylval.ptr = malloc(sizeof(struct node));
			yylval.ptr->node_type = WRITE_NODE;			
			return WRITE;

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

"<"              {     yylval.ptr = malloc(sizeof(struct node));
		       yylval.ptr->node_type = CONDITIONAL_LT;
                       yylval.ptr->left = NULL;
	 	       yylval.ptr->right = NULL;
		       return LT;

                 }

">"              {     yylval.ptr = malloc(sizeof(struct node));
		       yylval.ptr->node_type = CONDITIONAL_GT;
                       yylval.ptr->left = NULL;
	 	       yylval.ptr->right = NULL;
		       return GT;

                 }

"=="              {    yylval.ptr = malloc(sizeof(struct node));
		       yylval.ptr->node_type = CONDITIONAL_EQ;
                       yylval.ptr->left = NULL;
	 	       yylval.ptr->right = NULL;
		       return EQ;

                 }








[\(\)] 	return *yytext;

.	yyerror("ERROR");
%%
