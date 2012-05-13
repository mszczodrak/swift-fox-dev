/* Swift Fox Compiler v0.3
 * Authors: Marcin Szczodrak
 * Date: May 27, 2010
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sf.h"
#include "code_gen.h"
#include "y.tab.h"
#include "utils.h"

char *engineC = NULL;
char *engineM = NULL;

char *eventC = NULL;
char *eventM = NULL;

char *modulesH = NULL;
char *cachesH = NULL;
char *defparmsH = NULL;

char *fex = NULL;

FILE* tmp_confs = NULL;
int policy_conf_id = -1;

void setFiles() {

  char *fennec_fox_lib = getenv("FENNEC_FOX_LIB");

  if (fennec_fox_lib == NULL) {
    fprintf(stderr, "\n\nFENNEC_FOX_LIB is not set!\n");
    exit(1);
  }

  char *p_engineC = "Fennec/FennecEngineC.nc";		
  char *p_engineM = "Fennec/FennecEngineP.nc";		
  engineC = malloc(strlen(p_engineC)+strlen(fennec_fox_lib)+2);
  sprintf(engineC, "%s/%s", fennec_fox_lib, p_engineC);
  engineM = malloc(strlen(p_engineM)+strlen(fennec_fox_lib)+2);
  sprintf(engineM, "%s/%s", fennec_fox_lib, p_engineM);

  char *p_eventC = "Events/EventsC.nc";
  char *p_eventM = "Events/EventsP.nc";
  eventC = malloc(strlen(p_eventC)+strlen(fennec_fox_lib)+2);
  sprintf(eventC, "%s/%s", fennec_fox_lib, p_eventC);
  eventM = malloc(strlen(p_eventM)+strlen(fennec_fox_lib)+2);
  sprintf(eventM, "%s/%s", fennec_fox_lib, p_eventM);

  char *p_cachesH = "Fennec/caches.h";
  cachesH = malloc(strlen(p_cachesH)+strlen(fennec_fox_lib)+2);
  sprintf(cachesH, "%s/%s", fennec_fox_lib, p_cachesH);
	
  char *p_modulesH = "Fennec/modules.h";
  modulesH = malloc(strlen(p_modulesH)+strlen(fennec_fox_lib)+2);
  sprintf(modulesH, "%s/%s", fennec_fox_lib, p_modulesH);

  char *p_defparmsH = "Fennec/defparms.h";
  defparmsH = malloc(strlen(p_defparmsH)+strlen(fennec_fox_lib)+2);
  sprintf(defparmsH, "%s/%s", fennec_fox_lib, p_defparmsH);

  char *p_fex = "support/sfc/fennec.extra";
  fex = malloc(strlen(p_fex)+strlen(fennec_fox_lib)+2);
  sprintf(fex, "%s/%s", fennec_fox_lib, p_fex);

  FILE *tmp = fopen(TEMP_CONF_FILE, "w");
  fclose(tmp);

  /* check if sfc directory exists */
  create_dir("Fennec/sfc");

}

void setFennecExtra() {

  FILE *fp_fe = fopen(fex, "w");

  if (fp_fe == NULL) {
    fprintf(stderr, "You do not have a permission to write into file: %s\n", fex);
    exit(1);
  }

  fprintf(fp_fe, "CFLAGS+=-I$(FENNEC_FOX_LIB)/interfaces\n");
  //fprintf(fp_fe, "CFLAGS+=-I$(FENNEC_FOX_LIB)/chips\n");
  fprintf(fp_fe, "CFLAGS+=-I$(FENNEC_FOX_LIB)/system\n");
  fprintf(fp_fe, "CFLAGS+=-I$(FENNEC_FOX_LIB)/Fennec\n");
  fprintf(fp_fe, "CFLAGS+=-I$(FENNEC_FOX_LIB)/ControlUnit\n");
  fprintf(fp_fe, "CFLAGS+=-I$(FENNEC_FOX_LIB)/Events\n");
  fprintf(fp_fe, "include $(FENNEC_FOX_LIB)/Sensors/sensors.extra\n");
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


  generateCaches(event_counter, policy_counter);
  generateModules();
  generateDefaultParams();

  generateFennecEngineC();
  generateEventC();

  generateFennecEngineP();
  generateEventP(event_counter);

  generateParams();
//  generateGlobals();

  setFennecExtra();
}

/* Generate Events */

void generateEventC() {

  struct symtab *sp;
  FILE *fp_eventC = fopen(eventC, "w");

  if (fp_eventC == NULL) {
    fprintf(stderr, "You do not have a permission to write into file: %s\n", eventC);
    exit(1);
  }

  fprintf(fp_eventC, "/* Swift Fox generated code for Fennec Fox Event configuration */\n");
  fprintf(fp_eventC, "\n#include <Fennec.h>\n\n");
  fprintf(fp_eventC, "configuration EventsC {\n");
  fprintf(fp_eventC, "  provides interface Mgmt;\n");
  fprintf(fp_eventC, "}\n\n");
  fprintf(fp_eventC, "implementation {\n\n");
  fprintf(fp_eventC, "  components EventsP;\n");
  fprintf(fp_eventC, "  Mgmt = EventsP;\n\n");
  fprintf(fp_eventC, "  components CachesC;\n");
  fprintf(fp_eventC, "  EventsP.EventCache -> CachesC;\n");
  fprintf(fp_eventC, "  /* Defined and linked event handlers */\n");

  for(sp = symtab; sp < &symtab[NSYMS]; sp++) {
    if (sp->name && sp->type != NULL && !strcmp(sp->type, "event_id")) {
      fprintf(fp_eventC, "\n  components new %sEventC() as %sEvent%dC;\n", sp->lib->name, sp->lib->name, sp->value);
      fprintf(fp_eventC, "  EventsP.%sEvent%d -> %sEvent%dC;\n", sp->lib->name, sp->value, sp->lib->name, sp->value);
    }
  }

  fprintf(fp_eventC, "\n}\n");
  fclose(fp_eventC);
}

