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


#ifndef _YAVECCOMPOUND_H
#define _YAVECCOMPOUND_H _YAVECCOMPOUND_H 

namespace YaVec {
  class FPolyline;
  class FBox;
  class FArc;
  class FText;
}

#include <vector>
#include "YVPosInt.h"
#include "YaVecElm.h"

namespace YaVec {

  /// A class containing a fig compound

  /*
   * This class implements a compound, which can contain graphical objects, including
   * other compounds. This allows hierarchical structuring of figures.
   *
   * Note that this class is also used as a base class for FFigure, which implements a
   * complete figure. The reason for this is that the functionality is very similar,
   * actually the figure itself is like an invisible compound as it can contain several
   * graphical objects.
   */
  class FCompound : public YaVecElm {
  public:
    /// Standard constructor - needed by derived FFigure class
    FCompound() {};
    /// General constructor which accepts the parent compound and the figure compound
    FCompound(FCompound* parent_compound, FFigure* figure_compound)
      : YaVecElm(parent_compound, figure_compound) {};

    ~FCompound() { clear(); };
  
    /// Create a polyline (class FPolyline), points must be added later
    FPolyline* polyline();
    /// Create an arc (class FArc), define it by 3 points on the arc.  
    FArc* arc(PosInt p1, PosInt p2, PosInt p3, bool isPieWedge=false);
    /// Create an arc (class FArc), define it by center, radius, direction and angles.
    FArc* arc(PosInt center, double radius, bool clockwise, double angle1, double angle3, bool isPieWedge=false);
    /// Create a box (class FBox)
    FBox* box(PosInt upper_left, PosInt lower_right);
    /// Create a text element (class FText)
    FText* text();
    /// Create a compound (class FCompound)
    FCompound* compound();
    /// remove the figure element, return true if element was found and deleted.
    bool remove(YaVecElm* elm);
    /// Determine the region that is covered by this compound
    virtual void getBoundingBox(PosInt &upper_left, PosInt &lower_right);
    /// return all elements of this compound as a flat list
    /// Collect all figure elements hierarchicallly as a flat list.
    virtual std::vector<YaVecElm*> flatList();
    /// Draw the content of this compound to the given view.
    virtual void draw(FigView* view) {};
    /// Used by elements of this compound to announce that they changed.
    virtual void handleChange(YaVecElm*);
    virtual void saveElm(std::ofstream &fig_file);
    /// Print some (or some more) information about this figure element.
    virtual void debugPrint(std::ostream &dest, bool verbose, int depth);
    /// Save the elements contained in this compound.
    void save_content(std::ofstream &fig_file);
    /// This function copies all member elements of another compound to this compound.
    void copy_members(FCompound& source);
    /// Delete all the elements in this compound.
    void clear(void);
    /// Standard assignment operator from an existing compound.
    FCompound& operator=(FCompound& source);

    /// Return a list of significant points, which can be used for selection
    virtual void getPoints(std::vector<PosInt> &points, bool hierarchical, bool withCompounds);

  protected:
    /// Elements of this compound, including other compounds.
    std::vector<YaVecElm*> members;
  };

}

#endif /* _YAVECCOMPOUND_H */

