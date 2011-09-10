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


#ifndef _YAVECELMPOLYLINE_H
#define _YAVECELMPOLYLINE_H _YAVECELMPOLYLINE_H 

#include "YVPosInt.h"
#include "YaVecLine.h"
#include "YaVecArrow.h"
#include "YaVecElm.h"
#include "YaVecCompound.h"
#include "YaVecView.h"
#include <vector>

namespace YaVec {

  /// An FFigure polyline element - corresponds to fig element polyline (not box)
  class FPolyline : public YaVecElm, public YaVecLine, public YaVecArrow {
  public:
    /// General constructor with no extra arguments.
    FPolyline(FCompound* parent_compound, FFigure* figure_compound);
    /// Get the bounding box of this polyline.
    virtual void getBoundingBox(PosInt &upper_left, PosInt &lower_right);
    /// Add this point (given as PosInt).
    void addPoint(PosInt new_point);
    /// Add this point (given as integers).
    void addPoint(int x, int y) { this->addPoint(PosInt(x, y)); };
    /// Add a complete vector of  points (given as PosInt).
    void addPoints(std::vector<PosInt> new_points);
    /// Sets points for a box at a random angle
    void addAngleBox(PosInt corner1, PosInt corner2, double angle, bool clear=true);
    /// Collect all figure elements hierarchicallly as a flat list (just return myself).
    std::vector<YaVecElm*> flatList() { std::vector<YaVecElm*> res; res.push_back(this); return (res); };
    /// Draw the polyline to the given view.
    virtual void draw(FigView* view);
    virtual void saveElm(std::ofstream &fig_file);
    /// Print some (or some more) information about this figure element.
    virtual void debugPrint(std::ostream &dest, bool verbose, int depth);

    /// Return a list of significant points, which can be used for selection
    virtual void getPoints(std::vector<PosInt> &points, bool hierarchical, bool withCompounds);

  private:
    std::vector<PosInt> linePoints;
  };

}
  
#endif /* _YAVECELMPOLYLINE_H */

