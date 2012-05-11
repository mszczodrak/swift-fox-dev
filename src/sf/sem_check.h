/* Swift Fox Compiler v0.2
 * Authors: Marcin Szczodrak and Vasileios P. Kemerlis
 * Date: May 9, 2010
 */

#ifndef __SEM_CHECK_H__
#define __SEM_CHECK_H__

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
#include "traverse.h"

/* adapted from code_gen.h for semantic checking */

void init_sem_conf(void);
void init_sem_evt(void);
void checkConfiguration(struct confnode *c);
void checkEventCondition(struct eventnode *e);
void checkPolicy(struct policy *p);
void checkInitial(struct initnode *i);

#endif
