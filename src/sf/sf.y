%{
/* Swift Fox Compiler
 * Authors: Marcin Szczodrak
 * Date: 6/9/2012
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

int conf_counter	= 1;
int event_counter	= 1;
int policy_counter	= 0;
int virtual_counter 	= 0;
int event_id_counter	= 0;
int event_scale_counter = 1;
FILE *fcode		= NULL;

int module_id_counter = 1;

int active_state;

struct eventnodes *last_evens = NULL;
int file_status;
char *file_name;

%}

%union {
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
}

%token CONFIGURATION COMMA EVENT_CONDITION 
%token FROM GOTO START USE WHEN 
%token APPLICATION NETWORK QOI MAC RADIO ADDRESS
%token SOURCE LF VIRTUAL_NETWORK
%token LT GT LE GE NE EQ
%token OPEN_BRACE CLOSE_BRACE OPEN_PARENTHESIS CLOSE_PARENTHESIS ONCE
%token OPEN_SQUARE_BRACE CLOSE_SQUARE_BRACE
%token LEVEL AT SHARED


%token <symp>	CONSTANT
%token <symp>	IDENTIFIER
%token <str>	VARIABLE_LINE
%token <libp>	PATH
%token <ival>	RELOP
%token <ival>	AND
%token <ival>	OR
%token <ival>	NOT
%token <modp>	NOTHING
%token <symp>	ANY
%token <modp>	MODULES
%type <modp>	module
%type <symp>	from_configurations
%type <confp>	configuration
%type <confsp>	configurations
%type <confsp>	defined_configurations
%type <evep>	event_condition
%type <evesp>	defined_events
%type <vars>	global_variables
%type <var>	global_variable
%type <pol>	policy;
%type <pols>	policies;
%type <initp>	initial_configuration
%type <prog>	program
%type <str>	type
%type <ival>	when_events
%type <ival>	one_event
%type <ival>	virtual_network
%type <ival>	virtual_networks
%type <symp>	configuration_ids
%type <symp> 	conf_level
%type <symp> 	event_location
%type <symp> 	event_scale
%type <mtl>	module_types
%type <mtl>	next_module_type
%type <parv>	parameters
%type <parv>	next_parameter
%type <ival>	param_type

%%

swiftfox: library program 
		{
			/* verbose; to be removed */
			/* printTable(); */
			
			/* root node for the constructed AST */
			struct program *p = $2;

			/* traverse the AST for semantic checking */	
			traverse_program($2,
					TREE_CHECK_SEMANTIC,
					policy_counter);

			/* traverse the AST for code generation */
			traverse_program($2,
					TREE_GENERATE_CODE,
					policy_counter);
		}
	;

program: global_variables defined_configurations defined_events policies virtual_networks initial_configuration 
		{
			/* root node */
			$$		= calloc(1, sizeof(struct program));
			
			/* link the node appropriately */
			$2->parent	= NULL;  
			if ($3 != NULL ) 
				$3->parent = NULL;
			if ($4 != NULL ) 
				$4->parent = NULL;
			
			/* init */
			$$->defcon	= $2;
			$$->defeve	= $3;
			$$->defpol	= $4;
			$$->init	= $6;
		}
	;


global_variables: global_variables global_variable
                {
			/* global_variable set */
			$$ 		= calloc(1, sizeof(struct variables));

			/* link the child nodes */
			if ($1 != NULL)
				$1->parent = $$;

			$2->parent	= $$;

			$$->vars	= $1;
			$$->var		= $2;
		}
        |       
		{
                        $$ = NULL;
                }                       
        ;


global_variable:  param_type IDENTIFIER newlines
		{
			printf("hello\n");
			//printf("var %s\n", $1);

			$$		= calloc(1, sizeof(struct variable));
			$$->type 	= $1;
			$$->name	= $2;
		
			printf("hello type %d\n", $$->type);
			printf("hello type %s\n", $$->name->name);
			
			//$2->type	= "global_variable_type";
			//$3->type	= "global_variable_name";

			//$$->var_type	= $2;
			//$$->name	= $3;
		}


