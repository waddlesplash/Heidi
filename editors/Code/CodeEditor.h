/*
 * Copyright 2014 Kacper Kasper <kacperkasper@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
#ifndef EDITORS_CODEEDITOR_H
#define EDITORS_CODEEDITOR_H

#include "HeidiGlobal.h"
#include "Editor.h"

#include <scintilla/ScintillaView.h>

class CodeEditor : public BScintillaView, public Editor {
public:
	 					CodeEditor(entry_ref* fileRef);

			BView*		View();

			status_t	Load();
			status_t	Save();

			void		GoToLine(int32 line);

			void		NotificationReceived(SCNotification* n);
};

#endif // EDITORS_CODEEDITOR_H
