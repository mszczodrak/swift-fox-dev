/* Swift Fox Compiler v0.2
 * Authors: Marcin Szczodrak and Vasileios P. Kemerlis
 * Date: May 9, 2010
 */

#include "sem_check.h"

/* map configurations to names */
struct symtab *map_conf_id[NSYMS];

/* map event-conditions to names */
struct symtab *map_evt_id[NSYMS];

/* zero map_conf_id */
void
init_sem_conf(void) {
	/* clear */
	(void)memset(map_conf_id,
		0,
		sizeof(struct symtab *) * NSYMS);
}

/* zero map_evt_id */
void
init_sem_evt(void) {
	/* clear */
	(void)memset(map_evt_id,
		0,
		sizeof(struct symtab *) * NSYMS);
}

/* semantic checks for the configuration nodes */
void
checkConfiguration(struct confnode* c) {
	/* iterators */
	int i			= 0;
	struct symtab *sp	= NULL;

	/* flag */
	int found		= 0;

	
	/* traverse the previous configurations */
	while ((i < NSYMS - 1) && (map_conf_id[i] != NULL)) {
		/* check for redeclaration */
		if (map_conf_id[i] == c->id)
			goto conf_err;
		/* next */
		i++;
	}

	/* generate the mapping between name and configuration */
	map_conf_id[i] = c->id;
	
	/* check for undeclared application */
	if (c->app == NULL || c->app->type == NULL || c->app->lib == NULL)
		goto app_err;

	/* check for undeclared applications */
	if (strcmp(c->app->type, "keyword")) {
		/* loop */
		found = 0;
		for (sp = symtab; sp < &symtab[NSYMS]; sp++) 
			if (sp->name &&
				!strcmp(sp->name, c->app->lib->def)) 
				if (sp->type &&
					!strcmp(sp->type, "application")) {
					/* found */
					found = 1;
					break;
				}
		
		/* undeclared application */
		if (!found)
			goto app_err;
	}
	
	/* check for undeclared network */
	if (c->net == NULL || c->net->type == NULL || c->net->lib == NULL)
		goto net_err;
	
	if (strcmp(c->net->type, "keyword")) {
		if (c->net->lib == NULL)
			goto net_err;
		/* loop */
		found = 0;
		for (sp = symtab; sp < &symtab[NSYMS]; sp++)
			if (sp->name &&
				!strcmp(sp->name, c->net->lib->def))
				if (sp->type &&
					!strcmp(sp->type, "network")) {
					/* found */
					found = 1;
					break;
				}

		/* undeclared network */
		if (!found)
			goto net_err;
	}
	
	/* check for undeclared mac */
	if (c->mac == NULL || c->mac->type == NULL || c->mac->lib == NULL)
		goto mac_err;

        /* check for undeclared mac */
        if (strcmp(c->mac->type, "keyword")) {
                /* loop */
                found = 0;
                for (sp = symtab; sp < &symtab[NSYMS]; sp++)
                        if (sp->name &&
                                !strcmp(sp->name, c->mac->lib->def))
                                if (sp->type &&
                                        !strcmp(sp->type, "mac")) {
                                        /* found */
                                        found = 1;
                                        break;
                                }

                /* undeclared mac */
                if (!found)
                        goto mac_err;
        }

	/* check for undeclared network */
	if (c->radio == NULL || c->radio->type == NULL || c->radio->lib == NULL)
		goto radio_err;

        /* check for undeclared radio */
        if (strcmp(c->radio->type, "keyword")) {
		if (c->radio->lib == NULL)
			goto radio_err;

                /* loop */
                found = 0;
                for (sp = symtab; sp < &symtab[NSYMS]; sp++)
                        if (sp->name &&
                                !strcmp(sp->name, c->radio->lib->def))
                                if (sp->type &&
                                        !strcmp(sp->type, "radio")) {
                                        /* found */
                                        found = 1;
                                        break;
                                }

                /* undeclared radio */
                if (!found)
                        goto radio_err;
        }

        /* success */
        return;

conf_err:
	/* redeclaration */
	(void)fprintf(stderr, "error: redeclaration of configuration %s\n",
			c->id->name);
	/* terminate */
	exit(1);

app_err:
	/* undeclared application */
	if (c->app != NULL && c->app->lib != NULL && c->app->lib->name != NULL)
		(void)fprintf(stderr, "error: undeclared application %s\n",
				c->app->lib->name);
	else
		(void)fprintf(stderr, "error: undeclared application in configuration %s\n",
				c->id->name);

	/* terminate */
	exit(1);

net_err:
	/* undeclared network */
	if (c->net != NULL && c->net->lib != NULL && c->net->lib->name != NULL)
		(void)fprintf(stderr, "error: undeclared network %s\n",
				c->net->lib->name);
	else
		(void)fprintf(stderr, "error: undeclared network in configuration %s\n",
				c->id->name);
	/* terminate */
	exit(1);

mac_err:
        /* undeclared mac */
	if (c->mac != NULL && c->mac->lib != NULL && c->mac->lib->name != NULL)
        	(void)fprintf(stderr, "error: undeclared mac %s\n",
                	        c->mac->lib->name);
	else
		(void)fprintf(stderr, "error: undeclared mac in configuration %s\n",
				c->id->name);

        /* terminate */
        exit(1);

radio_err:
        /* undeclared radio */
	if (c->radio != NULL && c->radio->lib != NULL && c->radio->lib->name != NULL)
	        (void)fprintf(stderr, "error: undeclared radio %s\n",
        	                c->radio->lib->name);
	else
		(void)fprintf(stderr, "error: undeclared radio in configuration %s\n",
				c->id->name);

        /* terminate */
        exit(1);
}

