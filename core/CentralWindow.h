/*
 * Copyright 2014 Augustin Cavalier <waddlesplash>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
#ifndef CORE_CENTRALWINDOW_H
#define CORE_CENTRALWINDOW_H

#include <Entry.h>
#include <FilePanel.h>
#include <ObjectList.h>
#include <Window.h>

#include <private/shared/ToolBar.h>

#include "HeidiGlobal.h"
#include "Editor.h"
#include "Project.h"

// View Predefinitions
class BTabView;
class BTextView;
class BOutlineListView;
class BGroupLayout;
class ShellView;

// Window Predefinitions
class BFilePanel;

// Other Predefinitions
class Project;


class CentralWindow : public BWindow
{
public:
	enum WhatCodes {
		CW_OPEN = 'cw00',
		CW_SAVE,
		CW_SAVEAS,

		CW_BUILD,
		CW_BUILD_FINISHED,
		CW_RUN,
		CW_RUN_FINISHED,
		CW_RUN_DEBUG,

		CW_HOMEPAGE,
		CW_GITHUB,
		CW_ABOUT,
	};

				CentralWindow(BRect frame);
				~CentralWindow();

	Editor*		CurrentEditor();

	bool		OpenProject(entry_ref* ref);
	void		CloseProject();

	void		MessageReceived(BMessage* msg);
	bool		QuitRequested();

	// TODO: Hooks for the projects to call in multiproject mode.
	//status_t	AddProject(Project* project);
	//status_t	RemoveProject(Project* project);

private:
	BGroupLayout*			fRootLayout;
	BToolBar*				fToolbar;

	BOutlineListView*		fProjectTree;
	Project*				fOpenProject;

	BTabView*	  			fEditorsTabView;
	BObjectList<Editor>		fOpenEditors;

	BFilePanel*				fOpenPanel;

	BTabView*	 	 		fOutputsTabView;
	BTextView*				fBuildIssues;
	ShellView*				fCompileOutput;
	ShellView*				fAppOutput;
};

extern CentralWindow* central_window;

#endif // CORE_CENTRALWINDOW_H
