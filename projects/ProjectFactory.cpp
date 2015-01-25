/*
 * Copyright 2014 Augustin Cavalier <waddlesplash>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
#include "ProjectFactory.h"

#include "MakefileEngineProject.h"

Project*
ProjectFactory::Load(entry_ref* file)
{
	if (MakefileEngineProject::IsSupported(file))
		return new MakefileEngineProject(file);

	return NULL;
}
