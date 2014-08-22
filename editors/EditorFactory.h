/*
 * Copyright 2014 Augustin Cavalier <waddlesplash>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
#ifndef EDITORS_EDITORFACTORY_H
#define EDITORS_EDITORFACTORY_H

#include "HeidiGlobal.h"
#include "Editor.h"

#include <Entry.h>

class EditorFactory {
public:
	static 	Editor*		Create(entry_ref* file);
};

#endif // EDITORS_EDITORFACTORY_H
