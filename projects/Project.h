/*
 * Copyright 2014 Augustin Cavalier <waddlesplash>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
#ifndef PROJECTS_PROJECT_H
#define PROJECTS_PROJECT_H

#include "HeidiGlobal.h"

#include <Entry.h>
#include <File.h>
#include <ObjectList.h>
#include <String.h>
#include <StringList.h>

// Predefinitions
class BOutlineListView;

enum project_type {
	TYPE_APP,
	TYPE_SHARED,
	TYPE_STATIC,
	TYPE_DRIVER
};

enum optimize_amount {
	OPTIMIZE_NONE,
	OPTIMIZE_SOME,
	OPTIMIZE_FULL
};

enum warn_amount {
	WARN_NONE,
	WARN_DEFAULT,
	WARN_ALL
};

struct project_data {
	BString					name;
	BString					app_mime_sig;
	project_type			type;
	BObjectList<BEntry>		srcs;
	BObjectList<BEntry>		rdefs;
	BObjectList<BEntry>		rsrcs;
	BStringList				libs;
	BStringList				lib_paths;
	BStringList				system_include_paths;
	BStringList				local_include_paths;
	optimize_amount			optimize;
	BStringList				locales;
	BStringList				defines;
	warn_amount				warnings;
	bool					image_symbols;
	bool					debug_info;
	BStringList				compiler_flags;
	BStringList				linker_flags;
	BString					driver_path;
};

class Project {
public:
	struct project_data	data;
public:
	// Required constructors to have in your subclass:
	// 					Project(entry_ref* fileRef) = 0;

	virtual	status_t	Load() = 0;
	virtual	status_t	Save() = 0;
	
	virtual BString		BuildCommand() = 0;
			BString		DirectoryPath();
	
protected:
			BFile		fFile;
			BEntry		fFileEntry;
};

#endif // PROJECTS_PROJECT_H
