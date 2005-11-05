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

namespace YaVec {

  /// A simple 2D Position class which handles integer x,y coordinate pairs.
  
  class PosInt {
  public:
    /// Default constructor, which initializes both coordinates to 0. 
    PosInt() { cx = cy = 0; }
    /// General constructor to initialize coordinate from two ints.
    PosInt(int x, int y) {cx = x; cy = y;}
    /// General constructor to initialize coordinate from two doubles.
    PosInt(double x, double y) {cx = static_cast<int>(x); cy = static_cast<int>(y);}
    /// Function to set both coordinates. returns reference to result.
    PosInt &set(int x, int y) { cx=x; cy=y; return *this; };
    /// Subtraction operator.
    PosInt &operator-(const PosInt &destination) const;
    /// Multiplication (with an int) operator.
    PosInt &operator*(int mult ) const;
    /// Multiplication (with a double) operator.
    PosInt &operator*(double mult ) const;
    /// Division assignment operator.
    PosInt &operator/=(double divisor);
    /// Division operator.
    PosInt &operator/(double divisor) const;
    /// Adding assignment operator.
    PosInt &operator+=(PosInt &add);
    /// Adding assignment operator.
    PosInt &operator+=(PosInt add);
  
    /// Return the x coordinate.
    int xpos(void) const { return cx; };
    /// Return the y coordinate.
    int ypos(void) const { return cy; };
    /// Return the distance between two positions as double.
    double distance(const PosInt &destination) const;
    /// Return the angle of a line (against X-axis).
    double angle(const PosInt &dest) const;
    /// Set the coordinates of this to the minimum of this and the other PosInt object. 
    inline void minValues(const PosInt &other) {
      cx = cx<other.cx?cx:other.cx;
      cy = cy<other.cy?cy:other.cy;
    }
    /// Set the coordinates of this to the maximum of this and the other PosInt object. 
    inline void maxValues(const PosInt &other) {
      cx = cx>other.cx?cx:other.cx;
      cy = cy>other.cy?cy:other.cy;
    }
    /// Shift left operator (shift applied to both coordinates).
    PosInt operator<<(int shift);
    /// Shift right operator (shift applied to both coordinates).
    PosInt operator>>(int shift);
    /// Set the x coordinate
    void setx(const int x) { cx = x; }
    /// Set the y coordinate
    void sety(const int y) { cy = y; }

    /// Increment the x coordinate
    int incx(void) { return ++cx; }
    /// Increment the y coordinate
    int incy(void) { return ++cy; }
    /// Decrement the x coordinate
    int decx(void) { return --cx; }
    /// Decrement the y coordinate
    int decy(void) { return --cy; }
  
  private:
    int cx, cy;
  };

  /// Standard C++ ostream operator.
  std::ostream& operator<<(std::ostream& ostr, const PosInt Place);

  /// Divide both coordinates by integer argument
  inline PosInt operator/(const PosInt &z, int n) {
    return PosInt(z.xpos()/n, z.ypos()/n);
  }

  /// Add two PosInt.
  inline PosInt operator+(const PosInt &a, const PosInt &b) {
    return PosInt(a.xpos()+b.xpos(), a.ypos()+b.ypos());
  }

  /// Add a PosInt to this one.
  inline PosInt &PosInt::operator+=(PosInt &add) {
    this->cx += add.cx;
    this->cx += add.cx;
    return *this;
  }

  inline PosInt &PosInt::operator+=(PosInt add) {
    this->cx += add.cx;
    this->cy += add.cy;
    return *this;
  }

  inline PosInt PosInt::operator<<(int shift) {
    return PosInt(cx<<shift, cy<<shift);
  }

  inline PosInt PosInt::operator>>(int shift) {
    return PosInt(cx>>shift, cy>>shift);
  }


  /// Return the minimum coordinates (independently) of both PosInts.
  inline PosInt min_coords(const PosInt &a, const PosInt &b) {
    return PosInt(a.xpos()<b.xpos()?a.xpos():b.xpos(), a.ypos()<b.ypos()?a.ypos():b.ypos());
  }

  /// Return the maximum coordinates (independently) of both PosInts.
  inline PosInt max_coords(const PosInt &a, const PosInt &b) {
    return PosInt(a.xpos()>b.xpos()?a.xpos():b.xpos(), a.ypos()>b.ypos()?a.ypos():b.ypos());
  }

}

#endif /* _COORDINATE_H */

