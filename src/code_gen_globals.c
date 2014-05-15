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

void initDataStorageH() {
	char *full_path = get_sfc_path("", "data_storage.h");
	FILE *fp = fopen(full_path, "w");

	if (fp == NULL) {
		fprintf(stderr, "You do not have a permission to write \
						into file: %s\n", full_path);
		exit(1);
	}

	fprintf(fp, "#ifndef _FF_DATA_STORAGE_H_\n");
	fprintf(fp, "#define _FF_DATA_STORAGE_H_\n\n");
	fprintf(fp, "#include \"global_data.h\"\n");
	fprintf(fp, "#include \"local_data.h\"\n\n");

	fprintf(fp, "nx_struct data_storage {\n");
	fprintf(fp, "\tnx_struct global_data global;\n");
	fprintf(fp, "\tnx_struct local_data local;\n");
	fprintf(fp, "};\n\n");
	
	fprintf(fp, "#endif\n");

	free(full_path);
	fclose(fp);
}

void initDataStorageValues() {
	char *full_path = get_sfc_path("", "data_storage_values.h");
	FILE *fp = fopen(full_path, "w");

	if (fp == NULL) {
		fprintf(stderr, "You do not have a permission to write \
						into file: %s\n", full_path);
		exit(1);
	}

	fprintf(fp, "#ifndef _FF_DATA_STORAGE_VALUES_H_\n");
	fprintf(fp, "#define _FF_DATA_STORAGE_VALUES_H_\n\n");
	fprintf(fp, "#include \"data_storage.h\"\n\n");

	fprintf(fp, "nx_struct data_storage data {\n");
	fprintf(fp, "\t.global = {\n");
	
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

	fprintf(fp, "nx_struct global_data {\n");

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
	fprintf(fp, "#endif\n");

	free(full_path);
	fclose(fp);
	/* end of definig global variables */
}

void finishDataStorageValues() {
	/* global variables init */
	char *full_path = get_sfc_path("", "data_storage_values.h");
	FILE *fp = fopen(full_path, "a");

	if (fp == NULL) {
		fprintf(stderr, "You do not have a permission to write \
						into file: %s\n", full_path);
		exit(1);
	}

	fprintf(fp, "\t}\n");
	fprintf(fp, "};\n\n");
	fprintf(fp, "#endif\n");

	free(full_path);
	fclose(fp);
	/* end of initializing global variables */
}


void switchGlobalToLocalDataStorage() {
	/* global variables init */
	char *full_path = get_sfc_path("", "data_storage_values.h");
	FILE *fp = fopen(full_path, "a");

	if (fp == NULL) {
		fprintf(stderr, "You do not have a permission to write \
						into file: %s\n", full_path);
		exit(1);
	}

	fprintf(fp, "\t},\n");
	fprintf(fp, "\t.local = {\n");

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

	if (sh->length > 1) {
		fprintf(fp, "\tnx_%s %s[%d];\n", type_name(sh->type), 
						sh->name,
						sh->length);

	} else {
		fprintf(fp, "\tnx_%s %s;\n", type_name(sh->type), 
						sh->name);
	}


	free(full_path);
	fclose(fp);
	/* end of definig global variables */


	/* global variables init */
	full_path = get_sfc_path("", "data_storage_values.h");
	fp = fopen(full_path, "a");

	if (fp == NULL) {
		fprintf(stderr, "You do not have a permission to write \
						into file: %s\n", full_path);
		exit(1);
	}

	if (sh->length > 1) {
		fprintf(fp, "\t\t.%s = {%Lf},\n", sh->name,
						sh->value);

	} else {
		fprintf(fp, "\t\t.%s = %Lf,\n", sh->name,
						sh->value);
	}

	free(full_path);
	fclose(fp);
	/* end of initializing global variables */
}
