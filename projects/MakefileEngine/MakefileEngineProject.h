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

			static bool	IsSupported(BString filePath);
			static bool	IsSupported(entry_ref* fileRef);

			status_t	Load();
			status_t	Save();
	
			void		BuildTree(BOutlineListView* olv);
	
			BString		BuildCommand();

private:
			// Parser stuff
			BString		 _ParseString(BString& mkfile, int32& pos);
			bool		 _ParseConstant(BString& mkfile, int32& pos,
										const char* constant);
			BStringList	 _ParseStringList(BString& mkfile, int32& pos);
			bool		 _ParseBool(BString& mkfile, int32& pos);
			BObjectList<BEntry> _ParseFileList(BString& mkfile, int32& pos);
			
			// Data storage
			BString		fAppMimeSig;
};

#endif // PROJECTS_MAKEFILEENGINEPROJECT_H
