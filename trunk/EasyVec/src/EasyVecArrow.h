// -*- c++ -*-
// \file  
// Copyright 2005 by Ulf Klaperski
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


#ifndef _EASYVECELMARROW_H
#define _EASYVECELMARROW_H _EASYVECELMARROW_H 

#include <string>

using namespace std;

/// An EasyVecFigure arrow base class  - used for polyarrow and box
class EasyVecArrow {
public:
  EasyVecArrow();
  /// Set the state of the forward arrow to new_state and return the old value.
  bool forwardArrow(bool new_state);
  /// Return the current state of the forward arrow.
  bool forwardArrow(void);
  /// Set the state of the backward arrow to new_state and return the old value.
  bool backwardArrow(bool new_state);
  /// Return the current state of the backward arrow.
  bool backwardArrow(void);

  /// Set the forward arrow type, value must be one of the values in arrowTypeType.
  bool forwardArrowType(int newArrowType);
  /// Return the forward arrow type.
  int forwardArrowType(void) { return elmArrowType[0]; }
  /// Set the backward arrow type, value must be one of the values in arrowTypeType.
  bool backwardArrowType(int newArrowType);
  /// Return the backward arrow type.
  int backwardArrowType(void) { return elmArrowType[1]; }
  
  /// Set the forward arrow style, value must be one of the values in arrowStyleType.
  bool forwardArrowStyle(int newForwardArrowStyle);
  /// Return the forward arrow style.
  int forwardArrowStyle(void) { return elmArrowStyle[0]; }
  /// Set the backward arrow style, value must be one of the values in arrowStyleType.
  bool backwardArrowStyle(int newBackwardArrowStyle);
  /// Return the backward arrow style.
  int backwardArrowStyle(void) { return elmArrowStyle[1]; }

  string forwardArrowString(void);
  string backwardArrowString(void);
  
  enum arrowTypeType {
    stick_type,
    closed_triangle,
    closed_indented_butt,
    closed_pointed_butt
  };
  enum arrowStyleType {
    hollow,
    filled
  };
  
  friend class EasyVecPolyline;

private:
  // array with length 2 - 0 is forward arrow, 1 is backward arrow
  // this makes internal code simpler (common functions which are just passed the index)
  bool elmArrow[2];
  int elmArrowType[2];
  int elmArrowStyle[2];  

  string arrowString(int arrowIndex);

};


#endif /* _EASYVECELMARROW_H */
