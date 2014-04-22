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
#define RETURN_NODE 333
#define FUNCTION_NODE 444
#define T 1
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
{        int TYPE; 
	int NODE_TYPE;
	char * NAME;
        int VALUE;
	struct node *P1,*P2,*P3;
	struct Gsymbol_table *GENTRY;
        struct Lsymbol_table *LENTRY;  
        
};


/*Data structure for a  global symbol table*/
struct Gsymbol_table
{ char * NAME;                            //name of the identifier
  int TYPE ;                              //TYPE can be integer or boolean
  int SIZE  ;                              //size field for arrays ; 0 for functions
  int BINDING;                               //position in the memory for the code generation
  struct Gsymbol_table *NEXT;               //pointer to the next GENTRY in symbol table
  struct Argument_Struct* ARG_LIST;	// for functions, it is a structure which contains information about arguments
} *root_G = NULL;

struct Lsymbol_table
{
   char * NAME;
   int TYPE;
   int BINDING;
   struct Lsymbol_table * NEXT;
}*root_L = NULL;

struct Argument_Struct 
{ char * ARG_NAME;  
  int ARG_TYPE;
  int ARG_PASS_TYPE;            // 0 for "call by value" 1 for "call by reference"
  struct Argument_Struct * ARG_NEXT;
};


int memcount = 0;                          // this off_set will be used in implementing symbol table 
int fnlabel = 0;                       //to provide for function labelling

 
/*Function for looking up in  Gloabl symbol table  */
struct Gsymbol_table * GLOOKUP(char* NAME);

/* Function for looking up in  local symbol table  */
struct Lsymbol_table * LLOOKUP(char * NAME);
 
/* To install an indentifier in global  symbol table */
void Ginstall(char * NAME,int TYPE,int SIZE,struct Argument_Struct * ARG_LIST); 

/* To install an identifier in local symbol table */
void Linstall(char * NAME,int TYPE);

/*To keep track of number of free registers */
int regcount = -1;
int typeval;
int arg_typeval;
int ret_typeval;

struct Argument_Struct *headArg = NULL;
struct Argument_Struct *newArg;

struct Lsymbol_table *lcheck = NULL;


struct node* temp_head = NULL ;  // to print the code for a function ,it may be 'main' or some other function

struct node * arg_parameter = NULL; // to be used in arg_check function ,head of the  parameters in a function call


/* To add 'arg' list to 'head' list */
void makeArglist(struct Argument_Struct* arg);

/* To print the argument list */
void printArg(struct Argument_Struct* head);

/*  To check the definition of fucntion ,comparing type, name and arglist */
void fnDefCheck(int type, char* name, struct Argument_Struct* arg);

/* Helper function for fnDefCheck for comparing two argument list */
int argDefCheck(struct Argument_Struct* arg1, struct Argument_Struct* arg2);

/* to check the parameters in function call i.e whether the parameters are according to function definition or not*/
void arg_check(struct Argument_Struct*);


int argInstall(struct Argument_Struct* head);

void arg_push(struct node* x, struct Argument_Struct* y); // to push the arguments on stack

void arg_push_helper(struct Argument_Struct * y); 

void argument_popper(struct node * x);


int mainflag = 0;   //To differentiate between 'main' function and other functions

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
%token <ptr> P M S D C R READ WRITE ASSIGN_OP ID   WHILE  DO ENDWHILE AND OR NOT 
%token IF THEN ENDIF ELSE  DECL ENDDECL INT BOOL RETURN MAIN BEG END 
%left <ptr>  RELOP
%right NOT
%left AND OR
%left P S
%left M D
%nonassoc C
%nonassoc R 
%right UMINUS

%type <ptr> expr stmts stmt exprlist 
%start start
%%

start : Declblock fDefblock Mainblock		    {  }
      
      |Mainblock         {}             
      |Declblock Mainblock  {}    
      ;