void generateEventP(int event_counter) {

  struct symtab *sp;
  FILE *fp_eventM = fopen(eventM, "w");

  if (fp_eventM == NULL) {
    fprintf(stderr, "You do not have a permission to write into file: %s\n", eventM);
    exit(1);
  }

  fprintf(fp_eventM, "/* Swift Fox generated code for Fennec Fox Event module */\n");
  fprintf(fp_eventM, "\n#include <Fennec.h>\n\n");
  fprintf(fp_eventM, "module EventsP {\n\n");
  fprintf(fp_eventM, "  provides interface Mgmt;\n");
  fprintf(fp_eventM, "  uses interface EventCache;\n");

  for(sp = symtab; sp < &symtab[NSYMS]; sp++) {
    if (sp->name && sp->type != NULL && !strcmp(sp->type, "event_id")) {
      fprintf(fp_eventM, "  uses interface Event as %sEvent%d;\n", sp->lib->name, sp->value);
    }
  }

  fprintf(fp_eventM, "\n}\n\n");
  fprintf(fp_eventM, "implementation {\n\n");
  fprintf(fp_eventM, "  void turnEvents(bool flag);\n");
  fprintf(fp_eventM, "  void setEvent(uint8_t ev_num, bool flag);\n\n");
  fprintf(fp_eventM, "  command error_t Mgmt.start() {\n");
  fprintf(fp_eventM, "    turnEvents(ON);\n");
  fprintf(fp_eventM, "    dbg(\"Events\", \"Events started\\n\");\n");
  fprintf(fp_eventM, "    signal Mgmt.startDone(SUCCESS);\n");
  fprintf(fp_eventM, "    return SUCCESS;\n");
  fprintf(fp_eventM, "  }\n\n");
  fprintf(fp_eventM, "  command error_t Mgmt.stop() {\n");
  fprintf(fp_eventM, "    turnEvents(OFF);\n");
  fprintf(fp_eventM, "    dbg(\"Events\", \"Events stopped\\n\");\n");
  fprintf(fp_eventM, "    signal Mgmt.stopDone(SUCCESS);\n");
  fprintf(fp_eventM, "    return SUCCESS;\n");
  fprintf(fp_eventM, "  }\n\n");
  fprintf(fp_eventM, "  void turnEvents(bool flag) {\n");
  fprintf(fp_eventM, "    uint8_t i;\n");
  fprintf(fp_eventM, "    for(i = 0 ; i < %d; i++ ) {\n", event_counter);
  fprintf(fp_eventM, "      if ( call EventCache.eventStatus(i)) {\n");
  fprintf(fp_eventM, "        setEvent(i + 1, flag);\n");
  fprintf(fp_eventM, "      }\n");
  fprintf(fp_eventM, "    }\n");
  fprintf(fp_eventM, "  }\n\n");
  fprintf(fp_eventM, "  void setEvent(uint8_t ev_num, bool flag) {\n\n");
  fprintf(fp_eventM, "    switch(ev_num) {\n\n");
  fprintf(fp_eventM, "      case 0:\n");
  fprintf(fp_eventM, "        break;\n\n");

  for(sp = symtab; sp < &symtab[NSYMS]; sp++) {
    if (sp->name && sp->type != NULL && !strcmp(sp->type, "event_id")) {
      fprintf(fp_eventM, "      case %d:\n", sp->value);
      fprintf(fp_eventM, "        flag ? call %sEvent%d.start(call EventCache.getEntry(%d)) : call %sEvent%d.stop();\n", sp->lib->name, sp->value, sp->value, sp->lib->name, sp->value);
      fprintf(fp_eventM, "        break;\n\n");
    }
  }

  fprintf(fp_eventM, "      default:\n");
  fprintf(fp_eventM, "        dbg(\"Events\", \"Events: there is no event with number %s\\n\", ev_num);\n", "%d");
  fprintf(fp_eventM, "    }\n");
  fprintf(fp_eventM, "  }\n\n");

  for(sp = symtab; sp < &symtab[NSYMS]; sp++) {
    if (sp->name && sp->type != NULL && !strcmp(sp->type, "event_id")) {
      fprintf(fp_eventM, "  event void %sEvent%d.occured(bool oc) {\n", sp->lib->name, sp->value);
      fprintf(fp_eventM, "    oc ? call EventCache.setBit(%d) : call EventCache.clearBit(%d);\n", sp->value, sp->value);
      fprintf(fp_eventM, "  }\n\n");
    }
  }

  fprintf(fp_eventM, "\n}\n");
  fclose(fp_eventM);
}

char *relopToLetter(int i) {
  switch(i) {
    case LT:
      return "LT";
    case GT:
      return "GT";
    case LE:
      return "LE";
    case GE:
      return "GE";
    case NE:
      return "NE";
    case EQ:
      return "EQ";
    default:
      fprintf(stderr, "Unknown RELOP operator\n");
      exit(1);
    }
}
