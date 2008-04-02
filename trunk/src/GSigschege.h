// \file  
// Copyright 2007 by Ulf Klaperski
//
// This file is part of Sigschege - Signal Schedule Generator
// 
// #############################################################################
//
// Sigschege is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2, or (at your option)
// any later version.
// 
// Sigschege is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with the Sigschege sources; see the file COPYING.  
//
// #############################################################################
//
// $Id: $

  
#ifndef _GSIGSCHEGE_H
#define _GSIGSCHEGE_H _GSIGSCHEGE_H 

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
  void open_file(wxCommandEvent& event);
  /// Dummy comment.
  void save(wxCommandEvent& event);
  /// Dummy comment.
  void save_as(wxCommandEvent& event);
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
  void TestNotebookSizers(wxCommandEvent& event);
  /// Dummy comment.
  void about(wxCommandEvent& event);
  
 private:
  DECLARE_EVENT_TABLE()
};




#define LAYOUT_QUIT       100
#define LAYOUT_TEST       101
#define FILE_QUIT      102
#define FILE_OPEN_FILE    104
#define FILE_SAVE         105
#define FILE_SAVE_AS      106
#define HELP_ABOUT    107
#define BUTTON_DASHY 108
#define BUTTON_BOXES 109
#define BUTTON_ARROWS 110
#define BUTTON_ARCS 111
#define BUTTON_TEXT 112
#define MOUSE_RIGHT_DWN 121
#define LAYOUT_TOGGLE_MARKERS    113

#endif /* _GSIGSCHEGE_H */

