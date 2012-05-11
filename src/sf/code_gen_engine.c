#include "code_gen.h"

void generateFennecEngineC() {

  struct modtab *mp;
  FILE *fp_engineC = fopen(engineC, "w");

  if (fp_engineC == NULL) {
    fprintf(stderr, "You do not have a permission to write into file: %s\n", engineC);
    exit(1);
  }

  fprintf(fp_engineC, "/* Swift Fox generated code for Fennec Fox Application configuration */\n");
  fprintf(fp_engineC, "\n#include <Fennec.h>\n\n");
  fprintf(fp_engineC, "configuration FennecEngineC {\n");
  fprintf(fp_engineC, "  provides interface Mgmt;\n");
  fprintf(fp_engineC, "}\n\n");
  fprintf(fp_engineC, "implementation {\n\n");
  fprintf(fp_engineC, "  components FennecEngineP;\n");
  fprintf(fp_engineC, "  Mgmt = FennecEngineP.Mgmt;\n");

  fprintf(fp_engineC, "  components new TimerMilliC() as Timer;\n");
  fprintf(fp_engineC, "  FennecEngineP.Timer -> Timer;\n\n");

  fprintf(fp_engineC, "  components EventsC;\n");
  fprintf(fp_engineC, "  FennecEngineP.EventsMgmt-> EventsC.Mgmt;\n\n");

  fprintf(fp_engineC, "  /* Defined and linked applications */\n\n");

  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_APPLICATION) {
      fprintf(fp_engineC, "  components %s;\n", mp->lib->full_name);
      fprintf(fp_engineC, "  FennecEngineP.%sControl -> %s;\n", mp->lib->full_name, mp->lib->full_name);
      fprintf(fp_engineC, "  FennecEngineP.%sNetworkAMSend <- %s.NetworkAMSend;\n", mp->lib->full_name, mp->lib->full_name);
      fprintf(fp_engineC, "  FennecEngineP.%sNetworkReceive <- %s.NetworkReceive;\n", mp->lib->full_name, mp->lib->full_name);
      fprintf(fp_engineC, "  FennecEngineP.%sNetworkSnoop <- %s.NetworkSnoop;\n", mp->lib->full_name, mp->lib->full_name);
      fprintf(fp_engineC, "  FennecEngineP.%sNetworkPacket <- %s.NetworkPacket;\n", mp->lib->full_name, mp->lib->full_name);
      fprintf(fp_engineC, "  FennecEngineP.%sNetworkAMPacket <- %s.NetworkAMPacket;\n", mp->lib->full_name, mp->lib->full_name);
      fprintf(fp_engineC, "  FennecEngineP.%sNetworkPacketAcknowledgements <- %s.NetworkPacketAcknowledgements;\n", 
									mp->lib->full_name, mp->lib->full_name);
      fprintf(fp_engineC, "  FennecEngineP.%sNetworkStatus <- %s.NetworkStatus;\n\n", mp->lib->full_name, mp->lib->full_name);
    
    }
  }

  fprintf(fp_engineC, "  /* Defined and linked network modules */\n\n");

  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_NETWORK) {
      fprintf(fp_engineC, "\n  components %s as %s;\n", mp->lib->full_name, mp->lib->full_name);
      fprintf(fp_engineC, "  FennecEngineP.%sControl -> %s;\n", mp->lib->full_name, mp->lib->full_name);
      fprintf(fp_engineC, "  FennecEngineP.%sNetworkAMSend -> %s.NetworkAMSend;\n", mp->lib->full_name, mp->lib->full_name);
      fprintf(fp_engineC, "  FennecEngineP.%sNetworkReceive -> %s.NetworkReceive;\n", mp->lib->full_name, mp->lib->full_name);
      fprintf(fp_engineC, "  FennecEngineP.%sNetworkSnoop -> %s.NetworkSnoop;\n", mp->lib->full_name, mp->lib->full_name);
      fprintf(fp_engineC, "  FennecEngineP.%sNetworkAMPacket -> %s.NetworkAMPacket;\n", mp->lib->full_name, mp->lib->full_name);
      fprintf(fp_engineC, "  FennecEngineP.%sNetworkPacket -> %s.NetworkPacket;\n", mp->lib->full_name, mp->lib->full_name);
      fprintf(fp_engineC, "  FennecEngineP.%sNetworkPacketAcknowledgements -> %s.NetworkPacketAcknowledgements;\n", 
											mp->lib->full_name, mp->lib->full_name);
      fprintf(fp_engineC, "  FennecEngineP.%sNetworkStatus -> %s.NetworkStatus;\n", mp->lib->full_name, mp->lib->full_name);
      fprintf(fp_engineC, "  FennecEngineP.%sMacAMSend <- %s.MacAMSend;\n", mp->lib->full_name, mp->lib->full_name);
      fprintf(fp_engineC, "  FennecEngineP.%sMacReceive <- %s.MacReceive;\n", mp->lib->full_name, mp->lib->full_name);
      fprintf(fp_engineC, "  FennecEngineP.%sMacSnoop <- %s.MacSnoop;\n", mp->lib->full_name, mp->lib->full_name);
      fprintf(fp_engineC, "  FennecEngineP.%sMacAMPacket <- %s.MacAMPacket;\n", mp->lib->full_name, mp->lib->full_name);
      fprintf(fp_engineC, "  FennecEngineP.%sMacPacket <- %s.MacPacket;\n", mp->lib->full_name, mp->lib->full_name);
      fprintf(fp_engineC, "  FennecEngineP.%sMacPacketAcknowledgements <- %s.MacPacketAcknowledgements;\n", mp->lib->full_name, mp->lib->full_name);
      fprintf(fp_engineC, "  FennecEngineP.%sMacStatus <- %s.MacStatus;\n\n", mp->lib->full_name, mp->lib->full_name);
    }
  }

  /* ControlUnit is wired at the Network Layer, thou it is not expected to provide any service to any application */

  fprintf(fp_engineC, "  /* Here we wire the ControlUnit */\n\n");
  fprintf(fp_engineC, "  components ControlUnitC;\n");
  fprintf(fp_engineC, "  FennecEngineP.ControlUnit_MacAMSend <- ControlUnitC.MacAMSend;\n");
  fprintf(fp_engineC, "  FennecEngineP.ControlUnit_MacReceive <- ControlUnitC.MacReceive;\n");
  fprintf(fp_engineC, "  FennecEngineP.ControlUnit_MacSnoop <- ControlUnitC.MacSnoop;\n");
  fprintf(fp_engineC, "  FennecEngineP.ControlUnit_MacAMPacket <- ControlUnitC.MacAMPacket;\n");
  fprintf(fp_engineC, "  FennecEngineP.ControlUnit_MacPacket <- ControlUnitC.MacPacket;\n");
  fprintf(fp_engineC, "  FennecEngineP.ControlUnit_MacPacketAcknowledgements <- ControlUnitC.MacPacketAcknowledgements;\n");
  fprintf(fp_engineC, "  FennecEngineP.ControlUnit_MacStatus <- ControlUnitC.MacStatus;\n\n");

  fprintf(fp_engineC, "  /* Defined and linked mac */\n\n");

  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_MAC) {
      fprintf(fp_engineC, "\n  components %s as %s;\n", mp->lib->full_name, mp->lib->full_name);
      fprintf(fp_engineC, "  FennecEngineP.%sControl -> %s;\n", mp->lib->full_name, mp->lib->full_name);
      fprintf(fp_engineC, "  FennecEngineP.%sMacAMSend -> %s.MacAMSend;\n", mp->lib->full_name, mp->lib->full_name);
      fprintf(fp_engineC, "  FennecEngineP.%sMacReceive -> %s.MacReceive;\n", mp->lib->full_name, mp->lib->full_name);
      fprintf(fp_engineC, "  FennecEngineP.%sMacSnoop -> %s.MacSnoop;\n", mp->lib->full_name, mp->lib->full_name);
      fprintf(fp_engineC, "  FennecEngineP.%sMacPacket -> %s.MacPacket;\n", mp->lib->full_name, mp->lib->full_name);
      fprintf(fp_engineC, "  FennecEngineP.%sMacAMPacket -> %s.MacAMPacket;\n", mp->lib->full_name, mp->lib->full_name);
      fprintf(fp_engineC, "  FennecEngineP.%sMacPacketAcknowledgements -> %s.MacPacketAcknowledgements;\n", mp->lib->full_name, mp->lib->full_name);
      fprintf(fp_engineC, "  FennecEngineP.%sMacStatus -> %s.MacStatus;\n", mp->lib->full_name, mp->lib->full_name);
      fprintf(fp_engineC, "  FennecEngineP.%sRadioAMSend <- %s.RadioAMSend;\n", mp->lib->full_name, mp->lib->full_name);
      fprintf(fp_engineC, "  FennecEngineP.%sRadioReceive <- %s.RadioReceive;\n", mp->lib->full_name, mp->lib->full_name);
      fprintf(fp_engineC, "  FennecEngineP.%sRadioSnoop <- %s.RadioSnoop;\n", mp->lib->full_name, mp->lib->full_name);
      fprintf(fp_engineC, "  FennecEngineP.%sRadioPacket <- %s.RadioPacket;\n", mp->lib->full_name, mp->lib->full_name);
      fprintf(fp_engineC, "  FennecEngineP.%sRadioAMPacket <- %s.RadioAMPacket;\n", mp->lib->full_name, mp->lib->full_name);
      fprintf(fp_engineC, "  FennecEngineP.%sRadioPacketAcknowledgements <- %s.RadioPacketAcknowledgements;\n", mp->lib->full_name, mp->lib->full_name);
      fprintf(fp_engineC, "  FennecEngineP.%sRadioStatus <- %s.RadioStatus;\n\n", mp->lib->full_name, mp->lib->full_name);
    }
  }

  fprintf(fp_engineC, "  /* Defined and linked radios */\n\n");

  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_RADIO) {
      fprintf(fp_engineC, "\n  components %s as %s;\n", mp->lib->full_name, mp->lib->full_name);
      fprintf(fp_engineC, "  FennecEngineP.%sControl -> %s;\n", mp->lib->full_name, mp->lib->full_name);
      fprintf(fp_engineC, "  FennecEngineP.%sRadioAMSend -> %s.RadioAMSend;\n", mp->lib->full_name, mp->lib->full_name);
      fprintf(fp_engineC, "  FennecEngineP.%sRadioReceive -> %s.RadioReceive;\n", mp->lib->full_name, mp->lib->full_name);
      fprintf(fp_engineC, "  FennecEngineP.%sRadioSnoop -> %s.RadioSnoop;\n", mp->lib->full_name, mp->lib->full_name);
      fprintf(fp_engineC, "  FennecEngineP.%sRadioPacket -> %s.RadioPacket;\n", mp->lib->full_name, mp->lib->full_name);
      fprintf(fp_engineC, "  FennecEngineP.%sRadioAMPacket -> %s.RadioAMPacket;\n", mp->lib->full_name, mp->lib->full_name);
      fprintf(fp_engineC, "  FennecEngineP.%sRadioPacketAcknowledgements -> %s.RadioPacketAcknowledgements;\n", mp->lib->full_name, mp->lib->full_name);
      fprintf(fp_engineC, "  FennecEngineP.%sRadioStatus -> %s.RadioStatus;\n\n", mp->lib->full_name, mp->lib->full_name);
    }
  }


  fprintf(fp_engineC, "\n}\n");
  fclose(fp_engineC);
}

