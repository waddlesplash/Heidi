/*
 * Copyright 2014 Augustin Cavalier <waddlesplash>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
#ifndef EDITORS_CODEEDITOR_H
#define EDITORS_CODEEDITOR_H

#include "HeidiGlobal.h"
#include "Editor.h"

#include <TextView.h>
#include <ScrollView.h>

class PlainTextEditor : public BTextView, public Editor {
public:
	 					PlainTextEditor(entry_ref* fileRef);

			BView*		View();
			const char*	Name();

			status_t	Load();
			status_t	Save();
	
			void		GoToLine(int32 line);

private:
			BScrollView* fScrollView;
};

#endif // EDITORS_CODEEDITOR_H