defined_configurations: configurations configuration
		{
			/* configurations set */
			$$		= calloc(1, sizeof(struct confnodes));
			
			/* link the child nodes */
			if ($1 != NULL)
				$1->parent = $$;
			$2->parent	= $$;
			
			$$->confs	= $1;
			$$->conf	= $2;
		}	
	;

configurations: configurations configuration
		{
			/* configurations set */
			$$		= calloc(1, sizeof(struct confnodes));
			
			/* link the child nodes */
			if ($1 != NULL) 
				$1->parent = $$;
			$2->parent	= $$;

			$$->confs	= $1;
			$$->conf	= $2;
		}
	| 	
		{ 
			$$ = NULL; 
		}			
	;

configuration: CONFIGURATION IDENTIFIER conf_level OPEN_BRACE newlines module newlines module newlines module newlines module newlines CLOSE_BRACE newlines
		{

			/* configuration node */
			$$		= calloc(1, sizeof(struct confnode));

			/* init */
			$2->type	= "configuration_id";
			$$->id		= $2;
	
			if (strcmp($2->name, "policy") == 0) {
				policy_conf_id = conf_counter;
			}

			$2->value	= conf_counter;
			$$->counter	= conf_counter;

			/* level */
			if ($3 == NULL) {
				$$->level	= UNKNOWN;
			} else {
				$$->level	= editConst($3);
			}

			/* set ids */
			
			if ($6->id == 0) {
				$6->id = module_id_counter;
				$6->conf = $$;
				++module_id_counter;
			}

			if ($8->id == 0) {
				$8->id = module_id_counter;
				$8->conf = $$;
				++module_id_counter;
			}

			if ($10->id == 0) {
				$10->id = module_id_counter;
				$10->conf = $$;
				++module_id_counter;
			}

			if ($12->id == 0) {
				$12->id = module_id_counter;
				$12->conf = $$;
				++module_id_counter;
			}

			/* link child nodes */
			$$->app			= $6;
			$$->app_params		= $6->params;
			$$->net			= $8;
			$$->net_params		= $8->params;
			$$->mac			= $10;
			$$->mac_params		= $10->params;
			$$->radio		= $12;
			$$->radio_params	= $12->params;
			++conf_counter;
		}
	;

conf_level: LEVEL CONSTANT
		{
			$$ = $2;
		}
        |       
                {
                        $$ = NULL;
                }                       
        ;



module: IDENTIFIER OPEN_PARENTHESIS parameters CLOSE_PARENTHESIS
		{
			$$ = proc_module($1->name);
			$$->params = $3;
		}		
	;

parameters: IDENTIFIER next_parameter
                {
                        struct symtab *sp = symlook($1->name);
                        if (sp == NULL)
                                yyerror("sp not found: %s\n", $1->name);

                        /* paramvalue node */
                        $$              = calloc(1, sizeof(struct paramvalue));
			$$->child	= $2;
                        $$->value       = $1;
                }
        | CONSTANT next_parameter
                {
                        struct symtab *sp = symlook($1->name);
                        if (sp == NULL)
                                yyerror("sp not found: %s\n", $1->name);

                        /* pramvalue node */
                        $$              = calloc(1, sizeof(struct paramvalue));
                        $$->child       = $2;
                        $$->value       = $1;
                }
	|	
		{
                        $$ = NULL;

		}
        ;

next_parameter: COMMA IDENTIFIER next_parameter 
                {
                        struct symtab *sp = symlook($2->name);
                        if (sp == NULL)
                                yyerror("sp not found: %s\n", $2->name);

                        /* paramvalue node */
                        $$              = calloc(1, sizeof(struct paramvalue));
                        $$->child       = $3;
                        $$->value       = $2;
                }
        | COMMA CONSTANT next_parameter
		{
                        struct symtab *sp = symlook($2->name);
                        if (sp == NULL)
                                yyerror("sp not found: %s\n", $2->name);

                        /* pramvalue node */
                        $$              = calloc(1, sizeof(struct paramvalue));
                        $$->child       = $3;
                        $$->value       = $2;
		}
	|
                {
                        $$ = NULL;
                }
        ;



