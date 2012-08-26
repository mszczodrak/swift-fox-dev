#include "code_gen.h"
#include "utils.h"


/* Generate Events */

void generateEventC() {

        char *full_path = get_sfc_path("", "EventsC.nc");
        FILE *fp = fopen(full_path, "w");

	struct symtab *sp;

        if (fp == NULL) {
                fprintf(stderr, "You do not have a permission to write into file: %s\n", 
									full_path);
                exit(1);
        }

	fprintf(fp, "\n#include <Fennec.h>\n\n");
	fprintf(fp, "configuration EventsC {\n");
	fprintf(fp, "  provides interface Mgmt;\n");
	fprintf(fp, "}\n\n");
	fprintf(fp, "implementation {\n\n");
	fprintf(fp, "  components EventsP;\n");
	fprintf(fp, "  Mgmt = EventsP;\n\n");
	fprintf(fp, "  components CachesC;\n");
	fprintf(fp, "  EventsP.EventCache -> CachesC;\n");
	fprintf(fp, "  /* Defined and linked event handlers */\n");

	for(sp = symtab; sp < &symtab[NSYMS]; sp++) {
		if (sp->name && sp->type != NULL && !strcmp(sp->type, "event_id")) {
			fprintf(fp, "\n  components new %sEventC() as %sEvent%dC;\n", 
					sp->lib->name, sp->lib->name, sp->value);
			fprintf(fp, "  EventsP.%sEvent%d -> %sEvent%dC;\n", 
					sp->lib->name, sp->value, sp->lib->name, 
									sp->value);
		}
	}

	fprintf(fp, "\n}\n");
	fclose(fp);
}

void generateEventP(int event_counter) {

        char *full_path = get_sfc_path("", "EventsP.nc");
        FILE *fp = fopen(full_path, "w");

	struct symtab *sp;

        if (fp == NULL) {
                fprintf(stderr, "You do not have a permission to write into file: %s\n", full_path);
                exit(1);
        }

	fprintf(fp, "\n#include <Fennec.h>\n\n");
	fprintf(fp, "module EventsP {\n\n");
	fprintf(fp, "  provides interface Mgmt;\n");
	fprintf(fp, "  uses interface EventCache;\n");

	for(sp = symtab; sp < &symtab[NSYMS]; sp++) {
		if (sp->name && sp->type != NULL && !strcmp(sp->type, "event_id")) {
			fprintf(fp, "  uses interface Event as %sEvent%d;\n", 
							sp->lib->name, sp->value);
		}
	}

	fprintf(fp, "\n}\n\n");
	fprintf(fp, "implementation {\n\n");
	fprintf(fp, "  void turnEvents(bool flag);\n");
	fprintf(fp, "  void setEvent(uint8_t ev_num, bool flag);\n\n");
	fprintf(fp, "  command error_t Mgmt.start() {\n");
	fprintf(fp, "    turnEvents(ON);\n");
	fprintf(fp, "    dbg(\"Events\", \"Events started\\n\");\n");
	fprintf(fp, "    signal Mgmt.startDone(SUCCESS);\n");
	fprintf(fp, "    return SUCCESS;\n");
	fprintf(fp, "  }\n\n");
	fprintf(fp, "  command error_t Mgmt.stop() {\n");
	fprintf(fp, "    turnEvents(OFF);\n");
	fprintf(fp, "    dbg(\"Events\", \"Events stopped\\n\");\n");
	fprintf(fp, "    signal Mgmt.stopDone(SUCCESS);\n");
	fprintf(fp, "    return SUCCESS;\n");
	fprintf(fp, "  }\n\n");
	fprintf(fp, "  void turnEvents(bool flag) {\n");
	fprintf(fp, "    uint8_t i;\n");
	fprintf(fp, "    for(i = 0 ; i < %d; i++ ) {\n", event_counter);
	fprintf(fp, "      if ( call EventCache.eventStatus(i)) {\n");
	fprintf(fp, "        setEvent(i + 1, flag);\n");
	fprintf(fp, "      }\n");
	fprintf(fp, "    }\n");
	fprintf(fp, "  }\n\n");
	fprintf(fp, "  void setEvent(uint8_t ev_num, bool flag) {\n\n");
	fprintf(fp, "    switch(ev_num) {\n\n");
	fprintf(fp, "      case 0:\n");
	fprintf(fp, "        break;\n\n");

	for(sp = symtab; sp < &symtab[NSYMS]; sp++) {
		if (sp->name && sp->type != NULL && !strcmp(sp->type, "event_id")) {
			fprintf(fp, "      case %d:\n", sp->value);
			fprintf(fp, "        flag ? call %sEvent%d.start(call EventCache.getEntry(%d)) : call %sEvent%d.stop();\n", 
				sp->lib->name, sp->value, sp->value, sp->lib->name, sp->value);
			fprintf(fp, "        break;\n\n");
		}
	}

	fprintf(fp, "      default:\n");
	fprintf(fp, "        dbg(\"Events\", \"Events: there is no event with number %s\\n\", ev_num);\n", "%d");
	fprintf(fp, "    }\n");
	fprintf(fp, "  }\n\n");

	for(sp = symtab; sp < &symtab[NSYMS]; sp++) {
		if (sp->name && sp->type != NULL && !strcmp(sp->type, "event_id")) {
			fprintf(fp, "  event void %sEvent%d.occured(bool oc) {\n", 
							sp->lib->name, sp->value);
			fprintf(fp, "    oc ? call EventCache.setBit(%d) : call EventCache.clearBit(%d);\n", 
							sp->value, sp->value);
			fprintf(fp, "  }\n\n");
		}
	}

	fprintf(fp, "\n}\n");
	fclose(fp);
}
