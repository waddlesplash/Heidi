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

class Project {
public:
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
public:
	// Required constructors to have in your subclass:
	// 					Project(entry_ref* fileRef) = 0;

	virtual	status_t	Load() = 0;
	virtual	status_t	Save() = 0;
	
	virtual void		BuildTree(BOutlineListView* olv) = 0;
	
	virtual BString		BuildCommand() = 0;
	
protected:
			BFile		fFile;
			BEntry		fFileEntry;
			
			// Data storage
			BString					fName;
			project_type			fType;
			BObjectList<BEntry>		fSrcs;
			BObjectList<BEntry>		fRdefs;
			BObjectList<BEntry>		fRsrcs;
			BStringList				fLibs;
			BStringList				fLibpaths;
			BStringList				fSystemIncludePaths;
			BStringList				fLocalIncludePaths;
			optimize_amount			fOptimizeAmount;
			BStringList				fLocales;
			BStringList				fDefines;
			warn_amount				fWarnings;
			bool					fImageSymbols;
			bool					fDebugInfo;
			BStringList				fCompilerFlags;
			BStringList				fLinkerFlags;
			BString					fDriverPath;
};

#endif // PROJECTS_PROJECT_H
