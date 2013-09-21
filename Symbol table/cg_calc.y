%{
	/* Yacc program for generating code for an expression (using expression syntax tree)  */

/*Node type constants*/
/*#define PLUS 22
#define MINUS 33
#define MUL 44
#define DIV 55
#define REM 66
#define NEG 77
#define POW 88
#define NUM 99
#define MOD 98
#define ASSIGN_OP 97

*/
#define VOID 103
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

/*Function for looking up in symbol table  */
struct symbol_table * Lookup(char* name); 
 
/* To install an indentifier in symbol table */
void install(struct node* NODE, int size);





int regcount = 8;

/*To report an error */
void yyerror(char *);

/*To make a node in the tree*/
struct node* makenode(struct node *parent,struct node *left, struct node*right);

/*To recursively descend the tree and calculate the value of the expression*/
int calculate(struct node *t);



%}


%union 
{
	struct node *ptr;
	
};

%token <ptr> NUMBER
%token END DECLEND
%token <ptr> P M S D C R ID ASSIGN_OP 

%left P M
%left S D
%nonassoc C
%nonassoc R 
%nonassoc UMINUS

%type <ptr>  expr declare evaluate all_declarations declaration program
%start start
%%

start : program				         {		
			                                fp = fopen("sil.asm","a");
							fprintf(fp,"START");
                                                         calculate($1);
							fprintf(fp,"\nOUT R%d",use_reg(1));
							fprintf(fp,"\nHALT");                                                          
							fclose(fp);
							exit(1);
					         }
	;
program : declare END evaluate                 { struct node * t1 = malloc(sizeof(struct node));
                                                t1->node_type = VOID;
                                                $$ = makenode(t1,$1,$3); 
                                               }
        ;
declare : all_declarations DECLEND           { $$=$1; }
        ;

all_declarations : declaration all_declarations  { struct node * t1 = malloc(sizeof(struct node));
                                                      t1->node_type = VOID;
                                                     $$=makenode(t1,$1,$2); }
                 | {$$= NULL;} 
                 ;
declaration : ID ASSIGN_OP expr END               { install($1,4);
                                                  $$=makenode($2,$1,$3); } 
                                              
            ;  
evaluate   : expr END                           {$$=$1;}
           ;
expr : expr P expr                              {$$= makenode($2,$1,$3); }
     | expr M expr                              { $$=makenode($2,$1,$3); }
     | expr S expr				{ $$=makenode($2,$1,$3); }
     | expr R expr 				{ $$=makenode($2,$1,$3); }
     | expr D expr 				{ $$=makenode($2,$1,$3); }		
     |'(' expr ')' 				{ $$=$2;}
     | M expr %prec UMINUS                      {$$=makenode($1,$2,NULL);}
     | expr C expr                              { $$=makenode($2,$1,$3);  }
     | NUMBER                                   {$$= $1;}
     | ID                                       {$$= $1;}
     ;
 



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