void generateFennecEngineP() {

  struct modtab *mp;
  FILE *fp_engineM = fopen(engineM, "w");

  if (fp_engineM == NULL) {
    fprintf(stderr, "You do not have a permission to write into file: %s\n", engineM);
    exit(1);
  }

  fprintf(fp_engineM, "/* Swift Fox generated code for Fennec Fox Application module */\n");
  fprintf(fp_engineM, "#include <Fennec.h>\n");
  fprintf(fp_engineM, "#include \"engine.h\"\n");
  fprintf(fp_engineM, "#define MODULE_RESPONSE_DELAY    200\n\n");
  fprintf(fp_engineM, "module FennecEngineP {\n\n");
  fprintf(fp_engineM, "  provides interface Mgmt;\n");
  fprintf(fp_engineM, "  provides interface Module;\n\n");

  fprintf(fp_engineM, "  uses interface Timer<TMilli>;\n");
  fprintf(fp_engineM, "  uses interface Mgmt as EventsMgmt;\n\n");

  fprintf(fp_engineM, "  /* Application Modules */\n\n");

  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_APPLICATION) {
      fprintf(fp_engineM, "  /* Application  Module: %s */\n", mp->lib->full_name);
      fprintf(fp_engineM, "  uses interface Mgmt as %sControl;\n", mp->lib->full_name);
      fprintf(fp_engineM, "  provides interface AMSend as %sNetworkAMSend;\n", mp->lib->full_name);
      fprintf(fp_engineM, "  provides interface Receive as %sNetworkReceive;\n", mp->lib->full_name);
      fprintf(fp_engineM, "  provides interface Receive as %sNetworkSnoop;\n", mp->lib->full_name);
      fprintf(fp_engineM, "  provides interface Packet as %sNetworkPacket;\n", mp->lib->full_name);
      fprintf(fp_engineM, "  provides interface AMPacket as %sNetworkAMPacket;\n", mp->lib->full_name);
      fprintf(fp_engineM, "  provides interface PacketAcknowledgements as %sNetworkPacketAcknowledgements;\n", mp->lib->full_name);
      fprintf(fp_engineM, "  provides interface ModuleStatus as %sNetworkStatus;\n\n", mp->lib->full_name);
    }
  }

  fprintf(fp_engineM, "  /* Network Modules */\n\n");

  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_NETWORK) {
      fprintf(fp_engineM, "  /* Network Module: %s */\n", mp->lib->full_name);
      fprintf(fp_engineM, "  uses interface Mgmt as %sControl;\n", mp->lib->full_name);
      fprintf(fp_engineM, "  uses interface AMSend as %sNetworkAMSend;\n", mp->lib->full_name);
      fprintf(fp_engineM, "  uses interface Receive as %sNetworkReceive;\n", mp->lib->full_name);
      fprintf(fp_engineM, "  uses interface Receive as %sNetworkSnoop;\n", mp->lib->full_name);
      fprintf(fp_engineM, "  uses interface AMPacket as %sNetworkAMPacket;\n", mp->lib->full_name);
      fprintf(fp_engineM, "  uses interface Packet as %sNetworkPacket;\n", mp->lib->full_name);
      fprintf(fp_engineM, "  uses interface PacketAcknowledgements as %sNetworkPacketAcknowledgements;\n", mp->lib->full_name);
      fprintf(fp_engineM, "  uses interface ModuleStatus as %sNetworkStatus;\n", mp->lib->full_name);
      fprintf(fp_engineM, "  provides interface AMSend as %sMacAMSend;\n", mp->lib->full_name);
      fprintf(fp_engineM, "  provides interface Receive as %sMacReceive;\n", mp->lib->full_name);
      fprintf(fp_engineM, "  provides interface Receive as %sMacSnoop;\n", mp->lib->full_name);
      fprintf(fp_engineM, "  provides interface Packet as %sMacPacket;\n", mp->lib->full_name);
      fprintf(fp_engineM, "  provides interface AMPacket as %sMacAMPacket;\n", mp->lib->full_name);
      fprintf(fp_engineM, "  provides interface PacketAcknowledgements as %sMacPacketAcknowledgements;\n", mp->lib->full_name);
      fprintf(fp_engineM, "  provides interface ModuleStatus as %sMacStatus;\n\n", mp->lib->full_name);
    }
  }

  /* ControlUnit is wired at the Network Layer, thou it is not expected to provide any service to any application */

  fprintf(fp_engineM, "  /* Here we wire the ControlUnit */\n\n");
  fprintf(fp_engineM, "  provides interface AMSend as ControlUnit_MacAMSend;\n");
  fprintf(fp_engineM, "  provides interface Receive as ControlUnit_MacReceive;\n");
  fprintf(fp_engineM, "  provides interface Receive as ControlUnit_MacSnoop;\n");
  fprintf(fp_engineM, "  provides interface Packet as ControlUnit_MacPacket;\n");
  fprintf(fp_engineM, "  provides interface AMPacket as ControlUnit_MacAMPacket;\n");
  fprintf(fp_engineM, "  provides interface PacketAcknowledgements as ControlUnit_MacPacketAcknowledgements;\n");
  fprintf(fp_engineM, "  provides interface ModuleStatus as ControlUnit_MacStatus;\n\n");


  fprintf(fp_engineM, "  /* MAC Modules */\n\n");

  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_MAC) {
      fprintf(fp_engineM, "  /* MAC Module: %s */\n", mp->lib->full_name);
      fprintf(fp_engineM, "  uses interface Mgmt as %sControl;\n", mp->lib->full_name);
      fprintf(fp_engineM, "  uses interface AMSend as %sMacAMSend;\n", mp->lib->full_name);
      fprintf(fp_engineM, "  uses interface Receive as %sMacReceive;\n", mp->lib->full_name);
      fprintf(fp_engineM, "  uses interface Receive as %sMacSnoop;\n", mp->lib->full_name);
      fprintf(fp_engineM, "  uses interface Packet as %sMacPacket;\n", mp->lib->full_name);
      fprintf(fp_engineM, "  uses interface AMPacket as %sMacAMPacket;\n", mp->lib->full_name);
      fprintf(fp_engineM, "  uses interface PacketAcknowledgements as %sMacPacketAcknowledgements;\n", mp->lib->full_name);
      fprintf(fp_engineM, "  uses interface ModuleStatus as %sMacStatus;\n", mp->lib->full_name);
      fprintf(fp_engineM, "  provides interface AMSend as %sRadioAMSend;\n", mp->lib->full_name);
      fprintf(fp_engineM, "  provides interface Receive as %sRadioReceive;\n", mp->lib->full_name);
      fprintf(fp_engineM, "  provides interface Receive as %sRadioSnoop;\n", mp->lib->full_name);
      fprintf(fp_engineM, "  provides interface Packet as %sRadioPacket;\n", mp->lib->full_name);
      fprintf(fp_engineM, "  provides interface AMPacket as %sRadioAMPacket;\n", mp->lib->full_name);
      fprintf(fp_engineM, "  provides interface PacketAcknowledgements as %sRadioPacketAcknowledgements;\n", mp->lib->full_name);
      fprintf(fp_engineM, "  provides interface ModuleStatus as %sRadioStatus;\n\n", mp->lib->full_name);
    }
  }

  fprintf(fp_engineM, "  /* Radio Modules */\n\n");

  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_RADIO) {
      fprintf(fp_engineM, "  /* Radio Module: %s */\n", mp->lib->full_name);
      fprintf(fp_engineM, "  uses interface Mgmt as %sControl;\n", mp->lib->full_name);
      fprintf(fp_engineM, "  uses interface AMSend as %sRadioAMSend;\n", mp->lib->full_name);
      fprintf(fp_engineM, "  uses interface Receive as %sRadioReceive;\n", mp->lib->full_name);
      fprintf(fp_engineM, "  uses interface Receive as %sRadioSnoop;\n", mp->lib->full_name);
      fprintf(fp_engineM, "  uses interface Packet as %sRadioPacket;\n", mp->lib->full_name);
      fprintf(fp_engineM, "  uses interface AMPacket as %sRadioAMPacket;\n", mp->lib->full_name);
      fprintf(fp_engineM, "  uses interface PacketAcknowledgements as %sRadioPacketAcknowledgements;\n", mp->lib->full_name);
      fprintf(fp_engineM, "  uses interface ModuleStatus as %sRadioStatus;\n\n", mp->lib->full_name);
    }
  }

  fprintf(fp_engineM,"}\n\n");
  fprintf(fp_engineM,"implementation {\n\n");
  fprintf(fp_engineM,"  void ctrl_state_done(uint8_t status, uint8_t ctrl) @C() {\n");
  fprintf(fp_engineM,"    if (ctrl == ON) {\n");
  fprintf(fp_engineM,"      call EventsMgmt.start();\n");
  fprintf(fp_engineM,"    } else {\n");
  fprintf(fp_engineM,"      call EventsMgmt.stop();\n");
  fprintf(fp_engineM,"    }\n");
  fprintf(fp_engineM,"  }\n\n");

  fprintf(fp_engineM,"  void ctrl_module(uint16_t module_id, uint8_t ctrl) @C() {\n");
  fprintf(fp_engineM,"    switch(module_id) {\n\n");

  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0) {
      fprintf(fp_engineM, "      case %d:\n", mp->id);
      fprintf(fp_engineM, "        if (ctrl) {\n");
      fprintf(fp_engineM, "          call %sControl.start();\n", mp->lib->full_name);
      fprintf(fp_engineM, "        } else {\n");
      fprintf(fp_engineM, "          call %sControl.stop();\n", mp->lib->full_name);
      fprintf(fp_engineM, "        }\n");
      fprintf(fp_engineM, "        break;\n\n");
    }
  }

  fprintf(fp_engineM,"      default:\n");
  fprintf(fp_engineM,"    }\n");
  fprintf(fp_engineM,"    call Timer.startOneShot(MODULE_RESPONSE_DELAY);\n");
  fprintf(fp_engineM,"  }\n\n");

  fprintf(fp_engineM,"  task void configure_engine() {\n");
  fprintf(fp_engineM,"    call Timer.stop();\n");
  fprintf(fp_engineM,"    ctrl_module_done(0);\n");
  fprintf(fp_engineM,"  }\n\n");

  fprintf(fp_engineM,"  event void Timer.fired() {\n");
  fprintf(fp_engineM,"    ctrl_module_done(1);\n");
  fprintf(fp_engineM,"  }\n\n");

  fprintf(fp_engineM,"  command error_t Mgmt.start() {\n");
  fprintf(fp_engineM,"    ctrl_state(ON);\n");
  fprintf(fp_engineM,"    return SUCCESS;\n");
  fprintf(fp_engineM,"  }\n\n");

  fprintf(fp_engineM,"  command error_t Mgmt.stop() {\n");
  fprintf(fp_engineM,"    ctrl_state(OFF);\n");
  fprintf(fp_engineM,"    return SUCCESS;\n");
  fprintf(fp_engineM,"  }\n\n");

  fprintf(fp_engineM,"  event void EventsMgmt.startDone(error_t err) {\n");
  fprintf(fp_engineM,"    signal Mgmt.startDone(SUCCESS);\n");
  fprintf(fp_engineM,"  }\n\n");

  fprintf(fp_engineM,"  event void EventsMgmt.stopDone(error_t err) {\n");
  fprintf(fp_engineM,"    signal Mgmt.stopDone(SUCCESS);\n");
  fprintf(fp_engineM,"  }\n\n");


  fprintf(fp_engineM,"  error_t AMSend_send(uint16_t module_id, uint8_t to_layer, am_addr_t addr, message_t* msg, uint8_t len) {\n");
  fprintf(fp_engineM,"    if (msg->conf != POLICY_CONFIGURATION) msg->conf = get_conf_id();\n");
  fprintf(fp_engineM,"    switch( get_module_id(get_state_id(), get_conf_id(), to_layer) ) {\n");
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_NETWORK) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sNetworkAMSend.send(addr, msg, len);\n\n", mp->lib->full_name);
    }
  }
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_MAC) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sMacAMSend.send(addr, msg, len);\n\n", mp->lib->full_name);
    }
  }
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_RADIO) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sRadioAMSend.send(addr, msg, len);\n\n", mp->lib->full_name);
    }
  }

  fprintf(fp_engineM,"      default:\n");
  fprintf(fp_engineM,"        return FAIL;\n");
  fprintf(fp_engineM,"    }\n");
  fprintf(fp_engineM,"  }\n\n");


  fprintf(fp_engineM,"  error_t AMSend_cancel(uint16_t module_id, uint8_t to_layer, message_t *msg) {\n");
  fprintf(fp_engineM,"    if (msg->conf != POLICY_CONFIGURATION) msg->conf = get_conf_id();\n");
  fprintf(fp_engineM,"    switch( get_module_id(get_state_id(), get_conf_id(), to_layer) ) {\n");
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_NETWORK) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sNetworkAMSend.cancel(msg);\n\n", mp->lib->full_name);
    }
  }
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_MAC) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sMacAMSend.cancel(msg);\n\n", mp->lib->full_name);
    }
  }
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_RADIO) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sRadioAMSend.cancel(msg);\n\n", mp->lib->full_name);
    }
  }
  fprintf(fp_engineM,"      default:\n");
  fprintf(fp_engineM,"        return FAIL;\n");
  fprintf(fp_engineM,"    }\n");
  fprintf(fp_engineM,"  }\n\n");



  fprintf(fp_engineM,"  void* AMSend_getPayload(uint16_t module_id, uint8_t to_layer, message_t *msg, uint8_t len) {\n");
  fprintf(fp_engineM,"    if (msg->conf != POLICY_CONFIGURATION) msg->conf = get_conf_id();\n");
  fprintf(fp_engineM,"    switch( get_module_id(get_state_id(), get_conf_id(), to_layer) ) {\n");
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_NETWORK) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sNetworkAMSend.getPayload(msg, len);\n\n", mp->lib->full_name);
    }
  }
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_MAC) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sMacAMSend.getPayload(msg, len);\n\n", mp->lib->full_name);
    }
  }
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_RADIO) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sRadioAMSend.getPayload(msg, len);\n\n", mp->lib->full_name);
    }
  }
  fprintf(fp_engineM,"      default:\n");
  fprintf(fp_engineM,"        return NULL;\n");
  fprintf(fp_engineM,"    }\n");
  fprintf(fp_engineM,"  }\n\n");


  fprintf(fp_engineM,"  uint8_t AMSend_maxPayloadLength(uint16_t module_id, uint8_t to_layer) {\n");
  fprintf(fp_engineM,"    switch( get_module_id(get_state_id(), get_conf_id(), to_layer) ) {\n");
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_NETWORK) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sNetworkAMSend.maxPayloadLength();\n\n", mp->lib->full_name);
    }
  }
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_MAC) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sMacAMSend.maxPayloadLength();\n\n", mp->lib->full_name);
    }
  }
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_RADIO) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sRadioAMSend.maxPayloadLength();\n\n", mp->lib->full_name);
    }
  }
  fprintf(fp_engineM,"      default:\n");
  fprintf(fp_engineM,"        return 0;\n");
  fprintf(fp_engineM,"    }\n");
  fprintf(fp_engineM,"  }\n\n");



  fprintf(fp_engineM,"  am_addr_t AMPacket_address(uint16_t module_id, uint8_t to_layer) {\n");
  fprintf(fp_engineM,"    switch( get_module_id(get_state_id(), get_conf_id(), to_layer) ) {\n");
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_NETWORK) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sNetworkAMPacket.address();\n\n", mp->lib->full_name);
    }
  }
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_MAC) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sMacAMPacket.address();\n\n", mp->lib->full_name);
    }
  }
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_RADIO) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sRadioAMPacket.address();\n\n", mp->lib->full_name);
    }
  }
  fprintf(fp_engineM,"      default:\n");
  fprintf(fp_engineM,"        return 0;\n");
  fprintf(fp_engineM,"    }\n");
  fprintf(fp_engineM,"  }\n\n");


  fprintf(fp_engineM,"  am_addr_t AMPacket_destination(uint16_t module_id, uint8_t to_layer, message_t *msg) {\n");
  fprintf(fp_engineM,"    if (msg->conf != POLICY_CONFIGURATION) msg->conf = get_conf_id();\n");
  fprintf(fp_engineM,"    switch( get_module_id(get_state_id(), get_conf_id(), to_layer) ) {\n");
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_NETWORK) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sNetworkAMPacket.destination(msg);\n", mp->lib->full_name);
    }
  }
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_MAC) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sMacAMPacket.destination(msg);\n", mp->lib->full_name);
    }
  }
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_RADIO) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sRadioAMPacket.destination(msg);\n", mp->lib->full_name);
    }
  }
  fprintf(fp_engineM,"      default:\n");
  fprintf(fp_engineM,"        return 0;\n");
  fprintf(fp_engineM,"    }\n");
  fprintf(fp_engineM,"  }\n\n");



  fprintf(fp_engineM,"  am_addr_t AMPacket_source(uint16_t module_id, uint8_t to_layer, message_t *msg) {\n");
  fprintf(fp_engineM,"    if (msg->conf != POLICY_CONFIGURATION) msg->conf = get_conf_id();\n");
  fprintf(fp_engineM,"    switch( get_module_id(get_state_id(), get_conf_id(), to_layer) ) {\n");
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_NETWORK) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sNetworkAMPacket.source(msg);\n\n", mp->lib->full_name);
    }
  }
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_MAC) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sMacAMPacket.source(msg);\n\n", mp->lib->full_name);
    }
  }
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_RADIO) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sRadioAMPacket.source(msg);\n\n", mp->lib->full_name);
    }
  }
  fprintf(fp_engineM,"      default:\n");
  fprintf(fp_engineM,"        return 0;\n");
  fprintf(fp_engineM,"    }\n");
  fprintf(fp_engineM,"  }\n\n");



  fprintf(fp_engineM,"  void AMPacket_setDestination(uint16_t module_id, uint8_t to_layer, message_t *msg, am_addr_t addr) {\n");
  fprintf(fp_engineM,"    if (msg->conf != POLICY_CONFIGURATION) msg->conf = get_conf_id();\n");
  fprintf(fp_engineM,"    switch( get_module_id(get_state_id(), get_conf_id(), to_layer) ) {\n");
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_NETWORK) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sNetworkAMPacket.setDestination(msg, addr);\n\n", mp->lib->full_name);
    }
  }
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_MAC) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sMacAMPacket.setDestination(msg, addr);\n\n", mp->lib->full_name);
    }
  }
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_RADIO) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sRadioAMPacket.setDestination(msg, addr);\n\n", mp->lib->full_name);
    }
  }
  fprintf(fp_engineM,"      default:\n");
  fprintf(fp_engineM,"        return;\n");
  fprintf(fp_engineM,"    }\n");
  fprintf(fp_engineM,"  }\n\n");



  fprintf(fp_engineM,"  void AMPacket_setSource(uint16_t module_id, uint8_t to_layer, message_t *msg, am_addr_t addr) {\n");
  fprintf(fp_engineM,"    if (msg->conf != POLICY_CONFIGURATION) msg->conf = get_conf_id();\n");
  fprintf(fp_engineM,"    switch( get_module_id(get_state_id(), get_conf_id(), to_layer) ) {\n");
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_NETWORK) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sNetworkAMPacket.setSource(msg, addr);\n\n", mp->lib->full_name);
    }
  }
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_MAC) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sMacAMPacket.setSource(msg, addr);\n\n", mp->lib->full_name);
    }
  }
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_RADIO) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sRadioAMPacket.setSource(msg, addr);\n\n", mp->lib->full_name);
    }
  }
  fprintf(fp_engineM,"      default:\n");
  fprintf(fp_engineM,"        return;\n");
  fprintf(fp_engineM,"    }\n");
  fprintf(fp_engineM,"  }\n\n");



  fprintf(fp_engineM,"  bool AMPacket_isForMe(uint16_t module_id, uint8_t to_layer, message_t *msg) {\n");
  fprintf(fp_engineM,"    if (msg->conf != POLICY_CONFIGURATION) msg->conf = get_conf_id();\n");
  fprintf(fp_engineM,"    switch( get_module_id(get_state_id(), get_conf_id(), to_layer) ) {\n");
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_NETWORK) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sNetworkAMPacket.isForMe(msg);\n\n", mp->lib->full_name);
    }
  }
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_MAC) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sMacAMPacket.isForMe(msg);\n\n", mp->lib->full_name);
    }
  }
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_RADIO) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sRadioAMPacket.isForMe(msg);\n\n", mp->lib->full_name);
    }
  }
  fprintf(fp_engineM,"      default:\n");
  fprintf(fp_engineM,"        return 0;\n");
  fprintf(fp_engineM,"    }\n");
  fprintf(fp_engineM,"  }\n\n");


  fprintf(fp_engineM,"  am_id_t AMPacket_type(uint16_t module_id, uint8_t to_layer, message_t *msg) {\n");
  fprintf(fp_engineM,"    if (msg->conf != POLICY_CONFIGURATION) msg->conf = get_conf_id();\n");
  fprintf(fp_engineM,"    switch( get_module_id(get_state_id(), get_conf_id(), to_layer) ) {\n");
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_NETWORK) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sNetworkAMPacket.type(msg);\n\n", mp->lib->full_name);
    }
  }
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_MAC) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sMacAMPacket.type(msg);\n\n", mp->lib->full_name);
    }
  }
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_RADIO) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sRadioAMPacket.type(msg);\n\n", mp->lib->full_name);
    }
  }
  fprintf(fp_engineM,"      default:\n");
  fprintf(fp_engineM,"        return 0;\n");
  fprintf(fp_engineM,"    }\n");
  fprintf(fp_engineM,"  }\n\n");



  fprintf(fp_engineM,"  void AMPacket_setType(uint16_t module_id, uint8_t to_layer, message_t *msg, am_id_t t) {\n");
  fprintf(fp_engineM,"    if (msg->conf != POLICY_CONFIGURATION) msg->conf = get_conf_id();\n");
  fprintf(fp_engineM,"    switch( get_module_id(get_state_id(), get_conf_id(), to_layer) ) {\n");
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_NETWORK) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sNetworkAMPacket.setType(msg, t);\n\n", mp->lib->full_name);
    }
  }
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_MAC) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sMacAMPacket.setType(msg, t);\n\n", mp->lib->full_name);
    }
  }
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_RADIO) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sRadioAMPacket.setType(msg, t);\n\n", mp->lib->full_name);
    }
  }
  fprintf(fp_engineM,"      default:\n");
  fprintf(fp_engineM,"        return;\n");
  fprintf(fp_engineM,"    }\n");
  fprintf(fp_engineM,"  }\n\n");


  fprintf(fp_engineM,"  am_group_t AMPacket_group(uint16_t module_id, uint8_t to_layer, message_t *msg) {\n");
  fprintf(fp_engineM,"    if (msg->conf != POLICY_CONFIGURATION) msg->conf = get_conf_id();\n");
  fprintf(fp_engineM,"    switch( get_module_id(get_state_id(), get_conf_id(), to_layer) ) {\n");
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_NETWORK) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sNetworkAMPacket.group(msg);\n\n", mp->lib->full_name);
    }
  }
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_MAC) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sMacAMPacket.group(msg);\n\n", mp->lib->full_name);
    }
  }
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_RADIO) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sRadioAMPacket.group(msg);\n\n", mp->lib->full_name);
    }
  }
  fprintf(fp_engineM,"      default:\n");
  fprintf(fp_engineM,"        return 0;\n");
  fprintf(fp_engineM,"    }\n");
  fprintf(fp_engineM,"  }\n\n");


  fprintf(fp_engineM,"  void AMPacket_setGroup(uint16_t module_id, uint8_t to_layer, message_t *msg, am_group_t grp) {\n");
  fprintf(fp_engineM,"    if (msg->conf != POLICY_CONFIGURATION) msg->conf = get_conf_id();\n");
  fprintf(fp_engineM,"    switch( get_module_id(get_state_id(), get_conf_id(), to_layer) ) {\n");
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_NETWORK) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sNetworkAMPacket.setGroup(msg, grp);\n\n", mp->lib->full_name);
    }
  }
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_MAC) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sMacAMPacket.setGroup(msg, grp);\n\n", mp->lib->full_name);
    }
  }
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_RADIO) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sRadioAMPacket.setGroup(msg, grp);\n\n", mp->lib->full_name);
    }
  }
  fprintf(fp_engineM,"      default:\n");
  fprintf(fp_engineM,"        return;\n");
  fprintf(fp_engineM,"    }\n");
  fprintf(fp_engineM,"  }\n\n");



  fprintf(fp_engineM,"  void* Packet_getPayload(uint16_t module_id, uint8_t to_layer, message_t *msg, uint8_t len) {\n");
  fprintf(fp_engineM,"    if (msg->conf != POLICY_CONFIGURATION) msg->conf = get_conf_id();\n");
  fprintf(fp_engineM,"    switch( get_module_id(get_state_id(), get_conf_id(), to_layer) ) {\n");
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_NETWORK) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sNetworkPacket.getPayload(msg, len);\n\n", mp->lib->full_name);
    }
  }
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_MAC) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sMacPacket.getPayload(msg, len);\n\n", mp->lib->full_name);
    }
  }
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_RADIO) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sRadioPacket.getPayload(msg, len);\n\n", mp->lib->full_name);
    }
  }
  fprintf(fp_engineM,"      default:\n");
  fprintf(fp_engineM,"        return NULL;\n");
  fprintf(fp_engineM,"    }\n");
  fprintf(fp_engineM,"  }\n\n");



  fprintf(fp_engineM,"  uint8_t Packet_maxPayloadLength(uint16_t module_id, uint8_t to_layer) {\n");
  fprintf(fp_engineM,"    switch( get_module_id(get_state_id(), get_conf_id(), to_layer) ) {\n");
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_NETWORK) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sNetworkPacket.maxPayloadLength();\n\n", mp->lib->full_name);
    }
  }
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_MAC) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sMacPacket.maxPayloadLength();\n\n", mp->lib->full_name);
    }
  }
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_RADIO) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sRadioPacket.maxPayloadLength();\n\n", mp->lib->full_name);
    }
  }
  fprintf(fp_engineM,"      default:\n");
  fprintf(fp_engineM,"        return 0;\n");
  fprintf(fp_engineM,"    }\n");
  fprintf(fp_engineM,"  }\n\n");



  fprintf(fp_engineM,"  am_group_t AMPacket_localGroup(uint16_t module_id, uint8_t to_layer) {\n");
  fprintf(fp_engineM,"    switch( get_module_id(get_state_id(), get_conf_id(), to_layer) ) {\n");
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_NETWORK) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sNetworkAMPacket.localGroup();\n\n", mp->lib->full_name);
    }
  }
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_MAC) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sMacAMPacket.localGroup();\n\n", mp->lib->full_name);
    }
  }
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_RADIO) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sRadioAMPacket.localGroup();\n\n", mp->lib->full_name);
    }
  }
  fprintf(fp_engineM,"      default:\n");
  fprintf(fp_engineM,"        return 0;\n");
  fprintf(fp_engineM,"    }\n");
  fprintf(fp_engineM,"  }\n\n");



  fprintf(fp_engineM,"  void Packet_clear(uint16_t module_id, uint8_t to_layer, message_t *msg) {\n");
  fprintf(fp_engineM,"    if (msg->conf != POLICY_CONFIGURATION) msg->conf = get_conf_id();\n");
  fprintf(fp_engineM,"    switch( get_module_id(get_state_id(), get_conf_id(), to_layer) ) {\n");
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_NETWORK) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sNetworkPacket.clear(msg);\n\n", mp->lib->full_name);
    }
  }
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_MAC) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sMacPacket.clear(msg);\n\n", mp->lib->full_name);
    }
  }
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_RADIO) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sRadioPacket.clear(msg);\n\n", mp->lib->full_name);
    }
  }
  fprintf(fp_engineM,"      default:\n");
  fprintf(fp_engineM,"        return;\n");
  fprintf(fp_engineM,"    }\n");
  fprintf(fp_engineM,"  }\n\n");



  fprintf(fp_engineM,"  uint8_t Packet_payloadLength(uint16_t module_id, uint8_t to_layer, message_t *msg) {\n");
  fprintf(fp_engineM,"    if (msg->conf != POLICY_CONFIGURATION) msg->conf = get_conf_id();\n");
  fprintf(fp_engineM,"    switch( get_module_id(get_state_id(), get_conf_id(), to_layer) ) {\n");
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_NETWORK) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sNetworkPacket.payloadLength(msg);\n\n", mp->lib->full_name);
    }
  }
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_MAC) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sMacPacket.payloadLength(msg);\n\n", mp->lib->full_name);
    }
  }
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_RADIO) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sRadioPacket.payloadLength(msg);\n\n", mp->lib->full_name);
    }
  }
  fprintf(fp_engineM,"      default:\n");
  fprintf(fp_engineM,"        return 0;\n");
  fprintf(fp_engineM,"    }\n");
  fprintf(fp_engineM,"  }\n\n");



  fprintf(fp_engineM,"  void Packet_setPayloadLength(uint16_t module_id, uint8_t to_layer, message_t *msg, uint8_t len) {\n");
  fprintf(fp_engineM,"    if (msg->conf != POLICY_CONFIGURATION) msg->conf = get_conf_id();\n");
  fprintf(fp_engineM,"    switch( get_module_id(get_state_id(), get_conf_id(), to_layer) ) {\n");
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_NETWORK) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sNetworkPacket.setPayloadLength(msg, len);\n\n", mp->lib->full_name);
    }
  }
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_MAC) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sMacPacket.setPayloadLength(msg, len);\n\n", mp->lib->full_name);
    }
  }
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_RADIO) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sRadioPacket.setPayloadLength(msg, len);\n\n", mp->lib->full_name);
    }
  }
  fprintf(fp_engineM,"      default:\n");
  fprintf(fp_engineM,"        return;\n");
  fprintf(fp_engineM,"    }\n");
  fprintf(fp_engineM,"  }\n\n");



  fprintf(fp_engineM,"  error_t PacketAcknowledgements_requestAck(uint16_t module_id, uint8_t to_layer, message_t *msg) {\n");
  fprintf(fp_engineM,"    if (msg->conf != POLICY_CONFIGURATION) msg->conf = get_conf_id();\n");
  fprintf(fp_engineM,"    switch( get_module_id(get_state_id(), get_conf_id(), to_layer) ) {\n");
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_NETWORK) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sNetworkPacketAcknowledgements.requestAck(msg);\n\n", mp->lib->full_name);
    }
  }
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_MAC) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sMacPacketAcknowledgements.requestAck(msg);\n\n", mp->lib->full_name);
    }
  }
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_RADIO) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sRadioPacketAcknowledgements.requestAck(msg);\n\n", mp->lib->full_name);
    }
  }
  fprintf(fp_engineM,"      default:\n");
  fprintf(fp_engineM,"        return FAIL;\n");
  fprintf(fp_engineM,"    }\n");
  fprintf(fp_engineM,"  }\n\n");



  fprintf(fp_engineM,"  error_t PacketAcknowledgements_noAck(uint16_t module_id, uint8_t to_layer, message_t *msg) {\n");
  fprintf(fp_engineM,"    if (msg->conf != POLICY_CONFIGURATION) msg->conf = get_conf_id();\n");
  fprintf(fp_engineM,"    switch( get_module_id(get_state_id(), get_conf_id(), to_layer) ) {\n");
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_NETWORK) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sNetworkPacketAcknowledgements.noAck(msg);\n\n", mp->lib->full_name);
    }
  }
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_MAC) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sMacPacketAcknowledgements.noAck(msg);\n\n", mp->lib->full_name);
    }
  }
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_RADIO) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sRadioPacketAcknowledgements.noAck(msg);\n\n", mp->lib->full_name);
    }
  }
  fprintf(fp_engineM,"      default:\n");
  fprintf(fp_engineM,"        return FAIL;\n");
  fprintf(fp_engineM,"    }\n");
  fprintf(fp_engineM,"  }\n\n");


  fprintf(fp_engineM,"  bool PacketAcknowledgements_wasAcked(uint16_t module_id, uint8_t to_layer, message_t *msg) {\n");
  fprintf(fp_engineM,"    if (msg->conf != POLICY_CONFIGURATION) msg->conf = get_conf_id();\n");
  fprintf(fp_engineM,"    switch( get_module_id(get_state_id(), get_conf_id(), to_layer) ) {\n");
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_NETWORK) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sNetworkPacketAcknowledgements.wasAcked(msg);\n\n", mp->lib->full_name);
    }
  }
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_MAC) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sMacPacketAcknowledgements.wasAcked(msg);\n\n", mp->lib->full_name);
    }
  }
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_RADIO) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return call %sRadioPacketAcknowledgements.wasAcked(msg);\n\n", mp->lib->full_name);
    }
  }
  fprintf(fp_engineM,"      default:\n");
  fprintf(fp_engineM,"        return 0;\n");
  fprintf(fp_engineM,"    }\n");
  fprintf(fp_engineM,"  }\n\n");


  fprintf(fp_engineM,"  void sendDone(uint16_t module_id, uint8_t to_layer, message_t* msg, error_t error) {\n");
  fprintf(fp_engineM,"    switch( get_module_id(get_state_id(), msg->conf, to_layer) ) {\n");
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_APPLICATION) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        signal %sNetworkAMSend.sendDone(msg, error);\n", mp->lib->full_name);
      fprintf(fp_engineM,"        return;\n\n");
    }
  }
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_NETWORK) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        signal %sMacAMSend.sendDone(msg, error);\n", mp->lib->full_name);
      fprintf(fp_engineM,"        return;\n\n");
    }
  }
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_MAC) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        signal %sRadioAMSend.sendDone(msg, error);\n", mp->lib->full_name);
      fprintf(fp_engineM,"        return;\n\n");
    }
  }
  fprintf(fp_engineM,"      case POLICY_CONFIGURATION:\n");
  fprintf(fp_engineM,"        signal ControlUnit_MacAMSend.sendDone(msg, error);\n");
  fprintf(fp_engineM,"        return;\n\n");
  fprintf(fp_engineM,"      default:\n");
  fprintf(fp_engineM,"        return;\n");
  fprintf(fp_engineM,"    }\n\n");
  fprintf(fp_engineM,"  }\n\n");

  fprintf(fp_engineM,"  message_t* receive(uint16_t module_id, uint8_t to_layer, message_t* msg, void* payload, uint8_t len) {\n");
  fprintf(fp_engineM,"    switch( get_module_id(get_state_id(), msg->conf, to_layer) ) {\n");
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_APPLICATION) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return signal %sNetworkReceive.receive(msg, payload, len);\n\n", mp->lib->full_name);
    }
  }
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_NETWORK) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return signal %sMacReceive.receive(msg, payload, len);\n\n", mp->lib->full_name);
    }
  }
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_MAC) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return signal %sRadioReceive.receive(msg, payload, len);\n\n", mp->lib->full_name);
    }
  }
  fprintf(fp_engineM,"      case POLICY_CONFIGURATION:\n");
  fprintf(fp_engineM,"        return signal ControlUnit_MacReceive.receive(msg, payload, len);\n\n");
  fprintf(fp_engineM,"      default:\n");
  fprintf(fp_engineM,"        return msg;\n\n");
  fprintf(fp_engineM,"      }\n");
  fprintf(fp_engineM, "  }\n\n");


  fprintf(fp_engineM,"  message_t* snoop(uint16_t module_id, uint8_t to_layer, message_t* msg, void* payload, uint8_t len) {\n");
  fprintf(fp_engineM,"    switch( get_module_id(get_state_id(), msg->conf, to_layer) ) {\n");
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_APPLICATION) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return signal %sNetworkSnoop.receive(msg, payload, len);\n\n", mp->lib->full_name);
    }
  }
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_NETWORK) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return signal %sMacSnoop.receive(msg, payload, len);\n\n", mp->lib->full_name);
    }
  }
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_MAC) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return signal %sRadioSnoop.receive(msg, payload, len);\n\n", mp->lib->full_name);
    }
  }
  fprintf(fp_engineM,"      case POLICY_CONFIGURATION:\n");
  fprintf(fp_engineM,"        return signal ControlUnit_MacSnoop.receive(msg, payload, len);\n\n");
  fprintf(fp_engineM,"      default:\n");
  fprintf(fp_engineM,"        return msg;\n\n");
  fprintf(fp_engineM,"    }\n");
  fprintf(fp_engineM,"  }\n\n");


  fprintf(fp_engineM,"  void status(uint16_t module_id, uint8_t to_layer, uint8_t layer, uint8_t status_flag) {\n");
  fprintf(fp_engineM,"    switch( get_module_id(get_state_id(), get_conf_id(), to_layer) ) {\n");
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_APPLICATION) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return signal %sNetworkStatus.status(layer, status_flag);\n\n", mp->lib->full_name);
    }
  }
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_NETWORK) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return signal %sMacStatus.status(layer, status_flag);\n\n", mp->lib->full_name);
    }
  }
  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_MAC) {
      fprintf(fp_engineM,"      case %d:\n", mp->id);
      fprintf(fp_engineM,"        return signal %sRadioStatus.status(layer, status_flag);\n\n", mp->lib->full_name);
    }
  }
  fprintf(fp_engineM,"      case POLICY_CONFIGURATION:\n");
  fprintf(fp_engineM,"        return signal ControlUnit_MacStatus.status(layer, status_flag);\n\n");
  fprintf(fp_engineM,"    }\n");
  fprintf(fp_engineM,"  }\n\n");


  /* Interfaces with Applications */


  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_APPLICATION) {
      fprintf(fp_engineM, "  event void %sControl.startDone(error_t err){\n", mp->lib->full_name);
      fprintf(fp_engineM, "    post configure_engine();\n");
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  event void %sControl.stopDone(error_t err) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    post configure_engine();\n");
      fprintf(fp_engineM, "  }\n\n");

      fprintf(fp_engineM, "  command error_t %sNetworkAMSend.send(am_addr_t addr, message_t* msg, uint8_t len) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return AMSend_send(%d, F_NETWORK, addr, msg, len);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  command error_t %sNetworkAMSend.cancel(message_t* msg) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return AMSend_cancel(%d, F_NETWORK, msg);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  command uint8_t %sNetworkAMSend.maxPayloadLength() {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return AMSend_maxPayloadLength(%d, F_NETWORK);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  command void* %sNetworkAMSend.getPayload(message_t* msg, uint8_t len) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return AMSend_getPayload(%d, F_NETWORK, msg, len);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  command am_addr_t %sNetworkAMPacket.address() {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return AMPacket_address(%d, F_NETWORK);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  command am_addr_t %sNetworkAMPacket.destination(message_t* msg) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return AMPacket_destination(%d, F_NETWORK, msg);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  command am_addr_t %sNetworkAMPacket.source(message_t* msg) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return AMPacket_source(%d, F_NETWORK, msg);\n", mp->id);
      fprintf(fp_engineM, "  }\n");
      fprintf(fp_engineM, "  command void %sNetworkAMPacket.setDestination(message_t* msg, am_addr_t addr) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return AMPacket_setDestination(%d, F_NETWORK, msg, addr);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  command void %sNetworkAMPacket.setSource(message_t* msg, am_addr_t addr) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return AMPacket_setSource(%d, F_NETWORK, msg, addr);\n", mp->id);
      fprintf(fp_engineM, "  }\n");
      fprintf(fp_engineM, "  command bool %sNetworkAMPacket.isForMe(message_t* msg) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return AMPacket_isForMe(%d, F_NETWORK, msg);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  command am_id_t %sNetworkAMPacket.type(message_t* msg) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return AMPacket_type(%d, F_NETWORK, msg);\n",mp->id);
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  command void %sNetworkAMPacket.setType(message_t* msg, am_id_t t) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return AMPacket_setType(%d, F_NETWORK, msg, t);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  command am_group_t %sNetworkAMPacket.group(message_t* msg) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return AMPacket_group(%d, F_NETWORK, msg);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  command void %sNetworkAMPacket.setGroup(message_t* msg, am_group_t grp) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return AMPacket_setGroup(%d, F_NETWORK, msg, grp);\n", mp->id);
      fprintf(fp_engineM, "  }\n");
      fprintf(fp_engineM, "  command am_group_t %sNetworkAMPacket.localGroup() {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return AMPacket_localGroup(%d, F_NETWORK);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  command void %sNetworkPacket.clear(message_t* msg) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return Packet_clear(%d, F_NETWORK, msg);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  command uint8_t %sNetworkPacket.payloadLength(message_t* msg) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return Packet_payloadLength(%d, F_NETWORK, msg);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  command void %sNetworkPacket.setPayloadLength(message_t* msg, uint8_t len) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return Packet_setPayloadLength(%d, F_NETWORK, msg, len);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  command uint8_t %sNetworkPacket.maxPayloadLength() {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return Packet_maxPayloadLength(%d, F_NETWORK);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  command void* %sNetworkPacket.getPayload(message_t* msg, uint8_t len) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return Packet_getPayload(%d, F_NETWORK, msg, len);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  async command error_t %sNetworkPacketAcknowledgements.requestAck( message_t* msg ) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return PacketAcknowledgements_requestAck(%d, F_NETWORK, msg);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  async command error_t %sNetworkPacketAcknowledgements.noAck( message_t* msg ) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return PacketAcknowledgements_noAck(%d, F_NETWORK, msg);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  async command bool %sNetworkPacketAcknowledgements.wasAcked(message_t* msg) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return PacketAcknowledgements_wasAcked(%d, F_NETWORK, msg);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
    }
  }

  /* Interfaces with Networks */

  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_NETWORK) {
      fprintf(fp_engineM, "  event void %sControl.startDone(error_t err) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    post configure_engine();\n");
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  event void %sControl.stopDone(error_t err) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    post configure_engine();\n");
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  event void %sNetworkAMSend.sendDone(message_t *msg, error_t error) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    sendDone(%d, F_APPLICATION, msg, error);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  event message_t* %sNetworkReceive.receive(message_t *msg, void* payload, uint8_t len) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return receive(%d, F_APPLICATION, msg, payload, len);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  event message_t* %sNetworkSnoop.receive(message_t *msg, void* payload, uint8_t len) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return snoop(%d, F_APPLICATION, msg, payload, len);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  event void %sNetworkStatus.status(uint8_t layer, uint8_t status_flag) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return status(%d, F_APPLICATION, layer, status_flag);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  command error_t %sMacAMSend.send(am_addr_t addr, message_t* msg, uint8_t len) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return AMSend_send(%d, F_MAC, addr, msg, len);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  command error_t %sMacAMSend.cancel(message_t* msg) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return AMSend_cancel(%d, F_MAC, msg);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  command uint8_t %sMacAMSend.maxPayloadLength() {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return AMSend_maxPayloadLength(%d, F_MAC);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  command void* %sMacAMSend.getPayload(message_t* msg, uint8_t len) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return AMSend_getPayload(%d, F_MAC, msg, len);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  command am_addr_t %sMacAMPacket.address() {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return AMPacket_address(%d, F_MAC);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  command am_addr_t %sMacAMPacket.destination(message_t* msg) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return AMPacket_destination(%d, F_MAC, msg);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  command am_addr_t %sMacAMPacket.source(message_t* msg) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return AMPacket_source(%d, F_MAC, msg);\n", mp->id);
      fprintf(fp_engineM, "  }\n");
      fprintf(fp_engineM, "  command void %sMacAMPacket.setDestination(message_t* msg, am_addr_t addr) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return AMPacket_setDestination(%d, F_MAC, msg, addr);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  command void %sMacAMPacket.setSource(message_t* msg, am_addr_t addr) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return AMPacket_setSource(%d, F_MAC, msg, addr);\n", mp->id);
      fprintf(fp_engineM, "  }\n");
      fprintf(fp_engineM, "  command bool %sMacAMPacket.isForMe(message_t* msg) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return AMPacket_isForMe(%d, F_MAC, msg);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  command am_id_t %sMacAMPacket.type(message_t* msg) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return AMPacket_type(%d, F_MAC, msg);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  command void %sMacAMPacket.setType(message_t* msg, am_id_t t) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return AMPacket_setType(%d, F_MAC, msg, t);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  command am_group_t %sMacAMPacket.group(message_t* msg) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return AMPacket_group(%d, F_MAC, msg);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  command void %sMacAMPacket.setGroup(message_t* msg, am_group_t grp) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return AMPacket_setGroup(%d, F_MAC, msg, grp);\n", mp->id);
      fprintf(fp_engineM, "  }\n");
      fprintf(fp_engineM, "  command am_group_t %sMacAMPacket.localGroup() {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return AMPacket_localGroup(%d, F_MAC);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  command void %sMacPacket.clear(message_t* msg) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return Packet_clear(%d, F_MAC, msg);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  command uint8_t %sMacPacket.payloadLength(message_t* msg) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return Packet_payloadLength(%d, F_MAC, msg);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  command void %sMacPacket.setPayloadLength(message_t* msg, uint8_t len) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return Packet_setPayloadLength(%d, F_MAC, msg, len);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  command uint8_t %sMacPacket.maxPayloadLength() {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return Packet_maxPayloadLength(%d, F_MAC);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  command void* %sMacPacket.getPayload(message_t* msg, uint8_t len) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return Packet_getPayload(%d, F_MAC, msg, len);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  async command error_t %sMacPacketAcknowledgements.requestAck( message_t* msg ) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return PacketAcknowledgements_requestAck(%d, F_MAC, msg);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  async command error_t %sMacPacketAcknowledgements.noAck( message_t* msg ) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return PacketAcknowledgements_noAck(%d, F_MAC, msg);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  async command bool %sMacPacketAcknowledgements.wasAcked(message_t* msg) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return PacketAcknowledgements_wasAcked(%d, F_MAC, msg);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
    }
  }

  /* ControlUnit is wired at the Network Layer, thou it is not expected to provide any service to any application */
  fprintf(fp_engineM, "  command error_t ControlUnit_MacAMSend.send(am_addr_t addr, message_t* msg, uint8_t len) {\n");
  fprintf(fp_engineM, "    msg->conf = POLICY_CONFIGURATION;\n");
  fprintf(fp_engineM, "    return AMSend_send(POLICY_CONFIGURATION, F_MAC, addr, msg, len);\n");
  fprintf(fp_engineM, "  }\n\n");
  fprintf(fp_engineM, "  command error_t ControlUnit_MacAMSend.cancel(message_t* msg) {\n");
  fprintf(fp_engineM, "    msg->conf = POLICY_CONFIGURATION;\n");
  fprintf(fp_engineM, "    return AMSend_cancel(POLICY_CONFIGURATION, F_MAC, msg);\n");
  fprintf(fp_engineM, "  }\n\n");
  fprintf(fp_engineM, "  command uint8_t ControlUnit_MacAMSend.maxPayloadLength() {\n");
  fprintf(fp_engineM, "    return AMSend_maxPayloadLength(POLICY_CONFIGURATION, F_MAC);\n");
  fprintf(fp_engineM, "  }\n\n");
  fprintf(fp_engineM, "  command void* ControlUnit_MacAMSend.getPayload(message_t* msg, uint8_t len) {\n");
  fprintf(fp_engineM, "    msg->conf = POLICY_CONFIGURATION;\n");
  fprintf(fp_engineM, "    return AMSend_getPayload(POLICY_CONFIGURATION, F_MAC, msg, len);\n");
  fprintf(fp_engineM, "  }\n\n");
  fprintf(fp_engineM, "  command am_addr_t ControlUnit_MacAMPacket.address() {\n");
  fprintf(fp_engineM, "    return AMPacket_address(POLICY_CONFIGURATION, F_MAC);\n");
  fprintf(fp_engineM, "  }\n\n");
  fprintf(fp_engineM, "  command am_addr_t ControlUnit_MacAMPacket.destination(message_t* msg) {\n");
  fprintf(fp_engineM, "    msg->conf = POLICY_CONFIGURATION;\n");
  fprintf(fp_engineM, "    return AMPacket_destination(POLICY_CONFIGURATION, F_MAC, msg);\n");
  fprintf(fp_engineM, "  }\n\n");
  fprintf(fp_engineM, "  command am_addr_t ControlUnit_MacAMPacket.source(message_t* msg) {\n");
  fprintf(fp_engineM, "    msg->conf = POLICY_CONFIGURATION;\n");
  fprintf(fp_engineM, "    return AMPacket_source(POLICY_CONFIGURATION, F_MAC, msg);\n");
  fprintf(fp_engineM, "  }\n");
  fprintf(fp_engineM, "  command void ControlUnit_MacAMPacket.setDestination(message_t* msg, am_addr_t addr) {\n");
  fprintf(fp_engineM, "    msg->conf = POLICY_CONFIGURATION;\n");
  fprintf(fp_engineM, "    return AMPacket_setDestination(POLICY_CONFIGURATION, F_MAC, msg, addr);\n");
  fprintf(fp_engineM, "  }\n\n");
  fprintf(fp_engineM, "  command void ControlUnit_MacAMPacket.setSource(message_t* msg, am_addr_t addr) {\n");
  fprintf(fp_engineM, "    msg->conf = POLICY_CONFIGURATION;\n");
  fprintf(fp_engineM, "    return AMPacket_setSource(POLICY_CONFIGURATION, F_MAC, msg, addr);\n");
  fprintf(fp_engineM, "  }\n");
  fprintf(fp_engineM, "  command bool ControlUnit_MacAMPacket.isForMe(message_t* msg) {\n");
  fprintf(fp_engineM, "    msg->conf = POLICY_CONFIGURATION;\n");
  fprintf(fp_engineM, "    return AMPacket_isForMe(POLICY_CONFIGURATION, F_MAC, msg);\n");
  fprintf(fp_engineM, "  }\n\n");
  fprintf(fp_engineM, "  command am_id_t ControlUnit_MacAMPacket.type(message_t* msg) {\n");
  fprintf(fp_engineM, "    msg->conf = POLICY_CONFIGURATION;\n");
  fprintf(fp_engineM, "    return AMPacket_type(POLICY_CONFIGURATION, F_MAC, msg);\n");
  fprintf(fp_engineM, "  }\n\n");
  fprintf(fp_engineM, "  command void ControlUnit_MacAMPacket.setType(message_t* msg, am_id_t t) {\n");
  fprintf(fp_engineM, "    msg->conf = POLICY_CONFIGURATION;\n");
  fprintf(fp_engineM, "    return AMPacket_setType(POLICY_CONFIGURATION, F_MAC, msg, t);\n");
  fprintf(fp_engineM, "  }\n\n");
  fprintf(fp_engineM, "  command am_group_t ControlUnit_MacAMPacket.group(message_t* msg) {\n");
  fprintf(fp_engineM, "    msg->conf = POLICY_CONFIGURATION;\n");
  fprintf(fp_engineM, "    return AMPacket_group(POLICY_CONFIGURATION, F_MAC, msg);\n");
  fprintf(fp_engineM, "  }\n\n");
  fprintf(fp_engineM, "  command void ControlUnit_MacAMPacket.setGroup(message_t* msg, am_group_t grp) {\n");
  fprintf(fp_engineM, "    msg->conf = POLICY_CONFIGURATION;\n");
  fprintf(fp_engineM, "    return AMPacket_setGroup(POLICY_CONFIGURATION, F_MAC, msg, grp);\n");
  fprintf(fp_engineM, "  }\n");
  fprintf(fp_engineM, "  command am_group_t ControlUnit_MacAMPacket.localGroup() {\n");
  fprintf(fp_engineM, "    return AMPacket_localGroup(POLICY_CONFIGURATION, F_MAC);\n");
  fprintf(fp_engineM, "  }\n\n");
  fprintf(fp_engineM, "  command void ControlUnit_MacPacket.clear(message_t* msg) {\n");
  fprintf(fp_engineM, "    msg->conf = POLICY_CONFIGURATION;\n");
  fprintf(fp_engineM, "    return Packet_clear(POLICY_CONFIGURATION, F_MAC, msg);\n");
  fprintf(fp_engineM, "  }\n\n");
  fprintf(fp_engineM, "  command uint8_t ControlUnit_MacPacket.payloadLength(message_t* msg) {\n");
  fprintf(fp_engineM, "    msg->conf = POLICY_CONFIGURATION;\n");
  fprintf(fp_engineM, "    return Packet_payloadLength(POLICY_CONFIGURATION, F_MAC, msg);\n");
  fprintf(fp_engineM, "  }\n\n");
  fprintf(fp_engineM, "  command void ControlUnit_MacPacket.setPayloadLength(message_t* msg, uint8_t len) {\n");
  fprintf(fp_engineM, "    msg->conf = POLICY_CONFIGURATION;\n");
  fprintf(fp_engineM, "    return Packet_setPayloadLength(POLICY_CONFIGURATION, F_MAC, msg, len);\n");
  fprintf(fp_engineM, "  }\n\n");
  fprintf(fp_engineM, "  command uint8_t ControlUnit_MacPacket.maxPayloadLength() {\n");
  fprintf(fp_engineM, "    return Packet_maxPayloadLength(POLICY_CONFIGURATION, F_MAC);\n");
  fprintf(fp_engineM, "  }\n\n");
  fprintf(fp_engineM, "  command void* ControlUnit_MacPacket.getPayload(message_t* msg, uint8_t len) {\n");
  fprintf(fp_engineM, "    msg->conf = POLICY_CONFIGURATION;\n");
  fprintf(fp_engineM, "    return Packet_getPayload(POLICY_CONFIGURATION, F_MAC, msg, len);\n");
  fprintf(fp_engineM, "  }\n\n");
  fprintf(fp_engineM, "  async command error_t ControlUnit_MacPacketAcknowledgements.requestAck( message_t* msg ) {\n");
  fprintf(fp_engineM, "    msg->conf = POLICY_CONFIGURATION;\n");
  fprintf(fp_engineM, "    return PacketAcknowledgements_requestAck(POLICY_CONFIGURATION, F_MAC, msg);\n");
  fprintf(fp_engineM, "  }\n\n");
  fprintf(fp_engineM, "  async command error_t ControlUnit_MacPacketAcknowledgements.noAck( message_t* msg ) {\n");
  fprintf(fp_engineM, "    msg->conf = POLICY_CONFIGURATION;\n");
  fprintf(fp_engineM, "    return PacketAcknowledgements_noAck(POLICY_CONFIGURATION, F_MAC, msg);\n");
  fprintf(fp_engineM, "  }\n\n");
  fprintf(fp_engineM, "  async command bool ControlUnit_MacPacketAcknowledgements.wasAcked(message_t* msg) {\n");
  fprintf(fp_engineM, "    msg->conf = POLICY_CONFIGURATION;\n");
  fprintf(fp_engineM, "    return PacketAcknowledgements_wasAcked(POLICY_CONFIGURATION, F_MAC, msg);\n");
  fprintf(fp_engineM, "  }\n\n");



  /* Interfaces with Macs */

  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_MAC) {
      fprintf(fp_engineM, "  event void %sControl.startDone(error_t err) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    post configure_engine();\n");
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  event void %sControl.stopDone(error_t err) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    post configure_engine();\n");
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  event void %sMacAMSend.sendDone(message_t *msg, error_t error) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    sendDone(%d, F_NETWORK, msg, error);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  event message_t* %sMacReceive.receive(message_t *msg, void* payload, uint8_t len) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return receive(%d, F_NETWORK, msg, payload, len);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  event message_t* %sMacSnoop.receive(message_t *msg, void* payload, uint8_t len) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return snoop(%d, F_NETWORK, msg, payload, len);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  event void %sMacStatus.status(uint8_t layer, uint8_t status_flag) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return status(%d, F_NETWORK, layer, status_flag);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  command error_t %sRadioAMSend.send(am_addr_t addr, message_t* msg, uint8_t len) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return AMSend_send(%d, F_RADIO, addr, msg, len);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  command error_t %sRadioAMSend.cancel(message_t* msg) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return AMSend_cancel(%d, F_RADIO, msg);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  command uint8_t %sRadioAMSend.maxPayloadLength() {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return AMSend_maxPayloadLength(%d, F_RADIO);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  command void* %sRadioAMSend.getPayload(message_t* msg, uint8_t len) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return AMSend_getPayload(%d, F_RADIO, msg, len);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  command am_addr_t %sRadioAMPacket.address() {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return AMPacket_address(%d, F_RADIO);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  command am_addr_t %sRadioAMPacket.destination(message_t* msg) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return AMPacket_destination(%d, F_RADIO, msg);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  command am_addr_t %sRadioAMPacket.source(message_t* msg) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return AMPacket_source(%d, F_RADIO, msg);\n", mp->id);
      fprintf(fp_engineM, "  }\n");
      fprintf(fp_engineM, "  command void %sRadioAMPacket.setDestination(message_t* msg, am_addr_t addr) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return AMPacket_setDestination(%d, F_RADIO, msg, addr);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  command void %sRadioAMPacket.setSource(message_t* msg, am_addr_t addr) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return AMPacket_setSource(%d, F_RADIO, msg, addr);\n", mp->id);
      fprintf(fp_engineM, "  }\n");
      fprintf(fp_engineM, "  command bool %sRadioAMPacket.isForMe(message_t* msg) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return AMPacket_isForMe(%d, F_RADIO, msg);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  command am_id_t %sRadioAMPacket.type(message_t* msg) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return AMPacket_type(%d, F_RADIO, msg);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  command void %sRadioAMPacket.setType(message_t* msg, am_id_t t) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return AMPacket_setType(%d, F_RADIO, msg, t);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  command am_group_t %sRadioAMPacket.group(message_t* msg) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return AMPacket_group(%d, F_RADIO, msg);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  command void %sRadioAMPacket.setGroup(message_t* msg, am_group_t grp) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return AMPacket_setGroup(%d, F_RADIO, msg, grp);\n", mp->id);
      fprintf(fp_engineM, "  }\n");
      fprintf(fp_engineM, "  command am_group_t %sRadioAMPacket.localGroup() {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return AMPacket_localGroup(%d, F_RADIO);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  command void %sRadioPacket.clear(message_t* msg) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return Packet_clear(%d, F_RADIO, msg);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  command uint8_t %sRadioPacket.payloadLength(message_t* msg) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return Packet_payloadLength(%d, F_RADIO, msg);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  command void %sRadioPacket.setPayloadLength(message_t* msg, uint8_t len) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return Packet_setPayloadLength(%d, F_RADIO, msg, len);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  command uint8_t %sRadioPacket.maxPayloadLength() {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return Packet_maxPayloadLength(%d, F_RADIO);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  command void* %sRadioPacket.getPayload(message_t* msg, uint8_t len) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return Packet_getPayload(%d, F_RADIO, msg, len);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  async command error_t %sRadioPacketAcknowledgements.requestAck( message_t* msg ) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return PacketAcknowledgements_requestAck(%d, F_RADIO, msg);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  async command error_t %sRadioPacketAcknowledgements.noAck( message_t* msg ) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return PacketAcknowledgements_noAck(%d, F_RADIO, msg);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  async command bool %sRadioPacketAcknowledgements.wasAcked(message_t* msg) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return PacketAcknowledgements_wasAcked(%d, F_RADIO, msg);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
    }
  }

  /* Interfaces with Radios */

  for(mp = modtab; mp < &modtab[NSYMS]; mp++) {
    if (mp->lib != NULL && mp->lib->path && mp->id > 0 && mp->lib->type == TYPE_RADIO) {
      fprintf(fp_engineM, "  event void %sControl.startDone(error_t err) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    post configure_engine();\n");
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  event void %sControl.stopDone(error_t err) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    post configure_engine();\n");
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  event void %sRadioAMSend.sendDone(message_t *msg, error_t err) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    sendDone(%d, F_MAC, msg, err);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  event message_t* %sRadioReceive.receive(message_t *msg, void* payload, uint8_t len) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return receive(%d, F_MAC, msg, payload, len);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  event message_t* %sRadioSnoop.receive(message_t *msg, void* payload, uint8_t len) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return snoop(%d, F_MAC, msg, payload, len);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
      fprintf(fp_engineM, "  event void %sRadioStatus.status(uint8_t layer, uint8_t status_flag) {\n", mp->lib->full_name);
      fprintf(fp_engineM, "    return status(%d, F_MAC, layer, status_flag);\n", mp->id);
      fprintf(fp_engineM, "  }\n\n");
    }
  }

  fprintf(fp_engineM, "\n}\n");
  fclose(fp_engineM);
}

