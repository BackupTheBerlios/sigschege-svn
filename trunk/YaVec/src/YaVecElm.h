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


#ifndef _YAVECELM_H
#define _YAVECELM_H _YAVECELM_H

namespace YaVec {
  class FCompound;
  class FFigure;
}
#include <vector>
#include <list>
#include "YaVecUtil.h"
#include "YVPosInt.h"
#include "YaVecView.h"

namespace YaVec {

  class YaVecElm;

  /// Structure for element queries by position.
  struct YaVecElmHit {
    /// Pointer to the element.
    YaVecElm *elmP;
    /// Distance of the element to the given position.
    int distance;
    /// index: which part of the element was clicked (meaning depends on type of element).
    int idx;    
  };

  /// An YaVec Element - abstract base class for all YaVec elements (compound, polyline, text,...)
  class YaVecElm {
  public:
    // Constructor
    YaVecElm(void);
    // Constructor
    YaVecElm(FCompound* parent_compound, FFigure *figure_compound);
    // do we need a copy constructor?
    // destructor
    virtual ~YaVecElm();

    /// Return the bounding box in upper_left/lower_right
    /*!
     * The bounding box of an object is a rectangle defined by the points upper_left and
     * lower_right that is covered by the content of the object.
     */
    virtual void getBoundingBox(PosInt &upper_left, PosInt &lower_right)=0;
    /// Collect all figure elements hierarchicallly as a flat list.
    virtual std::vector<YaVecElm*> flatList() = 0;
    /// Draw this object in the given view.
    virtual void draw(FigView* view) = 0;
    /// Save this element into the given output file stream.
    virtual void saveElm(std::ofstream &fig_file) = 0;

    /// Print some (or some more) information about this figure element.
    virtual void debugPrint(std::ostream &dest, bool verbose, int depth) = 0;
  
    /// Return the pen color of this object.
    int penColor(void);
    /// Set the pen color of this object.
    bool penColor(int new_color);
    /// Return the fill color of this object.
    int fillColor(void);
    /// Set the fill color of this object.
    bool fillColor(int new_color);
    /// Return the area fill of this object.
    int areaFill(void);
    /// Set the fill color of this object.
    bool areaFill(int areaFill);  
    /// Return the depth (layer) of this object.
    int depth(void);
    /// Set the depth (layer) of this object.
    bool depth(int new_depth);
    /// Return the pen color as vector of 3 ints
    void getPenColorRGB(Array<int,3> &colorRGB);
    /// Return the actual fill color as vector of 3 ints.
    Array<int,3> actualFillColor(void);

    /// Return a list of significant points, which can be used for selection
    virtual void getPoints(std::vector<PosInt> &points, bool hierarchical, bool withCompounds) = 0;
  
    /// find a figure element near the given position.
    virtual void getElmNearPos(PosInt pos, int fuzzyFact, bool hierarchical, bool withCompounds,
                               std::list<YaVecElmHit> &hits);

    /// Check if the selected position is near the point.
    static bool checkProximity(PosInt selPos, PosInt point, int fuzzyFact, int &fuzzyRes);
    /// Return the scale factor (file res/screen res) for this figure.
    virtual int scale(void);
 
  protected:
    /// Needed to inform the owner about change events.
    FCompound *parent;
    /// Needed to access global picture states
    FFigure *figure;
    /// Color of the pen as fig color code.
    int elmPenColor;
    /// Fill color as fig color code.
    int elmFillColor;
    /// Fill style.
    int elmAreaFill;
    /// Depth (layer) of this element. 
    int elmDepth;
  };

  extern const int yavec_std_colors[][3];

  inline bool YaVecElm::penColor(int new_color) {
    if (new_color>=0 && new_color<512) {
      elmPenColor=new_color;
      return true;
    } else return false;
  }

  inline int YaVecElm::penColor(void) {
    return elmPenColor;
  }

  inline bool YaVecElm::fillColor(int new_color) {
    if (new_color>=0 && new_color<512) {
      elmFillColor=new_color;
      return true;
    } else return false;
  }

  inline int YaVecElm::fillColor(void) {
    return elmFillColor;
  }

  inline bool YaVecElm::areaFill(int areaFill) {
    if (areaFill>=-1 && areaFill<63) {
      elmAreaFill=areaFill;
      return true;
    } else return false;
  }

  inline int YaVecElm::areaFill(void) {
    return elmAreaFill;
  }

  inline bool YaVecElm::depth(int new_depth) {
    if (new_depth>=0 && new_depth<512) {
      elmDepth=new_depth;
      return true;
    } else return false;
  }

  inline int YaVecElm::depth(void) {
    return elmDepth;
  }

  inline void YaVecElm::getPenColorRGB(Array<int,3> &colorRGB) {
    colorRGB[0] = yavec_std_colors[elmPenColor][0];
    colorRGB[1] = yavec_std_colors[elmPenColor][1];
    colorRGB[2] = yavec_std_colors[elmPenColor][2];
  }

  
} // namespace
  
#endif /* _YAVECELM_H */

