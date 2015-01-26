/*
 * Copyright 2014 Augustin Cavalier <waddlesplash>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
#include "MakefileEngineProject.h"

#include <Path.h>


MakefileEngineProject::MakefileEngineProject(entry_ref* fileRef)
	: Project()
{
	fFile = BFile(fileRef, B_READ_WRITE);
	fFileEntry = BEntry(fileRef);

	Load();
}

// #pragma mark Project class functions

BString
MakefileEngineProject::BuildCommand(BString objDir, int jobs)
{
	return BString()
		.SetToFormat("make OBJ_DIR=\"%s\" -j%d", objDir.String(), jobs);
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
	if (_ParseConstant(mkfile, pos, CONSTANT)) { \
		while (mkfile[pos] != '=') \
			pos++; \
		pos++; /* Skip to after the '=' */ \
		BObjectList<BEntry>* l = _ParseFileList(mkfile, pos); \
		VARIABLE.AddList(l); \
		delete l; \
	}
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
			PARSE_STRING("APP_MIME_SIG", data.app_mime_sig)
		break;
		case 'C':
			PARSE_STRINGLIST("COMPILER_FLAGS", data.compiler_flags)
		break;
		case 'D':
			PARSE_STRINGLIST("DEFINES", data.defines)
			else PARSE_BOOL("DEBUGGER", data.debug_info)
			else PARSE_STRING("DRIVER_PATH", data.driver_path)
		break;
		case 'L':
			PARSE_STRINGLIST("LIBS", data.libs)
			else PARSE_STRINGLIST("LIBPATHS", data.lib_paths)
			else PARSE_STRINGLIST("LOCAL_INCLUDE_PATHS", data.local_include_paths)
			else PARSE_STRINGLIST("LOCALES", data.locales)
			else PARSE_STRINGLIST("LINKER_FLAGS", data.linker_flags)
		break;
		case 'N':
			PARSE_STRING("NAME", data.name)
		break;
		case 'R':
			PARSE_FILELIST("RDEFS", data.srcs)
			else PARSE_FILELIST("RSRCS", data.srcs)
		break;
		case 'S':
			PARSE_FILELIST("SRCS", data.srcs)
			else PARSE_STRINGLIST("SYSTEM_INCLUDE_PATHS", data.system_include_paths)
		break;

		case 'O':
			if (_ParseConstant(mkfile, pos, "OPTIMIZE")) {
				while (mkfile[pos] != '=')
					pos++;
				pos++; /* Skip to after the '=' */
				if (_ParseConstant(mkfile, pos, "SOME"))
					data.optimize = OPTIMIZE_SOME;
				else if (_ParseConstant(mkfile, pos, "FULL"))
					data.optimize = OPTIMIZE_FULL;
				else
					data.optimize = OPTIMIZE_NONE;
			}
		break;
		case 'T':
			if (_ParseConstant(mkfile, pos, "TYPE")) {
				while (mkfile[pos] != '=')
					pos++;
				pos++; /* Skip to after the '=' */
				if (_ParseConstant(mkfile, pos, "SHARED"))
					data.type = TYPE_SHARED;
				else if (_ParseConstant(mkfile, pos, "STATIC"))
					data.type = TYPE_STATIC;
				else if (_ParseConstant(mkfile, pos, "DRIVER"))
					data.type = TYPE_DRIVER;
				else
					data.type = TYPE_APP;
			}
		break;
		case 'W':
			if (_ParseConstant(mkfile, pos, "WARNINGS")) {
				while (mkfile[pos] != '=')
					pos++;
				pos++; /* Skip to after the '=' */
				if (_ParseConstant(mkfile, pos, "NONE"))
					data.warnings = WARN_NONE;
				else if (_ParseConstant(mkfile, pos, "ALL"))
					data.warnings = WARN_ALL;
				else
					data.warnings = WARN_DEFAULT;
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
	while (mkfile[pos] != '\n' && mkfile[pos] != '=' && mkfile[pos] != ':'
	       && pos < mkfile.Length()) {
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
	str.ReplaceAll("\t", " ").Split(" ", true, list);
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


BObjectList<BEntry>*
MakefileEngineProject::_ParseFileList(BString& mkfile, int32& pos)
{
	BStringList list = _ParseStringList(mkfile, pos);
	BObjectList<BEntry>* ret = new BObjectList<BEntry>;
	BString mkfilePathStr = DirectoryPath();

	for (int i = 0; i < list.CountStrings(); i++) {
		BString fileStr = list.StringAt(i);
		if (!fileStr.StartsWith("/"))
			fileStr.Prepend(mkfilePathStr);
		ret->AddItem(new BEntry(fileStr.String()));
	}

	return ret;
}
