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
  elmArrows[0] = elmArrows[1] = 0;
}

EasyVecArrow::~EasyVecArrow() {
  if (elmArrows[0]!=0) delete elmArrows[0];
  if (elmArrows[1]!=0) delete elmArrows[1];
}


void EasyVecArrow::forwardArrow(bool newState) {
  bool oldState = (elmArrows[0]!=0);
  if (oldState==newState) return;
  if (newState) {
    elmArrows[0] = new arrowInfo;
    elmArrows[0]->Type  = 0;
    elmArrows[0]->Style = 0;
    elmArrows[0]->Thickness = 1.0;
    elmArrows[0]->Width  = 60.0;
    elmArrows[0]->Height = 120.0;
  } else {
    delete elmArrows[0];
    elmArrows[0] = 0;
  }
}

void EasyVecArrow::backwardArrow(bool newState) {
  bool oldState = (elmArrows[1]!=0);
  if (oldState==newState) return;
  if (newState) {
    elmArrows[1] = new arrowInfo;
    elmArrows[1]->Type  = 0;
    elmArrows[1]->Style = 0;
    elmArrows[1]->Thickness = 1.0;
    elmArrows[1]->Width  = 60.0;
    elmArrows[1]->Height = 120.0;
  } else {
    delete elmArrows[1];
    elmArrows[1] = 0;
  }
}

bool EasyVecArrow::forwardArrow(void) {
  return elmArrows[0]!=0;
}

bool EasyVecArrow::backwardArrow(void) {
  return elmArrows[1]!=0;
}

bool EasyVecArrow::forwardArrowType(int newArrowType) {
  if ((newArrowType<0) or (newArrowType>3) or !forwardArrow()) return false;
  elmArrows[0]->Type = newArrowType;
  return true;
}

bool EasyVecArrow::backwardArrowType(int newArrowType) {
  if ((newArrowType<0) or (newArrowType>3) or !backwardArrow()) return false;
  elmArrows[1]->Type = newArrowType;
  return true;
}

bool EasyVecArrow::forwardArrowStyle(int newArrowStyle) {
  if ((newArrowStyle<0) or (newArrowStyle>1) or !forwardArrow()) return false;
  elmArrows[0]->Style = newArrowStyle;
  return true;
}

bool EasyVecArrow::backwardArrowStyle(int newArrowStyle) {
  if ((newArrowStyle<0) or (newArrowStyle>1) or !backwardArrow()) return false;
  elmArrows[1]->Style = newArrowStyle;
  return true;
}

string EasyVecArrow::arrowString(int arrowIndex) {
  ostringstream conv;
  conv << elmArrows[arrowIndex]->Type << " " << elmArrows[arrowIndex]->Style << " " << elmArrows[arrowIndex]->Thickness
       << " " << elmArrows[arrowIndex]->Width << " " <<  elmArrows[arrowIndex]->Height;
  return conv.str();
}

string EasyVecArrow::forwardArrowString(void) {
  return arrowString(0);
}

string EasyVecArrow::backwardArrowString(void) {
  return arrowString(1);
}

bool EasyVecArrow::forwardArrowSize(double newThickness, double newWidth, double newHeight) {
  if (!forwardArrow()) return false;
  elmArrows[0]->Thickness = fabs(newThickness);
  elmArrows[0]->Width  = fabs(newWidth);
  elmArrows[0]->Height = fabs(newHeight);
  return true;
}

bool EasyVecArrow::backwardArrowSize(double newThickness, double newWidth, double newHeight) {
  if (!backwardArrow()) return false;
  elmArrows[1]->Thickness = fabs(newThickness);
  elmArrows[1]->Width  = fabs(newWidth);
  elmArrows[1]->Height = fabs(newHeight);  
  return true;
}

void EasyVecArrow::calcPoints(arrowInfo &arrow, const EVPosInt &tip, double tipAngle,
                                     EVPosInt &pLeft, EVPosInt &pRight, EVPosInt &pMid) {
  double arrAngle = atan(arrow.Width/arrow.Height);
  tipAngle += M_PI;
  double length = sqrt(arrow.Width*arrow.Width+arrow.Height*arrow.Height);
  pLeft  = tip+EVPosInt(static_cast<int>(length*cos(tipAngle+arrAngle)), static_cast<int>(length*sin(tipAngle+arrAngle)));
  pRight = tip+EVPosInt(static_cast<int>(length*cos(tipAngle-arrAngle)), static_cast<int>(length*sin(tipAngle-arrAngle)));
  if (arrow.Type==closed_indented_butt || arrow.Type==closed_pointed_butt) {
    length *= (arrow.Type==closed_indented_butt) ? 0.666 : 1.333; 
    pMid = tip + EVPosInt(static_cast<int>(length*cos(tipAngle)), static_cast<int>(length*sin(tipAngle)));
  }
}
