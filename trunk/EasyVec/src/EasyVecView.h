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


#ifndef _EASYVECVIEW_H
#define _EASYVECVIEW_H _EASYVECVIEW_H 

#include "EVPosInt.h"
#include "EasyVecLine.h"
#include "EasyVecArrow.h"


class EasyVecFigure;

/// An abstract class for creating views for the EasyVecFigure class.
/*!
 * View classes for the EasyVecFigure class must (well, should) be derived from this
 * class and must implement the purely virtual member functions.
 */
class EasyVecView {
public:
  EasyVecView(EasyVecFigure *picture);
  virtual ~EasyVecView();
  /// Draw a single line to the view. Used by Polyline, Box and others. 
  virtual void drawLine(EVPosInt from, EVPosInt to, int color, int lineStyle, double styleLength) = 0;
  /// Draw the character given in buffer to the view.
  virtual void drawChar(EVPosInt origin, int rows, int width, int pitch, unsigned char *buffer, int color) = 0;
  // Draw an arrow head (of a line).  
  virtual void drawArrow(const EVPosInt &tip, double angle, int color, int arrType, int arrStyle) = 0;
  // Draw an arrow head (of a line). This is just a convenience function which calculates the angle from the line.  
  void drawArrow(const EVPosInt &tip, const EVPosInt &from, int color, int arrType, int arrStyle);
  /// Force a redraw of the complete figure area.
  virtual void refreshAll(void) = 0;
  /// Clear the figure area.
  virtual void clear(void) = 0;

protected:
  EasyVecFigure *mypicture;
};


#endif /* _EASYVECVIEW_H */

