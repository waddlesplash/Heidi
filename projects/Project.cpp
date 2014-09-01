/*
 * Copyright 2014 Augustin Cavalier <waddlesplash>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
#include "Project.h"

#include <Path.h>

Project::Project()
{
	data.type = TYPE_APP;
	data.optimize = OPTIMIZE_SOME;
	data.warnings = WARN_DEFAULT;
	data.image_symbols = false;
	data.debug_info = false;
}


BString
Project::DirectoryPath()
{
	BEntry e(&fFileEntry);
	BString pathStr;
	BPath path;
	e.GetPath(&path);
	path.GetParent(&path);
	pathStr = path.Path();
	pathStr += "/";
	return pathStr;
}
