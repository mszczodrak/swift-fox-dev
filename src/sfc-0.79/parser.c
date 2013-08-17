#ifndef lint
static const char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20120115

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)

#define YYPREFIX "yy"

#define YYPURE 0

#line 2 "parser.y"
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

#line 66 "parser.y"
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union {
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
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 111 "parser.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define CONFIGURATION 257
#define COMMA 258
#define EVENT_CONDITION 259
#define FROM 260
#define GOTO 261
#define START 262
#define USE 263
#define WHEN 264
#define APPLICATION 265
#define NETWORK 266
#define MAC 267
#define RADIO 268
#define ADDRESS 269
#define SOURCE 270
#define LF 271
#define VIRTUAL_NETWORK 272
#define LT 273
#define GT 274
#define LE 275
#define GE 276
#define NE 277
#define EQ 278
#define OPEN_BRACE 279
#define CLOSE_BRACE 280
#define OPEN_PARENTHESIS 281
#define CLOSE_PARENTHESIS 282
#define ONCE 283
#define OPEN_SQUARE_BRACE 284
#define CLOSE_SQUARE_BRACE 285
#define LEVEL 286
#define AT 287
#define SHARED 288
#define CONSTANT 289
#define IDENTIFIER 290
#define VARIABLE_LINE 291
#define PATH 292
#define RELOP 293
#define AND 294
#define OR 295
#define NOT 296
#define NOTHING 297
#define ANY 298
#define MODULES 299
#define YYERRCODE 256
static const short yylhs[] = {                           -1,
    0,   13,    8,    8,    9,    5,    4,    4,    3,   20,
   20,    1,   24,   24,   24,   25,   25,   25,    7,    7,
    6,   21,   21,   11,   11,   10,    2,    2,   15,   15,
   16,   16,   12,   18,   18,   17,   19,   19,   28,   30,
   30,   32,   31,   14,   14,   14,   14,   14,   22,   22,
   27,   27,   23,   23,   26,   29,   29,   33,
};
static const short yylen[] = {                            2,
    2,    6,    2,    0,    3,    2,    2,    0,   15,    2,
    0,    4,    2,    2,    0,    3,    3,    0,    2,    0,
   10,    2,    0,    2,    0,    7,    1,    1,    3,    1,
    1,    2,    3,    2,    0,    6,    2,    0,    2,    2,
    0,    0,   10,    1,    1,    1,    1,    1,    4,    0,
    2,    0,    7,    0,    1,    2,    0,    1,
};
static const short yydefred[] = {                        57,
    0,    4,    0,    0,    1,   58,    0,   56,   55,    0,
   20,    3,    0,    0,   40,    0,    0,    0,   57,   44,
   45,   46,   47,   48,    0,    0,    0,   19,    0,    0,
    0,    0,    0,    0,    0,   24,    0,    0,   10,   57,
    0,   27,   28,    0,    0,    0,    2,   34,   57,    0,
    0,    0,   57,    0,    0,    0,   57,    0,    0,    0,
   38,    0,    0,    0,    0,    0,    0,    0,   42,    0,
    0,    0,    0,   57,    0,   31,    0,   57,    0,   57,
   37,   57,    0,    0,    0,   14,   13,   12,    0,    0,
    0,   32,    0,    0,    0,    0,   51,   49,    0,    0,
    0,   57,   22,   57,   29,   57,   17,   16,    0,    0,
    0,   57,    0,    0,    0,   57,    0,    0,   53,
};
static const short yydgoto[] = {                          1,
   57,   44,   17,   10,   11,   28,   18,    4,   12,   36,
   29,   47,    5,   25,   78,   79,   48,   37,   68,   33,
   91,   62,   98,   73,   86,   13,   84,    2,   99,    7,
   15,   82,    8,
};
static const short yysindex[] = {                         0,
    0,    0, -264, -272,    0,    0, -241,    0,    0, -224,
    0,    0, -221, -178,    0, -219,    0, -212,    0,    0,
    0,    0,    0,    0, -193, -237, -191,    0, -165, -264,
 -190, -188, -183, -181, -246,    0, -249, -177,    0,    0,
 -184,    0,    0, -161, -182, -180,    0,    0,    0, -259,
 -179, -175,    0, -170, -256, -169,    0, -173, -153, -264,
    0, -164, -171, -205, -259, -168, -245, -217,    0, -172,
 -138, -138, -159,    0, -163,    0, -162,    0, -167,    0,
    0,    0, -160,    0, -196,    0,    0,    0, -259, -158,
 -155,    0, -264, -245, -264, -264,    0,    0, -210, -138,
 -138,    0,    0,    0,    0,    0,    0,    0, -259, -264,
 -256,    0, -157, -189, -172,    0,    0, -264,    0,
};
static const short yyrindex[] = {                         0,
    0,    0, -254, -131,    0,    0, -252,    0,    0,    0,
    0,    0,    0,    0,    0,    0, -232, -194,    0,    0,
    0,    0,    0,    0,    0, -149,    0,    0, -195, -251,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0, -150,    0,    0,    0,    0,  134,
    0,    0,    0, -147,    0,    0,    0,    0,    0, -250,
 -146, -146,    0,    0, -143,    0,    0,    0, -207,    0,
    0,    0,    0, -247,    0,    0,    0,    0,    0,    0,
    0,    0, -186,    0, -192, -253,    0,    0,    0, -146,
 -146,    0,    0,    0,    0,    0,    0,    0,    0, -243,
    0,    0,    0,    0, -250,    0, -247, -200,    0,
};
static const short yygindex[] = {                         0,
  -63,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   44,    0,    0,    0,    0,    0,
    0,    0,   22,    0,  -58,  -55,   25,    0,    1,    0,
    0,    0,    0,
};
#define YYTABLESIZE 140
static const short yytable[] = {                         63,
    3,   74,   41,   43,   39,    5,    6,   52,   41,   43,
   57,    6,   45,   87,    6,   21,   21,    9,   21,   30,
   52,   14,   46,   57,    7,  102,    6,    6,   21,    6,
   56,   52,   16,    9,   54,   41,   43,   39,    5,    6,
   50,  107,  108,   42,   76,  112,   27,  106,   32,   55,
   77,   43,   30,   60,   30,  113,    9,   65,    9,    9,
    6,    9,   80,   30,   30,   25,   35,   25,   19,   36,
   26,    9,   81,   26,   89,   26,   35,   25,   93,   36,
   95,    6,   96,   71,   72,   26,   20,   21,   22,   23,
  116,   24,  100,  101,   35,   40,   31,   41,   34,   52,
   39,   38,  109,   49,  110,   51,  111,   53,   61,   54,
   67,   64,  114,   58,   59,   66,  118,   69,   70,   85,
   83,   75,   88,   90,  104,    8,   94,   92,   97,   11,
  103,   50,  115,   33,   15,   18,   23,  105,  119,  117,
};
static const short yycheck[] = {                         55,
    0,   65,  257,  257,  257,  257,  271,  258,  263,  263,
  258,  271,  262,   72,  271,  259,  260,  290,  262,   19,
  271,  263,  272,  271,  257,   89,  259,  260,  272,  262,
  290,  282,  257,  290,  282,  290,  290,  290,  290,  272,
   40,  100,  101,  290,  290,  109,  259,  258,  286,   49,
  296,  298,  260,   53,  262,  111,  257,   57,  259,  260,
  271,  262,  280,  271,  272,  260,  262,  262,  290,  262,
  290,  272,  290,  260,   74,  262,  272,  272,   78,  272,
   80,  271,   82,  289,  290,  272,  265,  266,  267,  268,
  280,  270,  289,  290,  260,  279,  290,  279,  290,  261,
  289,  292,  102,  281,  104,  290,  106,  290,  279,  290,
  264,  281,  112,  293,  290,  289,  116,  282,  290,  258,
  293,  290,  282,  287,  280,  257,  294,  290,  289,  279,
  289,  282,  290,    0,  282,  282,  280,   94,  117,  115,
};
#define YYFINAL 1
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 299
#if YYDEBUG
static const char *yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"CONFIGURATION","COMMA",
"EVENT_CONDITION","FROM","GOTO","START","USE","WHEN","APPLICATION","NETWORK",
"MAC","RADIO","ADDRESS","SOURCE","LF","VIRTUAL_NETWORK","LT","GT","LE","GE",
"NE","EQ","OPEN_BRACE","CLOSE_BRACE","OPEN_PARENTHESIS","CLOSE_PARENTHESIS",
"ONCE","OPEN_SQUARE_BRACE","CLOSE_SQUARE_BRACE","LEVEL","AT","SHARED",
"CONSTANT","IDENTIFIER","VARIABLE_LINE","PATH","RELOP","AND","OR","NOT",
"NOTHING","ANY","MODULES",
};
static const char *yyrule[] = {
"$accept : swiftfox",
"swiftfox : library program",
"program : global_variables defined_configurations defined_events policies virtual_networks initial_configuration",
"global_variables : global_variables global_variable",
"global_variables :",
"global_variable : param_type IDENTIFIER newlines",
"defined_configurations : configurations configuration",
"configurations : configurations configuration",
"configurations :",
"configuration : CONFIGURATION IDENTIFIER conf_level OPEN_BRACE newlines module newlines module newlines module newlines module newlines CLOSE_BRACE newlines",
"conf_level : LEVEL CONSTANT",
"conf_level :",
"module : IDENTIFIER OPEN_PARENTHESIS parameters CLOSE_PARENTHESIS",
"parameters : IDENTIFIER next_parameter",
"parameters : CONSTANT next_parameter",
"parameters :",
"next_parameter : COMMA IDENTIFIER next_parameter",
"next_parameter : COMMA CONSTANT next_parameter",
"next_parameter :",
"defined_events : defined_events event_condition",
"defined_events :",
"event_condition : EVENT_CONDITION IDENTIFIER OPEN_BRACE IDENTIFIER RELOP CONSTANT IDENTIFIER event_location CLOSE_BRACE newlines",
"event_location : AT CONSTANT",
"event_location :",
"policies : policies policy",
"policies :",
"policy : FROM from_configurations GOTO IDENTIFIER WHEN when_events newlines",
"from_configurations : IDENTIFIER",
"from_configurations : ANY",
"when_events : one_event AND when_events",
"when_events : one_event",
"one_event : IDENTIFIER",
"one_event : NOT IDENTIFIER",
"initial_configuration : START IDENTIFIER newlines",
"virtual_networks : virtual_networks virtual_network",
"virtual_networks :",
"virtual_network : VIRTUAL_NETWORK IDENTIFIER OPEN_BRACE configuration_ids CLOSE_BRACE newlines",
"configuration_ids : configuration_ids IDENTIFIER",
"configuration_ids :",
"library : newlines definitions",
"definitions : definitions definition",
"definitions :",
"$$1 :",
"definition : USE type IDENTIFIER PATH OPEN_PARENTHESIS newlines module_types CLOSE_PARENTHESIS $$1 newlines",
"type : APPLICATION",
"type : NETWORK",
"type : MAC",
"type : RADIO",
"type : SOURCE",
"module_types : param_type IDENTIFIER default_value next_module_type",
"module_types :",
"default_value : RELOP CONSTANT",
"default_value :",
"next_module_type : newlines COMMA newlines param_type IDENTIFIER default_value next_module_type",
"next_module_type :",
"param_type : IDENTIFIER",
"newlines : newlines newline",
"newlines :",
"newline : LF",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 500
#define YYMAXDEPTH  500
#endif
#endif

#define YYINITSTACKSIZE 500

typedef struct {
    unsigned stacksize;
    short    *s_base;
    short    *s_mark;
    short    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;
#line 826 "parser.y"

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

#line 826 "parser.c"

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = data->s_mark - data->s_base;
    newss = (short *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return -1;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return -1;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack)) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    yyerror("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 1:
#line 140 "parser.y"
	{
			/* verbose; to be removed */
			/* printTable(); */
			
			/* root node for the constructed AST */
			/*struct program *p = $2;*/

			/* traverse the AST for semantic checking */	
			traverse_program(yystack.l_mark[0].prog,
					TREE_CHECK_SEMANTIC,
					policy_counter);

			/* traverse the AST for code generation */
			traverse_program(yystack.l_mark[0].prog,
					TREE_GENERATE_CODE,
					policy_counter);
		}
break;
case 2:
#line 160 "parser.y"
	{
			/* root node */
			yyval.prog		= calloc(1, sizeof(struct program));
			
			/* link the node appropriately */
			yystack.l_mark[-4].confsp->parent	= NULL;  
			if (yystack.l_mark[-3].evesp != NULL ) 
				yystack.l_mark[-3].evesp->parent = NULL;
			if (yystack.l_mark[-2].pols != NULL ) 
				yystack.l_mark[-2].pols->parent = NULL;
			
			/* init */
			yyval.prog->defcon	= yystack.l_mark[-4].confsp;
			yyval.prog->defeve	= yystack.l_mark[-3].evesp;
			yyval.prog->defpol	= yystack.l_mark[-2].pols;
			yyval.prog->init	= yystack.l_mark[0].initp;
		}
break;
case 3:
#line 181 "parser.y"
	{
			/* global_variable set */
			yyval.vars 		= calloc(1, sizeof(struct variables));

			/* link the child nodes */
			if (yystack.l_mark[-1].vars != NULL)
				yystack.l_mark[-1].vars->parent = yyval.vars;

			yystack.l_mark[0].var->parent	= yyval.vars;

			yyval.vars->vars	= yystack.l_mark[-1].vars;
			yyval.vars->var		= yystack.l_mark[0].var;
		}
break;
case 4:
#line 195 "parser.y"
	{
                        yyval.vars = NULL;
                }
break;
case 5:
#line 202 "parser.y"
	{
			printf("hello\n");
			/*printf("var %s\n", $1);*/

			yyval.var		= calloc(1, sizeof(struct variable));
			yyval.var->type 	= yystack.l_mark[-2].ival;
			yyval.var->name	= yystack.l_mark[-1].symp;
		
			printf("hello type %d\n", yyval.var->type);
			printf("hello type %s\n", yyval.var->name->name);
			
			/*$2->type	= "global_variable_type";*/
			/*$3->type	= "global_variable_name";*/

			/*$$->var_type	= $2;*/
			/*$$->name	= $3;*/
		}
break;
case 6:
#line 222 "parser.y"
	{
			/* configurations set */
			yyval.confsp		= calloc(1, sizeof(struct confnodes));
			
			/* link the child nodes */
			if (yystack.l_mark[-1].confsp != NULL)
				yystack.l_mark[-1].confsp->parent = yyval.confsp;
			yystack.l_mark[0].confp->parent	= yyval.confsp;
			
			yyval.confsp->confs	= yystack.l_mark[-1].confsp;
			yyval.confsp->conf	= yystack.l_mark[0].confp;
		}
break;
case 7:
#line 237 "parser.y"
	{
			/* configurations set */
			yyval.confsp		= calloc(1, sizeof(struct confnodes));
			
			/* link the child nodes */
			if (yystack.l_mark[-1].confsp != NULL) 
				yystack.l_mark[-1].confsp->parent = yyval.confsp;
			yystack.l_mark[0].confp->parent	= yyval.confsp;

			yyval.confsp->confs	= yystack.l_mark[-1].confsp;
			yyval.confsp->conf	= yystack.l_mark[0].confp;
		}
break;
case 8:
#line 250 "parser.y"
	{ 
			yyval.confsp = NULL; 
		}
break;
case 9:
#line 256 "parser.y"
	{

			/* configuration node */
			yyval.confp		= calloc(1, sizeof(struct confnode));

			/* init */
			yystack.l_mark[-13].symp->type	= "configuration_id";
			yyval.confp->id		= yystack.l_mark[-13].symp;
	
			/* level */
			if (yystack.l_mark[-12].symp == NULL) {
				yyval.confp->level	= UNKNOWN;
			} else {
				yyval.confp->level	= editConst(yystack.l_mark[-12].symp);
			}

			/* set ids */
			
			if (yystack.l_mark[-9].modp->id == 0) {
				yystack.l_mark[-9].modp->id = module_id_counter;
				yystack.l_mark[-9].modp->conf = yyval.confp;
				++module_id_counter;
			}

			if (yystack.l_mark[-7].modp->id == 0) {
				yystack.l_mark[-7].modp->id = module_id_counter;
				yystack.l_mark[-7].modp->conf = yyval.confp;
				++module_id_counter;
			}

			if (yystack.l_mark[-5].modp->id == 0) {
				yystack.l_mark[-5].modp->id = module_id_counter;
				yystack.l_mark[-5].modp->conf = yyval.confp;
				++module_id_counter;
			}

			if (yystack.l_mark[-3].modp->id == 0) {
				yystack.l_mark[-3].modp->id = module_id_counter;
				yystack.l_mark[-3].modp->conf = yyval.confp;
				++module_id_counter;
			}

			/* link child nodes */
			yyval.confp->app			= yystack.l_mark[-9].modp;
			yyval.confp->app_params		= yystack.l_mark[-9].modp->params;
			yyval.confp->net			= yystack.l_mark[-7].modp;
			yyval.confp->net_params		= yystack.l_mark[-7].modp->params;
			yyval.confp->mac			= yystack.l_mark[-5].modp;
			yyval.confp->mac_params		= yystack.l_mark[-5].modp->params;
			yyval.confp->radio		= yystack.l_mark[-3].modp;
			yyval.confp->radio_params	= yystack.l_mark[-3].modp->params;

			if (!strcmp(yystack.l_mark[-13].symp->name, conf_state_name)) {
				yystack.l_mark[-13].symp->value	= conf_state_id;
				yyval.confp->counter	= conf_state_id;
				conf_state_redefined = 1;
			} else {
				yystack.l_mark[-13].symp->value	= conf_counter;
				yyval.confp->counter	= conf_counter;
				++conf_counter;
			}
		}
break;
case 10:
#line 321 "parser.y"
	{
			yyval.symp = yystack.l_mark[0].symp;
		}
break;
case 11:
#line 325 "parser.y"
	{
                        yyval.symp = NULL;
                }
break;
case 12:
#line 333 "parser.y"
	{
			yyval.modp = proc_module(yystack.l_mark[-3].symp->name);
			yyval.modp->params = yystack.l_mark[-1].parv;
		}
break;
case 13:
#line 340 "parser.y"
	{
                        struct symtab *sp = symlook(yystack.l_mark[-1].symp->name);
                        if (sp == NULL)
                                yyerror("symtab pointer not found");

                        /* paramvalue node */
                        yyval.parv              = calloc(1, sizeof(struct paramvalue));
			yyval.parv->child	= yystack.l_mark[0].parv;
                        yyval.parv->value       = yystack.l_mark[-1].symp;
                }
break;
case 14:
#line 351 "parser.y"
	{
                        struct symtab *sp = symlook(yystack.l_mark[-1].symp->name);
                        if (sp == NULL)
                                yyerror("symtab pointer not found");

                        /* pramvalue node */
                        yyval.parv              = calloc(1, sizeof(struct paramvalue));
                        yyval.parv->child       = yystack.l_mark[0].parv;
                        yyval.parv->value       = yystack.l_mark[-1].symp;
                }
break;
case 15:
#line 362 "parser.y"
	{
                        yyval.parv = NULL;

		}
break;
case 16:
#line 369 "parser.y"
	{
                        struct symtab *sp = symlook(yystack.l_mark[-1].symp->name);
                        if (sp == NULL)
                                yyerror("symtab pointer not found");

                        /* paramvalue node */
                        yyval.parv              = calloc(1, sizeof(struct paramvalue));
                        yyval.parv->child       = yystack.l_mark[0].parv;
                        yyval.parv->value       = yystack.l_mark[-1].symp;
                }
break;
case 17:
#line 380 "parser.y"
	{
                        struct symtab *sp = symlook(yystack.l_mark[-1].symp->name);
                        if (sp == NULL)
                                yyerror("symtab pointer not found");

                        /* pramvalue node */
                        yyval.parv              = calloc(1, sizeof(struct paramvalue));
                        yyval.parv->child       = yystack.l_mark[0].parv;
                        yyval.parv->value       = yystack.l_mark[-1].symp;
		}
break;
case 18:
#line 391 "parser.y"
	{
                        yyval.parv = NULL;
                }
break;
case 19:
#line 399 "parser.y"
	{
			/* event-conditions set */
			yyval.evesp		= calloc(1, sizeof(struct eventnodes));
			
			/* link child nodes */
			if (yystack.l_mark[-1].evesp != NULL) {
				yystack.l_mark[-1].evesp->parent = yyval.evesp;
				last_evens = yyval.evesp;
			}
			yystack.l_mark[0].evep->parent = yyval.evesp;
			
			yyval.evesp->evens	= yystack.l_mark[-1].evesp;
			yyval.evesp->even	= yystack.l_mark[0].evep;
		}
break;
case 20:
#line 414 "parser.y"
	{ 
			yyval.evesp = NULL; 
		}
break;
case 21:
#line 420 "parser.y"
	{
			/* event-condition node */
			yystack.l_mark[-8].symp->value	= event_counter;
			yystack.l_mark[-8].symp->type	= "event_id";	
			yystack.l_mark[-8].symp->lib		= yystack.l_mark[-6].symp->lib;
	
			/* init */
			yyval.evep = calloc(1, sizeof(struct eventnode));
			yyval.evep->id		= yystack.l_mark[-8].symp;
			yyval.evep->counter	= yystack.l_mark[-8].symp->value;
			
			/* link child nodes */
			yyval.evep->src		= yystack.l_mark[-6].symp;
			yyval.evep->cst		= yystack.l_mark[-4].symp;
			yyval.evep->cst->value	= editConst(yystack.l_mark[-4].symp);

			struct evtab *ev= evlook(yystack.l_mark[-8].symp->name);
                        ev->num 	= event_counter;
                        ev->op		= yystack.l_mark[-5].ival;
                        ev->value 	= yyval.evep->cst->value;
			ev->scale	= yystack.l_mark[-3].symp;

                        /* event location */
                        if (yystack.l_mark[-2].symp == NULL) {
                                ev->addr        = UNKNOWN;
                        } else {
                                ev->addr        = editConst(yystack.l_mark[-2].symp);
                        }

			event_counter++;
		}
break;
case 22:
#line 455 "parser.y"
	{
                        yyval.symp = yystack.l_mark[0].symp;
                }
break;
case 23:
#line 459 "parser.y"
	{
                        yyval.symp = NULL;
                }
break;
case 24:
#line 466 "parser.y"
	{
			/* policies set */
			yyval.pols = calloc(1, sizeof(struct policies));

			/* link child nodes */
			if (yystack.l_mark[-1].pols != NULL) 
				yystack.l_mark[-1].pols->parent = yyval.pols;
			yystack.l_mark[0].pol->parent = yyval.pols;

			yyval.pols->pols	= yystack.l_mark[-1].pols;
			yyval.pols->pol		= yystack.l_mark[0].pol;
		}
break;
case 25:
#line 479 "parser.y"
	{
			yyval.pols = NULL;
		}
break;
case 26:
#line 485 "parser.y"
	{
			/* policy node */
			yyval.pol 		= calloc(1, sizeof(struct policy));

			/* link child nodes */
			yyval.pol->from	= yystack.l_mark[-5].symp;
			yyval.pol->to		= yystack.l_mark[-3].symp;

			yyval.pol->mask_r	= yystack.l_mark[-1].ival;
			yyval.pol->counter	= policy_counter;

			if (proc_policy(yyval.pol)) {
				fprintf(stderr, "Failed to store policy\n");
				exit(1);
			}
			++policy_counter;
		}
break;
case 27:
#line 504 "parser.y"
	{
			yyval.symp = yystack.l_mark[0].symp;
		}
break;
case 28:
#line 509 "parser.y"
	{
			yyval.symp = yystack.l_mark[0].symp;
		}
break;
case 29:
#line 515 "parser.y"
	{
			yyval.ival = yystack.l_mark[-2].ival + yystack.l_mark[0].ival;	
		}
break;
case 30:
#line 519 "parser.y"
	{
			yyval.ival = yystack.l_mark[0].ival;
		}
break;
case 31:
#line 526 "parser.y"
	{
			/* iterator */
			struct evtab *ep = NULL;
			/* flag */
			int found = 0;
			
			/* check for undeclared identifiers */
			for (ep = evtab; ep < &evtab[NEVS]; ep++)
				if (ep->name && !strcmp(ep->name, yystack.l_mark[0].symp->name)) {
                                        	/* found */
                                        	found = 1;
                                        	break;
                                }
			
			/* undeclared event identifier */
			if (!found)
				yyerror("undeclared event-condition identifier");

			yyval.ival = 1 << ((yystack.l_mark[0].symp->value) - 1);
		}
break;
case 32:
#line 547 "parser.y"
	{
			/* iterator */
			struct evtab *ep = NULL;
			/* flag */
			int found = 0;
			
			/* check for undeclared identifiers */
			for (ep = evtab; ep < &evtab[NEVS]; ep++)
				if (ep->name && !strcmp(ep->name, yystack.l_mark[0].symp->name)) {
                                        	/* found */
                                        	found = 1;
                                        	break;
                                }
			
			/* undeclared event identifier */
			if (!found)
				yyerror("undeclared identifier");

			/* create new event in symtab */
			int len = strlen(yystack.l_mark[0].symp->name) + strlen("not_") + 1;
			char *new = calloc(len, 1);
			(void)snprintf(new, len, "not_%s", yystack.l_mark[0].symp->name);
			struct symtab *sp = symlook(new);

			if (!sp->type) {
				sp->value = event_counter;
				sp->type = strdup(yystack.l_mark[0].symp->type);
				sp->lib = yystack.l_mark[0].symp->lib;

				/* 
				 * make a new event entry by negating the 
				 * operator 
				 */
        	                struct evtab *ev_old = evlook(yystack.l_mark[0].symp->name);
                	        struct evtab *ev_new = evlook(sp->name);

                        	ev_new->num = event_counter;
	                        ev_new->op = negateOperator(ev_old->op);
        	                ev_new->value = ev_old->value;
				
                	        event_counter++;
			}

			yyval.ival = 1 << ((sp->value) - 1);
		}
break;
case 33:
#line 596 "parser.y"
	{
			/* start node */
			yyval.initp = calloc(1, sizeof(struct initnode));

			/* link child nodes */
			yyval.initp->id = yystack.l_mark[-1].symp;
			yyval.initp->init = symlook(yystack.l_mark[-1].symp->name)->value;
		}
break;
case 34:
#line 608 "parser.y"
	{
                        yyval.ival              = yystack.l_mark[-1].ival;
                }
break;
case 35:
#line 612 "parser.y"
	{
                        yyval.ival = 0;
                }
break;
case 36:
#line 618 "parser.y"
	{
                        yyval.ival              = 0;
                        yystack.l_mark[-4].symp->type        = "virtual_id";
                        yystack.l_mark[-4].symp->value       = virtual_counter;


			++virtual_counter;
                }
break;
case 37:
#line 629 "parser.y"
	{
                        yyval.symp = yystack.l_mark[-1].symp;
                }
break;
case 38:
#line 634 "parser.y"
	{
                        yyval.symp = NULL;
                }
break;
case 42:
#line 650 "parser.y"
	{
			/* iterator */
			char *p = NULL;
			
			/* lookup */
			struct symtab *sp = NULL;
		
			/* check for library re-declarations */
			if ((sp = symlook(yystack.l_mark[-5].symp->name)) != NULL &&
						sp->type != NULL)
				/* failed */
				yyerror("redeclaration of library");

			/* fix the child properties */
			yystack.l_mark[-5].symp->type = yystack.l_mark[-6].str;
			yystack.l_mark[-5].symp->lib = yystack.l_mark[-4].libp;

			/* set params for the library */
			yystack.l_mark[-4].libp->params = yystack.l_mark[-1].mtl;

                        /* extract the name from the path */
                        if ((p = rindex(yystack.l_mark[-4].libp->path, '/')) == NULL)
                                yystack.l_mark[-4].libp->name = yystack.l_mark[-4].libp->path;
                        else
                                yystack.l_mark[-4].libp->name = ++p;

                        yystack.l_mark[-4].libp->used = 0;

                        /* save the name as it was defined */
                        yystack.l_mark[-4].libp->def = yystack.l_mark[-5].symp->name;


			/* differentiate based on the definition type */
			if (!strcmp(yystack.l_mark[-5].symp->type, "application")) {
				/* application */
			        char *full_name =  malloc(strlen(yystack.l_mark[-4].libp->name)+strlen("App")+1);
			        sprintf(full_name, "%sApp", yystack.l_mark[-4].libp->name);
				yystack.l_mark[-4].libp->full_name = full_name;
				yystack.l_mark[-4].libp->type = TYPE_APPLICATION;
				yystack.l_mark[-4].libp->used = 0;
				yystack.l_mark[-4].libp->id = 0;
			}
			if (!strcmp(yystack.l_mark[-5].symp->type, "network")) {
				/* network */
			        char *full_name =  malloc(strlen(yystack.l_mark[-4].libp->name)+strlen("Net")+1);
			        sprintf(full_name, "%sNet", yystack.l_mark[-4].libp->name);
				yystack.l_mark[-4].libp->full_name = full_name;
				yystack.l_mark[-4].libp->type = TYPE_NETWORK;
				yystack.l_mark[-4].libp->used = 0;
				yystack.l_mark[-4].libp->id = 0;
			}
                        if (!strcmp(yystack.l_mark[-5].symp->type, "mac")) {
                                /* mac */
			        char *full_name =  malloc(strlen(yystack.l_mark[-4].libp->name)+strlen("Mac")+1);
			        sprintf(full_name, "%sMac", yystack.l_mark[-4].libp->name);
				yystack.l_mark[-4].libp->full_name = full_name;
                                yystack.l_mark[-4].libp->type = TYPE_MAC;
				yystack.l_mark[-4].libp->used = 0;
                                yystack.l_mark[-4].libp->id = 0;
                        }
                        if (!strcmp(yystack.l_mark[-5].symp->type, "radio")) {
                                /* radio */
			        char *full_name =  malloc(strlen(yystack.l_mark[-4].libp->name)+strlen("Radio")+1);
			        sprintf(full_name, "%sRadio", yystack.l_mark[-4].libp->name);
				yystack.l_mark[-4].libp->full_name = full_name;
                                yystack.l_mark[-4].libp->type = TYPE_RADIO;
				yystack.l_mark[-4].libp->used = 0;
                                yystack.l_mark[-4].libp->id = 0;
                        }
			if (!strcmp(yystack.l_mark[-5].symp->type, "source")) {
				/* source */
				yystack.l_mark[-4].libp->type = TYPE_EVENT;
				event_id_counter++;
				yystack.l_mark[-4].libp->used = 0;
				yystack.l_mark[-4].libp->id = event_id_counter;
			}

		}
break;
case 44:
#line 731 "parser.y"
	{ yyval.str = "application"; }
break;
case 45:
#line 732 "parser.y"
	{ yyval.str = "network"; }
break;
case 46:
#line 733 "parser.y"
	{ yyval.str = "mac"; }
break;
case 47:
#line 734 "parser.y"
	{ yyval.str = "radio"; }
break;
case 48:
#line 735 "parser.y"
	{ yyval.str = "source"; }
break;
case 49:
#line 740 "parser.y"
	{

			struct symtab *sp = symlook(yystack.l_mark[-2].symp->name);
			if (sp == NULL)
                                yyerror("symtab pointer not found");


                        yyval.mtl              = calloc(1, sizeof(struct paramtype));
			yyval.mtl->type	= yystack.l_mark[-3].ival;
                        yyval.mtl->name   	= yystack.l_mark[-2].symp->name;
			yyval.mtl->def_val	= yystack.l_mark[-1].defv;
                        yyval.mtl->child       = yystack.l_mark[0].mtl;
		}
break;
case 50:
#line 754 "parser.y"
	{
			yyval.mtl = NULL;
		}
break;
case 51:
#line 761 "parser.y"
	{
			yyval.defv		= calloc(1, sizeof(struct defvalue));
			yyval.defv->def_value	= yystack.l_mark[0].symp;
			yyval.defv->def_valid	= 1;
		}
break;
case 52:
#line 767 "parser.y"
	{
			yyval.defv		= calloc(1, sizeof(struct defvalue));
			yyval.defv->def_value	= NULL;
			yyval.defv->def_valid	= 0;
		}
break;
case 53:
#line 776 "parser.y"
	{
			struct symtab *sp = symlook(yystack.l_mark[-2].symp->name);
			if (sp == NULL)
                                yyerror("symtab pointer not found");

                        yyval.mtl              = calloc(1, sizeof(struct paramtype));
                        yyval.mtl->type   	= yystack.l_mark[-3].ival;
                        yyval.mtl->name   	= yystack.l_mark[-2].symp->name;
			yyval.mtl->def_val	= yystack.l_mark[-1].defv;
			yyval.mtl->child	= yystack.l_mark[0].mtl;
		}
break;
case 54:
#line 788 "parser.y"
	{
			yyval.mtl = NULL;
		}
break;
case 55:
#line 795 "parser.y"
	{
			yyval.ival = 0;

			if (!strcmp(yystack.l_mark[0].symp->name, "uint8_t"))
				yyval.ival = TYPE_UINT8_T;

			if (!strcmp(yystack.l_mark[0].symp->name, "uint16_t"))
				yyval.ival = TYPE_UINT16_T;

			if (!strcmp(yystack.l_mark[0].symp->name, "uint32_t"))
				yyval.ival = TYPE_UINT32_T;

			if (!strcmp(yystack.l_mark[0].symp->name, "float"))
				yyval.ival = TYPE_FLOAT;

			if (!strcmp(yystack.l_mark[0].symp->name, "double"))
				yyval.ival = TYPE_DOUBLE;

		}
break;
#line 1731 "parser.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (short) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    yyerror("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
