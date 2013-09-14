/** \file

    Swift Fox Compiler
    Copyright (C) 2009-2012 Marcin Szczodrak

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "code_gen.h"
#include "utils.h"

/** Generates SF output file ff_caches.h.

\param event_counter number of events found in Swift Fox program
\param policy_counter number of policies found in Swift Fox program
*/
void generateCaches(int event_counter, int policy_counter) {

	FILE *tmp_confs = fopen(TEMP_CONF_FILE, "r");

	char *full_path = get_sfc_path("", "ff_caches.h");
	FILE *fp = fopen(full_path, "w");

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

	fprintf(fp, "#define NUMBER_OF_CONFIGURATIONS  %d\n", conf_id_counter);
	fprintf(fp, "#define NUMBER_OF_STATES  %d\n", state_id_counter);
	fprintf(fp, "#define NUMBER_OF_POLICIES  %d\n", policy_counter);
	fprintf(fp, "#include <Fennec.h>\n");
	fprintf(fp, "#include \"ff_defaults.h\"\n\n");

        for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
                if (mp->lib != NULL && mp->lib->path && mp->id > 0) {
                        fprintf(fp, "#include \"%sParams.h\"\n",
                                                mp->lib->full_name);
                }
        }
        fprintf(fp, "\n");



	/* Generate Configurations */

	fprintf(fp, "uint16_t active_state = %d;\n\n", active_state);
	fprintf(fp, "struct fennec_configuration configurations[NUMBER_OF_CONFIGURATIONS] = {\n");
//	fprintf(fp, "\t{\n");
//	fprintf(fp, "\t\t.application = 0,\n");
//	fprintf(fp, "\t\t.network = 0,\n");
//	fprintf(fp, "\t\t.mac = 0,\n");
//	fprintf(fp, "\t\t.radio = 0,\n");
//	fprintf(fp, "\t\t.level = 0\n");
//	fprintf(fp, "\t}\n");

	/* generate code specifying each configuration's definition */

	for( i = 0; i < conf_id_counter; i++ ) {
		fprintf(fp, "\t{\n");
    
		fprintf(fp, "\t\t.conf_id = %d,\n", conftab[i].conf->counter);
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
		if (i+1 < conf_id_counter) {
			fprintf(fp, "\t,\n");
		}
	}

	fprintf(fp, "};\n\n");


	/* Generate States */

	struct conf_ids *conf_ptr;
	int confs_per_state = 0;

	fprintf(fp, "struct network_state states[NUMBER_OF_STATES] = {\n");

	for( i = 0; i < state_id_counter; i++ ) {
		confs_per_state = 0;
		fprintf(fp, "\t{\n");
		fprintf(fp, "\t\t.state_id = %d,\n", statetab[i].state->counter);
		conf_ptr = statetab[i].state->confs;
		while (conf_ptr) { 
			if (conf_ptr->conf) {
				
				fprintf(fp, "\t\t.conf_ids[%d] = %d,\n", 
					confs_per_state, conf_ptr->conf->conf->counter);
				confs_per_state++;
			}
			conf_ptr = conf_ptr->confs;
		}
		fprintf(fp, "\t\t.num_confs = %d\n", confs_per_state);

		fprintf(fp, "\t}\n");
		if (i+1 < state_id_counter) {
			fprintf(fp, "\t,\n");
		}

	}
	fprintf(fp, "};\n\n");



	fprintf(fp, "struct default_params defaults[NUMBER_OF_CONFIGURATIONS] = {\n");

	for( i = 1; i < conf_id_counter; i++ ) {
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
		if (i+1 < state_id_counter) {
			fprintf(fp, "\t,\n");
		}
	}

	fprintf(fp, "};\n\n");

	fprintf(fp, "struct fennec_event eventsTable[%d] = {\n", event_counter);

	for ( i = 0; i < event_counter; ) {

		fprintf(fp, "\t{\n");
		fprintf(fp, "\t\t.operation = %s,\n", relopToLetter(evtab[i].op));
		fprintf(fp, "\t\t.value = %d,\n", evtab[i].value);

		if (evtab[i].scale == NULL) {
			fprintf(fp, "\t\t.scale = TYPE_NODE,\n");
		} else {
			fprintf(fp, "\t\t.scale = %s,\n", evtab[i].scale->name);
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

/** Prepares SF configuration for the output. Each configuration's
module is marked as used and the configuration is added to the 
conftab list of all configurations.

\param c pointer to configuration structure
*/
void generateConfiguration(struct confnode* c) {

}

/** Marks the initial state.

\param i pointer to the initial state structure
*/
void generateInitial(struct initnode *i) {
	active_state = i->init;
}
