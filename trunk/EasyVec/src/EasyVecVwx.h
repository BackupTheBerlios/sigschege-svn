// -*- c++ -*-
// \file  
// Copyright 2004, 2005 by Ulf Klaperski
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


#ifndef _EASYVECVWX_H
#define _EASYVECVWX_H _EASYVECVWX_H 

#include "wx/wx.h"
#include "EasyVecView.h"

/// An EasyVec View class for the wxWidgets toolkit.
class EasyVecVwx : public wxWindow, public EasyVecView {
public:
  EasyVecVwx(EasyVecFigure *picture, wxFrame *frame, int x=-1, int y=-1, int width=-1, int height=-1,
             long style=wxTE_MULTILINE);
  virtual void drawLine(EVPosInt from, EVPosInt to, int width, int color, int lineStyle, double styleLength);
  virtual void drawChar(EVPosInt origin, int rows, int width, int pitch, unsigned char *buffer, int color);
  virtual void drawArrow(const EVPosInt &tip, double angle, int color, EasyVecArrow::arrowInfo *arrow);
  virtual void refreshAll(void);
  virtual void clear(void);
  
  void OnPaint(wxPaintEvent& event);
private:
  DECLARE_EVENT_TABLE();
  // pointer to wxPaintDC object for current onPaint event
  wxPaintDC *onPaintPaintDCp;
};


#endif /* _EASYVECVWX_H */

