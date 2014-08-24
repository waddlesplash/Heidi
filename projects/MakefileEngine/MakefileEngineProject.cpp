/*
 * Copyright 2014 Augustin Cavalier <waddlesplash>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
#include "MakefileEngineProject.h"

#include "Makefile.h"


MakefileEngineProject::MakefileEngineProject(entry_ref* fileRef)
{
	fFile = BFile(fileRef, B_READ_WRITE);
	fFileEntry = BEntry(fileRef);

	Load();
}

// #pragma mark Project class functions

BString
MakefileEngineProject::BuildCommand()
{
	return BString("make"); // TODO: multijob!
}


void
MakefileEngineProject::BuildTree(BOutlineListView* olv)
{
	// TODO
}


bool
MakefileEngineProject::IsSupported(BString filePath)
{
	BEntry e(filePath.String());
	char* entryName = new char[B_FILE_NAME_LENGTH];
	BString name(entryName);
	delete[] entryName;
	return (name.ICompare("Makefile") == 0);
}


bool
MakefileEngineProject::IsSupported(entry_ref* fileRef)
{
	BString name(fileRef->name);
	return (name.IFindFirst("Makefile") != B_ERROR); 
}


// #pragma mark Makefile Parser
#define PARSE_T(CONSTANT, VARIABLE, PARSERFUNC) \
	if (_ParseConstant(mkfile, pos, CONSTANT)) { \
		while (mkfile[pos] != '=') \
			pos++; \
		pos++; /* Skip to after the '=' */ \
		VARIABLE = PARSERFUNC(mkfile, pos); \
	}
#define PARSE_STRING(CONSTANT, VARIABLE) \
	PARSE_T(CONSTANT, VARIABLE, _ParseString)
#define PARSE_STRINGLIST(CONSTANT, VARIABLE) \
	PARSE_T(CONSTANT, VARIABLE, _ParseStringList)
#define PARSE_FILELIST(CONSTANT, VARIABLE) \
	PARSE_T(CONSTANT, VARIABLE, _ParseFileList)
#define PARSE_BOOL(CONSTANT, VARIABLE) \
	PARSE_T(CONSTANT, VARIABLE, _ParseBool)


