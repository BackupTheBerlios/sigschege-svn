// \file  
// Copyright 2004 by Ulf Klaperski
//
// This file is part of YaVec - Vector Figure Creation Library.
// 
// #############################################################################
//
// YaVec is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2, or (at your option)
// any later version.
// 
// YaVec is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with the YaVec sources; see the file COPYING.  
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
    void toggleMarkers(wxCommandEvent& event);
    void toggleDashedLines(wxCommandEvent& event);
    void toggleBoxes(wxCommandEvent& event);
    void toggleArrows(wxCommandEvent& event);
    void toggleArcs(wxCommandEvent& event);
    void toggleText(wxCommandEvent& event);
    void OnMouse(wxMouseEvent& event);
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
#define LAYOUT_TOGGLE_DASHY    106
#define LAYOUT_SAVE    107
#define BUTTON_DASHY 108
#define BUTTON_BOXES 109
#define BUTTON_ARROWS 110
#define BUTTON_ARCS 111
#define BUTTON_TEXT 112
#define MOUSE_RIGHT_DWN 121
#define LAYOUT_TOGGLE_MARKERS    113

#endif /* _DEMOGUI_H */

