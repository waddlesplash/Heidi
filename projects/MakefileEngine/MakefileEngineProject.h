/*
 * Copyright 2014 Augustin Cavalier <waddlesplash>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
#ifndef PROJECTS_MAKEFILEENGINEPROJECT_H
#define PROJECTS_MAKEFILEENGINEPROJECT_H

#include "HeidiGlobal.h"
#include "Project.h"

class MakefileEngineProject : public Project {
public:
	 					MakefileEngineProject(entry_ref* fileRef);

			static bool	IsSupported(entry_ref* fileRef);

			status_t	Load();
			status_t	Save();
	
			BString		BuildCommand();

private:
			// Parser stuff
			BString		 _ParseString(BString& mkfile, int32& pos);
			bool		 _ParseConstant(BString& mkfile, int32& pos,
										const char* constant);
			BStringList	 _ParseStringList(BString& mkfile, int32& pos);
			bool		 _ParseBool(BString& mkfile, int32& pos);
			BObjectList<BEntry> _ParseFileList(BString& mkfile, int32& pos);
			
			inline BString _SerializeBool(bool val) { return val ? "TRUE" : "FALSE"; }
			inline BString _SerializeStringList(BStringList val)
					{ return val.Join(" \\\n\t"); }
			BString		_SerializeFileList(BObjectList<BEntry>& list);
};

#endif // PROJECTS_MAKEFILEENGINEPROJECT_H
