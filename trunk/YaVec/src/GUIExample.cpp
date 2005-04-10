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

#include "wx/wx.h"

#include "wx/sizer.h"
#include "wx/statline.h"
#include "wx/notebook.h"

#include "GUIExample.h"
#include "YaVecFigure.h"
#include "YaVecElm.h"
#include "YaVecPolyline.h"
#include "YaVecBox.h"
#include "YaVecArc.h"
#include "YaVecText.h"
#include "YaVecVwx.h"
#include <list>

#include <cstdio>

using namespace std;

MyFrame   *frame = (MyFrame *) NULL;
wxMenuBar *menu_bar = (wxMenuBar *) NULL;
YaVecVwx *canvas;


IMPLEMENT_APP(MyApp);

YaVecPolyline* mainline;
list<YaVecPolyline *> dlines;
list<YaVecPolyline *> alines;
list<YaVecArc *> arcs;
list<YaVecBox *> boxes;
YaVecFigure *mainpic;

MyApp::MyApp()
{
}


bool MyApp::OnInit()
{

  YaVecFigure *ev_pic = new YaVecFigure();
  YaVecPolyline *nline;
  nline = ev_pic->polyline();
  nline->addPoint(1500, 1500);
  nline->addPoint(300, 1500);
  nline->addPoint(3300, 1500);
  nline->addPoint(1720, 60);
  nline->depth(66);
  mainline = nline;
  mainpic = ev_pic;
  

  YaVecText *ntext;
  ntext = ev_pic->text();
  ntext->setText("This is an YaVec Demo");
  ntext->penColor(2);
  ntext->setOrigin(YVPosInt(300, 1000));
  ntext->depth(55);
  YVPosInt ul, lr;
  //ntext->getBoundingBox(ul, lr); TODO
  //cout << ul << ":" << lr << endl;

  ul = YVPosInt(600, 600); 
  lr = YVPosInt(1000, 2000); 

  // Create the main frame window
  frame = new MyFrame(NULL, _T("YaVec Demo"), -1, -1, 800, 600);

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
  wxButton *btn1 = new wxButton(panel, BUTTON_DASHY, _T("Toggle dashed lines")) ;
  wxButton *btn2 = new wxButton(panel, BUTTON_BOXES, _T("Toggle boxes")) ;
  wxButton *btn3 = new wxButton(panel, BUTTON_ARROWS, _T("Toggle arrow lines")) ;
  wxButton *btn4 = new wxButton(panel, BUTTON_ARCS, _T("Toggle arcs")) ;

  canvas = new YaVecVwx(ev_pic, frame, 0, 0, 400, 400, wxRETAINED);
  // Set constraints for canvas subwindow
  wxLayoutConstraints *c2 = new wxLayoutConstraints;
  c2->left.SameAs       (frame, wxLeft);
  c2->top.Below        (panel, wxTop);
  c2->right.SameAs      (frame, wxRight);
  c2->bottom.SameAs  (frame, wxBottom);
  canvas->SetConstraints(c2);
  
  wxLayoutConstraints *b1 = new wxLayoutConstraints;
  //b1->centreX.SameAs    (panel, wxCentreX);
  b1->top.SameAs        (panel, wxTop, 5);
  b1->width.PercentOf   (panel, wxWidth, 20);
  b1->height.AsIs       ();
  b1->left.SameAs       (panel, wxLeft);
  btn1->SetConstraints(b1);

  wxLayoutConstraints *b2 = new wxLayoutConstraints;
  //b2->centreX.SameAs    (panel, wxCentreX);
  b2->top.SameAs        (panel, wxTop, 5);
  b2->width.PercentOf   (panel, wxWidth, 20);
  b2->left.SameAs       (btn1, wxRight);
  b2->height.AsIs       ();
  btn2->SetConstraints(b2);
  
  wxLayoutConstraints *b3 = new wxLayoutConstraints;
  //b3->centreX.SameAs    (panel, wxCentreX);
  b3->top.SameAs        (panel, wxTop, 5);
  b3->width.PercentOf   (panel, wxWidth, 20);
  b3->left.SameAs       (btn2, wxRight);
  b3->height.AsIs       ();
  btn3->SetConstraints(b3);

  wxLayoutConstraints *b4 = new wxLayoutConstraints;
  //b3->centreX.SameAs    (panel, wxCentreX);
  b4->top.SameAs        (panel, wxTop, 5);
  b4->width.PercentOf   (panel, wxWidth, 20);
  b4->left.SameAs       (btn3, wxRight);
  b4->height.AsIs       ();
  btn4->SetConstraints(b4);


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

  frame->SetStatusText(_T("YaVec demo"));

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
  EVT_BUTTON(BUTTON_DASHY, MyFrame::toggleDashedLines)
  EVT_BUTTON(BUTTON_BOXES, MyFrame::toggleBoxes)
  EVT_BUTTON(BUTTON_ARROWS, MyFrame::toggleArrows)
  EVT_BUTTON(BUTTON_ARCS, MyFrame::toggleArcs)
  EVT_RIGHT_DOWN(MyFrame::OnMouse)
END_EVENT_TABLE()

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event) )
{
  Close(TRUE);
}

void MyFrame::toggleScreenDpi(wxCommandEvent& event) {
  if (mainpic->getScreenDpi()==80) mainpic->setScreenDpi(160);
  else  mainpic->setScreenDpi(80);
  canvas->refreshAll();
}

