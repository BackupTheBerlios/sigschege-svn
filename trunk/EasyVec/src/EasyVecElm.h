// -*- c++ -*-
// \file  
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
// $Id$


#ifndef _EASYVECELM_H
#define _EASYVECELM_H _EASYVECELM_H

class EasyVecCompound;

#include <vector>
#include "EVPosInt.h"
#include "EasyVecView.h"

using namespace std;


/// An EasyVec Element - abstract base class for all EasyVec elements (compound, polyline, text,...)
class EasyVecElm {
public:
  // constructor
  EasyVecElm(void);
  EasyVecElm(EasyVecCompound* parent_compound, EasyVecFigure *figure_compound);
  // do we need a copy constructor?
  // destructor
  virtual ~EasyVecElm();

  /// Return the bounding box in upper_left/lower_right
  /*!
   * The bounding box of an object is a rectangle defined by the points upper_left and
   * lower_right that is covered by the content of the object.
   */
  virtual void getBoundingBox(EVPosInt &upper_left, EVPosInt &lower_right)=0;
  virtual vector<EasyVecElm*> flatList() = 0;
  /// Draw this object in the given view.
  virtual void draw(EasyVecView* view) = 0;
  /// Save this element into the given output file stream.
  virtual void saveElm(ofstream &fig_file) = 0;

  /// Print some (or some more) information about this figure element.
  virtual void debugPrint(ostream &dest, bool verbose, int depth) = 0;
  
  /// Return the pen color of this object.
  int penColor(void);
  /// Set the pen color of this object.
  bool penColor(int new_color);
  /// Return the fill color of this object.
  int fillColor(void);
  /// Set the fill color of this object.
  bool fillColor(int new_color);
  /// Return the depth (layer) of this object.
  int depth(void);
  /// Set the depth (layer) of this object.
  bool depth(int new_depth);

protected:
  EasyVecCompound *parent; // needed to inform the owner about change events
  EasyVecFigure *figure; // needed to access global picture states
  int elmPenColor;
  int elmFillColor;
  int elmDepth;
};

inline bool EasyVecElm::penColor(int new_color) {
  if (new_color>=0 && new_color<512) {
    elmPenColor=new_color;
    return true;
  } else return false;
}

inline int EasyVecElm::penColor(void) {
  return elmPenColor;
}

inline bool EasyVecElm::fillColor(int new_color) {
  if (new_color>=0 && new_color<512) {
    elmFillColor=new_color;
    return true;
  } else return false;
}

inline int EasyVecElm::fillColor(void) {
  return elmFillColor;
}

inline bool EasyVecElm::depth(int new_depth) {
  if (new_depth>=0 && new_depth<512) {
    elmDepth=new_depth;
    return true;
  } else return false;
}

inline int EasyVecElm::depth(void) {
  return elmDepth;
}

extern const int easyvec_std_colors[][3];

#endif /* _EASYVECELM_H */

