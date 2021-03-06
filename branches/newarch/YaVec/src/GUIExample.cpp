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
#include <cmath>

#include <cstdio>

using namespace std;
using namespace YaVec;

MyFrame   *frame = (MyFrame *) NULL;
wxMenuBar *menu_bar = (wxMenuBar *) NULL;
FigVwx *canvas;

int state = 4;

IMPLEMENT_APP(MyApp);

FPolyline* mainline;
list<FPolyline *> dlines;
list<FPolyline *> alines;
list<FArc *> arcs;
list<FText *> texts;
list<FBox *> tboxes;
list<FBox *> boxes;
FFigure *mainpic;

MyApp::MyApp()
{
}


bool MyApp::OnInit()
{

  FFigure *ev_pic = new FFigure();
  FPolyline *nline;
  nline = ev_pic->polyline();
  nline->addPoint(1500, 1500);
  nline->addPoint(300, 1500);
  nline->addPoint(3300, 1500);
  nline->addPoint(1720, 60);
  nline->depth(66);
  mainline = nline;
  mainpic = ev_pic;
  

  FText *ntext;
  ntext = ev_pic->text();
  ntext->setText("This is a good YaVec Demo");
  ntext->penColor(2);
  ntext->setOrigin(PosInt(300, 6000));
  ntext->setSize(30);
  ntext->depth(55);

  FPolyline *tline;
  tline = ev_pic->polyline();
  nline->addPoint(300, 4500);
  nline->addPoint(5000, 4500);
  
  // Create the main frame window
  frame = new MyFrame(NULL, _T("YaVec Demo"), -1, -1, 800, 600);

  frame->SetAutoLayout(TRUE);

  // Make a menubar
  wxMenu *file_menu = new wxMenu;

  file_menu->Append(LAYOUT_ADD_PLINE_POINT, _T("&Add point"),      _T("Add point"));
  file_menu->Append(LAYOUT_TOGGLE_SCREENDPI, _T("&Toggle screen dpi"),      _T("Toggle screen dpi"));
  file_menu->Append(LAYOUT_TOGGLE_MARKERS, _T("&Toggle Markers"),      _T("Toggle Markers"));
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
  wxButton *btn5 = new wxButton(panel, BUTTON_TEXT, _T("Toggle text")) ;

  canvas = new FigVwx(ev_pic, frame, 0, 0, 400, 400, wxRETAINED);
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

  wxLayoutConstraints *b5 = new wxLayoutConstraints;
  //b3->centreX.SameAs    (panel, wxCentreX);
  b5->top.SameAs        (panel, wxTop, 5);
  b5->width.PercentOf   (panel, wxWidth, 20);
  b5->left.SameAs       (btn4, wxRight);
  b5->height.AsIs       ();
  btn5->SetConstraints(b5);

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
  EVT_MENU(LAYOUT_TOGGLE_MARKERS, MyFrame::toggleMarkers)
  EVT_MENU(LAYOUT_TOGGLE_DASHY, MyFrame::toggleDashedLines)
  EVT_MENU(LAYOUT_SAVE, MyFrame::save)
  EVT_BUTTON(BUTTON_DASHY, MyFrame::toggleDashedLines)
  EVT_BUTTON(BUTTON_BOXES, MyFrame::toggleBoxes)
  EVT_BUTTON(BUTTON_ARROWS, MyFrame::toggleArrows)
  EVT_BUTTON(BUTTON_ARCS, MyFrame::toggleArcs)
  EVT_BUTTON(BUTTON_TEXT, MyFrame::toggleText)
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

void MyFrame::toggleMarkers(wxCommandEvent& event) {
  if (++state>5) state=0;
  bool marker = (state&4)!=4;
  bool hier = (state&2)==2;
  bool comp = (state&1)==1;
  cout << "MARKERS=" << marker << " hier=" << hier << " comp=" << comp << " state=" << state <<endl;
  //mainpic->setMarkers(marker, hier, comp);
  mainpic->setMarkers(true, true, true);
  canvas->refreshAll();
}

void MyFrame::toggleDashedLines(wxCommandEvent& event) {
  mainpic->updating(false);
  if (dlines.empty()) {
    FPolyline *dline;
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
    list<FPolyline*>::iterator dlineIt;
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
    FPolyline *aline;
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
    list<FPolyline*>::iterator alineIt;
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
    FArc *arc;
    for (int i=0; i<8; i++) {
      arc = mainpic->arc(PosInt(0+i*1000,4000), PosInt(600+i*1000,4600), PosInt(1200+i*1000,4000));
      arc->lineStyle(i&3);
      arc->penColor(i+8);
      arcs.push_back(arc);
      arc = mainpic->arc(PosInt(400+i*800, 2000), 380, true, M_PI*2*7/8, M_PI*2*i/8, (i%2)==1);
      arc->penColor(i&15);
      arc->lineStyle(i&3);
      arcs.push_back(arc);
    }
  } else {
    list<FArc*>::iterator arcIt;
    for ( arcIt = arcs.begin(); arcIt != arcs.end(); ++arcIt ) {
      if (!mainpic->remove(*arcIt)) cerr << "ERROR: ARC element did not exist!" << endl; 
    }
    arcs.clear();
  }
  mainpic->updating(true);
  canvas->refreshAll();
}

void MyFrame::toggleText(wxCommandEvent& event) {
  mainpic->updating(false);
  if (texts.empty()) {
    FText *atext;
    double angle;
    FBox *nbox;
    PosInt ul, lr;
    for (int i=1; i<7; i++) {
      angle = 60*i;
      atext = mainpic->text();
      atext->penColor(i+3);
      atext->setOrigin(PosInt(4000, 4200));
      atext->setSize(30);
      atext->setAngle(angle);
      atext->setText("Text with angle AVA");
      atext->depth(11);
      atext->getBoundingBox(ul, lr);
      cout << "BBOX=" << ul << lr << endl;
      nbox = mainpic->box(ul, lr);
      nbox->depth(1);
      tboxes.push_back(nbox);
      texts.push_back(atext);
  }
  } else {
    list<FText*>::iterator textIt;
    for ( textIt = texts.begin(); textIt != texts.end(); ++textIt ) {
      if (!mainpic->remove(*textIt)) cerr << "ERROR: Text element did not exist!" << endl; 
    }
    texts.clear();
    list<FBox*>::iterator boxIt;
    for ( boxIt = tboxes.begin(); boxIt != tboxes.end(); ++boxIt ) {
      if (!mainpic->remove(*boxIt)) cerr << "ERROR: Text box element did not exist!" << endl; 
    }
    tboxes.clear();
  }
  mainpic->updating(true);
  canvas->refreshAll();
}


void MyFrame::toggleBoxes(wxCommandEvent& event) {
  mainpic->updating(false);
  if (boxes.empty()) {
    FBox *dbox;
    int j = 3;
    for (int i=100; i<4000; i+=499) {
      j++;
      dbox = mainpic->box(PosInt(i*2, 4200-i), PosInt((i+500)*2, 4200-i+500));
      dbox->lineStyle(YaVecLine::dashed);
      dbox->styleValue(static_cast<double>(i&15));
      dbox->fillColor(j);
      dbox->areaFill(20);
      boxes.push_back(dbox);

      dbox = mainpic->box(PosInt((i+200)*2, 4200-i+200), PosInt((i+500+200)*2, 4200-i+500+200));
      dbox->penColor(i&7);
      boxes.push_back(dbox);
    }
  } else {
    list<FBox*>::iterator boxIt;
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
  PosInt pos(event.m_x, event.m_y);
  cout << "MOUSE @ " << pos << endl;
}


void MyFrame::save(wxCommandEvent& event) {
  mainpic->save("demogui_result.fig");  
  mainpic->exportFig2dev("png", "demogui_result.png");  
  
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