void MyFrame::toggleDashedLines(wxCommandEvent& event) {
  mainpic->updating(false);
  if (dlines.empty()) {
    YaVecPolyline *dline;
    for (int i=100; i<5000; i+=1000) {
      dline = mainpic->polyline();
      dline->addPoint(3000, 4000);
      dline->addPoint(i, 100);
      dline->lineStyle(YaVecLine::dashed);
      dline->styleValue(8.0);
      dlines.push_back(dline);
      
      dline = mainpic->polyline();
      dline->addPoint(3000, 4000);
      dline->addPoint(i+200, 100);
      dline->lineStyle(YaVecLine::dotted);
      dline->styleValue(8.0);
      dlines.push_back(dline);
      
      dline = mainpic->polyline();
      dline->addPoint(3000, 4000);
      dline->addPoint(i+400, 100);
      dline->lineStyle(YaVecLine::dash_dotted);
      dline->styleValue(5.0);
      dlines.push_back(dline);
      
      dline = mainpic->polyline();
      dline->addPoint(3000, 4000);
      dline->addPoint(i+600, 100);
      dline->lineStyle(YaVecLine::dash_double_dotted);
      dline->styleValue(8.0);
      dlines.push_back(dline);
      
      dline = mainpic->polyline();
      dline->addPoint(3000, 4000);
      dline->addPoint(i+800, 100);
      dline->lineStyle(YaVecLine::dash_triple_dotted);
      dline->styleValue(8.0);
      dlines.push_back(dline);
    }
  } else {
    list<YaVecPolyline*>::iterator dlineIt;
    for ( dlineIt = dlines.begin(); dlineIt != dlines.end(); ++dlineIt ) {
      if (!mainpic->remove(*dlineIt)) cerr << "ERROR: DashedLine element did not exist!" << endl; 
    }
    dlines.clear();
  }
  mainpic->updating(true);
  canvas->refreshAll();
}


void MyFrame::toggleArrows(wxCommandEvent& event) {
  mainpic->updating(false);
  if (alines.empty()) {
    YaVecPolyline *aline;
    for (int i=900; i<8000; i+=499) {
      aline = mainpic->polyline();
      aline->addPoint(i, 200);
      aline->addPoint(4000, 2000);
      aline->addPoint(8500-i, 3000);
      aline->lineStyle(YaVecLine::solid);
      aline->styleValue(8.0);
      aline->lineThickness(1+(i&3));
      if ((i&1)==1) aline->forwardArrow(true);
      if ((i&1)==1) aline->penColor(3);
      if ((i&2)==2) aline->backwardArrow(true);
      aline->backwardArrowType(3);
      aline->forwardArrowType(YaVecArrow::closed_indented_butt);
      aline->forwardArrowSize(1.0, 100.0, 250.0);
      aline->forwardArrowSize(1.0, 50.0, 250.0);
      alines.push_back(aline);
    }
  } else {
    list<YaVecPolyline*>::iterator alineIt;
    for ( alineIt = alines.begin(); alineIt != alines.end(); ++alineIt ) {
      if (!mainpic->remove(*alineIt)) cerr << "ERROR: DashedLine element did not exist!" << endl; 
    }
    alines.clear();
  }
  mainpic->updating(true);
  canvas->refreshAll();
}

void MyFrame::toggleArcs(wxCommandEvent& event) {
  mainpic->updating(false);
  if (arcs.empty()) {
    YaVecArc *arc;
    for (int i=0; i<8; i++) {
      arc = mainpic->arc(YVPosInt(100+i*500,4000), YVPosInt(200+i*500,4500), YVPosInt(400+i*500,4000));
      //arc->lineThickness(1+(i&3));
      //if ((i&1)==1) aline->forwardArrow(true);
      //if ((i&1)==1) aline->penColor(3);
      //if ((i&2)==2) aline->backwardArrow(true);
      //aline->backwardArrowType(3);
      //aline->forwardArrowType(YaVecArrow::closed_indented_butt);
      //aline->forwardArrowSize(1.0, 100.0, 250.0);
      //aline->forwardArrowSize(1.0, 50.0, 250.0);
      arcs.push_back(arc);
    }
  } else {
    list<YaVecArc*>::iterator arcIt;
    for ( arcIt = arcs.begin(); arcIt != arcs.end(); ++arcIt ) {
      if (!mainpic->remove(*arcIt)) cerr << "ERROR: ARC element did not exist!" << endl; 
    }
    arcs.clear();
  }
  mainpic->updating(true);
  canvas->refreshAll();
}

void MyFrame::toggleBoxes(wxCommandEvent& event) {
  mainpic->updating(false);
  if (boxes.empty()) {
    YaVecBox *dbox;
    for (int i=100; i<4000; i+=499) {
      dbox = mainpic->box(YVPosInt(i*2, 4200-i), YVPosInt((i+500)*2, 4200-i+500));
      dbox->lineStyle(YaVecLine::dashed);
      dbox->styleValue(static_cast<double>(i&15));
      boxes.push_back(dbox);

      dbox = mainpic->box(YVPosInt((i+200)*2, 4200-i+200), YVPosInt((i+500+200)*2, 4200-i+500+200));
      dbox->penColor(i&7);
      boxes.push_back(dbox);
    }
  } else {
    list<YaVecBox*>::iterator boxIt;
    for ( boxIt = boxes.begin(); boxIt != boxes.end(); ++boxIt ) {
      if (!mainpic->remove(*boxIt)) cerr << "ERROR: Box element did not exist!" << endl;
    }
    boxes.clear();
  }
  mainpic->updating(true);
  canvas->refreshAll();
}

void MyFrame::OnMouse(wxMouseEvent& event)
{
  YVPosInt pos(event.m_x, event.m_y);
  cout << "MOUSE @ " << pos << endl;
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
  canvas->refreshAll();
}
