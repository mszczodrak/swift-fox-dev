/*
 * Copyright (c) 2010-2014, Columbia University.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *  - Neither the name of the Columbia University nor the
 *    names of its contributors may be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL COLUMBIA UNIVERSITY BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
  * Swift Fox compiler
  *
  * @author: Marcin K Szczodrak
  */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <ctype.h>
#include <stdint.h>
#include "utils.h"
#include "sf.h"
#include "parser.h"


/**
converts type value (int) into string

\param type_value constant representing a type

\return string C-compliant type
*/
char * type_name(int type_value) {
	switch(type_value) {
	case TYPE_BOOL:
		return "bool";

	case TYPE_UINT8_T:
		return "uint8_t";

	case TYPE_UINT16_T:
		return "uint16_t";

	case TYPE_UINT32_T:
		return "uint32_t";

	case TYPE_INT8_T:
		return "int8_t";

	case TYPE_INT16_T:
		return "int16_t";

	case TYPE_INT32_T:
		return "int32_t";

	case TYPE_FLOAT:
		return "float";

	case TYPE_DOUBLE:
		return "double";

	default:
		return "";
	}
}


int type_size(int type_value) {
	switch(type_value) {
	case TYPE_BOOL:
		return sizeof(uint8_t);

	case TYPE_UINT8_T:
		return sizeof(uint8_t);

	case TYPE_UINT16_T:
		return sizeof(uint16_t);

	case TYPE_UINT32_T:
		return sizeof(uint32_t);

	case TYPE_INT8_T:
		return sizeof(int8_t);

	case TYPE_INT16_T:
		return sizeof(int16_t);

	case TYPE_INT32_T:
		return sizeof(int32_t);

	case TYPE_FLOAT:
		return sizeof(float);

	case TYPE_DOUBLE:
		return sizeof(double);

	default:
		return 0;
	}
}


/**
converts local path within Fennec Fox library to a complete path 
within the system

\param ffsrc_relative string with local path

\return tmp complete path

*/
char *get_full_path(char *ffsrc_relative) {
	char *fennec_fox_lib = getenv("FENNEC_FOX_LIB");
	char *tmp;

	if (fennec_fox_lib == NULL) {
		fprintf(stderr, "\n\nFENNEC_FOX_LIB is not set!\n");
		exit(1);
	}

	tmp = malloc(strlen(ffsrc_relative) + strlen(fennec_fox_lib) + 2);
	sprintf(tmp, "%s/%s", fennec_fox_lib, ffsrc_relative);
	return tmp;
}

/** 
creates a path to a file located within Fennec Fox source directory

\param file1 string with relative path withing Fennec Fox

\param file2 name of a file

\return tmp a complete path to file2
*/
char *get_sfc_path(char *file1, char *file2) {
	char *fennec_fox_lib = getenv("FENNEC_FOX_LIB");
	char *tmp;

	if (fennec_fox_lib == NULL) {
		fprintf(stderr, "\n\nFENNEC_FOX_LIB is not set!\n");
		exit(1);
	}

	tmp = malloc(strlen(fennec_fox_lib) + strlen("Fennec/sfc/") + 
					strlen(file1) + strlen(file2) + 2);
	sprintf(tmp, "%s/Fennec/sfc/%s%s", fennec_fox_lib, file1, file2);
	return tmp;
}


