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


#ifndef _YAVECVIEW_H
#define _YAVECVIEW_H _YAVECVIEW_H 

#include "YVPosInt.h"
#include "YaVecLine.h"
#include "YaVecArrow.h"
#include "YaVecUtil.h"

namespace YaVec {

  class FFigure;

  /// An abstract class for creating views for the FFigure class.
  /*!
   * View classes for the FFigure class must (well, should) be derived from this
   * class and must implement the purely virtual member functions. An existing view class
   * exists for the wx Widgets library (FigVwx). For creating a new view class this can
   * also be used as an example.
   */
  class FigView {
  public:
    /// The constructor (register this view in the figure).
    FigView(FFigure *picture);
    /// The destructor (unregister this view from the figure).
    virtual ~FigView();
    /// Draw a single line to the view. Used by Polyline, Box and others.
    /*! 
     * \param from Startpoint of the line.
     * \param to   Endpoint of the line.
     * \param width Width of the line.
     * \param color Pen color of the line.
     * \param lineStyle The line style (solid, dashed, dotted, dash-dotted).
     * \param styleLength The length of the dashes or spaces between dashes or dots.
     */
    virtual void drawLine(PosInt from, PosInt to, int width, YaVec::Array<int, 3> &color, int lineStyle, double styleLength) = 0;
    /// Draw a single arc to the view. Used by Arc. The arc is drawn counterclockwise.
    /*! 
     * \param center Center of the arc circle.
     * \param radius Radius of the circle.
     * \param phiStart  Start angle of the arc. 
     * \param phiEnd End angle of the arc.
     * \param width Width of the arc.
     */
    virtual void drawArc(double xCenter, double yCenter, double radius, double phiStart, double phiEnd, int width) = 0;
    /// Draw the character given in buffer to the view.
    virtual void drawChar(PosInt origin, int rows, int width, int pitch, unsigned char *buffer, int color) = 0;
    /// Set up a paint buffer to speed up multiple paint events (used by Arc)
    // if a view doesn't require buffering color or thickness, just store them separately.
    virtual void setPaintBuffer(int color, int thickness) = 0; 
    virtual void clrPaintBuffer(void) = 0; 
    /// Force a redraw of the complete figure area.
    virtual void refreshAll(void) = 0;
    /// Clear the figure area.
    virtual void clear(void) = 0;
    // draw a marker at this point
    virtual void drawMarker(PosInt origin) = 0;
  protected:
    FFigure *mypicture;
  };

}

#endif /* _YAVECVIEW_H */

