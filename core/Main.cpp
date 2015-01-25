/*
 * Copyright 2014 Augustin Cavalier <waddlesplash>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
#include "Main.h"

#include <Alert.h>
#include <Entry.h>
#include <FindDirectory.h>
#include <Path.h>
#include <Roster.h>
#include <TextView.h>

#include "CentralWindow.h"


HeidiApp::HeidiApp()
	: BApplication(APP_SIGNATURE)
{
}


void
HeidiApp::AboutRequested()
{
	BString version;
	BString str("Heidi\n");
	str += TR("Version");
	str += " " VERSION_STRING;
	str += "\n\n";

	str += "Augustin Cavalier (waddlesplash)\n";
	str += "Kacper Kasper (KapiX)\n";

	BAlert *about = new BAlert("About", str.String(), "Homepage",
							   "Development Page", "Okay");
	BTextView *v = about->TextView();
	if (v) {
		v->SetStylable(true);

		char *text = (char*)v->Text();
		char *s = text;
		// first text line
		s = strchr(text, '\n');
		BFont font;
		v->GetFontAndColor(0, &font);
		font.SetSize(16);
		v->SetFontAndColor(0, s-text+1, &font, B_FONT_SIZE);
	}

	const char * url = NULL;
	switch(about->Go())
	{
		case 0: url = HOMEPAGE_URL; break;
		case 1: url = SOURCE_URL;   break;
	}
	if (url)
		be_roster->Launch("text/html", 1, (char**) &url);
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
