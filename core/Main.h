/*
 * Copyright 2014 Augustin Cavalier <waddlesplash>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
#ifndef CORE_MAIN_H
#define CORE_MAIN_H

#include <Application.h>

#include "HeidiGlobal.h"

// Predefinitions
class CentralWindow;

class HeidiApp : public BApplication
{
public:
			HeidiApp();
			~HeidiApp();

	void	AboutRequested();
	void	RefsReceived(BMessage* msg);
	void	ArgvReceived(int32 argc, char* argv[]);
	void	ReadyToRun();
	void	MessageReceived(BMessage* msg);
	bool	QuitRequested();
	
private:
};

#endif // CORE_MAIN_H
