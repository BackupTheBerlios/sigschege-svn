// -*- c++ -*-
// \file 
// Copyright 2005 by Ulf Klaperski
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
  
  TimText(std::string text1 = "", std::string text2 = "");

  /// The standard destructor
  virtual ~TimText() {}
  
  /// Set a new Text
  void setText(std::string newText);
  void setText1(std::string newText1);
  void setText2(std::string newText2);

  std::string getText(void) { return cText1; }
  
  /// Set the Font Type
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
  std::string cText1;
  std::string cText2;
  int cFontType;
  int cFontSize;
  int cFontSize2;
};

#endif // _H_TIMTEXT
