#ifndef PROJECTS_MAKEFILEENGINE_MAKEFILE_H
#define PROJECTS_MAKEFILEENGINE_MAKEFILE_H

const char* template_makefile = "## Haiku Generic Makefile v2.5+(Heidi-1) ## \n\
\n\
## Fill in this file to specify the project being created, and the referenced\n\
## Makefile-Engine will do all of the hard work for you. This handles any\n\
## architecture of Haiku.\n\
\n\
## Application Specific Settings ---------------------------------------------\n\
\n\
# the name of the binary\n\
NAME = $@NAME@$\n\
\n\
# the type of binary, must be one of:\n\
#	APP:	Application\n\
#	SHARED:	Shared library or add-on\n\
#	STATIC:	Static library archive\n\
#	DRIVER: Kernel driver\n\
TYPE = $@TYPE@$\n\
\n\
# 	if you plan to use localization features,\n\
# 	specify the application's MIME siganture\n\
APP_MIME_SIG = $@APP_MIME_SIG@$\n\
\n\
#	Specify the source files to use. Full paths or paths relative to\n\
#	the makefile can be included. All files, regardless of directory, will\n\
#	have their object files created in the common object directory.\n\
#	Note that this means this Makefile will not work correctly\n\
#	if two source files with the same name (source.c or source.cpp)\n\
#	are included from different directories. Also note that spaces\n\
#	in folder names do not work well with this Makefile.\n\
SRCS = $@SRCS@$\n\
\n\
#	specify the resource definition files to use\n\
#	full path or a relative path to the resource file can be used.\n\
RDEFS = $@RDEFS@$\n\
\n\
#	specify the resource files to use. \n\
#	full path or a relative path to the resource file can be used.\n\
#	both RDEFS and RSRCS can be defined in the same makefile.\n\
RSRCS = $@RSRCS@$\n\
\n\
#	Specify additional libraries to link against.\n\
#	There are two acceptable forms of library specifications\n\
#	-	if your library follows the naming pattern of:\n\
#		libXXX.so or libXXX.a you can simply specify XXX for the\n\
#		library. (e.g. the entry for libbe.so would be just \"be\")\n\
#\n\
#	-	for GCC-independent linking of standard C++ libraries, you can use\n\
#		$(STDCPPLIBS) instead of the raw \"stdc++[.r4] [supc++]\" library names.\n\
#\n\
#	-	for localization support, following libraries:\n\
#		locale localestub\n\
#\n\
#	- 	if your library does not follow the standard library\n\
#		naming scheme you need to specify the path to the library\n\
#		and it's name. (e.g. for my_lib.a, specify \"my_lib.a\" or \"path/my_lib.a\"\n\
LIBS = $@LIBS@$\n\
\n\
#	Specify additional paths to directories following the standard\n\
#	libXXX.so or libXXX.a naming scheme. You can specify full paths\n\
#	or paths relative to the Makefile. The paths included are not\n\
#	parsed recursively, so include all of the paths where libraries\n\
#	must be found. Directories where source files were specified are\n\
#	automatically included.\n\
LIBPATHS = $@LIBPATHS@$\n\
\n\
#	Additional paths to look for system headers.\n\
#	These use the form  \"#include <header>\"\n\
#	Directories that contain the files in SRCS are\n\
#   NOT auto-included here.\n\
SYSTEM_INCLUDE_PATHS = $@SYSTEM_INCLUDE_PATHS@$\n\
\n\
#	Additional paths paths to look for local headers\n\
#	thes use the form: #include \"header\"\n\
#	Directories that contain the files in SRCS are\n\
#	automatically included.\n\
LOCAL_INCLUDE_PATHS = $@LOCAL_INCLUDE_PATHS@$\n\
\n\
#	Specify the level of optimization that you want.\n\
#	NONE (O0), SOME (O1), FULL (O2)\n\
OPTIMIZE = $@OPTIMIZE@$\n\
\n\
# 	Specify the codes for languages you are going to support\n\
# 	in this application. The default \"en\" one must be provided too.\n\
# 	\"make catkeys\" will recreate only the \"locales/en.catkeys\" file.\n\
# 	Use it as template for creating catkeys for other languages.\n\
# 	All localization files must be placed in the \"locales\" subdirectory.\n\
LOCALES = $@LOCALES@$\n\
\n\
#	Specify all the preprocessor symbols to be defined. The symbols will not\n\
#	have their values set automatically; you must supply the value (if any)\n\
#	to use. For example, setting DEFINES to \"DEBUG=1\" will cause the\n\
#	compiler option \"-DDEBUG=1\" to be used. Setting DEFINES to \"DEBUG\"\n\
#	would pass \"-DDEBUG\" on the compiler's command line.\n\
DEFINES= $@DEFINES@$\n\
\n\
#	Specify special warning levels. If unspecified, default warnings will\n\
#	be used.\n\
#	NONE = supress all warnings\n\
#	ALL = enable all warnings\n\
WARNINGS = $@WARNINGS@$\n\
\n\
#	With image symbols, stack crawls in the debugger are meaningful.\n\
#	If set to \"TRUE\", symbols will be created.\n\
SYMBOLS = $@SYMBOLS@$\n\
\n\
#	If set to \"TRUE\" will allow application to be run from a source-level\n\
#	debugger.  Note that this will disable all optimzations.\n\
DEBUGGER = $@DEBUGGER@$\n\
\n\
#	Specify any additional compiler flags to be used.\n\
COMPILER_FLAGS = $@COMPILER_FLAGS@$\n\
\n\
#	Specify any additional linker flags to be used.\n\
LINKER_FLAGS = $@LINKER_FLAGS@$\n\
\n\
#	(For TYPE = DRIVER only). Specify the desired location of driver in the /dev\n\
#	hierarchy. Used by the driverinstall rule. E.g., DRIVER_PATH = video/usb will\n\
#	instruct the driverinstall rule to place a symlink to your driver's binary in\n\
#	~/add-ons/kernel/drivers/dev/video/usb, so that your driver will appear at\n\
#	/dev/video/usb when loaded. Default is \"misc\".\n\
DRIVER_PATH = $@DRIVER_PATH@$\n\
\n\
## Include the Makefile-Engine\n\
DEVEL_DIRECTORY := \\\n\
	$(shell findpaths -r \"makefile_engine\" B_FIND_PATH_DEVELOP_DIRECTORY)\n\
include $(DEVEL_DIRECTORY)/etc/makefile-engine";

#endif // PROJECTS_MAKEFILEENGINE_MAKEFILE_H
