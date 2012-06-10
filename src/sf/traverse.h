/* Swift Fox Compiler v0.2
 * Authors: Marcin Szczodrak, Yiwei Gu, and Vasileios P. Kemerlis
 * Date: May 9, 2010
 */

#ifndef __SF_TRAVERSE_H__
#define __SF_TRAVERSE_H__

#include "sf.h"

void traverse_program(struct program* p, int f, int policy_counter);
void traverse_variables(struct variables* sh, int f);
void traverse_variable(struct variable* sh, int f);
void traverse_confnodes(struct confnodes* c, int f);
void traverse_confnode(struct confnode* c, int f);
void traverse_eventnodes(struct eventnodes* e, int f);
void traverse_eventnode(struct eventnode* e, int f);
void traverse_policies(struct policies* p, int f);
void traverse_policy(struct policy* p, int f);
void traverse_initnode(struct initnode* i, int f);

#endif
