/* Swift Fox Compiler v0.2
 * Authors: Marcin Szczodrak
 * Date: May 9, 2010
 */

#ifndef __CODE_GEN_H__
#define __CODE_GEN_H__
#define TEMP_CONF_FILE	"/tmp/tmp_conf_file_sfc"

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
#include "sf.h"
#include "traverse.h"

extern int conf_counter;
extern int module_id_counter;
extern int event_scale_counter;

extern FILE* tmp_confs;

void setFiles();
void setFennecExtra();

void finishCodeGeneration(int policy_counter);

void generateConfiguration(struct confnode* c);

void generateCaches(int event_counter, int policy_counter);

void generateModules();

void generateDefaultParams();

void generateEvent();

void generateInitial(struct initnode *i);

void generateFennecEngineC();
void generateEventC();

void generateFennecEngineP();
void generateEventP();

void generateParams();
void generateGlobals();

#endif
