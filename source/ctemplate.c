#include "ctemplate.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Cruzer-S/cstring/cstring.h"

static char *get_next_tag(char *string, char **endptr)
{
	char *start = strstr(string, "<"), *end;

	if (start == NULL)
		return NULL;

	end = start + 1;
	while (*end != '>' && *end != '\0') {
		if (*end == '\"')
			while (*++end != '\"' && *end != '\0') ;

		if (*end == '\'')
			while (*++end != '\'' && *end != '\0') ;

		end++;
	}

	if (*end != '>')
		return NULL;

	if (endptr != NULL)
		*endptr = end;

	return start;
}

static char *find_token(char *start, char *end)
{
	size_t len;
	char *token;

	if (*(start + 1) != '#')
		return NULL;

	if ((start + 2) >= end)
		return NULL;

	len = end - (start + 2);
	token = malloc(len + 1);
	if (token == NULL)
		return NULL;

	strncpy(token, start + 2, len);

	return token;
}

static char *replace_holder(CString str, char *start, char *end,
		   struct cjson_object *json, char *token)
{
	size_t start_offset, end_offset;

	start_offset = start - cstring_get(str);
	end_offset = end - cstring_get(str);

	if ( !cstring_trim(str, start_offset, end_offset + 1) )
		return NULL;

	struct cjson_value *value = cjson_get_by_key(json, token);
	if (value->type != CJSON_VALUE_TYPE_STRING)
		return NULL;

	if ( !cstring_insert(str, start_offset, value->s) )
		return NULL;

	return cstring_get(str) + start_offset + strlen(value->s);
}

char *ctemplate_render(char *html, struct cjson_object *json)
{
	CString string;

	string = cstring_create(html);
	if (string == NULL)
		return NULL;

	for (char *start = cstring_get(string), *end;
	     (start = get_next_tag(start, &end));
	     start = end + 1)
	{
		char *token = find_token(start, end);
		if (token == NULL)
			continue;

		end = replace_holder(string, start, end, json, token);
		if ( !end ) {
			free(token);
			return NULL;
		}
	}

	return cstring_destroy_only(string);
}
