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


#ifndef _EASYVECCOMPOUND_H
#define _EASYVECCOMPOUND_H _EASYVECCOMPOUND_H 

class YaVecPolyline;
class YaVecBox;
class YaVecArc;
class YaVecText;

#include <vector>
#include "YVPosInt.h"
#include "YaVecElm.h"
using namespace std;

/// A class containing a fig compound

/*
 * This class implements a compound, which can contain graphical objects, including
 * other compounds. This allows hierarchical structuring of figures.
 *
 * Note that this class is also used as a base class for YaVecFigure, which implements a
 * complete figure. The reason for this is that the functionality is very similar,
 * actually the figure itself is like an invisible compound as it can contain several
 * graphical objects.
 */
class YaVecCompound : public YaVecElm {
public:
  /// Standard constructor - needed by derived YaVecFigure class
  YaVecCompound() {};
  /// General constructor which accepts the parent compound and the figure compound
  YaVecCompound(YaVecCompound* parent_compound, YaVecFigure* figure_compound)
    : YaVecElm(parent_compound, figure_compound) {};

  ~YaVecCompound() { clear(); };
  
  /// Create a polyline (class YaVecPolyline), points must be added later
  YaVecPolyline* polyline();
  /// Create an arc (class YaVecArc)
  YaVecArc* arc(YVPosInt p1, YVPosInt p2, YVPosInt p3);
  /// Create a box (class YaVecBox)
  YaVecBox* box(YVPosInt upper_left, YVPosInt lower_right);
  /// Create a text element (class YaVecText)
  YaVecText* text();
  /// Create a compound (class YaVecCompound)
  YaVecCompound* compound();
  /// remove the figure element, return true if element was found and deleted.
  bool remove(YaVecElm* elm);
  /// Determine the region that is covered by this compound
  virtual void getBoundingBox(YVPosInt &upper_left, YVPosInt &lower_right);
  /// return all elements of this compound as a flat list
  virtual vector<YaVecElm*> flatList();
  virtual void draw(YaVecView* view) {};
  virtual void handleChange(YaVecElm*);
  virtual void saveElm(ofstream &fig_file);
  /// Print some (or some more) information about this figure element.
  virtual void debugPrint(ostream &dest, bool verbose, int depth);
  void save_content(ofstream &fig_file);
  void copy_members(YaVecCompound& source);
  void clear(void);
  YaVecCompound& operator=(YaVecCompound& source);

  /// find a figure element near the given position.
  virtual void getElmNearPos(YVPosInt pos, int fuzzyFact, bool hierarchical, bool withCompounds,
                             list<YaVecElmHit> &hits);

protected:
  vector<YaVecElm*> members;
};

#endif /* _EASYVECCOMPOUND_H */

