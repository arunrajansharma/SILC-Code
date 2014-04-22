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
	#define LT 104
	#define GT 105
	#define EQ 106 
        #define LE 107
        #define GE 108
        #define NE 109
        #define READ_NODE 145
        #define WRITE_NODE 150
        #define AND_NODE 151
        #define OR_NODE 152
        #define NOT_NODE 153
     
%}


number  [0-9]+
alpha   [a-z]+
	

%%

"if"        { return IF ;}
"endif"     { return ENDIF ; }
"then"      { return THEN ;}
"else"      { return ELSE ;}
"while"      {return WHILE;}
"endwhile"    {return ENDWHILE;}
"return"      { return RETURN ;}
"main"  	{ return MAIN;   }
"do"           {return DO;}
"decl"         {return DECL; }
"enddecl"       {return ENDDECL ;}
"begin"         {return BEG ;}
"end"           {return END ;}
"integer"               {  	return INT;    }
"boolean"               {  	return BOOL;   }

[ \t\n]+		{
      			}
"+"		{
			yylval.ptr = malloc(sizeof(struct node));			
			yylval.ptr->NODE_TYPE = PLUS; 
                        yylval.ptr->TYPE = INTEGER;			
			return P;
		}
		
"-"		{
			yylval.ptr = malloc(sizeof(struct node));			
			yylval.ptr->NODE_TYPE = MINUS;
            		yylval.ptr->TYPE = INTEGER;	
			return S;
		}
"*"		{
			yylval.ptr = malloc(sizeof(struct node));			
			yylval.ptr->NODE_TYPE = MUL;
                        yylval.ptr->TYPE = INTEGER;
			return M;
		}
"/"		{
			yylval.ptr = malloc(sizeof(struct node));
			yylval.ptr->NODE_TYPE = DIV;
                        yylval.ptr->TYPE = INTEGER;			
			return D;
		}
"%"            {        yylval.ptr = malloc(sizeof(struct node ));
                        yylval.ptr->NODE_TYPE = MOD;
                        yylval.ptr->TYPE = INTEGER;
                        return R;
                 }
\^		{
			yylval.ptr = malloc(sizeof(struct node));
			yylval.ptr->NODE_TYPE = POW;
                        yylval.ptr->TYPE = INTEGER;			
			return C;
		}
"read"         {        yylval.ptr = malloc(sizeof(struct node));
			yylval.ptr->NODE_TYPE = READ_NODE;			
			return READ;
                
               }
"write"        {        yylval.ptr = malloc(sizeof(struct node));
			yylval.ptr->NODE_TYPE = WRITE_NODE;			
			return WRITE;

               }
"TRUE"         {        yylval.ptr =  malloc(sizeof(struct node));
                        yylval.ptr->VALUE = 1;
                        yylval.ptr->TYPE = BOOLEAN;
                        yylval.ptr->NODE_TYPE = NUM;
                        return BOOLEAN_NUMBER;                     
                        
                }
"FALSE"        {        yylval.ptr =  malloc(sizeof(struct node));
                        yylval.ptr->VALUE = 0;
                        yylval.ptr->TYPE = BOOLEAN;
                        yylval.ptr->NODE_TYPE = NUM;
                        return BOOLEAN_NUMBER;
               }
 "AND"     {     yylval.ptr =  malloc(sizeof(struct node));
                    yylval.ptr->VALUE = 0;
                    yylval.ptr->TYPE = BOOLEAN;
                    yylval.ptr->NODE_TYPE = AND_NODE;
                    return AND ;
              }
"OR"         {      yylval.ptr =  malloc(sizeof(struct node));
                    yylval.ptr->VALUE = 0;
                    yylval.ptr->TYPE = BOOLEAN;
                    yylval.ptr->NODE_TYPE = OR_NODE;
                    return OR ;
             }
"NOT"       {       yylval.ptr =  malloc(sizeof(struct node));
                    yylval.ptr->VALUE = 0;
                    yylval.ptr->TYPE = BOOLEAN;
                    yylval.ptr->NODE_TYPE = NOT_NODE;
                    return NOT ; 
            }

{alpha}        {        
                      
                        yylval.ptr = malloc(sizeof(struct node));
                        yylval.ptr->NAME=malloc(sizeof(yytext)); 
                        strcpy(yylval.ptr->NAME,yytext);
                        yylval.ptr->NODE_TYPE = VAR;
		        return ID;
	       }
	
		 
"="              {     yylval.ptr = malloc(sizeof(struct node));
		       yylval.ptr->NODE_TYPE = ASSIGN;
                      yylval.ptr->TYPE = VOID;
		       return ASSIGN_OP;
		 }
		  
{number}	 {
			yylval.ptr = malloc(sizeof(struct node));
			yylval.ptr->VALUE = atoi(yytext);
			yylval.ptr->NODE_TYPE = NUM;	
			yylval.ptr->TYPE=INTEGER;		
			return NUMBER;
		 }
"<="              {     yylval.ptr = malloc(sizeof(struct node));
		        yylval.ptr->NODE_TYPE = LE;
                       yylval.ptr->TYPE = BOOLEAN;
		       return RELOP;

                 }

"<"              {     yylval.ptr = malloc(sizeof(struct node));
		       yylval.ptr->NODE_TYPE = LT;
                       yylval.ptr->TYPE = BOOLEAN;
		       return RELOP;

                 }



">"              {     yylval.ptr = malloc(sizeof(struct node));
		       yylval.ptr->NODE_TYPE = GT;
                       yylval.ptr->TYPE = BOOLEAN;
                        return RELOP;

                 }

">="              {     yylval.ptr = malloc(sizeof(struct node));
		        yylval.ptr->NODE_TYPE = GE;
                       yylval.ptr->TYPE = BOOLEAN;
		        return RELOP;

                  }

"=="              {    yylval.ptr = malloc(sizeof(struct node));
		       yylval.ptr->NODE_TYPE = EQ;
                      yylval.ptr->TYPE = BOOLEAN;  
                      return RELOP;

                  }

"!="              {    yylval.ptr = malloc(sizeof(struct node));
		       yylval.ptr->NODE_TYPE = NE;
                       yylval.ptr->TYPE = BOOLEAN; 
		       return RELOP;

                 }







[();,\[\]{}&]		{	return *yytext;
			}

.	yyerror("ERROR");
%%
