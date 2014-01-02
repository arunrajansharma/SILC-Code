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
	#define LT 104
	#define GT 105
	#define EQ 106 
        #define READ_NODE 145
        #define WRITE_NODE 150
     
%}


number  [0-9]+
alpha   [a-z]+
	

%%
"start"      return START ;
"end"        return END  ;
"if"        { return IF ;}
"endif"     { return ENDIF ; }
"then"      { return THEN ;}
"else"      { return ELSE ;}
"while"      {return WHILE;}
"endwhile"    {return ENDWHILE;}

"do"           {return DO;}

[ \t\n]+		{
      			}
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
		        return ID;
	       }
	
		 
"="              {     yylval.ptr = malloc(sizeof(struct node));
		       yylval.ptr->node_type = ASSIGN;
		       return ASSIGN_OP;
		 }
		  
{number}	 {
			yylval.ptr = malloc(sizeof(struct node));
			yylval.ptr->val = atoi(yytext);
			yylval.ptr->node_type = NUM;			
			return NUMBER;
		 }

"<"              {     yylval.ptr = malloc(sizeof(struct node));
		       yylval.ptr->node_type = LT;
                       
		       return RELOP;

                 }

">"              {     yylval.ptr = malloc(sizeof(struct node));
		       yylval.ptr->node_type = GT;
                        return RELOP;

                 }

"=="              {    yylval.ptr = malloc(sizeof(struct node));
		       yylval.ptr->node_type = EQ;
                        return RELOP;

                  }







[();,\[\]{}&]		{	return *yytext;
			}

.	yyerror("ERROR");
%%