Declblock : DECL Declist ENDDECL                       {  
							  fp = fopen("sil.asm","a");
							  int i=0;
							  for(i=0;i<memcount;i++)              							            {
                                                               fprintf(fp,"\nPUSH R%d",regcount+1);
						 	    }						
							 memcount = 1;							
							 fprintf(fp,"\nJMP main");
							 fclose(fp);	    
                                                       }
          ;

Declist   : decl             {} 
          | Declist decl    {}
          ;

decl      : Type Idlist ';'    {}
          ;

Idlist    : Idlist ',' Ids         {}
          | Ids
          ;
Ids       : ID                   {    Ginstall($1->NAME,typeval,1,NULL); }
          | ID '[' NUMBER ']'    {     Ginstall($1->NAME,typeval,$3->VALUE,NULL); }
          | ID '(' arglist ')'   {     Ginstall($1->NAME,typeval,0,headArg); 
                                        headArg = NULL;           }
          ;
 
arglist   : arg {}    
          |arglist ';' arg { }
          | {}
          ;  

fArgdef   : farglist           { argInstall(headArg);}
          |                    {}
          ;

farglist  : arg {}
          | farglist ';' arg {}
          ;

arg       : argtype argIDlist {}
          ;
argIDlist : argID                  { makeArglist(newArg);}  /* this function adds the newArg at the end of headArg after checking if the  									      names of arguments are unique or not*/ 
          | argIDlist ',' argID    { makeArglist(newArg);}
          ;
argID     : ID   {                                      newArg = malloc(sizeof(struct Argument_Struct )); 
							newArg->ARG_NAME = $1->NAME;
							newArg->ARG_TYPE = arg_typeval;
							newArg->ARG_PASS_TYPE = 0;
							newArg->ARG_NEXT = NULL; }

          |'&'ID                                   {    newArg = malloc(sizeof(struct Argument_Struct ));
							newArg->ARG_NAME = $2->NAME;
							newArg->ARG_TYPE = arg_typeval;
							newArg->ARG_PASS_TYPE =1;
							newArg->ARG_NEXT = NULL;}
          ;

argtype   : INT                                         { arg_typeval = INTEGER ; } 
          | BOOL                                        { arg_typeval = BOOL ; }
          ;

Type      :      INT					{    typeval=INTEGER; }
          | 	 BOOL					{    typeval=BOOLEAN;	}
	  ;


fDefblock  : fDefblock fDef                           {}
           | fDef                                     {}
           ;

fDef      : Rtype ID '(' fArgdef ')' '{' fBlock '}'   {  fnDefCheck(ret_typeval, $2->NAME, headArg);
							 
							 fp = fopen("sil.asm","a");
							 fprintf(fp,"\nfn%d:", fnlabel);
							 fnlabel++;
							 fprintf(fp,"\nPUSH BP");
							 fprintf(fp,"\nMOV BP,SP");
							 int i=1;
							 for(i=1;i<memcount;i++)  //pushing the local variable ,as for function memcount starts from 1
							  	fprintf(fp,"\nPUSH R%d",regcount+1);
							 
							headArg=NULL;  // job of headArg is completed(for fnDefCheck) so now initialize it with NULL 
							calculate(temp_head); // print code for the body of the function.
							memcount=1;
							 root_L= NULL;  //
							// temp_head=NULL;
                                                         fclose(fp);
                                                                 }

          ;

Rtype    : INT                                   { ret_typeval = INTEGER ; }
         | BOOL                                   { ret_typeval = BOOLEAN ; }
         ;

Mainblock : INT MAIN '(' ')' '{' fBlock '}'         {   
							fp = fopen("sil.asm","a");
							fprintf(fp,"\nmain:");
							fprintf(fp,"\nPUSH BP");
							fprintf(fp,"\nMOV BP,SP");
							int i=1;
							for(i=1;i<memcount;i++)
							  	fprintf(fp,"\nPUSH R%d",0);
							
							mainflag=1;
                                                     
							calculate(temp_head); 
							memcount=1;
							root_L = NULL;
							temp_head=NULL; 
                                                        fprintf(fp,"\nHALT");   
                                                         fclose(fp);
                                                    }
         ;
