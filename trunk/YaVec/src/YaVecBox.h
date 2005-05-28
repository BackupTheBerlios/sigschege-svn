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


#ifndef _YAVECBOX_H
#define _YAVECBOX_H _YAVECBOX_H 

#include "YVPosInt.h"
#include "YaVecLine.h"
#include "YaVecElm.h"
#include "YaVecCompound.h"
#include "YaVecView.h"
#include <vector>

namespace YaVec {

  /// An YaVec box element - corresponds to fig element polyline:box and polyline:arcbox
  class FBox : public YaVecElm, public YaVecLine  {
  public:
    /// general constructor with no extra arguments
    FBox(FCompound* parent_compound, FFigure* figure_compound)
      : YaVecElm(parent_compound, figure_compound) {};
    /// general constructor accepting corner points
    FBox(FCompound* parent_compound, FFigure* figure_compound, PosInt upper_left, PosInt lower_right);

    /// Return the limits of this element
    virtual void getBoundingBox(PosInt &upper_left, PosInt &lower_right) {
      upper_left  = elm_upper_left;
      lower_right = elm_lower_right;
    }
    /// set both corners of the box
    void set_corners(PosInt upper_left, PosInt lower_right) {
      upper_left  = elm_upper_left;
      lower_right = elm_lower_right;
    }
  
    /// Collect all figure elements hierarchicallly as a flat list (just return myself).
    std::vector<YaVecElm*> flatList() { std::vector<YaVecElm*> res; res.push_back(this); return (res); };

    /// Draw the box to the given view.
    virtual void draw(FigView* view);
    /// save element into a fig file
    virtual void saveElm(std::ofstream &fig_file);

    /// Return a list of significant points, which can be used for selection
    virtual void getPoints(std::vector<PosInt> &points, bool hierarchical, bool withCompounds);
    /// find a figure element near the given position.
    virtual void getElmNearPos(PosInt pos, int fuzzyFact, bool hierarchical, bool withCompounds,
                               std::list<YaVecElmHit> &hits);

    /// Print some (or some more) information about this figure element.
    virtual void debugPrint(std::ostream &dest, bool verbose, int depth);
    
  private:
    PosInt elm_upper_left, elm_lower_right;
  };

}
  
#endif /* _YAVECBOX_H */

