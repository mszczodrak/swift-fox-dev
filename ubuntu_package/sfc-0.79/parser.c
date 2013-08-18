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
#line 1 "parser.y"

/*  
    Swift Fox Compiler
    Copyright (C) 2009-2012 Marcin Szczodrak

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <ctype.h>
#include "sf.h"
#include "traverse.h"

char *relopToLetter(int i);
int editConst(struct symtab *entry);
int negateOperator(int i);
void initialize(void);
void gc(void);
void checkForRemotePath(struct libtab*);

int event_counter	= 1;
int policy_counter	= 0;
int virtual_counter 	= 0;
int event_id_counter	= 0;
FILE *fcode		= NULL;

int module_id_counter = 1;

int active_state;
char *conf_state_name = "control";
int conf_state_id = 1;
int conf_state_redefined = 0;

char *conf_state_app = "cuApp";
char *conf_state_net = "cuNet";
char *conf_state_mac = "cuMac";
char *conf_state_radio = "cc2420";

int conf_counter	= 2;

struct eventnodes *last_evens = NULL;
int file_status;
char *file_name;
char *error_location;

void yyerror(char *errmsg);
int yylex(void);



/* Line 268 of yacc.c  */
#line 137 "parser.c"

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
     CONFIGURATION = 258,
     COMMA = 259,
     EVENT_CONDITION = 260,
     FROM = 261,
     GOTO = 262,
     START = 263,
     USE = 264,
     WHEN = 265,
     APPLICATION = 266,
     NETWORK = 267,
     MAC = 268,
     RADIO = 269,
     ADDRESS = 270,
     SOURCE = 271,
     LF = 272,
     VIRTUAL_NETWORK = 273,
     LT = 274,
     GT = 275,
     LE = 276,
     GE = 277,
     NE = 278,
     EQ = 279,
     OPEN_BRACE = 280,
     CLOSE_BRACE = 281,
     OPEN_PARENTHESIS = 282,
     CLOSE_PARENTHESIS = 283,
     ONCE = 284,
     OPEN_SQUARE_BRACE = 285,
     CLOSE_SQUARE_BRACE = 286,
     LEVEL = 287,
     AT = 288,
     SHARED = 289,
     CONSTANT = 290,
     IDENTIFIER = 291,
     VARIABLE_LINE = 292,
     PATH = 293,
     RELOP = 294,
     AND = 295,
     OR = 296,
     NOT = 297,
     NOTHING = 298,
     ANY = 299,
     MODULES = 300
   };
#endif
/* Tokens.  */
#define CONFIGURATION 258
#define COMMA 259
#define EVENT_CONDITION 260
#define FROM 261
#define GOTO 262
#define START 263
#define USE 264
#define WHEN 265
#define APPLICATION 266
#define NETWORK 267
#define MAC 268
#define RADIO 269
#define ADDRESS 270
#define SOURCE 271
#define LF 272
#define VIRTUAL_NETWORK 273
#define LT 274
#define GT 275
#define LE 276
#define GE 277
#define NE 278
#define EQ 279
#define OPEN_BRACE 280
#define CLOSE_BRACE 281
#define OPEN_PARENTHESIS 282
#define CLOSE_PARENTHESIS 283
#define ONCE 284
#define OPEN_SQUARE_BRACE 285
#define CLOSE_SQUARE_BRACE 286
#define LEVEL 287
#define AT 288
#define SHARED 289
#define CONSTANT 290
#define IDENTIFIER 291
#define VARIABLE_LINE 292
#define PATH 293
#define RELOP 294
#define AND 295
#define OR 296
#define NOT 297
#define NOTHING 298
#define ANY 299
#define MODULES 300




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 66 "parser.y"

	struct symtab		*symp;
	struct modtab		*modp;
	struct libtab		*libp;
	int 			ival;
	char 			*str;
	double			dval;
	struct confnode		*confp;
	struct confnodes	*confsp;
	struct eventnode	*evep;
	struct eventnodes	*evesp;
	struct policy		*pol;
	struct policies		*pols;
	struct initnode		*initp;
	struct program		*prog;
	struct variable		*var;
	struct variables	*vars;
	struct paramtype	*mtl;
	struct paramvalue	*parv;
	struct defvalue		*defv;



