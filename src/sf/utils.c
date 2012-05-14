#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include "utils.h"
#include "sf.h"


char * type_name(int type_value) {
  switch(type_value) {
    case TYPE_UINT8_T:
      return "uint8_t";

    case TYPE_UINT16_T:
      return "uint16_t";

    case TYPE_UINT32_T:
      return "uint32_t";

    case TYPE_FLOAT:
      return "float";

    case TYPE_DOUBLE:
      return "double";

    default:
      return "";
  }
}

char *get_full_path(char *ffsrc_relative) {
  char *fennec_fox_lib = getenv("FENNEC_FOX_LIB");
  char *tmp;

  if (fennec_fox_lib == NULL) {
    fprintf(stderr, "\n\nFENNEC_FOX_LIB is not set!\n");
    exit(1);
  }

  tmp = malloc(strlen(ffsrc_relative) + strlen(fennec_fox_lib) + 2);
  sprintf(tmp, "%s/%s", fennec_fox_lib, ffsrc_relative);
  return tmp;
}

char *get_sfc_path(char *file1, char *file2) {
  char *fennec_fox_lib = getenv("FENNEC_FOX_LIB");
  char *tmp;

  if (fennec_fox_lib == NULL) {
    fprintf(stderr, "\n\nFENNEC_FOX_LIB is not set!\n");
    exit(1);
  }

  tmp = malloc(strlen(fennec_fox_lib) + strlen("Fennec/sfc/") + 
					strlen(file1) + strlen(file2) + 2);
  sprintf(tmp, "%s/%sFennec/sfc/%s", fennec_fox_lib, file1, file2);
  return tmp;
}




int create_dir(char *ffsrc_relative) {
  struct stat st;
  char *dirpath = get_full_path(ffsrc_relative);
  int status = 0;
  if (stat(dirpath, &st) != 0) {
    status = mkdir(dirpath, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
  }
  free(dirpath);
  return status;
}
