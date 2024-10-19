#ifndef CTEMPLATE_H__
#define CTEMPLATE_H__

#include "Cruzer-S/cjson/cjson.h"

char *ctemplate_render(char *header, struct cjson_object *json);

#endif
