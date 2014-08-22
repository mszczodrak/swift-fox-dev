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


#include <stdio.h>
#include <string.h>
#include "traverse.h"
#include "sem_check.h"
#include "code_gen.h"
#include "utils.h"

/** 
AST (Abstract Syntax Tree) traversal; 
main entry point 

\param p pointer to a program structure 

\param f type of traversar (TREE_TRAVERSE, TREE_CHECK_SEMANTIC, TREE_GENERATE_CODE)

\param policy_counter number of policies
*/
void
traverse_program(struct program* p, int f, int policy_counter){
	if (p != NULL) {
		switch (f) {
			/** 
			plain traversal 
			*/
			case TREE_TRAVERSE:
				if (sfc_debug) {
					printf("traverse: first pass (%d)\n", f);
				}
				traverse_processnodes(p->defcon, f);
				traverse_statenodes(p->defstate, f);
				traverse_policies(p->defpol, f);
				traverse_initnode(p->init, f);
				break;
			/** 
			traversal for semantic checking 
			*/
			case TREE_CHECK_SEMANTIC:
				if (sfc_debug) {
					printf("traverse: check seminatic (%d)\n", f);
				}
				/** 
				zero the mapping structure 
				*/
				init_sem_conf();
				/** 
				zero the mapping structure 
				*/
				init_sem_evt();
				
				traverse_variables(p->vars, f);
				traverse_processnodes(p->defcon, f);
				traverse_statenodes(p->defstate, f);
				traverse_policies(p->defpol, f);
				traverse_initnode(p->init, f);
				break;

			/**
			traversal for code generation 
			*/
			case TREE_GENERATE_CODE:
				if (sfc_debug) {
					printf("traverse: generate code (%d)\n", f);
				}
				setFiles();

				initCodeGeneration();
				initDataStorageH();
				initDataStorageValues();

				initGlobalDataH();
				traverse_variables(p->vars, f);
				finishGlobalDataH();

				switchGlobalToLocalDataStorage();

				traverse_processnodes(p->defcon, f);
				traverse_statenodes(p->defstate, f);
				traverse_policies(p->defpol, f);
				traverse_initnode(p->init, f);
				finishDataStorageValues();
				finishCodeGeneration(policy_counter);
				break;
			/** 
			make the compiler happy 
			*/
			default:
				printf("traverse: UNNOWN STATE (%d)\n", f);
				break;
		}
	}
}

/** 
shared variables traversal 

\param sh pointer to header of a list of variables

\param f type of traversar (TREE_TRAVERSE, TREE_CHECK_SEMANTIC, TREE_GENERATE_CODE)
*/
void
traverse_variables(struct variables* sh, int f) {
        if (sh != NULL){
                switch (f) {
                        case TREE_TRAVERSE:
                                traverse_variables(sh->vars, f);
                                traverse_variable(sh->var, f);
                                break;

                        case TREE_CHECK_SEMANTIC:
                                traverse_variables(sh->vars, f);
                                traverse_variable(sh->var, f);
                                break;

                        case TREE_GENERATE_CODE:
                                traverse_variables(sh->vars, f);
                                traverse_variable(sh->var, f);
                                break;

                        default:
                                break;
                }
        }
}

/** 
inspects a single variable

\param sh pointer to a variable structure

\param f type of traversar (TREE_TRAVERSE, TREE_CHECK_SEMANTIC, TREE_GENERATE_CODE)
*/
void
traverse_variable(struct variable* sh, int f) {
	switch (f) {
	case TREE_TRAVERSE:
		break;

	case TREE_CHECK_SEMANTIC:
		break;

	case TREE_GENERATE_CODE:
		addGlobalVariable(sh);
		break;

	default:
		break;
	}
}


/** 
configuration traversal

\param c pointer to header of a list of configuration

\param f type of traversar (TREE_TRAVERSE, TREE_CHECK_SEMANTIC, TREE_GENERATE_CODE)
*/

void
traverse_processnodes(struct processnodes* c, int f) {	
	if (c != NULL){
		switch (f) {
		case TREE_TRAVERSE:
			printf("1");
			traverse_process(c->conf, f);
			printf("2");
			traverse_processnodes(c->confs, f);
			break;

		case TREE_CHECK_SEMANTIC:
			traverse_process(c->conf, f);
			traverse_processnodes(c->confs, f);
			break;

		case TREE_GENERATE_CODE:
			traverse_process(c->conf, f);
			traverse_processnodes(c->confs, f);
			break;
			
		default:
			break;
		}
	} else {
		switch(f) {
		case TREE_CHECK_SEMANTIC:
			checkControlState();	
			break;

		default:
			break;
		}

	}
}


