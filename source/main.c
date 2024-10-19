#include <stdio.h>
#include <stdlib.h>

#include "ctemplate.h"

static char *html = 
"<!doctype html>							\n"
"<html dir=\"ltr\" lang=\"ko\">						\n"
"	<head>								\n"
"		<#var1>							\n"
"		<meta charset=\"utf-8\">				\n"
"		<title>새 탭</title>					\n"
"		<style>							\n"
"			body {						\n"
"				background: #FFFFFF;			\n"
"				margin: 0;				\n"
"			}						\n"
"									\n"
"			#backgroundImage {				\n"
"				border: none;				\n"
"				height: 100%;				\n"
"				pointer-events: none;			\n"
"				position: fixed;			\n"
"				top: 0;					\n"
"				visibility: hidden;			\n"
"				width: 100%;				\n"
"			}						\n"
"									\n"
"			[show-background-image] #backgroundImage {	\n"
"				visibility: visible;			\n"
"			}						\n"
"		</style>						\n"
"	</head>								\n"
"	<body>								\n"
"		<iframe id=\"backgroundImage\" src=\"\"></iframe>	\n"
"		<ntp-app></ntp-app>					\n"
"		<script type=\"module\" src=\"new_tab_page.js\"></script>\n"
"		<link rel=\"stylesheet\" href=\"chrome://resources/css/text_defaults_md.css\">\n"
"		<link rel=\"stylesheet\" href=\"chrome://theme/colors.css?sets=ui,chrome\">\n"
"		<link rel=\"stylesheet\" href=\"shared_vars.css\">	\n"
"	</body>								\n"
"</html>";

int main(int argc, char *argv[])
{
	struct cjson_object *object;

	object = cjson_create_object("{\"var1\":\"5\"}");
	if (object == NULL)
		exit(EXIT_FAILURE);

	printf("----------------------------------------------------------\n");
	printf("before render...\n");
	printf("%s\n", html);
	printf("----------------------------------------------------------\n");
	printf("----------------------------------------------------------\n");
	printf("after render...\n");
	printf("%s\n", (html = ctemplate_render(html, object)));
	printf("----------------------------------------------------------\n");

	free(html);

	cjson_destroy_object(object);

	return 0;
}
