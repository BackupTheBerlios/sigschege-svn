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


#ifndef _EASYVECELMTEXT_H
#define _EASYVECELMTEXT_H _EASYVECELMTEXT_H 

#include "EVPosInt.h"
#include "EasyVecElm.h"
#include "EasyVecCompound.h"
#include "EasyVecView.h"
#include <vector>
extern "C" {
#include <ft2build.h>
#include FT_FREETYPE_H
}

using namespace std;

/// An EasyVec text - corresponds to fig element text
class EasyVecText : public EasyVecElm {
public:
  EasyVecText();
  EasyVecText(EasyVecCompound* parent_compound, EasyVecFigure* figure_compound);
  /// Place the edges of the bounding box in upper_left/lower_right.
  virtual void getBoundingBox(EVPosInt &upper_left, EVPosInt &lower_right);
  /// Return the width of the text.
  int getWidth(void) { return text_width; }
  /// Return the height of the text.
  int getHeight(void) { return text_height; }
  vector<EasyVecElm*> flatList() { vector<EasyVecElm*> res; res.push_back(this); return (res); };
  virtual void draw(EasyVecView* view);
  virtual void saveElm(ofstream &fig_file);
  /// Set the text to be shown to new_text
  bool setText(const string &new_text);
  /// Set the font for the text
  bool setFont(int new_font);
  /// Set the size of the text in points.
  bool setSize(int new_size);
  /// Set the origin of the text in the figure.
  bool setOrigin(EVPosInt new_origin);
  /// Set the justification of the text relative to its origin.
  bool setJustification(int newJustification);
  static bool initFreetype(void); // will be called by EasyVecFigure class
  /// Switch the fig2dev_fontfix on/off. Must be true for xfig/transfig versions before 3.2.5, false otherwise.
  /*!
   * This fixes a bug concerning font sizes for transfig/fig2dev for versions before 3.2.5. Instead
   * of the default dpi size of 1200 a dpi value of 1080 was used just for text.
   */
  static void fig2dev_fontfix(bool needed) {
    fix_fig2dev_quirk = needed;
  };
  static bool fig2dev_fontfix(void) { return fix_fig2dev_quirk; }

  /// The justifications of text to its origin point.
  enum justification {
    left,
    center,
    right
  };

private:
  EVPosInt elm_origin;
  string elm_text;
  int elm_font, elm_size;
  justification elmJustification;
  static FT_Library  freetype_lib;
  static bool freetype_already_initialized;
  FT_Face face;
  int text_height, text_width; // cache information to reduce cpu effort
  
  bool initEasyVecText();
  void updateDimensions(); // must be called by all methods which change text size!

  // must be true for transfig<3.2.5 
  static bool fix_fig2dev_quirk;
  static string gs_fontpath;
};

inline bool EasyVecText::setJustification(int newJustification) {
  if (newJustification>0 && newJustification<3) {
    elmJustification = static_cast<justification>(newJustification);
    return true;
  } else return false;
}



#endif /* _EASYVECELMTEXT_H */

