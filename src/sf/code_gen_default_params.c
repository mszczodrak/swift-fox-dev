#include "code_gen.h"
#include "utils.h"

void generateDefaultParams() {
        char *full_path = get_sfc_path("", "ff_defaults.h");
        FILE *fp = fopen(full_path, "w");
	struct paramvalue *pv;
	struct paramtype *pt;
	struct modtab *mp;
	int i;
	int j;

        if (fp == NULL) {
                fprintf(stderr, "You do not have a permission to write \
                                                into file: %s\n", full_path);
                exit(1);
        }

	fprintf(fp, "#ifndef _FF_DEFAULTS_H_\n");
	fprintf(fp, "#define _FF_DEFAULTS_H_\n\n");
	fprintf(fp, "#include <Fennec.h>\n");

	for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
		if (mp->lib != NULL && mp->lib->path && mp->id > 0) {
			fprintf(fp, "#include \"%sParams.h\"\n", 
						mp->lib->full_name);
		}
	}
	fprintf(fp, "\n");

	/* generate structure with default parameters for each module of a given configuration */

	for( i = 1; i < conf_counter; i++ ) {
	/* application default parameter values */
		for (pv = conftab[i].conf->app_params, 
			pt = conftab[i].conf->app->lib->params, j = 0;  pv != NULL; 
						pv = pv->child, pt = pt->child, j++ ) {

			if ((pv == NULL) ^ (pt == NULL)) {
				fprintf(stderr, "Error: Number of arguments does not match library definition for %s\n",
						conftab[i].conf->app->lib->name);
				exit(1);
			}

			fprintf(fp, "%s %s_%s_var%d = %s;\n", type_name(pt->type), 
			conftab[i].conf->id->name, conftab[i].conf->app->lib->full_name,
								j, pv->value->name);

			

		}
		fprintf(fp, "\n"); 

		fprintf(fp, "struct %s_params %s_%s = {\n",
        	        conftab[i].conf->app->lib->full_name, conftab[i].conf->id->name,
                	conftab[i].conf->app->lib->full_name);
	
		for (pv = conftab[i].conf->app_params, j = 0; pv != NULL; j++ ) {
			fprintf(fp, "\t&%s_%s_var%d", conftab[i].conf->id->name,
					conftab[i].conf->app->lib->full_name, j);
	
			pv = pv->child;
			if (pv == NULL)
				fprintf(fp, "\n");
			else
				fprintf(fp, ",\n");
			}
			fprintf(fp, "};\n");

		/* network default parameter values */
		for (pv = conftab[i].conf->net_params, 
			pt = conftab[i].conf->net->lib->params, j = 0; pv != NULL; 
						pv = pv->child, pt = pt->child, j++ ) {

                        if ((pv == NULL) ^ (pt == NULL)) {
                                fprintf(stderr, "Error: Number of arguments does not match library definition for %s\n",
                                                conftab[i].conf->net->lib->name);
                                exit(1);
                        }

			fprintf(fp, "%s %s_%s_var%d = %s;\n", type_name(pt->type), 
			conftab[i].conf->id->name, conftab[i].conf->net->lib->full_name,
								j, pv->value->name);
		}
		fprintf(fp, "\n");

		fprintf(fp, "struct %s_params %s_%s = {\n",
			conftab[i].conf->net->lib->full_name, conftab[i].conf->id->name,
			conftab[i].conf->net->lib->full_name);

		for (pv = conftab[i].conf->net_params, j = 0; pv != NULL; j++ ) {
			fprintf(fp, "\t&%s_%s_var%d", conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name, j);

			pv = pv->child;
			if (pv == NULL)
				fprintf(fp, "\n");
			else
				fprintf(fp, ",\n");
			}
			fprintf(fp, "};\n");

		/* mac default parameter values */
		for (pv = conftab[i].conf->mac_params, 
			pt = conftab[i].conf->mac->lib->params, j = 0; pv != NULL;
						pv = pv->child, pt = pt->child, j++ ) {
                        if ((pv == NULL) ^ (pt == NULL)) {
                                fprintf(stderr, "Error: Number of arguments does not match library definition for %s\n",
                                                conftab[i].conf->mac->lib->name);
                                exit(1);
                        }

			fprintf(fp, "%s %s_%s_var%d = %s;\n", type_name(pt->type),
			conftab[i].conf->id->name, conftab[i].conf->mac->lib->full_name,
								j, pv->value->name);
		}
		fprintf(fp, "\n");

		fprintf(fp, "struct %s_params %s_%s = {\n",
			conftab[i].conf->mac->lib->full_name, conftab[i].conf->id->name,
			conftab[i].conf->mac->lib->full_name);

		for (pv = conftab[i].conf->mac_params, j = 0; pv != NULL; j++ ) {
			fprintf(fp, "\t&%s_%s_var%d", conftab[i].conf->id->name,
				conftab[i].conf->mac->lib->full_name, j);

			pv = pv->child;
			if (pv == NULL)
				fprintf(fp, "\n");
			else
				fprintf(fp, ",\n");
		}
		fprintf(fp, "};\n");

		/* radio default parameter values */
		for (pv = conftab[i].conf->radio_params, 
			pt = conftab[i].conf->radio->lib->params, j = 0; pv != NULL;
						pv = pv->child, pt = pt->child, j++ ) {

                        if ((pv == NULL) ^ (pt == NULL)) {
                                fprintf(stderr, "Error: Number of arguments does not match library definition for %s\n",
                                                conftab[i].conf->radio->lib->name);
                                exit(1);
                        }

			fprintf(fp, "%s %s_%s_var%d = %s;\n", type_name(pt->type), 
			conftab[i].conf->id->name, 
			conftab[i].conf->radio->lib->full_name, j, pv->value->name);
		}
		fprintf(fp, "\n");

		fprintf(fp, "struct %s_params %s_%s = {\n",
			conftab[i].conf->radio->lib->full_name, conftab[i].conf->id->name,
			conftab[i].conf->radio->lib->full_name);

		for (pv = conftab[i].conf->radio_params, j = 0; pv != NULL; j++ ) {
			fprintf(fp, "\t&%s_%s_var%d", conftab[i].conf->id->name,
				conftab[i].conf->radio->lib->full_name, j);

			pv = pv->child;
			if (pv == NULL)
				fprintf(fp, "\n");
			else
				fprintf(fp, ",\n");
		}
		fprintf(fp, "};\n");
	}

	fprintf(fp, "#endif\n\n");
	fclose(fp);
	free(full_path);
}
