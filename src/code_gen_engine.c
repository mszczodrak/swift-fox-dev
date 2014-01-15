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

	fprintf(fp, "components CachesC;\n");
  	fprintf(fp, "FennecEngineP.Fennec -> CachesC;\n\n");


	for( i = 0; i < conf_id_counter; i++ ) {
  		fprintf(fp, "/* Defined and linked application module %s with %s state */\n\n", 
					conftab[i].conf->app->lib->full_name,
					conftab[i].conf->id->name);
 		fprintf(fp, "components %sC as %s_%s;\n",
					conftab[i].conf->app->lib->full_name,
					conftab[i].conf->id->name,
					conftab[i].conf->app->lib->full_name);
      		fprintf(fp, "FennecEngineP.%s_%s_Control -> %s_%s;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->app->lib->full_name,
					conftab[i].conf->id->name,
					conftab[i].conf->app->lib->full_name);
      		fprintf(fp, "FennecEngineP.%s_%s_Params <- %s_%s.%sParams;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->app->lib->full_name,
					conftab[i].conf->id->name,
					conftab[i].conf->app->lib->full_name, 
					conftab[i].conf->app->lib->full_name);
     		fprintf(fp, "FennecEngineP.%s_%s_NetworkAMSend <- %s_%s.NetworkAMSend;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->app->lib->full_name,
					conftab[i].conf->id->name,
					conftab[i].conf->app->lib->full_name);
      		fprintf(fp, "FennecEngineP.%s_%s_NetworkReceive <- %s_%s.NetworkReceive;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->app->lib->full_name,
					conftab[i].conf->id->name,
					conftab[i].conf->app->lib->full_name);
      		fprintf(fp, "FennecEngineP.%s_%s_NetworkSnoop <- %s_%s.NetworkSnoop;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->app->lib->full_name,
					conftab[i].conf->id->name,
					conftab[i].conf->app->lib->full_name);
      		fprintf(fp, "FennecEngineP.%s_%s_NetworkPacket <- %s_%s.NetworkPacket;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->app->lib->full_name,
					conftab[i].conf->id->name,
					conftab[i].conf->app->lib->full_name);
      		fprintf(fp, "FennecEngineP.%s_%s_NetworkAMPacket <- %s_%s.NetworkAMPacket;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->app->lib->full_name,
					conftab[i].conf->id->name,
					conftab[i].conf->app->lib->full_name);
      		fprintf(fp, "FennecEngineP.%s_%s_NetworkPacketAcknowledgements <- %s_%s.NetworkPacketAcknowledgements;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->app->lib->full_name, 
					conftab[i].conf->id->name,
					conftab[i].conf->app->lib->full_name);
		if (conftab[i].conf->app->lib->type == TYPE_EVENT) {
			fprintf(fp, "FennecEngineP.%s_%s_Event -> %s_%s.Event;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->app->lib->full_name,
					conftab[i].conf->id->name,
					conftab[i].conf->app->lib->full_name);
		}
		fprintf(fp, "\n\n");

  		fprintf(fp, "/* Defined and linked network module %s with %s state */\n\n", 
					conftab[i].conf->net->lib->full_name,
					conftab[i].conf->id->name);
		fprintf(fp, "components %sC as %s_%s;\n",
					conftab[i].conf->net->lib->full_name,
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name);
      		fprintf(fp, "FennecEngineP.%s_%s_Control -> %s_%s;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name,
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name); 
      		fprintf(fp, "FennecEngineP.%s_%s_Params <- %s_%s.%sParams;\n", 
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name, 
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name, 
					conftab[i].conf->net->lib->full_name);
      		fprintf(fp, "FennecEngineP.%s_%s_NetworkAMSend -> %s_%s.NetworkAMSend;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name, 
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name);
      		fprintf(fp, "FennecEngineP.%s_%s_NetworkReceive -> %s_%s.NetworkReceive;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name,
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name);
      		fprintf(fp, "FennecEngineP.%s_%s_NetworkSnoop -> %s_%s.NetworkSnoop;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name,
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name);
      		fprintf(fp, "FennecEngineP.%s_%s_NetworkAMPacket -> %s_%s.NetworkAMPacket;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name,
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name);
      		fprintf(fp, "FennecEngineP.%s_%s_NetworkPacket -> %s_%s.NetworkPacket;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name,
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name);
      		fprintf(fp, "FennecEngineP.%s_%s_NetworkPacketAcknowledgements -> %s_%s.NetworkPacketAcknowledgements;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name,
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name);
      		fprintf(fp, "FennecEngineP.%s_%s_MacAMSend <- %s_%s.MacAMSend;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name,
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name);
      		fprintf(fp, "FennecEngineP.%s_%s_MacReceive <- %s_%s.MacReceive;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name, 
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name);
      		fprintf(fp, "FennecEngineP.%s_%s_MacSnoop <- %s_%s.MacSnoop;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name,
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name);
      		fprintf(fp, "FennecEngineP.%s_%s_MacAMPacket <- %s_%s.MacAMPacket;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name,
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name);
      		fprintf(fp, "FennecEngineP.%s_%s_MacPacket <- %s_%s.MacPacket;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name,
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name);
      		fprintf(fp, "FennecEngineP.%s_%s_MacPacketAcknowledgements <- %s_%s.MacPacketAcknowledgements;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name,
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name);
      		fprintf(fp, "FennecEngineP.%s_%s_MacLinkPacketMetadata <- %s_%s.MacLinkPacketMetadata;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name,
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name);

		fprintf(fp, "\n\n");

  		fprintf(fp, "/* Defined and linked MAC module %s with %s state */\n\n", 
					conftab[i].conf->mac->lib->full_name,
					conftab[i].conf->id->name);
		fprintf(fp, "components %sC as %s_%s;\n",
					conftab[i].conf->mac->lib->full_name,
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
		fprintf(fp, "FennecEngineP.%s_%s_Control -> %s_%s;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name,
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
      		fprintf(fp, "FennecEngineP.%s_%s_Params <- %s_%s.%sParams;\n", 
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name, 
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name, 
					conftab[i].conf->mac->lib->full_name);
		fprintf(fp, "FennecEngineP.%s_%s_MacAMSend -> %s_%s.MacAMSend;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name,
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
		fprintf(fp, "FennecEngineP.%s_%s_MacReceive -> %s_%s.MacReceive;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name,
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
		fprintf(fp, "FennecEngineP.%s_%s_MacSnoop -> %s_%s.MacSnoop;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name,
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
		fprintf(fp, "FennecEngineP.%s_%s_MacPacket -> %s_%s.MacPacket;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name,
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
		fprintf(fp, "FennecEngineP.%s_%s_MacAMPacket -> %s_%s.MacAMPacket;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name,
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
		fprintf(fp, "FennecEngineP.%s_%s_MacPacketAcknowledgements -> %s_%s.MacPacketAcknowledgements;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name,
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
		fprintf(fp, "FennecEngineP.%s_%s_MacLinkPacketMetadata -> %s_%s.MacLinkPacketMetadata;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name,
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
		fprintf(fp, "FennecEngineP.%s_%s_RadioReceive <- %s_%s.RadioReceive;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name,
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
		fprintf(fp, "FennecEngineP.%s_%s_RadioResource <- %s_%s.RadioResource;\n", 
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name, 
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
		fprintf(fp, "FennecEngineP.%s_%s_RadioBuffer <- %s_%s.RadioBuffer;\n", 
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name, 
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
		fprintf(fp, "FennecEngineP.%s_%s_RadioSend <- %s_%s.RadioSend;\n", 
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name, 
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
		fprintf(fp, "FennecEngineP.%s_%s_RadioPacket <- %s_%s.RadioPacket;\n", 
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name, 
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
		fprintf(fp, "FennecEngineP.%s_%s_PacketTransmitPower <- %s_%s.PacketTransmitPower;\n", 
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name, 
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
		fprintf(fp, "FennecEngineP.%s_%s_PacketRSSI <- %s_%s.PacketRSSI;\n", 
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name, 
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
		fprintf(fp, "FennecEngineP.%s_%s_PacketTimeSync <- %s_%s.PacketTimeSync;\n", 
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name, 
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
		fprintf(fp, "FennecEngineP.%s_%s_PacketLinkQuality <- %s_%s.PacketLinkQuality;\n", 
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name, 
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
		fprintf(fp, "FennecEngineP.%s_%s_RadioCCA <- %s_%s.RadioCCA;\n", 
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name, 
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
		fprintf(fp, "FennecEngineP.%s_%s_RadioState <- %s_%s.RadioState;\n", 
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name, 
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
		fprintf(fp, "FennecEngineP.%s_%s_RadioLinkPacketMetadata <- %s_%s.RadioLinkPacketMetadata;\n", 
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name, 
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
		fprintf(fp, "\n\n");
		
  		fprintf(fp, "/* Defined and linked radio module %s with %s state */\n\n", 
					conftab[i].conf->radio->lib->full_name,
					conftab[i].conf->id->name);
		fprintf(fp, "components %sC as %s_%s;\n", 
					conftab[i].conf->radio->lib->full_name, 
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name);
		fprintf(fp, "FennecEngineP.%s_%s_Control -> %s_%s;\n", 
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name, 
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name);
      		fprintf(fp, "FennecEngineP.%s_%s_Params <- %s_%s.%sParams;\n", 
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name, 
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name, 
					conftab[i].conf->radio->lib->full_name);
		fprintf(fp, "FennecEngineP.%s_%s_RadioReceive -> %s_%s.RadioReceive;\n", 
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name, 
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name);
		fprintf(fp, "FennecEngineP.%s_%s_RadioResource -> %s_%s.RadioResource;\n", 
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name, 
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name);
		fprintf(fp, "FennecEngineP.%s_%s_RadioBuffer -> %s_%s.RadioBuffer;\n", 
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name, 
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name);
		fprintf(fp, "FennecEngineP.%s_%s_RadioSend -> %s_%s.RadioSend;\n", 
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name, 
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name);
		fprintf(fp, "FennecEngineP.%s_%s_RadioPacket -> %s_%s.RadioPacket;\n", 
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name, 
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name);
		fprintf(fp, "FennecEngineP.%s_%s_PacketTransmitPower -> %s_%s.PacketTransmitPower;\n", 
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name, 
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name);
		fprintf(fp, "FennecEngineP.%s_%s_PacketRSSI -> %s_%s.PacketRSSI;\n", 
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name, 
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name);
		fprintf(fp, "FennecEngineP.%s_%s_PacketTimeSync -> %s_%s.PacketTimeSync;\n", 
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name, 
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name);
		fprintf(fp, "FennecEngineP.%s_%s_PacketLinkQuality -> %s_%s.PacketLinkQuality;\n", 
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name, 
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name);
		fprintf(fp, "FennecEngineP.%s_%s_RadioCCA -> %s_%s.RadioCCA;\n", 
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name, 
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name);
		fprintf(fp, "FennecEngineP.%s_%s_RadioState -> %s_%s.RadioState;\n", 
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name, 
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name);
		fprintf(fp, "FennecEngineP.%s_%s_RadioLinkPacketMetadata -> %s_%s.RadioLinkPacketMetadata;\n", 
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name, 
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name);
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

        struct modtab *mp;

        if (fp == NULL) {
                fprintf(stderr, "You do not have a permission to write into file: %s\n", full_path);
                exit(1);
        }

	fprintf(fp, "/* Swift Fox generated code for Fennec Fox Application module */\n");
  	fprintf(fp, "#include <Fennec.h>\n");
  	fprintf(fp, "module FennecEngineP {\n\n");
  	fprintf(fp, "provides interface ModuleCtrl;\n");

  	fprintf(fp, "uses interface Leds;\n");
  	fprintf(fp, "uses interface Fennec;\n");

  	fprintf(fp, "\n\t/* Application Modules */\n\n");

	for( i = 0; i < conf_id_counter; i++ ) {
    		fprintf(fp, "/* Application Module %s with %s process */\n",
					conftab[i].conf->app->lib->full_name,
					conftab[i].conf->id->name);
      		fprintf(fp, "uses interface SplitControl as %s_%s_Control;\n", 
					conftab[i].conf->id->name,
					conftab[i].conf->app->lib->full_name);
      		fprintf(fp, "provides interface %sParams as %s_%s_Params;\n", 
					conftab[i].conf->app->lib->full_name,
					conftab[i].conf->id->name,
					conftab[i].conf->app->lib->full_name);
		fprintf(fp, "provides interface AMSend as %s_%s_NetworkAMSend;\n", 
					conftab[i].conf->id->name,
					conftab[i].conf->app->lib->full_name);
		fprintf(fp, "provides interface Receive as %s_%s_NetworkReceive;\n", 
					conftab[i].conf->id->name,
					conftab[i].conf->app->lib->full_name);
		fprintf(fp, "provides interface Receive as %s_%s_NetworkSnoop;\n", 
					conftab[i].conf->id->name,
					conftab[i].conf->app->lib->full_name);
		fprintf(fp, "provides interface Packet as %s_%s_NetworkPacket;\n", 
					conftab[i].conf->id->name,
					conftab[i].conf->app->lib->full_name);
		fprintf(fp, "provides interface AMPacket as %s_%s_NetworkAMPacket;\n", 
					conftab[i].conf->id->name,
					conftab[i].conf->app->lib->full_name);
		fprintf(fp, "provides interface PacketAcknowledgements as %s_%s_NetworkPacketAcknowledgements;\n", 
					conftab[i].conf->id->name,
					conftab[i].conf->app->lib->full_name);
		if (conftab[i].conf->app->lib->type == TYPE_EVENT) {
			fprintf(fp, "uses interface Event as %s_%s_Event;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->app->lib->full_name);
		}
		fprintf(fp, "\n\n");

    		fprintf(fp, "/* Network Module %s with %s process */\n",
					conftab[i].conf->net->lib->full_name,
					conftab[i].conf->id->name);
		fprintf(fp, "uses interface SplitControl as %s_%s_Control;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name);
      		fprintf(fp, "provides interface %sParams as %s_%s_Params;\n", 
					conftab[i].conf->net->lib->full_name,
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name);
		fprintf(fp, "uses interface AMSend as %s_%s_NetworkAMSend;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name);
		fprintf(fp, "uses interface Receive as %s_%s_NetworkReceive;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name);
		fprintf(fp, "uses interface Receive as %s_%s_NetworkSnoop;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name);
		fprintf(fp, "uses interface AMPacket as %s_%s_NetworkAMPacket;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name);
		fprintf(fp, "uses interface Packet as %s_%s_NetworkPacket;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name);
		fprintf(fp, "uses interface PacketAcknowledgements as %s_%s_NetworkPacketAcknowledgements;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name);
		fprintf(fp, "provides interface AMSend as %s_%s_MacAMSend;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name);
		fprintf(fp, "provides interface Receive as %s_%s_MacReceive;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name);
		fprintf(fp, "provides interface Receive as %s_%s_MacSnoop;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name);
		fprintf(fp, "provides interface Packet as %s_%s_MacPacket;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name);
		fprintf(fp, "provides interface AMPacket as %s_%s_MacAMPacket;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name);
		fprintf(fp, "provides interface PacketAcknowledgements as %s_%s_MacPacketAcknowledgements;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name);
		fprintf(fp, "provides interface LinkPacketMetadata as %s_%s_MacLinkPacketMetadata;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name);
		fprintf(fp, "\n\n");

    		fprintf(fp, "/* MAC Module %s with %s process */\n",
					conftab[i].conf->mac->lib->full_name,
					conftab[i].conf->id->name);
		fprintf(fp, "uses interface SplitControl as %s_%s_Control;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
      		fprintf(fp, "provides interface %sParams as %s_%s_Params;\n", 
					conftab[i].conf->mac->lib->full_name,
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
		fprintf(fp, "uses interface AMSend as %s_%s_MacAMSend;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
		fprintf(fp, "uses interface Receive as %s_%s_MacReceive;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
		fprintf(fp, "uses interface Receive as %s_%s_MacSnoop;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
		fprintf(fp, "uses interface Packet as %s_%s_MacPacket;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
		fprintf(fp, "uses interface AMPacket as %s_%s_MacAMPacket;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
		fprintf(fp, "uses interface PacketAcknowledgements as %s_%s_MacPacketAcknowledgements;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
		fprintf(fp, "uses interface LinkPacketMetadata as %s_%s_MacLinkPacketMetadata;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
		fprintf(fp, "provides interface RadioReceive as %s_%s_RadioReceive;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
		fprintf(fp, "provides interface Resource as %s_%s_RadioResource;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
		fprintf(fp, "provides interface RadioBuffer as %s_%s_RadioBuffer;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
		fprintf(fp, "provides interface RadioSend as %s_%s_RadioSend;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
		fprintf(fp, "provides interface RadioPacket as %s_%s_RadioPacket;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
		fprintf(fp, "provides interface RadioCCA as %s_%s_RadioCCA;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
		fprintf(fp, "provides interface PacketField<uint8_t> as %s_%s_PacketTransmitPower;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
		fprintf(fp, "provides interface PacketField<uint8_t> as %s_%s_PacketRSSI;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
		fprintf(fp, "provides interface PacketField<uint32_t> as %s_%s_PacketTimeSync;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
		fprintf(fp, "provides interface PacketField<uint8_t> as %s_%s_PacketLinkQuality;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
		fprintf(fp, "provides interface RadioState as %s_%s_RadioState;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
		fprintf(fp, "provides interface LinkPacketMetadata as %s_%s_RadioLinkPacketMetadata;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
		fprintf(fp, "\n\n");


    		fprintf(fp, "/* Radio Module %s with %s process */\n",
					conftab[i].conf->radio->lib->full_name,
					conftab[i].conf->id->name);
		fprintf(fp, "uses interface SplitControl as %s_%s_Control;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name);
    		fprintf(fp, "provides interface %sParams as %s_%s_Params;\n", 
					conftab[i].conf->radio->lib->full_name,
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name);
		fprintf(fp, "uses interface RadioReceive as %s_%s_RadioReceive;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name);
		fprintf(fp, "uses interface Resource as %s_%s_RadioResource;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name);
		fprintf(fp, "uses interface RadioBuffer as %s_%s_RadioBuffer;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name);
		fprintf(fp, "uses interface RadioSend as %s_%s_RadioSend;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name);
		fprintf(fp, "uses interface RadioPacket as %s_%s_RadioPacket;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name);
		fprintf(fp, "uses interface PacketField<uint8_t> as %s_%s_PacketTransmitPower;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name);
		fprintf(fp, "uses interface PacketField<uint8_t> as %s_%s_PacketRSSI;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name);
		fprintf(fp, "uses interface PacketField<uint32_t> as %s_%s_PacketTimeSync;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name);
		fprintf(fp, "uses interface PacketField<uint8_t> as %s_%s_PacketLinkQuality;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name);
		fprintf(fp, "uses interface RadioCCA as %s_%s_RadioCCA;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name);
		fprintf(fp, "uses interface RadioState as %s_%s_RadioState;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name);
		fprintf(fp, "uses interface LinkPacketMetadata as %s_%s_RadioLinkPacketMetadata;\n",
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name);
		fprintf(fp, "\n\n");
	}

	fprintf(fp,"}\n\n");
	fprintf(fp,"implementation {\n\n");

	fprintf(fp,"void radioControlStartDone(uint16_t module_id, uint8_t to_layer, error_t error);\n");
	fprintf(fp,"void radioControlStopDone(uint16_t module_id, uint8_t to_layer, error_t error);\n\n");

	fprintf(fp,"void module_startDone(uint8_t module_id, error_t error) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP module_startDone(%%d, %%d)\", module_id, error);\n");
	fprintf(fp,"\tsignal ModuleCtrl.startDone(module_id, error);\n");
	fprintf(fp,"}\n\n");

	fprintf(fp,"void module_stopDone(uint8_t module_id, error_t error) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP module_stopDone(%%d, %%d)\", module_id, error);\n");
	fprintf(fp,"\tsignal ModuleCtrl.stopDone(module_id, error);\n");
	fprintf(fp,"}\n\n");

	fprintf(fp,"command error_t ModuleCtrl.start(uint8_t module_id) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP ModuleCtrl.start(%%d)\", module_id);\n");
	fprintf(fp,"\tswitch(module_id) {\n\n");

	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_APPLICATION):\n", i);
		fprintf(fp, "\t\tdbg(\"FennecEngine\", \"FennecEngineP call %s_%s_Control.start()\");\n",
					conftab[i].conf->id->name,
					conftab[i].conf->app->lib->full_name);
		fprintf(fp, "\t\treturn call %s_%s_Control.start();\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->app->lib->full_name);

                fprintf(fp, "\tcase (%d * F_LAYERS + F_NETWORK):\n", i);
		fprintf(fp, "\t\tdbg(\"FennecEngine\", \"FennecEngineP call %s_%s_Control.start()\");\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name);
		fprintf(fp, "\t\treturn call %s_%s_Control.start();\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name);

                fprintf(fp, "\tcase (%d * F_LAYERS + F_MAC):\n", i);
		fprintf(fp, "\t\tdbg(\"FennecEngine\", \"FennecEngineP call %s_%s_Control.start()\");\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
		fprintf(fp, "\t\treturn call %s_%s_Control.start();\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);

                fprintf(fp, "\tcase (%d * F_LAYERS + F_RADIO):\n", i);
		fprintf(fp, "\t\tdbg(\"FennecEngine\", \"FennecEngineP call %s_%s_Control.start()\");\n",
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name);
		fprintf(fp, "\t\treturn call %s_%s_Control.start();\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name);
	}
	fprintf(fp,"\t}\n");
	fprintf(fp,"\treturn FAIL;\n");
	fprintf(fp,"}\n\n");

	fprintf(fp,"command error_t ModuleCtrl.stop(uint8_t module_id) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP ModuleCtrl.stop(%%d)\", module_id);\n");

	fprintf(fp,"\tswitch(module_id) {\n\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_APPLICATION):\n", i);
		fprintf(fp, "\t\tdbg(\"FennecEngine\", \"FennecEngineP call %s_%s_Control.stop()\");\n",
					conftab[i].conf->id->name,
					conftab[i].conf->app->lib->full_name);
		fprintf(fp, "\t\treturn call %s_%s_Control.stop();\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->app->lib->full_name);

                fprintf(fp, "\tcase (%d * F_LAYERS + F_NETWORK):\n", i);
		fprintf(fp, "\t\tdbg(\"FennecEngine\", \"FennecEngineP call %s_%s_Control.stop()\");\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name);
		fprintf(fp, "\t\treturn call %s_%s_Control.stop();\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name);

                fprintf(fp, "\tcase (%d * F_LAYERS + F_MAC):\n", i);
		fprintf(fp, "\t\tdbg(\"FennecEngine\", \"FennecEngineP call %s_%s_Control.stop()\");\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
		fprintf(fp, "\t\treturn call %s_%s_Control.stop();\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);

                fprintf(fp, "\tcase (%d * F_LAYERS + F_RADIO):\n", i);
		fprintf(fp, "\t\tdbg(\"FennecEngine\", \"FennecEngineP call %s_%s_Control.stop()\");\n",
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name);
		fprintf(fp, "\t\treturn call %s_%s_Control.stop();\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name);
	}
	fprintf(fp,"\t}\n");
	fprintf(fp,"\treturn FAIL;\n");
	fprintf(fp,"}\n\n");

	fprintf(fp,"error_t AMSend_send(uint16_t module_id, uint8_t to_layer, am_addr_t addr, message_t* msg, uint8_t len) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP AMSend_send(%%d, %%d, %%d, 0x%%1x, %%d)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer, addr, msg, len);\n");
	fprintf(fp,"\tmsg->conf = call Fennec.getConfId(module_id);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_NETWORK):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_NetworkAMSend.send(addr, msg, len);\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name);

                fprintf(fp, "\tcase (%d * F_LAYERS + F_MAC):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_MacAMSend.send(addr, msg, len);\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
	}
	fprintf(fp,"\tdefault:\n");
	fprintf(fp,"\t\treturn FAIL;\n");
	fprintf(fp,"\t}\n");
	fprintf(fp,"}\n\n");


	fprintf(fp,"error_t AMSend_cancel(uint16_t module_id, uint8_t to_layer, message_t *msg) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP AMSend_cancel(%%d, %%d, 0x%%1x)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer, msg);\n");
	fprintf(fp,"\tmsg->conf = call Fennec.getConfId(module_id);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_NETWORK):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_NetworkAMSend.cancel(msg);\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name);

                fprintf(fp, "\tcase (%d * F_LAYERS + F_MAC):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_MacAMSend.cancel(msg);\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
	}
	fprintf(fp,"\tdefault:\n");
	fprintf(fp,"\t\treturn FAIL;\n");
	fprintf(fp,"\t}\n");
	fprintf(fp,"}\n\n");


	fprintf(fp,"void* AMSend_getPayload(uint16_t module_id, uint8_t to_layer, message_t *msg, uint8_t len) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP AMSend_getPayload(%%d, %%d, 0x%%1x, %%d)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer, msg, len);\n");
	fprintf(fp,"\tmsg->conf = call Fennec.getConfId(module_id);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_NETWORK):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_NetworkAMSend.getPayload(msg, len);\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name);

                fprintf(fp, "\tcase (%d * F_LAYERS + F_MAC):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_MacAMSend.getPayload(msg, len);\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
	}
	fprintf(fp,"\tdefault:\n");
	fprintf(fp,"\t\treturn NULL;\n");
	fprintf(fp,"}\n");
	fprintf(fp,"  }\n\n");


	fprintf(fp,"uint8_t AMSend_maxPayloadLength(uint16_t module_id, uint8_t to_layer) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP AMSend_maxPayloadLength(%%d, %%d)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_NETWORK):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_NetworkAMSend.maxPayloadLength();\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name);

                fprintf(fp, "\tcase (%d * F_LAYERS + F_MAC):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_MacAMSend.maxPayloadLength();\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
	}
	fprintf(fp,"\tdefault:\n");
	fprintf(fp,"\t\treturn 0;\n");
	fprintf(fp,"\t}\n");
	fprintf(fp,"}\n\n");


	fprintf(fp,"am_addr_t AMPacket_address(uint16_t module_id, uint8_t to_layer) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP AMPacket_address(%%d, %%d)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_NETWORK):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_NetworkAMPacket.address();\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name);

                fprintf(fp, "\tcase (%d * F_LAYERS + F_MAC):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_MacAMPacket.address();\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
	}
	fprintf(fp,"\tdefault:\n");
	fprintf(fp,"\t\treturn 0;\n");
	fprintf(fp,"\t}\n");
	fprintf(fp,"}\n\n");


	fprintf(fp,"am_addr_t AMPacket_destination(uint16_t module_id, uint8_t to_layer, message_t *msg) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP AMPacket_destination(%%d, %%d, 0x%%1x)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer, msg);\n");
	fprintf(fp,"\tmsg->conf = call Fennec.getConfId(module_id);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_NETWORK):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_NetworkAMPacket.destination(msg);\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name);

                fprintf(fp, "\tcase (%d * F_LAYERS + F_MAC):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_MacAMPacket.destination(msg);\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
	}
	fprintf(fp,"\tdefault:\n");
	fprintf(fp,"\t\treturn 0;\n");
	fprintf(fp,"\t}\n");
	fprintf(fp,"}\n\n");


	fprintf(fp,"am_addr_t AMPacket_source(uint16_t module_id, uint8_t to_layer, message_t *msg) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP AMPacket_source(%%d, %%d, 0x%%1x)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer, msg);\n");
	fprintf(fp,"\tmsg->conf = call Fennec.getConfId(module_id);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_NETWORK):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_NetworkAMPacket.source(msg);\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name);

                fprintf(fp, "\tcase (%d * F_LAYERS + F_MAC):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_MacAMPacket.source(msg);\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
	}
	fprintf(fp,"\tdefault:\n");
	fprintf(fp,"\t\treturn 0;\n");
	fprintf(fp,"\t}\n");
	fprintf(fp,"}\n\n");


	fprintf(fp,"void AMPacket_setDestination(uint16_t module_id, uint8_t to_layer, message_t *msg, am_addr_t addr) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP AMPacket_setDestination(%%d, %%d, 0x%%1x, %%d)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer, msg, addr);\n");
	fprintf(fp,"\tmsg->conf = call Fennec.getConfId(module_id);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_NETWORK):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_NetworkAMPacket.setDestination(msg, addr);\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name);

                fprintf(fp, "\tcase (%d * F_LAYERS + F_MAC):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_MacAMPacket.setDestination(msg, addr);\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
	}
	fprintf(fp,"\tdefault:\n");
	fprintf(fp,"\t\treturn;\n");
	fprintf(fp,"\t}\n");
	fprintf(fp,"}\n\n");


	fprintf(fp,"void AMPacket_setSource(uint16_t module_id, uint8_t to_layer, message_t *msg, am_addr_t addr) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP AMPacket_setSource(%%d, %%d, 0x%%1x, %%d)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer, msg, addr);\n");
	fprintf(fp,"\tmsg->conf = call Fennec.getConfId(module_id);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_NETWORK):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_NetworkAMPacket.setSource(msg, addr);\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name);

                fprintf(fp, "\tcase (%d * F_LAYERS + F_MAC):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_MacAMPacket.setSource(msg, addr);\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
	}
	fprintf(fp,"\tdefault:\n");
	fprintf(fp,"\t\treturn;\n");
	fprintf(fp,"\t}\n");
	fprintf(fp,"}\n\n");



	fprintf(fp,"bool AMPacket_isForMe(uint16_t module_id, uint8_t to_layer, message_t *msg) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP AMPacket_isForMe(%%d, %%d, 0x%%1x)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer, msg);\n");
	fprintf(fp,"\tmsg->conf = call Fennec.getConfId(module_id);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_NETWORK):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_NetworkAMPacket.isForMe(msg);\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name);

                fprintf(fp, "\tcase (%d * F_LAYERS + F_MAC):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_MacAMPacket.isForMe(msg);\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
	}
	fprintf(fp,"\tdefault:\n");
	fprintf(fp,"\t\treturn 0;\n");
	fprintf(fp,"\t}\n");
	fprintf(fp,"}\n\n");


	fprintf(fp,"am_id_t AMPacket_type(uint16_t module_id, uint8_t to_layer, message_t *msg) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP AMPacket_type(%%d, %%d, 0x%%1x)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer, msg);\n");
	fprintf(fp,"\tmsg->conf = call Fennec.getConfId(module_id);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_NETWORK):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_NetworkAMPacket.type(msg);\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name);

                fprintf(fp, "\tcase (%d * F_LAYERS + F_MAC):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_MacAMPacket.type(msg);\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
	}
	fprintf(fp,"\tdefault:\n");
	fprintf(fp,"\t\treturn 0;\n");
	fprintf(fp,"\t}\n");
	fprintf(fp,"}\n\n");


	fprintf(fp,"void AMPacket_setType(uint16_t module_id, uint8_t to_layer, message_t *msg, am_id_t t) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP AMPacket_setType(%%d, %%d, 0x%%1x, %%d)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer, msg, t);\n");
	fprintf(fp,"\tmsg->conf = call Fennec.getConfId(module_id);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_NETWORK):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_NetworkAMPacket.setType(msg, t);\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name);

                fprintf(fp, "\tcase (%d * F_LAYERS + F_MAC):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_MacAMPacket.setType(msg, t);\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
	}
	fprintf(fp,"\tdefault:\n");
	fprintf(fp,"\t\treturn;\n");
	fprintf(fp,"\t}\n");
	fprintf(fp,"}\n\n");


	fprintf(fp,"am_group_t AMPacket_group(uint16_t module_id, uint8_t to_layer, message_t *msg) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP AMPacket_group(%%d, %%d, 0x%%1x)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer, msg);\n");
	fprintf(fp,"\tmsg->conf = call Fennec.getConfId(module_id);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_NETWORK):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_NetworkAMPacket.group(msg);\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name);

                fprintf(fp, "\tcase (%d * F_LAYERS + F_MAC):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_MacAMPacket.group(msg);\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
	}
	fprintf(fp,"\tdefault:\n");
	fprintf(fp,"\t\treturn 0;\n");
	fprintf(fp,"\t}\n");
	fprintf(fp,"}\n\n");


	fprintf(fp,"void AMPacket_setGroup(uint16_t module_id, uint8_t to_layer, message_t *msg, am_group_t grp) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP AMPacket_setGroup(%%d, %%d, 0x%%1x, %%d)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer, msg, grp);\n");
	fprintf(fp,"\tmsg->conf = call Fennec.getConfId(module_id);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_NETWORK):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_NetworkAMPacket.setGroup(msg, grp);\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name);

                fprintf(fp, "\tcase (%d * F_LAYERS + F_MAC):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_MacAMPacket.setGroup(msg, grp);\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
	}
	fprintf(fp,"\tdefault:\n");
	fprintf(fp,"\t\treturn;\n");
	fprintf(fp,"\t}\n");
	fprintf(fp,"}\n\n");



	fprintf(fp,"am_group_t AMPacket_localGroup(uint16_t module_id, uint8_t to_layer) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP Packet_localGroup(%%d, %%d)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_NETWORK):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_NetworkAMPacket.localGroup();\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name);

                fprintf(fp, "\tcase (%d * F_LAYERS + F_MAC):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_MacAMPacket.localGroup();\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
	}
	fprintf(fp,"\tdefault:\n");
	fprintf(fp,"\t\treturn 0;\n");
	fprintf(fp,"\t}\n");
	fprintf(fp,"}\n\n");



	fprintf(fp,"void* Packet_getPayload(uint16_t module_id, uint8_t to_layer, message_t *msg, uint8_t len) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP Packet_getPayload(%%d, %%d, 0x%%1x, %%d)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer, msg, len);\n");
	fprintf(fp,"\tmsg->conf = call Fennec.getConfId(module_id);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_NETWORK):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_NetworkPacket.getPayload(msg, len);\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name);

                fprintf(fp, "\tcase (%d * F_LAYERS + F_MAC):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_MacPacket.getPayload(msg, len);\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
	}
	fprintf(fp,"\tdefault:\n");
	fprintf(fp,"\t\treturn NULL;\n");
	fprintf(fp,"\t}\n");
	fprintf(fp,"}\n\n");


	fprintf(fp,"uint8_t Packet_maxPayloadLength(uint16_t module_id, uint8_t to_layer) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP Packet_maxPayloadLength(%%d, %%d)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_NETWORK):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_NetworkPacket.maxPayloadLength();\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name);

                fprintf(fp, "\tcase (%d * F_LAYERS + F_MAC):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_MacPacket.maxPayloadLength();\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
	}
	fprintf(fp,"\tdefault:\n");
	fprintf(fp,"\t\treturn 0;\n");
	fprintf(fp,"\t}\n");
	fprintf(fp,"}\n\n");


	fprintf(fp,"void Packet_clear(uint16_t module_id, uint8_t to_layer, message_t *msg) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP Packet_clear(%%d, %%d, 0x%%1x)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer, msg);\n");
	fprintf(fp,"\tmsg->conf = call Fennec.getConfId(module_id);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_NETWORK):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_NetworkPacket.clear(msg);\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name);

                fprintf(fp, "\tcase (%d * F_LAYERS + F_MAC):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_MacPacket.clear(msg);\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
	}
	fprintf(fp,"\tdefault:\n");
	fprintf(fp,"\t\treturn;\n");
	fprintf(fp,"\t}\n");
	fprintf(fp,"}\n\n");


	fprintf(fp,"uint8_t Packet_payloadLength(uint16_t module_id, uint8_t to_layer, message_t *msg) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP Packet_payloadLength(%%d, %%d, 0x%%1x)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer, msg);\n");
	fprintf(fp,"\tmsg->conf = call Fennec.getConfId(module_id);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_NETWORK):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_NetworkPacket.payloadLength(msg);\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name);

                fprintf(fp, "\tcase (%d * F_LAYERS + F_MAC):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_MacPacket.payloadLength(msg);\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
	}
	fprintf(fp,"\tdefault:\n");
	fprintf(fp,"\t\treturn 0;\n");
	fprintf(fp,"\t}\n");
	fprintf(fp,"}\n\n");


	fprintf(fp,"void Packet_setPayloadLength(uint16_t module_id, uint8_t to_layer, message_t *msg, uint8_t len) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP Packet_setPayloadLength(%%d, %%d, 0x%%1x, %%d)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer, msg, len);\n");
	fprintf(fp,"\tmsg->conf = call Fennec.getConfId(module_id);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_NETWORK):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_NetworkPacket.setPayloadLength(msg, len);\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name);

                fprintf(fp, "\tcase (%d * F_LAYERS + F_MAC):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_MacPacket.setPayloadLength(msg, len);\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
	}
	fprintf(fp,"\tdefault:\n");
	fprintf(fp,"\t\treturn;\n");
	fprintf(fp,"\t}\n");
	fprintf(fp,"}\n\n");


	fprintf(fp,"error_t PacketAcknowledgements_requestAck(uint16_t module_id, uint8_t to_layer, message_t *msg) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP PacketAcknowledgements_requestAck(%%d, %%d, 1x%%1x)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer, msg);\n");
	fprintf(fp,"\tmsg->conf = call Fennec.getConfId(module_id);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_NETWORK):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_NetworkPacketAcknowledgements.requestAck(msg);\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name);

                fprintf(fp, "\tcase (%d * F_LAYERS + F_MAC):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_MacPacketAcknowledgements.requestAck(msg);\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
	}
	fprintf(fp,"\tdefault:\n");
	fprintf(fp,"\t\treturn FAIL;\n");
	fprintf(fp,"\t}\n");
	fprintf(fp,"}\n\n");


	fprintf(fp,"error_t PacketAcknowledgements_noAck(uint16_t module_id, uint8_t to_layer, message_t *msg) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP PacketAcknowledgements_noAck(%%d, %%d, 0x%%1x)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer, msg);\n");
	fprintf(fp,"\tmsg->conf = call Fennec.getConfId(module_id);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_NETWORK):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_NetworkPacketAcknowledgements.noAck(msg);\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name);

                fprintf(fp, "\tcase (%d * F_LAYERS + F_MAC):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_MacPacketAcknowledgements.noAck(msg);\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
	}
	fprintf(fp,"\tdefault:\n");
	fprintf(fp,"\t\treturn FAIL;\n");
	fprintf(fp,"\t}\n");
	fprintf(fp,"}\n\n");


	fprintf(fp,"bool PacketAcknowledgements_wasAcked(uint16_t module_id, uint8_t to_layer, message_t *msg) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP PacketAcknowledgements_wasAcked(%%d, %%d, 0x%%1x)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer, msg);\n");
	fprintf(fp,"\tmsg->conf = call Fennec.getConfId(module_id);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_NETWORK):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_NetworkPacketAcknowledgements.wasAcked(msg);\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name);

                fprintf(fp, "\tcase (%d * F_LAYERS + F_MAC):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_MacPacketAcknowledgements.wasAcked(msg);\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
	}
	fprintf(fp,"\tdefault:\n");
	fprintf(fp,"\t\treturn 0;\n");
	fprintf(fp,"\t}\n");
	fprintf(fp,"}\n\n");


	fprintf(fp,"bool LinkPacketMetadata_highChannelQuality(uint16_t module_id, uint8_t to_layer, message_t *msg) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP LinkPacketMetadata_highChannelQuality(%%d, %%d, 0x%%1x)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer, msg);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_MAC):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_MacLinkPacketMetadata.highChannelQuality(msg);\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);

                fprintf(fp, "\tcase (%d * F_LAYERS + F_RADIO):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_RadioLinkPacketMetadata.highChannelQuality(msg);\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name);
	}
	fprintf(fp,"\tdefault:\n");
	fprintf(fp,"\t\treturn FALSE;\n");
	fprintf(fp,"\t}\n");
	fprintf(fp,"}\n\n");


	/* Radio Only Interfaces */



	fprintf(fp,"error_t RadioResource_request(uint16_t module_id, uint8_t to_layer) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP RadioResource_request(%%d, %%d)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_RADIO):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_RadioResource.request();\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name);
	}
	fprintf(fp,"\tdefault:\n");
	fprintf(fp,"\t\treturn FAIL;\n");
	fprintf(fp,"\t}\n");
	fprintf(fp,"}\n\n");


	fprintf(fp,"error_t RadioResource_immediateRequest(uint16_t module_id, uint8_t to_layer) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP RadioResource_immediateRequest(%%d, %%d)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_RADIO):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_RadioResource.immediateRequest();\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name);
	}
	fprintf(fp,"\tdefault:\n");
	fprintf(fp,"\t\treturn 0;\n");
	fprintf(fp,"\t}\n");
	fprintf(fp,"}\n\n");


	fprintf(fp,"error_t RadioResource_release(uint16_t module_id, uint8_t to_layer) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP RadioResource_release(%%d, %%d)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_RADIO):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_RadioResource.release();\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name);
	}
	fprintf(fp,"\tdefault:\n");
	fprintf(fp,"\t\treturn 0;\n");
	fprintf(fp,"\t}\n");
	fprintf(fp,"}\n\n");


	fprintf(fp,"bool RadioResource_isOwner(uint16_t module_id, uint8_t to_layer) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP RadioResource_isOwner(%%d, %%d)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_RADIO):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_RadioResource.isOwner();\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name);
	}
	fprintf(fp,"\tdefault:\n");
	fprintf(fp,"\t\treturn 0;\n");
	fprintf(fp,"\t}\n");
	fprintf(fp,"}\n\n");


	fprintf(fp,"error_t RadioSend_send(uint16_t module_id, uint8_t to_layer, message_t* msg, bool useCca) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP RadioSend_send(%%d, %%d, 0x%%1x, %%d)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer, msg, useCca);\n");
	fprintf(fp,"\tmsg->conf = call Fennec.getConfId(module_id);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_RADIO):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_RadioSend.send(msg, useCca);\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name);
	}
	fprintf(fp,"\tdefault:\n");
	fprintf(fp,"\t\treturn FAIL;\n");
	fprintf(fp,"\t}\n");
	fprintf(fp,"}\n\n");


	fprintf(fp,"uint8_t RadioPacket_maxPayloadLength(uint16_t module_id, uint8_t to_layer) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP RadioPacket_maxPayloadLength(%%d, %%d)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_RADIO):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_RadioPacket.maxPayloadLength();\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name);
	}
	fprintf(fp,"\tdefault:\n");
	fprintf(fp,"\t\treturn 0;\n");
	fprintf(fp,"\t}\n");
	fprintf(fp,"}\n\n");


	fprintf(fp,"uint8_t RadioPacket_headerLength(uint16_t module_id, uint8_t to_layer, message_t *msg) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP RadioPacket_headerLength(%%d, %%d, 0x%%1x)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer, msg);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_RADIO):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_RadioPacket.headerLength(msg);\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name);
	}
	fprintf(fp,"\tdefault:\n");
	fprintf(fp,"\t\treturn 0;\n");
	fprintf(fp,"\t}\n");
	fprintf(fp,"}\n\n");


	fprintf(fp,"uint8_t RadioPacket_payloadLength(uint16_t module_id, uint8_t to_layer, message_t *msg) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP RadioPacket_payloadLength(%%d, %%d, 0x%%1x)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer, msg);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_RADIO):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_RadioPacket.payloadLength(msg);\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name);
	}
	fprintf(fp,"\tdefault:\n");
	fprintf(fp,"\t\treturn 0;\n");
	fprintf(fp,"\t}\n");
	fprintf(fp,"}\n\n");


	fprintf(fp,"void RadioPacket_setPayloadLength(uint16_t module_id, uint8_t to_layer, message_t *msg, uint8_t length) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP RadioPacket_setPayloadLength(%%d, %%d, 0x%%1x, %%d)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer, msg, length);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_RADIO):\n", i);
		fprintf(fp,"\t\tcall %s_%s_RadioPacket.setPayloadLength(msg, length);\n",
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name);
		fprintf(fp,"\t\treturn;\n\n");
	}
	fprintf(fp,"\tdefault:\n");
	fprintf(fp,"\t\treturn;\n");
	fprintf(fp,"\t}\n");
	fprintf(fp,"}\n\n");


	fprintf(fp,"uint8_t RadioPacket_metadataLength(uint16_t module_id, uint8_t to_layer, message_t *msg) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP RadioPacket_metadataLength(%%d, %%d, 0x%%1x)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer, msg);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_RADIO):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_RadioPacket.metadataLength(msg);\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name);
	}
	fprintf(fp,"\tdefault:\n");
	fprintf(fp,"\t\treturn 0;\n");
	fprintf(fp,"\t}\n");
	fprintf(fp,"}\n\n");


	fprintf(fp,"void RadioPacket_clear(uint16_t module_id, uint8_t to_layer, message_t *msg) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP RadioPacket_clear(%%d, %%d, 0x%%1x)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer, msg);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_RADIO):\n", i);
		fprintf(fp,"\t\tcall %s_%s_RadioPacket.clear(msg);\n",
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name);
		fprintf(fp,"\t\treturn;\n\n");
	}
	fprintf(fp,"\tdefault:\n");
	fprintf(fp,"\t\treturn;\n");
	fprintf(fp,"\t}\n");
	fprintf(fp,"}\n\n");


	fprintf(fp,"error_t RadioBuffer_load(uint16_t module_id, uint8_t to_layer, message_t* msg) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP RadioBuffer_load(%%d, %%d, 0x%%1x)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer, msg);\n");
	fprintf(fp,"\tmsg->conf = call Fennec.getConfId(module_id);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_RADIO):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_RadioBuffer.load(msg);\n",
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name);
	}
	fprintf(fp,"\tdefault:\n");
	fprintf(fp,"\t\treturn FAIL;\n");
	fprintf(fp,"\t}\n");
	fprintf(fp,"}\n\n");


	fprintf(fp,"bool PacketTransmitPower_isSet(uint16_t module_id, uint8_t to_layer, message_t *msg) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP PacketTransmitPower_isSet(%%d, %%d, 0x%%1x)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer, msg);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_RADIO):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_PacketTransmitPower.isSet(msg);\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name);
	}
	fprintf(fp,"\tdefault:\n");
	fprintf(fp,"\t\treturn 0;\n");
	fprintf(fp,"\t}\n");
	fprintf(fp,"}\n\n");


	fprintf(fp,"uint8_t PacketTransmitPower_get(uint16_t module_id, uint8_t to_layer, message_t *msg) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP PacketTransmitPower_get(%%d, %%d, 0x%%1x)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer, msg);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_RADIO):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_PacketTransmitPower.get(msg);\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name);
	}
	fprintf(fp,"\tdefault:\n");
	fprintf(fp,"\t\treturn 0;\n");
	fprintf(fp,"\t}\n");
	fprintf(fp,"}\n\n");


	fprintf(fp,"void PacketTransmitPower_clear(uint16_t module_id, uint8_t to_layer, message_t *msg) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP PacketTransmitPower_clear(%%d, %%d, 0x%%1x)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer, msg);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_RADIO):\n", i);
		fprintf(fp,"\t\tcall %s_%s_PacketTransmitPower.clear(msg);\n",
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name);
		fprintf(fp,"\t\treturn;\n\n");
	}
	fprintf(fp,"\tdefault:\n");
	fprintf(fp,"\t\treturn;\n");
	fprintf(fp,"\t}\n");
	fprintf(fp,"}\n\n");


	fprintf(fp,"void PacketTransmitPower_set(uint16_t module_id, uint8_t to_layer, message_t *msg, uint8_t value) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP PacketTransmitPower_set(%%d, %%d, 0x%%1x, %%d)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer, msg, value);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_RADIO):\n", i);
		fprintf(fp,"\t\tcall %s_%s_PacketTransmitPower.set(msg, value);\n",
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name);
		fprintf(fp,"\t\treturn;\n\n");
	}
	fprintf(fp,"\tdefault:\n");
	fprintf(fp,"\t\treturn;\n");
	fprintf(fp,"\t}\n");
	fprintf(fp,"}\n\n");



	fprintf(fp,"bool PacketRSSI_isSet(uint16_t module_id, uint8_t to_layer, message_t *msg) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP PacketRSSI_isSet(%%d, %%d, 0x%%1x)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer, msg);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_RADIO):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_PacketRSSI.isSet(msg);\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name);
	}
	fprintf(fp,"\tdefault:\n");
	fprintf(fp,"\t\treturn 0;\n");
	fprintf(fp,"\t}\n");
	fprintf(fp,"}\n\n");


	fprintf(fp,"uint8_t PacketRSSI_get(uint16_t module_id, uint8_t to_layer, message_t *msg) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP PacketRSSI_get(%%d, %%d, 0x%%1x)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer, msg);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_RADIO):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_PacketRSSI.get(msg);\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name);
	}
	fprintf(fp,"\tdefault:\n");
	fprintf(fp,"\t\treturn 0;\n");
	fprintf(fp,"\t}\n");
	fprintf(fp,"}\n\n");


	fprintf(fp,"void PacketRSSI_clear(uint16_t module_id, uint8_t to_layer, message_t *msg) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP PacketRSSI_clear(%%d, %%d, 0x%%1x)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer, msg);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_RADIO):\n", i);
		fprintf(fp,"\t\tcall %s_%s_PacketRSSI.clear(msg);\n",
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name);
		fprintf(fp,"\t\treturn;\n\n");
	}
	fprintf(fp,"\tdefault:\n");
	fprintf(fp,"\t\treturn;\n");
	fprintf(fp,"\t}\n");
	fprintf(fp,"}\n\n");


	fprintf(fp,"void PacketRSSI_set(uint16_t module_id, uint8_t to_layer, message_t *msg, uint8_t value) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP PacketRSSI_set(%%d, %%d, 0x%%1x, %%d)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer, msg, value);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_RADIO):\n", i);
		fprintf(fp,"\t\tcall %s_%s_PacketRSSI.set(msg, value);\n",
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name);
		fprintf(fp,"\t\treturn;\n\n");
	}
	fprintf(fp,"\tdefault:\n");
	fprintf(fp,"\t\treturn;\n");
	fprintf(fp,"\t}\n");
	fprintf(fp,"}\n\n");


	fprintf(fp,"bool PacketTimeSync_isSet(uint16_t module_id, uint8_t to_layer, message_t *msg) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP PacketTimeSync_isSet(%%d, %%d, 0x%%1x)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer, msg);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_RADIO):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_PacketTimeSync.isSet(msg);\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name);
	}
	fprintf(fp,"\tdefault:\n");
	fprintf(fp,"\t\treturn 0;\n");
	fprintf(fp,"\t}\n");
	fprintf(fp,"}\n\n");


	fprintf(fp,"uint32_t PacketTimeSync_get(uint16_t module_id, uint8_t to_layer, message_t *msg) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP PacketTimeSync_get(%%d, %%d, 0x%%1x)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer, msg);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_RADIO):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_PacketTimeSync.get(msg);\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name);
	}
	fprintf(fp,"\tdefault:\n");
	fprintf(fp,"\t\treturn 0;\n");
	fprintf(fp,"\t}\n");
	fprintf(fp,"}\n\n");


	fprintf(fp,"void PacketTimeSync_clear(uint16_t module_id, uint8_t to_layer, message_t *msg) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP PacketTimeSync_clear(%%d, %%d, 0x%%1x)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer, msg);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_RADIO):\n", i);
		fprintf(fp,"\t\tcall %s_%s_PacketTimeSync.clear(msg);\n",
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name);
		fprintf(fp,"\t\treturn;\n\n");
	}
	fprintf(fp,"\tdefault:\n");
	fprintf(fp,"\t\treturn;\n");
	fprintf(fp,"\t}\n");
	fprintf(fp,"}\n\n");


	fprintf(fp,"void PacketTimeSync_set(uint16_t module_id, uint8_t to_layer, message_t *msg, uint32_t value) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP PacketTimeSync_set(%%d, %%d, 0x%%1x, %%d)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer, msg, value);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_RADIO):\n", i);
		fprintf(fp,"\t\tcall %s_%s_PacketTimeSync.set(msg, value);\n",
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name);
		fprintf(fp,"\t\treturn;\n\n");
	}
	fprintf(fp,"\tdefault:\n");
	fprintf(fp,"\t\treturn;\n");
	fprintf(fp,"\t}\n");
	fprintf(fp,"}\n\n");


	fprintf(fp,"bool PacketLinkQuality_isSet(uint16_t module_id, uint8_t to_layer, message_t *msg) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP PacketLinkQuality_isSet(%%d, %%d, 0x%%1x)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer, msg);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_RADIO):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_PacketLinkQuality.isSet(msg);\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name);
	}
	fprintf(fp,"\tdefault:\n");
	fprintf(fp,"\t\treturn 0;\n");
	fprintf(fp,"\t}\n");
	fprintf(fp,"}\n\n");


	fprintf(fp,"uint8_t PacketLinkQuality_get(uint16_t module_id, uint8_t to_layer, message_t *msg) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP PacketLinkQuality_get(%%d, %%d, 0x%%1x)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer, msg);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_RADIO):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_PacketLinkQuality.get(msg);\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name);
	}
	fprintf(fp,"\tdefault:\n");
	fprintf(fp,"\t\treturn 0;\n");
	fprintf(fp,"\t}\n");
	fprintf(fp,"}\n\n");


	fprintf(fp,"void PacketLinkQuality_clear(uint16_t module_id, uint8_t to_layer, message_t *msg) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP PacketLinkQuality_clear(%%d, %%d, 0x%%1x)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer, msg);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_RADIO):\n", i);
		fprintf(fp,"\t\tcall %s_%s_PacketLinkQuality.clear(msg);\n",
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name);
		fprintf(fp,"\t\treturn;\n\n");
	}
	fprintf(fp,"\tdefault:\n");
	fprintf(fp,"\t\treturn;\n");
	fprintf(fp,"\t}\n");
	fprintf(fp,"}\n\n");


	fprintf(fp,"void PacketLinkQuality_set(uint16_t module_id, uint8_t to_layer, message_t *msg, uint8_t value) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP PacketLinkQuality_set(%%d, %%d, 0x%%1x, %%d)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer, msg, value);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_RADIO):\n", i);
		fprintf(fp,"\t\tcall %s_%s_PacketLinkQuality.set(msg, value);\n",
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name);
		fprintf(fp,"\t\treturn;\n\n");
	}
	fprintf(fp,"\tdefault:\n");
	fprintf(fp,"\t\treturn;\n");
	fprintf(fp,"\t}\n");
	fprintf(fp,"}\n\n");


	fprintf(fp,"error_t RadioCCA_request(uint16_t module_id, uint8_t to_layer) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP RadioCCA_request(%%d, %%d)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_RADIO):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_RadioCCA.request();\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name);
	}
	fprintf(fp,"\tdefault:\n");
	fprintf(fp,"\t\treturn FAIL;\n");
	fprintf(fp,"\t}\n");
	fprintf(fp,"}\n\n");


	fprintf(fp,"error_t RadioState_turnOff(uint16_t module_id, uint8_t to_layer) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP RadioState_turnOff(%%d, %%d)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_RADIO):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_RadioState.turnOff();\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name);
	}
	fprintf(fp,"\tdefault:\n");
	fprintf(fp,"\t\treturn FALSE;\n");
	fprintf(fp,"\t}\n");
	fprintf(fp,"}\n\n");


	fprintf(fp,"error_t RadioState_standby(uint16_t module_id, uint8_t to_layer) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP RadioState_standby(%%d, %%d)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_RADIO):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_RadioState.standby();\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name);
	}
	fprintf(fp,"\tdefault:\n");
	fprintf(fp,"\t\treturn FALSE;\n");
	fprintf(fp,"\t}\n");
	fprintf(fp,"}\n\n");


	fprintf(fp,"error_t RadioState_turnOn(uint16_t module_id, uint8_t to_layer) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP RadioState_turnOn(%%d, %%d)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_RADIO):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_RadioState.turnOn();\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name);
	}
	fprintf(fp,"\tdefault:\n");
	fprintf(fp,"\t\treturn FALSE;\n");
	fprintf(fp,"\t}\n");
	fprintf(fp,"}\n\n");


	fprintf(fp,"error_t RadioState_setChannel(uint16_t module_id, uint8_t to_layer, uint8_t channel) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP RadioState_setChannel(%%d, %%d, %%d)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer, channel);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_RADIO):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_RadioState.setChannel(channel);\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name);
	}
	fprintf(fp,"\tdefault:\n");
	fprintf(fp,"\t\treturn FALSE;\n");
	fprintf(fp,"\t}\n");
	fprintf(fp,"}\n\n");


	fprintf(fp,"uint8_t RadioState_getChannel(uint16_t module_id, uint8_t to_layer) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP RadioState_getChannel(%%d, %%d)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_RADIO):\n", i);
		fprintf(fp,"\t\treturn call %s_%s_RadioState.getChannel();\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->radio->lib->full_name);
	}
	fprintf(fp,"\tdefault:\n");
	fprintf(fp,"\t\treturn 0;\n");
	fprintf(fp,"\t}\n");
	fprintf(fp,"}\n\n");



	/* Events */


	fprintf(fp,"void sendDone(uint16_t module_id, uint8_t to_layer, message_t* msg, error_t error) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP sendDone(%%d, %%d, 0x%%1x, %%d)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer, msg, error);\n");
	fprintf(fp,"\tmsg->conf = call Fennec.getConfId(module_id);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_APPLICATION):\n", i);
		fprintf(fp,"\t\tsignal %s_%s_NetworkAMSend.sendDone(msg, error);\n",
					conftab[i].conf->id->name,
					conftab[i].conf->app->lib->full_name);
		fprintf(fp,"\t\treturn;\n\n");

                fprintf(fp, "\tcase (%d * F_LAYERS + F_NETWORK):\n", i);
		fprintf(fp,"\t\tsignal %s_%s_MacAMSend.sendDone(msg, error);\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name);
		fprintf(fp,"\t\treturn;\n\n");
	}
	fprintf(fp,"\tdefault:\n");
	fprintf(fp,"\t\treturn;\n");
	fprintf(fp,"}\n\n");
	fprintf(fp,"}\n\n");


	fprintf(fp,"message_t* receive(uint16_t module_id, uint8_t to_layer, message_t* msg, void* payload, uint8_t len) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP receive(%%d, %%d, 0x%%1x, 0x%%1x, %%d)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer, msg, payload, len);\n");
	fprintf(fp,"\tif (call Fennec.checkPacket(msg) != SUCCESS) {\n");
	fprintf(fp,"\t\t return msg;\n");
	fprintf(fp,"\t}\n\n");
	fprintf(fp,"\tmsg->conf = call Fennec.getConfId(module_id);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	fprintf(fp,"\t\treturn msg;\n");
	fprintf(fp,"\t}\n\n");

	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_APPLICATION):\n", i);
		fprintf(fp,"\t\treturn signal %s_%s_NetworkReceive.receive(msg, payload, len);\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->app->lib->full_name);

                fprintf(fp, "\tcase (%d * F_LAYERS + F_NETWORK):\n", i);
		fprintf(fp,"\t\treturn signal %s_%s_MacReceive.receive(msg, payload, len);\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name);
	}
	fprintf(fp,"\tdefault:\n");
	fprintf(fp,"\t\treturn msg;\n\n");
	fprintf(fp,"\t}\n");
	fprintf(fp,"}\n\n");


	fprintf(fp,"message_t* snoop(uint16_t module_id, uint8_t to_layer, message_t* msg, void* payload, uint8_t len) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP snoop(%%d, %%d, 0x%%1x, 0x%%1x, %%d)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer, msg, payload, len);\n");
	fprintf(fp,"\tif (call Fennec.checkPacket(msg) != SUCCESS) {\n");
	fprintf(fp,"\t\t return msg;\n");
	fprintf(fp,"\t}\n\n");
	fprintf(fp,"\tmsg->conf = call Fennec.getConfId(module_id);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	fprintf(fp,"\t\treturn msg;\n");
	fprintf(fp,"\t}\n\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_APPLICATION):\n", i);
		fprintf(fp,"\t\treturn signal %s_%s_NetworkSnoop.receive(msg, payload, len);\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->app->lib->full_name);

                fprintf(fp, "\tcase (%d * F_LAYERS + F_NETWORK):\n", i);
		fprintf(fp,"\t\treturn signal %s_%s_MacSnoop.receive(msg, payload, len);\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->net->lib->full_name);
	}
	fprintf(fp,"\tdefault:\n");
	fprintf(fp,"\t\treturn msg;\n\n");
	fprintf(fp,"\t}\n");
	fprintf(fp,"}\n\n");


	/* Radio Only events */



	fprintf(fp,"void granted(uint16_t module_id, uint8_t to_layer) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP granted(%%d, %%d)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_MAC):\n", i);
		fprintf(fp,"\t\treturn signal %s_%s_RadioResource.granted();\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
	}
	fprintf(fp,"\t}\n");
	fprintf(fp,"}\n\n");


	fprintf(fp,"void transmitLoadDone(uint16_t module_id, uint8_t to_layer, message_t *msg, error_t error) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP transmitLoadDone(%%d, %%d, 0x%%1x, %%d)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer, msg, error);\n");
	fprintf(fp,"\tmsg->conf = call Fennec.getConfId(module_id);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_MAC):\n", i);
		fprintf(fp,"\t\treturn signal %s_%s_RadioBuffer.loadDone(msg, error);\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
	}
	fprintf(fp,"\t}\n");
	fprintf(fp,"}\n\n");


	fprintf(fp,"void RadioSend_sendDone(uint16_t module_id, uint8_t to_layer, message_t *msg, error_t error) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP RadioSend_sendDone(%%d, %%d, 0x%%1x, %%d)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer, msg, error);\n");
	fprintf(fp,"\tmsg->conf = call Fennec.getConfId(module_id);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_MAC):\n", i);
		fprintf(fp,"\t\treturn signal %s_%s_RadioSend.sendDone(msg, error);\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
	}
	fprintf(fp,"\t}\n");
	fprintf(fp,"}\n\n");


	fprintf(fp,"void RadioSend_ready(uint16_t module_id, uint8_t to_layer) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP RadioSend_ready(%%d, %%d)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_MAC):\n", i);
		fprintf(fp,"\t\treturn signal %s_%s_RadioSend.ready();\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
	}
	fprintf(fp,"\t}\n");
	fprintf(fp,"}\n\n");


	fprintf(fp,"void RadioState_done(uint16_t module_id, uint8_t to_layer) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP RadioState_done(%%d, %%d)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_MAC):\n", i);
		fprintf(fp,"\t\tsignal %s_%s_RadioState.done();\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
		fprintf(fp,"\t\treturn;\n\n");
	}
	fprintf(fp,"\t}\n");
	fprintf(fp,"}\n\n");


	fprintf(fp,"void RadioCCA_done(uint16_t module_id, uint8_t to_layer, error_t error) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP RadioCCA_done(%%d, %%d, %%d)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer, error);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_MAC):\n", i);
		fprintf(fp,"\t\tsignal %s_%s_RadioCCA.done(error);\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
		fprintf(fp,"\t\treturn;\n\n");
	}
	fprintf(fp,"\t}\n");
	fprintf(fp,"}\n\n");


	fprintf(fp,"message_t* RadioReceive_receive(uint16_t module_id, uint8_t to_layer, message_t* msg) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP RadioReceive_receive(%%d, %%d, 0x%%1x)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer, msg);\n");
	fprintf(fp,"\tif (call Fennec.checkPacket(msg) != SUCCESS) {\n");
	fprintf(fp,"\t\t return msg;\n");
	fprintf(fp,"\t}\n\n");
	fprintf(fp,"\tmsg->conf = call Fennec.getConfId(module_id);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	fprintf(fp,"\t\treturn msg;\n");
	fprintf(fp,"\t}\n\n");

	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_MAC):\n", i);
		fprintf(fp,"\t\treturn signal %s_%s_RadioReceive.receive(msg);\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
	}
	fprintf(fp,"\tdefault:\n");
	fprintf(fp,"\t\treturn msg;\n\n");
	fprintf(fp,"\t}\n");
	fprintf(fp,"}\n\n");


	fprintf(fp,"bool RadioReceive_header(uint16_t module_id, uint8_t to_layer, message_t* msg) {\n");
	fprintf(fp,"\tdbg(\"FennecEngine\", \"FennecEngineP RadioReceive_header(%%d, %%d, 0x%%1x)\",\n");
	fprintf(fp,"\t\t\tmodule_id, to_layer, msg);\n");
	fprintf(fp,"\tif (call Fennec.checkPacket(msg) != SUCCESS) {\n");
	fprintf(fp,"\t\t return 0;\n");
	fprintf(fp,"\t}\n\n");
	fprintf(fp,"\tmsg->conf = call Fennec.getConfId(module_id);\n");
	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	fprintf(fp,"\t\treturn 0;\n");
	fprintf(fp,"\t}\n\n");

	fprintf(fp,"\tswitch( call Fennec.getNextModuleId(module_id, to_layer) ) {\n");
	for( i = 0; i < conf_id_counter; i++ ) {
                fprintf(fp, "\tcase (%d * F_LAYERS + F_MAC):\n", i);
		fprintf(fp,"\t\treturn signal %s_%s_RadioReceive.header(msg);\n\n",
					conftab[i].conf->id->name,
					conftab[i].conf->mac->lib->full_name);
	}
	fprintf(fp,"\tdefault:\n");
	fprintf(fp,"\t\treturn 0;\n\n");
	fprintf(fp,"\t}\n");
	fprintf(fp,"}\n\n");


	struct paramtype *pt;

	/* Interfaces with Applications */


	for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
		if (mp->lib != NULL && mp->lib->path && mp->id > 0 && ((mp->lib->type == TYPE_APPLICATION) || (mp->lib->type == TYPE_EVENT))) {
			fprintf(fp, "\n/* Linking Application %s */\n", mp->lib->full_name);

			fprintf(fp, "\t/* Module Control Interface */\n\n");	

			fprintf(fp, "event void %sControl.startDone(error_t err){\n", mp->lib->full_name);
			fprintf(fp, "\tmodule_startDone(%d, err);\n", mp->id);
			fprintf(fp, "}\n\n");
			fprintf(fp, "event void %sControl.stopDone(error_t err) {\n", mp->lib->full_name);
			fprintf(fp, "\tmodule_stopDone(%d, err);\n", mp->id);
			fprintf(fp, "}\n\n");

			if (mp->lib->type == TYPE_EVENT) {
				fprintf(fp, "\t/* Event Interface */\n\n");	
				fprintf(fp, "event void %sEvent.occured(uint16_t oc) {\n", mp->lib->full_name);
				fprintf(fp, "\tcall Fennec.eventOccured(%d, oc);\n", mp->id);
				fprintf(fp, "}\n\n");
			}

			fprintf(fp, "\t/* Parameter Interface */\n\n");	

			/* check if the interface is empty, if it is add dummy call */
			if (mp->lib->params == NULL) {
				fprintf(fp, "command void %sParams.dummy() {}\n", mp->lib->full_name);
			}

			for(pt = mp->lib->params; pt != NULL; pt = pt->child ) {
				fprintf(fp, "command %s %sParams.get_%s() {\n",
						type_name(pt->type), 
						mp->lib->full_name, 
						pt->name);
				fprintf(fp, "\tstruct %s_params_ptr *params = (struct %s_params_ptr*) (call Fennec.getConfParams(%d)).application;\n", 
							mp->lib->full_name, 
							mp->lib->full_name, 
							mp->id);
				fprintf(fp, "\treturn *(params->%s);\n", pt->name);
				fprintf(fp, "}\n\n");

				fprintf(fp, "command error_t %sParams.set_%s(%s new_%s) {\n",
						mp->lib->full_name, 
						pt->name, 
						type_name(pt->type), 
						pt->name);
				fprintf(fp, "\tstruct %s_params_ptr *params = (struct %s_params_ptr*) (call Fennec.getConfParams(%d)).application;\n", 
							mp->lib->full_name, 
							mp->lib->full_name, 
							mp->id);

				fprintf(fp, "\t*params->%s = new_%s;\n", 
						pt->name,
						pt->name);
				fprintf(fp, "\treturn SUCCESS;\n");
		                fprintf(fp, "}\n\n");
		        }

			fprintf(fp, "command error_t %sNetworkAMSend.send(am_addr_t addr, message_t* msg, uint8_t len) {\n",
						mp->lib->full_name);
			fprintf(fp, "\tdbg(\"FennecEngine\", \"FennecEngineP call %sNetworkAMSend.send()\");\n",
						mp->lib->full_name);
			fprintf(fp, "\treturn AMSend_send(%d, F_NETWORK, addr, msg, len);\n", 
						mp->id);
			fprintf(fp, "}\n\n");

			fprintf(fp, "command error_t %sNetworkAMSend.cancel(message_t* msg) {\n",
						mp->lib->full_name);
			fprintf(fp, "\tdbg(\"FennecEngine\", \"FennecEngineP call %sNetworkAMSend.cancel()\");\n",
						mp->lib->full_name);
			fprintf(fp, "\treturn AMSend_cancel(%d, F_NETWORK, msg);\n",
						mp->id);
			fprintf(fp, "}\n\n");

			fprintf(fp, "command uint8_t %sNetworkAMSend.maxPayloadLength() {\n", mp->lib->full_name);
			fprintf(fp, "\tdbg(\"FennecEngine\", \"FennecEngineP call %sNetworkAMSend.maxPayloadLength()\");\n",
						mp->lib->full_name);
			fprintf(fp, "\treturn AMSend_maxPayloadLength(%d, F_NETWORK);\n", mp->id);
			fprintf(fp, "}\n\n");

			fprintf(fp, "command void* %sNetworkAMSend.getPayload(message_t* msg, uint8_t len) {\n", mp->lib->full_name);
			fprintf(fp, "\tdbg(\"FennecEngine\", \"FennecEngineP call %sNetworkAMSend.getPayload()\");\n",
						mp->lib->full_name);
			fprintf(fp, "\treturn AMSend_getPayload(%d, F_NETWORK, msg, len);\n", mp->id);
			fprintf(fp, "}\n\n");

			fprintf(fp, "command am_addr_t %sNetworkAMPacket.address() {\n", mp->lib->full_name);
			fprintf(fp, "\tdbg(\"FennecEngine\", \"FennecEngineP call %sNetworkAMPacket.address()\");\n",
						mp->lib->full_name);
			fprintf(fp, "\treturn AMPacket_address(%d, F_NETWORK);\n", mp->id);
			fprintf(fp, "}\n\n");

			fprintf(fp, "command am_addr_t %sNetworkAMPacket.destination(message_t* msg) {\n", mp->lib->full_name);
			fprintf(fp, "\tdbg(\"FennecEngine\", \"FennecEngineP call %sNetworkAMPacket.destination()\");\n",
						mp->lib->full_name);
			fprintf(fp, "\treturn AMPacket_destination(%d, F_NETWORK, msg);\n", mp->id);
			fprintf(fp, "}\n\n");

			fprintf(fp, "command am_addr_t %sNetworkAMPacket.source(message_t* msg) {\n", mp->lib->full_name);
			fprintf(fp, "\tdbg(\"FennecEngine\", \"FennecEngineP call %sNetworkAMPacket.source()\");\n",
						mp->lib->full_name);
			fprintf(fp, "\treturn AMPacket_source(%d, F_NETWORK, msg);\n", mp->id);
			fprintf(fp, "}\n\n");

			fprintf(fp, "command void %sNetworkAMPacket.setDestination(message_t* msg, am_addr_t addr) {\n", mp->lib->full_name);
			fprintf(fp, "\tdbg(\"FennecEngine\", \"FennecEngineP call %sNetworkAMPacket.setDestination()\");\n",
						mp->lib->full_name);
			fprintf(fp, "\treturn AMPacket_setDestination(%d, F_NETWORK, msg, addr);\n", mp->id);
			fprintf(fp, "}\n\n");

			fprintf(fp, "command void %sNetworkAMPacket.setSource(message_t* msg, am_addr_t addr) {\n", mp->lib->full_name);
			fprintf(fp, "\tdbg(\"FennecEngine\", \"FennecEngineP call %sNetworkAMPacket.setSource()\");\n",
						mp->lib->full_name);
			fprintf(fp, "\treturn AMPacket_setSource(%d, F_NETWORK, msg, addr);\n", mp->id);
			fprintf(fp, "}\n\n");

			fprintf(fp, "command bool %sNetworkAMPacket.isForMe(message_t* msg) {\n", mp->lib->full_name);
			fprintf(fp, "\tdbg(\"FennecEngine\", \"FennecEngineP call %sNetworkAMPacket.isForMe()\");\n",
						mp->lib->full_name);
			fprintf(fp, "\treturn AMPacket_isForMe(%d, F_NETWORK, msg);\n", mp->id);
			fprintf(fp, "}\n\n");

			fprintf(fp, "command am_id_t %sNetworkAMPacket.type(message_t* msg) {\n", mp->lib->full_name);
			fprintf(fp, "\tdbg(\"FennecEngine\", \"FennecEngineP call %sNetworkAMPacket.type()\");\n",
						mp->lib->full_name);
			fprintf(fp, "\treturn AMPacket_type(%d, F_NETWORK, msg);\n",mp->id);
			fprintf(fp, "}\n\n");

			fprintf(fp, "command void %sNetworkAMPacket.setType(message_t* msg, am_id_t t) {\n", mp->lib->full_name);
			fprintf(fp, "\tdbg(\"FennecEngine\", \"FennecEngineP call %sNetworkAMPacket.setType()\");\n",
						mp->lib->full_name);
			fprintf(fp, "\treturn AMPacket_setType(%d, F_NETWORK, msg, t);\n", mp->id);
			fprintf(fp, "}\n\n");

			fprintf(fp, "command am_group_t %sNetworkAMPacket.group(message_t* msg) {\n", mp->lib->full_name);
			fprintf(fp, "\tdbg(\"FennecEngine\", \"FennecEngineP call %sNetworkAMPacket.group()\");\n",
						mp->lib->full_name);
			fprintf(fp, "\treturn AMPacket_group(%d, F_NETWORK, msg);\n", mp->id);
			fprintf(fp, "}\n\n");

			fprintf(fp, "command void %sNetworkAMPacket.setGroup(message_t* msg, am_group_t grp) {\n", mp->lib->full_name);
			fprintf(fp, "\tdbg(\"FennecEngine\", \"FennecEngineP call %sNetworkAMPacket.setGroup()\");\n",
						mp->lib->full_name);
			fprintf(fp, "\treturn AMPacket_setGroup(%d, F_NETWORK, msg, grp);\n", mp->id);
			fprintf(fp, "}\n\n");

			fprintf(fp, "command am_group_t %sNetworkAMPacket.localGroup() {\n", mp->lib->full_name);
			fprintf(fp, "\tdbg(\"FennecEngine\", \"FennecEngineP call %sNetworkAMPacket.localGroup()\");\n",
						mp->lib->full_name);
			fprintf(fp, "\treturn AMPacket_localGroup(%d, F_NETWORK);\n", mp->id);
			fprintf(fp, "}\n\n");

			fprintf(fp, "command void %sNetworkPacket.clear(message_t* msg) {\n", mp->lib->full_name);
			fprintf(fp, "\tdbg(\"FennecEngine\", \"FennecEngineP call %sNetworkPacket.clear()\");\n",
						mp->lib->full_name);
			fprintf(fp, "\treturn Packet_clear(%d, F_NETWORK, msg);\n", mp->id);
			fprintf(fp, "}\n\n");

			fprintf(fp, "command uint8_t %sNetworkPacket.payloadLength(message_t* msg) {\n", mp->lib->full_name);
			fprintf(fp, "\tdbg(\"FennecEngine\", \"FennecEngineP call %sNetworkPacket.payloadLength()\");\n",
						mp->lib->full_name);
			fprintf(fp, "\treturn Packet_payloadLength(%d, F_NETWORK, msg);\n", mp->id);
			fprintf(fp, "}\n\n");

			fprintf(fp, "command void %sNetworkPacket.setPayloadLength(message_t* msg, uint8_t len) {\n", mp->lib->full_name);
			fprintf(fp, "\tdbg(\"FennecEngine\", \"FennecEngineP call %sNetworkPacket.setPayloadLength()\");\n",
						mp->lib->full_name);
			fprintf(fp, "\treturn Packet_setPayloadLength(%d, F_NETWORK, msg, len);\n", mp->id);
			fprintf(fp, "}\n\n");

			fprintf(fp, "command uint8_t %sNetworkPacket.maxPayloadLength() {\n", mp->lib->full_name);
			fprintf(fp, "\tdbg(\"FennecEngine\", \"FennecEngineP call %sNetworkPacket.maxPayloadLength()\");\n",
						mp->lib->full_name);
			fprintf(fp, "\treturn Packet_maxPayloadLength(%d, F_NETWORK);\n", mp->id);
			fprintf(fp, "}\n\n");

			fprintf(fp, "command void* %sNetworkPacket.getPayload(message_t* msg, uint8_t len) {\n", mp->lib->full_name);
			fprintf(fp, "\tdbg(\"FennecEngine\", \"FennecEngineP call %sNetworkPacket.getPayload()\");\n",
						mp->lib->full_name);
			fprintf(fp, "\treturn Packet_getPayload(%d, F_NETWORK, msg, len);\n", mp->id);
			fprintf(fp, "}\n\n");

			fprintf(fp, "async command error_t %sNetworkPacketAcknowledgements.requestAck( message_t* msg ) {\n", mp->lib->full_name);
			fprintf(fp, "\tdbg(\"FennecEngine\", \"FennecEngineP call %sNetworkPacket.requestAck()\");\n",
						mp->lib->full_name);
			fprintf(fp, "\treturn PacketAcknowledgements_requestAck(%d, F_NETWORK, msg);\n", mp->id);
			fprintf(fp, "}\n\n");

			fprintf(fp, "async command error_t %sNetworkPacketAcknowledgements.noAck( message_t* msg ) {\n", mp->lib->full_name);
			fprintf(fp, "\tdbg(\"FennecEngine\", \"FennecEngineP call %sNetworkPacket.noAck()\");\n",
						mp->lib->full_name);
			fprintf(fp, "\treturn PacketAcknowledgements_noAck(%d, F_NETWORK, msg);\n", mp->id);
			fprintf(fp, "}\n\n");

			fprintf(fp, "async command bool %sNetworkPacketAcknowledgements.wasAcked(message_t* msg) {\n", mp->lib->full_name);
			fprintf(fp, "\tdbg(\"FennecEngine\", \"FennecEngineP call %sNetworkPacket.wasAcked()\");\n",
						mp->lib->full_name);
			fprintf(fp, "\treturn PacketAcknowledgements_wasAcked(%d, F_NETWORK, msg);\n", mp->id);
			fprintf(fp, "}\n\n");
		}
	}

  /* Interfaces with Networks */

	for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
		if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_NETWORK) {
			fprintf(fp, "event void %sControl.startDone(error_t err) {\n", mp->lib->full_name);
			fprintf(fp, "\tmodule_startDone(%d, err);\n", mp->id);
			fprintf(fp, "}\n\n");
			fprintf(fp, "event void %sControl.stopDone(error_t err) {\n", mp->lib->full_name);
			fprintf(fp, "\tmodule_stopDone(%d, err);\n", mp->id);
			fprintf(fp, "}\n\n");


			fprintf(fp, "\t/* Parameter Interfaces */\n\n");	

			/* check if the interface is empty, if it is add dummy call */
			if (mp->lib->params == NULL) {
				fprintf(fp, "command void %sParams.dummy() {}\n", mp->lib->full_name);
			}

			for(pt = mp->lib->params; pt != NULL; pt = pt->child ) {
				fprintf(fp, "command %s %sParams.get_%s() {\n",
						type_name(pt->type), 
						mp->lib->full_name, 
						pt->name);
				fprintf(fp, "\tstruct %s_params_ptr *params = (struct %s_params_ptr*) (call Fennec.getConfParams(%d)).network;\n", 
							mp->lib->full_name, 
							mp->lib->full_name, 
							mp->id);
				fprintf(fp, "\treturn *(params->%s);\n", pt->name);
				fprintf(fp, "}\n\n");
				fprintf(fp, "command error_t %sParams.set_%s(%s new_%s) {\n",
						mp->lib->full_name, 
						pt->name, 
						type_name(pt->type), 
						pt->name);
				fprintf(fp, "\tstruct %s_params_ptr *params = (struct %s_params_ptr*) (call Fennec.getConfParams(%d)).network;\n", 
							mp->lib->full_name, 
							mp->lib->full_name, 
							mp->id);

				fprintf(fp, "\t*params->%s = new_%s;\n", 
						pt->name,
						pt->name);
				fprintf(fp, "\treturn SUCCESS;\n");
		                fprintf(fp, "}\n\n");
		        }


			fprintf(fp, "event void %sNetworkAMSend.sendDone(message_t *msg, error_t error) {\n", mp->lib->full_name);
			fprintf(fp, "\tsendDone(%d, F_APPLICATION, msg, error);\n", mp->id);
			fprintf(fp, "}\n\n");
			fprintf(fp, "event message_t* %sNetworkReceive.receive(message_t *msg, void* payload, uint8_t len) {\n", mp->lib->full_name);
			fprintf(fp, "\treturn receive(%d, F_APPLICATION, msg, payload, len);\n", mp->id);
			fprintf(fp, "}\n\n");
			fprintf(fp, "event message_t* %sNetworkSnoop.receive(message_t *msg, void* payload, uint8_t len) {\n", mp->lib->full_name);
			fprintf(fp, "\treturn snoop(%d, F_APPLICATION, msg, payload, len);\n", mp->id);
			fprintf(fp, "}\n\n");
			fprintf(fp, "command error_t %sMacAMSend.send(am_addr_t addr, message_t* msg, uint8_t len) {\n", mp->lib->full_name);
			fprintf(fp, "\treturn AMSend_send(%d, F_MAC, addr, msg, len);\n", mp->id);
			fprintf(fp, "}\n\n");
			fprintf(fp, "command error_t %sMacAMSend.cancel(message_t* msg) {\n", mp->lib->full_name);
			fprintf(fp, "\treturn AMSend_cancel(%d, F_MAC, msg);\n", mp->id);
			fprintf(fp, "}\n\n");
			fprintf(fp, "command uint8_t %sMacAMSend.maxPayloadLength() {\n", mp->lib->full_name);
			fprintf(fp, "\treturn AMSend_maxPayloadLength(%d, F_MAC);\n", mp->id);
			fprintf(fp, "}\n\n");
			fprintf(fp, "command void* %sMacAMSend.getPayload(message_t* msg, uint8_t len) {\n", mp->lib->full_name);
			fprintf(fp, "\treturn AMSend_getPayload(%d, F_MAC, msg, len);\n", mp->id);
			fprintf(fp, "}\n\n");
			fprintf(fp, "command am_addr_t %sMacAMPacket.address() {\n", mp->lib->full_name);
			fprintf(fp, "\treturn AMPacket_address(%d, F_MAC);\n", mp->id);
			fprintf(fp, "}\n\n");
			fprintf(fp, "command am_addr_t %sMacAMPacket.destination(message_t* msg) {\n", mp->lib->full_name);
			fprintf(fp, "\treturn AMPacket_destination(%d, F_MAC, msg);\n", mp->id);
			fprintf(fp, "}\n\n");
			fprintf(fp, "command am_addr_t %sMacAMPacket.source(message_t* msg) {\n", mp->lib->full_name);
			fprintf(fp, "\treturn AMPacket_source(%d, F_MAC, msg);\n", mp->id);
			fprintf(fp, "}\n");
			fprintf(fp, "command void %sMacAMPacket.setDestination(message_t* msg, am_addr_t addr) {\n", mp->lib->full_name);
			fprintf(fp, "\treturn AMPacket_setDestination(%d, F_MAC, msg, addr);\n", mp->id);
			fprintf(fp, "}\n\n");
			fprintf(fp, "command void %sMacAMPacket.setSource(message_t* msg, am_addr_t addr) {\n", mp->lib->full_name);
			fprintf(fp, "\treturn AMPacket_setSource(%d, F_MAC, msg, addr);\n", mp->id);
			fprintf(fp, "}\n\n");
			fprintf(fp, "command bool %sMacAMPacket.isForMe(message_t* msg) {\n", mp->lib->full_name);
			fprintf(fp, "\treturn AMPacket_isForMe(%d, F_MAC, msg);\n", mp->id);
			fprintf(fp, "}\n\n");
			fprintf(fp, "command am_id_t %sMacAMPacket.type(message_t* msg) {\n", mp->lib->full_name);
			fprintf(fp, "\treturn AMPacket_type(%d, F_MAC, msg);\n", mp->id);
			fprintf(fp, "}\n\n");
			fprintf(fp, "command void %sMacAMPacket.setType(message_t* msg, am_id_t t) {\n", mp->lib->full_name);
			fprintf(fp, "\treturn AMPacket_setType(%d, F_MAC, msg, t);\n", mp->id);
			fprintf(fp, "}\n\n");
			fprintf(fp, "command am_group_t %sMacAMPacket.group(message_t* msg) {\n", mp->lib->full_name);
			fprintf(fp, "\treturn AMPacket_group(%d, F_MAC, msg);\n", mp->id);
			fprintf(fp, "}\n\n");
			fprintf(fp, "command void %sMacAMPacket.setGroup(message_t* msg, am_group_t grp) {\n", mp->lib->full_name);
			fprintf(fp, "\treturn AMPacket_setGroup(%d, F_MAC, msg, grp);\n", mp->id);
			fprintf(fp, "}\n");
			fprintf(fp, "command am_group_t %sMacAMPacket.localGroup() {\n", mp->lib->full_name);
			fprintf(fp, "\treturn AMPacket_localGroup(%d, F_MAC);\n", mp->id);
			fprintf(fp, "}\n\n");
			fprintf(fp, "command void %sMacPacket.clear(message_t* msg) {\n", mp->lib->full_name);
			fprintf(fp, "\treturn Packet_clear(%d, F_MAC, msg);\n", mp->id);
			fprintf(fp, "}\n\n");
			fprintf(fp, "command uint8_t %sMacPacket.payloadLength(message_t* msg) {\n", mp->lib->full_name);
			fprintf(fp, "\treturn Packet_payloadLength(%d, F_MAC, msg);\n", mp->id);
			fprintf(fp, "}\n\n");
			fprintf(fp, "command void %sMacPacket.setPayloadLength(message_t* msg, uint8_t len) {\n", mp->lib->full_name);
			fprintf(fp, "\treturn Packet_setPayloadLength(%d, F_MAC, msg, len);\n", mp->id);
			fprintf(fp, "}\n\n");
			fprintf(fp, "command uint8_t %sMacPacket.maxPayloadLength() {\n", mp->lib->full_name);
			fprintf(fp, "\treturn Packet_maxPayloadLength(%d, F_MAC);\n", mp->id);
			fprintf(fp, "}\n\n");
			fprintf(fp, "command void* %sMacPacket.getPayload(message_t* msg, uint8_t len) {\n", mp->lib->full_name);
			fprintf(fp, "\treturn Packet_getPayload(%d, F_MAC, msg, len);\n", mp->id);
			fprintf(fp, "}\n\n");
			fprintf(fp, "async command error_t %sMacPacketAcknowledgements.requestAck( message_t* msg ) {\n", mp->lib->full_name);
			fprintf(fp, "\treturn PacketAcknowledgements_requestAck(%d, F_MAC, msg);\n", mp->id);
			fprintf(fp, "}\n\n");
			fprintf(fp, "async command error_t %sMacPacketAcknowledgements.noAck( message_t* msg ) {\n", mp->lib->full_name);
			fprintf(fp, "\treturn PacketAcknowledgements_noAck(%d, F_MAC, msg);\n", mp->id);
			fprintf(fp, "}\n\n");
			fprintf(fp, "async command bool %sMacPacketAcknowledgements.wasAcked(message_t* msg) {\n", mp->lib->full_name);
			fprintf(fp, "\treturn PacketAcknowledgements_wasAcked(%d, F_MAC, msg);\n", mp->id);
			fprintf(fp, "}\n\n");

			fprintf(fp, "async command bool %sMacLinkPacketMetadata.highChannelQuality(message_t *msg) {\n", mp->lib->full_name);
			fprintf(fp, "\treturn LinkPacketMetadata_highChannelQuality(%d, F_MAC, msg);\n", mp->id);
			fprintf(fp, "}\n\n");
		}
	}

/* Interfaces with Macs */

	for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
		if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_MAC) {
			fprintf(fp, "event void %sControl.startDone(error_t err) {\n", mp->lib->full_name);
			fprintf(fp, "\tmodule_startDone(%d, err);\n", mp->id);
			fprintf(fp, "}\n\n");
			fprintf(fp, "event void %sControl.stopDone(error_t err) {\n", mp->lib->full_name);
			fprintf(fp, "\tmodule_stopDone(%d, err);\n", mp->id);
			fprintf(fp, "}\n\n");


			fprintf(fp, "\t/* Parameter Interfaces */\n\n");	

			/* check if the interface is empty, if it is add dummy call */
			if (mp->lib->params == NULL) {
				fprintf(fp, "command void %sParams.dummy() {}\n", mp->lib->full_name);
			}

			for(pt = mp->lib->params; pt != NULL; pt = pt->child ) {
				fprintf(fp, "command %s %sParams.get_%s() {\n",
						type_name(pt->type), 
						mp->lib->full_name, 
						pt->name);
				fprintf(fp, "\tstruct %s_params_ptr *params = (struct %s_params_ptr*) (call Fennec.getConfParams(%d)).mac;\n", 
							mp->lib->full_name, 
							mp->lib->full_name, 
							mp->id);
				fprintf(fp, "\treturn *(params->%s);\n", pt->name);
				fprintf(fp, "}\n\n");
				fprintf(fp, "command error_t %sParams.set_%s(%s new_%s) {\n",
						mp->lib->full_name, 
						pt->name, 
						type_name(pt->type), 
						pt->name);
				fprintf(fp, "\tstruct %s_params_ptr *params = (struct %s_params_ptr*) (call Fennec.getConfParams(%d)).mac;\n", 
							mp->lib->full_name, 
							mp->lib->full_name, 
							mp->id);
				fprintf(fp, "\t*params->%s = new_%s;\n", 
						pt->name,
						pt->name);
				fprintf(fp, "\treturn SUCCESS;\n");
		                fprintf(fp, "}\n\n");
		        }


			fprintf(fp, "event void %sMacAMSend.sendDone(message_t *msg, error_t error) {\n", mp->lib->full_name);
			fprintf(fp, "\tsendDone(%d, F_NETWORK, msg, error);\n", mp->id);
			fprintf(fp, "}\n\n");
			fprintf(fp, "event message_t* %sMacReceive.receive(message_t *msg, void* payload, uint8_t len) {\n", mp->lib->full_name);
			fprintf(fp, "\treturn receive(%d, F_NETWORK, msg, payload, len);\n", mp->id);
			fprintf(fp, "}\n\n");
			fprintf(fp, "event message_t* %sMacSnoop.receive(message_t *msg, void* payload, uint8_t len) {\n", mp->lib->full_name);
			fprintf(fp, "\treturn snoop(%d, F_NETWORK, msg, payload, len);\n", mp->id);
			fprintf(fp, "}\n\n");


			fprintf(fp, "async command error_t %sRadioResource.request() {\n", mp->lib->full_name);
			fprintf(fp, "\treturn RadioResource_request(%d, F_RADIO);\n", mp->id);
			fprintf(fp, "}\n\n");
			fprintf(fp, "async command error_t %sRadioResource.immediateRequest() {\n", mp->lib->full_name);
			fprintf(fp, "\treturn RadioResource_immediateRequest(%d, F_RADIO);\n", mp->id);
			fprintf(fp, "}\n\n");
			fprintf(fp, "async command error_t %sRadioResource.release() {\n", mp->lib->full_name);
			fprintf(fp, "\treturn RadioResource_release(%d, F_RADIO);\n", mp->id);
			fprintf(fp, "}\n\n");
			fprintf(fp, "async command error_t %sRadioResource.isOwner() {\n", mp->lib->full_name);
			fprintf(fp, "\treturn RadioResource_isOwner(%d, F_RADIO);\n", mp->id);
			fprintf(fp, "}\n\n");


			fprintf(fp, "async command error_t %sRadioSend.send(message_t* msg, bool useCca) {\n", mp->lib->full_name);
			fprintf(fp, "\treturn RadioSend_send(%d, F_RADIO, msg, useCca);\n", mp->id);
			fprintf(fp, "}\n\n");


			fprintf(fp, "async command uint8_t %sRadioPacket.maxPayloadLength() {\n", mp->lib->full_name);
			fprintf(fp, "\treturn RadioPacket_maxPayloadLength(%d, F_RADIO);\n", mp->id);
			fprintf(fp, "}\n\n");
			fprintf(fp, "async command uint8_t %sRadioPacket.headerLength(message_t* msg) {\n", mp->lib->full_name);
			fprintf(fp, "\treturn RadioPacket_headerLength(%d, F_RADIO, msg);\n", mp->id);
			fprintf(fp, "}\n\n");
			fprintf(fp, "async command uint8_t %sRadioPacket.payloadLength(message_t* msg) {\n", mp->lib->full_name);
			fprintf(fp, "\treturn RadioPacket_payloadLength(%d, F_RADIO, msg);\n", mp->id);
			fprintf(fp, "}\n\n");
			fprintf(fp, "async command void %sRadioPacket.setPayloadLength(message_t* msg, uint8_t length) {\n", mp->lib->full_name);
			fprintf(fp, "\treturn RadioPacket_setPayloadLength(%d, F_RADIO, msg, length);\n", mp->id);
			fprintf(fp, "}\n\n");
			fprintf(fp, "async command uint8_t %sRadioPacket.metadataLength(message_t* msg) {\n", mp->lib->full_name);
			fprintf(fp, "\treturn RadioPacket_metadataLength(%d, F_RADIO, msg);\n", mp->id);
			fprintf(fp, "}\n\n");
			fprintf(fp, "async command void %sRadioPacket.clear(message_t* msg) {\n", mp->lib->full_name);
			fprintf(fp, "\treturn RadioPacket_clear(%d, F_RADIO, msg);\n", mp->id);
			fprintf(fp, "}\n\n");


			fprintf(fp, "async command error_t %sRadioBuffer.load(message_t* msg) {\n", mp->lib->full_name);
			fprintf(fp, "\treturn RadioBuffer_load(%d, F_RADIO, msg);\n", mp->id);
			fprintf(fp, "}\n\n");


			fprintf(fp, "async command bool %sPacketTransmitPower.isSet(message_t *msg) {\n", mp->lib->full_name);
			fprintf(fp, "\treturn PacketTransmitPower_isSet(%d, F_RADIO, msg);\n", mp->id);
			fprintf(fp, "}\n\n");
			fprintf(fp, "async command uint8_t %sPacketTransmitPower.get(message_t *msg) {\n", mp->lib->full_name);
			fprintf(fp, "\treturn PacketTransmitPower_get(%d, F_RADIO, msg);\n", mp->id);
			fprintf(fp, "}\n\n");
			fprintf(fp, "async command void %sPacketTransmitPower.clear(message_t *msg) {\n", mp->lib->full_name);
			fprintf(fp, "\treturn PacketTransmitPower_clear(%d, F_RADIO, msg);\n", mp->id);
			fprintf(fp, "}\n\n");
			fprintf(fp, "async command void %sPacketTransmitPower.set(message_t *msg, uint8_t value) {\n", mp->lib->full_name);
			fprintf(fp, "\treturn PacketTransmitPower_set(%d, F_RADIO, msg, value);\n", mp->id);
			fprintf(fp, "}\n\n");


			fprintf(fp, "async command bool %sPacketRSSI.isSet(message_t *msg) {\n", mp->lib->full_name);
			fprintf(fp, "\treturn PacketRSSI_isSet(%d, F_RADIO, msg);\n", mp->id);
			fprintf(fp, "}\n\n");
			fprintf(fp, "async command uint8_t %sPacketRSSI.get(message_t *msg) {\n", mp->lib->full_name);
			fprintf(fp, "\treturn PacketRSSI_get(%d, F_RADIO, msg);\n", mp->id);
			fprintf(fp, "}\n\n");
			fprintf(fp, "async command void %sPacketRSSI.clear(message_t *msg) {\n", mp->lib->full_name);
			fprintf(fp, "\treturn PacketRSSI_clear(%d, F_RADIO, msg);\n", mp->id);
			fprintf(fp, "}\n\n");
			fprintf(fp, "async command void %sPacketRSSI.set(message_t *msg, uint8_t value) {\n", mp->lib->full_name);
			fprintf(fp, "\treturn PacketRSSI_set(%d, F_RADIO, msg, value);\n", mp->id);
			fprintf(fp, "}\n\n");


			fprintf(fp, "async command bool %sPacketTimeSync.isSet(message_t *msg) {\n", mp->lib->full_name);
			fprintf(fp, "\treturn PacketTimeSync_isSet(%d, F_RADIO, msg);\n", mp->id);
			fprintf(fp, "}\n\n");
			fprintf(fp, "async command uint32_t %sPacketTimeSync.get(message_t *msg) {\n", mp->lib->full_name);
			fprintf(fp, "\treturn PacketTimeSync_get(%d, F_RADIO, msg);\n", mp->id);
			fprintf(fp, "}\n\n");
			fprintf(fp, "async command void %sPacketTimeSync.clear(message_t *msg) {\n", mp->lib->full_name);
			fprintf(fp, "\treturn PacketTimeSync_clear(%d, F_RADIO, msg);\n", mp->id);
			fprintf(fp, "}\n\n");
			fprintf(fp, "async command void %sPacketTimeSync.set(message_t *msg, uint32_t value) {\n", mp->lib->full_name);
			fprintf(fp, "\treturn PacketTimeSync_set(%d, F_RADIO, msg, value);\n", mp->id);
			fprintf(fp, "}\n\n");


			fprintf(fp, "async command bool %sPacketLinkQuality.isSet(message_t *msg) {\n", mp->lib->full_name);
			fprintf(fp, "\treturn PacketLinkQuality_isSet(%d, F_RADIO, msg);\n", mp->id);
			fprintf(fp, "}\n\n");
			fprintf(fp, "async command uint8_t %sPacketLinkQuality.get(message_t *msg) {\n", mp->lib->full_name);
			fprintf(fp, "\treturn PacketLinkQuality_get(%d, F_RADIO, msg);\n", mp->id);
			fprintf(fp, "}\n\n");
			fprintf(fp, "async command void %sPacketLinkQuality.clear(message_t *msg) {\n", mp->lib->full_name);
			fprintf(fp, "\treturn PacketLinkQuality_clear(%d, F_RADIO, msg);\n", mp->id);
			fprintf(fp, "}\n\n");
			fprintf(fp, "async command void %sPacketLinkQuality.set(message_t *msg, uint8_t value) {\n", mp->lib->full_name);
			fprintf(fp, "\treturn PacketLinkQuality_set(%d, F_RADIO, msg, value);\n", mp->id);
			fprintf(fp, "}\n\n");


			fprintf(fp, "async command error_t %sRadioCCA.request() {\n", mp->lib->full_name);
			fprintf(fp, "\treturn RadioCCA_request(%d, F_RADIO);\n", mp->id);
			fprintf(fp, "}\n\n");


			fprintf(fp, "command error_t %sRadioState.turnOff() {\n", mp->lib->full_name);
			fprintf(fp, "\treturn RadioState_turnOff(%d, F_RADIO);\n", mp->id);
			fprintf(fp, "}\n\n");
			fprintf(fp, "command error_t %sRadioState.standby() {\n", mp->lib->full_name);
			fprintf(fp, "\treturn RadioState_standby(%d, F_RADIO);\n", mp->id);
			fprintf(fp, "}\n\n");
			fprintf(fp, "command error_t %sRadioState.turnOn() {\n", mp->lib->full_name);
			fprintf(fp, "\treturn RadioState_turnOn(%d, F_RADIO);\n", mp->id);
			fprintf(fp, "}\n\n");
			fprintf(fp, "command error_t %sRadioState.setChannel(uint8_t channel) {\n", mp->lib->full_name);
			fprintf(fp, "\treturn RadioState_setChannel(%d, F_RADIO, channel);\n", mp->id);
			fprintf(fp, "}\n\n");
			fprintf(fp, "command uint8_t %sRadioState.getChannel() {\n", mp->lib->full_name);
			fprintf(fp, "\treturn RadioState_getChannel(%d, F_RADIO);\n", mp->id);
			fprintf(fp, "}\n\n");

			fprintf(fp, "async command bool %sRadioLinkPacketMetadata.highChannelQuality(message_t *msg) {\n", mp->lib->full_name);
			fprintf(fp, "\treturn LinkPacketMetadata_highChannelQuality(%d, F_RADIO, msg);\n", mp->id);
			fprintf(fp, "}\n\n");


		}
	}

/* Interfaces with Radios */

	for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
		if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_RADIO) {
			fprintf(fp, "event void %sControl.startDone(error_t err) {\n", mp->lib->full_name);
			fprintf(fp, "\tmodule_startDone(%d, err);\n", mp->id);
			fprintf(fp, "}\n\n");
			fprintf(fp, "event void %sControl.stopDone(error_t err) {\n", mp->lib->full_name);
			fprintf(fp, "\tmodule_stopDone(%d, err);\n", mp->id);
			fprintf(fp, "}\n\n");


			fprintf(fp, "\t/* Parameter Interfaces */\n\n");	

			/* check if the interface is empty, if it is add dummy call */
			if (mp->lib->params == NULL) {
				fprintf(fp, "command void %sParams.dummy() {}\n", mp->lib->full_name);
			}

			for(pt = mp->lib->params; pt != NULL; pt = pt->child ) {
				fprintf(fp, "command %s %sParams.get_%s() {\n",
						type_name(pt->type), 
						mp->lib->full_name, 
						pt->name);
				fprintf(fp, "\tstruct %s_params_ptr *params = (struct %s_params_ptr*) (call Fennec.getConfParams(%d)).radio;\n", 
							mp->lib->full_name, 
							mp->lib->full_name, 
							mp->id);
				fprintf(fp, "\treturn *(params->%s);\n", pt->name);
				fprintf(fp, "}\n\n");
				fprintf(fp, "command error_t %sParams.set_%s(%s new_%s) {\n",
						mp->lib->full_name, 
						pt->name, 
						type_name(pt->type), 
						pt->name);
				fprintf(fp, "\tstruct %s_params_ptr *params = (struct %s_params_ptr*) (call Fennec.getConfParams(%d)).radio;\n", 
							mp->lib->full_name, 
							mp->lib->full_name, 
							mp->id);
				fprintf(fp, "\t*params->%s = new_%s;\n", 
						pt->name,
						pt->name);
				fprintf(fp, "\treturn SUCCESS;\n");
		                fprintf(fp, "}\n\n");
		        }


			fprintf(fp, "async event message_t* %sRadioReceive.receive(message_t *msg) {\n", mp->lib->full_name);
			fprintf(fp, "\treturn RadioReceive_receive(%d, F_MAC, msg);\n", mp->id);
			fprintf(fp, "}\n\n");

			fprintf(fp, "async event bool %sRadioReceive.header(message_t *msg) {\n", mp->lib->full_name);
			fprintf(fp, "\treturn RadioReceive_header(%d, F_MAC, msg);\n", mp->id);
			fprintf(fp, "}\n\n");


			fprintf(fp, "event void %sRadioResource.granted() {\n", mp->lib->full_name);
			fprintf(fp, "\treturn granted(%d, F_MAC);\n", mp->id);
			fprintf(fp, "}\n\n");

			fprintf(fp, "async event void %sRadioBuffer.loadDone(message_t* msg, error_t error) {\n", mp->lib->full_name);
			fprintf(fp, "\treturn transmitLoadDone(%d, F_MAC, msg, error);\n", mp->id);
			fprintf(fp, "}\n\n");

			fprintf(fp, "async event void %sRadioSend.sendDone(message_t *msg, error_t error) {\n", mp->lib->full_name);
			fprintf(fp, "\treturn RadioSend_sendDone(%d, F_MAC, msg, error);\n", mp->id);
			fprintf(fp, "}\n\n");
			fprintf(fp, "async event void %sRadioSend.ready() {\n", mp->lib->full_name);
			fprintf(fp, "\treturn RadioSend_ready(%d, F_MAC);\n", mp->id);
			fprintf(fp, "}\n\n");

			fprintf(fp, "event void %sRadioState.done() {\n", mp->lib->full_name);
			fprintf(fp, "\treturn RadioState_done(%d, F_MAC);\n", mp->id);
			fprintf(fp, "}\n\n");

			fprintf(fp, "async event void %sRadioCCA.done(error_t error) {\n", mp->lib->full_name);
			fprintf(fp, "\treturn RadioCCA_done(%d, F_MAC, error);\n", mp->id);
			fprintf(fp, "}\n\n");
		}
	}

	fprintf(fp, "\n}\n");
	fclose(fp);
	free(full_path);
}

