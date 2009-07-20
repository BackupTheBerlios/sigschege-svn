// -*- c++ -*-
// \file  
// Copyright 2009 by Ulf Klaperski
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
// $Id: YaVecVwx.cpp 153 2009-06-29 22:17:21Z ro_kenn $

#include <iostream>
#include "YaVecVqt.h"
#include "YaVecFigure.h"
#include "YaVecElm.h"
#include <cmath>

using namespace std;
namespace YaVec {

  // Define a constructor for my canvas
  FigVqt::FigVqt(FFigure *picture, QWidget *parent = 0, int x, int y, int w, int h)
      : QWidget(parent), FigView(picture)
  {
    cout << "constr: " << this << endl;
    maxDist = 5*mypicture->scale()+5;
    resize(200, 200);
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
  }

void FigVqt::paintEvent(QPaintEvent *)
{
  cout << "PAINTEVENT" << endl;
  mypicture->drawView(this);
}

  void FigVqt::drawLine(PosInt from, PosInt to, int width, Array<int, 3> &color, int lineStyle, double styleLength) {
    QPainter painter(this);
    QColor LineColor(color[0], color[1], color[2]);
    painter.setPen(QPen(LineColor));
    painter.setBrush(LineColor);
    painter.setRenderHint(QPainter::Antialiasing);
    //painter.translate(width() / 2, height() / 2);
    //painter.scale(side / 200.0, side / 200.0);
    if (lineStyle==YaVecLine::solid) {
      painter.drawLine(from.xpos(), from.ypos(), to.xpos(), to.ypos());
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
          painter.drawLine(curPoint.xpos(), curPoint.ypos(), nextPoint.xpos(), nextPoint.ypos());
        } else {
          nextDist += styleLength;
          nextPoint = from+PosInt(static_cast<int>(nextDist*deltaX), static_cast<int>(nextDist*deltaY));
        }
        curPoint = nextPoint;
        curDist = nextDist;
        activePhase = !activePhase;
      }
    }
  }

  void FigVqt::drawArc(double xCenter, double yCenter, double radius, double phiStart, double phiEnd, int width, Array<int, 3> &color) {
  
    QPainter painter(this);
    QColor LineColor(color[0], color[1], color[2]);
    painter.setPen(QPen(LineColor));
    painter.setBrush(LineColor);
    painter.setRenderHint(QPainter::Antialiasing);
    double phi, phiDiff;
    phiDiff = 2*1.0/(radius*2*M_PI);

    phi = phiStart;
    if (phi<phiEnd) phiEnd -= 2*M_PI;
    while (phi>=phiEnd) {
      painter.drawPoint(static_cast<int>(xCenter+cos(phi)*radius), static_cast<int>(yCenter+sin(phi)*radius));
      phi -= phiDiff;
    }
  }


  void FigVqt::drawChar(PosInt origin, int rows, int width, int pitch, unsigned char *buffer, Array<int, 3> &color) {
    int x, y, bit_no, bit_val;
    char bb;
    QPainter painter(this);
    QColor CharColor(color[0], color[1], color[2]);
    painter.setPen(QPen(CharColor));
    painter.setBrush(CharColor);
    painter.setRenderHint(QPainter::Antialiasing);
    for (y=0; y<rows; ++y) {
      for (x=0; x<width; ++x) {
        bit_no = 7-(x % 8);
        bit_val = 1<<bit_no;
        bb=buffer[y*pitch+x/8];
        //cout << bit_no << ":" << bit_val << "-";
        if ((bb & bit_val) == bit_val) {
          painter.drawPoint(x+origin.xpos(), y+origin.ypos());
          //cout << ">" << x+origin.xpos() << ":" << y+origin.ypos() << endl;
        } else {
          //cout << " ";
        }
      }
    }
    
  }

  void FigVqt::setPaintBuffer(int color, int thickness) {
  }

  void FigVqt::clrPaintBuffer(void) {
  }


  void FigVqt::clear(void) {
    cout << "Clear" << endl;
    //ClearBackground();
  }

  void FigVqt::drawMarker(PosInt origin) {
  }


  void FigVqt::refreshAll(void) {
    update();
  }



}
