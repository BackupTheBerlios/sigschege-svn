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


#ifndef _COORDINATE_H
#define _COORDINATE_H _COORDINATE_H 

#include <iostream>


/// A simple 2D Position class which handles integer x,y coordinate pairs 


class YVPosInt {
public:
  /// Default constructor, which initializes both coordinates to 0. 
  YVPosInt() { cx = cy = 0; }
  /// General constructor to initialize coordinate from two ints.
  YVPosInt(int x, int y) {cx = x; cy = y;}
  /// General constructor to initialize coordinate from two doubles.
  YVPosInt(double x, double y) {cx = static_cast<int>(x); cy = static_cast<int>(y);}
  /// Function to set both coordinates. returns reference to result.
  YVPosInt &set(int x, int y) { cx=x; cy=y; return *this; };
  /// Subtraction operator.
  YVPosInt &operator-(const YVPosInt &destination) const;
  /// Multiplication (with an int) operator.
  YVPosInt &operator*(int mult ) const;
  /// Division assignment operator.
  YVPosInt &operator/=(double divisor);
  /// Division operator.
  YVPosInt &operator/(double divisor) const;
  
  /// Return the x coordinate.
  int xpos(void) const { return cx; };
  /// Return the y coordinate.
  int ypos(void) const { return cy; };
  /// Return the distance between two positions as double.
  double distance(const YVPosInt &destination) const;
  /// Return the angle of a line (against X-axis).
  double angle(const YVPosInt &dest) const;
  /// Set the coordinates of this to the minimum of this and the other YVPosInt object. 
  inline void minValues(const YVPosInt &other) {
    cx = cx<other.cx?cx:other.cx;
    cy = cy<other.cy?cy:other.cy;
  }
  /// Set the coordinates of this to the maximum of this and the other YVPosInt object. 
  inline void maxValues(const YVPosInt &other) {
    cx = cx>other.cx?cx:other.cx;
    cy = cy>other.cy?cy:other.cy;
  }
  /// Set the x coordinate
  void setx(const int x) { cx = x; }
  /// Set the y coordinate
  void sety(const int y) { cy = y; }
private:
  int cx, cy;
};

/// Standard C++ ostream operator.
std::ostream& operator<<(std::ostream& ostr, const YVPosInt Place);

/// Divide both coordinates by integer argument
inline YVPosInt operator/(const YVPosInt &z, int n) {
  return YVPosInt(z.xpos()/n, z.ypos()/n);
}

/// Add two YVPosInt.
inline YVPosInt operator+(const YVPosInt &a, const YVPosInt &b) {
  return YVPosInt(a.xpos()+b.xpos(), a.ypos()+b.ypos());
}

/// Return the minimum coordinates (independently) of both YVPosInts.
inline YVPosInt min_coords(const YVPosInt &a, const YVPosInt &b) {
  return YVPosInt(a.xpos()<b.xpos()?a.xpos():b.xpos(), a.ypos()<b.ypos()?a.ypos():b.ypos());
}

/// Return the maximum coordinates (independently) of both YVPosInts.
inline YVPosInt max_coords(const YVPosInt &a, const YVPosInt &b) {
  return YVPosInt(a.xpos()>b.xpos()?a.xpos():b.xpos(), a.ypos()>b.ypos()?a.ypos():b.ypos());
}


#endif /* _COORDINATE_H */

