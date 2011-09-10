// -*- c++ -*-
// \file  
// Copyright 2004, 2005 by Ulf Klaperski
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

#include <wx/colour.h>
#include <iostream>
#include "YaVecVwx.h"
#include "YaVecFigure.h"
#include "YaVecElm.h"
#include <cmath>

using namespace std;
namespace YaVec {

  BEGIN_EVENT_TABLE(FigVwx, wxWindow)
    EVT_PAINT(FigVwx::OnPaint)
    EVT_RIGHT_DOWN(FigVwx::OnMouse)
    END_EVENT_TABLE()

  // Define a constructor for my canvas
    FigVwx::FigVwx(FFigure *picture, wxFrame *frame, int x, int y, int w, int h, long style)
      : wxScrolledWindow(frame, -1, wxPoint(x, y), wxSize(w, h), style), FigView(picture)
  {
    cout << "constr: " << this << endl;
    SetBackgroundColour(*wxWHITE);
    maxDist = 5*mypicture->scale()+5;
    SetVirtualSize(wxSize(w, h));
    SetScrollRate( 10, 10 );
  }


  void FigVwx::drawLine(PosInt from, PosInt to, int width, Array<int, 3> &color, int lineStyle, double styleLength) {
    wxColour wxMyColour(color[0], color[1], color[2]);
    wxPen wxMyPen(wxMyColour, width, 1);
    wxWindowDC *paintPtr;
    if (onPaintPaintDCp!=0) paintPtr = onPaintPaintDCp;
    else paintPtr = new wxClientDC;
  
    paintPtr->SetPen(wxMyPen);

    if (lineStyle==YaVecLine::solid) {
      paintPtr->DrawLine(from.xpos(), from.ypos(), to.xpos(), to.ypos());
    } else {
      double dotLength = 0.0125*mypicture->getScreenDpi();
      double distance = to.distance(from);
      double curDist = 0.0;
      double nextDist = 0.0;
      bool activePhase = true;
      PosInt delta = to-from;
      double deltaX = delta.xpos()/distance;
      double deltaY = delta.ypos()/distance;
      PosInt curPoint(from);
      PosInt nextPoint;
      int activeCnt = 0;
      double activeLength = lineStyle==YaVecLine::dashed ? styleLength : dotLength;
      while (curDist<distance) {
        if (activePhase) {
          if (lineStyle!=YaVecLine::solid && lineStyle!=YaVecLine::dashed) {
            if (lineStyle==YaVecLine::dash_dotted) {
              activeLength = activeCnt==0 ? styleLength : dotLength;
              if (++activeCnt > 1) activeCnt=0;
            } else if (lineStyle==YaVecLine::dash_double_dotted) {
              activeLength = activeCnt==0 ? styleLength : dotLength;
              if (++activeCnt > 2) activeCnt=0;
            } else if (lineStyle==YaVecLine::dash_triple_dotted) {
              activeLength = activeCnt==0 ? styleLength : dotLength;
              if (++activeCnt > 3) activeCnt=0;
            }
          }
          nextDist += activeLength;
          if (nextDist>distance) nextDist = distance;
          nextPoint = from+PosInt(static_cast<int>(nextDist*deltaX), static_cast<int>(nextDist*deltaY));
          paintPtr->DrawLine(curPoint.xpos(), curPoint.ypos(), nextPoint.xpos(), nextPoint.ypos());
        } else {
          nextDist += styleLength;
          nextPoint = from+PosInt(static_cast<int>(nextDist*deltaX), static_cast<int>(nextDist*deltaY));
        }
        curPoint = nextPoint;
        curDist = nextDist;
        activePhase = !activePhase;
      }
    }
  
    if (onPaintPaintDCp==0) delete paintPtr;
  }

  void FigVwx::drawArc(double xCenter, double yCenter, double radius, double phiStart, double phiEnd, int width, YaVec::Array<int, 3> &color) {
  
    double phi, phiDiff;
    phiDiff = 2*1.0/(radius*2*M_PI);

    phi = phiStart;
    if (phi<phiEnd) phiEnd -= 2*M_PI;
    while (phi>=phiEnd) {
      pBufpaintPtr->DrawPoint(static_cast<int>(xCenter+cos(phi)*radius), static_cast<int>(yCenter+sin(phi)*radius));
      phi -= phiDiff;
    }  
  }


  void FigVwx::drawChar(PosInt origin, int rows, int width, int pitch, unsigned char *buffer, Array<int, 3> &color) {
    int x, y, bit_no, bit_val;
    char bb;

    wxWindowDC *paintPtr;
    if (onPaintPaintDCp!=0) paintPtr = onPaintPaintDCp;
    else paintPtr = new wxClientDC;

    wxColour wxMyColour(color[0], color[1], color[2]);
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
  }

  void FigVwx::setPaintBuffer(int color, int thickness) {
    if (onPaintPaintDCp!=0) pBufpaintPtr = onPaintPaintDCp;
    else   pBufpaintPtr = new wxClientDC;
    // TODO: thickness

    pBufColor = new wxColour(yavec_std_colors[color][0], yavec_std_colors[color][1], yavec_std_colors[color][2]);
    pBufPen = new wxPen(*pBufColor, 1, 1);
    pBufpaintPtr->SetPen(*pBufPen);
  }

  void FigVwx::clrPaintBuffer(void) {
    delete pBufColor;
    pBufColor = 0;
    delete pBufPen;
    pBufPen = 0;
    if (pBufpaintPtr != onPaintPaintDCp) delete pBufpaintPtr;
    pBufpaintPtr = 0;
  }


  void FigVwx::clear(void) {
    cout << "Clear" << endl;
    ClearBackground();
  }

  void FigVwx::drawMarker(PosInt origin) {
    wxColour wxMyColour(255, 255, 255);
    wxPen wxMyPen(wxMyColour, 1, 1);
    wxWindowDC *paintPtr;
    if (onPaintPaintDCp!=0) paintPtr = onPaintPaintDCp;
    else paintPtr = new wxClientDC;
  
    paintPtr->SetPen(wxMyPen);

    paintPtr->SetLogicalFunction(wxXOR);
    paintPtr->DrawLine(origin.xpos()-2, origin.ypos()-2, origin.xpos()+3, origin.ypos()+3);  
    paintPtr->DrawLine(origin.xpos()+2, origin.ypos()-2, origin.xpos()-3, origin.ypos()+3);  
    paintPtr->SetLogicalFunction(wxCOPY);

    if (onPaintPaintDCp==0) delete paintPtr;
  }


  void FigVwx::refreshAll(void) {
    int width, height;
    GetClientSize(&width, &height);
    wxRect rect = wxRect(0, 0, width, height);
    Refresh(true, &rect);
  }


  /// Define the repainting behaviour
  void FigVwx::OnPaint(wxPaintEvent& WXUNUSED(event) )
  {
    //SetBackgroundColour(*wxWHITE);
    wxPaintDC dc(this);
    onPaintPaintDCp = &dc;
    dc.SetPen(*wxWHITE_PEN);
    dc.SetBrush(*wxWHITE_BRUSH);
    //dc.DrawRectangle()
    mypicture->drawView(this);
    onPaintPaintDCp = 0;
  }

  void FigVwx::OnMouse(wxMouseEvent& event)
  {
    PosInt pos(event.m_x, event.m_y);
    cout << "MOUSE @ " << pos << endl;
    list<YaVecElmHit> hits;
    mypicture->getElmNearPos(pos*mypicture->scale(), maxDist, true, true, hits);
    cout << "HITS " << hits.size() << endl;
  }

}
