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


#include "EasyVecArrow.h"
#include <sstream>

EasyVecArrow::EasyVecArrow() {
  elmArrow[0] = elmArrow[1] = false;
  elmArrowType[0] = elmArrowType[1] = 0;
  elmArrowStyle[0] = elmArrowStyle[1] = 0;
}

bool EasyVecArrow::forwardArrow(bool new_state) {
  bool oldval = elmArrow[0];
  elmArrow[0] = new_state;
  return oldval;
}

bool EasyVecArrow::backwardArrow(bool new_state) {
  bool oldval = elmArrow[1];
  elmArrow[1] = new_state;
  return oldval;
}

bool EasyVecArrow::forwardArrow(void) {
  return elmArrow[0];
}

bool EasyVecArrow::backwardArrow(void) {
  return elmArrow[1];
}

bool EasyVecArrow::forwardArrowType(int newArrowType) {
  if ((newArrowType<0) or (newArrowType>3)) return false;
  elmArrowType[0] = newArrowType;
  return true;
}

bool EasyVecArrow::backwardArrowType(int newArrowType) {
  if ((newArrowType<0) or (newArrowType>3)) return false;
  elmArrowType[1] = newArrowType;
  return true;
}

bool EasyVecArrow::forwardArrowStyle(int newArrowStyle) {
  if ((newArrowStyle<0) or (newArrowStyle>1)) return false;
  elmArrowStyle[0] = newArrowStyle;
  return true;
}

bool EasyVecArrow::backwardArrowStyle(int newArrowStyle) {
  if ((newArrowStyle<0) or (newArrowStyle>1)) return false;
  elmArrowStyle[1] = newArrowStyle;
  return true;
}

string EasyVecArrow::arrowString(int arrowIndex) {
  ostringstream conv;
  conv << elmArrowType[arrowIndex] << " " << elmArrowStyle[arrowIndex] << " 1.00 60.00 120.00";
  return conv.str();
}

string EasyVecArrow::forwardArrowString(void) {
  return arrowString(0);
}

string EasyVecArrow::backwardArrowString(void) {
  return arrowString(1);
}
