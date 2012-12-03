#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sf.h"
#include "code_gen.h"
#include "y.tab.h"
#include "utils.h"


char *fex = NULL;

FILE* tmp_confs = NULL;

void setFiles() {

  char *fennec_fox_lib = getenv("FENNEC_FOX_LIB");

  if (fennec_fox_lib == NULL) {
    fprintf(stderr, "\n\nFENNEC_FOX_LIB is not set!\n");
    exit(1);
  }

  char *p_fex = "support/sfc/fennec.extra";
  fex = malloc(strlen(p_fex)+strlen(fennec_fox_lib)+2);
  sprintf(fex, "%s/%s", fennec_fox_lib, p_fex);

  FILE *tmp = fopen(TEMP_CONF_FILE, "w");
  fclose(tmp);

}

void setFennecExtra() {

  FILE *fp_fe = fopen(fex, "w");

  if (fp_fe == NULL) {
    fprintf(stderr, "You do not have a permission to write into file: %s\n", fex);
    exit(1);
  }

  fprintf(fp_fe, "CFLAGS+=-I$(FENNEC_FOX_LIB)/interfaces\n");
  fprintf(fp_fe, "CFLAGS+=-I$(FENNEC_FOX_LIB)/system\n");
  fprintf(fp_fe, "CFLAGS+=-I$(FENNEC_FOX_LIB)/Fennec\n");
  fprintf(fp_fe, "CFLAGS+=-I$(FENNEC_FOX_LIB)/Fennec/sfc\n");
  fprintf(fp_fe, "CFLAGS+=-I$(FENNEC_FOX_LIB)/ControlUnit\n");
  fprintf(fp_fe, "CFLAGS+=-I$(FENNEC_FOX_LIB)/Events\n");
  fprintf(fp_fe, "include $(FENNEC_FOX_LIB)/sensors/sensors.extra\n");
  fprintf(fp_fe, "include $(FENNEC_FOX_LIB)/libs/libs.extra\n");

  struct modtab *mp;
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->conf != NULL && mp->conf->counter > 0) {
      fprintf(fp_fe, "CFLAGS+=-I%s\n", mp->lib->path);
    }
  }

  struct libtab *lp;
  for(lp = libtab; lp < &libtab[NSYMS]; lp++) {
    if (lp->path && lp->used == 1) {
      fprintf(fp_fe, "CFLAGS+=-I%s\n", lp->path);
    }
  }

  fclose(fp_fe);
}

void finishCodeGeneration(int policy_counter) {
  int conf_counter = 0;
  int event_counter = 0;
  struct symtab *sp;


  for(sp = symtab; sp < &symtab[NSYMS]; sp++) {
    if (sp->name && sp->type != NULL) {
      if (!strcmp(sp->type, "event_id")) {
        event_counter++;
      }
      if (!strcmp(sp->type, "configuration_id")) {
        conf_counter++;
      }
    }
  }


  /* check if sfc directory exists */
  if (create_dir("Fennec/sfc")) {
    fprintf(stderr, "Cannot create directory %s\n", "Fennec/sfc");
    exit(1);
  }

  generateCaches(event_counter, policy_counter);
  generateDefaultParams();

  generateFennecEngineC();
  generateEventC();

  generateFennecEngineP();
  generateEventP(event_counter);

  generateParams();
  generateGlobals();

  setFennecExtra();
}

