#include "code_gen.h"
#include "utils.h"

void module_params_interface(struct modtab *mp) {
	char *full_path = get_sfc_path(mp->lib->full_name, "Params.nc");
	FILE *fp = fopen(full_path, "w");
	struct paramtype *pt;

	if (fp == NULL) {
		fprintf(stderr, "You do not have a permission to write \
						into file: %s\n", full_path);
		exit(1);
	}

	fprintf(fp, "interface %sParams {\n", (mp->lib->full_name));
	fprintf(fp, "\tevent void receive_status(uint16_t status_flag);\n");
	fprintf(fp, "\tcommand void send_status(uint16_t status_flag);\n");

        for(pt = mp->lib->params; pt != NULL; pt = pt->child ) {
                fprintf(fp, "\tcommand %s get_%s();\n", 
				type_name(pt->type), pt->name);
                fprintf(fp, "\tcommand error_t set_%s(%s new_%s);\n", 
				pt->name, type_name(pt->type), pt->name);
        }

	fprintf(fp, "}\n\n");

	fclose(fp);
	free(full_path);
}

void module_params_c(struct modtab *mp) {

	char *full_path = get_sfc_path(mp->lib->full_name, "ParamsC.nc");
	FILE *fp = fopen(full_path, "w");
	struct paramtype *pt;

	if (fp == NULL) {
		fprintf(stderr, "You do not have a permission to write \
						into file: %s\n", full_path);
		 exit(1);
	}

        fprintf(fp, "#include <Fennec.h>\n");
        fprintf(fp, "#include \"%sParams.h\"\n\n", mp->lib->full_name);
        fprintf(fp, "module %sParamsC {\n", mp->lib->full_name);
        fprintf(fp, "\t provides interface %sParams;\n", mp->lib->full_name);
        fprintf(fp, "}\n\n");

        fprintf(fp, "implementation {\n\n");
	fprintf(fp, "\tcommand void %sParams.send_status(uint16_t status_flag) {\n", 
							mp->lib->full_name);
        fprintf(fp, "\t}\n\n");

	for(pt = mp->lib->params; pt != NULL; pt = pt->child ) {
		fprintf(fp, "\tcommand %s %sParams.get_%s() {\n",
			type_name(pt->type), mp->lib->full_name, pt->name);
		fprintf(fp, "\t\treturn %s_data.%s;\n", mp->lib->full_name, pt->name);
		fprintf(fp, "\t}\n\n");
		fprintf(fp, "\tcommand error_t %sParams.set_%s(%s new_%s) {\n",
			mp->lib->full_name, pt->name, type_name(pt->type), pt->name);
		fprintf(fp, "\t\t%s_data.%s = new_%s;\n",
					mp->lib->full_name, pt->name, pt->name);
		fprintf(fp, "\t\treturn SUCCESS;\n");
		fprintf(fp, "\t}\n\n");
        }

        fprintf(fp, "}\n\n");

	fclose(fp);
	free(full_path);
}

void module_params_h(struct modtab *mp) {
	char *full_path = get_sfc_path(mp->lib->full_name, "Params.h");
	FILE *fp = fopen(full_path, "w");
	struct paramtype *pt;

	if (fp == NULL) {
		fprintf(stderr, "You do not have a permission to write \
						into file: %s\n", full_path);
		exit(1);
	}

	fprintf(fp, "#ifndef _FF_MODULE_%s_H_\n", mp->lib->full_name);
	fprintf(fp, "#define _FF_MODULE_%s_H_\n\n", mp->lib->full_name);

//	for(pt = mp->lib->params; pt != NULL; pt = pt->child) {
//        	fprintf(fp, "%s %s_%s;\n", type_name(pt->type), mp->lib->full_name, pt->name);
//	}
//	fprintf(fp, "\n");

	fprintf(fp, "struct %s_params {\n", mp->lib->full_name);

	for(pt = mp->lib->params; pt != NULL; pt = pt->child) {
		fprintf(fp, "\t%s %s;\n", type_name(pt->type), pt->name);
	}

	fprintf(fp, "};\n\n");

	fprintf(fp, "struct %s_params %s_data;\n", mp->lib->full_name, mp->lib->full_name);

	fprintf(fp, "#endif\n");

	fclose(fp);
	free(full_path);
}

void generateParams() {
	struct modtab *mp;
	for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
		if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->used == 1) {
			module_params_interface(mp);
			module_params_c(mp);
			module_params_h(mp);
		}
	}
}


