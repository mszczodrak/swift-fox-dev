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

#include "code_gen.h"
#include "utils.h"

int generate_globals = 1;

void initDataStorageValues() {
	char *full_path = get_sfc_path("", "fennec_data_values.h");
	FILE *fp = fopen(full_path, "w");

	if (fp == NULL) {
		fprintf(stderr, "You do not have a permission to write \
						into file: %s\n", full_path);
		exit(1);
	}

	fprintf(fp, "#ifndef _FF_DATA_STORAGE_VALUES_H_\n");
	fprintf(fp, "#define _FF_DATA_STORAGE_VALUES_H_\n\n");
	fprintf(fp, "#include \"Fennec.h\"\n\n");

	fprintf(fp, "struct global_data fennec_global_data = {\n");
	
	free(full_path);
	fclose(fp);
}


void initGlobalDataH() {
	/* global struct */
	char *full_path = get_sfc_path("", "global_data.h");
	FILE *fp = fopen(full_path, "w");

	if (fp == NULL) {
		fprintf(stderr, "You do not have a permission to write \
						into file: %s\n", full_path);
		exit(1);
	}

	fprintf(fp, "#ifndef _GLOBAL_DATA_H_\n");
	fprintf(fp, "#define _GLOBAL_DATA_H_\n\n");

	fprintf(fp, "struct global_data {\n");

	free(full_path);
	fclose(fp);
	/* end of definig global variables */
}

void finishGlobalDataH() {
	/* global struct */
	char *full_path = get_sfc_path("", "global_data.h");
	FILE *fp = fopen(full_path, "a");

	if (fp == NULL) {
		fprintf(stderr, "You do not have a permission to write \
						into file: %s\n", full_path);
		exit(1);
	}

	fprintf(fp, "};\n\n");
	fprintf(fp, "#endif\n\n");

	free(full_path);
	fclose(fp);
	/* end of definig global variables */
}

