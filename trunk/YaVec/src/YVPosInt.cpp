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

#include "YVPosInt.h"
#include <cmath>

namespace YaVec {

  PosInt &PosInt::operator-(const PosInt &destination) const {
    PosInt *rv = new PosInt;
    *rv = *this;
    rv->cx -= destination.cx;
    rv->cy -= destination.cy;
    return *rv;
  };

  PosInt &PosInt::operator*(int mult) const {
    PosInt *rv = new PosInt;
    *rv = *this;
    rv->cx *= mult;
    rv->cy *= mult;
    return *rv;
  
  }

  PosInt &PosInt::operator*(double mult) const {
    PosInt *rv = new PosInt;
    *rv = *this;
    rv->cx = static_cast<int>(rv->cx * mult);
    rv->cy = static_cast<int>(rv->cy * mult);
    return *rv;
  
  }

  PosInt &PosInt::operator/=(double divisor) {
    cx = static_cast<int>(cx / divisor);
    cy = static_cast<int>(cy / divisor);
    return *this;
  };

  PosInt &PosInt::operator/(double divisor) const {
    PosInt *rv = new PosInt;
    *rv /= divisor;
    return *rv;
  };


  std::ostream& operator<<(std::ostream& ostr, const PosInt Place) {
    ostr << "x=" << Place.xpos() << ",y=" << Place.ypos();
    return ostr;
  }

  double PosInt::distance(const PosInt &dest) const {
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

  double PosInt::angle(const PosInt &from) const {
    double angl;
    int xdiff = xpos()-from.xpos();
    angl = atan(static_cast<double>(ypos()-from.ypos())/xdiff);
    if (xdiff<0) angl += M_PI;
    return angl;
  }

}
