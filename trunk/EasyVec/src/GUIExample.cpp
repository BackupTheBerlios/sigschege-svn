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

#include "wx/wx.h"

#include "wx/sizer.h"
#include "wx/statline.h"
#include "wx/notebook.h"

#include "GUIExample.h"
#include "EasyVecFigure.h"
#include "EasyVecElm.h"
#include "EasyVecPolyline.h"
#include "EasyVecText.h"
#include "EasyVecVwx.h"

#include <cstdio>

using namespace std;

MyFrame   *frame = (MyFrame *) NULL;
wxMenuBar *menu_bar = (wxMenuBar *) NULL;

IMPLEMENT_APP(MyApp);

EasyVecPolyline* mainline;
EasyVecFigure *mainpic;

MyApp::MyApp()
{
}


bool MyApp::OnInit()
{
  // Create the main frame window
  frame = new MyFrame(NULL, _T("EasyVec Demo"), -1, -1, 400, 300);

  frame->SetAutoLayout(TRUE);

  // Make a menubar
  wxMenu *file_menu = new wxMenu;

  file_menu->Append(LAYOUT_ADD_PLINE_POINT, _T("&Add point"),      _T("Add point"));
  file_menu->Append(LAYOUT_TOGGLE_SCREENDPI, _T("&Toggle screen dpi"),      _T("Toggle screen dpi"));
  file_menu->Append(LAYOUT_SAVE, _T("&Save"),      _T("Save"));

  file_menu->AppendSeparator();
  file_menu->Append(LAYOUT_QUIT, _T("E&xit"),                _T("Quit program"));

  wxMenu *help_menu = new wxMenu;
  help_menu->Append(LAYOUT_ABOUT, _T("&About"),              _T("About layout demo"));

  menu_bar = new wxMenuBar;

  menu_bar->Append(file_menu, _T("&File"));
  menu_bar->Append(help_menu, _T("&Help"));

  // Associate the menu bar with the frame
  frame->SetMenuBar(menu_bar);

  // Make a panel
  wxPanel *panel = new wxPanel(frame);

  // Create some panel items
  wxButton *btn1 = new wxButton(panel, -1, _T("A button (1)")) ;

  wxLayoutConstraints *b1 = new wxLayoutConstraints;
  b1->centreX.SameAs    (panel, wxCentreX);
  b1->top.SameAs        (panel, wxTop, 5);
  b1->width.PercentOf   (panel, wxWidth, 80);
  b1->height.AsIs       ();
  btn1->SetConstraints(b1);


  wxLayoutConstraints *b2 = new wxLayoutConstraints;
  b2->top.Below         (btn1, 5);
  b2->left.SameAs       (panel, wxLeft, 5);
  b2->width.PercentOf   (panel, wxWidth, 40);
  b2->bottom.SameAs     (panel, wxBottom, 5);
  //list->SetConstraints(b2);

//  wxTextCtrl *mtext = new wxTextCtrl(panel, -1, _T("Some text"));

//   wxLayoutConstraints *b3 = new wxLayoutConstraints;
//   b3->top.Below         (btn1, 5);
//   b3->left.RightOf      (list, 5);
//   b3->right.SameAs      (panel, wxRight, 5);
//   b3->bottom.SameAs     (panel, wxBottom, 5);
//   mtext->SetConstraints(b3);

  EasyVecFigure *ev_pic = new EasyVecFigure();
  EasyVecPolyline *nline;
  nline = ev_pic->polyline();
  nline->addPoint(1500, 1500);
  nline->addPoint(300, 1500);
  nline->addPoint(3300, 1500);

  mainline = nline;
  mainpic = ev_pic;
  
  nline = ev_pic->polyline();
  nline->addPoint(600, 1500);
  nline->addPoint(300, 3000);
  nline->addPoint(1500, 1800);

  nline = ev_pic->polyline();
  nline->pen_color(4);
  nline->addPoint(660, 1560);
  nline->addPoint(360, 3060);
  nline->addPoint(1560, 1860);

  EasyVecText *ntext;
  ntext = ev_pic->text();
  ntext->setText("This is an EasyVec Demo");

  EVPosInt ul, lr;
  //ntext->getBoundingBox(ul, lr); TODO
  //cout << ul << ":" << lr << endl;

  ul = EVPosInt(600, 600); 
  lr = EVPosInt(1000, 2000); 

  EasyVecVwx *canvas = new EasyVecVwx(ev_pic, frame, 0, 0, 400, 400, wxRETAINED);

  // Set constraints for canvas subwindow
  wxLayoutConstraints *c2 = new wxLayoutConstraints;

  c2->left.SameAs       (frame, wxLeft);
  c2->top.SameAs        (frame, wxTop);
  c2->right.SameAs      (frame, wxRight);
  c2->bottom.SameAs  (frame, wxBottom);

  canvas->SetConstraints(c2);


  frame->Show(TRUE);

  frame->SetStatusText(_T("EasyVec demo"));

  SetTopWindow(frame);

  return TRUE;
}

// Define my frame constructor
MyFrame::MyFrame(wxFrame *frame, const wxChar *title, int x, int y, int w, int h)
       : wxFrame(frame, -1, title, wxPoint(x, y), wxSize(w, h))
{
}

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
  EVT_MENU(LAYOUT_QUIT, MyFrame::OnQuit)
  EVT_MENU(LAYOUT_ADD_PLINE_POINT, MyFrame::add_pline_point)
  EVT_MENU(LAYOUT_TOGGLE_SCREENDPI, MyFrame::toggle_screen_dpi)
  EVT_MENU(LAYOUT_SAVE, MyFrame::save)
END_EVENT_TABLE()

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event) )
{
  Close(TRUE);
}

void MyFrame::toggle_screen_dpi(wxCommandEvent& event) {
  if (mainpic->get_screen_dpi()==80) mainpic->set_screen_dpi(160);
  else  mainpic->set_screen_dpi(80);
}

void MyFrame::save(wxCommandEvent& event) {
  mainpic->save("demogui_result.fig");
}

void MyFrame::add_pline_point(wxCommandEvent& event) {
  double x, y;
  x = rand(); 
  y = rand();
  x *= 15*200.0/RAND_MAX;
  y *= 15*200.0/RAND_MAX;
  cout << "add_pline_point =" << x << ":" << y << endl;
  mainline->addPoint(static_cast<int>(x), static_cast<int>(y)); 
}
