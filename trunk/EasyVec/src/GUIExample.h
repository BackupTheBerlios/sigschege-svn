// \file  
// Copyright 2004 by Ulf Klaperski
//
// This file is part of EasyVec - Vector Figure Creation Library.
// 
// #############################################################################
//
// EasyVec is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2, or (at your option)
// any later version.
// 
// EasyVec is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with the EasyVec sources; see the file COPYING.  
//
// #############################################################################
//
// $Id$

#ifndef _DEMOGUI_H
#define _DEMOGUI_H _DEMOGUI_H 

class MyApp: public wxApp
{
public:
    MyApp();
    bool OnInit();
};

// Define a new frame
class MyTextWindow;
class MyWindow;

class MyFrame: public wxFrame
{
public:
    MyFrame(wxFrame *frame, const wxChar *title, int x, int y, int w, int h);

    void OnQuit(wxCommandEvent& event);

    void add_pline_point(wxCommandEvent& event);
    void toggleScreenDpi(wxCommandEvent& event);
    void save(wxCommandEvent& event);
    void TestNotebookSizers(wxCommandEvent& event);
    void About(wxCommandEvent& event);

private:
    DECLARE_EVENT_TABLE()
};




#define LAYOUT_QUIT       100
#define LAYOUT_TEST       101
#define LAYOUT_ABOUT      102
#define LAYOUT_ADD_PLINE_POINT 104
#define LAYOUT_TOGGLE_SCREENDPI    105
#define LAYOUT_SAVE    106


#endif /* _DEMOGUI_H */

