#ifndef _SF_UTILS_H_
#define _SF_UTILS_H_

#include "y.tab.h"

char * type_name(int type_value);
char *get_full_path(char *ffsrc_relative);
char *get_sfc_path(char *file1, char *file2);
int create_dir(char *ffsrc_relative);
char *relopToLetter(int i);


#endif
