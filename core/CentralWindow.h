/*
 * Copyright 2014 Augustin Cavalier <waddlesplash>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
#ifndef CORE_CENTRALWINDOW_H
#define CORE_CENTRALWINDOW_H

#include <Entry.h>
#include <FilePanel.h>
#include <ToolBar.h>
#include <ObjectList.h>
#include <Window.h>

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
	// 'what' codes that are used internally by this class
	enum WhatCodes {
		CW_OPEN 		= 'cwOP',
		CW_SAVE 		= 'cwSV',
		CW_SAVEAS		= 'cwSa',

		CW_BUILD		= 'cwBU',
		CW_BUILD_FINISHED='cwBF',
		CW_RUN			= 'cwRU',
		CW_RUN_FINISHED	= 'cwRF',
		CW_RUN_DEBUG	= 'cwRD',

		CW_HOMEPAGE		= 'cwHM',
		CW_GITHUB		= 'cwGH',
		CW_ABOUT		= 'cwAB'
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
