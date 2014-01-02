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

/*Global file pointer */
FILE *fp;

/*Data structure of a binary tree (which will be used to implement the expression syntax tree)*/
struct node
{
	int node_type;
	int val;
        char * id;
	struct node *P1,*P2,*P3;
	struct symbol_table *ENTRY;
        
};


/*Data structure of a symbol table*/
struct symbol_table
{ char * name;                            //name of the identifier
  int *value;                             //Address of the identifier in memory
  int mptr;                               //position in the memory for the code generation
  struct symbol_table *next;
} *root = NULL;

int off_set = 0;                          // this off_set will be used in implementing symbol table 

/*Function for looking up in symbol table  */
struct symbol_table * Lookup(char* name); 
 
/* To install an indentifier in symbol table */
void install(struct node* NODE);


/*To keep track of number of free registers */
int regcount = -1;

/*To report an error */
void yyerror(char *);

/*To make a node in the tree*/
struct node* makenode(struct node *parent,struct node *P1, struct node*P2,struct node* P3);

/*To recursively descend the tree and calculate the value of the expression*/
int calculate(struct node *t);
 
int ifcount = 0;            // to print labels for IF statements  for example 'I0' will indicate that IF statement has been used    						for 1 time

struct istack                    //stack data structure for mainting the correct labelling
{
 int value;
 struct istack *next;
}*itop;


void ipush(int count)
{
 struct istack *temp = malloc(sizeof(struct istack));
 temp->value = count;
 temp->next = itop;
 itop = temp;
 }

int ipop()
{
  struct istack *temp = itop;
  int res = temp->value;
  itop = itop->next;
  free(temp);
  return res; 
}

int whilecount = 0;     // to print labels for WHILE statements  for example 'w0' will indicate that WhILE statement has been 					used for 1 time.

struct wstack{
 int value;
 struct wstack *next;
}*wtop;

void wpush(int count)
{
 struct wstack *temp = malloc(sizeof(struct wstack));
 temp->value = count;
 temp->next = wtop;
 wtop = temp;
 }

int wpop()
{
  struct wstack *temp = wtop;
  int res = temp->value;
  wtop = wtop->next;
  free(temp);
  return res; 
}


%}


%union 
{
	struct node *ptr;
	
};

%token <ptr> NUMBER
%token END   START
%token <ptr> P M S D C R READ WRITE ASSIGN_OP ID RELOP WHILE  DO ENDWHILE
%token IF THEN ENDIF ELSE
%left P M
%left S D
%nonassoc C
%nonassoc R 
%nonassoc UMINUS

%type <ptr> expr stmts stmt program lexpr
%start start
%%

start : program				    {		
			                        fp = fopen("sil.asm","a");
			   			fprintf(fp,"START");
						fprintf(fp,"\nMOV SP,0");
						fprintf(fp,"\nMOV BP,0");
                                                calculate($1);
						fprintf(fp,"\nHALT");                                                          
						fclose(fp);
						exit(1);
					   	}
	;

program : START stmts  END                               {	$$=$2; }
        ;

stmts 	: stmts stmt				{  
							struct node * t1 = malloc(sizeof(struct node));
			                                t1->node_type = VOID;
                	                               	$$=makenode(t1,$1,$2,NULL); 
						} 
      	|                                       {  	$$= NULL;} 
      	;
	
stmt  	: ID ASSIGN_OP expr ';'                {        install($1); 
                                                        struct symbol_table* temp = Lookup($1->id);
                                                         $1->ENTRY = temp;
                                                       	$$=makenode($2,$1,$3,NULL);}

      	| READ '(' ID ')' ';'                  {         install($3);
                                                         struct symbol_table* temp = Lookup($3->id);
                                                         $3->ENTRY = temp;
                                                        $$=makenode($1,$3,NULL,NULL);}

      	| WRITE '(' expr ')' ';'                {	$$=makenode($1,$3,NULL,NULL);}

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

expr 	:  expr P expr				{	$$=makenode($2,$1,$3,NULL);}				
	| expr M expr				{	$$=makenode($2,$1,$3,NULL);}
	| expr S expr				{	$$=makenode($2,$1,$3,NULL);}
	|expr R expr                            {	$$=makenode($2,$1,$3,NULL);}
        | expr D expr				{	$$=makenode($2,$1,$3,NULL);}
	//| expr RELOP expr 		        {       $$=makenode($2,$1,$3,NULL);}
        | '(' expr ')'				{	$$=$2;}
	| M expr %prec UMINUS			{	$$=makenode($1,$2,NULL,NULL);}
	| expr C expr 				{	$$=makenode($2,$1,$3,NULL);}
        
	| NUMBER				{	$$=$1;}
        | ID                                    {      $$=$1;
                                                         struct symbol_table* temp = Lookup($$->id);
                                                         $$->ENTRY = temp;
                                                               }
	;


%%

#include "lex.yy.c"

