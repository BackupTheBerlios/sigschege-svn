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


#ifndef _YAVECVWX_H
#define _YAVECVWX_H _YAVECVWX_H 

#include "wx/wx.h"
#include "YaVecUtil.h"
#include "YaVecView.h"

namespace YaVec {

  /// A YaVec View class for the wxWidgets toolkit.
  class FigVwx : public wxScrolledWindow, public FigView {
  public:
    /// Constructor for this class.
    FigVwx(FFigure *picture, wxFrame *frame, int x=-1, int y=-1, int width=-1, int height=-1,
             long style=wxTE_MULTILINE);
    virtual void drawLine(PosInt from, PosInt to, int width, YaVec::Array<int, 3> &color, int lineStyle, double styleLength);
    /// Draw an arc clockwise from phiStart to phiEnd.
    /*!
     * This draws an arc of a circle. The drawing is done clockwise (negative phi direction) from
     * phiStart to phiEnd. Before calling this function setPaintBuffer() must be called to set
     * up the pBuf (paint buffer) elements.
     * \param xCenter The horizontal center of the arc circle.
     * \param yCenter The vertical center of the arc circle.
     * \param radius  The radius of the circle.
     * \param phiStart The start angle of the circle, must be between 0 and 2*pi. 
     * \param phiEnd The end angle of the circle, must be between 0 and 2*pi. 
     * \param width The width of the line to be drawn.
     */
    virtual void drawArc(double xCenter, double yCenter, double radius, double phiStart, double phiEnd, int width);
    virtual void drawChar(PosInt origin, int rows, int width, int pitch, unsigned char *buffer, int color);
    /// Set up a paint buffer for functions which require it.
    virtual void setPaintBuffer(int color, int thickness); 
    /// Delete a previously allocated paint buffer.
    virtual void clrPaintBuffer(void); 
    virtual void refreshAll(void);
    virtual void clear(void);
    /// Draw a marker at this point.
    virtual void drawMarker(PosInt origin);

    /// Actions to be done when painting.
    void OnPaint(wxPaintEvent& event);
    /// Actions to be done for mouse events.
    void OnMouse(wxMouseEvent& event);
  private:
    DECLARE_EVENT_TABLE();
    // pointer to wxPaintDC object for current onPaint event
    wxPaintDC *onPaintPaintDCp;
    int maxDist;
    wxPen *pBufPen;
    wxColour *pBufColor;
    wxWindowDC *pBufpaintPtr;
  };

}

#endif /* _YAVECVWX_H */

