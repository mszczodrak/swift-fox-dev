#include "code_gen.h"
#include "utils.h"


void generateGlobals() {
	char *full_path = get_sfc_path("", "globals.h");
	FILE *fp = fopen(full_path, "w");
//	struct paramtype *pt;
//	int i;

	if (fp == NULL) {
		fprintf(stderr, "You do not have a permission to write \
						into file: %s\n", full_path);
		exit(1);
	}

	fprintf(fp, "#ifndef _FF_GLOBALS_H_\n");
	fprintf(fp, "#define _FF_GLOBALS_H_\n\n");

	fprintf(fp, "#endif\n");

	fclose(fp);
	free(full_path);
}



