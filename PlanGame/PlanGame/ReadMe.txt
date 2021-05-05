================================================================================
 Microsoft Base Class Library: Overview of the Plangame Project
===============================================================================

The application wizard has created this Plangame application for you. This application not only demonstrates the basic use of Microsoft base classes, but also serves as a starting point for you to write applications.



This file Outlines the contents of each file that makes up the Plangame application.



PlanGame.vcxproj

This is the main project file for the VC++ project that was generated using the application wizard. It contains information about the version of Visual C++ from which the file was generated, as well as information about the platform, configuration, and project functionality selected using the application wizard.



PlanGame.vcxproj.filters

This is a VC++ project filter file generated using the Application Wizard. It contains information about the association between the project file and the filter. In the IDE, through this association, files with similar extensions are displayed in groups under a particular node. For example, the ".cpp "file is associated with the" Source Files "filter.



PlanGame.h

This is the main header file for the application.

It includes other project-specific headers, including resource-.h, and declares the CplangameApp application class.



PlanGame.cpp

This is the main application source file that contains the application class CplangameApp.



PlanGame.rc

This is a list of all Microsoft Windows resources used by the program. It includes ICONS, bitmaps, and cursors stored in the RES subdirectory. This file can be edited directly from Microsoft Visual C++. Project resources are contained in 2052.



res\PlanGame.ico

This is the icon file used as the icon for the application. This icon is included in the main resource file, plangame.rc.



res\PlanGame.rc2

This file contains resources that are not edited in Microsoft Visual C++. You should put all resources in this file that are not editable by the resource editor.



/////////////////////////////////////////////////////////////////////////////



For the main frame window:

The project includes a standard MFC interface.



MainFrm.h, MainFrm.cpp

These files contain the frame class cmainFrame, which is derived from

Cframewnd controls all SDI framework functions.



res\Toolbar.bmp

This bitmap file is used to create a tiled image for the toolbar.

The initial toolbar and status bar are constructed in the cmainFrame class. Edit the TOOLBAR bitmap using the resource editor and update the IDR_MainFrame Toolbar array in plangame.rc to add TOOLBAR buttons.

/////////////////////////////////////////////////////////////////////////////



The application wizard creates a document type and a view:



Plangamedoc. h, plangamedoc. CPP - document

These files contain the CplangameDoc class. Edit these files to add special document data and implement file save and load (through cplangameDoc ::Serialize).



PlangaView. h, plangaView. CPP - document view

These files contain the CPLangaView class.

The CPLangaView object is used to view the CPLangameDoc object.









/////////////////////////////////////////////////////////////////////////////



Other standard documents:



StdAfx.h, StdAfx.cpp

These files are used to generate a precompiled header (PCH) file named plangame.pch and a precompiled type file named stdafx.obj.



Resource.h

This is the standard header file that can be used to define a new resource ID. Microsoft Visual C++ will read and update this file.



/////////////////////////////////////////////////////////////////////////////



Other Notes:



The application wizard uses "TODO:" to indicate the part of the source code that should be added or customized.



If your application uses an MFC in a shared DLL, you will need to redistribute the MFC DLL. If the language used by the application is different from the operating system locale, you also need to redistribute the corresponding localization resource MFC110XXXX.

For more information on the above topics, see the section on redistributing Visual C++ applications in the MSDN documentation.

