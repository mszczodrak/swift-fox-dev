#include "code_gen.h"
#include "utils.h"

void module_params_interface(struct modtab *mp) {
	char *full_path = get_sfc_path(mp->lib->full_name, "Params.nc");
	FILE *fp = fopen(full_path, "w");

	if (fp == NULL) {
		fprintf(stderr, "You do not have a permission to write \
						into file: %s\n", full_path);
		exit(1);
	}

	fclose(fp);
	free(full_path);
}

void module_params_c(struct modtab *mp) {

	char *full_path = get_sfc_path(mp->lib->full_name, "ParamsC.nc");
	FILE *fp = fopen(full_path, "w");

	if (fp == NULL) {
		fprintf(stderr, "You do not have a permission to write \
						into file: %s\n", full_path);
		 exit(1);
	}


	fclose(fp);
	free(full_path);
}

void module_params_h(struct modtab *mp) {
	char *full_path = get_sfc_path(mp->lib->full_name, "Params.h");
	FILE *fp = fopen(full_path, "w");
	struct paramtype *pt;
	int i;

	if (fp == NULL) {
		fprintf(stderr, "You do not have a permission to write \
						into file: %s\n", full_path);
		exit(1);
	}

	fprintf(fp, "#ifndef _FF_MODULE_%s_H_\n", mp->lib->full_name);
	fprintf(fp, "#define _FF_MODULE_%s_H_\n\n", mp->lib->full_name);

	for(pt = mp->lib->params, i = 0; pt != NULL; pt = pt->child, i++) {
        	fprintf(fp, "%s %s;\n", type_name(pt->type), pt->name);
	}

	fprintf(fp, "\n");

	fprintf(fp, "struct %s_params {\n", mp->lib->full_name);

	for(pt = mp->lib->params, i = 0; pt != NULL; pt = pt->child, i++) {
		fprintf(fp, "\t%s *%s;\n", type_name(pt->type), pt->name);
	}

	fprintf(fp, "};\n\n");

	fprintf(fp, "struct %s_params %s_data = {\n", mp->lib->full_name, mp->lib->full_name);
	for(pt = mp->lib->params, i = 0; pt != NULL; pt = pt->child, i++) {
		fprintf(fp, "\t&%s,\n", pt->name);
	}
	fprintf(fp, "};\n\n");

	fprintf(fp, "#endif\n");

	fclose(fp);
	free(full_path);
}

void generateParams() {
	struct modtab *mp;
	for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
		if (mp->lib != NULL && mp->lib->path && mp->id > 0) {
			module_params_interface(mp);
			module_params_c(mp);
			module_params_h(mp);
		}
	}
}


