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
#define IF_THEN 111
#define WHILE_LOOP 222
#define T 3
#define F 0

#define VOID 0
#define INTEGER 1
#define BOOLEAN 2

/*Header files */
#include<stdio.h>
#include<stdlib.h> 

/*Global file pointer */
FILE *fp;

/*Data structure of a binary tree (which will be used to implement the expression syntax tree)*/
struct node
{        int TYPE; //
	int NODE_TYPE;
	char * NAME;
        int VALUE;
        
	struct node *P1,*P2,*P3;
	struct symbol_table *ENTRY;
        
};


/*Data structure of a symbol table*/
struct symbol_table
{ char * NAME;                            //name of the identifier
  int TYPE ;                              //TYPE can be integer or boolean
  int SIZE  ;                              //size field for arrays
  int BINDING;                               //position in the memory for the code generation
  struct symbol_table *NEXT;               //pointer to the next entry in symbol table
} *root = NULL;

int memcount = 0;                          // this off_set will be used in implementing symbol table 

/*Function for looking up in symbol table  */
struct symbol_table * Lookup(char* NAME); 
 
/* To install an indentifier in symbol table */
void install(char * NAME,int TYPE,int SIZE);


/*To keep track of number of free registers */
int regcount = -1;
int typeval;

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

%token <ptr> NUMBER BOOLEAN_NUMBER
%token END   START
%token <ptr> P M S D C R READ WRITE ASSIGN_OP ID   WHILE  DO ENDWHILE
%token IF THEN ENDIF ELSE  DECL ENDDECL INT BOOL
%left <ptr>  RELOP
%left P S
%left M D
%nonassoc C
%nonassoc R 
%right UMINUS

%type <ptr> expr stmts stmt
%start start
%%

start : Declblock  Mainblock				    {		return(0);
			                        
					   	}
	;

Declblock : DECL Declist ENDDECL     {}
          ;

Declist   : decl             {} 
          | Declist decl    {}
          ;

decl      : Type Idlist ';'    {}
          ;

Idlist    : Idlist ',' Ids         {}
          | Ids
          ;
Ids       : ID                   {     install($1->NAME,typeval,1); }
          | ID '[' NUMBER ']'    {     install($1->NAME,typeval,$3->VALUE); }
          ;

Type      :      INT					{    typeval=INTEGER; }
          | 	 BOOL					{    typeval=BOOLEAN;	}
	  ;

Mainblock : START stmts  END                               {	
						fp = fopen("sil.asm","a");
			   			fprintf(fp,"START");
						
                                                calculate($2);
						fprintf(fp,"\nHALT");                                                          
						fclose(fp);
						exit(1); }
         ;

stmts 	: stmts   stmt				  {  
							struct node * t1 = malloc(sizeof(struct node));
			                                t1->NODE_TYPE = VOID;
                	                               	$$=makenode(t1,$1,$2,NULL); 
						   } 
        | stmt                                        {    $$=$1;   }
      	;
	
stmt  	: ID ASSIGN_OP expr ';'                    {        
                                                        struct symbol_table* temp = Lookup($1->NAME);
                                                        if(temp==NULL || temp->SIZE!=1) yyerror("Undefined Variable");
                                                        
                                                        else
							       {
							     	 $1->ENTRY = temp;
							     	 $1->TYPE = temp->TYPE;
							       } 
							if($1->TYPE == $3->TYPE) 
							 	$$=makenode($2,$1,NULL,$3);
							  else
							  	{ yyerror("Type Mismatch");}       
                                                         
                                                       	
                                                   }
        | ID '[' expr ']' ASSIGN_OP expr ';'		{ 
							  struct symbol_table* temp = Lookup($1->NAME);
							  if(temp==NULL || temp->SIZE==1) yyerror("Undefined Array");
							  else
							       {
							     	 $1->TYPE = temp->TYPE;
							       }
							 if($1->TYPE == $6->TYPE) 
							 	{ $1->ENTRY = temp;
							 	  $$ = makenode($5, $1, $3, $6);
							 	}
							  else
							  	yyerror("Type Mismatch"); 	
		
							}                                          

      	| READ '(' ID ')'      ';'               {          
                                                         struct symbol_table* temp = Lookup($3->NAME);
                                                        if(temp == NULL || temp->TYPE == BOOLEAN)
                                                           { yyerror("Undefined variable in READ or You are taking input in a boolean variable which is not allowed here");
                                                           }   
                                                                                                             
                                                       else{ 
                                                               $3->ENTRY = temp;

                                                              $$=makenode($1,$3,NULL,NULL);
                                                            } 
                                                  }
       | READ '(' ID '['expr ']'  ')' ';'        {   struct symbol_table * temp = Lookup($3->NAME);
                                                      
					 		 if(temp == NULL )
					 		   {
					 		     yyerror("Undefined array in READ");
					 		   }
					 		  else
					 		    { 
					 		      $3->ENTRY = temp;
					 		      $$ = makenode($1, $3, $5, NULL);
							      
							    }
							}
                                                 
      	| WRITE '(' expr ')' ';'                {	$$=makenode($1,$3,NULL,NULL);}

        | IF '('expr')' THEN stmts ENDIF ';'            {   struct node * t1 = malloc(sizeof(struct node));
	                                                     t1->NODE_TYPE = IF_THEN;
 						             $$=makenode(t1,$3,$6,NULL); }
        |IF '('expr')' THEN stmts ELSE stmts ENDIF ';'  {   struct node * t1 = malloc(sizeof(struct node));
	                                                     t1->NODE_TYPE = IF_THEN;
 						             $$=makenode(t1,$3,$6,$8); }

   
        |WHILE '('expr')' DO stmts ENDWHILE ';'          {   struct node * t1 = malloc(sizeof(struct node));
	                                                     t1->NODE_TYPE = WHILE_LOOP;
 						             $$=makenode(t1,$3,$6,NULL); }
      	; 


