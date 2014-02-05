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




/* Line 268 of yacc.c  */
#line 198 "y.tab.c"

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
     END = 260,
     START = 261,
     P = 262,
     M = 263,
     S = 264,
     D = 265,
     C = 266,
     R = 267,
     READ = 268,
     WRITE = 269,
     ASSIGN_OP = 270,
     ID = 271,
     WHILE = 272,
     DO = 273,
     ENDWHILE = 274,
     IF = 275,
     THEN = 276,
     ENDIF = 277,
     ELSE = 278,
     DECL = 279,
     ENDDECL = 280,
     INT = 281,
     BOOL = 282,
     RELOP = 283,
     UMINUS = 284
   };
#endif
/* Tokens.  */
#define NUMBER 258
#define BOOLEAN_NUMBER 259
#define END 260
#define START 261
#define P 262
#define M 263
#define S 264
#define D 265
#define C 266
#define R 267
#define READ 268
#define WRITE 269
#define ASSIGN_OP 270
#define ID 271
#define WHILE 272
#define DO 273
#define ENDWHILE 274
#define IF 275
#define THEN 276
#define ENDIF 277
#define ELSE 278
#define DECL 279
#define ENDDECL 280
#define INT 281
#define BOOL 282
#define RELOP 283
#define UMINUS 284




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 129 "cg_calc.y"

	struct node *ptr;
	



