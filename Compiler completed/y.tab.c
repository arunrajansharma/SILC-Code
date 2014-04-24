/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 1 "cg_calc.y"

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
int ret_typeval = 1; // for main function by default

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




/* Line 268 of yacc.c  */
#line 264 "y.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     NUMBER = 258,
     BOOLEAN_NUMBER = 259,
     P = 260,
     M = 261,
     S = 262,
     D = 263,
     C = 264,
     R = 265,
     READ = 266,
     WRITE = 267,
     ASSIGN_OP = 268,
     ID = 269,
     WHILE = 270,
     DO = 271,
     ENDWHILE = 272,
     AND = 273,
     OR = 274,
     NOT = 275,
     IF = 276,
     THEN = 277,
     ENDIF = 278,
     ELSE = 279,
     DECL = 280,
     ENDDECL = 281,
     INT = 282,
     BOOL = 283,
     RETURN = 284,
     MAIN = 285,
     BEG = 286,
     END = 287,
     RELOP = 288,
     UMINUS = 289
   };
#endif
/* Tokens.  */
#define NUMBER 258
#define BOOLEAN_NUMBER 259
#define P 260
#define M 261
#define S 262
#define D 263
#define C 264
#define R 265
#define READ 266
#define WRITE 267
#define ASSIGN_OP 268
#define ID 269
#define WHILE 270
#define DO 271
#define ENDWHILE 272
#define AND 273
#define OR 274
#define NOT 275
#define IF 276
#define THEN 277
#define ENDIF 278
#define ELSE 279
#define DECL 280
#define ENDDECL 281
#define INT 282
#define BOOL 283
#define RETURN 284
#define MAIN 285
#define BEG 286
#define END 287
#define RELOP 288
#define UMINUS 289




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 195 "cg_calc.y"

	struct node *ptr;
	



