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

#include "EVPosInt.h"
#include <cmath>

EVPosInt &EVPosInt::operator-(const EVPosInt &destination) const {
    EVPosInt *rv = new EVPosInt;
    *rv = *this;
    rv->cx -= destination.cx;
    rv->cy -= destination.cy;
    return *rv;
  };

EVPosInt &EVPosInt::operator*(int mult) const {
    EVPosInt *rv = new EVPosInt;
    *rv = *this;
    rv->cx *= mult;
    rv->cy *= mult;
    return *rv;
  
}

EVPosInt &EVPosInt::operator/=(double divisor) {
  cx = static_cast<int>(cx / divisor);
  cy = static_cast<int>(cy / divisor);
  return *this;
};

EVPosInt &EVPosInt::operator/(double divisor) const {
  EVPosInt *rv = new EVPosInt;
  *rv /= divisor;
  return *rv;
};


std::ostream& operator<<(std::ostream& ostr, const EVPosInt Place) {
  ostr << "x=" << Place.xpos() << ",y=" << Place.ypos();
  return ostr;
}

double EVPosInt::distance(const EVPosInt &dest) const {
  int xdist, ydist;
  xdist = cx - dest.cx;
  ydist = cy - dest.cy;
  if (xdist==0) {
    return fabs(ydist);
  } else if (ydist==0) {
    return fabs(xdist);
  } else {
    return sqrt(static_cast<double>(xdist)*xdist+static_cast<double>(ydist)*ydist);
  }
}

double EVPosInt::angle(const EVPosInt &from) const {
  double angl;
  int xdiff = xpos()-from.xpos();
  angl = atan(static_cast<double>(ypos()-from.ypos())/xdiff);
  if (xdiff<0) angl += M_PI;
  return angl;
}