fBlock   : LDefblock stmtblock  {}
         | stmtblock           { }
         ;

LDefblock : DECL LDlist ENDDECL  {}
          ;

LDlist   :  LDecl                   {}
         | LDlist LDecl             {}
         ;
LDecl    : Type LIdlist ';'         {}
         ;

LIdlist  :  LIdlist ',' LId	{	}
	|   LId	  {}
        ;		
		
		
LId     : ID	                    {   Linstall($1->NAME, typeval); }		
	;

stmtblock : BEG stmts  END  {  temp_head = $2; }
          | BEG END {}
          ;        
stmts 	: stmts   stmt				  {  
							struct node * t1 = malloc(sizeof(struct node));
			                                t1->NODE_TYPE = VOID;
                	                               	$$=makenode(t1,$1,$2,NULL); 
						   } 
        | stmt                                        {    $$=$1;   }
      	;
	
stmt  	: ID ASSIGN_OP expr ';'                    {     struct Lsymbol_table * temp = LLOOKUP($1->NAME);
                                                         if(!temp)
                                                       {   
                                                         struct Gsymbol_table* gtemp = GLOOKUP($1->NAME);
                                                         if(gtemp==NULL || gtemp->SIZE!=1) yyerror("Undefined Variable");
                                                         else
							       {
							     	 $1->GENTRY = gtemp;
							     	 $1->TYPE = gtemp->TYPE;
							       }
                                                       }
                                                       else 
                                                      {  $1->LENTRY = temp;
                                                         $1->TYPE = temp->TYPE ;
                                                      } 

							if($1->TYPE == $3->TYPE) 
							 	$$=makenode($2,$1,NULL,$3);
							  else
							  	{ yyerror("Type Mismatch");}       
                                                         
                                                       	
                                                   }
        | ID '[' expr ']' ASSIGN_OP expr ';'		{ 
							  struct Gsymbol_table* temp = GLOOKUP($1->NAME);
							  if(temp==NULL || temp->SIZE==1) yyerror("Undefined Array");
							  else
							       {
							     	 $1->TYPE = temp->TYPE;
							       }
							 if($1->TYPE == $6->TYPE) 
							 	{ $1->GENTRY = temp;
							 	  $$ = makenode($5, $1, $3, $6);
							 	}
							  else
							  	yyerror("Type Mismatch"); 	
		
							}                                          

      	| READ '(' ID ')'      ';'               {       struct Lsymbol_table * temp = LLOOKUP($3->NAME);
                                                        if(temp ==NULL)
                                                   { 
                                                         struct Gsymbol_table* gtemp = GLOOKUP($3->NAME);
                                                        if(gtemp == NULL || gtemp->TYPE == BOOLEAN || gtemp->SIZE != 1)
                                                           { yyerror("Undefined variable in READ or You are taking input in a boolean variable which is not allowed here");
                                                           }   
                                                                                                             
                                                       else{ 
                                                               $3->GENTRY = gtemp;
                                                              $$=makenode($1,$3,NULL,NULL);
                                                            }
                                                   }
                                             else { $3->LENTRY = temp;
                                                    $$ = makenode($1,$3,NULL,NULL);                    
                                                   }
                                          
            
                                                  }

       | READ '(' ID '['expr ']'  ')' ';'        {   struct Gsymbol_table * temp = GLOOKUP($3->NAME);
                                                      
					 		 if(temp == NULL || temp->SIZE == 1 || temp ->TYPE == BOOLEAN)
					 		   {
					 		     yyerror("Undefined array in READ or you are using a non integer array in Read");
					 		   }
					 		  else
					 		    { 
					 		      $3->GENTRY = temp;
					 		      $$ = makenode($1, $3, $5, NULL);
							      
							    }
							}
                                                 
      	| WRITE '(' expr ')' ';'                {	if($3->TYPE == INTEGER) 
                                                       {
                                                         $$=makenode($1,$3,NULL,NULL);
                                                        }
                                                        else { yyerror("Type Mismatch,Type of expression inside WRITE should be integer") ; }

                                                }
        | IF '('expr')' THEN stmts ENDIF ';'            {   struct node * t1 = malloc(sizeof(struct node));
	                                                     t1->NODE_TYPE = IF_THEN;
 						         if($3->TYPE == BOOLEAN)    
                                                            {
                                                               $$=makenode(t1,$3,$6,NULL);
                                                            } 

                                                         else { yyerror("Type Mismatch , expr inside IF should be of boolean type "); }
 
                                                        }
        |IF '('expr')' THEN stmts ELSE stmts ENDIF ';'  {   struct node * t1 = malloc(sizeof(struct node));
	                                                     t1->NODE_TYPE = IF_THEN;
 						         if($3->TYPE == BOOLEAN)   
                                                            { 
                                                              $$=makenode(t1,$3,$6,$8); 
                                                             }
                                                         else { yyerror("Type Mismatch , expr inside IF should be of boolean type "); }
                                                         }

   
        |WHILE '('expr')' DO stmts ENDWHILE ';'          {   struct node * t1 = malloc(sizeof(struct node));
	                                                     t1->NODE_TYPE = WHILE_LOOP;
 						             if($3->TYPE == BOOLEAN)
                                                              {
                                                                  $$=makenode(t1,$3,$6,NULL);
                                                              }
                                                         else { yyerror("Type Mismatch , expr inside WHILE should be of boolean type "); }
 
                                                          }

        |RETURN expr          ';'                   {      struct node * t1 = malloc(sizeof(struct node));
			                                t1->NODE_TYPE = RETURN_NODE;
                                                         if(ret_typeval == $2->TYPE)
                	                               	   { 
                                                              $$=makenode(t1,NULL,$2,NULL);
                                                            }
                                                        else { yyerror("Type mismatch in return statment"); }
                                                  }
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
        |expr AND expr                       {  if( $1->TYPE == $3->TYPE && $1->TYPE == BOOLEAN )
						   	 $$=makenode($2,$1,$3,NULL); 
						  else
						  	yyerror("Type Mismatch for AND Operator");  
                                                    
                                              }
        |expr OR expr                      {  if( $1->TYPE == $3->TYPE && $1->TYPE == BOOLEAN )
						   	 $$=makenode($2,$1,$3,NULL); 
						  else
						  	yyerror("Type Mismatch for OR Operator");   
                                           }
        | NOT expr                       {   if( $2->TYPE== BOOLEAN )
						   	$$ = makenode($1, NULL, $2, NULL);
						  else
						  	yyerror("Type Mismatch for NOT Operator");
                                           }
      
        
	| NUMBER				{	$$=$1;}
         
        |BOOLEAN_NUMBER                         { $$=$1;
                                                  $$->TYPE = BOOLEAN; 
                                                } 




        | ID                                    {                                                                  
                                                        $$ = $1;
                                                  struct Lsymbol_table * ltemp = LLOOKUP($$->NAME);
                                                 if(ltemp == NULL) 
                                                 {
						   struct Gsymbol_table* temp = GLOOKUP($$->NAME);
						  
						   if(temp==NULL || temp->SIZE != 1)
                                                     yyerror("Undefined Variable in Expression");
						   else
						       {
						       	 $$->GENTRY = temp;
						     	 $$->TYPE = temp->TYPE;
						       }
						  }
                                                 else 
                                                  {
                                                       $$->LENTRY = ltemp ;
                                                       $$->TYPE = ltemp->TYPE;
                                                  }
                                                }                 
                                                  
        | ID'['expr']'		        	{
		 				  $$ = makenode($1,$3,NULL,NULL);
		 				  struct Gsymbol_table* temp = GLOOKUP($$->NAME);
					      	  if(temp==NULL || temp->SIZE == 1 ) 
                                                    yyerror("Undefined Array is being used");
					          else
					           {
					       		 $$->GENTRY = temp;
					     	 	 $$->TYPE = temp->TYPE;
					     	   }
						  
						 } 


       |ID '('exprlist ')'                {    
	        
                                                     struct Gsymbol_table* gtemp = GLOOKUP($1->NAME);
						      if(gtemp==NULL || gtemp->SIZE!=0) yyerror("Undefined Function");
						      else
						       { 
                                                         arg_parameter = $3;
                                                         arg_check(gtemp->ARG_LIST);
                                                      if(arg_parameter)
                                                         yyerror("mismatch argument in function call");
                                                         
						       	 $$= $1;
                                                         $$->GENTRY = gtemp;
                                                         $$->NODE_TYPE = FUNCTION_NODE;
						     	 $$->TYPE = gtemp->TYPE;
						     	 $$->P1 = $3;
						       }


                                           }     
                                                          
                                      
	;
   
    exprlist :  expr               {   struct node * t1 = malloc(sizeof(struct node));
                                       t1->NODE_TYPE = VOID ;
                                       $$ = makenode(t1,NULL,$1,NULL);                                    
                                   
                                   }

             | exprlist ',' expr  {    struct node * t1 = malloc(sizeof(struct node));
                                       t1->NODE_TYPE = VOID ;
                                       $$ = makenode(t1,$1,$3,NULL);   
                                  }
             |                    { $$ = NULL ; }
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
		


