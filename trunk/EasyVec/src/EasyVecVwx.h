// -*- c++ -*-
/// \file 
 
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


#ifndef _EASYVECVWX_H
#define _EASYVECVWX_H _EASYVECVWX_H 

#include "wx/wx.h"
#include "EasyVecView.h"

class EasyVecVwx : public wxWindow, public EasyVecView {
public:
  EasyVecVwx(EasyVec *picture, wxFrame *frame, int x=-1, int y=-1, int width=-1, int height=-1,
             long style=wxTE_MULTILINE);
  virtual void draw_line(EVPosInt from, EVPosInt to, int color);
  virtual void draw_char(EVPosInt origin, int rows, int width, int pitch, unsigned char *buffer, int color);
  virtual void clear(void);
  
   void OnPaint(wxPaintEvent& event);
private:
  DECLARE_EVENT_TABLE();
};


#endif /* _EASYVECVWX_H */

