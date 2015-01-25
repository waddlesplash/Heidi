/*
 * Copyright 2014 Augustin Cavalier <waddlesplash>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
#ifndef EDITORS_PLAINTEXTEDITOR_H
#define EDITORS_PLAINTEXTEDITOR_H

#include "HeidiGlobal.h"
#include "Editor.h"

#include <TextView.h>
#include <ScrollView.h>

class PlainTextEditor : public BTextView, public Editor {
public:
	 					PlainTextEditor(entry_ref* fileRef);

			BView*		View();

			status_t	Load();
			status_t	Save();

			void		GoToLine(int32 line);

private:
			BScrollView* fScrollView;
};

#endif // EDITORS_PLAINTEXTEDITOR_H
