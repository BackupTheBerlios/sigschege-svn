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

#include "EVPosInt.h"
#include <cmath>

std::ostream& operator<<(std::ostream& ostr, const EVPosInt Place) {
  ostr << "x=" << Place.xpos() << ",y=" << Place.ypos();
  return ostr;
}

double EVPosInt::distance(const EVPosInt &dest) const {
  int xdist, ydist;
  xdist = cx - dest.cx;
  ydist = cy - dest.cy;
  if (xdist==0) {
    return ydist;
  } else if (ydist==0) {
    return xdist;
  } else {
    return sqrt(static_cast<double>(xdist)*xdist+static_cast<double>(ydist)*ydist);
  }
}
