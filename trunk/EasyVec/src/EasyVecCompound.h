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

class EasyVecPolyline;
class EasyVecBox;
class EasyVecText;

#include <vector>
#include "EVPosInt.h"
#include "EasyVecElm.h"
using namespace std;

/// A class containing a fig compound

/*
 * This class implements a compound, which can contain graphical objects, including
 * other compounds. This allows hierarchical structuring of figures.
 *
 * Note that this class is also used as a base class for EasyVecFigure, which implements a
 * complete figure. The reason for this is that the functionality is very similar,
 * actually the figure itself is like an invisible compound as it can contain several
 * graphical objects.
 */
class EasyVecCompound : public EasyVecElm {
public:
  /// Standard constructor - needed by derived EasyVecFigure class
  EasyVecCompound() {};
  /// General constructor which accepts the parent compound and the figure compound
  EasyVecCompound(EasyVecCompound* parent_compound, EasyVecFigure* figure_compound)
    : EasyVecElm(parent_compound, figure_compound) {};

  ~EasyVecCompound() { clear(); };
  
  /// Create a polyline (class EasyVecPolyline), points must be added later
  EasyVecPolyline* polyline();
  /// Create a box (class EasyVecBox)
  EasyVecBox* box(EVPosInt upper_left, EVPosInt lower_right);
  /// Create a text element (class EasyVecText)
  EasyVecText* text();
  /// Create a compound (class EasyVecCompound)
  EasyVecCompound* compound();
  /// remove the figure element, return true if element was found and deleted.
  bool remove(EasyVecElm* elm);
  /// Determine the region that is covered by this compound
  virtual void getBoundingBox(EVPosInt &upper_left, EVPosInt &lower_right);
  /// return all elements of this compound as a flat list
  virtual vector<EasyVecElm*> flatList();
  virtual void draw(EasyVecView* view) {};
  virtual void handleChange(EasyVecElm*);
  virtual void saveElm(ofstream &fig_file);
  /// Print some (or some more) information about this figure element.
  virtual void debugPrint(ostream &dest, bool verbose, int depth);
  void save_content(ofstream &fig_file);
  void copy_members(EasyVecCompound& source);
  void clear(void);
  EasyVecCompound& operator=(EasyVecCompound& source);

protected:
  vector<EasyVecElm*> members;
};

#endif /* _EASYVECELMCOMPOUND_H */

