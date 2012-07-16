#include "code_gen.h"
#include "utils.h"

void generateCaches(int event_counter, int policy_counter) {

	FILE *tmp_confs = fopen(TEMP_CONF_FILE, "r");

	char *full_path = get_sfc_path("", "ff_caches.h");
	FILE *fp = fopen(full_path, "w");

	struct symtab *sp;
	struct modtab *mp;
	struct poltab *pp;
	int i;

	if (fp == NULL) {
		fprintf(stderr, "You do not have a permission to write \
					into file: %s\n", full_path);
		exit(1);
	}

	if (tmp_confs == NULL) {
		fprintf(stderr, "You do not have a permission to write \
					into file: %s\n", TEMP_CONF_FILE);
		exit(1);
	}

	fprintf(fp, "/* Swift Fox generated code for Fennec Fox caches.h */\n");
	fprintf(fp, "#ifndef __FF_CACHES_H__\n");
	fprintf(fp, "#define __FF_CACHES_H__\n\n");

	fprintf(fp, "#define NUMBER_OF_CONFIGURATIONS  %d\n", conf_counter);
	fprintf(fp, "#define INTERNAL_POLICY_CONFIGURATION_ID  %d\n\n", policy_conf_id);
	fprintf(fp, "#define NUMBER_OF_POLICIES  %d\n\n", policy_counter);
	fprintf(fp, "#include <Fennec.h>\n");
	fprintf(fp, "#include \"ff_defaults.h\"\n\n");

        for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
                if (mp->lib != NULL && mp->lib->path && mp->id > 0) {
                        fprintf(fp, "#include \"%sParams.h\"\n",
                                                mp->lib->full_name);
                }
        }
        fprintf(fp, "\n");


	fprintf(fp, "uint16_t active_state = %d;\n\n", active_state);
	fprintf(fp, "struct fennec_configuration configurations[NUMBER_OF_CONFIGURATIONS] = {\n");
	fprintf(fp, "\t{\n");
	fprintf(fp, "\t\t.application = 0,\n");
	fprintf(fp, "\t\t.network = 0,\n");
	fprintf(fp, "\t\t.mac = 0,\n");
	fprintf(fp, "\t\t.radio = 0,\n");
	fprintf(fp, "\t\t.level = 0\n");
	fprintf(fp, "\t}\n");

	/* generate code specifying each configuration's definition */

	for( i = 1; i < conf_counter; i++ ) {
		fprintf(fp, "\t,\n");
		fprintf(fp, "\t{\n");
    
		fprintf(fp, "\t\t.application = %d,\n", conftab[i].conf->app->id);
		fprintf(fp, "\t\t.network = %d,\n", conftab[i].conf->net->id);
		fprintf(fp, "\t\t.mac = %d,\n", conftab[i].conf->mac->id);
		fprintf(fp, "\t\t.radio = %d,\n", conftab[i].conf->radio->id);
		if (conftab[i].conf->level == UNKNOWN) {
			fprintf(fp, "\t\t.level = F_MINIMUM_STATE_LEVEL\n");
		} else {
			fprintf(fp, "\t\t.level = %d\n", conftab[i].conf->level);
		}
		fprintf(fp, "\t}\n");
	}

	fprintf(fp, "};\n\n");

	fprintf(fp, "struct default_params defaults[NUMBER_OF_CONFIGURATIONS] = {\n");
	fprintf(fp, "\t{\n");
	fprintf(fp, "\t\t.application_cache = NULL,\n");
	fprintf(fp, "\t\t.network_cache = NULL,\n");
	fprintf(fp, "\t\t.mac_cache = NULL,\n");
	fprintf(fp, "\t\t.radio_cache = NULL\n");
	fprintf(fp, "\t}\n");

	for( i = 1; i < conf_counter; i++ ) {
		fprintf(fp, "\t,\n");
		fprintf(fp, "\t{\n");
		fprintf(fp, "\t\t.application_cache = &%s_data,\n", 
					conftab[i].conf->app->lib->full_name);
		for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
			if (mp->lib != NULL && mp->lib->path && mp->id == conftab[i].conf->app->id) {
				fprintf(fp, "\t\t.application_default_params = &%s_%s,\n",
				conftab[i].conf->id->name, mp->lib->full_name);
				fprintf(fp, "\t\t.application_default_size = sizeof(struct %s_params),\n", 
						 	mp->lib->full_name);
				break;
			}
		}

		fprintf(fp, "\t\t.network_cache = &%s_data,\n", 
					conftab[i].conf->net->lib->full_name);
                for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
                        if (mp->lib != NULL && mp->lib->path && mp->id == conftab[i].conf->net->id) {
                                fprintf(fp, "\t\t.network_default_params = &%s_%s,\n",
                                conftab[i].conf->id->name, mp->lib->full_name);
                                fprintf(fp, "\t\t.network_default_size = sizeof(struct %s_params),\n",
                                                 	mp->lib->full_name);
                                break;
                        }
                }

		fprintf(fp, "\t\t.mac_cache = &%s_data,\n", 
					conftab[i].conf->mac->lib->full_name);
                for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
                        if (mp->lib != NULL && mp->lib->path && mp->id == conftab[i].conf->mac->id) {
                                fprintf(fp, "\t\t.mac_default_params = &%s_%s,\n",
                                conftab[i].conf->id->name, mp->lib->full_name);
                                fprintf(fp, "\t\t.mac_default_size = sizeof(struct %s_params),\n",
                                                 	mp->lib->full_name);
                                break;
                        }
                }

		fprintf(fp, "\t\t.radio_cache = &%s_data,\n", 
					conftab[i].conf->radio->lib->full_name);
                for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
                        if (mp->lib != NULL && mp->lib->path && mp->id == conftab[i].conf->radio->id) {
                                fprintf(fp, "\t\t.radio_default_params = &%s_%s,\n",
                                conftab[i].conf->id->name, mp->lib->full_name);
                                fprintf(fp, "\t\t.radio_default_size = sizeof(struct %s_params)\n",
                                	                 mp->lib->full_name);
                                break;
                        }
                }

		fprintf(fp, "\t}\n");
	}

	fprintf(fp, "};\n\n");

	fprintf(fp, "char* eventsScales[%d] = {\"\"", event_scale_counter);

	int event_scale_id = 1;

	for(event_scale_id = 1; event_scale_id < event_scale_counter; event_scale_id++) {
		for(sp = symtab; sp < &symtab[NSYMS]; sp++) {
			if (sp != NULL && sp->type != NULL && !strcmp(sp->type, "event_scale") && sp->value == event_scale_id) {
				fprintf(fp, ", \"%s\"", sp->name);
			}
		}
	}
	fprintf(fp, "};\n\n");


	fprintf(fp, "struct fennec_event eventsTable[%d] = {\n", event_counter);


	for ( i = 0; i < event_counter; ) {

		fprintf(fp, "\t{\n");
		fprintf(fp, "\t\t.operation = %s,\n", relopToLetter(evtab[i].op));
		fprintf(fp, "\t\t.value = %d,\n", evtab[i].value);

		if (evtab[i].scale == NULL) {
			fprintf(fp, "\t\t.scale = 0,\n");
		} else {
			fprintf(fp, "\t\t.scale = %d,\n", evtab[i].scale->value);
		}

		if (evtab[i].addr == UNKNOWN) {
			fprintf(fp, "\t\t.addr = TOS_NODE_ID,\n");
		} else {
			fprintf(fp, "\t\t.addr = %d\n", evtab[i].addr);
		}
		if (++i < event_counter) {
			fprintf(fp, "\t},\n");
		} else {
			fprintf(fp, "\t}\n");
		}
	}