void Ginstall(char * NAME,int TYPE,int SIZE, struct Argument_Struct *ARGLIST)
{ 
  struct Gsymbol_table * temp = malloc(sizeof(struct Gsymbol_table));
 
           temp->NAME = NAME;
	   temp->TYPE = TYPE;
	   temp->SIZE = SIZE; 
           temp->ARG_LIST = ARGLIST;
          
              
	   temp->BINDING = memcount;
           memcount = memcount+SIZE;
	     
	   
	   temp->NEXT = root_G;
	   root_G = temp;
    
}

void Linstall(char *NAME ,int TYPE)
{ struct Lsymbol_table * temp = malloc(sizeof(struct Lsymbol_table));
       temp->NAME = NAME; 
       temp->TYPE = TYPE;       
       temp->BINDING = memcount;
       memcount = memcount + 1;
  
       temp->NEXT = root_L;
       root_L = temp;
}

struct Gsymbol_table * GLOOKUP(char * NAME)
{
  struct Gsymbol_table *temp;
  temp=root_G;  
  while(temp !=NULL) 
    {   if(strcmp(temp->NAME,NAME)==0)
            { return temp;
            }
      else { 
          temp=temp->NEXT;
           }
     }
  return NULL;
}

struct Lsymbol_table * LLOOKUP(char * NAME)
{
   struct Lsymbol_table * temp;
   temp =root_L;
   while(temp !=NULL) 
    {   if(strcmp(temp->NAME,NAME)==0)
            { return temp;
            }
      else { 
          temp=temp->NEXT;
           }
    }
  return NULL;
}

