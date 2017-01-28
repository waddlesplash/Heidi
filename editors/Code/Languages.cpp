 /*
 * Copyright 2015 Augustin Cavalier <waddlesplash>
 * All rights reserved. Distributed under the terms of the MIT license.
 */

#include <Message.h>
#include <scintilla/SciLexer.h>

#include "Languages.h"

BMessage* all_languages = NULL;

language_data* language_for_extension(BString ext)
{
	if (all_languages == NULL)
		languages_init();

	void* ret = NULL;
	status_t status = all_languages->FindPointer(ext.ToLower(), &ret);
	if (status == B_OK)
		return (language_data*)ret;
	return NULL;
}


// #pragma mark Languages initialization

#define E(EXT) \
	all_languages->AddPointer(EXT, temp);

#define ADD_LANGUAGE(NAME) \
	temp = new language_data; \
	temp->name = NAME ## _NAME; \
	temp->sclex_id = NAME ## _SCLEX_ID; \
	temp->keywords = NAME ## _KEYWORDS; \
	temp->types = NAME ## _TYPES; \
	NAME ## _EXTENSIONS

status_t languages_init()
{
	if (all_languages != NULL)
		return B_OK;

	all_languages = new BMessage;
	language_data* temp = NULL;

	#include "languages/cpp.h"
	#include "languages/shell.h"
	#include "languages/recipe.h"
}
