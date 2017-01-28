/*
 * Copyright 2014-2016 Augustin Cavalier <waddlesplash>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
#include "Editor.h"

#include <TabView.h>

void
Editor::ContentsModified()
{
	if (fModified)
		return;
	if (fTab == NULL)
		return;
	if (fLabel.IsEmpty())
		fLabel = BString(fTab->Label());

	BString modifiedLabel = fLabel;
	modifiedLabel += "*";
	fTab->SetLabel(modifiedLabel.String());
	fModified = true;
}


void
Editor::ContentsSaved()
{
	if (!fModified)
		return;
	if (fTab == NULL)
		return;
	if (fLabel.IsEmpty())
		return;

	fTab->SetLabel(fLabel.String());
	fModified = false;
}
