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


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <ctype.h>
#include <stdint.h>
#include "utils.h"
#include "dbg_utils.h"
#include "sf.h"
#include "parser.h"


/* prints all variables */
void print_variables(int class_type) {

        /* iterator */
        struct variable *vp = NULL;

	if (!sfc_debug) {
		return;
	}

	printf("ID\tTYPE\t\tNAME\t\tVALUE\t\tINIT\tOFFSET\tUSED\tCLASS_TYPE\tFULL_NAME\n");

	/* loop */
	for(vp = vartab; vp < &vartab[NVARS]; vp++) {
		/* is it free */
		if(!vp->name) {
			break;
		}

		if (class_type != 0 && vp->class_type != class_type) {
			continue;
		}

		printf("%d \t%-10s \t%-10s \t%-10.1Lf \t%d \t%d \t%d \t%-10d \t%s\n",
				vp->id, type_name(vp->type), vp->name, vp->value, vp->init,
				vp->offset, vp->used, vp->class_type, vp->cap_name);
	}

	printf("\n");
}


void print_process_module(struct modtab *mp) {
	struct variables *mvar = mp->variables_end;

	if (!sfc_debug) {
		return;
	}

	printf("\tModule %s\n", mp->name);
	printf("\t\tTYPE\tNAME\t\tVALUE\t\tINIT\tOFFSET\tUSED\tCLASS_TYPE\tFULL_NAME\n");

	for(; mvar != NULL; mvar = mvar->parent) {
		printf("\t\t%d \t%-10s \t%-10.1Lf \t%d \t%d \t%d \t%-10d \t%s\n", mvar->var->type,
		mvar->var->name, mvar->var->value, mvar->var->init, mvar->var->offset,
		mvar->var->used, mvar->var->class_type, mvar->var->cap_name);
	}
	printf("\n");
}

void print_process(struct confnode* c) {
	if (!sfc_debug) {
		return;
	}

	printf("Process %s\n", c->name);
	print_process_module(c->app);
	print_process_module(c->net);
	print_process_module(c->am);

}
