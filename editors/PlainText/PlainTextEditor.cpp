/*
 * Copyright 2014 Augustin Cavalier <waddlesplash>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
#include "PlainTextEditor.h"


PlainTextEditor::PlainTextEditor(entry_ref* fileRef)
	: BTextView("PlainTextEditor", be_fixed_font, NULL, B_WILL_DRAW | B_PULSE_NEEDED)
{
	fFile = BFile(fileRef, B_READ_WRITE);
	fFileEntry = BEntry(fileRef);

	BTextView::SetWordWrap(false);
	fScrollView = new BScrollView(fileRef->name, this, B_NAVIGABLE, true, true);
	Load();
}


BView*
PlainTextEditor::View()
{
	return fScrollView;
}


status_t
PlainTextEditor::Load()
{
	off_t size;
	fFile.GetSize(&size);
	fFile.Seek(0, SEEK_SET);

	char* buffer = new char[size + 1];
	off_t len = fFile.Read(buffer, size);

	buffer[size] = '\0';
	BTextView::SetText(buffer);
	delete[] buffer;
	return (len == size) ? B_OK : B_ERROR;
}


status_t
PlainTextEditor::Save()
{
	off_t size = BTextView::TextLength();
	fFile.SetSize(size);
	fFile.Seek(0, SEEK_SET);

	off_t len = fFile.Write(BTextView::Text(), size);
	fFile.Flush();

	return (len == size) ? B_OK : B_ERROR;
}


void
PlainTextEditor::GoToLine(int32 line)
{
	BTextView::GoToLine(line);
}

