#include "code_gen.h"

void generateDefaultParams() {

  FILE *fp_defparmsH = fopen(defparmsH, "w");
  struct paramvalue *pv;
  struct paramtype *pt;
  int i;
  int j;


  if (fp_defparmsH == NULL) {
    fprintf(stderr, "You do not have a permission to write into file: %s\n", defparmsH);
    exit(1);
  }

  fprintf(fp_defparmsH, "/* Swift Fox generated code for Fennec Fox defparms.h */\n");
  fprintf(fp_defparmsH, "#ifndef _FF_DEFPARMS_H_\n");
  fprintf(fp_defparmsH, "#define _FF_DEFPARMS_H_\n\n");
  fprintf(fp_defparmsH, "#include <Fennec.h>\n");
  fprintf(fp_defparmsH, "#include \"modules.h\"\n\n");

  /* generate structure with default parameters for each module of a given configuration */

  for( i = 1; i < conf_counter; i++ ) {

    /* application default parameter values */
    for (pv = conftab[i].conf->app_params, pt = conftab[i].conf->app->lib->params, j = 0;  
		pv != NULL; pv = pv->child, pt = pt->child, j++ ) {
      fprintf(fp_defparmsH, "%s %s_%s_var%d = %s;\n", pt->type_name, conftab[i].conf->id->name,
                		conftab[i].conf->app->lib->full_name, j, pv->value->name);
    }
    fprintf(fp_defparmsH, "\n"); 

    fprintf(fp_defparmsH, "struct %s_params %s_%s = {\n",
                conftab[i].conf->app->lib->full_name, conftab[i].conf->id->name,
                conftab[i].conf->app->lib->full_name);

    for (pv = conftab[i].conf->app_params, j = 0; pv != NULL; j++ ) {
      fprintf(fp_defparmsH, "\t&%s_%s_var%d", conftab[i].conf->id->name,
      			          conftab[i].conf->app->lib->full_name, j);

      pv = pv->child;
      if (pv == NULL)
        fprintf(fp_defparmsH, "\n");
      else
        fprintf(fp_defparmsH, ",\n");
    }
    fprintf(fp_defparmsH, "};\n");

    /* network default parameter values */
    for (pv = conftab[i].conf->net_params, pt = conftab[i].conf->net->lib->params, j = 0;
                pv != NULL; pv = pv->child, pt = pt->child, j++ ) {
      fprintf(fp_defparmsH, "%s %s_%s_var%d = %s;\n", pt->type_name, conftab[i].conf->id->name,
                                conftab[i].conf->net->lib->full_name, j, pv->value->name);
    }
    fprintf(fp_defparmsH, "\n");

    fprintf(fp_defparmsH, "struct %s_params %s_%s = {\n",
                conftab[i].conf->net->lib->full_name, conftab[i].conf->id->name,
                conftab[i].conf->net->lib->full_name);

    for (pv = conftab[i].conf->net_params, j = 0; pv != NULL; j++ ) {
      fprintf(fp_defparmsH, "\t&%s_%s_var%d", conftab[i].conf->id->name,
                                  conftab[i].conf->net->lib->full_name, j);

      pv = pv->child;
      if (pv == NULL)
        fprintf(fp_defparmsH, "\n");
      else
        fprintf(fp_defparmsH, ",\n");
    }
    fprintf(fp_defparmsH, "};\n");

    /* mac default parameter values */
    for (pv = conftab[i].conf->mac_params, pt = conftab[i].conf->mac->lib->params, j = 0;
                pv != NULL; pv = pv->child, pt = pt->child, j++ ) {
      fprintf(fp_defparmsH, "%s %s_%s_var%d = %s;\n", pt->type_name, conftab[i].conf->id->name,
                                conftab[i].conf->mac->lib->full_name, j, pv->value->name);
    }
    fprintf(fp_defparmsH, "\n");

    fprintf(fp_defparmsH, "struct %s_params %s_%s = {\n",
                conftab[i].conf->mac->lib->full_name, conftab[i].conf->id->name,
                conftab[i].conf->mac->lib->full_name);

    for (pv = conftab[i].conf->mac_params, j = 0; pv != NULL; j++ ) {
      fprintf(fp_defparmsH, "\t&%s_%s_var%d", conftab[i].conf->id->name,
                                  conftab[i].conf->mac->lib->full_name, j);

      pv = pv->child;
      if (pv == NULL)
        fprintf(fp_defparmsH, "\n");
      else
        fprintf(fp_defparmsH, ",\n");
    }
    fprintf(fp_defparmsH, "};\n");

    /* radio default parameter values */
    for (pv = conftab[i].conf->radio_params, pt = conftab[i].conf->radio->lib->params, j = 0;
                pv != NULL; pv = pv->child, pt = pt->child, j++ ) {
      fprintf(fp_defparmsH, "%s %s_%s_var%d = %s;\n", pt->type_name, conftab[i].conf->id->name,
                                conftab[i].conf->radio->lib->full_name, j, pv->value->name);
    }
    fprintf(fp_defparmsH, "\n");

    fprintf(fp_defparmsH, "struct %s_params %s_%s = {\n",
                conftab[i].conf->radio->lib->full_name, conftab[i].conf->id->name,
                conftab[i].conf->radio->lib->full_name);

    for (pv = conftab[i].conf->radio_params, j = 0; pv != NULL; j++ ) {
      fprintf(fp_defparmsH, "\t&%s_%s_var%d", conftab[i].conf->id->name,
                                  conftab[i].conf->radio->lib->full_name, j);

      pv = pv->child;
      if (pv == NULL)
        fprintf(fp_defparmsH, "\n");
      else
        fprintf(fp_defparmsH, ",\n");
    }
    fprintf(fp_defparmsH, "};\n");
  }

  fprintf(fp_defparmsH, "#endif\n\n");
  fclose(fp_defparmsH);

}
