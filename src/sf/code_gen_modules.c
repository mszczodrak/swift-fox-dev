#include "code_gen.h"
#include "utils.h"

void generateModules() {

/*
  struct modtab *mp;
  FILE *fp_modulesH = fopen(modulesH, "w");
  struct paramtype *pt;
  int i;

  if (fp_modulesH == NULL) {
    fprintf(stderr, "You do not have a permission to write into file: %s\n", modulesH);
    exit(1);
  }

  fprintf(fp_modulesH, "#ifndef _FF_MODULES_H_\n");
  fprintf(fp_modulesH, "#define _FF_MODULES_H_\n\n");
  

  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0) {

      for(pt = mp->lib->params, i = 0; pt != NULL; pt = pt->child, i++) {
        fprintf(fp_modulesH, "%s %s;\n", type_name(pt->type), pt->name);
      }

      fprintf(fp_modulesH, "\n");
      fprintf(fp_modulesH, "struct %s_params {\n", mp->lib->full_name);

      for(pt = mp->lib->params, i = 0; pt != NULL; pt = pt->child, i++) {
        fprintf(fp_modulesH, "\t%s *%s;\n", type_name(pt->type), pt->name);
      }

      fprintf(fp_modulesH, "};\n");
      fprintf(fp_modulesH, "struct %s_params %s_data = {\n", mp->lib->full_name, mp->lib->full_name);
      for(pt = mp->lib->params, i = 0; pt != NULL; pt = pt->child, i++) {
        fprintf(fp_modulesH, "\t&%s,\n", pt->name);
      }

      fprintf(fp_modulesH, "};\n\n");

    }
  }

  fprintf(fp_modulesH, "\n\n");
  fprintf(fp_modulesH, "void *modules_structs[%d] = {\n", module_id_counter);
  fprintf(fp_modulesH, "\tNULL");

  for(i = 0; i < module_id_counter; i++) {
    for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
      if (mp->lib != NULL && mp->lib->path && mp->id == i) {
        fprintf(fp_modulesH, ",\n\t&%s_data", mp->lib->full_name);
        break;
      }
    }
  }

  fprintf(fp_modulesH, "\n};\n\n");
  fprintf(fp_modulesH, "#endif\n");
*/
}