void
checkSingleModule(struct confnode *c, struct modtab *mp, 
		struct paramvalue **mod_par_val, struct paramtype *par_type) {

        /* check if there are too many parameters */
        for(; *mod_par_val != NULL; mod_par_val = &(*mod_par_val)->child) {
                /* check if there are more passed parameters then
                 * there are defined variables 
                 */
                if ((par_type == NULL) && (*mod_par_val != NULL)) {
		        (void)fprintf(stderr, "error: Too many parameters in configuration %s in module %s\n",
        	                c->id->name, mp->lib->name);
			/* terminate */
			exit(1);
                        break;
                }

                if (par_type != NULL)
                        par_type = par_type->child;
        }

        /* check if parameters are missing */
        for (; (*mod_par_val == NULL) && (par_type != NULL); 
		par_type = par_type->child, mod_par_val = &(*mod_par_val)->child) {
                if (par_type->def_val->def_valid) {
			/* TODO: add warning message? */
			//printf("adding default param\n");
			/* extend module's parameter list with the 
			 * default values */
			*mod_par_val = calloc(1, sizeof(struct paramvalue));
			(*mod_par_val)->value = par_type->def_val->def_value;
			(*mod_par_val)->child = NULL;
                } else {
			/* parameters are missing and there are no default
			 * values defined to fill the missing ones */
		        (void)fprintf(stderr, "error: Missing parameters in "
				"configuration %s in module %s - default "
					"values are not defined\n",
        	                c->id->name, mp->lib->name);
			/* terminate */
			exit(1);
                }
        }
}

/* semantic check for modules passed to configuration */
void 
checkConfigurationModules(struct confnode *c) {

	/* check application module params */
	checkSingleModule(c, c->app, &(c->app_params), c->app->lib->params);

	/* check network module params */
	checkSingleModule(c, c->net, &(c->net_params), c->net->lib->params);

	/* check mac module params */
	checkSingleModule(c, c->mac, &(c->mac_params), c->mac->lib->params);

	/* check radio module params */
	checkSingleModule(c, c->radio, &(c->radio_params), c->radio->lib->params);

}

/* semantic checks for the event-condition nodes */
void
checkEventCondition(struct eventnode *e) {
	/* iterators */
	int i = 0;
	struct symtab *sp	= NULL;

	/* flag */
	int found		= 0;
	
	/* traverse the previous event-conditions */
	while ((i < NSYMS - 1) && (map_evt_id[i] != NULL)) {
		/* redeclaration */
		if (map_evt_id[i] == e->id)
			goto evt_err;
		/* next */
		i++;
	}

	/* generate the mapping between name and event-condition */
	map_evt_id[i] = e->id;
	
	/* check for undeclared source */

	/* loop */
	found = 0;
	for (sp = symtab; sp < &symtab[NSYMS]; sp++)
		if (sp->name &&
			!strcmp(sp->name, e->src->name))
			if (sp->type &&
				!strcmp(sp->type, "source")) {
				/* found */
				found = 1;
				break;
			}

	/* undeclared source */
	if (!found)
		goto src_err;
	
	/* success */	
	return;

evt_err:
	/* redeclaration */
	(void)fprintf(stderr, "error: redeclaration of event-condition %s\n",
			e->id->name);
	/* terminate */
	exit(1);

src_err:
	/* undeclared source */
	(void)fprintf(stderr, "error: undeclared source %s\n",
			e->src->name);
	/* terminate */
	exit(1);
}

/* semantic checks for the policy nodes */
void
checkPolicy(struct policy *p) {
	/* iterator */
	struct symtab *sp	= NULL;

	/* flag */
	int found		= 0;
	
	/* check the from configuration */
	if (strcmp(p->from->name, "any")) {	
		/* loop */
		found = 0;
		for (sp = symtab; sp < &symtab[NSYMS]; sp++)
			if (sp->name &&
				!strcmp(sp->name, p->from->name))
				if (sp->type &&
					!strcmp(sp->type, "configuration_id")) {
					/* found */
					found = 1;
					break;
				}
	
		/* undeclared from */
		if (!found)
			goto from_conf_err;
	}
	
	/* loop */
	found = 0;
	for (sp = symtab; sp < &symtab[NSYMS]; sp++)
		if (sp->name &&
			!strcmp(sp->name, p->to->name))
			if (sp->type &&
				!strcmp(sp->type, "configuration_id")) {
				/* found */
				found = 1;
				break;
			}

	/* check the to configuration */
	if (!found)
		goto to_conf_err;
	
	/* success */	
	return;

from_conf_err:
	/* undeclared from configuration */
	(void)fprintf(stderr, "error: undeclared 'from' configuration %s\n",
			p->from->name);
	/* terminate */
	exit(1);

to_conf_err:
	/* undeclared to configuration */
	(void)fprintf(stderr, "error: undeclared 'to' configuration %s\n",
			p->to->name);
	/* terminate */
	exit(1);
}

/* semantic checks for the initial node */
void
checkInitial(struct initnode *i) {

	/* iterator */
	struct symtab *sp	= NULL;
	/* flag */
	int found		= 0;
	
	/* loop */
	for (sp = symtab; sp < &symtab[NSYMS]; sp++)
		if (sp->name &&
			!strcmp(sp->name, i->id->name))
			if (sp->type &&
				!strcmp(sp->type, "configuration_id")) {
				/* found */
				found = 1;
				break;
			}
	
	/* check the initial configuration */
	if (!found)
		goto conf_err;
	
	/* done */	
	return;

conf_err:
	/* undeclared initial configuration */
	(void)fprintf(stderr, "error: undeclared 'initial' configuration %s\n",
			i->id->name);
	/* terminate */
	exit(1);
}

void
checkControlState(void) {
	printf("Checking control state\n");

}
