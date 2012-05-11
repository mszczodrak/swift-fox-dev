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