/* Line 293 of yacc.c  */
#line 287 "parser.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 299 "parser.c"

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
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   117

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  46
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  35
/* YYNRULES -- Number of rules.  */
#define YYNRULES  59
/* YYNRULES -- Number of states.  */
#define YYNSTATES  121

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   300

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     6,    13,    16,    17,    21,    24,    27,
      28,    44,    47,    48,    53,    56,    59,    60,    64,    68,
      69,    72,    73,    84,    87,    88,    91,    92,   100,   102,
     104,   108,   110,   112,   115,   119,   122,   123,   130,   133,
     134,   137,   140,   141,   142,   153,   155,   157,   159,   161,
     163,   168,   169,   172,   173,   181,   182,   184,   187,   188
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      47,     0,    -1,    70,    48,    -1,    49,    51,    58,    61,
      67,    66,    -1,    49,    50,    -1,    -1,    78,    36,    79,
      -1,    52,    53,    -1,    52,    53,    -1,    -1,     3,    36,
      54,    25,    79,    55,    79,    55,    79,    55,    79,    55,
      79,    26,    79,    -1,    32,    35,    -1,    -1,    36,    27,
      56,    28,    -1,    36,    57,    -1,    35,    57,    -1,    -1,
       4,    36,    57,    -1,     4,    35,    57,    -1,    -1,    58,
      59,    -1,    -1,     5,    36,    25,    36,    39,    35,    36,
      60,    26,    79,    -1,    33,    35,    -1,    -1,    61,    62,
      -1,    -1,     6,    63,     7,    36,    10,    64,    79,    -1,
      36,    -1,    44,    -1,    65,    40,    64,    -1,    65,    -1,
      36,    -1,    42,    36,    -1,     8,    36,    79,    -1,    67,
      68,    -1,    -1,    18,    36,    25,    69,    26,    79,    -1,
      69,    36,    -1,    -1,    79,    71,    -1,    71,    72,    -1,
      -1,    -1,     9,    74,    36,    38,    27,    79,    75,    28,
      73,    79,    -1,    11,    -1,    12,    -1,    13,    -1,    14,
      -1,    16,    -1,    78,    36,    76,    77,    -1,    -1,    39,
      35,    -1,    -1,    79,     4,    79,    78,    36,    76,    77,
      -1,    -1,    36,    -1,    79,    80,    -1,    -1,    17,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   139,   139,   159,   180,   195,   201,   221,   236,   250,
     255,   320,   325,   332,   339,   350,   362,   368,   379,   391,
     398,   414,   419,   454,   459,   465,   479,   484,   503,   508,
     514,   518,   525,   546,   595,   607,   612,   617,   628,   634,
     642,   645,   646,   650,   649,   731,   732,   733,   734,   735,
     739,   754,   760,   767,   775,   788,   794,   818,   819,   822
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CONFIGURATION", "COMMA",
  "EVENT_CONDITION", "FROM", "GOTO", "START", "USE", "WHEN", "APPLICATION",
  "NETWORK", "MAC", "RADIO", "ADDRESS", "SOURCE", "LF", "VIRTUAL_NETWORK",
  "LT", "GT", "LE", "GE", "NE", "EQ", "OPEN_BRACE", "CLOSE_BRACE",
  "OPEN_PARENTHESIS", "CLOSE_PARENTHESIS", "ONCE", "OPEN_SQUARE_BRACE",
  "CLOSE_SQUARE_BRACE", "LEVEL", "AT", "SHARED", "CONSTANT", "IDENTIFIER",
  "VARIABLE_LINE", "PATH", "RELOP", "AND", "OR", "NOT", "NOTHING", "ANY",
  "MODULES", "$accept", "swiftfox", "program", "global_variables",
  "global_variable", "defined_configurations", "configurations",
  "configuration", "conf_level", "module", "parameters", "next_parameter",
  "defined_events", "event_condition", "event_location", "policies",
  "policy", "from_configurations", "when_events", "one_event",
  "initial_configuration", "virtual_networks", "virtual_network",
  "configuration_ids", "library", "definitions", "definition", "$@1",
  "type", "module_types", "default_value", "next_module_type",
  "param_type", "newlines", "newline", 0
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    46,    47,    48,    49,    49,    50,    51,    52,    52,
      53,    54,    54,    55,    56,    56,    56,    57,    57,    57,
      58,    58,    59,    60,    60,    61,    61,    62,    63,    63,
      64,    64,    65,    65,    66,    67,    67,    68,    69,    69,
      70,    71,    71,    73,    72,    74,    74,    74,    74,    74,
      75,    75,    76,    76,    77,    77,    78,    79,    79,    80
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     6,     2,     0,     3,     2,     2,     0,
      15,     2,     0,     4,     2,     2,     0,     3,     3,     0,
       2,     0,    10,     2,     0,     2,     0,     7,     1,     1,
       3,     1,     1,     2,     3,     2,     0,     6,     2,     0,
       2,     2,     0,     0,    10,     1,     1,     1,     1,     1,
       4,     0,     2,     0,     7,     0,     1,     2,     0,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
      58,     0,     5,    42,     1,     2,     9,    59,    40,    57,
      56,     4,    21,     0,     0,     0,    41,    26,     0,     7,
      58,    45,    46,    47,    48,    49,     0,     0,    20,    36,
      12,     6,     0,     0,     0,    25,     0,     0,     0,     0,
       0,    28,    29,     0,     0,     0,     3,    35,    11,    58,
      58,     0,     0,    58,     0,     0,    51,     0,     0,    34,
      39,     0,    58,     0,     0,     0,     0,     0,    16,     0,
      43,    53,    24,    32,     0,    58,    31,    58,    38,    19,
      19,     0,    58,    58,     0,    58,     0,     0,    33,    27,
       0,    37,     0,    15,    14,    13,     0,    44,    52,    50,
       0,    23,    58,    30,    19,    19,    58,    58,    22,    18,
      17,     0,     0,    58,     0,     0,    53,    58,    58,    10,
      54
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     5,     6,    11,    12,    13,    19,    38,    62,
      81,    93,    17,    28,    87,    29,    35,    43,    75,    76,
      46,    36,    47,    67,     2,     8,    16,    83,    26,    63,
      85,    99,    14,   100,     9
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -78
static const yytype_int8 yypact[] =
{
     -78,    13,   -78,    17,   -78,   -78,   -20,   -78,    27,   -78,
     -78,   -78,   -78,    34,     3,    19,   -78,    33,     4,    38,
     -78,   -78,   -78,   -78,   -78,   -78,     6,     7,   -78,    39,
      14,    17,     9,    23,   -22,   -78,    -1,    16,    29,    25,
      20,   -78,   -78,    48,    22,    24,   -78,   -78,   -78,   -78,
     -78,    26,    28,   -78,    36,   -13,   -12,    31,    49,    17,
     -78,    40,   -78,    35,    32,    37,   -27,   -18,   -25,   -13,
     -78,    30,    41,   -78,    42,   -78,    44,   -78,   -78,    66,
      66,    43,   -78,   -78,    45,    51,    46,    50,   -78,    17,
     -27,    17,   -10,   -78,   -78,   -78,   -13,    17,   -78,   -78,
       2,   -78,   -78,   -78,    66,    66,   -78,   -78,    17,   -78,
     -78,   -13,   -12,   -78,    52,    -5,    30,   -78,    51,    17,
     -78
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -78,   -78,   -78,   -78,   -78,   -78,   -78,   -78,   -78,   -67,
     -78,   -77,   -78,   -78,   -78,   -78,   -78,   -78,    -4,   -78,
     -78,   -78,   -78,   -78,   -78,   -78,   -78,   -78,   -78,   -78,
     -44,   -33,   -55,     0,   -78
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -56
static const yytype_int8 yytable[] =
{
       3,    64,    82,    94,     7,     7,   107,    44,    77,    73,
      79,    80,     7,     4,    41,    74,    10,    45,    78,     7,
      31,   117,    42,    61,    10,   104,   105,   109,   110,   106,
      21,    22,    23,    24,     7,    25,    15,    18,    27,    20,
      30,    -8,    32,    33,   113,    34,    37,    39,    40,    55,
      56,    48,    50,    59,    49,    52,    51,   114,    53,    66,
      54,    60,    69,    70,    58,    57,    65,    68,    71,    84,
      92,    95,   118,    72,    86,    89,   102,    91,    88,   -55,
      98,   101,    96,    97,    90,   120,   103,     0,   116,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   108,     0,     0,     0,   111,   112,     0,     0,
       0,     0,     0,   115,     0,     0,     0,   119
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-78))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int8 yycheck[] =
{
       0,    56,    69,    80,    17,    17,     4,     8,    26,    36,
      35,    36,    17,     0,    36,    42,    36,    18,    36,    17,
      20,    26,    44,    36,    36,    35,    36,   104,   105,    96,
      11,    12,    13,    14,    17,    16,     9,     3,     5,    36,
      36,     3,    36,    36,   111,     6,    32,    38,    25,    49,
      50,    35,    27,    53,    25,     7,    36,   112,    36,    10,
      36,    25,    62,    28,    36,    39,    35,    27,    36,    39,
       4,    28,   116,    36,    33,    75,    26,    77,    36,    28,
      35,    35,    82,    83,    40,   118,    90,    -1,    36,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   102,    -1,    -1,    -1,   106,   107,    -1,    -1,
      -1,    -1,    -1,   113,    -1,    -1,    -1,   117
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    47,    70,    79,     0,    48,    49,    17,    71,    80,
      36,    50,    51,    52,    78,     9,    72,    58,     3,    53,
      36,    11,    12,    13,    14,    16,    74,     5,    59,    61,
      36,    79,    36,    36,     6,    62,    67,    32,    54,    38,
      25,    36,    44,    63,     8,    18,    66,    68,    35,    25,
      27,    36,     7,    36,    36,    79,    79,    39,    36,    79,
      25,    36,    55,    75,    78,    35,    10,    69,    27,    79,
      28,    36,    36,    36,    42,    64,    65,    26,    36,    35,
      36,    56,    55,    73,    39,    76,    33,    60,    36,    79,
      40,    79,     4,    57,    57,    28,    79,    79,    35,    77,
      79,    35,    26,    64,    35,    36,    55,     4,    79,    57,
      57,    79,    79,    55,    78,    79,    36,    26,    76,    79,
      77
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
#line 140 "parser.y"
    {
			/* verbose; to be removed */
			/* printTable(); */
			
			/* root node for the constructed AST */
			//struct program *p = $2;

			/* traverse the AST for semantic checking */	
			traverse_program((yyvsp[(2) - (2)].prog),
					TREE_CHECK_SEMANTIC,
					policy_counter);

			/* traverse the AST for code generation */
			traverse_program((yyvsp[(2) - (2)].prog),
					TREE_GENERATE_CODE,
					policy_counter);
		}
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 160 "parser.y"
    {
			/* root node */
			(yyval.prog)		= calloc(1, sizeof(struct program));
			
			/* link the node appropriately */
			(yyvsp[(2) - (6)].confsp)->parent	= NULL;  
			if ((yyvsp[(3) - (6)].evesp) != NULL ) 
				(yyvsp[(3) - (6)].evesp)->parent = NULL;
			if ((yyvsp[(4) - (6)].pols) != NULL ) 
				(yyvsp[(4) - (6)].pols)->parent = NULL;
			
			/* init */
			(yyval.prog)->defcon	= (yyvsp[(2) - (6)].confsp);
			(yyval.prog)->defeve	= (yyvsp[(3) - (6)].evesp);
			(yyval.prog)->defpol	= (yyvsp[(4) - (6)].pols);
			(yyval.prog)->init	= (yyvsp[(6) - (6)].initp);
		}
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 181 "parser.y"
    {
			/* global_variable set */
			(yyval.vars) 		= calloc(1, sizeof(struct variables));

			/* link the child nodes */
			if ((yyvsp[(1) - (2)].vars) != NULL)
				(yyvsp[(1) - (2)].vars)->parent = (yyval.vars);

			(yyvsp[(2) - (2)].var)->parent	= (yyval.vars);

			(yyval.vars)->vars	= (yyvsp[(1) - (2)].vars);
			(yyval.vars)->var		= (yyvsp[(2) - (2)].var);
		}
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 195 "parser.y"
    {
                        (yyval.vars) = NULL;
                }
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 202 "parser.y"
    {
			printf("hello\n");
			//printf("var %s\n", $1);

			(yyval.var)		= calloc(1, sizeof(struct variable));
			(yyval.var)->type 	= (yyvsp[(1) - (3)].ival);
			(yyval.var)->name	= (yyvsp[(2) - (3)].symp);
		
			printf("hello type %d\n", (yyval.var)->type);
			printf("hello type %s\n", (yyval.var)->name->name);
			
			//$2->type	= "global_variable_type";
			//$3->type	= "global_variable_name";

			//$$->var_type	= $2;
			//$$->name	= $3;
		}
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 222 "parser.y"
    {
			/* configurations set */
			(yyval.confsp)		= calloc(1, sizeof(struct confnodes));
			
			/* link the child nodes */
			if ((yyvsp[(1) - (2)].confsp) != NULL)
				(yyvsp[(1) - (2)].confsp)->parent = (yyval.confsp);
			(yyvsp[(2) - (2)].confp)->parent	= (yyval.confsp);
			
			(yyval.confsp)->confs	= (yyvsp[(1) - (2)].confsp);
			(yyval.confsp)->conf	= (yyvsp[(2) - (2)].confp);
		}
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 237 "parser.y"
    {
			/* configurations set */
			(yyval.confsp)		= calloc(1, sizeof(struct confnodes));
			
			/* link the child nodes */
			if ((yyvsp[(1) - (2)].confsp) != NULL) 
				(yyvsp[(1) - (2)].confsp)->parent = (yyval.confsp);
			(yyvsp[(2) - (2)].confp)->parent	= (yyval.confsp);

			(yyval.confsp)->confs	= (yyvsp[(1) - (2)].confsp);
			(yyval.confsp)->conf	= (yyvsp[(2) - (2)].confp);
		}
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 250 "parser.y"
    { 
			(yyval.confsp) = NULL; 
		}
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 256 "parser.y"
    {

			/* configuration node */
			(yyval.confp)		= calloc(1, sizeof(struct confnode));

			/* init */
			(yyvsp[(2) - (15)].symp)->type	= "configuration_id";
			(yyval.confp)->id		= (yyvsp[(2) - (15)].symp);
	
			/* level */
			if ((yyvsp[(3) - (15)].symp) == NULL) {
				(yyval.confp)->level	= UNKNOWN;
			} else {
				(yyval.confp)->level	= editConst((yyvsp[(3) - (15)].symp));
			}

			/* set ids */
			
			if ((yyvsp[(6) - (15)].modp)->id == 0) {
				(yyvsp[(6) - (15)].modp)->id = module_id_counter;
				(yyvsp[(6) - (15)].modp)->conf = (yyval.confp);
				++module_id_counter;
			}

			if ((yyvsp[(8) - (15)].modp)->id == 0) {
				(yyvsp[(8) - (15)].modp)->id = module_id_counter;
				(yyvsp[(8) - (15)].modp)->conf = (yyval.confp);
				++module_id_counter;
			}

			if ((yyvsp[(10) - (15)].modp)->id == 0) {
				(yyvsp[(10) - (15)].modp)->id = module_id_counter;
				(yyvsp[(10) - (15)].modp)->conf = (yyval.confp);
				++module_id_counter;
			}

			if ((yyvsp[(12) - (15)].modp)->id == 0) {
				(yyvsp[(12) - (15)].modp)->id = module_id_counter;
				(yyvsp[(12) - (15)].modp)->conf = (yyval.confp);
				++module_id_counter;
			}

			/* link child nodes */
			(yyval.confp)->app			= (yyvsp[(6) - (15)].modp);
			(yyval.confp)->app_params		= (yyvsp[(6) - (15)].modp)->params;
			(yyval.confp)->net			= (yyvsp[(8) - (15)].modp);
			(yyval.confp)->net_params		= (yyvsp[(8) - (15)].modp)->params;
			(yyval.confp)->mac			= (yyvsp[(10) - (15)].modp);
			(yyval.confp)->mac_params		= (yyvsp[(10) - (15)].modp)->params;
			(yyval.confp)->radio		= (yyvsp[(12) - (15)].modp);
			(yyval.confp)->radio_params	= (yyvsp[(12) - (15)].modp)->params;

			if (!strcmp((yyvsp[(2) - (15)].symp)->name, conf_state_name)) {
				(yyvsp[(2) - (15)].symp)->value	= conf_state_id;
				(yyval.confp)->counter	= conf_state_id;
				conf_state_redefined = 1;
			} else {
				(yyvsp[(2) - (15)].symp)->value	= conf_counter;
				(yyval.confp)->counter	= conf_counter;
				++conf_counter;
			}
		}
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 321 "parser.y"
    {
			(yyval.symp) = (yyvsp[(2) - (2)].symp);
		}
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 325 "parser.y"
    {
                        (yyval.symp) = NULL;
                }
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 333 "parser.y"
    {
			(yyval.modp) = proc_module((yyvsp[(1) - (4)].symp)->name);
			(yyval.modp)->params = (yyvsp[(3) - (4)].parv);
		}
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 340 "parser.y"
    {
                        struct symtab *sp = symlook((yyvsp[(1) - (2)].symp)->name);
                        if (sp == NULL)
                                yyerror("symtab pointer not found");

                        /* paramvalue node */
                        (yyval.parv)              = calloc(1, sizeof(struct paramvalue));
			(yyval.parv)->child	= (yyvsp[(2) - (2)].parv);
                        (yyval.parv)->value       = (yyvsp[(1) - (2)].symp);
                }
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 351 "parser.y"
    {
                        struct symtab *sp = symlook((yyvsp[(1) - (2)].symp)->name);
                        if (sp == NULL)
                                yyerror("symtab pointer not found");

                        /* pramvalue node */
                        (yyval.parv)              = calloc(1, sizeof(struct paramvalue));
                        (yyval.parv)->child       = (yyvsp[(2) - (2)].parv);
                        (yyval.parv)->value       = (yyvsp[(1) - (2)].symp);
                }
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 362 "parser.y"
    {
                        (yyval.parv) = NULL;

		}
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 369 "parser.y"
    {
                        struct symtab *sp = symlook((yyvsp[(2) - (3)].symp)->name);
                        if (sp == NULL)
                                yyerror("symtab pointer not found");

                        /* paramvalue node */
                        (yyval.parv)              = calloc(1, sizeof(struct paramvalue));
                        (yyval.parv)->child       = (yyvsp[(3) - (3)].parv);
                        (yyval.parv)->value       = (yyvsp[(2) - (3)].symp);
                }
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 380 "parser.y"
    {
                        struct symtab *sp = symlook((yyvsp[(2) - (3)].symp)->name);
                        if (sp == NULL)
                                yyerror("symtab pointer not found");

                        /* pramvalue node */
                        (yyval.parv)              = calloc(1, sizeof(struct paramvalue));
                        (yyval.parv)->child       = (yyvsp[(3) - (3)].parv);
                        (yyval.parv)->value       = (yyvsp[(2) - (3)].symp);
		}
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 391 "parser.y"
    {
                        (yyval.parv) = NULL;
                }
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 399 "parser.y"
    {
			/* event-conditions set */
			(yyval.evesp)		= calloc(1, sizeof(struct eventnodes));
			
			/* link child nodes */
			if ((yyvsp[(1) - (2)].evesp) != NULL) {
				(yyvsp[(1) - (2)].evesp)->parent = (yyval.evesp);
				last_evens = (yyval.evesp);
			}
			(yyvsp[(2) - (2)].evep)->parent = (yyval.evesp);
			
			(yyval.evesp)->evens	= (yyvsp[(1) - (2)].evesp);
			(yyval.evesp)->even	= (yyvsp[(2) - (2)].evep);
		}
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 414 "parser.y"
    { 
			(yyval.evesp) = NULL; 
		}
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 420 "parser.y"
    {
			/* event-condition node */
			(yyvsp[(2) - (10)].symp)->value	= event_counter;
			(yyvsp[(2) - (10)].symp)->type	= "event_id";	
			(yyvsp[(2) - (10)].symp)->lib		= (yyvsp[(4) - (10)].symp)->lib;
	
			/* init */
			(yyval.evep) = calloc(1, sizeof(struct eventnode));
			(yyval.evep)->id		= (yyvsp[(2) - (10)].symp);
			(yyval.evep)->counter	= (yyvsp[(2) - (10)].symp)->value;
			
			/* link child nodes */
			(yyval.evep)->src		= (yyvsp[(4) - (10)].symp);
			(yyval.evep)->cst		= (yyvsp[(6) - (10)].symp);
			(yyval.evep)->cst->value	= editConst((yyvsp[(6) - (10)].symp));

			struct evtab *ev= evlook((yyvsp[(2) - (10)].symp)->name);
                        ev->num 	= event_counter;
                        ev->op		= (yyvsp[(5) - (10)].ival);
                        ev->value 	= (yyval.evep)->cst->value;
			ev->scale	= (yyvsp[(7) - (10)].symp);

                        /* event location */
                        if ((yyvsp[(8) - (10)].symp) == NULL) {
                                ev->addr        = UNKNOWN;
                        } else {
                                ev->addr        = editConst((yyvsp[(8) - (10)].symp));
                        }

			event_counter++;
		}
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 455 "parser.y"
    {
                        (yyval.symp) = (yyvsp[(2) - (2)].symp);
                }
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 459 "parser.y"
    {
                        (yyval.symp) = NULL;
                }
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 466 "parser.y"
    {
			/* policies set */
			(yyval.pols) = calloc(1, sizeof(struct policies));

			/* link child nodes */
			if ((yyvsp[(1) - (2)].pols) != NULL) 
				(yyvsp[(1) - (2)].pols)->parent = (yyval.pols);
			(yyvsp[(2) - (2)].pol)->parent = (yyval.pols);

			(yyval.pols)->pols	= (yyvsp[(1) - (2)].pols);
			(yyval.pols)->pol		= (yyvsp[(2) - (2)].pol);
		}
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 479 "parser.y"
    {
			(yyval.pols) = NULL;
		}
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 485 "parser.y"
    {
			/* policy node */
			(yyval.pol) 		= calloc(1, sizeof(struct policy));

			/* link child nodes */
			(yyval.pol)->from	= (yyvsp[(2) - (7)].symp);
			(yyval.pol)->to		= (yyvsp[(4) - (7)].symp);

			(yyval.pol)->mask_r	= (yyvsp[(6) - (7)].ival);
			(yyval.pol)->counter	= policy_counter;

			if (proc_policy((yyval.pol))) {
				fprintf(stderr, "Failed to store policy\n");
				exit(1);
			}
			++policy_counter;
		}
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 504 "parser.y"
    {
			(yyval.symp) = (yyvsp[(1) - (1)].symp);
		}
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 509 "parser.y"
    {
			(yyval.symp) = (yyvsp[(1) - (1)].symp);
		}
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 515 "parser.y"
    {
			(yyval.ival) = (yyvsp[(1) - (3)].ival) + (yyvsp[(3) - (3)].ival);	
		}
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 519 "parser.y"
    {
			(yyval.ival) = (yyvsp[(1) - (1)].ival);
		}
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 526 "parser.y"
    {
			/* iterator */
			struct evtab *ep = NULL;
			/* flag */
			int found = 0;
			
			/* check for undeclared identifiers */
			for (ep = evtab; ep < &evtab[NEVS]; ep++)
				if (ep->name && !strcmp(ep->name, (yyvsp[(1) - (1)].symp)->name)) {
                                        	/* found */
                                        	found = 1;
                                        	break;
                                }
			
			/* undeclared event identifier */
			if (!found)
				yyerror("undeclared event-condition identifier");

			(yyval.ival) = 1 << (((yyvsp[(1) - (1)].symp)->value) - 1);
		}
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 547 "parser.y"
    {
			/* iterator */
			struct evtab *ep = NULL;
			/* flag */
			int found = 0;
			
			/* check for undeclared identifiers */
			for (ep = evtab; ep < &evtab[NEVS]; ep++)
				if (ep->name && !strcmp(ep->name, (yyvsp[(2) - (2)].symp)->name)) {
                                        	/* found */
                                        	found = 1;
                                        	break;
                                }
			
			/* undeclared event identifier */
			if (!found)
				yyerror("undeclared identifier");

			/* create new event in symtab */
			int len = strlen((yyvsp[(2) - (2)].symp)->name) + strlen("not_") + 1;
			char *new = calloc(len, 1);
			(void)snprintf(new, len, "not_%s", (yyvsp[(2) - (2)].symp)->name);
			struct symtab *sp = symlook(new);

			if (!sp->type) {
				sp->value = event_counter;
				sp->type = strdup((yyvsp[(2) - (2)].symp)->type);
				sp->lib = (yyvsp[(2) - (2)].symp)->lib;

				/* 
				 * make a new event entry by negating the 
				 * operator 
				 */
        	                struct evtab *ev_old = evlook((yyvsp[(2) - (2)].symp)->name);
                	        struct evtab *ev_new = evlook(sp->name);

                        	ev_new->num = event_counter;
	                        ev_new->op = negateOperator(ev_old->op);
        	                ev_new->value = ev_old->value;
				
                	        event_counter++;
			}

			(yyval.ival) = 1 << ((sp->value) - 1);
		}
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 596 "parser.y"
    {
			/* start node */
			(yyval.initp) = calloc(1, sizeof(struct initnode));

			/* link child nodes */
			(yyval.initp)->id = (yyvsp[(2) - (3)].symp);
			(yyval.initp)->init = symlook((yyvsp[(2) - (3)].symp)->name)->value;
		}
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 608 "parser.y"
    {
                        (yyval.ival)              = (yyvsp[(1) - (2)].ival);
                }
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 612 "parser.y"
    {
                        (yyval.ival) = 0;
                }
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 618 "parser.y"
    {
                        (yyval.ival)              = 0;
                        (yyvsp[(2) - (6)].symp)->type        = "virtual_id";
                        (yyvsp[(2) - (6)].symp)->value       = virtual_counter;


			++virtual_counter;
                }
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 629 "parser.y"
    {
                        (yyval.symp) = (yyvsp[(1) - (2)].symp);
                }
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 634 "parser.y"
    {
                        (yyval.symp) = NULL;
                }
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 650 "parser.y"
    {
			/* iterator */
			char *p = NULL;
			
			/* lookup */
			struct symtab *sp = NULL;
		
			/* check for library re-declarations */
			if ((sp = symlook((yyvsp[(3) - (8)].symp)->name)) != NULL &&
						sp->type != NULL)
				/* failed */
				yyerror("redeclaration of library");

			/* fix the child properties */
			(yyvsp[(3) - (8)].symp)->type = (yyvsp[(2) - (8)].str);
			(yyvsp[(3) - (8)].symp)->lib = (yyvsp[(4) - (8)].libp);

			/* set params for the library */
			(yyvsp[(4) - (8)].libp)->params = (yyvsp[(7) - (8)].mtl);

                        /* extract the name from the path */
                        if ((p = rindex((yyvsp[(4) - (8)].libp)->path, '/')) == NULL)
                                (yyvsp[(4) - (8)].libp)->name = (yyvsp[(4) - (8)].libp)->path;
                        else
                                (yyvsp[(4) - (8)].libp)->name = ++p;

                        (yyvsp[(4) - (8)].libp)->used = 0;

                        /* save the name as it was defined */
                        (yyvsp[(4) - (8)].libp)->def = (yyvsp[(3) - (8)].symp)->name;


			/* differentiate based on the definition type */
			if (!strcmp((yyvsp[(3) - (8)].symp)->type, "application")) {
				/* application */
			        char *full_name =  malloc(strlen((yyvsp[(4) - (8)].libp)->name)+strlen("App")+1);
			        sprintf(full_name, "%sApp", (yyvsp[(4) - (8)].libp)->name);
				(yyvsp[(4) - (8)].libp)->full_name = full_name;
				(yyvsp[(4) - (8)].libp)->type = TYPE_APPLICATION;
				(yyvsp[(4) - (8)].libp)->used = 0;
				(yyvsp[(4) - (8)].libp)->id = 0;
			}
			if (!strcmp((yyvsp[(3) - (8)].symp)->type, "network")) {
				/* network */
			        char *full_name =  malloc(strlen((yyvsp[(4) - (8)].libp)->name)+strlen("Net")+1);
			        sprintf(full_name, "%sNet", (yyvsp[(4) - (8)].libp)->name);
				(yyvsp[(4) - (8)].libp)->full_name = full_name;
				(yyvsp[(4) - (8)].libp)->type = TYPE_NETWORK;
				(yyvsp[(4) - (8)].libp)->used = 0;
				(yyvsp[(4) - (8)].libp)->id = 0;
			}
                        if (!strcmp((yyvsp[(3) - (8)].symp)->type, "mac")) {
                                /* mac */
			        char *full_name =  malloc(strlen((yyvsp[(4) - (8)].libp)->name)+strlen("Mac")+1);
			        sprintf(full_name, "%sMac", (yyvsp[(4) - (8)].libp)->name);
				(yyvsp[(4) - (8)].libp)->full_name = full_name;
                                (yyvsp[(4) - (8)].libp)->type = TYPE_MAC;
				(yyvsp[(4) - (8)].libp)->used = 0;
                                (yyvsp[(4) - (8)].libp)->id = 0;
                        }
                        if (!strcmp((yyvsp[(3) - (8)].symp)->type, "radio")) {
                                /* radio */
			        char *full_name =  malloc(strlen((yyvsp[(4) - (8)].libp)->name)+strlen("Radio")+1);
			        sprintf(full_name, "%sRadio", (yyvsp[(4) - (8)].libp)->name);
				(yyvsp[(4) - (8)].libp)->full_name = full_name;
                                (yyvsp[(4) - (8)].libp)->type = TYPE_RADIO;
				(yyvsp[(4) - (8)].libp)->used = 0;
                                (yyvsp[(4) - (8)].libp)->id = 0;
                        }
			if (!strcmp((yyvsp[(3) - (8)].symp)->type, "source")) {
				/* source */
				(yyvsp[(4) - (8)].libp)->type = TYPE_EVENT;
				event_id_counter++;
				(yyvsp[(4) - (8)].libp)->used = 0;
				(yyvsp[(4) - (8)].libp)->id = event_id_counter;
			}

		}
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 731 "parser.y"
    { (yyval.str) = "application"; }
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 732 "parser.y"
    { (yyval.str) = "network"; }
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 733 "parser.y"
    { (yyval.str) = "mac"; }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 734 "parser.y"
    { (yyval.str) = "radio"; }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 735 "parser.y"
    { (yyval.str) = "source"; }
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 740 "parser.y"
    {

			struct symtab *sp = symlook((yyvsp[(2) - (4)].symp)->name);
			if (sp == NULL)
                                yyerror("symtab pointer not found");


                        (yyval.mtl)              = calloc(1, sizeof(struct paramtype));
			(yyval.mtl)->type	= (yyvsp[(1) - (4)].ival);
                        (yyval.mtl)->name   	= (yyvsp[(2) - (4)].symp)->name;
			(yyval.mtl)->def_val	= (yyvsp[(3) - (4)].defv);
                        (yyval.mtl)->child       = (yyvsp[(4) - (4)].mtl);
		}
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 754 "parser.y"
    {
			(yyval.mtl) = NULL;
		}
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 761 "parser.y"
    {
			(yyval.defv)		= calloc(1, sizeof(struct defvalue));
			(yyval.defv)->def_value	= (yyvsp[(2) - (2)].symp);
			(yyval.defv)->def_valid	= 1;
		}
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 767 "parser.y"
    {
			(yyval.defv)		= calloc(1, sizeof(struct defvalue));
			(yyval.defv)->def_value	= NULL;
			(yyval.defv)->def_valid	= 0;
		}
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 776 "parser.y"
    {
			struct symtab *sp = symlook((yyvsp[(5) - (7)].symp)->name);
			if (sp == NULL)
                                yyerror("symtab pointer not found");

                        (yyval.mtl)              = calloc(1, sizeof(struct paramtype));
                        (yyval.mtl)->type   	= (yyvsp[(4) - (7)].ival);
                        (yyval.mtl)->name   	= (yyvsp[(5) - (7)].symp)->name;
			(yyval.mtl)->def_val	= (yyvsp[(6) - (7)].defv);
			(yyval.mtl)->child	= (yyvsp[(7) - (7)].mtl);
		}
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 788 "parser.y"
    {
			(yyval.mtl) = NULL;
		}
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 795 "parser.y"
    {
			(yyval.ival) = 0;

			if (!strcmp((yyvsp[(1) - (1)].symp)->name, "uint8_t"))
				(yyval.ival) = TYPE_UINT8_T;

			if (!strcmp((yyvsp[(1) - (1)].symp)->name, "uint16_t"))
				(yyval.ival) = TYPE_UINT16_T;

			if (!strcmp((yyvsp[(1) - (1)].symp)->name, "uint32_t"))
				(yyval.ival) = TYPE_UINT32_T;

			if (!strcmp((yyvsp[(1) - (1)].symp)->name, "float"))
				(yyval.ival) = TYPE_FLOAT;

			if (!strcmp((yyvsp[(1) - (1)].symp)->name, "double"))
				(yyval.ival) = TYPE_DOUBLE;

		}
    break;



/* Line 1806 of yacc.c  */
#line 2485 "parser.c"
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
#line 825 "parser.y"


char program_file[PATH_SZ];
char library_file[PATH_SZ];
char fennec_library_file[PATH_SZ];

extern FILE *yyin;
extern char *yytext;
extern int yyleng;

/* main entry point */
int
start_parser(int argc, char *argv[]) {

	/* check the file extention */
	if (rindex(argv[1], '.') != NULL && !strcmp(rindex(argv[1], '.'), ".sfp")) {
		argv[1][strlen(argv[1])-4] = '\0';
	}
		
	/* init */
	(void)memset(program_file, 0, PATH_SZ);
	(void)memset(library_file, 0, PATH_SZ);
	(void)memset(fennec_library_file, 0, PATH_SZ);

	(void)snprintf(program_file, PATH_SZ, "%s.sfp", argv[1]);
	(void)snprintf(library_file, PATH_SZ, "%s.sfl", argv[1]);
	(void)snprintf(fennec_library_file, PATH_SZ, "%s/%s", 
			getenv("FENNEC_FOX_LIB"), STD_FENNEC_FOX_LIB);


	if ((error_location = malloc(strlen("fennec_library") + 1)) == NULL) {
		/* failed */
		(void)fprintf(stderr, 
			"Cannot allocate memory for error_location\n");
		exit(1);
	}

	/* cleanup */	
	(void)atexit(gc);

	initialize();
	
	/* process libraries */
	lineno = 1;
	tokenpos = 0;
	
	/* try fennec fox standart libray located at ($FENNEC_FOX_LIB)/STD_FENNEC_FOX_LIB */
	yyin = fopen(fennec_library_file, "r");
	strcpy(error_location, "fennec library");
	file_status = 1;
	file_name = fennec_library_file;

	if (!yyin) {
		/* failed */
		(void)fprintf(stderr, 
			"%s.sfl: no such file or directory and no standard library\n",
			argv[1]);
		exit(1);
	}

	/* main loop */
	do {
		yyparse();

	} while(!feof(yyin));

	return 0;
}

/* error reporting */
void
yyerror(char *errmsg) {
	
	/* error in program */
	(void)fprintf(stderr, "\nsfc in %s %s\n", error_location, file_name);

	/* line */
        (void)fprintf(stderr, "%s at line %d, position %d:\n", errmsg, lineno, 
							tokenpos - yyleng + 1);
	(void)fprintf(stderr, "%s\n", linebuf);
	(void)fprintf(stderr, "%*s\n", tokenpos - yyleng + 1, "^");

	/* terminate */
	exit(1);
}

/* restart the parser with the program file */
int
yywrap(void) {
	/* finish; done with library and program */
	switch(file_status) {
		case 1:
	        	/* open the specific library file */
		        yyin 		= fopen(library_file, "r");
			strcpy(error_location, "library");
			file_status 	= 2;
			file_name 	= library_file;

			if (yyin) {
				/* re-init */
				lineno		= 1;
				tokenpos	= 0;
				break;
			}

		case 2:
			/* re-init */
			lineno		= 1;
			tokenpos	= 0;

			/* open the program file */
		       	yyin		= fopen(program_file, "r");
			strcpy(error_location, "program");
			file_status 	= 3;
			file_name 	= program_file;
        		if (!yyin) {
				/* failed */
				(void)fprintf(stderr, 
					"%s: no such file or directory\n",
					program_file);
		                exit(1);
	        	}	
			break;

		case 3:
			return 1;
	}

	/* default */
	return 0;
}

/* symbol lookup */
struct symtab *
symlook(char *s) {
	/* iterator */
 	struct symtab *sp = NULL;

	/* loop */
	for(sp = symtab; sp < &symtab[NSYMS]; sp++) {
        	/* is it already here? */
	        if (sp->name && !strcmp(sp->name, s))
	      		return sp;

		/* is it free */
		if(!sp->name) {
		        /* check if this symbol has related library */
		        struct libtab *lp = NULL;
		        /* loop */
		        for(lp = libtab; lp < &libtab[NLIBS]; lp++) {
                		/* is it this the lib ? */
		                if (lp->def != NULL && !strcmp(lp->def, s)) {
					sp->lib = lp;
					sp->name = lp->def;
					return sp;
				}
			}
			sp->lib = NULL;
			sp->name = strdup(s);
			return sp;
		}
		/* otherwise continue to next */
	}
	yyerror("symtab is full");
	return sp;
}


/* symbol */
struct symtab *
find_sym(char *s) {
        /* iterator */
        struct symtab *sp = NULL;

        /* loop */
        for(sp = symtab; sp < &symtab[NSYMS]; sp++) {
                /* is it already here? */
                if (sp->name && !strcmp(sp->name, s))
                        return sp;

        }
	return NULL;
}

/* process_module */
struct modtab *
proc_module(char *s) {
	/* symtab ptr */
	struct symtab *sp = find_sym(s);

        /* iterator */
        struct modtab *mp = NULL;

	/* check if this is a know module */
	if (sp == NULL)
		yyerror("no such module");

        /* loop */
        for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
                /* is it free */
                if(!mp->lib) {
			mp->id = 0;
			mp->type = sp->type;
			mp->lib = sp->lib;
			mp->params = NULL;
			mp->conf = NULL;
			mp->conf_num = 0;
                        return mp;
                }
		if (strcmp(mp->lib->def, sp->name) == 0) {
			return mp;
		}
        }
        yyerror("modtab is full");
	return mp;
}