void makeArglist(struct Argument_Struct* arg)
{
	if(!headArg)
		headArg = arg;
	else
	 {
		struct Argument_Struct * x = headArg->ARG_NEXT;
		struct Argument_Struct * y = headArg;
		while(x)
		 {
			if(strcmp(y->ARG_NAME, arg->ARG_NAME)==0)
				yyerror("Arguments with the same name......ERROR");
			else
			 {
				x=x->ARG_NEXT;
				y=y->ARG_NEXT;
			 }
		 }
		if(strcmp(y->ARG_NAME, arg->ARG_NAME)==0)
			yyerror("Arguments with the same name.....ERROR");
		else
			y->ARG_NEXT = arg;
	 }
	
	
}

void printArg(struct Argument_Struct* head)
{
	struct Argument_Struct* i = head;
	while(i!=NULL)
	{
		printf("%d %s - ",i->ARG_TYPE,i->ARG_NAME);
		i=i->ARG_NEXT;
	}
}

void fnDefCheck(int type, char* name, struct Argument_Struct* arg)
{
	   struct Gsymbol_table* res = GLOOKUP(name) ;
	   if(!res)
		yyerror("Undeclared function");
	   else
	     {	
		if(res->TYPE != type)
			yyerror("Type Mismatch in function definiton");
		else if(argDefCheck(res->ARG_LIST, arg))
			yyerror("Arguments don't match with the declaration ");
		else
		 {
			res->BINDING = fnlabel;
		 }
	      }
	  

}

