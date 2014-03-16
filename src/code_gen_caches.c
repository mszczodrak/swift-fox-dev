/*
 * Copyright (c) 2010-2014, Columbia University.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *  - Neither the name of the Columbia University nor the
 *    names of its contributors may be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL COLUMBIA UNIVERSITY BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
  * Swift Fox compiler
  *
  * @author: Marcin K Szczodrak
  */


#include "code_gen.h"
#include "utils.h"

/** Generates SF output file ff_caches.h.

\param event_counter number of events found in Swift Fox program
\param policy_counter number of policies found in Swift Fox program
*/


void define_modules() {
	char *full_path = get_sfc_path("", "ff_modules.h");
	FILE *fp = fopen(full_path, "w");
	int i;

	if (fp == NULL) {
		fprintf(stderr, "You do not have a permission to write \
					into file: %s\n", full_path);
		exit(1);
	}

	fprintf(fp, "/* Swift Fox generated code for Fennec Fox modules.h */\n");
	fprintf(fp, "#ifndef __FF_MODULES_H__\n");
	fprintf(fp, "#define __FF_MODULES_H__\n\n");

	for( i = 0; i < conf_id_counter; i++ ) {
		fprintf(fp, "/* %s for process %s\n"
				"Computation module located at %s */\n",
			conftab[i].conf->app->lib->name,
			conftab[i].conf->id->name,
			conftab[i].conf->app->lib->path);
		fprintf(fp, "#define %s\t%d\n\n",
			conftab[i].conf->app_id_name,
			conftab[i].conf->app_id_value);

		fprintf(fp, "/* %s for process %s\n"
				"Network module located at %s */\n",
			conftab[i].conf->net->lib->name,
			conftab[i].conf->id->name,
			conftab[i].conf->net->lib->path);
		fprintf(fp, "#define %s\t%d\n\n",
			conftab[i].conf->net_id_name,
			conftab[i].conf->net_id_value);

		fprintf(fp, "/* %s for process %s\n"
				"MAC module located at %s */\n",
			conftab[i].conf->mac->lib->name,
			conftab[i].conf->id->name,
			conftab[i].conf->mac->lib->path);
		fprintf(fp, "#define %s\t%d\n\n",
			conftab[i].conf->mac_id_name,
			conftab[i].conf->mac_id_value);

		fprintf(fp, "/* %s for process %s\n"
				"Radio module located at %s */\n",
			conftab[i].conf->radio->lib->name,
			conftab[i].conf->id->name,
			conftab[i].conf->radio->lib->path);
		fprintf(fp, "#define %s\t%d\n\n",
			conftab[i].conf->radio_id_name,
			conftab[i].conf->radio_id_value);

        }
        fprintf(fp, "\n");
	fprintf(fp, "#endif\n\n");
	fclose(fp);
}


void define_processes() {
	char *full_path = get_sfc_path("", "ff_processes.h");
	FILE *fp = fopen(full_path, "w");
	int i;

	if (fp == NULL) {
		fprintf(stderr, "You do not have a permission to write \
					into file: %s\n", full_path);
		exit(1);
	}

	fprintf(fp, "/* Swift Fox generated code for Fennec Fox ff_processes.h */\n");
	fprintf(fp, "#ifndef __FF_PROCESSES_H__\n");
	fprintf(fp, "#define __FF_PROCESSES_H__\n\n");

	fprintf(fp, "#define NUMBER_OF_PROCESSES\t\t%d\n\n", conf_id_counter);

	for( i = 0; i < conf_id_counter; i++ ) {
		fprintf(fp, "/* Process %s */\n",
			conftab[i].conf->id_name);
		fprintf(fp, "#define %s\t%d\n\n",
			conftab[i].conf->id_name,
			conftab[i].conf->counter);
	}

        fprintf(fp, "\n");

	/* Generate Proceses */

	fprintf(fp, "struct network_process processes[NUMBER_OF_PROCESSES] = {\n");

	/* generate code specifying each process's definition */

	for( i = 0; i < conf_id_counter; i++ ) {
		fprintf(fp, "\t{\n");
   		fprintf(fp, "\t\t/* %s */\n", conftab[i].conf->id->name); 
		fprintf(fp, "\t\t.process_id = %s, \t/* %d */\n",
				conftab[i].conf->id_name, conftab[i].conf->counter);
		fprintf(fp, "\t\t.application = %s,\n", conftab[i].conf->app_id_name);
		fprintf(fp, "\t\t.network = %s,\n", conftab[i].conf->net_id_name);
		fprintf(fp, "\t\t.mac = %s,\n", conftab[i].conf->mac_id_name);
		fprintf(fp, "\t\t.radio = %s\n", conftab[i].conf->radio_id_name);
		fprintf(fp, "\t}\n");
		if (i+1 < conf_id_counter) {
			fprintf(fp, "\t,\n");
		}
	}

	fprintf(fp, "};\n\n");
	fprintf(fp, "#endif\n\n");
	fclose(fp);
}


