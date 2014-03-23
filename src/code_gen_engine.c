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

void generateFennecEngineC() {

	char *full_path = get_sfc_path("", "FennecEngineC.nc");
	FILE *fp = fopen(full_path, "w");
	int i;

	if (fp == NULL) {
		fprintf(stderr, "You do not have a permission to write into file: %s\n", full_path);
		exit(1);
	}

	fprintf(fp, "\n#include <Fennec.h>\n\n");
	fprintf(fp, "configuration FennecEngineC {\n");
	fprintf(fp, "provides interface ModuleCtrl;\n");
	fprintf(fp, "}\n\n");
	fprintf(fp, "implementation {\n\n");
	fprintf(fp, "components FennecEngineP;\n");
	fprintf(fp, "ModuleCtrl = FennecEngineP.ModuleCtrl;\n");

	fprintf(fp, "components LedsC;\n");
  	fprintf(fp, "FennecEngineP.Leds -> LedsC;\n\n");

	fprintf(fp, "components FennecC;\n");
  	fprintf(fp, "FennecEngineP.Fennec -> FennecC;\n\n");


	for( i = 0; i < conf_id_counter; i++ ) {
  		fprintf(fp, "/* Process %s */\n\n", 
					conftab[i].conf->id->name);
 		fprintf(fp, "components new %sC(%d) as %s_%s;\n",
					conftab[i].conf->app->lib->name,
					conftab[i].conf->counter,
					conftab[i].conf->id->name,
					conftab[i].conf->app->lib->name);
      		fprintf(fp, "FennecEngineP.%s_%s_Control -> %s_%s;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->app->lib->name,
					conftab[i].conf->id->name,
					conftab[i].conf->app->lib->name);
      		fprintf(fp, "FennecEngineP.%s_%s_Params <- %s_%s.%sParams;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->app->lib->name,
					conftab[i].conf->id->name,
					conftab[i].conf->app->lib->name, 
					conftab[i].conf->app->lib->name);

		fprintf(fp, "\n");

		fprintf(fp, "components new %sC(%d) as %s_%s;\n",
					conftab[i].conf->net->lib->name,
					conftab[i].conf->counter,
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->name);
      		fprintf(fp, "FennecEngineP.%s_%s_Control -> %s_%s;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->name,
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->name); 
      		fprintf(fp, "FennecEngineP.%s_%s_Params <- %s_%s.%sParams;\n", 
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->name, 
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->name, 
					conftab[i].conf->net->lib->name);

		fprintf(fp, "\n");

		fprintf(fp, "components %sC as %s_%s;\n",
					conftab[i].conf->mac->lib->name,
					//conftab[i].conf->counter,
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->name);
		fprintf(fp, "FennecEngineP.%s_%s_Control -> %s_%s;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->name,
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->name);
      		fprintf(fp, "FennecEngineP.%s_%s_Params <- %s_%s.%sParams;\n", 
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->name, 
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->name, 
					conftab[i].conf->mac->lib->name);

		fprintf(fp, "\n");

		if (conftab[i].conf->app->lib->type == TYPE_EVENT) {
			fprintf(fp, "%s_%s.Event -> FennecC.Event;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->app->lib->name);
		}

		fprintf(fp, "\n");

     		fprintf(fp, "%s_%s.NetworkAMSend -> %s_%s.NetworkAMSend;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->app->lib->name,
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->name);
      		fprintf(fp, "%s_%s.NetworkReceive -> %s_%s.NetworkReceive;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->app->lib->name,
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->name);
      		fprintf(fp, "%s_%s.NetworkSnoop -> %s_%s.NetworkSnoop;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->app->lib->name,
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->name);
      		fprintf(fp, "%s_%s.NetworkPacket -> %s_%s.NetworkPacket;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->app->lib->name,
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->name);
      		fprintf(fp, "%s_%s.NetworkAMPacket -> %s_%s.NetworkAMPacket;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->app->lib->name,
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->name);
      		fprintf(fp, "%s_%s.NetworkPacketAcknowledgements -> %s_%s.NetworkPacketAcknowledgements;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->app->lib->name, 
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->name);

		fprintf(fp, "\n");

      		fprintf(fp, "%s_%s.MacAMSend -> %s_%s.MacAMSend[%s];\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->name,
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->name,
					conftab[i].conf->id_name);
      		fprintf(fp, "%s_%s.MacReceive -> %s_%s.MacReceive[%s];\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->name, 
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->name,
					conftab[i].conf->id_name);
      		fprintf(fp, "%s_%s.MacSnoop -> %s_%s.MacSnoop[%s];\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->name,
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->name,
					conftab[i].conf->id_name);
      		fprintf(fp, "%s_%s.MacAMPacket -> %s_%s.MacAMPacket;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->name,
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->name);
      		fprintf(fp, "%s_%s.MacPacket -> %s_%s.MacPacket;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->name,
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->name);
      		fprintf(fp, "%s_%s.MacPacketAcknowledgements -> %s_%s.MacPacketAcknowledgements;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->name,
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->name);
      		fprintf(fp, "%s_%s.MacLinkPacketMetadata -> %s_%s.MacLinkPacketMetadata;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->name,
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->name);
		fprintf(fp, "\n");
	}

	fprintf(fp, "\n}\n");
	fclose(fp);
	free(full_path);
}

void generateFennecEngineP() {

        char *full_path = get_sfc_path("", "FennecEngineP.nc");
        FILE *fp = fopen(full_path, "w");
	int i;

        if (fp == NULL) {
                fprintf(stderr, "You do not have a permission to write into file: %s\n", full_path);
                exit(1);
        }

	fprintf(fp, "/* Swift Fox generated code for Fennec Fox Computation module */\n");
  	fprintf(fp, "#include <Fennec.h>\n");
  	fprintf(fp, "module FennecEngineP {\n\n");
  	fprintf(fp, "provides interface ModuleCtrl;\n");

  	fprintf(fp, "uses interface Leds;\n");
  	fprintf(fp, "uses interface Fennec;\n\n");

	for( i = 0; i < conf_id_counter; i++ ) {
    		fprintf(fp, "/* Process %s with id: %d  */\n",
					conftab[i].conf->id->name,
					conftab[i].conf->counter);
    		fprintf(fp, "/* Application Module %s */\n",
					conftab[i].conf->app->lib->name);
      		fprintf(fp, "uses interface SplitControl as %s_%s_Control;\n", 
					conftab[i].conf->id->name,
					conftab[i].conf->app->lib->name);
      		fprintf(fp, "provides interface %sParams as %s_%s_Params;\n", 
					conftab[i].conf->app->lib->name,
					conftab[i].conf->id->name,
					conftab[i].conf->app->lib->name);
    		fprintf(fp, "/* Network Module %s */\n",
					conftab[i].conf->net->lib->name);
		fprintf(fp, "uses interface SplitControl as %s_%s_Control;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->name);
      		fprintf(fp, "provides interface %sParams as %s_%s_Params;\n", 
					conftab[i].conf->net->lib->name,
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->name);

    		fprintf(fp, "/* MAC Module %s */\n",
					conftab[i].conf->mac->lib->name);
		fprintf(fp, "uses interface SplitControl as %s_%s_Control;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->name);
      		fprintf(fp, "provides interface %sParams as %s_%s_Params;\n", 
					conftab[i].conf->mac->lib->name,
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->name);
		fprintf(fp, "\n\n");
	}

	fprintf(fp,"}\n\n");
	fprintf(fp,"implementation {\n\n");

	fprintf(fp,"void module_startDone(module_t module_id, error_t error) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"[-] FennecEngine module_startDone(%%d, %%d)\", module_id, error);\n");
	fprintf(fp,"\tsignal ModuleCtrl.startDone(module_id, error);\n");
	fprintf(fp,"}\n\n");

	fprintf(fp,"void module_stopDone(module_t module_id, error_t error) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"[-] FennecEngine module_stopDone(%%d, %%d)\", module_id, error);\n");
	fprintf(fp,"\tsignal ModuleCtrl.stopDone(module_id, error);\n");
	fprintf(fp,"}\n\n");

	fprintf(fp,"command error_t ModuleCtrl.start(module_t module_id) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"[-] FennecEngine ModuleCtrl.start(%%d)\", module_id);\n");
	fprintf(fp,"\tswitch(module_id) {\n\n");

	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase %s:\n", conftab[i].conf->app_id_name);
		fprintf(fp, "\t\tdbg(\"FennecEngine\", \"[-] FennecEngine call %s_%s_Control.start()\");\n",
					conftab[i].conf->id->name,
					conftab[i].conf->app->lib->name);
		fprintf(fp, "\t\treturn call %s_%s_Control.start();\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->app->lib->name);

                fprintf(fp, "\tcase %s:\n", conftab[i].conf->net_id_name);
		fprintf(fp, "\t\tdbg(\"FennecEngine\", \"[-] FennecEngine call %s_%s_Control.start()\");\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->name);
		fprintf(fp, "\t\treturn call %s_%s_Control.start();\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->name);

                fprintf(fp, "\tcase %s:\n", conftab[i].conf->mac_id_name);
		fprintf(fp, "\t\tdbg(\"FennecEngine\", \"[-] FennecEngine call %s_%s_Control.start()\");\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->name);
		fprintf(fp, "\t\treturn call %s_%s_Control.start();\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->name);
	}
	fprintf(fp,"\t}\n");
	fprintf(fp,"\treturn FAIL;\n");
	fprintf(fp,"}\n\n");

	fprintf(fp,"command error_t ModuleCtrl.stop(module_t module_id) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"[-] FennecEngine ModuleCtrl.stop(%%d)\", module_id);\n");

	fprintf(fp,"\tswitch(module_id) {\n\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase %s:\n", conftab[i].conf->app_id_name);
		fprintf(fp, "\t\tdbg(\"FennecEngine\", \"[-] FennecEngine call %s_%s_Control.stop()\");\n",
					conftab[i].conf->id->name,
					conftab[i].conf->app->lib->name);
		fprintf(fp, "\t\treturn call %s_%s_Control.stop();\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->app->lib->name);

                fprintf(fp, "\tcase %s:\n", conftab[i].conf->net_id_name);
		fprintf(fp, "\t\tdbg(\"FennecEngine\", \"[-] FennecEngine call %s_%s_Control.stop()\");\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->name);
		fprintf(fp, "\t\treturn call %s_%s_Control.stop();\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->name);

                fprintf(fp, "\tcase %s:\n", conftab[i].conf->mac_id_name);
		fprintf(fp, "\t\tdbg(\"FennecEngine\", \"[-] FennecEngine call %s_%s_Control.stop()\");\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->name);
		fprintf(fp, "\t\treturn call %s_%s_Control.stop();\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->name);
	}
	fprintf(fp,"\t}\n");
	fprintf(fp,"\treturn FAIL;\n");
	fprintf(fp,"}\n\n");

	struct paramtype *pt;

	/* Interfaces with Computations */

	for( i = 0; i < conf_id_counter; i++ ) {

		fprintf(fp, "\n/* Linking Computation %s */\n",
					conftab[i].conf->app->lib->name);

		fprintf(fp, "\t/* Module Control Interface */\n\n");	

		fprintf(fp, "event void %s_%s_Control.startDone(error_t err){\n", 
					conftab[i].conf->id->name,
					conftab[i].conf->app->lib->name);
		fprintf(fp, "\tmodule_startDone(%s, err);\n",
					conftab[i].conf->app_id_name);
		fprintf(fp, "}\n\n");
		fprintf(fp, "event void %s_%s_Control.stopDone(error_t err) {\n",
					conftab[i].conf->id->name,
					conftab[i].conf->app->lib->name);
		fprintf(fp, "\tmodule_stopDone(%s, err);\n",
					conftab[i].conf->app_id_name);
		fprintf(fp, "}\n\n");

		fprintf(fp, "\t/* Parameter Interface */\n\n");	

		/* check if the interface is empty, if it is add dummy call */
		if (conftab[i].conf->app->lib->params == NULL) {
			fprintf(fp, "command void %s_%s_Params.dummy() {}\n",
					conftab[i].conf->id->name,
					conftab[i].conf->app->lib->name);
		}

		for(pt = conftab[i].conf->app->lib->params; pt != NULL; pt = pt->child ) {
			fprintf(fp, "command %s %s_%s_Params.get_%s() {\n",
					type_name(pt->type), 
					conftab[i].conf->id->name,
					conftab[i].conf->app->lib->name, 
					pt->name);
			fprintf(fp, "\treturn *(%s_ptr.%s);\n",
					conftab[i].conf->app_id_name,
					pt->name);
			fprintf(fp, "}\n\n");

			fprintf(fp, "command error_t %s_%s_Params.set_%s(%s new_%s) {\n",
					conftab[i].conf->id->name,
					conftab[i].conf->app->lib->name, 
					pt->name, 
					type_name(pt->type), 
					pt->name);
			fprintf(fp, "\t*(%s_ptr.%s) = new_%s;\n", 
					conftab[i].conf->app_id_name,
					pt->name,
					pt->name);
			fprintf(fp, "\treturn SUCCESS;\n");
	                fprintf(fp, "}\n\n");
	        }

		fprintf(fp, "event void %s_%s_Control.startDone(error_t err) {\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->name);
		fprintf(fp, "\tmodule_startDone(%s, err);\n",
					conftab[i].conf->net_id_name);
		fprintf(fp, "}\n\n");
		fprintf(fp, "event void %s_%s_Control.stopDone(error_t err) {\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->name);
		fprintf(fp, "\tmodule_stopDone(%s, err);\n",
					conftab[i].conf->net_id_name);
		fprintf(fp, "}\n\n");


		fprintf(fp, "\t/* Parameter Interfaces */\n\n");	

		/* check if the interface is empty, if it is add dummy call */
		if (conftab[i].conf->net->lib->params == NULL) {
			fprintf(fp, "command void %s_%s_Params.dummy() {}\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->name);
		}

		for(pt = conftab[i].conf->net->lib->params; pt != NULL; pt = pt->child ) {
			fprintf(fp, "command %s %s_%s_Params.get_%s() {\n",
					type_name(pt->type), 
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->name, 
					pt->name);
			fprintf(fp, "\treturn *(%s_ptr.%s);\n",
					conftab[i].conf->net_id_name,
					pt->name);
			fprintf(fp, "}\n\n");
			fprintf(fp, "command error_t %s_%s_Params.set_%s(%s new_%s) {\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->name, 
					pt->name, 
					type_name(pt->type), 
					pt->name);
			fprintf(fp, "\t*(%s_ptr.%s) = new_%s;\n", 
					conftab[i].conf->net_id_name,
					pt->name,
					pt->name);
			fprintf(fp, "\treturn SUCCESS;\n");
	                fprintf(fp, "}\n\n");
	        }


/* Interfaces with Macs */

		fprintf(fp, "event void %s_%s_Control.startDone(error_t err) {\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->name);
		fprintf(fp, "\tmodule_startDone(%s, err);\n",
					conftab[i].conf->mac_id_name);
		fprintf(fp, "}\n\n");
		fprintf(fp, "event void %s_%s_Control.stopDone(error_t err) {\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->name);
		fprintf(fp, "\tmodule_stopDone(%s, err);\n",
					conftab[i].conf->mac_id_name);
		fprintf(fp, "}\n\n");


		fprintf(fp, "\t/* Parameter Interfaces */\n\n");	

		/* check if the interface is empty, if it is add dummy call */
		if (conftab[i].conf->mac->lib->params == NULL) {
			fprintf(fp, "command void %s_%s_Params.dummy() {}\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->name);
		}

		for(pt = conftab[i].conf->mac->lib->params; pt != NULL; pt = pt->child ) {
			fprintf(fp, "command %s %s_%s_Params.get_%s() {\n",
					type_name(pt->type), 
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->name, 
					pt->name);
			fprintf(fp, "\treturn *(%s_ptr.%s);\n",
					conftab[i].conf->mac_id_name,
					pt->name);
			fprintf(fp, "}\n\n");
			fprintf(fp, "command error_t %s_%s_Params.set_%s(%s new_%s) {\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->name, 
					pt->name, 
					type_name(pt->type), 
					pt->name);
			fprintf(fp, "\t*(%s_ptr.%s) = new_%s;\n", 
					conftab[i].conf->mac_id_name,
					pt->name,
					pt->name);
			fprintf(fp, "\treturn SUCCESS;\n");
	                fprintf(fp, "}\n\n");
	        }
	}

	fprintf(fp, "\n}\n");
	fclose(fp);
	free(full_path);
}