/* Line 293 of yacc.c  */
#line 299 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 311 "y.tab.c"

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
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   184

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  36
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  12
/* YYNRULES -- Number of rules.  */
#define YYNRULES  36
/* YYNRULES -- Number of states.  */
#define YYNSTATES  97

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   284

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      34,    35,     2,     2,    31,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    30,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    32,     2,    33,     2,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     6,    10,    12,    15,    19,    23,    25,
      27,    32,    34,    36,    40,    43,    45,    50,    58,    64,
      73,    79,    88,    99,   108,   112,   116,   120,   124,   128,
     132,   136,   139,   143,   145,   147,   149
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      37,     0,    -1,    38,    44,    -1,    24,    39,    25,    -1,
      40,    -1,    39,    40,    -1,    43,    41,    30,    -1,    41,
      31,    42,    -1,    42,    -1,    16,    -1,    16,    32,     3,
      33,    -1,    26,    -1,    27,    -1,     6,    45,     5,    -1,
      45,    46,    -1,    46,    -1,    16,    15,    47,    30,    -1,
      16,    32,    47,    33,    15,    47,    30,    -1,    13,    34,
      16,    35,    30,    -1,    13,    34,    16,    32,    47,    33,
      35,    30,    -1,    14,    34,    47,    35,    30,    -1,    20,
      34,    47,    35,    21,    45,    22,    30,    -1,    20,    34,
      47,    35,    21,    45,    23,    45,    22,    30,    -1,    17,
      34,    47,    35,    18,    45,    19,    30,    -1,    47,     7,
      47,    -1,    47,     8,    47,    -1,    47,     9,    47,    -1,
      47,    12,    47,    -1,    47,    10,    47,    -1,    47,    28,
      47,    -1,    34,    47,    35,    -1,     9,    47,    -1,    47,
      11,    47,    -1,     3,    -1,     4,    -1,    16,    -1,    16,
      32,    47,    33,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   149,   149,   154,   157,   158,   161,   164,   165,   167,
     168,   171,   172,   175,   185,   190,   193,   209,   225,   237,
     251,   253,   256,   261,   267,   273,   278,   283,   288,   293,
     299,   301,   306,   312,   314,   321,   333
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUMBER", "BOOLEAN_NUMBER", "END",
  "START", "P", "M", "S", "D", "C", "R", "READ", "WRITE", "ASSIGN_OP",
  "ID", "WHILE", "DO", "ENDWHILE", "IF", "THEN", "ENDIF", "ELSE", "DECL",
  "ENDDECL", "INT", "BOOL", "RELOP", "UMINUS", "';'", "','", "'['", "']'",
  "'('", "')'", "$accept", "start", "Declblock", "Declist", "decl",
  "Idlist", "Ids", "Type", "Mainblock", "stmts", "stmt", "expr", 0
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
      59,    44,    91,    93,    40,    41
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    36,    37,    38,    39,    39,    40,    41,    41,    42,
      42,    43,    43,    44,    45,    45,    46,    46,    46,    46,
      46,    46,    46,    46,    47,    47,    47,    47,    47,    47,
      47,    47,    47,    47,    47,    47,    47
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     3,     1,     2,     3,     3,     1,     1,
       4,     1,     1,     3,     2,     1,     4,     7,     5,     8,
       5,     8,    10,     8,     3,     3,     3,     3,     3,     3,
       3,     2,     3,     1,     1,     1,     4
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,    11,    12,     0,     4,     0,     1,
       0,     2,     3,     5,     9,     0,     8,     0,     0,     0,
       0,     0,     0,    15,     0,     6,     0,     0,     0,     0,
       0,     0,     0,    13,    14,     0,     7,     0,    33,    34,
       0,    35,     0,     0,     0,     0,     0,     0,    10,     0,
       0,    31,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    16,     0,     0,     0,     0,    18,     0,    30,
      24,    25,    26,    28,    32,    27,    29,    20,     0,     0,
       0,     0,    36,     0,     0,     0,     0,    17,     0,     0,
       0,    19,    23,    21,     0,     0,    22
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     3,     6,     7,    15,    16,     8,    11,    22,
      23,    43
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -71
static const yytype_int16 yypact[] =
{
     -17,    33,    23,    43,   -71,   -71,     8,   -71,    35,   -71,
     158,   -71,   -71,   -71,    29,    37,   -71,    32,    47,    -7,
      60,    73,    99,   -71,   107,   -71,    35,    95,     2,     2,
       2,     2,     2,   -71,   -71,    85,   -71,   -13,   -71,   -71,
       2,    88,     2,    30,   116,    75,    36,    45,   -71,     2,
      91,   -71,     2,    67,     2,     2,     2,     2,     2,     2,
       2,   105,   -71,   121,   119,   128,    81,   -71,    89,   -71,
       5,    58,     5,    58,    94,   131,   172,   -71,     2,   158,
     158,   120,   -71,   122,   150,   125,   110,   -71,   129,   135,
     158,   -71,   -71,   -71,   140,   138,   -71
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -71,   -71,   -71,   -71,   145,   -71,   132,   -71,   -71,   -70,
     -22,   -28
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_int8 yytable[] =
{
      34,    44,    45,    46,    47,    38,    39,     1,    29,    84,
      85,    40,    51,    55,    53,    57,    58,    59,    41,    49,
      94,    66,    50,     9,    68,    30,    70,    71,    72,    73,
      74,    75,    76,    12,     4,     5,    42,    54,    55,    56,
      57,    58,    59,    54,    55,    56,    57,    58,    59,    10,
      83,    14,    54,    55,    56,    57,    58,    59,    60,     4,
       5,    24,    34,    34,    60,    61,    27,    25,    26,    58,
      59,    64,    34,    60,    54,    55,    56,    57,    58,    59,
      65,    28,    54,    55,    56,    57,    58,    59,    54,    55,
      56,    57,    58,    59,    31,    60,    54,    55,    56,    57,
      58,    59,    69,    60,    33,    -1,    59,    32,    63,    60,
      35,    37,    17,    18,    81,    19,    20,    60,    48,    21,
      52,    67,    82,    54,    55,    56,    57,    58,    59,    54,
      55,    56,    57,    58,    59,    77,    78,    79,    17,    18,
      91,    19,    20,    -1,    60,    21,    62,    89,    90,    80,
      60,    13,    87,    17,    18,    86,    19,    20,    36,    92,
      21,     0,    95,    17,    18,    93,    19,    20,    96,    88,
      21,    17,    18,     0,    19,    20,     0,     0,    21,    54,
      55,    56,    57,    58,    59
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-71))

#define yytable_value_is_error(yytable_value) \
  ((yytable_value) == (-1))

