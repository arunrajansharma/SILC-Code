%{
	/* Yacc program for evaluating an expressions which contains just single variable (using expression syntax tree)  */

/*Node type constants*/
#define PLUS 22
#define MINUS 33
#define MUL 44
#define DIV 55
#define NEG 77
#define POW 88
#define NUM 99

#define MOD 102
#define VOID 103
#define IF_THEN 107
#define IF_THEN_ELSE 108
#define WHILE_LOOP 109
#define T 1
#define F 0

/*Header files */
#include<stdio.h>
#include<stdlib.h> 


/*Data structure of a binary tree (which will be used to implement the expression syntax tree)*/
struct node
{
	int node_type;
	int val;
        char * id;
	struct node *P1;
	struct node *P2;
        struct node *P3;
};


/*To report an error */
void yyerror(char *);

/*To make a node in the tree*/
struct node* makenode(struct node *parent,struct node *P1, struct node*P2,struct node*P3);

/*To recursively descend the tree and calculate the value of the expression*/
int calculate(struct node *t);

/*To calculate the static binding of single variable*/
int variable_binding(char *x);

int my_array[26]; // to store value for a,b,c....z if it occurs in programe

/* TO calculate the power for example power(2,3) mean 2^3 which is equal to 8  */
int power(int a,int b);



%}


%union 
{
	struct node *ptr;
	
};

%token <ptr> NUMBER
%token END  START
%token <ptr> P M S D C R READ WRITE ASSIGN_OP ID  RELOP
%token IF THEN ENDIF ELSE WHILE DO ENDWHILE

%left P S
%left M D
%nonassoc C
%nonassoc R 
%nonassoc UMINUS

%type <ptr> expr stmts stmt program lexpr
%start start
%%

start : program				    	{		
			                               calculate($1);
							                                              
							exit(1);
					   	}
	;

program : START stmts END                                {	$$=$2; }
        ;

stmts 	: stmts stmt				{  
							struct node * t1 = malloc(sizeof(struct node));
			                                t1->node_type = VOID;
                	                               	$$=makenode(t1,$1,$2,NULL); 
						} 
      	|                                       {  	$$= NULL;} 
      	;
	
stmt  	: ID ASSIGN_OP expr ';'                 {	$$=makenode($2,$1,$3,NULL);    }
      	| READ '(' ID ')'   ';'                 {	$$=makenode($1,$3,NULL,NULL);}
      	| WRITE '(' expr ')' ';'                {	$$=makenode($1,$3,NULL,NULL); }

        | IF '('lexpr')' THEN stmts ENDIF ';'            {   struct node * t1 = malloc(sizeof(struct node));
	                                                     t1->node_type = IF_THEN;
 						             $$=makenode(t1,$3,$6,NULL); }
        |IF '('lexpr')' THEN stmts ELSE stmts ENDIF ';'  {   struct node * t1 = malloc(sizeof(struct node));
	                                                     t1->node_type = IF_THEN;
 						             $$=makenode(t1,$3,$6,$8); }
        |WHILE '('lexpr')' DO stmts ENDWHILE ';'          {   struct node * t1 = malloc(sizeof(struct node));
	                                                     t1->node_type = WHILE_LOOP;
 						             $$=makenode(t1,$3,$6,NULL); }
      	;

lexpr   : expr RELOP expr  {$$=makenode($2,$1,$3,NULL); }
        ; 

expr 	:expr P expr				{	$$=makenode($2,$1,$3,NULL);}				
	| expr M expr				{	$$=makenode($2,$1,$3,NULL);}
	| expr S expr				{	$$=makenode($2,$1,$3,NULL);}
	|expr R expr                            {	$$=makenode($2,$1,$3,NULL);}
        | expr D expr				{	$$=makenode($2,$1,$3,NULL);}
	| '(' expr ')'				{	$$=$2;}
	| M expr %prec UMINUS			{	$$=makenode($1,$2,NULL,NULL);}
	| expr C expr 				{	$$=makenode($2,$1,$3,NULL);}		
	| NUMBER				{	$$=$1;}
        | ID                                    {	$$=$1;}
	;


%%

#include "lex.yy.c"

struct node *makenode(struct node *parent,struct node *P1, struct node*P2,struct node * P3)
{
	parent->P1=P1;
	parent->P2=P2;
        parent->P3=P3;

	return parent;
}



int variable_binding(char * a)
{  
	char x = *a;
	int y = 0;
   	y = (int)x;
  	return(y-97);
}

int power(int a,int b)
{  int c = 1;
  while(b>0)
   {  c = c*a; 
      b--;
    }
return c ;
}


int calculate(struct node *t)
{
	if(t!=NULL)
	{       int result ;
		int ret;
               
                if(t->node_type==VOID)
                {  
			calculate(t->P1); 
	                calculate(t->P2);
                }
		else if(t->node_type==PLUS)
		{	
			result = calculate(t->P1) + calculate(t->P2);			
					
		}
		else if(t->node_type==MINUS)
		{
			if(t->P2 == NULL)
			{	
				result =  (-1)*calculate(t->P1);
			}
			else
			{
				result = calculate(t->P1) - calculate(t->P2); 
			}
		}
		else if(t->node_type==MUL)
		{
			result = calculate(t->P1) * calculate(t->P2);
		}
                else if(t->node_type==MOD)
		{
			result = calculate(t->P1) % calculate(t->P2);
		}
		else if(t->node_type==DIV)
		{
			result = calculate(t->P1) / calculate(t->P2);
		}
                else if(t->node_type==POW)
		{
			result = power(calculate(t->P1),calculate(t->P2));
			
		}
		
		else if(t->node_type==NUM)
		{       result = t->val;
			
		}
             
                else if (t->node_type == VAR)
                {      
		            int mptr = variable_binding(t->id);
                            result = my_array[mptr];
                     
               	} 
                else if (t->node_type == ASSIGN)
                {         int mptr = variable_binding(t->P1->id);
                          
                        
			my_array[mptr] =calculate(t->P2);

                } 
               
           	else if(t->node_type == WRITE_NODE)
                {  	
			 
			printf("%d\n", calculate(t->P1));
                } 
                
           	else if(t->node_type == READ_NODE)
                {      
                      
		         int mptr = variable_binding(t->P1->id);
                         fflush(stdin);
                
			
                     scanf("%d",&my_array[mptr]);
                }
 
                  else if (t->node_type == IF_THEN)
                {   
                 	if(calculate(t->P1) == 1)
                             calculate(t->P2);
			else
                          calculate(t->P3);
                            
                                                  
	        }
                else if (t->node_type == WHILE_LOOP)
                {
                       while(calculate(t->P1) == 1)
                           {  calculate(t->P2);
                           }
                 } 
                else if (t->node_type == LT)
                {    
                     
                      if(calculate(t->P1) < calculate(t->P2))
  			   result = T;
  			else  
  			   result =  F;
                      
                     
                } 
               else if (t->node_type == GT)
                {     
                       if(calculate(t->P1) > calculate(t->P2))
  			   result = T;
  			else  
  			   result =  F;
                      
                     
                }

              else if (t->node_type == EQ)
                {
                     
                    if(calculate(t->P1) < calculate(t->P2))
  			   result = T;
  			else  
  			   result =  F;
                     
                      }
               
          return result;

	} 
         else  return 0 ;
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