defined_events: defined_events event_condition
		{
			/* event-conditions set */
			$$		= calloc(1, sizeof(struct eventnodes));
			
			/* link child nodes */
			if ($1 != NULL) {
				$1->parent = $$;
				last_evens = $$;
			}
			$2->parent = $$;
			
			$$->evens	= $1;
			$$->even	= $2;
		}
	|	
		{ 
			$$ = NULL; 
		}	
	;

event_condition: EVENT_CONDITION IDENTIFIER OPEN_BRACE IDENTIFIER RELOP CONSTANT event_scale event_location CLOSE_BRACE newlines
		{
			/* event-condition node */
			$2->value	= event_counter;
			$2->type	= "event_id";	
			$2->lib		= $4->lib;
	
			/* init */
			$$ = calloc(1, sizeof(struct eventnode));
			$$->id		= $2;
			$$->counter	= $2->value;
			
			/* link child nodes */
			$$->src		= $4;
			$$->cst		= $6;
			$$->cst->value	= editConst($6);


			struct evtab *ev= evlook($2->name);
                        ev->num 	= event_counter;
                        ev->op		= $5;
                        ev->value 	= $$->cst->value;

			if ($7 != NULL) {
				if ($7->type == NULL) {
					$7->value = event_scale_counter;
					$7->type = "event_scale";
					event_scale_counter++;
				}

				ev->scale	= $7;
			} else {
				ev->scale	= NULL;
			}

                        /* event location */
                        if ($8 == NULL) {
                                ev->addr        = UNKNOWN;
                        } else {
                                ev->addr        = editConst($8);
                        }

			event_counter++;
		}
	;


event_location: AT CONSTANT
                {
                        $$ = $2;
                }
        |       
                {
                        $$ = NULL;
                }                       
        ;


event_scale: IDENTIFIER
		{
			$$ = $1;
			/*
			if ($1 != NULL && $1->type != NULL) {
				$1->value = event_scale_counter;
				$1->type = "event_scale";
				event_scale_counter++;
			}
			*/
		}
	|
		{
			$$ = NULL;
		}
	;



policies: policies policy 
		{
			/* policies set */
			$$ = calloc(1, sizeof(struct policies));

			/* link child nodes */
			if ($1 != NULL) 
				$1->parent = $$;
			$2->parent = $$;

			$$->pols	= $1;
			$$->pol		= $2;
		}
	|	
		{
			$$ = NULL;
		}		
	;

policy: FROM from_configurations GOTO IDENTIFIER WHEN when_events newlines
		{
			/* policy node */
			$$ 		= calloc(1, sizeof(struct policy));

			/* link child nodes */
			$$->from	= $2;
			$$->to		= $4;

			$$->mask_l	= 0;
			$$->mask_r	= -1;
			$$->mask_l	= $6;
			$$->counter	= policy_counter;

			if (proc_policy($$)) {
				fprintf(stderr, "Failed to store policy\n");
				exit(1);
			}
			++policy_counter;
		}

/*

	|	FROM from_configurations GOTO IDENTIFIER WHEN when_events OR when_events newlines
                {
                        $$              = calloc(1, sizeof(struct policy));

                        $$->from        = $2;
                        $$->to          = $4;

                        $$->mask_l        = 0;
                        $$->mask_r        = 0;
                        $$->mask_l        = $6;
                        $$->mask_r        = $8;
                        $$->counter     = policy_counter;

                        ++policy_counter;
                        ++policy_counter;
                }
*/

	;

from_configurations: IDENTIFIER 	
		{
			$$ = $1;
		}
		
	| 	ANY
		{
			$$ = $1;
		}
	;

when_events: one_event AND when_events 
		{
			$$ = $1 + $3;	
		}
	| 	one_event
		{
			$$ = $1;
		}
	;


