/*
 * Copyright 2014 Augustin Cavalier <waddlesplash>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
#include "EditorFactory.h"

#include "PlainTextEditor.h"

Editor*
EditorFactory::Create(entry_ref* file)
{
	return new PlainTextEditor(file);
}
