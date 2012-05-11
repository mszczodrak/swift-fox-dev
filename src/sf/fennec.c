#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

        char *fennec_fox_lib = getenv("FENNEC_FOX_LIB");

        if (fennec_fox_lib == NULL) {
                fprintf(stderr, "\n\nFENNEC_FOX_LIB is not set!\n");
                exit(1);
        }

	int i = 1;
	char *command = malloc(strlen(fennec_fox_lib) + 9 );
	sprintf(command, "make -C %s", fennec_fox_lib);

	while(argv[i]!=NULL) {
		strcat(command, " ");
		strcat(command, argv[i]);
		i++;
	}

	printf("%s\n", command);
	return system(command);
}
