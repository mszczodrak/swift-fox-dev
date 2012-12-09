/** \file
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

#ifndef SF_H
#define SF_H

#define TREE_TRAVERSE 		1
#define TREE_CHECK_SEMANTIC 	2 
#define TREE_GENERATE_CODE 	3

#define NSYMS 			256
#define NMODS 			256
#define NLIBS 			256
#define NEVS 			256
#define NCONFS			256
#define NPOLS			256

#define TYPE_APPLICATION	1
#define TYPE_NETWORK		2
#define TYPE_EVENT		3
#define TYPE_MAC		5
#define TYPE_RADIO		6
#define TYPE_ADDRESS		7
#define TYPE_TYPE		8

#define TYPE_UINT8_T		20
#define TYPE_UINT16_T		21
#define TYPE_UINT32_T		22
#define TYPE_FLOAT		23
#define TYPE_DOUBLE		24

#define PATH_SZ			256
#define ARGC_MAX		2

#define SEC_CONV		1024
#define MIN_CONV		60 * SEC_CONV
#define HR_CONV			60 * MIN_CONV

#define NUMBER_OF_FF_MODULES	7

#define BUF_SZ			1024

#define TEMP_DIR                "/tmp/swift_fox"

#define STD_FENNEC_FOX_LIB	"support/sfc/fennec.sfl"

#define POLICY_CONFIGURATION	250

#define UNKNOWN			-1

extern char *ffmodules;
extern int active_state;
extern char *conf_state_name;
extern int conf_state_id;
extern int conf_state_redefined;

extern char *conf_state_app;
extern char *conf_state_net;
extern char *conf_state_mac;
extern char *conf_state_radio;

int start_parser(int argc, char *argv[]);

int lineno;
char linebuf[BUF_SZ];
int tokenpos;

/* Symbol Table */
struct symtab {
	char			*name;
	int			value;
	char 			*type;
	struct libtab		*lib;
} symtab[NSYMS];

struct symtab *symlook(char *);
struct symtab *find_sym(char *);

struct defvalue {
	struct symtab		*def_value;
	int 			def_valid;
};

struct paramtype {
        struct paramtype        *child;
	int			type;
	struct defvalue		*def_val;
        char                    *name;
};

struct paramvalue {
	struct paramvalue	*child;	
	struct symtab		*value;
};

struct libtab {
        char			*path;
	char			*def;
	char			*name;
	char			*full_name;
	struct paramtype	*params;
	int			used;
	int			type;
	int			id;
} libtab[NLIBS];

struct libtab *liblook(char *);

struct evtab {
	char			*name;
	int			num;
	int			op;	
	int			value;
	int			addr;
	struct symtab 		*scale;
} evtab[NEVS];

struct evtab *evlook(char *);

struct modtab {
        int            		 id;
        char            	*type;
        struct libtab   	*lib;
	struct paramvalue	*params;
        struct confnode 	*conf;
        int             	conf_num;
        int             	confs[NCONFS];
} modtab[NMODS];

struct modtab *proc_module(char *);

struct confnode {
	struct confnodes	*parent;
	struct symtab		*id;
	struct modtab		*app;
	struct modtab		*net;
	struct modtab		*mac;
	struct modtab		*radio;
	struct paramvalue	*app_params;
	struct paramvalue	*net_params;
	struct paramvalue	*mac_params;
	struct paramvalue	*radio_params;
	int			counter;
	int 			level;
};

struct conftab {
        struct confnode		*conf;
} conftab[NCONFS];


struct confnodes {
	struct confnodes	*parent;
	struct confnodes	*confs;
	struct confnode		*conf;
};


struct eventnode {
	struct eventnodes	*parent;
	struct symtab		*id;
	struct symtab		*src;
	int 			op;
	int 			counter;
	struct symtab		*cst;
};

struct eventnodes {
	struct eventnodes	*parent;
        struct eventnodes	*evens;
        struct eventnode	*even;
};

struct variable {
	struct variables	*parent;
	int			type;
	struct symtab		*var_type;
	struct symtab		*name;
};


struct variables {
	struct variables	*parent;
	struct variables	*vars;
	struct variable		*var;
};

struct policy {
	struct policies		*parent;
	struct symtab		*from;
	struct symtab		*to;
	int 			mask_r;
	int 			counter;
};

struct policies {
	struct policies		*parent;
	struct policies		*pols;
	struct policy 		*pol;
};

struct initnode {
	struct symtab 		*id;
	int 			init;
};

struct program {
	struct variables	*vars;
	struct confnodes	*defcon;
	struct eventnodes	*defeve;
	struct policies		*defpol;
	struct initnode		*init;
};


struct poltab {
        int                     policy_num;
        int                     *src_conf;
        int                     *event_mask;
        int                     *dst_conf;
} poltab[NPOLS];

int proc_policy(struct policy *p);

#endif
