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


#ifndef _COORDINATE_H
#define _COORDINATE_H _COORDINATE_H 

#include <iostream>


/// A simple 2D Position class which handles integer x,y coordinate pairs 


class EVPosInt {
public:
  /// Default constructor, which initializes both coordinates to 0. 
  EVPosInt() { cx = cy = 0; }
  /// General constructor to initialize coordinate from two ints.
  EVPosInt(int x, int y) {cx = x; cy = y;}
  /// Function to set both coordinates. returns reference to result.
  EVPosInt &set(int x, int y) { cx=x; cy=y; return *this; };
  /// Subtraction operator.
  EVPosInt operator-(const EVPosInt &destination) {
    return EVPosInt(cx-destination.cx,cy-destination.cy);
  };
  /// Return the x coordinate.
  int xpos(void) const { return cx; };
  /// Return the y coordinate.
  int ypos(void) const { return cy; };
  /// Return the distance between two positions as double.
  double distance(const EVPosInt &destination) const;
  /// Set the coordinates of this to the minimum of this and the other EVPosInt object. 
  inline void min_values(const EVPosInt &other) {
    cx = cx<other.cx?cx:other.cx;
    cy = cy<other.cy?cy:other.cy;
  }
  /// Set the coordinates of this to the maximum of this and the other EVPosInt object. 
  inline void max_values(const EVPosInt &other) {
    cx = cx>other.cx?cx:other.cx;
    cy = cy>other.cy?cy:other.cy;
  }
 
private:
  int cx, cy;
};

/// Standard C++ ostream operator.
std::ostream& operator<<(std::ostream& ostr, const EVPosInt Place);

/// Divide both coordinates by integer argument
inline EVPosInt operator/(const EVPosInt &z, int n) {
  return EVPosInt(z.xpos()/n, z.ypos()/n);
}

// Add two EVPosInt.
inline EVPosInt operator+(const EVPosInt &a, const EVPosInt &b) {
  return EVPosInt(a.xpos()+b.xpos(), a.ypos()+b.ypos());
}

inline EVPosInt min_coords(const EVPosInt &a, const EVPosInt &b) {
  return EVPosInt(a.xpos()<b.xpos()?a.xpos():b.xpos(), a.ypos()<b.ypos()?a.ypos():b.ypos());
}

inline EVPosInt max_coords(const EVPosInt &a, const EVPosInt &b) {
  return EVPosInt(a.xpos()>b.xpos()?a.xpos():b.xpos(), a.ypos()>b.ypos()?a.ypos():b.ypos());
}


#endif /* _COORDINATE_H */

