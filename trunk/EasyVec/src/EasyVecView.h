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


#ifndef _EASYVECVIEW_H
#define _EASYVECVIEW_H _EASYVECVIEW_H 

#include "EVPosInt.h"


class EasyVec;

class EasyVecView {
public:
  EasyVecView(EasyVec *picture);
  virtual ~EasyVecView();
  virtual void draw_line(EVPosInt from, EVPosInt to, int color) = 0;
  virtual void draw_char(EVPosInt origin, int rows, int width, int pitch, unsigned char *buffer, int color) = 0;
  virtual void clear(void) = 0;

protected:
  EasyVec *mypicture;
};


#endif /* _EASYVECVIEW_H */