/**
creates directory within Fennec Fox

\param ffsrc_relative string with a path within Fennec Fox source directory

\return status reporting successful creation of a directory
*/
int create_dir(char *ffsrc_relative) {
	struct stat st;
	char *dirpath = get_full_path(ffsrc_relative);
	int status = 0;
	if (stat(dirpath, &st) != 0) {
		status = mkdir(dirpath, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	}
	free(dirpath);
	return status;
}

int get_policy_mask(struct policy *p) {
	struct conf_ids *cids = NULL;
	int mask = 0;
	for (cids = p->event_confs; cids != NULL; cids = cids->confs) {
		mask |= 1 << cids->conf->conf->id->value;
	}
	return mask;
}


int check_path(char *path) {
	struct stat st;
	char temp_path[PATH_SZ];

	(void)memset(temp_path, 0, PATH_SZ);

	if (path[0] == '$') {
		(void)sprintf(temp_path, "%s%s", getenv("FENNEC_FOX_LIB"),
			path + strlen("$(FENNEC_FOX_LIB)"));
		path = temp_path;
	}

	if (stat(path, &st) != 0) {
		return 1;
	}
	return 0;
}

char *str_toupper(char *s) {
	char *p = s;
	for(; *p != '\0'; p++ ) {
		*p = toupper(*p);
	}
	return s;
}

char *conf_module_name(char *conf, char *module) {
	char *n = NULL;
	if((n = malloc(strlen(conf) + strlen(module) + 2)) != NULL) {
		n[0] = '\0';
		strcat(n, conf);
		strcat(n, "_");
		strcat(n, module);
	} else {
		printf("malloc failed!\n");
		// exit?
	}
	return str_toupper(n);
}



int updateModuleVariables(struct modtab *mp) {
	struct variables *lvar = mp->lib->variables;
	struct variables *mvar = mp->variables;
	struct variables *revar = NULL;
	int number_of_variables = 0;

	while(mvar != NULL && mvar->vars != NULL) {
		mvar = mvar->vars;
	}

	revar = mvar;

	while(lvar != NULL && lvar->vars != NULL) {
		lvar = lvar->vars;
	}

	while (lvar != NULL) {
		/* case when we use global variable */
		if (mvar != NULL && mvar->var->class_type == TYPE_VARIABLE_GLOBAL) {
			/* this already points to global variable, so should
			 * be fine; just check if the type matches */
			if (mvar->var->type != lvar->var->type) {
				if (sfc_debug) {
					printf("type mismatch %d vs %d\n", mvar->var->type, lvar->var->type);
				}
				fprintf(stderr, "module %s got variable %s of type %s, while the library expects type %s for variable %s\n",
					mp->name,
					mvar->var->name,
					type_name(mvar->var->type),
					type_name(lvar->var->type),
					lvar->var->name);
				exit(1);
			}
			/* still copy the application perspective name */
			struct variable *global_var = mvar->var;
			mvar->var = malloc(sizeof(struct variable));
			memcpy(mvar->var, global_var, sizeof(struct variable));
			mvar->var->cap_name = lvar->var->cap_name;
		}

		/* case when we use a constant as a variable */
		if (mvar != NULL && mvar->var->class_type == TYPE_VARIABLE_LOCAL) {
			mvar->var->type = lvar->var->type;	
			mvar->var->name = lvar->var->name;
			mvar->var->length = lvar->var->length;
			mvar->var->cap_name = lvar->var->cap_name;
			mvar->var->offset = variable_memory_offset;
			mvar->var->init = 1;
			variable_memory_offset += (type_size(lvar->var->type) * lvar->var->length);
		}

		/* case when mvar is missing, so copy the lvar */
		if (mvar == NULL) {
			mvar = malloc(sizeof(struct variables));
			//mvar->vars = NULL;
			mvar->var = malloc(sizeof(struct variable));
			mvar->parent = NULL;

			mvar->vars = mp->variables;
			mp->variables = mvar;
			mvar->vars->parent = mvar;

			memcpy(mvar->var, lvar->var, sizeof(struct variable));
			mvar->var->offset = variable_memory_offset;
			mvar->var->class_type = TYPE_VARIABLE_LOCAL;
			variable_memory_offset += (type_size(lvar->var->type) * lvar->var->length);
		}

		if (mvar != NULL) {
			mvar = mvar->parent;
		}
		lvar = lvar->parent;
		number_of_variables++;
	}

	if (mvar != NULL) {
		fprintf(stderr, "more variables defined that declared\n");
		exit(1);
	}

	/* Reverse order of variables.. this way they can be traversed in order */
	mp->variables_end = revar;

	return number_of_variables;
}

void updateProcessVariables(struct confnode* c) {
	c->app_var_num = updateModuleVariables(c->app);
	c->net_var_num = updateModuleVariables(c->net);
	c->am_var_num = updateModuleVariables(c->am);
}