int argDefCheck(struct Argument_Struct* arg1, struct Argument_Struct* arg2)
{
	struct Argument_Struct* i = arg1;
	struct Argument_Struct* j = arg2;
	while(i!=NULL)
	{
		if(j==NULL)
		{
		 
		 	return 1;
			
		}
		else
		{
			if(strcmp(j->ARG_NAME,i->ARG_NAME)!=0 || i->ARG_TYPE!=j->ARG_TYPE )
			{
			return 1;
			} 
			i=i->ARG_NEXT;
			j=j->ARG_NEXT;
			
		}
	}
	if(j==NULL) 
	{
	 	return 0;
	}
	else 
	{	
	 	return 1;
		
	}
}


void arg_check(struct Argument_Struct * temp)
{
	if(!temp)
		return;
	arg_check(temp->ARG_NEXT);	
	if(!arg_parameter)
		yyerror(" mismatch argument in funcion call ");	

	if((arg_parameter->P2)->TYPE == temp->ARG_TYPE)
	 {
		if(temp->ARG_PASS_TYPE == 1)           // ARG_PASS_TYPE = 0 for call by value , ARG_PASS_TYPE = 1 for call by reference 
			if(arg_parameter->P2->NODE_TYPE != VAR )
				yyerror(" PASS BY REFERENCE MISMATCH ");
	 }

	if(arg_parameter)
		arg_parameter = arg_parameter->P1;
}

void arg_push(struct node* x, struct Argument_Struct* y)
{
   arg_parameter = x ;
   arg_push_helper(y);
}

void arg_push_helper(struct Argument_Struct * y)
{     if(!y)
		return;
	arg_push_helper(y->ARG_NEXT);

	calculate(arg_parameter->P2);
	fprintf(fp,"\nPUSH R%d", use_reg(1));
	free_reg(1);

	if(arg_parameter)
		arg_parameter = arg_parameter->P1;

}

void argument_popper(struct node * x)
{ 
         if(!x)
		return;
	argument_popper(x->P1);
	if(newArg->ARG_PASS_TYPE == 1)
	 {
		if(x->P2->LENTRY)
		{
			res_reg(2);
			fprintf(fp,"\nMOV R%d, BP",use_reg(2));
			fprintf(fp,"\nMOV R%d, %d",use_reg(1), x->P2->LENTRY->BINDING);
			fprintf(fp,"\nADD R%d, R%d", use_reg(2), use_reg(1));
			fprintf(fp,"\nPOP R%d", use_reg(1));
			fprintf(fp,"\nMOV [R%d], R%d", use_reg(2), use_reg(1));
			free_reg(2);
		}
		else
		{
			res_reg(1);
			fprintf(fp,"\nPOP R%d",use_reg(1));
			fprintf(fp,"\nMOV [%d], R%d",x->P2->GENTRY->BINDING,use_reg(1));
			free_reg(1);
		}
	 }
	else
	{
		fprintf(fp,"\nPOP R%d",regcount+1);		
	}
	newArg = newArg->ARG_NEXT;
}





