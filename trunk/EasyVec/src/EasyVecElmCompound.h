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


#ifndef _EASYVECELMCOMPOUND_H
#define _EASYVECELMCOMPOUND_H _EASYVECELMCOMPOUND_H 

class EasyVecElmPolyline;
class EasyVecElmBox;
class EasyVecElmText;

#include <vector>
#include "EVPosInt.h"
#include "EasyVecElm.h"
using namespace std;

/// A class containing a fig compound

/*
 * This class implements a compound, which can contain graphical objects, including
 * other compounds. This allows hierarchical structuring of figures.
 *
 * Note that this class is also used as a base class for EasyVec, which implements a
 * complete figure. The reason for this is that the functionality is very similar,
 * actually the figure itself is like an invisible compound as it can contain several
 * graphical objects.
 */
class EasyVecElmCompound : public EasyVecElm {
public:
  /// Standard constructor - needed by derived EasyVec class
  EasyVecElmCompound() {};
  /// General constructor which accepts the parent compound and the figure compound
  EasyVecElmCompound(EasyVecElmCompound* parent_compound, EasyVec* figure_compound)
    : EasyVecElm(parent_compound, figure_compound) {};

  //virtual EasyVecElmCompound& operator=(const EasyVecElmCompound& right);
  
  /// Create a polyline (class EasyVecElmPolyline), points must be added later
  EasyVecElmPolyline* polyline();
  /// Create a box (class EasyVecElmBox)
  EasyVecElmBox* box(EVPosInt upper_left, EVPosInt lower_right);
  /// Create a text element (class EasyVecElmText)
  EasyVecElmText* text();
  /// Create a compound (class EasyVecElmCompound)
  EasyVecElmCompound* compound();
  /// Determine the region that is covered by this compound
  virtual void getBoundingBox(EVPosInt &upper_left, EVPosInt &lower_right);
  /// return all elements of this compound as a flat list
  virtual vector<EasyVecElm*> flatList();
  virtual void draw(EasyVecView* view) {};
  virtual void handle_change(EasyVecElm*);
  virtual void saveElm(ofstream &fig_file);
  void save_content(ofstream &fig_file);

  /// Return the type of an element - values are from enum EasyVecElm::Type
  virtual EasyVecElm::Type type(void) { return Compound; };

protected:
  vector<EasyVecElm*> members;
};

#endif /* _EASYVECELMCOMPOUND_H */

