// -*- c++ -*-
// \file 
// Copyright 2005, 2006 by Ulf Klaperski
//
// This file is part of Sigschege - Signal Schedule Generator
// 
// #############################################################################
//
// Sigschege is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2, or (at your option)
// any later version.
// 
// Sigschege is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with the Sigschege sources; see the file COPYING.  
//
// #############################################################################
//
// $Id$

#ifndef _H_TIMTEXT
#define _H_TIMTEXT

#include <string>
#include "YaVecCompound.h"


/// Text Class
/*!
 * This Text Class shows a text for signals or time scales.
 */

class TimText {
public:

  /*!The horizontal alignment of a text.
   * "follow" is meant for secondary text and makes
   * it just follow alignment of the primary text.
   */
  enum hAlignment {
    hcenter,
    left,
    right,
    follow
  };

  
  /// Constructor.
  TimText(std::string text1 = "", std::string text2 = "",
          hAlignment align1 = left, hAlignment align2 = follow);

  /// The standard destructor
  virtual ~TimText() {}
  
  /// Set a new Text.
  void setText(std::string newText);
  /// Set a new Text (same as setText).
  void setText1(std::string newText1);
  /// Set a new Text2 - if this is used two lines of text are shown.
  void setText2(std::string newText2);
  /// Set the alignment for text1.
  void setAlign1(hAlignment align);
  /// Set the alignment for text2.
  void setAlign2(hAlignment align);


  /// Return the currently active text.
  std::string getText(void) { return cText1; }
  
  /// Set the Font Type.
  void setFontType(int newFont) { cFontType = newFont; }

  /// Set the Font Size
  void setFontSize(int newSize) { cFontSize = newSize; }

  /// Set the size of the secondary font. 
  void setFontSize2(int newSize) { cFontSize2 = newSize; }

  /// paint the layout object
  void paint(YaVec::FCompound *cCompound);

  /// Function to be filled in by the derived class to query the text area.
  virtual void getTextGeometry(YaVec::PosInt &upperLeft, YaVec::PosInt &lowerRight) = 0;
  
protected:
  /// The text(s). If text2 is set, two lines of text are shown
  std::string cText1, cText2;
  /// The font type as defined by the fig format.
  int cFontType;
  /// The size of the (upper) text.
  int cFontSize;
  /// The size of the lower text.
  int cFontSize2;
  /// Alignment of text1.
  hAlignment cHAlign1;
  /// Alignment of text2.
  hAlignment cHAlign2;
};

inline void TimText::setAlign1(hAlignment align) {
  cHAlign1 = align;
}

inline void TimText::setAlign2(hAlignment align) {
  cHAlign2 = align;
}

#endif // _H_TIMTEXT