int argInstall(struct Argument_Struct* head)
{
	memcount=-3;
	/*memcount starts at -3 for arguments, as -1: Return address and -2 Return value*/
	while(head)
	{
                struct Lsymbol_table * ltemp = malloc(sizeof(struct Lsymbol_table));  
		ltemp->NAME = head->ARG_NAME;
		ltemp->TYPE = head->ARG_TYPE;
		ltemp->BINDING = memcount;
		memcount--;
		ltemp->NEXT = root_L;
		root_L = ltemp;
		head=head->ARG_NEXT;
		
	}
	memcount=1;
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
					res_reg(1);
        	fprintf(fp,"\nMOV R%d,%d",use_reg(1), t->VALUE);		
		}
                else if (t->NODE_TYPE == VAR)
                {      
		    
	  	    if(t->LENTRY == NULL)
                     {
                        if(t->P1)
                           {
                                 res_reg(1);
                                 fprintf(fp,"\nMOV R%d, %d",use_reg(1),(t->GENTRY)->BINDING);				
				 calculate(t->P1);
				 fprintf(fp,"\nADD R%d, R%d",use_reg(1),use_reg(2));
				 fprintf(fp,"\nMOV R%d, [R%d]",use_reg(2),use_reg(1));
				 free_reg(1);
	
                           }
                       else
                           {            res_reg(1);
					fprintf(fp,"\nMOV R%d, [%d]",use_reg(1),(t->GENTRY)->BINDING);
                           }
                      }
                   else 
                       {
                                res_reg(2);
				fprintf(fp,"\nMOV R%d, BP", use_reg(2));
				fprintf(fp,"\nMOV R%d, %d", use_reg(1), (t->LENTRY)->BINDING);
				fprintf(fp,"\nADD R%d, R%d", use_reg(1), use_reg(2));
				fprintf(fp,"\nMOV R%d, [R%d]",use_reg(2),use_reg(1));
				free_reg(1);


                        }
                } 


	
               	
                else if (t->NODE_TYPE == ASSIGN)
                {     
			
	                lcheck = LLOOKUP(t->P1->NAME);
	                if(!lcheck)
                       {  
                           if(!t->P2 )
		             {    calculate(t->P3);
		               	   fprintf(fp,"\nMOV [%d], R%d",((t->P1)->GENTRY)->BINDING,use_reg(1));
			            free_reg(1);   
			
		             }
                          
                         else 
                          {      res_reg(1);
				 fprintf(fp,"\nMOV R%d, %d",use_reg(1),(((t->P1)->GENTRY)->BINDING));
				 calculate(t->P2);
				 fprintf(fp,"\nADD R%d, R%d",use_reg(1),use_reg(2));
				 calculate(t->P3);
				 fprintf(fp,"\nMOV [R%d], R%d",use_reg(2),use_reg(1)); 
				 free_reg(3);
                            }
                       }
                  else
                    {  
                          res_reg(2);
		          fprintf(fp,"\nMOV R%d, BP", use_reg(2));
			  fprintf(fp,"\nMOV R%d, %d", use_reg(1), lcheck->BINDING);
		          fprintf(fp,"\nADD R%d, R%d", use_reg(2), use_reg(1));
			  free_reg(1);
			  calculate(t->P3);
			  fprintf(fp,"\nMOV [R%d], R%d", use_reg(2), use_reg(1));
			  free_reg(2);

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
			struct Lsymbol_table * check = LLOOKUP(t->P1->NAME);
                        if(check == NULL)
                          { 
                             if(t->P2 ==NULL)
                             { res_reg(1);
                               fprintf(fp,"\nIN R%d",use_reg(1) );
                               fprintf(fp,"\nMOV [%d],R%d",((t->P1)->GENTRY)->BINDING,use_reg(1));
                               free_reg(1);
                             }
                           else
                           {           res_reg(1);	
					fprintf(fp,"\nMOV R%d, %d",use_reg(1),((t->P1)->GENTRY)->BINDING);
					calculate(t->P2);
					fprintf(fp,"\nADD R%d, R%d",use_reg(2),use_reg(1));
					fprintf(fp,"\nIN R%d", use_reg(1));
					fprintf(fp,"\nMOV [R%d], R%d",use_reg(2), use_reg(1));
					free_reg(2);

                               
                            }



                          }
                       else 
                        { 
                             res_reg(3);
		             fprintf(fp,"\nIN R%d",use_reg(3));
			     fprintf(fp,"\nMOV R%d, BP",use_reg(2));
			     fprintf(fp,"\nMOV R%d, %d",use_reg(1),((t->P1)->LENTRY)->BINDING);
			     fprintf(fp,"\nADD R%d, R%d",use_reg(2),use_reg(1));
			     fprintf(fp,"\nMOV [R%d], R%d",use_reg(2),use_reg(3));
		             free_reg(3);

                         }
                        


                }
   
             else if (t->NODE_TYPE == FUNCTION_NODE)
                {
                       int temp_regcount = regcount;
                       while(regcount >=0)
                       {
				fprintf(fp,"\nPUSH R%d", regcount);
				regcount--;
		        }
                       arg_push(t->P1, t->GENTRY->ARG_LIST);		// Pushing the arguments
			fprintf(fp,"\nPUSH R0");			// Return value 
			fprintf(fp,"\nCALL fn%d", t->GENTRY->BINDING);  
			fprintf(fp,"\nPOP R%d", temp_regcount + 1);		
			regcount = temp_regcount + 1;

                        newArg = t->GENTRY->ARG_LIST;
                        argument_popper(t->P1);

                        regcount = 0;				// for restoring the register 
			 while(regcount <= temp_regcount)
			{
				fprintf(fp,"\nPOP R%d", regcount);
				regcount++;
			}
			regcount = temp_regcount + 1;					


                       
                }
         
             else if (t->NODE_TYPE == RETURN_NODE)
                {
                     calculate(t->P2);				
			if(mainflag == 0)
			{
				res_reg(2);
				fprintf(fp,"\nMOV R%d, BP", use_reg(2));
				fprintf(fp,"\nMOV R%d, -2", use_reg(1));	
				fprintf(fp,"\nADD R%d, R%d", use_reg(2),use_reg(1));
				fprintf(fp,"\nMOV [R%d], R%d", use_reg(2),use_reg(3));
				free_reg(3);
				int i = 1;
				for(i = 1;i < memcount; i++)			
					fprintf(fp,"\nPOP R%d", 0);

				fprintf(fp,"\nPOP BP");			
				fprintf(fp,"\nRET");			
			}
                }

             else if (t->NODE_TYPE == AND_NODE)
               {
                          calculate(t->P1);
			  calculate(t->P2);
			  fprintf(fp,"\nMUL R%d, R%d",use_reg(2),use_reg(1));	// AND
			  free_reg(1);

               }

                else if (t->NODE_TYPE == OR_NODE)
               {
                          calculate(t->P1);
			  calculate(t->P2);
			  fprintf(fp,"\nADD R%d, R%d",use_reg(2),use_reg(1));	// AND
			  free_reg(1);

               }
              else if (t->NODE_TYPE == NOT_NODE)
              {
                   calculate(t->P2);
		   res_reg(1);
		   fprintf(fp,"\nMOV R%d, 1",use_reg(1));
		   fprintf(fp,"\nSUB R%d, R%d",use_reg(1),use_reg(2));	// NOT
					free_reg(1);
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
        FILE *fp;
	fp = fopen("sil.asm","w");
	fprintf(fp,"START");
	fprintf(fp,"\nMOV SP, 0");
	fprintf(fp,"\nMOV BP, 0");
	fclose(fp);
	yyparse();	
    	return 0; 	

}
