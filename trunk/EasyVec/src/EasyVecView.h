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


#ifndef _EASYVECVIEW_H
#define _EASYVECVIEW_H _EASYVECVIEW_H 

#include "EVPosInt.h"


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
  virtual void drawLine(EVPosInt from, EVPosInt to, int color) = 0;
  virtual void drawChar(EVPosInt origin, int rows, int width, int pitch, unsigned char *buffer, int color) = 0;
  virtual void clear(void) = 0;

protected:
  EasyVecFigure *mypicture;
};


#endif /* _EASYVECVIEW_H */