one_event: IDENTIFIER
		{
			/* iterator */
			struct evtab *ep = NULL;
			/* flag */
			int found = 0;
			
			/* check for undeclared identifiers */
			for (ep = evtab; ep < &evtab[NEVS]; ep++)
				if (ep->name && !strcmp(ep->name, $1->name)) {
                                        	/* found */
                                        	found = 1;
                                        	break;
                                }
			
			/* undeclared event identifier */
			if (!found)
				yyerror("undeclared event-condition identifier");

			$$ = 1 << (($1->value) - 1);
		}
	| NOT IDENTIFIER
		{
			/* iterator */
			struct evtab *ep = NULL;
			/* flag */
			int found = 0;
			
			/* check for undeclared identifiers */
			for (ep = evtab; ep < &evtab[NEVS]; ep++)
				if (ep->name && !strcmp(ep->name, $2->name)) {
                                        	/* found */
                                        	found = 1;
                                        	break;
                                }
			
			/* undeclared event identifier */
			if (!found)
				yyerror("undeclared identifier");

			/* create new event in symtab */
			int len = strlen($2->name) + strlen("not_") + 1;
			char *new = calloc(len, 1);
			(void)snprintf(new, len, "not_%s", $2->name);
			struct symtab *sp = symlook(new);

			if (!sp->type) {
				sp->value = event_counter;
				sp->type = strdup($2->type);
				sp->lib = $2->lib;

				/* 
				 * make a new event entry by negating the 
				 * operator 
				 */
        	                struct evtab *ev_old = evlook($2->name);
                	        struct evtab *ev_new = evlook(sp->name);

                        	ev_new->num = event_counter;
	                        ev_new->op = negateOperator(ev_old->op);
        	                ev_new->value = ev_old->value;
				
                	        event_counter++;
			}

			$$ = 1 << ((sp->value) - 1);
		}
	;


initial_configuration: START IDENTIFIER newlines
		{
			/* start node */
			$$ = calloc(1, sizeof(struct initnode));

			/* link child nodes */
			$$->id = $2;
			$$->init = symlook($2->name)->value;
		} 
	;


virtual_networks: virtual_networks virtual_network
                {
                        $$              = $1;
                }
        |       
                {
                        $$ = 0;
                }    
        ;

virtual_network: VIRTUAL_NETWORK IDENTIFIER OPEN_BRACE configuration_ids CLOSE_BRACE newlines
                {
                        $$              = 0;
                        $2->type        = "virtual_id";
                        $2->value       = virtual_counter;


			++virtual_counter;
                }
        ;

configuration_ids: configuration_ids IDENTIFIER         
                {
                        $$ = $1;
                }
                
        |
                {
                        $$ = NULL;
                }
        ;

/* Library section */


library: newlines definitions
	;

definitions: definitions definition 
        |
        ;

definition: USE type IDENTIFIER PATH OPEN_PARENTHESIS newlines module_types CLOSE_PARENTHESIS
		{
			/* iterator */
			char *p = NULL;
			
			/* lookup */
			struct symtab *sp = NULL;
		
			/* check for library re-declarations */
			if ((sp = symlook($3->name)) != NULL &&
						sp->type != NULL)
				/* failed */
				yyerror("redeclaration of library");

			/* fix the child properties */
			$3->type = $2;
			$3->lib = $4;

			/* set params for the library */
			$4->params = $7;

                        /* extract the name from the path */
                        if ((p = rindex($4->path, '/')) == NULL)
                                $4->name = $4->path;
                        else
                                $4->name = ++p;

                        $4->used = 0;

                        /* save the name as it was defined */
                        $4->def = $3->name;


			/* differentiate based on the definition type */
			if (!strcmp($3->type, "application")) {
				/* application */
			        char *full_name =  malloc(strlen($4->name)+strlen("App")+1);
			        sprintf(full_name, "%sApp", $4->name);
				$4->full_name = full_name;
				$4->type = TYPE_APPLICATION;
				$4->used = 0;
				$4->id = 0;
			}
			if (!strcmp($3->type, "network")) {
				/* network */
			        char *full_name =  malloc(strlen($4->name)+strlen("Net")+1);
			        sprintf(full_name, "%sNet", $4->name);
				$4->full_name = full_name;
				$4->type = TYPE_NETWORK;
				$4->used = 0;
				$4->id = 0;
			}
                        if (!strcmp($3->type, "mac")) {
                                /* mac */
			        char *full_name =  malloc(strlen($4->name)+strlen("Mac")+1);
			        sprintf(full_name, "%sMac", $4->name);
				$4->full_name = full_name;
                                $4->type = TYPE_MAC;
				$4->used = 0;
                                $4->id = 0;
                        }
                        if (!strcmp($3->type, "radio")) {
                                /* radio */
			        char *full_name =  malloc(strlen($4->name)+strlen("Radio")+1);
			        sprintf(full_name, "%sRadio", $4->name);
				$4->full_name = full_name;
                                $4->type = TYPE_RADIO;
				$4->used = 0;
                                $4->id = 0;
                        }
			if (!strcmp($3->type, "source")) {
				/* source */
				$4->type = TYPE_EVENT;
				event_id_counter++;
				$4->used = 0;
				$4->id = event_id_counter;
			}

		}
		newlines
        ;

