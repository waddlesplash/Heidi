/*
 * Copyright 2014-2015 Augustin Cavalier <waddlesplash>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
#include "Main.h"

#include <AboutWindow.h>

#include "CentralWindow.h"


HeidiApp::HeidiApp()
	: BApplication(APP_SIGNATURE)
{
}


void
HeidiApp::AboutRequested()
{
	BAboutWindow* window = new BAboutWindow("Heidi",
		APP_SIGNATURE);
	const char* authors[] = {
		"Augustin Cavalier",
		"Kacper Kasper",
		NULL
	};

	window->AddCopyright(2015, "Augustin Cavalier");
	window->AddAuthors(authors);

	window->Show();
}



void
HeidiApp::ArgvReceived(int32 argc, char* argv[])
{
	// Called when be_roster->Launch sends args
}


void
HeidiApp::RefsReceived(BMessage* msg)
{
	central_window->PostMessage(msg);
}


void
HeidiApp::ReadyToRun()
{
	BRect rect(0, 0, 975, 600);
	new CentralWindow(rect);
	central_window->CenterOnScreen();
	central_window->Show();
}


void
HeidiApp::MessageReceived(BMessage* msg)
{
	switch (msg->what) {
	default:
		BApplication::MessageReceived(msg);
	}
}


bool
HeidiApp::QuitRequested()
{
	return true;
}


int main(int argc, char* argv[])
{
	HeidiApp().Run();
	return 0;
}