void globalDataMsgH() {
	/* global struct */
	char *full_path = get_sfc_path("", "global_data_msg.h");
	FILE *fp = fopen(full_path, "w");
	int i;
	int global_number = 0;
//	int byte_hist = 0;

	if (fp == NULL) {
		fprintf(stderr, "You do not have a permission to write \
						into file: %s\n", full_path);
		exit(1);
	}

	fprintf(fp, "#ifndef _GLOBAL_DATA_MSG_H_\n");
	fprintf(fp, "#define _GLOBAL_DATA_MSG_H_\n\n");

	fprintf(fp, "nx_struct global_data_msg {\n");

	for( i = 0; i < NVARS; i++ ) {
		if (vartab[i].length == 0) {
			break;
		}

		if ((vartab[i].class_type != TYPE_VARIABLE_GLOBAL) ||
			(vartab[i].used != 1) ||
			(vartab[i].gname != NULL)) {
			continue;
		}

		if (vartab[i].length > 1) {
			fprintf(fp, "\tnx_%s %s[%d];\n", type_name(vartab[i].type), 
						vartab[i].name,
						vartab[i].length);
		} else {
			fprintf(fp, "\tnx_%s %s;\n", type_name(vartab[i].type), 
						vartab[i].name);
		}
		global_number++;
	}

	fprintf(fp, "};\n\n\n");

//	byte_hist = global_number / 8;
//	if (global_number % 8 != 0) {
//		byte_hist++;
//	}

//	//printf("%d %d\n", global_number, byte_hist);
	fprintf(fp, "#define NUMBER_OF_GLOBALS \t%d\n\n", global_number);

	fprintf(fp, "nx_struct global_data_msg fennec_global_data_nx;\n\n");

	fprintf(fp, "struct variable_info global_data_info[NUMBER_OF_GLOBALS] = {\n");
	for( i = 0; i < NVARS; i++ ) {
		if (vartab[i].length == 0) {
			break;
		}

		if ((vartab[i].class_type != TYPE_VARIABLE_GLOBAL) ||
			(vartab[i].used != 1) ||
			(vartab[i].gname != NULL)) {
			continue;
		}

		fprintf(fp, "\t{ %s, \t%d, \t%d },\n", vartab[i].cap_name,
				vartab[i].offset, 
				(type_size(vartab[i].type) * vartab[i].length));
	}

	fprintf(fp, "};\n\n");
/*
	switch(byte_hist) {
	case 1:
		fprintf(fp, "nx_uint8_t global_data_history = 0;\n\n");
		break;
	case 2:
		fprintf(fp, "nx_uint16_t global_data_history = 0;\n\n");
		break;
	case 3:
	case 4:
		fprintf(fp, "nx_uint32_t global_data_history = 0;\n\n");
		break;
	default:
		(void)fprintf(stderr, "Too many global variables: %d", global_number);
		exit(1);
	}
*/

	fprintf(fp, "void globalDataSyncWithNetwork() {\n");
	for( i = 0; i < NVARS; i++ ) {
		if (vartab[i].length == 0) {
			break;
		}

		if ((vartab[i].class_type != TYPE_VARIABLE_GLOBAL) ||
			(vartab[i].used != 1) ||
			(vartab[i].gname != NULL)) {
			continue;
		}

		fprintf(fp, "\tfennec_global_data.%s = (%s) fennec_global_data_nx.%s;\n",
			vartab[i].name, type_name(vartab[i].type), vartab[i].name);
	}
	fprintf(fp, "};\n\n\n");

	fprintf(fp, "void globalDataSyncWithLocal() {\n");
	for( i = 0; i < NVARS; i++ ) {
		if (vartab[i].length == 0) {
			break;
		}

		if ((vartab[i].class_type != TYPE_VARIABLE_GLOBAL) ||
			(vartab[i].used != 1) ||
			(vartab[i].gname != NULL)) {
			continue;
		}

		fprintf(fp, "\tfennec_global_data_nx.%s = (nx_%s) fennec_global_data.%s;\n",
			vartab[i].name, type_name(vartab[i].type), vartab[i].name);
	}
	fprintf(fp, "};\n\n\n");

	fprintf(fp, "#if defined(FENNEC_TOS_PRINTF) || defined(FENNEC_COOJA_PRINTF)\n");
	fprintf(fp, "void printfGlobalData() {\n");
	for( i = 0; i < NVARS; i++ ) {
		if (vartab[i].length == 0) {
			break;
		}

		if ((vartab[i].class_type != TYPE_VARIABLE_GLOBAL) ||
			(vartab[i].used != 1) ||
			(vartab[i].gname != NULL)) {
			continue;
		}

		switch(vartab[i].type) {
		case TYPE_BOOL:
		case TYPE_UINT8_T:
		case TYPE_UINT16_T:
		case TYPE_NXUINT8_T:
		case TYPE_NXUINT16_T:
			fprintf(fp, "\tprintf(\"%s -> %%u\\n\", fennec_global_data_nx.%s);\n",
				vartab[i].name, vartab[i].name);
			break;
		case TYPE_UINT32_T:
		case TYPE_NXUINT32_T:
			fprintf(fp, "\tprintf(\"%s -> %%lu\\n\", fennec_global_data_nx.%s);\n",
				vartab[i].name, vartab[i].name);
			break;
		case TYPE_FLOAT:
		case TYPE_DOUBLE:
			fprintf(fp, "\tprintf(\"%s -> %%f\\n\", fennec_global_data_nx.%s);\n",
				vartab[i].name, vartab[i].name);
			break;
		default:
			fprintf(fp, "\tprintf(\"%s -> %%d\\n\", fennec_global_data_nx.%s);\n",
				vartab[i].name, vartab[i].name);
		}
	}
	fprintf(fp, "};\n");
	fprintf(fp, "#endif\n\n");

	fprintf(fp, "#endif\n\n");

	free(full_path);
	fclose(fp);
	/* end of definig global variables */
}


void initLocalDataH() {
	/* local struct */
	char *full_path = get_sfc_path("", "local_data.h");
	FILE *fp = fopen(full_path, "w");

	if (fp == NULL) {
		fprintf(stderr, "You do not have a permission to write \
						into file: %s\n", full_path);
		exit(1);
	}

	fprintf(fp, "#ifndef _LOCAL_DATA_H_\n");
	fprintf(fp, "#define _LOCAL_DATA_H_\n\n");

	fprintf(fp, "struct local_data {\n");

	free(full_path);
	fclose(fp);
	/* end of definig local variables */
}


