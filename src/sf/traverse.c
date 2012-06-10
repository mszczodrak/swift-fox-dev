/* Swift Fox Compiler v0.2
 * Authors: Marcin Szczodrak, Yiwei Gu, and Vasileios P. Kemerlis
 * Date: May 9, 2010
 */

#include <stdio.h>
#include <string.h>
#include "traverse.h"
#include "sem_check.h"
#include "code_gen.h"

/* AST traversal; main entry point */
void
traverse_program(struct program* p, int f, int policy_counter){
	if (p != NULL) {
		switch (f) {
			/* plain traversal */
			case TREE_TRAVERSE:
				traverse_confnodes(p->defcon, f);
				traverse_eventnodes(p->defeve, f);
				traverse_policies(p->defpol, f);
				traverse_initnode(p->init, f);
				break;
			/* traversal for semantic checking */
			case TREE_CHECK_SEMANTIC:
				/* zero the mapping structure */
				init_sem_conf();
				/* zero the mapping structure */
				init_sem_evt();
				
				traverse_confnodes(p->defcon, f);
				traverse_eventnodes(p->defeve, f);
				traverse_policies(p->defpol, f);
				traverse_initnode(p->init, f);
				break;
			/* traversal for code generation */
			case TREE_GENERATE_CODE:
				setFiles();
				traverse_variables(p->vars, f);
				traverse_confnodes(p->defcon, f);
				traverse_eventnodes(p->defeve, f);
				traverse_policies(p->defpol, f);
				traverse_initnode(p->init, f);
				finishCodeGeneration(policy_counter);
				break;
			/* make the compiler happy */
			default:
				break;
		}
	}
}

/* shared variables traversal */
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

void
traverse_variable(struct variable* sh, int f) {
        switch (f) {
                case TREE_TRAVERSE:
                        break;

                case TREE_CHECK_SEMANTIC:
                        break;

                case TREE_GENERATE_CODE:
        //                generateSharedVariable(sh);
                        break;

                default:
                        break;
        }
}


/* configuration traversal */
void
traverse_confnodes(struct confnodes* c, int f) {	
	if (c != NULL){
		switch (f) {
			case TREE_TRAVERSE:
				traverse_confnodes(c->confs, f);
				traverse_confnode(c->conf, f);
				break;

			case TREE_CHECK_SEMANTIC:
				traverse_confnodes(c->confs, f);
				traverse_confnode(c->conf, f);
				break;

			case TREE_GENERATE_CODE:
				traverse_confnodes(c->confs, f);
				traverse_confnode(c->conf, f);
				break;
			
			default:
				break;
		}
	} 
}

void
traverse_confnode(struct confnode* c, int f) {	
	switch (f) {
		case TREE_TRAVERSE:
			break;

		case TREE_CHECK_SEMANTIC:
			checkConfiguration(c);
			break;
        
		case TREE_GENERATE_CODE:
			generateConfiguration(c);
			break;

		default:
                        break;
	}
}

/* event-condition traversal */
void
traverse_eventnodes(struct eventnodes* e, int f) {
	if (e != NULL){
		switch (f) {
			case TREE_TRAVERSE:
				traverse_eventnodes(e->evens, f);
				traverse_eventnode(e->even, f);
                                break;

			case TREE_CHECK_SEMANTIC:
				traverse_eventnodes(e->evens, f);
				traverse_eventnode(e->even, f);
                                break;
        
			case TREE_GENERATE_CODE:
				traverse_eventnodes(e->evens, f);
				traverse_eventnode(e->even, f);
                                break;

			default:
				break;
		}
	}
}

void
traverse_eventnode(struct eventnode* e, int f) {
	switch (f) {
        	case TREE_TRAVERSE:
			break;

		case TREE_CHECK_SEMANTIC:
			checkEventCondition(e);
			break;
        
		case TREE_GENERATE_CODE:
			e->src->lib->used = 1;
			break;

       		default:
			break;
	}
}

/* policy traversal */
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

void
traverse_policy(struct policy* p, int f) {
	switch (f) {
        	case TREE_TRAVERSE:
			break;

       		case TREE_CHECK_SEMANTIC:
			checkPolicy(p);
			break;
        
       		case TREE_GENERATE_CODE:
			proc_policy(p);
			break;

       		default:
			break;
	}
}

/* initial node traversal */
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