/* Line 293 of yacc.c  */
#line 375 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 387 "y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  12
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   346

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  44
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  30
/* YYNRULES -- Number of rules.  */
#define YYNRULES  77
/* YYNRULES -- Number of states.  */
#define YYNSTATES  170

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   289

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    41,     2,
      39,    40,     2,     2,    36,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    35,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    37,     2,    38,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    42,     2,    43,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     7,     9,    12,    16,    18,    21,    25,
      29,    31,    33,    38,    43,    45,    49,    50,    52,    53,
      55,    59,    62,    64,    68,    70,    73,    75,    77,    79,
      81,    84,    86,    95,    97,    99,   107,   110,   112,   116,
     118,   121,   125,   129,   131,   133,   137,   140,   143,   145,
     150,   158,   164,   173,   179,   188,   199,   208,   212,   216,
     220,   224,   228,   232,   236,   240,   243,   247,   251,   255,
     258,   260,   262,   264,   269,   274,   276,   280
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      45,     0,    -1,    46,    59,    62,    -1,    62,    -1,    46,
      62,    -1,    25,    47,    26,    -1,    48,    -1,    47,    48,
      -1,    58,    49,    35,    -1,    49,    36,    50,    -1,    50,
      -1,    14,    -1,    14,    37,     3,    38,    -1,    14,    39,
      51,    40,    -1,    54,    -1,    51,    35,    54,    -1,    -1,
      53,    -1,    -1,    54,    -1,    53,    35,    54,    -1,    57,
      55,    -1,    56,    -1,    55,    36,    56,    -1,    14,    -1,
      41,    14,    -1,    27,    -1,    28,    -1,    27,    -1,    28,
      -1,    59,    60,    -1,    60,    -1,    61,    14,    39,    52,
      40,    42,    63,    43,    -1,    27,    -1,    28,    -1,    27,
      30,    39,    40,    42,    63,    43,    -1,    64,    69,    -1,
      69,    -1,    25,    65,    26,    -1,    66,    -1,    65,    66,
      -1,    58,    67,    35,    -1,    67,    36,    68,    -1,    68,
      -1,    14,    -1,    31,    70,    32,    -1,    31,    32,    -1,
      70,    71,    -1,    71,    -1,    14,    13,    72,    35,    -1,
      14,    37,    72,    38,    13,    72,    35,    -1,    11,    39,
      14,    40,    35,    -1,    11,    39,    14,    37,    72,    38,
      40,    35,    -1,    12,    39,    72,    40,    35,    -1,    21,
      39,    72,    40,    22,    70,    23,    35,    -1,    21,    39,
      72,    40,    22,    70,    24,    70,    23,    35,    -1,    15,
      39,    72,    40,    16,    70,    17,    35,    -1,    29,    72,
      35,    -1,    72,     5,    72,    -1,    72,     6,    72,    -1,
      72,     7,    72,    -1,    72,    10,    72,    -1,    72,     8,
      72,    -1,    72,    33,    72,    -1,    39,    72,    40,    -1,
       7,    72,    -1,    72,     9,    72,    -1,    72,    18,    72,
      -1,    72,    19,    72,    -1,    20,    72,    -1,     3,    -1,
       4,    -1,    14,    -1,    14,    37,    72,    38,    -1,    14,
      39,    73,    40,    -1,    72,    -1,    73,    36,    72,    -1,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   216,   216,   218,   219,   222,   234,   235,   238,   241,
     242,   244,   245,   246,   250,   251,   252,   255,   256,   259,
     260,   263,   265,   266,   268,   274,   281,   282,   285,   286,
     290,   291,   294,   315,   316,   319,   338,   339,   342,   345,
     346,   348,   351,   352,   356,   359,   360,   362,   367,   370,
     393,   409,   429,   443,   450,   460,   470,   480,   491,   497,
     502,   507,   512,   517,   527,   529,   534,   539,   545,   550,
     557,   559,   566,   588,   602,   627,   633,   637
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUMBER", "BOOLEAN_NUMBER", "P", "M",
  "S", "D", "C", "R", "READ", "WRITE", "ASSIGN_OP", "ID", "WHILE", "DO",
  "ENDWHILE", "AND", "OR", "NOT", "IF", "THEN", "ENDIF", "ELSE", "DECL",
  "ENDDECL", "INT", "BOOL", "RETURN", "MAIN", "BEG", "END", "RELOP",
  "UMINUS", "';'", "','", "'['", "']'", "'('", "')'", "'&'", "'{'", "'}'",
  "$accept", "start", "Declblock", "Declist", "decl", "Idlist", "Ids",
  "arglist", "fArgdef", "farglist", "arg", "argIDlist", "argID", "argtype",
  "Type", "fDefblock", "fDef", "Rtype", "Mainblock", "fBlock", "LDefblock",
  "LDlist", "LDecl", "LIdlist", "LId", "stmtblock", "stmts", "stmt",
  "expr", "exprlist", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,    59,    44,    91,    93,    40,
      41,    38,   123,   125
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    44,    45,    45,    45,    46,    47,    47,    48,    49,
      49,    50,    50,    50,    51,    51,    51,    52,    52,    53,
      53,    54,    55,    55,    56,    56,    57,    57,    58,    58,
      59,    59,    60,    61,    61,    62,    63,    63,    64,    65,
      65,    66,    67,    67,    68,    69,    69,    70,    70,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    72,    72,
      72,    72,    72,    72,    72,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    73,    73,    73
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     1,     2,     3,     1,     2,     3,     3,
       1,     1,     4,     4,     1,     3,     0,     1,     0,     1,
       3,     2,     1,     3,     1,     2,     1,     1,     1,     1,
       2,     1,     8,     1,     1,     7,     2,     1,     3,     1,
       2,     3,     3,     1,     1,     3,     2,     2,     1,     4,
       7,     5,     8,     5,     8,    10,     8,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     3,     3,     3,     2,
       1,     1,     1,     4,     4,     1,     3,     0
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     3,    28,    29,     0,     6,
       0,     0,     1,    33,    34,     0,    31,     0,     4,     5,
       7,    11,     0,    10,     0,    30,     2,     0,     0,    16,
       8,     0,     0,    18,     0,    26,    27,     0,    14,     0,
       9,     0,     0,    17,    19,    12,     0,    13,    24,     0,
      21,    22,     0,     0,     0,     0,    37,     0,     0,    15,
      25,     0,     0,     0,    39,     0,     0,     0,     0,     0,
       0,    46,     0,    48,    35,    36,     0,    20,    23,    44,
       0,    43,    38,    40,     0,     0,     0,     0,     0,     0,
      70,    71,     0,    72,     0,     0,     0,    45,    47,     0,
      41,     0,     0,     0,     0,     0,     0,     0,    65,     0,
      77,    69,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    57,    32,    42,     0,     0,     0,    49,     0,
       0,     0,     0,    75,     0,    64,    58,    59,    60,    62,
      66,    61,    67,    68,    63,     0,    51,    53,     0,     0,
       0,    73,     0,    74,     0,     0,     0,     0,    76,     0,
      50,     0,     0,     0,    52,    56,    54,     0,     0,    55
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,     8,     9,    22,    23,    37,    42,    43,
      38,    50,    51,    39,    10,    15,    16,    17,     5,    54,
      55,    63,    64,    80,    81,    56,    72,    73,    96,   134
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -144
static const yytype_int16 yypact[] =
{
      40,    49,   -14,    21,    69,  -144,  -144,  -144,    26,  -144,
      10,    20,  -144,   -14,  -144,    69,  -144,    59,  -144,  -144,
    -144,    33,    47,  -144,    58,  -144,  -144,    54,    98,    90,
    -144,    10,    91,    90,    96,  -144,  -144,   -21,  -144,    -1,
    -144,   -16,   104,   110,  -144,  -144,    90,  -144,  -144,   132,
     111,  -144,    49,   246,   105,   118,  -144,   112,    90,  -144,
    -144,    -1,   139,    53,  -144,   116,   126,    14,   128,   129,
      35,  -144,   258,  -144,  -144,  -144,   -16,  -144,  -144,  -144,
      84,  -144,  -144,  -144,   142,    35,    35,    35,    35,    35,
    -144,  -144,    35,    55,    35,    35,   176,  -144,  -144,   115,
    -144,   139,    29,    38,   207,   133,    81,    97,  -144,    35,
      35,   327,   117,    35,    35,    35,    35,    35,    35,    35,
      35,    35,  -144,  -144,  -144,    35,   134,   135,  -144,   161,
     174,   169,   154,   244,   -18,  -144,    52,   119,    52,   119,
     122,   183,   103,   103,   327,   170,  -144,  -144,    35,   302,
     302,  -144,    35,  -144,   156,   213,   286,   270,   244,   162,
    -144,   163,   164,   302,  -144,  -144,  -144,   297,   165,  -144
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -144,  -144,  -144,  -144,   193,  -144,   171,  -144,  -144,  -144,
      17,  -144,   143,  -144,   -40,  -144,   190,  -144,    13,   130,
    -144,  -144,   144,  -144,   109,   172,  -143,   -72,   -84,  -144
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_int16 yytable[] =
{
      98,   103,   104,   105,   106,   107,   156,   157,   108,    52,
     111,   112,    62,    48,    46,    53,    11,    18,   152,    47,
     167,    12,   153,    62,    21,   132,   133,    86,    26,   136,
     137,   138,   139,   140,   141,   142,   143,   144,    90,    91,
      49,   145,    92,   113,   114,   115,   116,   117,   118,    93,
      44,    87,    19,     6,     7,    94,   119,   120,   114,    24,
     116,   117,   118,    59,   155,     1,   125,     2,   158,   126,
      28,   121,    29,    27,    95,    77,     6,     7,   127,    82,
       6,     7,    30,    31,    98,    98,   113,   114,   115,   116,
     117,   118,   109,    33,   110,    98,    13,    14,    32,   119,
     120,    34,   113,   114,   115,   116,   117,   118,   113,   114,
     115,   116,   117,   118,   121,   119,   120,    35,    36,   100,
     101,   130,   113,   114,   115,   116,   117,   118,   117,   118,
     121,    -1,   118,    41,    45,   119,   120,   131,   113,   114,
     115,   116,   117,   118,    57,    58,    60,    61,    74,    53,
     121,   119,   120,    79,    76,    84,   102,   135,   123,   113,
     114,   115,   116,   117,   118,    85,   121,    88,    89,   146,
     147,   129,   119,   120,   148,   113,   114,   115,   116,   117,
     118,   113,   114,   115,   116,   117,   118,   121,   119,   120,
     149,   150,   151,    -1,   119,   120,   159,   164,   165,   166,
     169,    20,    40,   121,    78,    25,    99,    83,   154,   121,
     124,   122,   113,   114,   115,   116,   117,   118,   113,   114,
     115,   116,   117,   118,     0,   119,   120,    75,     0,     0,
       0,   119,   120,     0,     0,     0,     0,     0,     0,     0,
     121,     0,   128,     0,     0,     0,   121,     0,   160,   113,
     114,   115,   116,   117,   118,     0,     0,    65,    66,     0,
      67,    68,   119,   120,     0,     0,     0,    69,     0,    65,
      66,     0,    67,    68,     0,    70,     0,   121,    71,    69,
       0,    65,    66,     0,    67,    68,     0,    70,     0,     0,
      97,    69,     0,   162,   163,     0,     0,    65,    66,    70,
      67,    68,     0,   161,     0,     0,     0,    69,    65,    66,
       0,    67,    68,    65,    66,    70,    67,    68,    69,     0,
     168,     0,     0,    69,     0,     0,    70,     0,     0,     0,
       0,    70,   113,   114,   115,   116,   117,   118,     0,     0,
       0,     0,     0,     0,     0,   119,   120
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-144))

