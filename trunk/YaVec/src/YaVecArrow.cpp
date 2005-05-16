// -*- c++ -*-
// \file  
// Copyright 2005 by Ulf Klaperski
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


#include "YaVecArrow.h"
#include <sstream>

YaVecArrow::YaVecArrow() {
  elmArrows[0] = elmArrows[1] = 0;
}

YaVecArrow::~YaVecArrow() {
  if (elmArrows[0]!=0) delete elmArrows[0];
  if (elmArrows[1]!=0) delete elmArrows[1];
}


void YaVecArrow::forwardArrow(bool newState) {
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

void YaVecArrow::backwardArrow(bool newState) {
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

bool YaVecArrow::forwardArrow(void) {
  return elmArrows[0]!=0;
}

bool YaVecArrow::backwardArrow(void) {
  return elmArrows[1]!=0;
}

bool YaVecArrow::forwardArrowType(int newArrowType) {
  if ((newArrowType<0) or (newArrowType>3) or !forwardArrow()) return false;
  elmArrows[0]->Type = newArrowType;
  return true;
}

bool YaVecArrow::backwardArrowType(int newArrowType) {
  if ((newArrowType<0) or (newArrowType>3) or !backwardArrow()) return false;
  elmArrows[1]->Type = newArrowType;
  return true;
}

bool YaVecArrow::forwardArrowStyle(int newArrowStyle) {
  if ((newArrowStyle<0) or (newArrowStyle>1) or !forwardArrow()) return false;
  elmArrows[0]->Style = newArrowStyle;
  return true;
}

bool YaVecArrow::backwardArrowStyle(int newArrowStyle) {
  if ((newArrowStyle<0) or (newArrowStyle>1) or !backwardArrow()) return false;
  elmArrows[1]->Style = newArrowStyle;
  return true;
}

string YaVecArrow::arrowString(int arrowIndex) {
  ostringstream conv;
  conv << elmArrows[arrowIndex]->Type << " " << elmArrows[arrowIndex]->Style << " " << elmArrows[arrowIndex]->Thickness
       << " " << elmArrows[arrowIndex]->Width << " " <<  elmArrows[arrowIndex]->Height;
  return conv.str();
}

string YaVecArrow::forwardArrowString(void) {
  return arrowString(0);
}

string YaVecArrow::backwardArrowString(void) {
  return arrowString(1);
}

bool YaVecArrow::forwardArrowSize(double newThickness, double newWidth, double newHeight) {
  if (!forwardArrow()) return false;
  elmArrows[0]->Thickness = fabs(newThickness);
  elmArrows[0]->Width  = fabs(newWidth);
  elmArrows[0]->Height = fabs(newHeight);
  return true;
}

bool YaVecArrow::backwardArrowSize(double newThickness, double newWidth, double newHeight) {
  if (!backwardArrow()) return false;
  elmArrows[1]->Thickness = fabs(newThickness);
  elmArrows[1]->Width  = fabs(newWidth);
  elmArrows[1]->Height = fabs(newHeight);  
  return true;
}

void YaVecArrow::calcPoints(arrowInfo &arrow, const YVPosInt &tip, double tipAngle,
                                     YVPosInt &pLeft, YVPosInt &pRight, YVPosInt &pMid) {
  double arrAngle = atan(arrow.Width/arrow.Height);
  tipAngle += M_PI;
  double length = sqrt(arrow.Width*arrow.Width+arrow.Height*arrow.Height);
  pLeft  = tip+YVPosInt(static_cast<int>(length*cos(tipAngle+arrAngle)), static_cast<int>(length*sin(tipAngle+arrAngle)));
  pRight = tip+YVPosInt(static_cast<int>(length*cos(tipAngle-arrAngle)), static_cast<int>(length*sin(tipAngle-arrAngle)));
  if (arrow.Type==closed_indented_butt || arrow.Type==closed_pointed_butt) {
    length *= (arrow.Type==closed_indented_butt) ? 0.666 : 1.333; 
    pMid = tip + YVPosInt(static_cast<int>(length*cos(tipAngle)), static_cast<int>(length*sin(tipAngle)));
  }
}