/* store policy */
int
proc_policy(struct policy *p) {

	poltab[policy_counter].policy_num = policy_counter;
	poltab[policy_counter].src_conf = &p->from->value;
	poltab[policy_counter].event_mask = &p->mask_r;
	poltab[policy_counter].dst_conf = &p->to->value;

	return 0;	
}


/* library lookup */
struct libtab*
liblook(char *l) {
	
	/* iterator */
	struct libtab *lp = NULL;

	/* loop */
        for(lp = libtab; lp < &libtab[NLIBS]; lp++) {
                /* is it already here? */
                if (lp->path && !strcmp(lp->path, l)) 
			yyerror("library already exists");

                /* is it free */
                if(!lp->path) {
                        lp->path = strdup(l);
			checkForRemotePath(lp);
			lp->used = 0;
                        return lp;
                }

                /* otherwise continue to next */
        }
        yyerror("libtab is full");
	return lp;
}

/* event-condition lookup */
struct evtab*
evlook(char *name) {

	/* iterator */
	struct evtab *ev = NULL;

	/* loop */
	for(ev = evtab; ev < &evtab[NEVS]; ev++) {
		/* found */
                if (ev->name && !strcmp(ev->name, name)) 
			return ev;
		
		/* insert */
		if (!ev->name) {
			ev->name = strdup(name);
			return ev;
		}
	}

	/* failed */
	yyerror("evtab is full");
	return ev;
}