int updateModuleVariables(struct modtab *mp) {
	struct variables *lvar = mp->lib->variables;
	struct variables *mvar = mp->variables;
	int number_of_variables = 0;

	if (sfc_debug) {
		printf("\tModule %s\n", mp->name);
		printf("\t\tTYPE\tNAME\t\tVALUE\t\tINIT\tOFFSET\tCLASS_TYPE\tFULL_NAME\n");
	}

	while (lvar != NULL) {
		printf("Checking %s %s\n", mvar->var->name, lvar->var->name);

		/* case when we use global variable */
		if (mvar != NULL && mvar->var->class_type == TYPE_VARIABLE_GLOBAL) {
			/* this already points to global variable, so should
			 * be fine; just check if the type matches */
			if (mvar->var->type != lvar->var->type) {
				if (sfc_debug) {
					printf("type mismatch %d vs %d\n", mvar->var->type, lvar->var->type);
				}
				fprintf(stderr, "module %s got variable %s of type %s, while the library expects type %s for variable %s\n",
					mp->name,
					mvar->var->name,
					type_name(mvar->var->type),
					type_name(lvar->var->type),
					lvar->var->name);
				exit(1);
			}
			/* still copy the application perspective name */
			struct variable *global_var = mvar->var;
			mvar->var = malloc(sizeof(struct variable));
			memcpy(mvar->var, global_var, sizeof(struct variable));
			mvar->var->cap_name = lvar->var->cap_name;
		}

		/* case when we use a constant as a variable */
		if (mvar != NULL && mvar->var->class_type == TYPE_VARIABLE_LOCAL) {
			mvar->var->type = lvar->var->type;	
			mvar->var->name = lvar->var->name;
			mvar->var->length = lvar->var->length;
			mvar->var->cap_name = lvar->var->cap_name;
			mvar->var->offset = variable_memory_offset;
			variable_memory_offset += (type_size(lvar->var->type) * lvar->var->length);
		}

		/* case when mvar is missing, so copy the lvar */
		if (mvar == NULL) {
			mvar = malloc(sizeof(struct variables));
			mvar->vars = NULL;
			mvar->var = malloc(sizeof(struct variable));
			memcpy(mvar->var, lvar->var, sizeof(struct variable));
			mvar->var->offset = variable_memory_offset;
			variable_memory_offset += (type_size(lvar->var->type) * lvar->var->length);
		}

		if (sfc_debug) {
			printf("\t\t%d \t%-10s \t%-10.1Lf \t%d \t%d \t%-10d \t%s\n", mvar->var->type,
			mvar->var->name, mvar->var->value, mvar->var->init, mvar->var->offset,
			mvar->var->class_type, mvar->var->cap_name);
		}

		if (mvar != NULL) {
			mvar = mvar->vars;
		}
		lvar = lvar->vars;
		number_of_variables++;
	}

	if (mvar != NULL) {
		fprintf(stderr, "more variables defined that declared\n");
		exit(1);
	}
	return number_of_variables;
}

void updateProcessVariables(struct confnode* c) {
	if (sfc_debug) {
		printf("\nProcess %s\n", c->name);
	}

	c->app_var_num = updateModuleVariables(c->app);
	c->net_var_num = updateModuleVariables(c->net);
	c->am_var_num = updateModuleVariables(c->am);
}


/** 
visit a single configuration

\param c pointer to a configuration structure

\param f type of traversar (TREE_TRAVERSE, TREE_CHECK_SEMANTIC, TREE_GENERATE_CODE)
*/

void
traverse_process(struct confnode* c, int f) {	
	switch (f) {
		case TREE_TRAVERSE:
			updateProcessVariables(c);
			break;

		case TREE_CHECK_SEMANTIC:
			checkConfiguration(c);
			checkConfigurationModules(c);
			break;
        
		case TREE_GENERATE_CODE:
			break;

		default:
                        break;
	}
}


void
traverse_statenodes(struct statenodes* s, int f) {	
	if (s != NULL){
		switch (f) {
		case TREE_TRAVERSE:
			traverse_statenodes(s->states, f);
			traverse_statenode(s->state, f);
			break;

		case TREE_CHECK_SEMANTIC:
			traverse_statenodes(s->states, f);
			traverse_statenode(s->state, f);
			break;

		case TREE_GENERATE_CODE:
			traverse_statenodes(s->states, f);
			traverse_statenode(s->state, f);
			break;
			
		default:
			break;
		}
	} else {
		switch(f) {
		case TREE_CHECK_SEMANTIC:
			break;

		default:
			break;
		}

	}
}


void
traverse_statenode(struct statenode* s, int f) {	
	switch (f) {
		case TREE_TRAVERSE:
			break;

		case TREE_CHECK_SEMANTIC:
			checkState(s);
			break;
        
		case TREE_GENERATE_CODE:
			break;

		default:
                        break;
	}
}



/** 
policy traversal

\param p pointer to header of a list of policies

\param f type of traversar (TREE_TRAVERSE, TREE_CHECK_SEMANTIC, TREE_GENERATE_CODE)
*/
void traverse_policies(struct policies* p, int f) {
	if (p != NULL){
		switch (f) {
			case TREE_TRAVERSE:
				traverse_policies(p->pols, f);
				traverse_policy(p->pol, f);
                                break;

			case TREE_CHECK_SEMANTIC:
				traverse_policies(p->pols, f);
				traverse_policy(p->pol, f);
                                break;
        
			case TREE_GENERATE_CODE:
				traverse_policies(p->pols, f);
				traverse_policy(p->pol, f);
                                break;

			default:
				break;
		}
	}
}

/** 
visit a policy definition

\param p pointer to single policy structure

\param f type of traversar (TREE_TRAVERSE, TREE_CHECK_SEMANTIC, TREE_GENERATE_CODE)
*/
void
traverse_policy(struct policy* p, int f) {
	switch (f) {
        	case TREE_TRAVERSE:
			break;

       		case TREE_CHECK_SEMANTIC:
			checkPolicy(p);
			updateStatesWithEvents(p);
			break;
        
       		case TREE_GENERATE_CODE:
			proc_policy(p);
			break;

       		default:
			break;
	}
}
/** 
initial node visit

\param i pointer to the initial state

\param f type of traversar (TREE_TRAVERSE, TREE_CHECK_SEMANTIC, TREE_GENERATE_CODE)
*/
void
traverse_initnode(struct initnode *i, int f) {
	switch (f) {
        	case TREE_TRAVERSE:
			break;

       		case TREE_CHECK_SEMANTIC:
			checkInitial(i);
			break;
        
       		case TREE_GENERATE_CODE:
			generateInitial(i);
			break;

       		default:
			break;
	}
}
