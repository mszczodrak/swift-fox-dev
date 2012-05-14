#include "code_gen.h"

void generateCaches(int event_counter, int policy_counter) {

  FILE *tmp_confs = fopen(TEMP_CONF_FILE, "r");
  FILE *fp_cachesH = fopen(cachesH, "w");
  struct symtab *sp;
  int i;

  if (fp_cachesH == NULL) {
    fprintf(stderr, "You do not have a permission to write into file: %s\n", cachesH);
    exit(1);
  }

  if (tmp_confs == NULL) {
    fprintf(stderr, "You do not have a permission to write into file: %s\n", TEMP_CONF_FILE);
    exit(1);
  }

  fprintf(fp_cachesH, "/* Swift Fox generated code for Fennec Fox caches.h */\n");
  fprintf(fp_cachesH, "#ifndef __FF_CACHES_H__\n");
  fprintf(fp_cachesH, "#define __FF_CACHES_H__\n\n");

  fprintf(fp_cachesH, "#define NUMBER_OF_CONFIGURATIONS  %d\n", conf_counter);
  fprintf(fp_cachesH, "#define INTERNAL_POLICY_CONFIGURATION_ID  %d\n\n", policy_conf_id);
  fprintf(fp_cachesH, "#include <Fennec.h>\n");
  fprintf(fp_cachesH, "#include \"defparms.h\"\n\n");

  fprintf(fp_cachesH, "uint16_t active_state = %d;\n\n", active_state);
  fprintf(fp_cachesH, "struct fennec_configuration configurations[NUMBER_OF_CONFIGURATIONS] = {\n");
  fprintf(fp_cachesH, "\t{\n");
  fprintf(fp_cachesH, "\t.application = 0,\n");
  fprintf(fp_cachesH, "\t.network = 0,\n");
  fprintf(fp_cachesH, "\t.mac = 0,\n");
  fprintf(fp_cachesH, "\t.radio = 0,\n");
  fprintf(fp_cachesH, "\t.level = 0\n");
  fprintf(fp_cachesH, "\t}\n");

  /* generate code specifying each configuration's definition */

  for( i = 1; i < conf_counter; i++ ) {
    fprintf(fp_cachesH, "\t,\n");
    fprintf(fp_cachesH, "\t{\n");
    
    fprintf(fp_cachesH, "\t.application = %d,\n", conftab[i].conf->app->id);
    fprintf(fp_cachesH, "\t.network = %d,\n", conftab[i].conf->net->id);
    fprintf(fp_cachesH, "\t.mac = %d,\n", conftab[i].conf->mac->id);
    fprintf(fp_cachesH, "\t.radio = %d,\n", conftab[i].conf->radio->id);
    if (conftab[i].conf->level == UNKNOWN) {
      fprintf(fp_cachesH, "\t.level = F_MINIMUM_STATE_LEVEL\n");
    } else {
      fprintf(fp_cachesH, "\t.level = %d\n", conftab[i].conf->level);
    }
    fprintf(fp_cachesH, "\t}\n");
  }

  fprintf(fp_cachesH, "};\n\n");


  fprintf(fp_cachesH, "struct default_params defs[NUMBER_OF_CONFIGURATIONS] = {\n");
  fprintf(fp_cachesH, "\t{\n");
  fprintf(fp_cachesH, "\t.application = NULL,\n");
  fprintf(fp_cachesH, "\t.network = NULL,\n");
  fprintf(fp_cachesH, "\t.mac = NULL,\n");
  fprintf(fp_cachesH, "\t.radio = NULL\n");
  fprintf(fp_cachesH, "\t}\n");


  for( i = 1; i < conf_counter; i++ ) {
    fprintf(fp_cachesH, "\t,\n");
    fprintf(fp_cachesH, "\t{\n");
    fprintf(fp_cachesH, "\t.application = &%s_%s,\n", conftab[i].conf->id->name, conftab[i].conf->app->lib->full_name);
    fprintf(fp_cachesH, "\t.network = &%s_%s,\n", conftab[i].conf->id->name, conftab[i].conf->net->lib->full_name);
    fprintf(fp_cachesH, "\t.mac = &%s_%s,\n", conftab[i].conf->id->name, conftab[i].conf->mac->lib->full_name);
    fprintf(fp_cachesH, "\t.radio = &%s_%s\n", conftab[i].conf->id->name, conftab[i].conf->radio->lib->full_name);
    fprintf(fp_cachesH, "\t}\n");
  }

  fprintf(fp_cachesH, "};\n\n");

  fprintf(fp_cachesH, "char* eventsScales[%d] = {\"\"", event_scale_counter);

  int event_scale_id = 1;

  for(event_scale_id = 1; event_scale_id < event_scale_counter; event_scale_id++) {
    for(sp = symtab; sp < &symtab[NSYMS]; sp++) {
      if (sp != NULL && sp->type != NULL && !strcmp(sp->type, "event_scale") && sp->value == event_scale_id) {
        fprintf(fp_cachesH, ", \"%s\"", sp->name);
      }
    }
  }
  fprintf(fp_cachesH, "};\n\n");



  fprintf(fp_cachesH, "struct fennec_event eventsTable[%d] = {\n\n", event_counter);

  for ( i = 0; i < event_counter; i++) {
    fprintf(fp_cachesH, "\t{\n");
    fprintf(fp_cachesH, "\t.operation = %d,\n", evtab[i].op);
    fprintf(fp_cachesH, "\t.value = %d,\n", evtab[i].value);

    if (evtab[i].scale == NULL) {
      fprintf(fp_cachesH, "\t.scale = eventsScales[0],\n");
    } else {
      fprintf(fp_cachesH, "\t.scale = eventsScales[%d],\n", evtab[i].scale->value);
    }
    if (evtab[i].addr == UNKNOWN) {
      fprintf(fp_cachesH, "\t.addr = TOS_NODE_ID,\n");
    } else {
      fprintf(fp_cachesH, "\t.addr = %d\n", evtab[i].addr);
    }
    fprintf(fp_cachesH, "\t},\n");
  }

/*
  struct evtab *ev;
  for(ev = evtab; ev < &evtab[NEVS]; ev++) {
    if (ev->name) {

      fprintf(fp_cachesH, "\t}\n");

      fprintf(tmp_confs, "      eventsTable[%d].operation = %s;\n", ev->num-1, relopToLetter(ev->op));
      fprintf(tmp_confs, "      eventsTable[%d].value = %d;\n", ev->num-1, ev->value);

      if (ev->scale == NULL) {
        fprintf(tmp_confs, "      eventsTable[%d].scale = eventsScales[0];\n", ev->num-1);
      } else {
        fprintf(tmp_confs, "      eventsTable[%d].scale = eventsScales[%d];\n", ev->num-1, ev->scale->value);
      }
      if (ev->addr == UNKNOWN) {
        fprintf(tmp_confs, "      eventsTable[%d].addr = TOS_NODE_ID;\n\n", ev->num-1);
      } else {
        fprintf(tmp_confs, "      eventsTable[%d].addr = %d;\n\n", ev->num-1, ev->addr);
      }
      fprintf(fp_cachesH, "\t{\n");
      fprintf(fp_cachesH, "\t,\n");

    } else {
      break;
    }
  }
*/
  fprintf(fp_cachesH, "};\n\n");


  fprintf(fp_cachesH, "nx_struct fennec_policy policies[%d];\n\n", policy_counter);
  fprintf(fp_cachesH, "bool control_unit_support;\n\n");
  fprintf(fp_cachesH, "module_t get_protocol(layer_t layer, conf_t conf);\n\n");
  fprintf(fp_cachesH, "nxle_uint16_t event_mask;\n\n");

  fprintf(fp_cachesH, "void checkEvent() {\n");

  if (policy_counter > 0) {
  	fprintf(fp_cachesH, "    uint8_t i;\n");
	fprintf(fp_cachesH, "    for( i=0; i < %d; i++ ) {\n", policy_counter);
	fprintf(fp_cachesH, "      if (((policies[i].src_conf == ANY) || (policies[i].src_conf == active_state))\n");
	fprintf(fp_cachesH, "         && (policies[i].event_mask == event_mask)) {\n");
	fprintf(fp_cachesH, "        signal PolicyCache.newConf( policies[i].dst_conf );\n");
	fprintf(fp_cachesH, "      }\n");
	fprintf(fp_cachesH, "    }\n");
  }
  fprintf(fp_cachesH, "}\n\n");

  fprintf(fp_cachesH, "bool eventStatus(uint16_t event_num) {\n");

  if (policy_counter > 0) {
    fprintf(fp_cachesH, "    uint8_t i;\n");
    fprintf(fp_cachesH, "    for( i=0; i < %d; i++ ){\n", policy_counter);
    fprintf(fp_cachesH, "      if (((policies[i].src_conf == ANY) || (policies[i].src_conf == active_state)) &&\n");
    fprintf(fp_cachesH, "                                       (policies[i].event_mask & (1 << event_num))) {\n");
    fprintf(fp_cachesH, "        return 1;\n");
    fprintf(fp_cachesH, "      }\n");
    fprintf(fp_cachesH, "    }\n");
    fprintf(fp_cachesH, "    return 0;\n");
  } else {
    fprintf(fp_cachesH, "    return 0;\n");
  }

  fprintf(fp_cachesH, "}\n\n");
  fprintf(fp_cachesH, "#endif\n\n");

  fclose(fp_cachesH);
  fclose(tmp_confs);

}


