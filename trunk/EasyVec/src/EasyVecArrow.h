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


#ifndef _EASYVECARROW_H
#define _EASYVECARROW_H _EASYVECARROW_H 

#include <string>
#include "EVPosInt.h"

using namespace std;

/// An EasyVecFigure arrow base class  - used for polyarrow and box
class EasyVecArrow {
public:

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

  struct arrowInfo {
    int Type;
    int Style;
    double Thickness;
    double Width;
    double Height;
  };

  EasyVecArrow();
  ~EasyVecArrow();
  /// Set the state of the forward arrow to new_state.
  void forwardArrow(bool new_state);
  /// Return the current state of the forward arrow.
  bool forwardArrow(void);
  /// Set the state of the backward arrow to new_state.
  void backwardArrow(bool new_state);
  /// Return the current state of the backward arrow.
  bool backwardArrow(void);

  /// Set the forward arrow type, value must be one of the values in arrowTypeType.
  bool forwardArrowType(int newArrowType);
  /// Return the forward arrow type.
  int forwardArrowType(void);
  /// Set the backward arrow type, value must be one of the values in arrowTypeType.
  bool backwardArrowType(int newArrowType);
  /// Return the backward arrow type.
  int backwardArrowType(void);
  
  /// Set the forward arrow style, value must be one of the values in arrowStyleType.
  bool forwardArrowStyle(int newForwardArrowStyle);
  /// Return the forward arrow style.
  int forwardArrowStyle(void);
  /// Set the backward arrow style, value must be one of the values in arrowStyleType.
  bool backwardArrowStyle(int newBackwardArrowStyle);
  /// Return the backward arrow style.
  int backwardArrowStyle(void);

  /// Set the size of the forward arrow.
  bool forwardArrowSize(double newThickness, double newWidth, double newHeight);
  /// Return the thickness of the forward arrow. 
  double forwardArrowThickness(void);
  /// Return the width of the forward arrow. 
  double forwardArrowWidth(void);
  /// Return the height of the forward arrow. 
  double forwardArrowHeight(void);

  /// Set the size of the backward arrow.
  bool backwardArrowSize(double newThickness, double newWidth, double newHeight);
  /// Return the thickness of the backward arrow. 
  double backwardArrowThickness(void);
  /// Return the width of the backward arrow. 
  double backwardArrowWidth(void);
  /// Return the height of the backward arrow. 
  double backwardArrowHeight(void);

  /// Return the string to be inserted into fig file for a forward arrow.
  string forwardArrowString(void);
  /// Return the string to be inserted into fig file for a backward arrow.
  string backwardArrowString(void);

  static void calcPoints(arrowInfo &arrow, const EVPosInt &tip, double tipAngle, 
                         EVPosInt &pLeft, EVPosInt &pRight, EVPosInt &pMid);
  
  friend class EasyVecPolyline;
  
private:
  // array with length 2 - 0 is forward arrow, 1 is backward arrow
  // this makes internal code simpler (common functions which are just passed the index)
  // TODO (CPUOPT): Cache angle
  arrowInfo *elmArrows[2];

  
  string arrowString(int arrowIndex);

};

inline int EasyVecArrow::forwardArrowType(void) {
  return forwardArrow() ? elmArrows[0]->Type : -1;
}

inline int EasyVecArrow::backwardArrowType(void) {
  return backwardArrow() ? elmArrows[1]->Type : -1;
}

inline int EasyVecArrow::forwardArrowStyle(void) {
  return forwardArrow() ? elmArrows[0]->Style : -1;
}

inline int EasyVecArrow::backwardArrowStyle(void) {
  return backwardArrow() ? elmArrows[1]->Style : -1;
}

inline double EasyVecArrow::forwardArrowThickness(void) {
  return forwardArrow() ? elmArrows[0]->Thickness : -1.0;
}

inline double EasyVecArrow::backwardArrowThickness(void) {
  return backwardArrow() ? elmArrows[1]->Thickness : -1.0;
}

inline double EasyVecArrow::forwardArrowWidth(void) {
  return forwardArrow() ? elmArrows[0]->Width : -1.0;
}

inline double EasyVecArrow::backwardArrowWidth(void) {
  return backwardArrow() ? elmArrows[1]->Width : -1.0;
}

inline double EasyVecArrow::forwardArrowHeight(void) {
  return forwardArrow() ? elmArrows[0]->Height : -1.0;
}

inline double EasyVecArrow::backwardArrowHeight(void) {
  return backwardArrow() ? elmArrows[1]->Height : -1.0;
}


#endif /* _EASYVECARROW_H */
