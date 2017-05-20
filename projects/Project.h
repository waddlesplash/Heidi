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

class Project {
public:
	BString				Name;
	bool				IsApp;
	BStringList			SystemIncludePaths;
	BStringList			LocalIncludePaths;
	BStringList			Defines;
	BObjectList<BEntry>	Files;

public:
						Project();
	// Required constructors to have in subclasses:
	// 					Project(entry_ref* fileRef);

	// Generic functions
	BString				DirectoryPath();

	virtual	status_t	Load() = 0;
	virtual BString		BuildCommand(BString objDir = DEFAULT_BUILD_DIR,
								int jobs = 1) = 0;

protected:
			BEntry		fFileEntry;
};

#endif // PROJECTS_PROJECT_H