struct node *makenode(struct node *parent,struct node *P1, struct node*P2,struct node*P3)
{
	parent->P1=P1;
	parent->P2=P2;
        parent->P3=P3;

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
		


void install(struct node * NODE)
{ 
  struct symbol_table * temp = malloc(sizeof(struct symbol_table));
  temp->name = NODE->id;
  temp->value = malloc(sizeof(int));
  temp->mptr = off_set;
  off_set = off_set + 1;
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

int calculate(struct node *t)
{
	if(t!=NULL)
	{     int result;
		int ret;
                if(t->node_type==VOID)
                {  
			calculate(t->P1); 
	                calculate(t->P2);
                }
		else if(t->node_type==PLUS)
		{	
			result = calculate(t->P1) + calculate(t->P2);
			
 			fprintf(fp,"\nADD R%d,R%d",use_reg(2), use_reg(1));
			free_reg(1);		
		
		}
		else if(t->node_type==MINUS)
		{
			if(t->P2 == NULL)
			{	
				result = calculate(t->P1);
				res_reg(1);
				fprintf(fp,"\nMOV R%d,-1",use_reg(1));
				fprintf(fp,"\nMUL R%d,R%d",use_reg(2),use_reg(1));
				free_reg(1);
			}
			else
			{
				result = calculate(t->P1) - calculate(t->P2); 
				
				fprintf(fp,"\nSUB R%d,R%d",use_reg(2), use_reg(1));
				free_reg(1);
			}
		}
		else if(t->node_type==MUL)
		{
			result = calculate(t->P1) * calculate(t->P2);
			fprintf(fp,"\nMUL R%d,R%d",use_reg(2), use_reg(1));
			free_reg(1);
		}
                else if(t->node_type==MOD)
		{
			result = calculate(t->P1) % calculate(t->P2);
			fprintf(fp,"\nMOD R%d,R%d",use_reg(2), use_reg(1));
			free_reg(1);
		}
		else if(t->node_type==DIV)
		{
			result = calculate(t->P1) / calculate(t->P2);
			fprintf(fp,"\nDIV R%d,R%d",use_reg(2), use_reg(1));
			free_reg(1);
		}
		
		else if(t->node_type==NUM)
		{       result = t->val;
			ret = t->val;
			res_reg(1);
			fprintf(fp,"\nMOV R%d,%d",use_reg(1), ret);		
		}
                else if (t->node_type == VAR)
                {      result =*(t->ENTRY->value);
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
	                temp_node = Lookup(t->P1->id);
                        int mptr = temp_node->mptr;
                      
                       *(temp_node->value) = calculate(t->P3);
                         res_reg(2);
			fprintf(fp,"\nMOV R%d,BP",use_reg(2));
			fprintf(fp,"\nMOV R%d,%d",use_reg(1),mptr);
			fprintf(fp,"\nADD R%d,R%d",use_reg(2),use_reg(1));
			free_reg(1);
			calculate(t->P2);
                   	fprintf(fp,"\nMOV [R%d],R%d",use_reg(2),use_reg(1));
                   	free_reg(2);
                } 
                else if (t->node_type == IF_THEN)
                {   
                           fprintf(fp,"\nI%d:", ifcount);
			   ipush(ifcount);
			   ifcount++;   
                           free_reg(1);

                           calculate(t->P1);
                            
                           res_reg(1);
                           fprintf(fp,"\nJZ R%d,E%d", use_reg(1),ifcount-1);
			   free_reg(1);
                           
                           calculate(t->P2);
                           
                           fprintf(fp,"\nJMP EI%d", itop->value);
			   fprintf(fp,"\nE%d:", itop->value);
                           calculate(t->P3);
                           fprintf(fp,"\nEI%d:", ipop());
                            
                                                  
	        }
                else if (t->node_type == WHILE_LOOP)
                {          fprintf(fp,"\nW%d:", whilecount);
			   wpush(whilecount);
			   whilecount++;
                           free_reg(1);

                          calculate(t->P1);

                          res_reg(1);
                          fprintf(fp,"\nJZ R%d,EW%d", use_reg(1),whilecount-1);
                          free_reg(2);
 
                          calculate(t->P2);
                          fprintf(fp,"\nJMP W%d", wtop->value);
			  fprintf(fp,"\nEW%d:", wpop());

                }

           	else if(t->node_type == WRITE_NODE)
                {  	
			calculate(t->P1);
                    	fprintf(fp,"\nOUT R%d",use_reg(1));
                        free_reg(1);
                }
           	else if(t->node_type == READ_NODE)
                {    
			res_reg(1);			
			fprintf(fp,"\nIN R%d",use_reg(1));
                        struct symbol_table *temp_node;
                         temp_node = Lookup(t->P1->id);
                      	 int mptr = temp_node->mptr;
                        res_reg(2);
			fprintf(fp,"\nMOV R%d,BP",use_reg(1));
			fprintf(fp,"\nMOV R%d,%d",use_reg(2),mptr);
			fprintf(fp,"\nADD R%d,R%d",use_reg(1),use_reg(2));
			fprintf(fp,"\nMOV [R%d],R%d",use_reg(1),use_reg(3));
			free_reg(3);
                }
               
             else if (t->node_type == LT)
                {    
                      
                       res_reg(2);
                      if(calculate(t->P1) < calculate(t->P2))
  			   result = T;
  			else  
  			   result =  F;
                       
                      fprintf(fp,"\nLT  R%d,R%d",use_reg(2),use_reg(1));
                                          
                      free_reg(2);
                      
                     
                } 
               else if (t->node_type == GT)
                {     res_reg(2);
                    
                       if(calculate(t->P1) > calculate(t->P2))
  			   result = T;
  			else  
  			   result =  F;
                      fprintf(fp,"\nGT  R%d,R%d",use_reg(2),use_reg(1));
                     
                   
                      free_reg(2);
                      
                     
                }

              else if (t->node_type == EQ)
                {     res_reg(2);
                     
                    if(calculate(t->P1) < calculate(t->P2))
  			   result = T;
  			else  
  			   result =  F;
                     
                      fprintf(fp,"\nEQ  R%d,R%d",use_reg(2),use_reg(1));
                     
                  
                     
                      free_reg(2);
                       
                      
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
