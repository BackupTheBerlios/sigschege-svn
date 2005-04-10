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


#ifndef _EASYVECVWX_H
#define _EASYVECVWX_H _EASYVECVWX_H 

#include "wx/wx.h"
#include "YaVecView.h"

/// An YaVec View class for the wxWidgets toolkit.
class YaVecVwx : public wxWindow, public YaVecView {
public:
  YaVecVwx(YaVecFigure *picture, wxFrame *frame, int x=-1, int y=-1, int width=-1, int height=-1,
             long style=wxTE_MULTILINE);
  virtual void drawLine(EVPosInt from, EVPosInt to, int width, int color, int lineStyle, double styleLength);
  virtual void drawArc(EVPosInt center, int radius, double phiStart, double phiEnd, int width, int color, int lineStyle, double styleLength);  
  virtual void drawChar(EVPosInt origin, int rows, int width, int pitch, unsigned char *buffer, int color);
  virtual void drawArrow(const EVPosInt &tip, double angle, int color, YaVecArrow::arrowInfo *arrow);
  virtual void refreshAll(void);
  virtual void clear(void);
  
  void OnPaint(wxPaintEvent& event);
  void OnMouse(wxMouseEvent& event);
private:
  DECLARE_EVENT_TABLE();
  // pointer to wxPaintDC object for current onPaint event
  wxPaintDC *onPaintPaintDCp;
  int maxDist;
};


#endif /* _EASYVECVWX_H */

