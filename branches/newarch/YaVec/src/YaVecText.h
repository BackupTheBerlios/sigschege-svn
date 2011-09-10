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


#ifndef _YAVECELMTEXT_H
#define _YAVECELMTEXT_H _YAVECELMTEXT_H 

#include "YVPosInt.h"
#include "YaVecElm.h"
#include "YaVecCompound.h"
#include "YaVecView.h"
#include <vector>
extern "C" {
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H
}

namespace YaVec {

  /// An YaVec text - corresponds to fig element text
  class FText : public YaVecElm {
  public:
    FText(); // TODO: needed?
    /// Constructor.
    FText(FCompound* parent_compound, FFigure* figure_compound);
    /// Place the edges of the bounding box in upper_left/lower_right.
    virtual void getBoundingBox(PosInt &upper_left, PosInt &lower_right);
    /// Return the corner points of a box around the text.
    void getTextBox(PosInt &lowerLeft, PosInt &upperRight);
    /// Return the width of the text.
    int getWidth(void) { return textWidth; }
    /// Return the height of the text.
    int getHeight(void) { return textHeight; }
    /// Collect all figure elements hierarchicallly as a flat list (just return myself).
    std::vector<YaVecElm*> flatList() { std::vector<YaVecElm*> res; res.push_back(this); return (res); };
    /// Draw the text to the given view.
    virtual void draw(FigView* view);
    virtual void saveElm(std::ofstream &fig_file);
    /// Print some (or some more) information about this figure element.
    virtual void debugPrint(std::ostream &dest, bool verbose, int depth);
    /// Set the text to be shown to new_text
    bool setText(const std::string &new_text);
    /// Set the font for the text
    bool setFont(int new_font);
    /// Set the size of the text in points.
    bool setSize(int new_size);
    /// Set the origin of the text in the figure.
    bool setOrigin(PosInt new_origin);
    /// Set the justification of the text relative to its origin.
    bool setJustification(int newJustification);
    /// Set the angle of the text.
    bool setAngle(double angle);
    /// Draw the text into a view or calculate its dimensions.
    /*!
     * This function combines the actual drawing and the dimension calculations. Both share
     * similar code.
     * \param view The view to which the text should be drawn.
     * \param noUpdate Suppress updating of the cached text dimensions.
     * \return The new text dimensions.
     */
    PosInt drawOrCalc(FigView* view, bool noUpdate=false);
    /// Calculates the maximum point size so that the text fits into the given box.
    int sizeForBox(int height, int width, bool allowIncrease = false);
    /// Initialize Freetype library - will be called by FFigure class.
    static bool initFreetype(void); 
    /// Switch the fig2dev_fontfix on/off. Must be true for xfig/transfig versions before 3.2.5, false otherwise.
    /*!
     * This fixes a bug concerning font sizes for transfig/fig2dev for versions before 3.2.5. Instead
     * of the default dpi size of 1200 a dpi value of 1080 was used just for text.
     */
    static void fig2dev_fontfix(bool needed) {
      fix_fig2dev_quirk = needed;
    };
    /// Return the current setting of the fontfix feature.
    static bool fig2dev_fontfix(void) { return fix_fig2dev_quirk; }

    /// The justifications of text to its origin point.
    enum justification {
      left,
      center,
      right
    };

    /// Return a list of significant points, which can be used for selection
    virtual void getPoints(std::vector<PosInt> &points, bool hierarchical, bool withCompounds);

    /// Set this variable to true to use kerning. This is not recommended as transfig does not support it
    static bool use_kerning;

  private:
    PosInt elmOrigin;
    std::string elmText;
    int elmFont, elmSize;
    justification elmJustification;
    double cAngle;
  
    static FT_Library  freetype_lib;
    static bool freetype_already_initialized;
    FT_Face face;
    int textHeight, textWidth; // cache information to reduce cpu effort
  
    bool initFText();
    void updateDimensions(); // must be called by all methods which change text size!

    PosInt BBoxUpperleft;
    PosInt BBoxLowerRight;
  
    // must be true for transfig<3.2.5 
    static bool fix_fig2dev_quirk;
    static std::string gs_fontpath;
  };


  inline bool FText::setJustification(int newJustification) {
    if (newJustification>0 && newJustification<3) {
      elmJustification = static_cast<justification>(newJustification);
      return true;
    } else return false;
  }

  /// update the dimensions - calls draw without a view
  inline void FText::updateDimensions() {
    draw(NULL); 
  }

}


#endif /* _YAVECELMTEXT_H */

