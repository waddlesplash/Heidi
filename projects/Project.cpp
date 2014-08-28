/*
 * Copyright 2014 Augustin Cavalier <waddlesplash>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
#include "Project.h"

#include <Path.h>

BString
Project::DirectoryPath()
{
	BString pathStr;
	BPath path;
	fFileEntry.GetPath(&path);
	path.GetParent(&path);
	pathStr = path.Path();
	pathStr += "/";
	return pathStr;
}