type: APPLICATION { $$ = "application"; }
        | NETWORK { $$ = "network"; }
        | MAC { $$ = "mac"; }
        | RADIO { $$ = "radio"; }
	| SOURCE { $$ = "source"; }
        ;


module_types: param_type IDENTIFIER next_module_type
		{

			struct symtab *sp = symlook($2->name);
			if (sp == NULL)
				yyerror("sp not found: %s\n", $2->name);


                        $$              = calloc(1, sizeof(struct paramtype));
			$$->type	= $1;
                        $$->name   = $2->name;
                        $$->child       = $3;
		}
	|
		{
			$$ = NULL;
		}
	;

next_module_type: newlines COMMA newlines param_type IDENTIFIER next_module_type
		{
			struct symtab *sp = symlook($5->name);
			if (sp == NULL)
				yyerror("sp not found: %s\n", $5->name);

                        $$              = calloc(1, sizeof(struct paramtype));
                        $$->type   	= $4;
                        $$->name   	= $5->name;
			$$->child	= $6;
		}
	|
		{
			$$ = NULL;
		}
	;


param_type: IDENTIFIER
		{
			$$ = 0;

			if (!strcmp($1->name, "uint8_t"))
				$$ = TYPE_UINT8_T;

			if (!strcmp($1->name, "uint16_t"))
				$$ = TYPE_UINT16_T;

			if (!strcmp($1->name, "uint32_t"))
				$$ = TYPE_UINT32_T;

			if (!strcmp($1->name, "float"))
				$$ = TYPE_FLOAT;

			if (!strcmp($1->name, "double"))
				$$ = TYPE_DOUBLE;

		}
	;



newlines: newlines newline
	|
	;

newline: LF 
	;

%%

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

	/* cleanup */	
	(void)atexit(gc);

	initialize();
	
	/* process libraries */
	lineno = 1;
	tokenpos = 0;
	
	/* try fennec fox standart libray located at ($FENNEC_FOX_LIB)/STD_FENNEC_FOX_LIB */
	yyin = fopen(fennec_library_file, "r");
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
yyerror(char *errmsg) {
	
	/* error in program */
	(void)fprintf(stderr, "\nsfc in program: %s\n", file_name);

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
	printf("file status is %d\n", file_status);

	switch(file_status) {
		case 1:
	        	/* open the specific library file */
		        yyin 		= fopen(library_file, "r");
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

	for (; isdigit(*sp); sp++);
	
	/* set the type accordingly */

	/* sec */
        if (!strcmp(sp, "sec")) {
		entry->type = strdup("timer");
                v *= SEC_CONV;
		return v;
	}
	
	/* min */
        if (!strcmp(sp, "min")) {
		entry->type = strdup("timer");
                v *= MIN_CONV;
		return v;
	}
	
	/* hr */
        if (!strcmp(sp, "hr")) {
		entry->type = strdup("timer");
                v = HR_CONV;
		return v;
	}
	
	/* Celsius */
	if (!strcmp(sp, "C")) {
		entry->type = strdup("temperature");
		return v;
	}
	
	/* Fahrenheit */
	if (!strcmp(sp, "F")) {
		entry->type = strdup("temperature");
                v = (v - 32) * 5 / 9 ;
		return v;
	}
	
	/* default */
	entry->type = strdup("number");

        return v;
}

printTable() {

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
	(void)close(yyin);
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