void generateConfiguration(struct confnode* c) {

  int conf_num = c->counter;

//  if (!strcmp(c->app->type, "keyword")) {
//    conftab[conf_num].app = NULL;
//  } else {
    if (c->app->lib->id == 0) {
      c->app->lib->used = 1;
    }
    conftab[conf_num].conf = c;
//  }

//  if (!strcmp(c->net->type, "keyword")) {
//    conftab[conf_num].net = NULL;
//  } else {
    if (c->net->lib->id == 0) {
      c->net->lib->used = 1;
    } 
    conftab[conf_num].conf = c;
//  }

//  if (!strcmp(c->mac->type, "keyword")) {
//    conftab[conf_num].mac = NULL;
//  } else {
    if (c->mac->lib->id == 0) {
      c->mac->lib->used = 1;
    } 
    conftab[conf_num].conf = c;
//  }

//  if (!strcmp(c->radio->type, "keyword")) {
//    conftab[conf_num].radio = NULL;
//  } else {
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

void generatePolicy(struct policy* p) {

  FILE *tmp_confs = fopen(TEMP_CONF_FILE, "a");

  if (tmp_confs == NULL) {
    fprintf(stderr, "You do not have a permission to write into file: %s\n", TEMP_CONF_FILE);
    exit(1);
  }

  int policy_num = p->counter;

  fprintf(tmp_confs, "      policies[%d].src_conf = %d;\n", policy_num, p->from->value);
  fprintf(tmp_confs, "      policies[%d].event_mask = %d;\n", policy_num, p->mask_l);
  fprintf(tmp_confs, "      policies[%d].dst_conf = %d;\n\n", policy_num, p->to->value);

  if (p->mask_r > -1) {
    ++policy_num;
    fprintf(tmp_confs, "      policies[%d].src_conf = %d;\n", policy_num, p->from->value);
    fprintf(tmp_confs, "      policies[%d].event_mask = %d;\n", policy_num, p->mask_r);
    fprintf(tmp_confs, "      policies[%d].dst_conf = %d;\n\n", policy_num, p->to->value);
  }

  fclose(tmp_confs);
}

void generateInitial(struct initnode *i) {
  active_state = i->init;
}