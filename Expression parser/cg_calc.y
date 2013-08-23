%{
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
	struct node *left;
	struct node *right;
};

int regcount = 8;

/*To report an error */
void yyerror(char *);

/*To calculate power*/
double power(int a, int b);

/*To make a leaf in the tree*/
struct node* makeLeaf(int node_type,int val);

/*To make a node in the tree*/
struct node* makenode(int node_type,struct node *left, struct node*right);

/*To recursively descend the tree and calculate the value of the expression*/
int calculate(struct node *t);


%}


%union 
{
	struct node *ptr;
	
};

%token <ptr> NUMBER
%token END 
%token <ptr> P M S D R C

%left '+' '-'
%left '*' '/'
%left '%'
%nonassoc '^' 
%nonassoc UMINUS

%type <ptr> expr 
%start program

%%

program : expr END				{					
							
			                                fp = fopen("sil.asm","a");
							fprintf(fp,"START");
                                                        calculate($1); 
							fprintf(fp,"\nOUT R%d",use_reg(1));
							fprintf(fp,"\nHALT");                                                          
							fclose(fp);
							exit(1);
						}
	

expr :   expr P expr				{$$=makenode($2->node_type,$1,$3);	}				
	| expr M expr				{$$=makenode($2->node_type,$1,$3);	}
	| expr S expr				{$$=makenode($2->node_type,$1,$3);	}
	| expr D expr				{$$=makenode($2->node_type,$1,$3);	}
	| expr R expr				{$$=makenode($2->node_type,$1,$3);	}
	| '(' expr ')'				{$$=$2;					}
	| M expr %prec UMINUS			{$$=makenode($1->node_type,$2,NULL);	}
	| expr C expr 				{$$=makenode($2->node_type,$1,$3);			}		
	| NUMBER				{$$=makeLeaf($1->node_type,$1->val);	}

	;


%%

#include "lex.yy.c"

double power(int a,int b)
{
	int i;
	double c=1;	
	for(i=0;i<b;i++)
		c=c*a;
	return c;
}

struct node* makeLeaf(int node_type,int val)
{
	struct node *ptr=malloc(sizeof(struct node));
	
	ptr->node_type=node_type;
	ptr->val=val;
	ptr->left=NULL;
	ptr->right=NULL;

	return ptr;
}

struct node *makenode(int node_type,struct node *left, struct node*right)
{
	struct node *ptr=malloc(sizeof(struct node));

	ptr->node_type=node_type;
	ptr->left=left;
	ptr->right=right;

	return ptr;
}

void res_reg(int no_reg)	
{
	regcount=regcount-no_reg;					//reserves the higher registers
}

void free_reg(int no_reg)
{
	regcount=regcount+no_reg;					//frees the lower registers
}

int use_reg(int regno)
{
	return regcount+regno-1;					
}

int calculate(struct node *t)
{

	if(t!=NULL)
	{
		int ret;
		if(t->node_type==PLUS)
		{	
			calculate(t->left);
			calculate(t->right);
 			fprintf(fp,"\nADD R%d,R%d",use_reg(2), use_reg(1));
			free_reg(1);		
		
		}
		else if(t->node_type==NEG)
		{
			calculate(t->left);
			res_reg(1);
			fprintf(fp,"\nMOV R%d,-1",use_reg(1));
			fprintf(fp,"\nMUL R%d,R%d",use_reg(2),use_reg(1));
			free_reg(1);
		}
		
		else if(t->node_type==MINUS)
		{
			calculate(t->left);
			calculate(t->right);
			fprintf(fp,"\nSUB R%d,R%d",use_reg(2), use_reg(1));
			free_reg(1);
		}
		else if(t->node_type==MUL)
		{
			calculate(t->left);
			calculate(t->right);
			fprintf(fp,"\nMUL R%d,R%d",use_reg(2), use_reg(1));
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
		else if(t->node_type==POW)
		{
			int a = calculate(t->left);
			int b = calculate(t->right);
			ret = (int)power(a,b);
		}
		else if(t->node_type==NUM)
		{
			ret = t->val;
			res_reg(1);
			fprintf(fp,"\nMOV R%d,%d",use_reg(1), ret);		
		}
		return 1;
	}
	
	else
		return 0;
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

