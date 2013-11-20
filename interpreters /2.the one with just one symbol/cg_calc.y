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
};


/*To report an error */
void yyerror(char *);

/*To make a node in the tree*/
struct node* makenode(struct node *parent,struct node *P1, struct node*P2);

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
%token END   
%token <ptr> P M S D C R READ WRITE ASSIGN_OP ID 

%left P S
%left M D
%nonassoc C
%nonassoc R 
%nonassoc UMINUS

%type <ptr> expr stmts stmt program
%start start
%%

start : program				    	{		
			                               calculate($1);
							                                              
							exit(1);
					   	}
	;

program : stmts                                 {	$$=$1; }
        ;

stmts 	: stmts stmt				{  
							struct node * t1 = malloc(sizeof(struct node));
			                                t1->node_type = VOID;
                	                               	$$=makenode(t1,$1,$2); 
						} 
      	|                                       {  	$$= NULL;} 
      	;
	
stmt  	: ID ASSIGN_OP expr ';'                 {	$$=makenode($2,$1,$3);    }
      	| READ '(' ID ')'   ';'                 {	$$=makenode($1,$3,NULL);}
      	| WRITE '(' expr ')' ';'                {	$$=makenode($1,$3,NULL); }
      	; 

expr 	:expr P expr				{	$$=makenode($2,$1,$3);}				
	| expr M expr				{	$$=makenode($2,$1,$3);}
	| expr S expr				{	$$=makenode($2,$1,$3);}
	|expr R expr                            {	$$=makenode($2,$1,$3);}
        | expr D expr				{	$$=makenode($2,$1,$3);}
	| '(' expr ')'				{	$$=$2;}
	| M expr %prec UMINUS			{	$$=makenode($1,$2,NULL);}
	| expr C expr 				{	$$=makenode($2,$1,$3);}		
	| NUMBER				{	$$=$1;}
        | ID                                    {	$$=$1;}
	;


%%

#include "lex.yy.c"

struct node *makenode(struct node *parent,struct node *P1, struct node*P2)
{
	parent->P1=P1;
	parent->P2=P2;

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
