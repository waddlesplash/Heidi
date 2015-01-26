/*
 * Copyright 2014 Kacper Kasper <kacperkasper@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
#include "CodeEditor.h"
#include "Languages.h"

#include <SciLexer.h>


CodeEditor::CodeEditor(entry_ref* fileRef)
	: BScintillaView(fileRef->name, 0, true, true, B_NO_BORDER)
{
	fFile = BFile(fileRef, B_READ_WRITE);
	fFileEntry = BEntry(fileRef);

	Load();

	// TODO Read color schemes from XML
  	// We need to set font names explicitly, otherwise Scintilla
  	// won't allocate styled fonts
  	SendMessage(SCI_STYLESETFONT, STYLE_DEFAULT, (sptr_t) "DejaVu Sans Mono");
	SendMessage(SCI_STYLESETFORE, 0, 0x808080);	// White space
	SendMessage(SCI_STYLESETFONT, 1, (sptr_t) "DejaVu Sans Mono");
	SendMessage(SCI_STYLESETFORE, 1, 0x007F00);	// Comment
	SendMessage(SCI_STYLESETITALIC, 1, 1);	// Comment
	SendMessage(SCI_STYLESETFONT, 2, (sptr_t) "DejaVu Sans Mono");
	SendMessage(SCI_STYLESETFORE, 2, 0x007F00);	// Line comment
	SendMessage(SCI_STYLESETITALIC, 2, 1);	// Line comment
	SendMessage(SCI_STYLESETFONT, 3, (sptr_t) "DejaVu Sans Mono");
	SendMessage(SCI_STYLESETFORE, 3, 0x3F703F);	// Doc comment
	SendMessage(SCI_STYLESETITALIC, 3, 1);	// Doc comment
	SendMessage(SCI_STYLESETFORE, 4, 0x7F7F00);	// Number
	SendMessage(SCI_STYLESETFONT, 5, (sptr_t) "DejaVu Sans Mono");	// Keyword
	SendMessage(SCI_STYLESETFORE, 5, 0x7F0000);	// Keyword
	SendMessage(SCI_STYLESETBOLD, 5, 1);	// Keyword
	SendMessage(SCI_STYLESETFONT, SCE_C_WORD2, (sptr_t) "DejaVu Sans Mono");	// Keyword
	SendMessage(SCI_STYLESETFORE, SCE_C_WORD2, 0x7F0000);	// Keyword
	SendMessage(SCI_STYLESETBOLD, SCE_C_WORD2, 1);	// Keyword
	SendMessage(SCI_STYLESETFORE, 6, 0x7F007F);	// String
	SendMessage(SCI_STYLESETFORE, 7, 0x7F007F);	// Character
	SendMessage(SCI_STYLESETFORE, 8, 0x804080);	// UUID
	SendMessage(SCI_STYLESETFORE, 9, 0x007F7F);	// Preprocessor
	SendMessage(SCI_STYLESETFONT, 10, (sptr_t) "DejaVu Sans Mono");
	SendMessage(SCI_STYLESETFORE,10, 0x000000);	// Operators
	SendMessage(SCI_STYLESETBOLD,10, 1);	// Operators
	SendMessage(SCI_STYLESETFORE,11, 0x000000);	// Identifiers

	// Get language definition
	BString name(fileRef->name), ext;
	name.CopyInto(ext, name.FindLast('.') + 1, name.Length());
	language_data* lang = language_for_extension(ext);
	if (lang != NULL) {
		SendMessage(SCI_SETLEXER, lang->sclex_id, 0);
		SendMessage(SCI_SETKEYWORDS, 0, (sptr_t)lang->keywords);
		SendMessage(SCI_SETKEYWORDS, 1, (sptr_t)lang->types);
	}

	ToggleLineHighlight();
	ToggleLineNumbers(40);

	SendMessage(SCI_SETTABWIDTH, 4, 0);
	//SendMessage(SCI_SETINDENTATIONGUIDES, SC_IV_REAL, 0);
		// Still ugly, needs fix in Scintilla
}


BView*
CodeEditor::View()
{
	return this;
}


status_t
CodeEditor::Load()
{
	off_t size;
	fFile.GetSize(&size);
	fFile.Seek(0, SEEK_SET);

	char* buffer = new char[size];
	off_t len = fFile.Read(buffer, size);

	SetText(buffer);
	delete[] buffer;
	SetSavePoint();

	return (len == size) ? B_OK : B_ERROR;
}


status_t
CodeEditor::Save()
{
	off_t size = SendMessage(SCI_GETLENGTH, 0, 0);
	fFile.SetSize(size);
	fFile.Seek(0, SEEK_SET);

	char* buffer = new char[size + 1];
	GetText(0, size + 1, buffer);
	off_t len = fFile.Write(buffer, size);
	delete[] buffer;
	SetSavePoint();
	fFile.Flush();

	return (len == size) ? B_OK : B_ERROR;
}


void
CodeEditor::GoToLine(int32 line)
{
	SendMessage(SCI_GOTOLINE, line, 0);
}


void
CodeEditor::NotificationReceived(SCNotification* n)
{
}

