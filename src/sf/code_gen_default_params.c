#include "code_gen.h"
#include "utils.h"

/*
 * creates ff_defaults.h file
 * the file stores default parameters for application module
 */

void generateDefaultParams() {
        char *full_path = get_sfc_path("", "ff_defaults.h");
        FILE *fp = fopen(full_path, "w");
	struct paramvalue *pv;
	struct modtab *mp;
	int i;

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
		fprintf(fp, "struct %s_params %s_%s = {\n",
        	        conftab[i].conf->app->lib->full_name, conftab[i].conf->id->name,
                	conftab[i].conf->app->lib->full_name);

                for (pv = conftab[i].conf->app_params; pv != NULL; ) {
                        fprintf(fp, "\t%s", pv->value->name);

                        pv = pv->child;
                        if (pv == NULL)
                                fprintf(fp, "\n");
                        else
                                fprintf(fp, ",\n");
                }
                fprintf(fp, "};\n");

                /* network default parameter values */
                fprintf(fp, "struct %s_params %s_%s = {\n",
                        conftab[i].conf->net->lib->full_name, conftab[i].conf->id->name,
                        conftab[i].conf->net->lib->full_name);

                for (pv = conftab[i].conf->net_params; pv != NULL; ) {
                        fprintf(fp, "\t%s", pv->value->name);

                        pv = pv->child;
                        if (pv == NULL)
                                fprintf(fp, "\n");
                        else
                                fprintf(fp, ",\n");
                }
                fprintf(fp, "};\n");

		/* mac default parameter values */
                fprintf(fp, "struct %s_params %s_%s = {\n",
                        conftab[i].conf->mac->lib->full_name, conftab[i].conf->id->name,
                        conftab[i].conf->mac->lib->full_name);

                for (pv = conftab[i].conf->mac_params; pv != NULL; ) {
                        fprintf(fp, "\t%s", pv->value->name);
                        
                        pv = pv->child;         
                        if (pv == NULL)
                                fprintf(fp, "\n");
                        else    
                                fprintf(fp, ",\n");
                }               
                fprintf(fp, "};\n");

		/* radio default parameter values */
                fprintf(fp, "struct %s_params %s_%s = {\n",
                        conftab[i].conf->radio->lib->full_name, conftab[i].conf->id->name,
                        conftab[i].conf->radio->lib->full_name);

                for (pv = conftab[i].conf->radio_params; pv != NULL; ) {
                        fprintf(fp, "\t%s", pv->value->name);
                                                
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