void finishLocalDataH() {
	/* local struct */
	char *full_path = get_sfc_path("", "local_data.h");
	FILE *fp = fopen(full_path, "a");

	if (fp == NULL) {
		fprintf(stderr, "You do not have a permission to write \
						into file: %s\n", full_path);
		exit(1);
	}

	fprintf(fp, "};\n\n");
	fprintf(fp, "#endif\n\n");

	free(full_path);
	fclose(fp);
	/* end of definig local variables */
}


void finishDataStorageValues() {
	/* global variables init */
	char *full_path = get_sfc_path("", "fennec_data_values.h");
	FILE *fp = fopen(full_path, "a");

	if (fp == NULL) {
		fprintf(stderr, "You do not have a permission to write \
						into file: %s\n", full_path);
		exit(1);
	}

	fprintf(fp, "};\n\n");
	fprintf(fp, "#endif\n\n");

	free(full_path);
	fclose(fp);
	/* end of initializing global variables */
}


void switchGlobalToLocalDataStorage() {
	/* global variables init */
	char *full_path = get_sfc_path("", "fennec_data_values.h");
	FILE *fp = fopen(full_path, "a");

	if (fp == NULL) {
		fprintf(stderr, "You do not have a permission to write \
						into file: %s\n", full_path);
		exit(1);
	}

	fprintf(fp, "};\n\n");

	generate_globals = 0;

	fprintf(fp, "struct local_data fennec_local_data = {\n");

	free(full_path);
	fclose(fp);
	/* end of initializing global variables */
}


void addGlobalVariable(struct variable *sh) {
	/* global struct */
	char *full_path = get_sfc_path("", "global_data.h");
	FILE *fp = fopen(full_path, "a");

	if (fp == NULL) {
		fprintf(stderr, "You do not have a permission to write \
						into file: %s\n", full_path);
		exit(1);
	}

	if (sh->used == 1) {
		if (sh->length > 1) {
			fprintf(fp, "\t%s %s[%d];\n", type_name(sh->type), 
						sh->name,
						sh->length);
		} else {
			fprintf(fp, "\t%s %s;\n", type_name(sh->type), 
						sh->name);
		}
	}

	free(full_path);
	fclose(fp);
	/* end of definig global variables */
}


void addLocalVariable(struct variable *sh, struct confnode* current_process_gen, struct modtab* current_module_gen) {
	/* local struct */
	char *full_path = get_sfc_path("", "local_data.h");
	FILE *fp = fopen(full_path, "a");

	if (fp == NULL) {
		fprintf(stderr, "You do not have a permission to write \
						into file: %s\n", full_path);
		exit(1);
	}

	if (sh->class_type == TYPE_VARIABLE_LOCAL) {
		if (sh->length > 1) {
			fprintf(fp, "\t%-10s %s_%s_%s[%d];\n", type_name(sh->type), 
						current_process_gen->name, current_module_gen->name, sh->name,
						sh->length);
		} else {
			fprintf(fp, "\t%-10s %s_%s_%s;\n", type_name(sh->type), 
						current_process_gen->name, current_module_gen->name, sh->name);
		}
	}

	free(full_path);
	fclose(fp);
	/* end of definig local variables */
}


void generateVariable(struct variable *sh, struct confnode* current_process_gen, struct modtab* current_module_gen) {
	if (generate_globals) {
		addGlobalVariable(sh);
	} else {
		addLocalVariable(sh, current_process_gen, current_module_gen);
	}

	setVariableValue(sh, current_process_gen, current_module_gen);
}	

void setVariableValue(struct variable *sh, struct confnode* current_process_gen, struct modtab* current_module_gen) {

	/* global variables init */
	char *full_path = get_sfc_path("", "fennec_data_values.h");
	FILE *fp = fopen(full_path, "a");

	if (fp == NULL) {
		fprintf(stderr, "You do not have a permission to write \
						into file: %s\n", full_path);
		exit(1);
	}

	if ((generate_globals && sh->used == 1)) {
		if (sh->length > 1) {
			fprintf(fp, "\t.%-50s = {%Lf},\t/* %d */\n", sh->name,
						sh->value, sh->offset);
		} else {
			fprintf(fp, "\t.%-50s = %Lf,\t/* %d */\n", sh->name,
						sh->value, sh->offset);
		}
	}

	if (sh->class_type == TYPE_VARIABLE_LOCAL) {
		if (sh->length > 1) {
			fprintf(fp, "\t.%s_%s_%-40s = {%Lf},\t/* %d */\n",
						current_process_gen->name, current_module_gen->name,
						sh->name, sh->value, sh->offset);
		} else {
			fprintf(fp, "\t.%s_%s_%-40s = %Lf,\t/* %d */\n",
						current_process_gen->name, current_module_gen->name,
						sh->name, sh->value, sh->offset);
		}
	}

	free(full_path);
	fclose(fp);
	/* end of initializing global variables */
}

