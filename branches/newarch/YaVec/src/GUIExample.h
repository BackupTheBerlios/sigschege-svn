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

/// Example application
class MyApp: public wxApp
{
public:
    MyApp();
    /// To be executed on initialization of the application.
    bool OnInit();
};

// Define a new frame
class MyTextWindow;
class MyWindow;

/// Example frame 
class MyFrame: public wxFrame
{
public:

  /// Constructor.
  MyFrame(wxFrame *frame, const wxChar *title, int x, int y, int w, int h);

  /// Function to be executed when quitting this frame.
  void OnQuit(wxCommandEvent& event);
  /// Dummy comment.
  void add_pline_point(wxCommandEvent& event);
  /// Dummy comment.
  void toggleScreenDpi(wxCommandEvent& event);
  /// Dummy comment.
  void toggleMarkers(wxCommandEvent& event);
  /// Dummy comment.
  void toggleDashedLines(wxCommandEvent& event);
  /// Dummy comment.
  void toggleBoxes(wxCommandEvent& event);
  /// Dummy comment.
  void toggleArrows(wxCommandEvent& event);
  /// Dummy comment.
  void toggleArcs(wxCommandEvent& event);
  /// Dummy comment.
  void toggleText(wxCommandEvent& event);
  /// Dummy comment.
  void OnMouse(wxMouseEvent& event);
  /// Dummy comment.
  void save(wxCommandEvent& event);
  /// Dummy comment.
  void TestNotebookSizers(wxCommandEvent& event);
  /// Dummy comment.
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

