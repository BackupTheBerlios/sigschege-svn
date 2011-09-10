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


#ifndef _YAVECARC_H
#define _YAVECARC_H _YAVECARC_H 

#include "YVPosInt.h"
#include "YaVecLine.h"
#include "YaVecArrow.h"
#include "YaVecElm.h"
#include "YaVecCompound.h"
#include "YaVecView.h"
#include <vector>

namespace YaVec {

  /// An FFigure arc element - corresponds to fig element arc.
  class FArc : public YaVecElm, public YaVecLine, public YaVecArrow {
  public:
    /// General constructor which creates the object, from center, radius, angles.
    FArc(FCompound* parent_compound, FFigure* figure_compound, PosInt center,
             double radius, bool clockwise, double angle1, double angle3, bool isPieWedge=false);
    /// General constructor, which creates the arc from three points.
    FArc(FCompound* parent_compound, FFigure* figure_compound,
             PosInt p1, PosInt p2, PosInt p3, bool isPieWedge=false);
    virtual void getBoundingBox(PosInt &upper_left, PosInt &lower_right);

    /// Set point number num to the given position.
    void setPoint(int num, PosInt newPosition);
    /// Set all three points.
    void setPoints(PosInt newPoint1, PosInt newPoint2, PosInt newPoint3);
    /// Set arc geometry by center, radius, direction and angles.
    void setArc(PosInt center, double radius, bool clockwise, double angle1, double angle3);

    /// Collect all figure elements hierarchicallly as a flat list (just return myself).
    std::vector<YaVecElm*> flatList() { std::vector<YaVecElm*> res; res.push_back(this); return (res); };
    /// Draw the arc to the given view.
    virtual void draw(FigView* view);
    virtual void saveElm(std::ofstream &fig_file);
    /// Print some (or some more) information about this figure element.
    virtual void debugPrint(std::ostream &dest, bool verbose, int depth);

    /// Return a list of significant points, which can be used for selection
    virtual void getPoints(std::vector<PosInt> &points, bool hierarchical, bool withCompounds);
    /// find a figure element near the given position.
    virtual void getElmNearPos(PosInt pos, int fuzzyFact, bool hierarchical, bool withCompounds,
                               std::list<YaVecElmHit> &hits);

  private:
    PosInt elmPoint1, elmPoint2, elmPoint3;
    bool elmIsPieWedge;
    double elmXCenter, elmYCenter, elmRadius;
    bool elmClockwise;
    double elmPhi1, elmPhi2, elmPhi3;

    void computeArc(void);
  
  };

}
  
#endif /* _YAVECARC_H */