#define yytable_value_is_error(yytable_value) \
  ((yytable_value) == (-1))

static const yytype_int16 yycheck[] =
{
      72,    85,    86,    87,    88,    89,   149,   150,    92,    25,
      94,    95,    52,    14,    35,    31,    30,     4,    36,    40,
     163,     0,    40,    63,    14,   109,   110,    13,    15,   113,
     114,   115,   116,   117,   118,   119,   120,   121,     3,     4,
      41,   125,     7,     5,     6,     7,     8,     9,    10,    14,
      33,    37,    26,    27,    28,    20,    18,    19,     6,    39,
       8,     9,    10,    46,   148,    25,    37,    27,   152,    40,
      37,    33,    39,    14,    39,    58,    27,    28,    40,    26,
      27,    28,    35,    36,   156,   157,     5,     6,     7,     8,
       9,    10,    37,    39,    39,   167,    27,    28,    40,    18,
      19,     3,     5,     6,     7,     8,     9,    10,     5,     6,
       7,     8,     9,    10,    33,    18,    19,    27,    28,    35,
      36,    40,     5,     6,     7,     8,     9,    10,     9,    10,
      33,     9,    10,    42,    38,    18,    19,    40,     5,     6,
       7,     8,     9,    10,    40,    35,    14,    36,    43,    31,
      33,    18,    19,    14,    42,    39,    14,    40,    43,     5,
       6,     7,     8,     9,    10,    39,    33,    39,    39,    35,
      35,    38,    18,    19,    13,     5,     6,     7,     8,     9,
      10,     5,     6,     7,     8,     9,    10,    33,    18,    19,
      16,    22,    38,    10,    18,    19,    40,    35,    35,    35,
      35,     8,    31,    33,    61,    15,    76,    63,    38,    33,
     101,    35,     5,     6,     7,     8,     9,    10,     5,     6,
       7,     8,     9,    10,    -1,    18,    19,    55,    -1,    -1,
      -1,    18,    19,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      33,    -1,    35,    -1,    -1,    -1,    33,    -1,    35,     5,
       6,     7,     8,     9,    10,    -1,    -1,    11,    12,    -1,
      14,    15,    18,    19,    -1,    -1,    -1,    21,    -1,    11,
      12,    -1,    14,    15,    -1,    29,    -1,    33,    32,    21,
      -1,    11,    12,    -1,    14,    15,    -1,    29,    -1,    -1,
      32,    21,    -1,    23,    24,    -1,    -1,    11,    12,    29,
      14,    15,    -1,    17,    -1,    -1,    -1,    21,    11,    12,
      -1,    14,    15,    11,    12,    29,    14,    15,    21,    -1,
      23,    -1,    -1,    21,    -1,    -1,    29,    -1,    -1,    -1,
      -1,    29,     5,     6,     7,     8,     9,    10,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    18,    19
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    25,    27,    45,    46,    62,    27,    28,    47,    48,
      58,    30,     0,    27,    28,    59,    60,    61,    62,    26,
      48,    14,    49,    50,    39,    60,    62,    14,    37,    39,
      35,    36,    40,    39,     3,    27,    28,    51,    54,    57,
      50,    42,    52,    53,    54,    38,    35,    40,    14,    41,
      55,    56,    25,    31,    63,    64,    69,    40,    35,    54,
      14,    36,    58,    65,    66,    11,    12,    14,    15,    21,
      29,    32,    70,    71,    43,    69,    42,    54,    56,    14,
      67,    68,    26,    66,    39,    39,    13,    37,    39,    39,
       3,     4,     7,    14,    20,    39,    72,    32,    71,    63,
      35,    36,    14,    72,    72,    72,    72,    72,    72,    37,
      39,    72,    72,     5,     6,     7,     8,     9,    10,    18,
      19,    33,    35,    43,    68,    37,    40,    40,    35,    38,
      40,    40,    72,    72,    73,    40,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    35,    35,    13,    16,
      22,    38,    36,    40,    38,    72,    70,    70,    72,    40,
      35,    17,    23,    24,    35,    35,    35,    70,    23,    35
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1806 of yacc.c  */
#line 216 "cg_calc.y"
    {  }
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 218 "cg_calc.y"
    {}
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 219 "cg_calc.y"
    {}
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 222 "cg_calc.y"
    {  
							  fp = fopen("sil.asm","a");
							  int i=0;
							  for(i=0;i<memcount;i++)              							            {
                                                               fprintf(fp,"\nPUSH R%d",regcount+1);
						 	    }						
							 memcount = 1;							
							 fprintf(fp,"\nJMP main");
							 fclose(fp);	    
                                                       }
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 234 "cg_calc.y"
    {}
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 235 "cg_calc.y"
    {}
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 238 "cg_calc.y"
    {}
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 241 "cg_calc.y"
    {}
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 244 "cg_calc.y"
    {    Ginstall((yyvsp[(1) - (1)].ptr)->NAME,typeval,1,NULL); }
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 245 "cg_calc.y"
    {     Ginstall((yyvsp[(1) - (4)].ptr)->NAME,typeval,(yyvsp[(3) - (4)].ptr)->VALUE,NULL); }
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 246 "cg_calc.y"
    {     Ginstall((yyvsp[(1) - (4)].ptr)->NAME,typeval,0,headArg); 
                                        headArg = NULL;           }
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 250 "cg_calc.y"
    {}
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 251 "cg_calc.y"
    { }
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 252 "cg_calc.y"
    {}
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 255 "cg_calc.y"
    { argInstall(headArg);}
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 256 "cg_calc.y"
    {}
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 259 "cg_calc.y"
    {}
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 260 "cg_calc.y"
    {}
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 263 "cg_calc.y"
    {}
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 265 "cg_calc.y"
    { makeArglist(newArg);}
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 266 "cg_calc.y"
    { makeArglist(newArg);}
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 268 "cg_calc.y"
    {                                      newArg = malloc(sizeof(struct Argument_Struct )); 
							newArg->ARG_NAME = (yyvsp[(1) - (1)].ptr)->NAME;
							newArg->ARG_TYPE = arg_typeval;
							newArg->ARG_PASS_TYPE = 0;
							newArg->ARG_NEXT = NULL; }
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 274 "cg_calc.y"
    {    newArg = malloc(sizeof(struct Argument_Struct ));
							newArg->ARG_NAME = (yyvsp[(2) - (2)].ptr)->NAME;
							newArg->ARG_TYPE = arg_typeval;
							newArg->ARG_PASS_TYPE =1;
							newArg->ARG_NEXT = NULL;}
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 281 "cg_calc.y"
    { arg_typeval = INTEGER ; }
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 282 "cg_calc.y"
    { arg_typeval = BOOL ; }
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 285 "cg_calc.y"
    {    typeval=INTEGER; }
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 286 "cg_calc.y"
    {    typeval=BOOLEAN;	}
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 290 "cg_calc.y"
    {}
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 291 "cg_calc.y"
    {}
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 294 "cg_calc.y"
    {  fnDefCheck(ret_typeval, (yyvsp[(2) - (8)].ptr)->NAME, headArg);
							 
							 fp = fopen("sil.asm","a");
							 fprintf(fp,"\nfn%d:", fnlabel);
							 fnlabel++;
							 fprintf(fp,"\nPUSH BP");
							 fprintf(fp,"\nMOV BP,SP");
							 int i=1;
							 for(i=1;i<memcount;i++)  //pushing the local variable ,as for function memcount starts from 1
							  	fprintf(fp,"\nPUSH R%d",0);
							 
							headArg=NULL;  // job of headArg is completed(for fnDefCheck) so now initialize it with NULL 
							calculate(temp_head); // print code for the body of the function.
							memcount=1;
							 root_L= NULL;  //
							 temp_head=NULL;
                                                         fclose(fp);
                                                                 }
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 315 "cg_calc.y"
    { ret_typeval = INTEGER ; }
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 316 "cg_calc.y"
    { ret_typeval = BOOLEAN ; }
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 319 "cg_calc.y"
    {   
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
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 338 "cg_calc.y"
    {}
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 339 "cg_calc.y"
    { }
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 342 "cg_calc.y"
    {}
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 345 "cg_calc.y"
    {}
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 346 "cg_calc.y"
    {}
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 348 "cg_calc.y"
    {}
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 351 "cg_calc.y"
    {	}
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 352 "cg_calc.y"
    {}
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 356 "cg_calc.y"
    {   Linstall((yyvsp[(1) - (1)].ptr)->NAME, typeval); }
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 359 "cg_calc.y"
    {  temp_head = (yyvsp[(2) - (3)].ptr); }
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 360 "cg_calc.y"
    {}
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 362 "cg_calc.y"
    {  
							struct node * t1 = malloc(sizeof(struct node));
			                                t1->NODE_TYPE = VOID;
                	                               	(yyval.ptr)=makenode(t1,(yyvsp[(1) - (2)].ptr),(yyvsp[(2) - (2)].ptr),NULL); 
						   }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 367 "cg_calc.y"
    {    (yyval.ptr)=(yyvsp[(1) - (1)].ptr);   }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 370 "cg_calc.y"
    {     struct Lsymbol_table * temp = LLOOKUP((yyvsp[(1) - (4)].ptr)->NAME);
                                                         if(!temp)
                                                       {   
                                                         struct Gsymbol_table* gtemp = GLOOKUP((yyvsp[(1) - (4)].ptr)->NAME);
                                                         if(gtemp==NULL || gtemp->SIZE!=1) yyerror("Undefined Variable");
                                                         else
							       {
							     	 (yyvsp[(1) - (4)].ptr)->GENTRY = gtemp;
							     	 (yyvsp[(1) - (4)].ptr)->TYPE = gtemp->TYPE;
							       }
                                                       }
                                                       else 
                                                      {  (yyvsp[(1) - (4)].ptr)->LENTRY = temp;
                                                         (yyvsp[(1) - (4)].ptr)->TYPE = temp->TYPE ;
                                                      } 

							if((yyvsp[(1) - (4)].ptr)->TYPE == (yyvsp[(3) - (4)].ptr)->TYPE) 
							 	(yyval.ptr)=makenode((yyvsp[(2) - (4)].ptr),(yyvsp[(1) - (4)].ptr),NULL,(yyvsp[(3) - (4)].ptr));
							  else
							  	{ yyerror("Type Mismatch");}       
                                                         
                                                       	
                                                   }
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 393 "cg_calc.y"
    { 
							  struct Gsymbol_table* temp = GLOOKUP((yyvsp[(1) - (7)].ptr)->NAME);
							  if(temp==NULL || temp->SIZE==1) yyerror("Undefined Array");
							  else
							       {
							     	 (yyvsp[(1) - (7)].ptr)->TYPE = temp->TYPE;
							       }
							 if((yyvsp[(1) - (7)].ptr)->TYPE == (yyvsp[(6) - (7)].ptr)->TYPE) 
							 	{ (yyvsp[(1) - (7)].ptr)->GENTRY = temp;
							 	  (yyval.ptr) = makenode((yyvsp[(5) - (7)].ptr), (yyvsp[(1) - (7)].ptr), (yyvsp[(3) - (7)].ptr), (yyvsp[(6) - (7)].ptr));
							 	}
							  else
							  	yyerror("Type Mismatch"); 	
		
							}
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 409 "cg_calc.y"
    {       struct Lsymbol_table * temp = LLOOKUP((yyvsp[(3) - (5)].ptr)->NAME);
                                                        if(temp ==NULL)
                                                   { 
                                                         struct Gsymbol_table* gtemp = GLOOKUP((yyvsp[(3) - (5)].ptr)->NAME);
                                                        if(gtemp == NULL || gtemp->TYPE == BOOLEAN || gtemp->SIZE != 1)
                                                           { yyerror("Undefined variable in READ or You are taking input in a boolean variable which is not allowed here");
                                                           }   
                                                                                                             
                                                       else{ 
                                                               (yyvsp[(3) - (5)].ptr)->GENTRY = gtemp;
                                                              (yyval.ptr)=makenode((yyvsp[(1) - (5)].ptr),(yyvsp[(3) - (5)].ptr),NULL,NULL);
                                                            }
                                                   }
                                             else { (yyvsp[(3) - (5)].ptr)->LENTRY = temp;
                                                    (yyval.ptr) = makenode((yyvsp[(1) - (5)].ptr),(yyvsp[(3) - (5)].ptr),NULL,NULL);                    
                                                   }
                                          
            
                                                  }
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 429 "cg_calc.y"
    {   struct Gsymbol_table * temp = GLOOKUP((yyvsp[(3) - (8)].ptr)->NAME);
                                                      
					 		 if(temp == NULL || temp->SIZE == 1 || temp ->TYPE == BOOLEAN)
					 		   {
					 		     yyerror("Undefined array in READ or you are using a non integer array in Read");
					 		   }
					 		  else
					 		    { 
					 		      (yyvsp[(3) - (8)].ptr)->GENTRY = temp;
					 		      (yyval.ptr) = makenode((yyvsp[(1) - (8)].ptr), (yyvsp[(3) - (8)].ptr), (yyvsp[(5) - (8)].ptr), NULL);
							      
							    }
							}
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 443 "cg_calc.y"
    {	if((yyvsp[(3) - (5)].ptr)->TYPE == INTEGER) 
                                                       {
                                                         (yyval.ptr)=makenode((yyvsp[(1) - (5)].ptr),(yyvsp[(3) - (5)].ptr),NULL,NULL);
                                                        }
                                                        else { yyerror("Type Mismatch,Type of expression inside WRITE should be integer") ; }

                                                }
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 450 "cg_calc.y"
    {   struct node * t1 = malloc(sizeof(struct node));
	                                                     t1->NODE_TYPE = IF_THEN;
 						         if((yyvsp[(3) - (8)].ptr)->TYPE == BOOLEAN)    
                                                            {
                                                               (yyval.ptr)=makenode(t1,(yyvsp[(3) - (8)].ptr),(yyvsp[(6) - (8)].ptr),NULL);
                                                            } 

                                                         else { yyerror("Type Mismatch , expr inside IF should be of boolean type "); }
 
                                                        }
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 460 "cg_calc.y"
    {   struct node * t1 = malloc(sizeof(struct node));
	                                                     t1->NODE_TYPE = IF_THEN;
 						         if((yyvsp[(3) - (10)].ptr)->TYPE == BOOLEAN)   
                                                            { 
                                                              (yyval.ptr)=makenode(t1,(yyvsp[(3) - (10)].ptr),(yyvsp[(6) - (10)].ptr),(yyvsp[(8) - (10)].ptr)); 
                                                             }
                                                         else { yyerror("Type Mismatch , expr inside IF should be of boolean type "); }
                                                         }
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 470 "cg_calc.y"
    {   struct node * t1 = malloc(sizeof(struct node));
	                                                     t1->NODE_TYPE = WHILE_LOOP;
 						             if((yyvsp[(3) - (8)].ptr)->TYPE == BOOLEAN)
                                                              {
                                                                  (yyval.ptr)=makenode(t1,(yyvsp[(3) - (8)].ptr),(yyvsp[(6) - (8)].ptr),NULL);
                                                              }
                                                         else { yyerror("Type Mismatch , expr inside WHILE should be of boolean type "); }
 
                                                          }
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 480 "cg_calc.y"
    {      struct node * t1 = malloc(sizeof(struct node));
			                                t1->NODE_TYPE = RETURN_NODE;
                                                         if(ret_typeval == (yyvsp[(2) - (3)].ptr)->TYPE)
                	                               	   { 
                                                              (yyval.ptr)=makenode(t1,NULL,(yyvsp[(2) - (3)].ptr),NULL);
                                                            }
                                                        else { yyerror("Type mismatch in return statment"); }
                                                  }
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 491 "cg_calc.y"
    {	if( (yyvsp[(1) - (3)].ptr)->TYPE == (yyvsp[(2) - (3)].ptr)->TYPE && (yyvsp[(2) - (3)].ptr)->TYPE == (yyvsp[(3) - (3)].ptr)->TYPE )
						   	(yyval.ptr)=makenode((yyvsp[(2) - (3)].ptr),(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr),NULL);
						  else
						  	{ yyerror("Type Mismatch"); } 
                                                         
                                                }
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 497 "cg_calc.y"
    {       if( (yyvsp[(1) - (3)].ptr)->TYPE == (yyvsp[(2) - (3)].ptr)->TYPE && (yyvsp[(2) - (3)].ptr)->TYPE == (yyvsp[(3) - (3)].ptr)->TYPE )
						   	  (yyval.ptr)=makenode((yyvsp[(2) - (3)].ptr),(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr),NULL);
						  else
						  	{ yyerror("Type Mismatch");   } 
                                                }
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 502 "cg_calc.y"
    {	if( (yyvsp[(1) - (3)].ptr)->TYPE == (yyvsp[(2) - (3)].ptr)->TYPE && (yyvsp[(2) - (3)].ptr)->TYPE == (yyvsp[(3) - (3)].ptr)->TYPE )
						   	  (yyval.ptr)=makenode((yyvsp[(2) - (3)].ptr),(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr),NULL);
						  else
						  	{ yyerror("Type Mismatch");   } 
                                                }
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 507 "cg_calc.y"
    {  if( (yyvsp[(1) - (3)].ptr)->TYPE == (yyvsp[(2) - (3)].ptr)->TYPE && (yyvsp[(2) - (3)].ptr)->TYPE == (yyvsp[(3) - (3)].ptr)->TYPE )
						   	  (yyval.ptr)=makenode((yyvsp[(2) - (3)].ptr),(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr),NULL);
						  else
						  	{ yyerror("Type Mismatch");   } 
                                                }
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 512 "cg_calc.y"
    {	if( (yyvsp[(1) - (3)].ptr)->TYPE == (yyvsp[(2) - (3)].ptr)->TYPE && (yyvsp[(2) - (3)].ptr)->TYPE == (yyvsp[(3) - (3)].ptr)->TYPE )
						   	  (yyval.ptr)=makenode((yyvsp[(2) - (3)].ptr),(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr),NULL);
						  else
						  	{ yyerror("Type Mismatch");   } 
                                                 }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 517 "cg_calc.y"
    {   if( (yyvsp[(1) - (3)].ptr)->TYPE == (yyvsp[(3) - (3)].ptr)->TYPE && (yyvsp[(1) - (3)].ptr)->TYPE == INTEGER )
						   	 (yyval.ptr)=makenode((yyvsp[(2) - (3)].ptr),(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr),NULL); 
						  else
						  	yyerror("Type Mismatch for Boolean Operator");  
                                                      
                                                }
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 527 "cg_calc.y"
    {	(yyval.ptr)=(yyvsp[(2) - (3)].ptr);}
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 529 "cg_calc.y"
    {	if((yyvsp[(1) - (2)].ptr)->TYPE == (yyvsp[(2) - (2)].ptr)->TYPE)
                                                          { (yyval.ptr)=makenode((yyvsp[(1) - (2)].ptr),(yyvsp[(2) - (2)].ptr),NULL,NULL);
                                                          }
                                                         else { yyerror("Type Mismatch"); }
                                                }
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 534 "cg_calc.y"
    {	if( (yyvsp[(1) - (3)].ptr)->TYPE == (yyvsp[(2) - (3)].ptr)->TYPE && (yyvsp[(2) - (3)].ptr)->TYPE == (yyvsp[(3) - (3)].ptr)->TYPE )
						   	  (yyval.ptr)=makenode((yyvsp[(2) - (3)].ptr),(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr),NULL);
						  else
						  	{ yyerror("Type Mismatch");   }
                                                }
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 539 "cg_calc.y"
    {  if( (yyvsp[(1) - (3)].ptr)->TYPE == (yyvsp[(3) - (3)].ptr)->TYPE && (yyvsp[(1) - (3)].ptr)->TYPE == BOOLEAN )
						   	 (yyval.ptr)=makenode((yyvsp[(2) - (3)].ptr),(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr),NULL); 
						  else
						  	yyerror("Type Mismatch for AND Operator");  
                                                    
                                              }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 545 "cg_calc.y"
    {  if( (yyvsp[(1) - (3)].ptr)->TYPE == (yyvsp[(3) - (3)].ptr)->TYPE && (yyvsp[(1) - (3)].ptr)->TYPE == BOOLEAN )
						   	 (yyval.ptr)=makenode((yyvsp[(2) - (3)].ptr),(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr),NULL); 
						  else
						  	yyerror("Type Mismatch for OR Operator");   
                                           }
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 550 "cg_calc.y"
    {   if( (yyvsp[(2) - (2)].ptr)->TYPE== BOOLEAN )
						   	(yyval.ptr) = makenode((yyvsp[(1) - (2)].ptr), NULL, (yyvsp[(2) - (2)].ptr), NULL);
						  else
						  	yyerror("Type Mismatch for NOT Operator");
                                           }
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 557 "cg_calc.y"
    {	(yyval.ptr)=(yyvsp[(1) - (1)].ptr);}
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 559 "cg_calc.y"
    { (yyval.ptr)=(yyvsp[(1) - (1)].ptr);
                                                  (yyval.ptr)->TYPE = BOOLEAN; 
                                                }
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 566 "cg_calc.y"
    {                                                                  
                                                        (yyval.ptr) = (yyvsp[(1) - (1)].ptr);
                                                  struct Lsymbol_table * ltemp = LLOOKUP((yyval.ptr)->NAME);
                                                 if(ltemp == NULL) 
                                                 {
						   struct Gsymbol_table* temp = GLOOKUP((yyval.ptr)->NAME);
						  
						   if(temp==NULL || temp->SIZE != 1)
                                                     yyerror("Undefined Variable in Expression");
						   else
						       {
						       	 (yyval.ptr)->GENTRY = temp;
						     	 (yyval.ptr)->TYPE = temp->TYPE;
						       }
						  }
                                                 else 
                                                  {
                                                       (yyval.ptr)->LENTRY = ltemp ;
                                                       (yyval.ptr)->TYPE = ltemp->TYPE;
                                                  }
                                                }
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 588 "cg_calc.y"
    {
		 				  (yyval.ptr) = makenode((yyvsp[(1) - (4)].ptr),(yyvsp[(3) - (4)].ptr),NULL,NULL);
		 				  struct Gsymbol_table* temp = GLOOKUP((yyval.ptr)->NAME);
					      	  if(temp==NULL || temp->SIZE == 1 ) 
                                                    yyerror("Undefined Array is being used");
					          else
					           {
					       		 (yyval.ptr)->GENTRY = temp;
					     	 	 (yyval.ptr)->TYPE = temp->TYPE;
					     	   }
						  
						 }
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 602 "cg_calc.y"
    {    
	        
                                                     struct Gsymbol_table* gtemp = GLOOKUP((yyvsp[(1) - (4)].ptr)->NAME);
                                                      printf("%d %s - ",gtemp->BINDING,gtemp->NAME);
						      if(gtemp==NULL || gtemp->SIZE!=0) yyerror("Undefined Function");
						      else
						       { 
                                                         arg_parameter = (yyvsp[(3) - (4)].ptr);
                                                         arg_check(gtemp->ARG_LIST); //check the arguments for type and passing type using global symbol table
                                                      if(arg_parameter)
                                                         yyerror("mismatch argument in function call");
                                                         
						       	 (yyval.ptr)= (yyvsp[(1) - (4)].ptr);
                                                         (yyval.ptr)->GENTRY = gtemp;
                                                         (yyval.ptr)->NODE_TYPE = FUNCTION_NODE;
						     	 (yyval.ptr)->TYPE = gtemp->TYPE;
						     	 (yyval.ptr)->P1 = (yyvsp[(3) - (4)].ptr);
						       }


                                           }
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 627 "cg_calc.y"
    {   struct node * t1 = malloc(sizeof(struct node));
                                       t1->NODE_TYPE = VOID ;
                                       (yyval.ptr) = makenode(t1,NULL,(yyvsp[(1) - (1)].ptr),NULL);                                    
                                   
                                   }
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 633 "cg_calc.y"
    {    struct node * t1 = malloc(sizeof(struct node));
                                       t1->NODE_TYPE = VOID ;
                                       (yyval.ptr) = makenode(t1,(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr),NULL);   
                                  }
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 637 "cg_calc.y"
    { (yyval.ptr) = NULL ; }
    break;



/* Line 1806 of yacc.c  */
#line 2578 "y.tab.c"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 2067 of yacc.c  */
#line 641 "cg_calc.y"


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
                       int temp_regcount = regcount;  // for keeping the track of pushing and poping the register
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