/*
	struct evtab *ev;
	for(ev = evtab; ev < &evtab[NEVS]; ev++) {
		if (ev->name) {

			fprintf(fp, "\t}\n");

			fprintf(tmp_confs, "      eventsTable[%d].operation = %s;\n", 
							ev->num-1, relopToLetter(ev->op));
			fprintf(tmp_confs, "      eventsTable[%d].value = %d;\n", 
							ev->num-1, ev->value);

			if (ev->scale == NULL) {
				fprintf(tmp_confs, "      eventsTable[%d].scale = eventsScales[0];\n", 
							ev->num-1);
			} else {
				fprintf(tmp_confs, "      eventsTable[%d].scale = eventsScales[%d];\n", 
							ev->num-1, ev->scale->value);
			}

			if (ev->addr == UNKNOWN) {
				fprintf(tmp_confs, "      eventsTable[%d].addr = TOS_NODE_ID;\n\n", 
							ev->num-1);
			} else {
				fprintf(tmp_confs, "      eventsTable[%d].addr = %d;\n\n", 
							ev->num-1, ev->addr);
			}
			fprintf(fp, "\t{\n");
			fprintf(fp, "\t,\n");

		} else {
			break;
		}
	}
*/

	fprintf(fp, "};\n\n");

        fprintf(fp, "struct fennec_policy policies[%d] = {\n", policy_counter);
	for(i = 0; i < policy_counter; ) {
		pp = &poltab[i];
		if (pp->src_conf != NULL && pp->event_mask != NULL && 
							pp->dst_conf != NULL) {
			fprintf(fp, "\t{\n");
			fprintf(fp, "\t\t.src_conf = %d,\n", *pp->src_conf);
			fprintf(fp, "\t\t.event_mask = %d,\n", *pp->event_mask);
			fprintf(fp, "\t\t.dst_conf = %d\n\n", *pp->dst_conf);

			if (++i < policy_counter) {
				fprintf(fp, "\t},\n");
			} else {
				fprintf(fp, "\t}\n");
			}
		}
	}

	fprintf(fp, "};\n\n");

	fprintf(fp, "bool control_unit_support;\n\n");
	fprintf(fp, "nxle_uint16_t event_mask;\n\n");
	fprintf(fp, "#endif\n\n");

	fclose(fp);
	fclose(tmp_confs);
}


void generateConfiguration(struct confnode* c) {

	int conf_num = c->counter;

	if (c->app->lib->id == 0) {
		c->app->lib->used = 1;
	}
	conftab[conf_num].conf = c;

	if (c->net->lib->id == 0) {
		c->net->lib->used = 1;
	} 
	conftab[conf_num].conf = c;

	if (c->mac->lib->id == 0) {
		c->mac->lib->used = 1;
	} 
	conftab[conf_num].conf = c;

	if (c->radio->lib->id == 0) {
		c->radio->lib->used = 1;
	} 
	conftab[conf_num].conf = c;
//  }
//  if (c->level == UNKNOWN) {
//    conftab[conf_num].level = F_MINIMUM_STATE_LEVEL;
//    conftab[conf_num].level = 0;
//  } else {
//    conftab[conf_num].level = c->level;
//  }
}

void generateEvent() {

}

void generateInitial(struct initnode *i) {
	active_state = i->init;
}