/* initialize the keywords set */
void
initialize(void) {

	/* keywords set */
	char *keywords[] = {"configuration", "start", "use", "application",
			"network", "source", "event-condition", "from", "goto",
			"none", "conf", "event", "on", "off", 			
			"mac", "radio", "virtual-network",   // new keywords
			"when", "nothing", "once", "event"};
	
	/* size of the keywords set */
	int k_num 		= sizeof(keywords)/sizeof(char*);
	
	/* iterate */
	int i			= 0;
	struct symtab *sp	= NULL;
	
	/* init */
	for(i = 0, sp = symtab; i < k_num; i++, sp++) {
		sp->name = keywords[i];
		sp->value = 0;
		sp->type = "keyword";
	}
	sp->name = "any";
	sp->value = 253;
	sp->type = "keyword";
}

/* get the negation of an operator */
int
negateOperator(int i) {
	switch(i) {
		case LT:
			return GE;
		case GT:
			return LE;
		case LE:
			return GT;
		case GE:
			return LT;
		case NE:
			return EQ;
		case EQ:
			return NE;
		default:
			yyerror("unknown RELOP operator");
			return -1;
	}
}

/* parse constants */
int
editConst(struct symtab *entry ) {
	
	/* get the constant */
	char *sp = entry->name;

	/* extract the integer part */
	int v = atoi(sp);

	/* default */
	entry->type = strdup("number");
	return v;
}

