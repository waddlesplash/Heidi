/*
 * Copyright 2014 Augustin Cavalier <waddlesplash>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
#ifndef EDITORS_EDITOR_H
#define EDITORS_EDITOR_H

#include "HeidiGlobal.h"

#include <File.h>
#include <String.h>
#include <Entry.h>

// Predefinitions
class BView;

class Editor {
public:
	// Required constructors to have in your subclass:
	// 					Editor(entry_ref* fileRef) = 0;

	virtual	BView*		View() = 0;

	virtual	status_t	Load() = 0;
	virtual	status_t	Save() = 0;
	
	virtual	void		GoToLine(int32 line) = 0;
	
protected:
			BFile		fFile;
			BString 	fFileName;
};

#endif // EDITORS_EDITOR_H