expr 	:  expr P expr				{	if( $1->TYPE == $2->TYPE && $2->TYPE == $3->TYPE )
						   	$$=makenode($2,$1,$3,NULL);
						  else
						  	{ yyerror("Type Mismatch"); } 
                                                         
                                                }				
	| expr M expr				{       if( $1->TYPE == $2->TYPE && $2->TYPE == $3->TYPE )
						   	  $$=makenode($2,$1,$3,NULL);
						  else
						  	{ yyerror("Type Mismatch");   } 
                                                }
	| expr S expr				{	if( $1->TYPE == $2->TYPE && $2->TYPE == $3->TYPE )
						   	  $$=makenode($2,$1,$3,NULL);
						  else
						  	{ yyerror("Type Mismatch");   } 
                                                }
	|expr R expr                            {  if( $1->TYPE == $2->TYPE && $2->TYPE == $3->TYPE )
						   	  $$=makenode($2,$1,$3,NULL);
						  else
						  	{ yyerror("Type Mismatch");   } 
                                                }
        | expr D expr				{	if( $1->TYPE == $2->TYPE && $2->TYPE == $3->TYPE )
						   	  $$=makenode($2,$1,$3,NULL);
						  else
						  	{ yyerror("Type Mismatch");   } 
                                                 }
	| expr RELOP expr 		        {   if( $1->TYPE == $3->TYPE && $1->TYPE == INTEGER )
						   	 $$=makenode($2,$1,$3,NULL); 
						  else
						  	yyerror("Type Mismatch for Boolean Operator");  
                                                      
                                                }
        | '(' expr ')'				{	$$=$2;}

	| S expr %prec UMINUS			{	if($1->TYPE == $2->TYPE)
                                                          { $$=makenode($1,$2,NULL,NULL);
                                                          }
                                                         else { yyerror("Type Mismatch"); }
                                                }
	| expr C expr 				{	if( $1->TYPE == $2->TYPE && $2->TYPE == $3->TYPE )
						   	  $$=makenode($2,$1,$3,NULL);
						  else
						  	{ yyerror("Type Mismatch");   }
                                                }
        
	| NUMBER				{	$$=$1;}
         
        |BOOLEAN_NUMBER                         { $$=$1;
                                                  $$->TYPE = BOOLEAN; 
                                                } 




        | ID                                    {                                                                  
                                                        $$ = $1;
						  struct symbol_table* temp = Lookup($$->NAME);
						  
						  if(temp==NULL) yyerror("Undefined Variable in Expression");
						  else
						       {
						       	 $$->ENTRY = temp;
						     	 $$->TYPE = temp->TYPE;
						       }
						                  
                                                }
        | ID'['expr']'		        	{
		 				  $$ = makenode($1,$3,NULL,NULL);
		 				  struct symbol_table* temp = Lookup($$->NAME);
					      	  if(temp==NULL) yyerror("Undefined Variable1");
					          else
					           {
					       		 $$->ENTRY = temp;
					     	 	 $$->TYPE = temp->TYPE;
					     	   }
						  
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
		


void install(char * NAME,int TYPE,int SIZE)
{ 
  struct symbol_table * temp = malloc(sizeof(struct symbol_table));
      temp->NAME = NAME;
	   temp->TYPE = TYPE;
	   temp->SIZE = SIZE; 
	   
	   
	   	   temp->BINDING = memcount;
		   memcount = memcount+SIZE;
	    
	   
	   temp->NEXT = root;
	   root = temp;
    
}

struct symbol_table * Lookup(char * NAME)
{
  struct symbol_table *temp;
  temp=root;  
  while(temp !=NULL && (strcmp(temp->NAME,NAME)!=0))
    { 
      temp=temp->NEXT;
    } 
  return temp;
}

int calculate(struct node *t)
{
	if(t!=NULL)
	{     
		int ret;
                if(t->NODE_TYPE==VOID)
                {  
			calculate(t->P1); 
	                calculate(t->P2);
                }
		else if(t->NODE_TYPE==PLUS)
		{	
			 calculate(t->P1); 
			 calculate(t->P2);
			
 			fprintf(fp,"\nADD R%d,R%d",use_reg(2), use_reg(1));
			free_reg(1);		
		
		}
		else if(t->NODE_TYPE==MINUS)
		{
			if(t->P2 == NULL)
			{	
			        calculate(t->P1);
				res_reg(1);
				fprintf(fp,"\nMOV R%d,-1",use_reg(1));
				fprintf(fp,"\nMUL R%d,R%d",use_reg(2),use_reg(1));
				free_reg(1);
			}
			else
			{
				 calculate(t->P1); 
				 calculate(t->P2); 
				
				fprintf(fp,"\nSUB R%d,R%d",use_reg(2), use_reg(1));
				free_reg(1);
			}
		}
		else if(t->NODE_TYPE==MUL)
		{
		        calculate(t->P1); 
		        calculate(t->P2);
			fprintf(fp,"\nMUL R%d,R%d",use_reg(2), use_reg(1));
			free_reg(1);
		}
                else if(t->NODE_TYPE==MOD)
		{
			  calculate(t->P1) ;
			  calculate(t->P2);
			fprintf(fp,"\nMOD R%d,R%d",use_reg(2), use_reg(1));
			free_reg(1);
		}
		else if(t->NODE_TYPE==DIV)
		{
			 calculate(t->P1) ;
			 calculate(t->P2);
			fprintf(fp,"\nDIV R%d,R%d",use_reg(2), use_reg(1));
			free_reg(1);
		}
		
		else if(t->NODE_TYPE==NUM)
		{       
			ret = t->VALUE;
			res_reg(1);
			fprintf(fp,"\nMOV R%d,%d",use_reg(1), ret);		
		}
                else if (t->NODE_TYPE == VAR)
                {      
		    
	  	 	
	  	 	if(t->P1==NULL)
	  	 	{
				
				   res_reg(1);
				   fprintf(fp,"\nMOV R%d,[%d]", use_reg(1), t->ENTRY->BINDING);
				   
				   	
				 
			}
			else
			{
			            calculate(t->P1);
			  
			  
			           res_reg(1);
				   fprintf(fp,"\nMOV R%d,%d", use_reg(1), t->ENTRY->BINDING);
				   
				   fprintf(fp,"\nADD R%d,R%d", use_reg(1),use_reg(2));
				    
				   fprintf(fp,"\nMOV R%d,[R%d]", use_reg(2), use_reg(1));    
				   free_reg(1)   ;
			      	
			   } 
			  
		         }
	  	 	
	  	 		
               	
                else if (t->NODE_TYPE == ASSIGN)
                {     
			struct symbol_table *check;
	                check = Lookup(t->P1->NAME);
	                if(check==NULL)
		  	   	yyerror("Undefined Variable in assignment statement");
                        else 
                         { 
                            if(t->P2 == NULL)
		             {    calculate(t->P3);
		               	   
		         	   fprintf(fp,"\nMOV [%d],R%d", check->BINDING, use_reg(1));
			            	free_reg(1);   
			
		             }
		             
		             else 
		              {
                                   calculate(t->P2);					   
					 
			           res_reg(1);
			           fprintf(fp,"\nMOV R%d,%d", use_reg(1), check->BINDING);
			           fprintf(fp,"\nADD R%d,R%d",use_reg(2),use_reg(1)); 
	         		   free_reg(1);

				   calculate(t->P3);						   
				   fprintf(fp,"\nMOV [R%d],R%d", use_reg(2), use_reg(1));
				   free_reg(2);   	
							  	              
		              }
                           
                           }
 
               }     
                
                else if (t->NODE_TYPE == IF_THEN)
                {   
                           fprintf(fp,"\nI%d:", ifcount);
			   ipush(ifcount);
			   ifcount++;   
                          

                           calculate(t->P1);
                            
                           
                           fprintf(fp,"\nJZ R%d,E%d", use_reg(1),ifcount-1);
			   
                           
                           calculate(t->P2);
                           
                           fprintf(fp,"\nJMP EI%d", itop->value);
			   fprintf(fp,"\nE%d:", itop->value);
                           calculate(t->P3);
                           fprintf(fp,"\nEI%d:", ipop());
                            
                                                  
	        }
                else if (t->NODE_TYPE == WHILE_LOOP)
                {          fprintf(fp,"\nW%d:", whilecount);
			   wpush(whilecount);
			   whilecount++;
                           

                          calculate(t->P1);

                          
                          fprintf(fp,"\nJZ R%d,EW%d", use_reg(1),whilecount-1);
                          
 
                          calculate(t->P2);
                          fprintf(fp,"\nJMP W%d", wtop->value);
			  fprintf(fp,"\nEW%d:", wpop());

                }

           	else if(t->NODE_TYPE == WRITE_NODE)
                {  	
			calculate(t->P1);
                    	fprintf(fp,"\nOUT R%d",use_reg(1));
                        free_reg(1);
                }
           	else if(t->NODE_TYPE == READ_NODE)
                {    
			struct symbol_table * check = Lookup(t->P1->NAME);
                        if(check == NULL)
                             yyerror("Undefined symbol in Read ");
                        else
                          { if(t->P2 ==NULL)
                            { res_reg(1);
                              fprintf(fp,"\nIN R%d",use_reg(1) );
                              fprintf(fp,"\nMOV [%d],R%d", check->BINDING,use_reg(1));
                              free_reg(1);
                            }
                           else
                           { 
                                calculate(t->P2);
                                res_reg(1);
                              
                                fprintf(fp,"\nMOV R%d,%d", use_reg(1), check->BINDING);
                                 fprintf(fp,"\nADD R%d,R%d",use_reg(2),use_reg(1));
			         
              	                fprintf(fp,"\nIN R%d",use_reg(1) );
                                fprintf(fp,"\nMOV[R%d],R%d", use_reg(2),use_reg(1));
                                free_reg(1);
                            }



                          }
                        


                }
               
             else if (t->NODE_TYPE == LT)
                {    
                      
                       
                      calculate(t->P1) ;
                       calculate(t->P2) ;
  			 
                       
                      fprintf(fp,"\nLT  R%d,R%d",use_reg(2),use_reg(1));
                                          
                      free_reg(1);
                      
                     
                }
 
             else if (t->NODE_TYPE == LE)
                {    
                      
                       
                      calculate(t->P1) ;
                       calculate(t->P2);
  			   
  			                       
                      fprintf(fp,"\nLE  R%d,R%d",use_reg(2),use_reg(1));
                                          
                      free_reg(1);
                      
                     
                } 

                else if (t->NODE_TYPE == GE)
                {    
                      
                       
                      calculate(t->P1) ; 
                       calculate(t->P2) ;
  			
  			
  			  
                       
                      fprintf(fp,"\nGE  R%d,R%d",use_reg(2),use_reg(1));
                                          
                      free_reg(1);
                      
                     
                } 
               else if (t->NODE_TYPE == GT)
                {     
                    
                       calculate(t->P1) ;
                        calculate(t->P2) ;
  			  
                      fprintf(fp,"\nGT  R%d,R%d",use_reg(2),use_reg(1));
                     
                   
                      free_reg(1);
                      
                     
                }

              else if (t->NODE_TYPE == EQ)
                {     
                     
                    calculate(t->P1) ; 
                    calculate(t->P2) ;
  			   
  			
                     
                      fprintf(fp,"\nEQ  R%d,R%d",use_reg(2),use_reg(1));
                     
                  
                     
                      free_reg(1);
                       
                      
                 }
                else if (t->NODE_TYPE == NE)
                {    
                      
                       
                      calculate(t->P1) ; calculate(t->P2);
  			  
  			
                       
                      fprintf(fp,"\nNE  R%d,R%d",use_reg(2),use_reg(1));
                                          
                      free_reg(1);
                      
                     
                } 
          return 1;

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
