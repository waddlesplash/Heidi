/*
 * Copyright 2015 Augustin Cavalier <waddlesplash>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
#ifndef EDITORS_CODEEDITOR_LANGUAGES_H
#define EDITORS_CODEEDITOR_LANGUAGES_H

#include <String.h>

#include "HeidiGlobal.h"

struct language_data {
	const char* name;
	int sclex_id;
	const char* keywords;
	const char* types;
};

language_data* language_for_extension(BString ext);
status_t languages_init();

#endif // EDITORS_CODEEDITOR_LANGUAGES_H
