// -*- c++ -*-
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

#include <wx/colour.h>
#include <iostream>
#include "EasyVecVwx.h"
#include "EasyVecFigure.h"
#include "EasyVecElm.h"

using namespace std;

BEGIN_EVENT_TABLE(EasyVecVwx, wxWindow)
    EVT_PAINT(EasyVecVwx::OnPaint)
END_EVENT_TABLE()

// Define a constructor for my canvas
EasyVecVwx::EasyVecVwx(EasyVecFigure *picture, wxFrame *frame, int x, int y, int w, int h, long style)
  : wxWindow(frame, -1, wxPoint(x, y), wxSize(w, h), style), EasyVecView(picture)
{
  cout << "constr: " << this << endl;
  SetBackgroundColour(*wxWHITE);
}


void EasyVecVwx::drawLine(EVPosInt from, EVPosInt to, int color, int lineStyle, double styleLength) {
  wxColour wxMyColour(easyvec_std_colors[color][0], easyvec_std_colors[color][1], easyvec_std_colors[color][2]);
  wxPen wxMyPen(wxMyColour, 1, 1);
  wxWindowDC *paintPtr;
  if (onPaintPaintDCp!=0) paintPtr = onPaintPaintDCp;
  else paintPtr = new wxClientDC;
  
  paintPtr->SetPen(wxMyPen);
  
  if (lineStyle==EasyVecLine::solid) {
    paintPtr->DrawLine(from.xpos(), from.ypos(), to.xpos(), to.ypos());
  } else {
    double dotLength = 0.0125*mypicture->getScreenDpi();
    double distance = to.distance(from);
    double curDist = 0.0;
    double nextDist = 0.0;
    bool activePhase = true;
    EVPosInt delta = to-from;
    double deltaX = delta.xpos()/distance;
    double deltaY = delta.ypos()/distance;
    EVPosInt curPoint(from);
    EVPosInt nextPoint;
    int activeCnt = 0;
    double activeLength = lineStyle==EasyVecLine::dashed ? styleLength : dotLength;
    while (curDist<distance) {
      if (activePhase) {
        if (lineStyle!=EasyVecLine::solid && lineStyle!=EasyVecLine::dashed) {
          if (lineStyle==EasyVecLine::dash_dotted) {
            activeLength = activeCnt==0 ? styleLength : dotLength;
            if (++activeCnt > 1) activeCnt=0;
          } else if (lineStyle==EasyVecLine::dash_double_dotted) {
            activeLength = activeCnt==0 ? styleLength : dotLength;
            if (++activeCnt > 2) activeCnt=0;
          } else if (lineStyle==EasyVecLine::dash_triple_dotted) {
            activeLength = activeCnt==0 ? styleLength : dotLength;
            if (++activeCnt > 3) activeCnt=0;
          }
        }
        nextDist += activeLength;
        if (nextDist>distance) nextDist = distance;
        nextPoint = from+EVPosInt(static_cast<int>(nextDist*deltaX), static_cast<int>(nextDist*deltaY));
        paintPtr->DrawLine(curPoint.xpos(), curPoint.ypos(), nextPoint.xpos(), nextPoint.ypos());
      } else {
        nextDist += styleLength;
        nextPoint = from+EVPosInt(static_cast<int>(nextDist*deltaX), static_cast<int>(nextDist*deltaY));
      }
      curPoint = nextPoint;
      curDist = nextDist;
      activePhase = !activePhase;
    }
  }
  if (onPaintPaintDCp==0) delete paintPtr;
  //Refresh();
}

void EasyVecVwx::drawChar(EVPosInt origin, int rows, int width, int pitch, unsigned char *buffer, int color) {
  int x,y, bit_no, bit_val;
  char bb;

  wxWindowDC *paintPtr;
  if (onPaintPaintDCp!=0) paintPtr = onPaintPaintDCp;
  else paintPtr = new wxClientDC;

  wxColour wxMyColour(easyvec_std_colors[color][0], easyvec_std_colors[color][1], easyvec_std_colors[color][2]);
  wxPen wxMyPen(wxMyColour, 1, 1);
  paintPtr->SetPen(wxMyPen);

  for (y=0; y<rows; ++y) {
    for (x=0; x<width; ++x) {
      bit_no = 7-(x % 8);
      bit_val = 1<<bit_no;
      bb=buffer[y*pitch+x/8];
      //cout << bit_no << ":" << bit_val << "-";
      if ((bb & bit_val) == bit_val) {
        paintPtr->DrawPoint(x+origin.xpos(), y+origin.ypos());
        //cout << ">" << x+origin.xpos() << ":" << y+origin.ypos() << endl;
      } else {
        //cout << " ";
      }
    }
  }

  if (onPaintPaintDCp==0) delete paintPtr;
  //Refresh();
}


void EasyVecVwx::clear(void) {
  cout << "Clear" << endl;
  Clear();
}

// Define the repainting behaviour
void EasyVecVwx::OnPaint(wxPaintEvent& WXUNUSED(event) )
{
  //SetBackgroundColour(*wxWHITE);
  cout << "onpaint: " << this << endl;
  wxPaintDC dc(this);
  onPaintPaintDCp = &dc;
  dc.SetPen(*wxWHITE_PEN);
  dc.SetBrush(*wxWHITE_BRUSH);
  //dc.DrawRectangle()
  mypicture->drawView(this);
  onPaintPaintDCp = 0;
}
