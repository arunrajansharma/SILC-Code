%{
	/* Yacc program for generating code for an expression (using expression syntax tree)  */


#define VOID 103
#define IF_THEN 107
#define IF_THEN_ELSE 108


/*Header files */
#include<stdio.h>
#include<stdlib.h> 

/*Global file pointer */
FILE *fp;

/*Data structure of a binary tree (which will be used to implement the expression syntax tree)*/
struct node
{       char* id;
	int node_type;
	int val;
	struct node *left;
	struct node *right;
};

/*Data structure of a symbol table*/
struct symbol_table
{ char * name;
  int size;
  int mptr;
  struct symbol_table *next;
} *root = NULL;

int off_set = 0;
int label = 5;

/*Function for looking up in symbol table  */
struct symbol_table * Lookup(char* name); 
 
/* To install an indentifier in symbol table */
void install(struct node* NODE, int size);

/*To keep track of number of free registers */
int regcount = 8;

/*To report an error */
void yyerror(char *);

/*To make a node in the tree*/
struct node* makenode(struct node *parent,struct node *left, struct node*right);

/*To recursively descend the tree and calculate the value of the expression*/
void calculate(struct node *t);



%}


%union 
{
	struct node *ptr;
	
};

%token <ptr> NUMBER
%token END DECLEND
%token <ptr> P M S D C R ID ASSIGN_OP  LT GT EQ
%token IF THEN ENDIF ELSE

%left P M
%left S D
%nonassoc C
%nonassoc R 
%nonassoc UMINUS
%nonassoc LT GT EQ

%type <ptr>  aexpr lexpr
%type <ptr> declare evaluate all_declarations declaration program if_statement 
%start start
%%

start : program				    	{		
			                                fp = fopen("sil.asm","a");
							fprintf(fp,"START");
							fprintf(fp,"\nMOV SP,0");
							fprintf(fp,"\nMOV BP,0");
                                                        calculate($1);
							fprintf(fp,"\nOUT R%d",use_reg(1));
							fprintf(fp,"\nHALT");                                                          
							fclose(fp);
							exit(1);
					   	}
	;

program : declare END evaluate               	{ 
							struct node * t1 = malloc(sizeof(struct node));
	                                                t1->node_type = VOID;
	                                                $$ = makenode(t1,$1,$3); 
                                               	}
        ;

declare : all_declarations DECLEND		{ $$=$1; }
        ;

all_declarations : declaration all_declarations { 
							struct node * t1 = malloc(sizeof(struct node));
		                                        t1->node_type = VOID;
                                                     	$$=makenode(t1,$1,$2); 
						}
                 | 				{$$= NULL;} 
                 ;

declaration : ID ASSIGN_OP aexpr END             { 
							install($1,4);
	                                                $$=makenode($2,$1,$3); 
						} 
                                              
            ;  

evaluate   : aexpr END                           {$$=$1;}
           | if_statement END                    {$$=$1;}
           ;


aexpr : aexpr P aexpr                           {$$= makenode($2,$1,$3);}
     | aexpr M aexpr                            {$$=makenode($2,$1,$3); }
     | aexpr S aexpr				{$$=makenode($2,$1,$3); }
     | aexpr R aexpr 				{$$=makenode($2,$1,$3); }
     | aexpr D aexpr 				{$$=makenode($2,$1,$3); }		
     |'(' aexpr ')' 				{$$=$2;}
     | M aexpr %prec UMINUS                     {$$=makenode($1,$2,NULL);}
     | aexpr C aexpr                            {$$=makenode($2,$1,$3);  }
     | NUMBER                                   {$$= $1;}
     | ID                                       {$$= $1;}
     ;
 
lexpr   :  aexpr LT aexpr                       { $$= makenode($2,$1,$3);}
	| aexpr GT aexpr                        { $$= makenode($2,$1,$3);}
	| aexpr EQ aexpr                        {$$= makenode($2,$1,$3);}
	;

if_statement : IF lexpr THEN aexpr ENDIF          { struct node * t1 = malloc(sizeof(struct node));
	                                            t1->node_type = IF_THEN;
 						    $$=makenode(t1,$2,$4);
                                         	  }
             | IF lexpr THEN aexpr ELSE aexpr ENDIF { struct node * t1 = malloc(sizeof(struct node));
                                                   t1->node_type = IF_THEN;
                                                   struct node * t2 = malloc(sizeof(struct node));
                                                   t2 = makenode(t1,$2,$4);
                                                   struct node * t3 = malloc(sizeof(struct node));
                                                   t3->node_type = IF_THEN_ELSE;
                                                   $$ = makenode(t3,t2,$6);
                                                  }
                                        
                                                   		