status_t
MakefileEngineProject::Load()
{
	off_t size;
	fFile.GetSize(&size);
	fFile.Seek(0, SEEK_SET);
	char* buffer = new char[size];
	off_t len = fFile.Read(buffer, size);
	BString mkfile(buffer);
	mkfile.Trim();
	mkfile.ReplaceAll("\r\n", "\n");
	mkfile.ReplaceAll("\r", "\n");
	
	int32 pos = 0;
	int32 length = mkfile.Length();
	while (pos < length) {
		switch (mkfile[pos]) {
		case '#':
			// We're at a comment. Ignore until the next newline.
			pos = mkfile.FindFirst('\n', pos);
		break;
		case 'A':
			PARSE_STRING("APP_MIME_SIG", fAppMimeSig)
		break;
		case 'C':
			PARSE_STRINGLIST("COMPILER_FLAGS", fCompilerFlags)
		break;
		case 'D':
			PARSE_STRINGLIST("DEFINES", fDefines)
			else PARSE_BOOL("DEBUGGER", fDebugInfo)
			else PARSE_STRING("DRIVER_PATH", fDriverPath)
		break;
		case 'L':
			PARSE_STRINGLIST("LIBS", fLibs)
			else PARSE_STRINGLIST("LIBPATHS", fLibpaths)
			else PARSE_STRINGLIST("LOCAL_INCLUDE_PATHS", fLocalIncludePaths)
			else PARSE_STRINGLIST("LOCALES", fLocales)
			else PARSE_STRINGLIST("LINKER_FLAGS", fLinkerFlags)
		break;
		case 'N':
			PARSE_STRING("NAME", fName)
		break;
		case 'R':
			PARSE_FILELIST("RDEFS", fRdefs)
			else PARSE_FILELIST("RSRCS", fRsrcs)
		break;
		case 'S':
			PARSE_FILELIST("SRCS", fSrcs)
			else PARSE_STRINGLIST("SYSTEM_INCLUDE_PATHS", fSystemIncludePaths)
			else PARSE_BOOL("SYMBOLS", fImageSymbols)
		break;

		case 'O':
			if (_ParseConstant(mkfile, pos, "OPTIMIZE")) {
				while (mkfile[pos] != '=')
					pos++;
				pos++; /* Skip to after the '=' */
				if (_ParseConstant(mkfile, pos, "SOME"))
					fOptimizeAmount = OPTIMIZE_SOME;
				else if (_ParseConstant(mkfile, pos, "FULL"))
					fOptimizeAmount = OPTIMIZE_FULL;
				else
					fOptimizeAmount = OPTIMIZE_NONE;
			}
		break;
		case 'T':
			if (_ParseConstant(mkfile, pos, "TYPE")) {
				while (mkfile[pos] != '=')
					pos++;
				pos++; /* Skip to after the '=' */
				if (_ParseConstant(mkfile, pos, "SHARED"))
					fType = TYPE_SHARED;
				else if (_ParseConstant(mkfile, pos, "STATIC"))
					fType = TYPE_STATIC;
				else if (_ParseConstant(mkfile, pos, "DRIVER"))
					fType = TYPE_DRIVER;
				else
					fType = TYPE_APP;
			}
		break;
		case 'W':
			if (_ParseConstant(mkfile, pos, "WARNINGS")) {
				while (mkfile[pos] != '=')
					pos++;
				pos++; /* Skip to after the '=' */
				if (_ParseConstant(mkfile, pos, "NONE"))
					fWarnings = WARN_NONE;
				else if (_ParseConstant(mkfile, pos, "ALL"))
					fWarnings = WARN_ALL;
				else
					fWarnings = WARN_DEFAULT;
			}
		break;
		
		default:
		break;
		}
		pos++;
	}

	delete[] buffer;
	return B_OK;
}


BString
MakefileEngineProject::_ParseString(BString& mkfile, int32& pos)
{
	BString str;
	while (mkfile[pos] != '\n' && mkfile[pos] != '=') {
		if (mkfile[pos] == '\\')
			pos++; // Skip next character, probably a newline
		else
			str += mkfile[pos];
		pos++;
	}

	return str.Trim();
}


bool
MakefileEngineProject::_ParseConstant(BString& mkfile, int32& pos,
			const char* constant)
{
	int32 oldpos = pos;
	BString value = _ParseString(mkfile, pos);
	if (value.Compare(constant) == 0) {
		return true;
	} else {
		pos = oldpos;
		return false;
	}
}


BStringList
MakefileEngineProject::_ParseStringList(BString& mkfile, int32& pos)
{
	BString str = _ParseString(mkfile, pos);
	BStringList list;
	str.Split(" ", true, list);	
	return list;
}


bool
MakefileEngineProject::_ParseBool(BString& mkfile, int32& pos)
{
	if (_ParseConstant(mkfile, pos, "TRUE"))
		return true;
	else
		return false;
}


BObjectList<BEntry>
MakefileEngineProject::_ParseFileList(BString& mkfile, int32& pos)
{
	BStringList list = _ParseStringList(mkfile, pos);
	BObjectList<BEntry> ret;

	for (int i = 0; i < list.CountStrings(); i++)
		ret.AddItem(new BEntry(list.StringAt(i).String()));

	return ret;
}

// #pragma mark Makefile generator

status_t
MakefileEngineProject::Save()
{
	BString mkfile(template_makefile);
	off_t size = mkfile.Length();
	fFile.SetSize(size);
	fFile.Seek(0, SEEK_SET);

	off_t len = fFile.Write(mkfile.String(), size);
	fFile.Flush();
	
	return (len == size) ? B_OK : B_ERROR;
}