void printTable() {
	struct symtab *sp;
	printf("\n");
        for(sp = symtab; sp < &symtab[NSYMS]; sp++) {
                /* is it already here? */
                if (sp->name ) {
	                        printf("%s   %s   %d\n", sp->name, sp->type, sp->value);
                } else {
			printf("\n\n");
			break;
		}
        }

        struct evtab *ev;
        for(ev = evtab; ev < &evtab[NEVS]; ev++) {
                if (ev->name) {
			printf("%s     %d    %d     %d\n", ev->name, ev->num, ev->op, ev->value);
                } else {
			printf("\n\n");
			return;
		}
        }
} 

/* garbage collection */
void
gc(void) {
	
	/* cleanup */
	(void)fclose(yyin);
}

/* check if the path is remote */
void
checkForRemotePath(struct libtab *lp) {

        /* check if it is http:// */
        if (!strncmp(lp->path, "http://",7)) {

                /* make temp dir for all downloaded libraries */
                mkdir(TEMP_DIR, S_IRWXU);

                char *p = NULL;
                /* extract the name from the path */
                if ((p = rindex(lp->path, '/')) != NULL) {
                        p++;
                }

                /* make dir for this library */
                char *new = malloc(strlen(p)+strlen(TEMP_DIR)+2);
                sprintf(new, "%s/%s", TEMP_DIR, p);
                mkdir(new, S_IRWXU);

                /* prepare system command */
                char *command = malloc(strlen(lp->path)+strlen(new)+40);
                sprintf(command, "wget -q -nd -r --no-parent -A.nc -P %s %s", new, lp->path);

                if( system(command) ) {
                        fprintf(stderr, "Swift Fox Error: Could not download files from %s\n", lp->path);
                        exit(1);
                }
                free(lp->path);
                lp->path = strdup(new);
                free(command);
                free(new);
        }
}