%%

#include "lex.yy.c"

struct node *makenode(struct node *parent,struct node *left, struct node*right)
{
	parent->left=left;
	parent->right=right;

	return parent;
}

void install(struct node * NODE,int size)
{ 
  struct symbol_table * temp = malloc(sizeof(struct symbol_table));
  temp->name = NODE->id;
  temp->size = size ;
  temp->mptr = off_set;
  off_set = off_set + size;
  temp->next = root;
  root = temp;
}

struct symbol_table * Lookup(char * name)
{
  struct symbol_table *temp;
  temp=root;  
  while(temp !=NULL && (strcmp(temp->name,name)!=0))
    { 
      temp=temp->next;
    } 
  return temp;
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

void res_label(int no_label)	
{
	label=label-no_label;					//reserves the higher registers
}

void free_label(int no_label)
{
	label=label+no_label;					//frees the lower registers
}

int use_label(int regno)
{
	return label+regno-1;					
}

void calculate(struct node *t)
{

	if(t!=NULL)
	{
                if(t->node_type == VOID)
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
			{	calculate(t->right);
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
		else if(t->node_type==NUM)
		{
			int val = t->val;
			res_reg(1);
			fprintf(fp,"\nMOV R%d,%d",use_reg(1), val);		
		}
              	else if (t->node_type == VAR)
                {    
			struct symbol_table *temp_node;
	                temp_node = Lookup(t->id);
                        int mptr = temp_node->mptr;
                        res_reg(3);
			fprintf(fp,"\nMOV R%d,BP",use_reg(2));
			fprintf(fp,"\nMOV R%d,%d",use_reg(1),mptr);
			fprintf(fp,"\nADD R%d,R%d",use_reg(2),use_reg(1));
			fprintf(fp,"\nMOV R%d,[R%d]",use_reg(3),use_reg(2));
			free_reg(2);		
               	}
                else if (t->node_type == ASSIGN)
                {  
			struct symbol_table *temp_node;
	                temp_node = Lookup(t->left->id);
                        int mptr = temp_node->mptr;
                        res_reg(2);
			fprintf(fp,"\nMOV R%d,BP",use_reg(2));
			fprintf(fp,"\nMOV R%d,%d",use_reg(1),mptr);
			fprintf(fp,"\nADD R%d,R%d",use_reg(2),use_reg(1));
			free_reg(1);
			calculate(t->right);
                   	fprintf(fp,"\nMOV [R%d],R%d",use_reg(2),use_reg(1));
                   	free_reg(2);
                }
             else if (t->node_type == IF_THEN)
                {   calculate(t->left);
                  
                    calculate(t->right);
                    res_label(1);
                    fprintf(fp,"\nJMP L%d",use_label(1));
                    
                    free_label(1);

                }

        else if (t->node_type == IF_THEN_ELSE)
                {   calculate(t->left);
                    fprintf(fp,"\nL%d:",use_label(1));        
                    calculate(t->right);
                    res_label(1);
                    fprintf(fp,"\nL%d:",use_label(1));
                    
                }
    
             
             else if (t->node_type == CONDITIONAL_LT)
                {     res_reg(2);
                      res_label(1);
                      calculate(t->left);
                      calculate(t->right);
                      fprintf(fp,"\nLT  R%d,R%d",use_reg(2),use_reg(1));
                      fprintf(fp,"\nJZ  R%d, L%d",use_reg(2),use_label(1));
                     // free_label(1);
                      free_reg(2);
                      
                     
                } 
               else if (t->node_type == CONDITIONAL_GT)
                {     res_reg(2);
                      res_label(1);
                      calculate(t->left);
                      calculate(t->right);
                      fprintf(fp,"\nGT  R%d,R%d",use_reg(2),use_reg(1));
                      fprintf(fp,"\nJZ  R%d, L%d",use_reg(2),use_label(1));
                   //   free_label(1);
                      free_reg(2);
                      
                     
                }

              else if (t->node_type == CONDITIONAL_EQ)
                {     res_reg(2);
                      res_label(1);
                      calculate(t->left);
                      calculate(t->right);
                      fprintf(fp,"\nEQ  R%d,R%d",use_reg(2),use_reg(1));
                      fprintf(fp,"\nJZ  R%d, L%d",use_reg(2),use_label(1));
                  
                     // free_label(1);
                      free_reg(2);
                       
                      
                     
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

