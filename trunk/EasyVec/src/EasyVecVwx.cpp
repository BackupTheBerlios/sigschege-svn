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
// $Id: $

#include <wx/colour.h>
#include <iostream>
#include "EasyVecVwx.h"
#include "EasyVec.h"
#include "EasyVecElm.h"

using namespace std;

BEGIN_EVENT_TABLE(EasyVecVwx, wxWindow)
    EVT_PAINT(EasyVecVwx::OnPaint)
END_EVENT_TABLE()

// Define a constructor for my canvas
EasyVecVwx::EasyVecVwx(EasyVec *picture, wxFrame *frame, int x, int y, int w, int h, long style)
  : wxWindow(frame, -1, wxPoint(x, y), wxSize(w, h), style), EasyVecView(picture)
{
  cout << "constr: " << this << endl;
  SetBackgroundColour(*wxWHITE);
}


void EasyVecVwx::draw_line(EVPosInt from, EVPosInt to, int color) {
  cout << "DrawLine: " << from << ":" << to << endl;
  wxPaintDC dc(this);
  wxColour wxMyColour(easyvec_std_colors[color][0], easyvec_std_colors[color][1], easyvec_std_colors[color][2]);
  wxPen wxMyPen(wxMyColour, 1, 1);
  dc.SetPen(wxMyPen);
  dc.DrawLine(from.xpos(), from.ypos(), to.xpos(), to.ypos());
  Refresh();
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
  dc.SetPen(*wxWHITE_PEN);
  dc.SetBrush(*wxWHITE_BRUSH);
  //dc.DrawRectangle()
  mypicture->draw_view(this);
}
