%{
	/* Yacc program for generating code for an expression (using expression syntax tree)  */
     /* Node type constants */
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
        char * id;
	struct node *left;
	struct node *right;
};

int regcount = -1;

/*To report an error */
void yyerror(char *);

/*To make a node in the tree*/
struct node* makenode(struct node *parent,struct node *left, struct node*right);

/*To print the expressoin tree */
void print_tree(struct node *root);

/* To evealuate the expression tree */
int evaluate_tree(struct node *root);


/*To recursively descend the tree and calculate the value of the expression*/
void calculate(struct node *t);

/*To calculate the static binding of single variable*/
int variable_binding(char *x);


%}


%union 
{
	struct node *ptr;
	
};

%token <ptr> NUMBER
%token END   
%token <ptr> P M S D C R READ WRITE ASSIGN_OP ID LT GT EQ

%left P M
%left S D
%nonassoc C
%nonassoc R 
%nonassoc UMINUS

%type <ptr> expr stmts stmt program
%start start
%%

start : program				    	{		
			                                fp = fopen("sil.asm","a");
							fprintf(fp,"START");
							fprintf(fp,"\nMOV SP,0");
							fprintf(fp,"\nMOV BP,0");
                                                        print_tree($1);
							fprintf(fp,"\nHALT");                                                          
							fclose(fp);
							exit(1);
					   	}
	;

program : stmts                                 {	$$=$1; }
        ;

stmts 	: stmt stmts				{  
							struct node * t1 = malloc(sizeof(struct node));
			                                t1->node_type = VOID;
                	                               	$$=makenode(t1,$1,$2); 
						} 
      	|                                       {  	$$= NULL;} 
      	;
	
stmt  	: ID ASSIGN_OP expr END                 {	$$=makenode($2,$1,$3);}
      	| READ '(' ID ')' END                   {	$$=makenode($1,$3,NULL);}
      	| WRITE '(' expr ')' END                {	$$=makenode($1,$3,NULL);}
      	; 

expr 	:   expr P expr				{	$$=makenode($2,$1,$3);}				
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

struct node *makenode(struct node *parent,struct node *left, struct node*right)
{
	parent->left=left;
	parent->right=right;

	return parent;
}

void res_reg(int no_reg)			//Reserves a higher numbered register
{
	regcount = regcount + no_reg;
}

void free_reg(int no_reg)			//Unlocks a higher numbered register
{
	regcount = regcount - no_reg;
}

int use_reg(int regno)				/* Uses the regno'th lower numbered register of the available reserved registers */
{
	return regcount-regno+1;		/* Example: Conceptually, use_reg(2) will return R0 if R0 and R1 were reserved i.e. 						         res_reg(2)*/
}

int variable_binding(char * a)
{  
	char x = *a;
	int y = 0;
   	y = (int)x;
  	return(y-97);
}

void print_tree(struct node * root)
{
        
        printf("(");
        printf(" %d ",root->node_type);
        if(root->left != NULL)
        { printf("\n");printf("\t");
          print_tree(root->left);
         }
        if (root->right !=NULL)
        { printf("\n");printf("\t");
         print_tree(root->right);
        }
        printf(")");
        
  
}

int evaluate_tree(struct node *root)
{  if(root->node_type == VOID)
    { evaluate_tree(root->left);
      evaluate_tree(root->right);
    }
   else if(root->node_type == NUM)
    {  return root->val;
    }
   else if(root->node_type == VAR)
   {
   

    



void calculate(struct node *t)
{
	if(t!=NULL)
	{
		int ret;
                if(t->node_type==VOID)
                {  
			calculate(t->left); 
	                calculate(t->right);
                }
		else if(t->node_type==PLUS)
		{	
			calculate(t->left);
			calculate(t->right);
 			fprintf(fp,"\nADD R%d,R%d",use_reg(2), use_reg(1));
			free_reg(1);		
		
		}
		else if(t->node_type==MINUS)
		{
			if(t->right == NULL)
			{	
				calculate(t->left);
				res_reg(1);
				fprintf(fp,"\nMOV R%d,-1",use_reg(1));
				fprintf(fp,"\nMUL R%d,R%d",use_reg(2),use_reg(1));
				free_reg(1);
			}
			else
			{
				calculate(t->left);
				calculate(t->right);
				fprintf(fp,"\nSUB R%d,R%d",use_reg(2), use_reg(1));
				free_reg(1);
			}
		}
		else if(t->node_type==MUL)
		{
			calculate(t->left);
			calculate(t->right);
			fprintf(fp,"\nMUL R%d,R%d",use_reg(2), use_reg(1));
			free_reg(1);
		}
                else if(t->node_type==MOD)
		{
			calculate(t->left);
			calculate(t->right);
			fprintf(fp,"\nMOD R%d,R%d",use_reg(2), use_reg(1));
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
		else if(t->node_type==NUM)
		{
			ret = t->val;
			res_reg(1);
			fprintf(fp,"\nMOV R%d,%d",use_reg(1), ret);		
		}
                else if (t->node_type == VAR)
                {    
		        int mptr = variable_binding(t->id);
                        res_reg(3);
			fprintf(fp,"\nMOV R%d,BP",use_reg(2));
			fprintf(fp,"\nMOV R%d,%d",use_reg(1),mptr);
			fprintf(fp,"\nADD R%d,R%d",use_reg(2),use_reg(1));
			fprintf(fp,"\nMOV R%d,[R%d]",use_reg(3),use_reg(2));
			free_reg(2);		
               	}
                else if (t->node_type == ASSIGN)
                {  
			int mptr = variable_binding(t->left->id);
                        res_reg(2);
			fprintf(fp,"\nMOV R%d,BP",use_reg(2));
			fprintf(fp,"\nMOV R%d,%d",use_reg(1),mptr);
			fprintf(fp,"\nADD R%d,R%d",use_reg(2),use_reg(1));
			free_reg(1);
			calculate(t->right);
                   	fprintf(fp,"\nMOV [R%d],R%d",use_reg(2),use_reg(1));
                   	free_reg(2);
                }
           	else if(t->node_type == WRITE_NODE)
                {  	
			calculate(t->left);
                    	fprintf(fp,"\nOUT R%d",use_reg(1));
                }
           	else if(t->node_type == READ_NODE)
                {    
			res_reg(1);			
			fprintf(fp,"\nIN R%d",use_reg(1));
                      	int mptr = variable_binding(t->left->id);
                        res_reg(2);
			fprintf(fp,"\nMOV R%d,BP",use_reg(1));
			fprintf(fp,"\nMOV R%d,%d",use_reg(2),mptr);
			fprintf(fp,"\nADD R%d,R%d",use_reg(1),use_reg(2));
			fprintf(fp,"\nMOV [R%d],R%d",use_reg(1),use_reg(3));
			free_reg(3);
                }
	}
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
