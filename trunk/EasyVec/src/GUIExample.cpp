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
#include <list>

#include <cstdio>

using namespace std;

MyFrame   *frame = (MyFrame *) NULL;
wxMenuBar *menu_bar = (wxMenuBar *) NULL;

IMPLEMENT_APP(MyApp);

EasyVecPolyline* mainline;
list<EasyVecPolyline *> dlines;
EasyVecFigure *mainpic;

MyApp::MyApp()
{
}

static void gen_dlines(void) {
  EasyVecPolyline *dline;
  for (int i=100; i<5000; i+=1000) {
    dline = mainpic->polyline();
    dline->addPoint(3000, 4000);
    dline->addPoint(i, 100);
    dline->lineStyle(EasyVecLine::dashed);
    dline->styleValue(8.0);
    dlines.push_back(dline);
    
    dline = mainpic->polyline();
    dline->addPoint(3000, 4000);
    dline->addPoint(i+200, 100);
    dline->lineStyle(EasyVecLine::dotted);
    dline->styleValue(8.0);
    dlines.push_back(dline);
    
    dline = mainpic->polyline();
    dline->addPoint(3000, 4000);
    dline->addPoint(i+400, 100);
    dline->lineStyle(EasyVecLine::dash_dotted);
    dline->styleValue(5.0);
    dlines.push_back(dline);
    
    dline = mainpic->polyline();
    dline->addPoint(3000, 4000);
    dline->addPoint(i+600, 100);
    dline->lineStyle(EasyVecLine::dash_double_dotted);
    dline->styleValue(8.0);
    dlines.push_back(dline);
    
    dline = mainpic->polyline();
    dline->addPoint(3000, 4000);
    dline->addPoint(i+800, 100);
    dline->lineStyle(EasyVecLine::dash_triple_dotted);
    dline->styleValue(8.0);
    dlines.push_back(dline);
  }
}


bool MyApp::OnInit()
{

  EasyVecFigure *ev_pic = new EasyVecFigure();
  EasyVecPolyline *nline;
  nline = ev_pic->polyline();
  nline->addPoint(1500, 1500);
  nline->addPoint(300, 1500);
  nline->addPoint(3300, 1500);
  nline->addPoint(1720, 60);
  nline->depth(66);
  mainline = nline;
  mainpic = ev_pic;
  

  EasyVecText *ntext;
  ntext = ev_pic->text();
  ntext->setText("This is an EasyVec Demo");
  ntext->pen_color(2);
  ntext->setOrigin(EVPosInt(300, 1000));
  ntext->depth(55);
  EVPosInt ul, lr;
  //ntext->getBoundingBox(ul, lr); TODO
  //cout << ul << ":" << lr << endl;

  ul = EVPosInt(600, 600); 
  lr = EVPosInt(1000, 2000); 

  // Create the main frame window
  frame = new MyFrame(NULL, _T("EasyVec Demo"), -1, -1, 800, 600);

  frame->SetAutoLayout(TRUE);

  // Make a menubar
  wxMenu *file_menu = new wxMenu;

  file_menu->Append(LAYOUT_ADD_PLINE_POINT, _T("&Add point"),      _T("Add point"));
  file_menu->Append(LAYOUT_TOGGLE_SCREENDPI, _T("&Toggle screen dpi"),      _T("Toggle screen dpi"));
  file_menu->Append(LAYOUT_TOGGLE_DASHY, _T("&Toggle dashed lines"),      _T("Toggle dashed lines"));
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

  wxLayoutConstraints *c1 = new wxLayoutConstraints;

  c1->left.SameAs       (frame, wxLeft);
  c1->top.SameAs        (frame, wxTop);
  c1->right.SameAs      (frame, wxRight);
  c1->height.PercentOf  (frame, wxHeight, 10);
  panel->SetConstraints(c1);

  // Create some panel items
  wxButton *btn1 = new wxButton(panel, -1, _T("Toggle dashed lines")) ;

  EasyVecVwx *canvas = new EasyVecVwx(ev_pic, frame, 0, 0, 400, 400, wxRETAINED);
  // Set constraints for canvas subwindow
  wxLayoutConstraints *c2 = new wxLayoutConstraints;
  c2->left.SameAs       (frame, wxLeft);
  c2->top.Below        (panel, wxTop);
  c2->right.SameAs      (frame, wxRight);
  c2->bottom.SameAs  (frame, wxBottom);
  canvas->SetConstraints(c2);
  
  wxLayoutConstraints *b1 = new wxLayoutConstraints;
  b1->centreX.SameAs    (panel, wxCentreX);
  b1->top.SameAs        (panel, wxTop, 5);
  b1->width.PercentOf   (panel, wxWidth, 80);
  b1->height.AsIs       ();
  btn1->SetConstraints(b1);


//   wxLayoutConstraints *b2 = new wxLayoutConstraints;
//   b2->top.Below         (btn1, 5);
//   b2->left.SameAs       (panel, wxLeft, 5);
//   b2->width.PercentOf   (panel, wxWidth, 40);
//   b2->bottom.SameAs     (panel, wxBottom, 5);
//   list->SetConstraints(b2);

//  wxTextCtrl *mtext = new wxTextCtrl(panel, -1, _T("Some text"));

//   wxLayoutConstraints *b3 = new wxLayoutConstraints;
//   b3->top.Below         (btn1, 5);
//   b3->left.RightOf      (list, 5);
//   b3->right.SameAs      (panel, wxRight, 5);
//   b3->bottom.SameAs     (panel, wxBottom, 5);
//   mtext->SetConstraints(b3);


  




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
  EVT_MENU(LAYOUT_TOGGLE_SCREENDPI, MyFrame::toggleScreenDpi)
  EVT_MENU(LAYOUT_TOGGLE_DASHY, MyFrame::toggleDashedLines)
  EVT_MENU(LAYOUT_SAVE, MyFrame::save)
END_EVENT_TABLE()

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event) )
{
  Close(TRUE);
}

void MyFrame::toggleScreenDpi(wxCommandEvent& event) {
  if (mainpic->getScreenDpi()==80) mainpic->setScreenDpi(160);
  else  mainpic->setScreenDpi(80);
  Refresh();
}

void MyFrame::toggleDashedLines(wxCommandEvent& event) {
  mainpic->updating(false);
  if (dlines.empty()) gen_dlines();
  else {
    list<EasyVecPolyline*>::iterator dlineIt;
    for ( dlineIt = dlines.begin(); dlineIt != dlines.end(); ++dlineIt ) {
      if (!mainpic->remove(*dlineIt)) cerr << "ERROR: DashedLine element did not exist!" << endl; 
    }
    dlines.clear();
  }
  mainpic->updating(true);
  Refresh();
}

void MyFrame::save(wxCommandEvent& event) {
  mainpic->save("demogui_result.fig");
}

void MyFrame::add_pline_point(wxCommandEvent& event) {
  mainpic->updating(false);
  double x, y;
  x = rand(); 
  y = rand();
  x *= 15*200.0/RAND_MAX;
  y *= 15*200.0/RAND_MAX;
  cout << "add_pline_point =" << x << ":" << y << endl;
  mainline->addPoint(static_cast<int>(x), static_cast<int>(y)); 
  mainpic->updating(true);
  Refresh();
}