void setProcessesLookupTable() {
	/* variable_lookup struct */
	char *full_path = get_sfc_path("", "variable_lookup.h");
	FILE *fp = fopen(full_path, "w");
	struct variables *mvar;
	int i;
	int vc;
	char *cap_name;

	if (fp == NULL) {
		fprintf(stderr, "You do not have a permission to write \
						into file: %s\n", full_path);
		exit(1);
	}

	fprintf(fp, "#ifndef _VARIABLE_LOOKUP_DATA_H_\n");
	fprintf(fp, "#define _VARIABLE_LOOKUP_DATA_H_\n\n");
	fprintf(fp, "#include <Fennec.h>\n\n");

	fprintf(fp, "struct variable_reference variable_lookup[%d] = {\n", number_of_variables_in_cache);


	for( i = 0; i < conf_id_counter; i++ ) {
		for (vc = 0, mvar = conftab[i].conf->app->variables; vc < conftab[i].conf->app_var_num && mvar != NULL; vc++) {
			if (mvar->var->class_type == TYPE_VARIABLE_GLOBAL) {
				cap_name = strdup(mvar->var->gname);
				cap_name = str_toupper(cap_name);
				fprintf(fp, "\t{ %-35s, &(fennec_global_data.%s), %s },\n",
						mvar->var->cap_name, mvar->var->gname,
						cap_name);
			} else {
				fprintf(fp, "\t{ %-35s, &(fennec_local_data.%s_%s_%s), UNKNOWN },\n",
						mvar->var->cap_name, conftab[i].conf->name,
						conftab[i].conf->app->name, mvar->var->name);
			}
			mvar = mvar->vars;
		}

		conftab[i].conf->app_var_offset = variable_cache;
		variable_cache += conftab[i].conf->app_var_num;

		for (vc = 0, mvar = conftab[i].conf->net->variables; vc < conftab[i].conf->net_var_num && mvar != NULL; vc++) {
			if (mvar->var->class_type == TYPE_VARIABLE_GLOBAL) {
				cap_name = strdup(mvar->var->gname);
				cap_name = str_toupper(cap_name);
				fprintf(fp, "\t{ %-35s, &(fennec_global_data.%s), %s },\n",
						mvar->var->cap_name, mvar->var->gname,
						cap_name);
			} else {
				fprintf(fp, "\t{ %-35s, &(fennec_local_data.%s_%s_%s), UNKNOWN },\n",
						mvar->var->cap_name, conftab[i].conf->name,
						conftab[i].conf->net->name, mvar->var->name);
			}
			mvar = mvar->vars;
		}

		conftab[i].conf->net_var_offset = variable_cache;
		variable_cache += conftab[i].conf->net_var_num;

		for (vc = 0, mvar = conftab[i].conf->am->variables; vc < conftab[i].conf->am_var_num && mvar != NULL; vc++) {
			if (mvar->var->class_type == TYPE_VARIABLE_GLOBAL) {
				cap_name = strdup(mvar->var->gname);
				cap_name = str_toupper(cap_name);
				fprintf(fp, "\t{ %-35s, &(fennec_global_data.%s), %s },\n",
						mvar->var->cap_name, mvar->var->gname,
						cap_name);
			} else {
				fprintf(fp, "\t{ %-35s, &(fennec_local_data.%s_%s_%s), UNKNOWN },\n",
						mvar->var->cap_name, conftab[i].conf->name,
						conftab[i].conf->am->name, mvar->var->name);
			}
			mvar = mvar->vars;
		}

		conftab[i].conf->am_var_offset = variable_cache;
		variable_cache += conftab[i].conf->am_var_num;

	}
	fprintf(fp, "};\n\n");
	fprintf(fp, "#endif\n\n");

	free(full_path);
	fclose(fp);
	/* end of adding variable lookup */
}