int calculate(struct node *t)
{

	if(t!=NULL)
	{
		int ret;
                 if(t->node_type == VOID)
                {  calculate(t->left); 
                   
                   calculate(t->right);
                }
		else if(t->node_type==PLUS)
		{	//calculate(t->left);
                       // calculate(t->right);
                       if(t->left->node_type == VAR)
                         { res_reg(1);
                           int mptr = calculate(t->left);
                           fprintf(fp,"\nMOV R%d,[%d]",use_reg(1),mptr);
                           
                         }
                        else 
                         { calculate(t->left);
                         }
                       

                         if(t->right->node_type == VAR)
                         {  res_reg(1); 
                           int mptr = calculate(t->right);
                           fprintf(fp,"\nMOV R%d,[%d]",use_reg(1),mptr);
                            
                         }                        
                         if(t->right->node_type == NUM)
                         { calculate(t->right);
                         }
			
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
				//calculate(t->left);
				//calculate(t->right);
                             if(t->left->node_type == VAR)
                              {  res_reg(1);
                          	 int mptr = calculate(t->left);
                          	 fprintf(fp,"\nMOV R%d,[%d]",use_reg(1),mptr);
                           
                       	      }
                     	   else 
                              {
                                  calculate(t->left);
                              }
                       

                            if(t->right->node_type == VAR)
                       	      {  
                                 res_reg(1); 
                          	 int mptr = calculate(t->right);
                           	 fprintf(fp,"\nMOV R%d,[%d]",use_reg(1),mptr);
                            
                       	      }                        
                         if(t->right->node_type == NUM)
                             {
                                 calculate(t->right);
                             }
		       fprintf(fp,"\nSUB R%d,R%d",use_reg(2), use_reg(1));
		       free_reg(1);
			}
		}
		else if(t->node_type==MUL)
		{
			//calculate(t->left);
			//calculate(t->right);
                               if(t->left->node_type == VAR)
                              {  res_reg(1);
                          	 int mptr = calculate(t->left);
                          	 fprintf(fp,"\nMOV R%d,[%d]",use_reg(1),mptr);
                           
                       	      }
                     	   else 
                              {
                                  calculate(t->left);
                              }
                       

                            if(t->right->node_type == VAR)
                       	      {  
                                 res_reg(1); 
                          	 int mptr = calculate(t->right);
                           	 fprintf(fp,"\nMOV R%d,[%d]",use_reg(1),mptr);
                            
                       	      }                        
                          else
                             {
                                 calculate(t->right);
                             }
			fprintf(fp,"\nMUL R%d,R%d",use_reg(2), use_reg(1));
			free_reg(1);
		}
                else if(t->node_type==MOD)
		{
			//calculate(t->left);
			//calculate(t->right);
                         if(t->left->node_type == VAR)
                         { int mptr = calculate(t->left);
                           fprintf(fp,"\nMOV R%d,[%d]",use_reg(1),mptr);
                           res_reg(1);
                         }
                        if(t->left->node_type == NUM)
                         { calculate(t->left);
                         }
                         if(t->right->node_type == VAR)
                         { int mptr = calculate(t->right);
                           fprintf(fp,"\nMOV R%d,[%d]",use_reg(1),mptr);
                         }                        
                         if(t->right->node_type == NUM)
                         { calculate(t->right);
                         }
			fprintf(fp,"\nMOD R%d,R%d",use_reg(2), use_reg(1));
			free_reg(1);
		}
		else if(t->node_type==DIV)
		{
			//calculate(t->left);
			//calculate(t->right);
                        if(t->left->node_type == VAR)
                              {  res_reg(1);
                          	 int mptr = calculate(t->left);
                          	 fprintf(fp,"\nMOV R%d,[%d]",use_reg(1),mptr);
                           
                       	      }
                     	   else 
                              {
                                  calculate(t->left);
                              }
                       

                            if(t->right->node_type == VAR)
                       	      {  
                                 res_reg(1); 
                          	 int mptr = calculate(t->right);
                           	 fprintf(fp,"\nMOV R%d,[%d]",use_reg(1),mptr);
                            
                       	      }                        
                          else
                             {
                                 calculate(t->right);
                             }
			fprintf(fp,"\nDIV R%d,R%d",use_reg(2), use_reg(1));
			free_reg(1);
		}
		else if(t->node_type==REM)
		{
			//calculate(t->left);
			//calculate(t->right);
                      if(t->left->node_type == VAR)
                              {  res_reg(1);
                          	 int mptr = calculate(t->left);
                          	 fprintf(fp,"\nMOV R%d,[%d]",use_reg(1),mptr);
                           
                       	      }
                     	   else 
                              {
                                  calculate(t->left);
                              }
                       

                            if(t->right->node_type == VAR)
                       	      {  
                                 res_reg(1); 
                          	 int mptr = calculate(t->right);
                           	 fprintf(fp,"\nMOV R%d,[%d]",use_reg(1),mptr);
                            
                       	      }                        
                          else
                             {
                                 calculate(t->right);
                             }
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
                {    struct symbol_table *temp_node;
                     temp_node = Lookup(t->id);
                     return temp_node->mptr;             
                     // 
               }
                else if (t->node_type == ASSIGN)
                {  
                   
                   calculate(t->right);
                   int mptr = calculate(t->left);
                   fprintf(fp,"\nMOV [%d],R%d",mptr,use_reg(1));
                   free_reg(1);
                   //calculate(t->left);
                            
                   
                }
	
	else
		return 0;
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

