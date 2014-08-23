/*
 * Copyright 2014 Augustin Cavalier <waddlesplash>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
#ifndef PROJECTS_PROJECTFACTORY_H
#define PROJECTS_PROJECTFACTORY_H

#include "HeidiGlobal.h"
#include "Project.h"

#include <Entry.h>

class ProjectFactory {
public:
	static 	Project*	Load(entry_ref* file);
};

#endif // PROJECTS_PROJECTFACTORY_H
