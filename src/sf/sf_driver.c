/* Swift Fox Compiler v0.1
 * Authors: Marcin Szczodrak and Vasileios P. Kemerlis
 * Date: April 12, 2010
 */

#include <stdio.h>
#include <stdlib.h>
#include "sf.h"

/* day 0; time 0 */
int
main(int argc, char *argv[] ) {

	/* Argument checking */
  	if (argc != ARGC_MAX) {

		(void)fprintf(stderr, "%s: no input files\n\n", argv[0]);
		(void)fprintf(stderr, "If your source program is located in");
		(void)fprintf(stderr, " sample.sfp and sample.sfl, then run:");
  		(void)fprintf(stderr, "\n\n$ %s sample\n\n", argv[0]);
                exit(1);
       	}


	/* Invoke the parser */
       	start_parser(argc, argv);
}