void define_states() {
	char *full_path = get_sfc_path("", "ff_states.h");
	FILE *fp = fopen(full_path, "w");
	struct conf_ids *conf_ptr;
	int i;

	if (fp == NULL) {
		fprintf(stderr, "You do not have a permission to write \
					into file: %s\n", full_path);
		exit(1);
	}

	fprintf(fp, "/* Swift Fox generated code for Fennec Fox ff_states.h */\n");
	fprintf(fp, "#ifndef __FF_STATES_H__\n");
	fprintf(fp, "#define __FF_STATES_H__\n\n");

	fprintf(fp, "#include \"ff_processes.h\"\n\n");
	fprintf(fp, "#define NUMBER_OF_STATES\t\t%d\n\n", state_id_counter);

	fprintf(fp, "state_t active_state = %d;\n\n", active_state);

	/* Generate States */

	for( i = 0; i < state_id_counter; i++ ) {
		fprintf(fp, "/* State %s */\n",
			conftab[i].conf->id->name);
		fprintf(fp, "#define %s\t%d\n\n",
			statetab[i].state->id_name,
			statetab[i].state->counter);
	}

	for( i = 0; i < state_id_counter; i++ ) {
		fprintf(fp, "process_t state_%s_processes[%d] = {\n", statetab[i].state->id->name, statetab[i].state->confs_counter);
		conf_ptr = statetab[i].state->confs;
		while (conf_ptr) { 
			if (conf_ptr->conf) {
				fprintf(fp, "\t%s", conf_ptr->conf->conf->id_name);
			}
			conf_ptr = conf_ptr->confs;
			if (conf_ptr != NULL) {
				fprintf(fp, ",\n");

			}
		}
		fprintf(fp, "\n\t};\n\n");
	}


	fprintf(fp, "struct state states[NUMBER_OF_STATES] = {\n");
	for( i = 0; i < state_id_counter; i++ ) {
                fprintf(fp, "\t{\n");
   		fprintf(fp, "\t\t/* %s */\n", statetab[i].state->id->name); 
                fprintf(fp, "\t\t.state_id = %s, /* %d */\n",
				statetab[i].state->id_name, statetab[i].state->counter);
                fprintf(fp, "\t\t.num_processes = %d,\n", statetab[i].state->confs_counter);
		fprintf(fp, "\t\t.process_list = state_%s_processes,\n", statetab[i].state->id->name);

		if (statetab[i].state->level == UNKNOWN) {
			fprintf(fp, "\t\t.level = F_MINIMUM_STATE_LEVEL\n");
		} else {
			fprintf(fp, "\t\t.level = %d\n", statetab[i].state->level);
		}


		fprintf(fp, "\t}\n");
		if (i+1 < state_id_counter) {
			fprintf(fp, "\t,\n");
		}

	}
	fprintf(fp, "};\n\n");

	fprintf(fp, "#endif\n\n");
	fclose(fp);
}


void generateCaches(int event_counter, int policy_counter) {

	char *full_path = get_sfc_path("", "ff_caches.h");
	FILE *fp = fopen(full_path, "w");

	struct modtab *mp;
	int i;

	define_modules();
	define_processes();
	define_states();

	if (fp == NULL) {
		fprintf(stderr, "You do not have a permission to write \
					into file: %s\n", full_path);
		exit(1);
	}

	fprintf(fp, "/* Swift Fox generated code for Fennec Fox caches.h */\n");
	fprintf(fp, "#ifndef __FF_CACHES_H__\n");
	fprintf(fp, "#define __FF_CACHES_H__\n\n");


	fprintf(fp, "#define NUMBER_OF_EVENTS\t\t%d\n", event_id_counter);
	fprintf(fp, "#define NUMBER_OF_POLICIES\t\t%d\n", policy_counter);
	fprintf(fp, "#include <Fennec.h>\n");
	fprintf(fp, "#include \"ff_defaults.h\"\n");
	fprintf(fp, "#include \"ff_modules.h\"\n");
	fprintf(fp, "#include \"ff_processes.h\"\n");
	fprintf(fp, "#include \"ff_states.h\"\n\n");

        for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
                if (mp->lib != NULL && mp->lib->path && mp->lib->used) {
                        fprintf(fp, "#include \"%sParams.h\"\n",
                                                mp->lib->name);
                }
        }
        fprintf(fp, "\n");




	/* module_t to event_id */
	fprintf(fp, "struct event_module_conf event_module_conf[NUMBER_OF_EVENTS] = {\n");
	fprintf(fp, "\t/* [event_id, module_id, conf_id */\n");
	for ( i = 0; i < conf_id_counter; i++ ) {
		if (conftab[i].conf->id->type == TYPE_PROCESS_EVENT) {
			fprintf(fp, "\t{%d, %d, %d},\n",
					conftab[i].conf->id->value,
					conftab[i].conf->app_id_value,
					conftab[i].conf->counter);
		}
	}

	fprintf(fp, "};\n\n");


        fprintf(fp, "struct fennec_policy policies[NUMBER_OF_POLICIES] = {\n");
	for(i = 0; i < policy_counter; ) {
		fprintf(fp, "\t{\n");
		fprintf(fp, "\t\t.src_conf = %d,\n", poltab[i].policy->from->value);
		fprintf(fp, "\t\t.event_mask = %d,\n", get_policy_mask(poltab[i].policy));
		fprintf(fp, "\t\t.dst_conf = %d\n\n", poltab[i].policy->to->value);

		if (++i < policy_counter) {
			fprintf(fp, "\t},\n");
		} else {
			fprintf(fp, "\t}\n");
		}
	}

	fprintf(fp, "};\n\n");

	fprintf(fp, "#endif\n\n");

	fclose(fp);
}

/** Marks the initial state.

\param i pointer to the initial state structure
*/
void generateInitial(struct initnode *i) {
	active_state = i->init;
}