static const yytype_int8 yycheck[] =
{
      22,    29,    30,    31,    32,     3,     4,    24,    15,    79,
      80,     9,    40,     8,    42,    10,    11,    12,    16,    32,
      90,    49,    35,     0,    52,    32,    54,    55,    56,    57,
      58,    59,    60,    25,    26,    27,    34,     7,     8,     9,
      10,    11,    12,     7,     8,     9,    10,    11,    12,     6,
      78,    16,     7,     8,     9,    10,    11,    12,    28,    26,
      27,    32,    84,    85,    28,    35,    34,    30,    31,    11,
      12,    35,    94,    28,     7,     8,     9,    10,    11,    12,
      35,    34,     7,     8,     9,    10,    11,    12,     7,     8,
       9,    10,    11,    12,    34,    28,     7,     8,     9,    10,
      11,    12,    35,    28,     5,    11,    12,    34,    33,    28,
       3,    16,    13,    14,    33,    16,    17,    28,    33,    20,
      32,    30,    33,     7,     8,     9,    10,    11,    12,     7,
       8,     9,    10,    11,    12,    30,    15,    18,    13,    14,
      30,    16,    17,    12,    28,    20,    30,    22,    23,    21,
      28,     6,    30,    13,    14,    35,    16,    17,    26,    30,
      20,    -1,    22,    13,    14,    30,    16,    17,    30,    19,
      20,    13,    14,    -1,    16,    17,    -1,    -1,    20,     7,
       8,     9,    10,    11,    12
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    24,    37,    38,    26,    27,    39,    40,    43,     0,
       6,    44,    25,    40,    16,    41,    42,    13,    14,    16,
      17,    20,    45,    46,    32,    30,    31,    34,    34,    15,
      32,    34,    34,     5,    46,     3,    42,    16,     3,     4,
       9,    16,    34,    47,    47,    47,    47,    47,    33,    32,
      35,    47,    32,    47,     7,     8,     9,    10,    11,    12,
      28,    35,    30,    33,    35,    35,    47,    30,    47,    35,
      47,    47,    47,    47,    47,    47,    47,    30,    15,    18,
      21,    33,    33,    47,    45,    45,    35,    30,    19,    22,
      23,    30,    30,    30,    45,    22,    30
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
#line 149 "cg_calc.y"
    {		return(0);
			                        
					   	}
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 154 "cg_calc.y"
    {}
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 157 "cg_calc.y"
    {}
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 158 "cg_calc.y"
    {}
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 161 "cg_calc.y"
    {}
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 164 "cg_calc.y"
    {}
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 167 "cg_calc.y"
    {     install((yyvsp[(1) - (1)].ptr)->NAME,typeval,1); }
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 168 "cg_calc.y"
    {     install((yyvsp[(1) - (4)].ptr)->NAME,typeval,(yyvsp[(3) - (4)].ptr)->VALUE); }
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 171 "cg_calc.y"
    {    typeval=INTEGER; }
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 172 "cg_calc.y"
    {    typeval=BOOLEAN;	}
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 175 "cg_calc.y"
    {	
						fp = fopen("sil.asm","a");
			   			fprintf(fp,"START");
						
                                                calculate((yyvsp[(2) - (3)].ptr));
						fprintf(fp,"\nHALT");                                                          
						fclose(fp);
						exit(1); }
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 185 "cg_calc.y"
    {  
							struct node * t1 = malloc(sizeof(struct node));
			                                t1->NODE_TYPE = VOID;
                	                               	(yyval.ptr)=makenode(t1,(yyvsp[(1) - (2)].ptr),(yyvsp[(2) - (2)].ptr),NULL); 
						   }
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 190 "cg_calc.y"
    {    (yyval.ptr)=(yyvsp[(1) - (1)].ptr);   }
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 193 "cg_calc.y"
    {        
                                                        struct symbol_table* temp = Lookup((yyvsp[(1) - (4)].ptr)->NAME);
                                                        if(temp==NULL || temp->SIZE!=1) yyerror("Undefined Variable");
                                                        
                                                        else
							       {
							     	 (yyvsp[(1) - (4)].ptr)->ENTRY = temp;
							     	 (yyvsp[(1) - (4)].ptr)->TYPE = temp->TYPE;
							       } 
							if((yyvsp[(1) - (4)].ptr)->TYPE == (yyvsp[(3) - (4)].ptr)->TYPE) 
							 	(yyval.ptr)=makenode((yyvsp[(2) - (4)].ptr),(yyvsp[(1) - (4)].ptr),NULL,(yyvsp[(3) - (4)].ptr));
							  else
							  	{ yyerror("Type Mismatch");}       
                                                         
                                                       	
                                                   }
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 209 "cg_calc.y"
    { 
							  struct symbol_table* temp = Lookup((yyvsp[(1) - (7)].ptr)->NAME);
							  if(temp==NULL || temp->SIZE==1) yyerror("Undefined Array");
							  else
							       {
							     	 (yyvsp[(1) - (7)].ptr)->TYPE = temp->TYPE;
							       }
							 if((yyvsp[(1) - (7)].ptr)->TYPE == (yyvsp[(6) - (7)].ptr)->TYPE) 
							 	{ (yyvsp[(1) - (7)].ptr)->ENTRY = temp;
							 	  (yyval.ptr) = makenode((yyvsp[(5) - (7)].ptr), (yyvsp[(1) - (7)].ptr), (yyvsp[(3) - (7)].ptr), (yyvsp[(6) - (7)].ptr));
							 	}
							  else
							  	yyerror("Type Mismatch"); 	
		
							}
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 225 "cg_calc.y"
    {          
                                                         struct symbol_table* temp = Lookup((yyvsp[(3) - (5)].ptr)->NAME);
                                                        if(temp == NULL || temp->TYPE == BOOLEAN)
                                                           { yyerror("Undefined variable in READ or You are taking input in a boolean variable which is not allowed here");
                                                           }   
                                                                                                             
                                                       else{ 
                                                               (yyvsp[(3) - (5)].ptr)->ENTRY = temp;

                                                              (yyval.ptr)=makenode((yyvsp[(1) - (5)].ptr),(yyvsp[(3) - (5)].ptr),NULL,NULL);
                                                            } 
                                                  }
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 237 "cg_calc.y"
    {   struct symbol_table * temp = Lookup((yyvsp[(3) - (8)].ptr)->NAME);
                                                      
					 		 if(temp == NULL )
					 		   {
					 		     yyerror("Undefined array in READ");
					 		   }
					 		  else
					 		    { 
					 		      (yyvsp[(3) - (8)].ptr)->ENTRY = temp;
					 		      (yyval.ptr) = makenode((yyvsp[(1) - (8)].ptr), (yyvsp[(3) - (8)].ptr), (yyvsp[(5) - (8)].ptr), NULL);
							      
							    }
							}
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 251 "cg_calc.y"
    {	(yyval.ptr)=makenode((yyvsp[(1) - (5)].ptr),(yyvsp[(3) - (5)].ptr),NULL,NULL);}
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 253 "cg_calc.y"
    {   struct node * t1 = malloc(sizeof(struct node));
	                                                     t1->NODE_TYPE = IF_THEN;
 						             (yyval.ptr)=makenode(t1,(yyvsp[(3) - (8)].ptr),(yyvsp[(6) - (8)].ptr),NULL); }
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 256 "cg_calc.y"
    {   struct node * t1 = malloc(sizeof(struct node));
	                                                     t1->NODE_TYPE = IF_THEN;
 						             (yyval.ptr)=makenode(t1,(yyvsp[(3) - (10)].ptr),(yyvsp[(6) - (10)].ptr),(yyvsp[(8) - (10)].ptr)); }
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 261 "cg_calc.y"
    {   struct node * t1 = malloc(sizeof(struct node));
	                                                     t1->NODE_TYPE = WHILE_LOOP;
 						             (yyval.ptr)=makenode(t1,(yyvsp[(3) - (8)].ptr),(yyvsp[(6) - (8)].ptr),NULL); }
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 267 "cg_calc.y"
    {	if( (yyvsp[(1) - (3)].ptr)->TYPE == (yyvsp[(2) - (3)].ptr)->TYPE && (yyvsp[(2) - (3)].ptr)->TYPE == (yyvsp[(3) - (3)].ptr)->TYPE )
						   	(yyval.ptr)=makenode((yyvsp[(2) - (3)].ptr),(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr),NULL);
						  else
						  	{ yyerror("Type Mismatch"); } 
                                                         
                                                }
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 273 "cg_calc.y"
    {       if( (yyvsp[(1) - (3)].ptr)->TYPE == (yyvsp[(2) - (3)].ptr)->TYPE && (yyvsp[(2) - (3)].ptr)->TYPE == (yyvsp[(3) - (3)].ptr)->TYPE )
						   	  (yyval.ptr)=makenode((yyvsp[(2) - (3)].ptr),(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr),NULL);
						  else
						  	{ yyerror("Type Mismatch");   } 
                                                }
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 278 "cg_calc.y"
    {	if( (yyvsp[(1) - (3)].ptr)->TYPE == (yyvsp[(2) - (3)].ptr)->TYPE && (yyvsp[(2) - (3)].ptr)->TYPE == (yyvsp[(3) - (3)].ptr)->TYPE )
						   	  (yyval.ptr)=makenode((yyvsp[(2) - (3)].ptr),(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr),NULL);
						  else
						  	{ yyerror("Type Mismatch");   } 
                                                }
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 283 "cg_calc.y"
    {  if( (yyvsp[(1) - (3)].ptr)->TYPE == (yyvsp[(2) - (3)].ptr)->TYPE && (yyvsp[(2) - (3)].ptr)->TYPE == (yyvsp[(3) - (3)].ptr)->TYPE )
						   	  (yyval.ptr)=makenode((yyvsp[(2) - (3)].ptr),(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr),NULL);
						  else
						  	{ yyerror("Type Mismatch");   } 
                                                }
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 288 "cg_calc.y"
    {	if( (yyvsp[(1) - (3)].ptr)->TYPE == (yyvsp[(2) - (3)].ptr)->TYPE && (yyvsp[(2) - (3)].ptr)->TYPE == (yyvsp[(3) - (3)].ptr)->TYPE )
						   	  (yyval.ptr)=makenode((yyvsp[(2) - (3)].ptr),(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr),NULL);
						  else
						  	{ yyerror("Type Mismatch");   } 
                                                 }
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 293 "cg_calc.y"
    {   if( (yyvsp[(1) - (3)].ptr)->TYPE == (yyvsp[(3) - (3)].ptr)->TYPE && (yyvsp[(1) - (3)].ptr)->TYPE == INTEGER )
						   	 (yyval.ptr)=makenode((yyvsp[(2) - (3)].ptr),(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr),NULL); 
						  else
						  	yyerror("Type Mismatch for Boolean Operator");  
                                                      
                                                }
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 299 "cg_calc.y"
    {	(yyval.ptr)=(yyvsp[(2) - (3)].ptr);}
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 301 "cg_calc.y"
    {	if((yyvsp[(1) - (2)].ptr)->TYPE == (yyvsp[(2) - (2)].ptr)->TYPE)
                                                          { (yyval.ptr)=makenode((yyvsp[(1) - (2)].ptr),(yyvsp[(2) - (2)].ptr),NULL,NULL);
                                                          }
                                                         else { yyerror("Type Mismatch"); }
                                                }
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 306 "cg_calc.y"
    {	if( (yyvsp[(1) - (3)].ptr)->TYPE == (yyvsp[(2) - (3)].ptr)->TYPE && (yyvsp[(2) - (3)].ptr)->TYPE == (yyvsp[(3) - (3)].ptr)->TYPE )
						   	  (yyval.ptr)=makenode((yyvsp[(2) - (3)].ptr),(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr),NULL);
						  else
						  	{ yyerror("Type Mismatch");   }
                                                }
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 312 "cg_calc.y"
    {	(yyval.ptr)=(yyvsp[(1) - (1)].ptr);}
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 314 "cg_calc.y"
    { (yyval.ptr)=(yyvsp[(1) - (1)].ptr);
                                                  (yyval.ptr)->TYPE = BOOLEAN; 
                                                }
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 321 "cg_calc.y"
    {                                                                  
                                                        (yyval.ptr) = (yyvsp[(1) - (1)].ptr);
						  struct symbol_table* temp = Lookup((yyval.ptr)->NAME);
						  
						  if(temp==NULL) yyerror("Undefined Variable in Expression");
						  else
						       {
						       	 (yyval.ptr)->ENTRY = temp;
						     	 (yyval.ptr)->TYPE = temp->TYPE;
						       }
						                  
                                                }
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 333 "cg_calc.y"
    {
		 				  (yyval.ptr) = makenode((yyvsp[(1) - (4)].ptr),(yyvsp[(3) - (4)].ptr),NULL,NULL);
		 				  struct symbol_table* temp = Lookup((yyval.ptr)->NAME);
					      	  if(temp==NULL) yyerror("Undefined Variable1");
					          else
					           {
					       		 (yyval.ptr)->ENTRY = temp;
					     	 	 (yyval.ptr)->TYPE = temp->TYPE;
					     	   }
						  
						 }
    break;



/* Line 1806 of yacc.c  */
#line 1988 "y.tab.c"
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
#line 347 "cg_calc.y"


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

