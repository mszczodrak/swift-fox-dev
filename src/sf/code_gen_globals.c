#include "code_gen.h"
#include "utils.h"

void generateGlobals() {

  char *globals = "hello";
  struct modtab *mp;
  FILE *fp_globalsH = fopen(globalsH, "w");
  struct paramtype *pt;
  int i;

  if (fp_globalsH == NULL) {
    fprintf(stderr, "You do not have a permission to write into file: %s\n", globalsH);
    exit(1);
  }

  fprintf(fp_globalsH, "/* Swift Fox generated code for Fennec Fox globals.h */\n\n");
  fprintf(fp_globalsH, "#ifndef _FF_MODULES_H_\n");
  fprintf(fp_globalsH, "#define _FF_MODULES_H_\n\n");
  

  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0) {
      fprintf(fp_globalsH, "/* %s */\n", mp->lib->full_name);

      for(pt = mp->lib->params, i = 0; pt != NULL; pt = pt->child, i++) {
        fprintf(fp_globalsH, "%s %s;\n", type_name(pt->type), pt->name);
      }

      fprintf(fp_globalsH, "\n");
      fprintf(fp_globalsH, "struct %s_params {\n", mp->lib->full_name);

      for(pt = mp->lib->params, i = 0; pt != NULL; pt = pt->child, i++) {
        fprintf(fp_globalsH, "\t%s *%s;\n", type_name(pt->type), pt->name);
      }

      fprintf(fp_globalsH, "};\n");
      fprintf(fp_globalsH, "struct %s_params %s_data = {\n", mp->lib->full_name, mp->lib->full_name);
      for(pt = mp->lib->params, i = 0; pt != NULL; pt = pt->child, i++) {
        fprintf(fp_globalsH, "\t&%s,\n", pt->name);
      }

      fprintf(fp_globalsH, "};\n\n");

    }
  }

  fprintf(fp_globalsH, "\n\n");
  fprintf(fp_globalsH, "void *globals_structs[%d] = {\n", module_id_counter);
  fprintf(fp_globalsH, "\tNULL");

  for(i = 0; i < module_id_counter; i++) {
    for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
      if (mp->lib != NULL && mp->lib->path && mp->id == i) {
        fprintf(fp_globalsH, ",\n\t&%s_data", mp->lib->full_name);
        break;
      }
    }
  }

  fprintf(fp_globalsH, "\n};\n\n");
  fprintf(fp_globalsH, "#endif\n");

}


