// -*- c++ -*-
// \file  
// Copyright 2004 by Ulf Klaperski
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


#ifndef _YAVECLINE_H
#define _YAVECLINE_H _YAVECLINE_H 

namespace YaVec {

  /// An FFigure line base class  - used for polyline and box
  class YaVecLine {
  public:
    /// The standard constructor.
    YaVecLine();
    /// Set the line style for this polyline - allowed values are 0 - 5 
    bool lineStyle(int newLineStyle);
    /// Return the current line style.
    int lineStyle(void) { return elmLineStyle; }
    /// Set the style value for this polyline - multiples of 1/80 inch
    bool styleValue(double newStyleValue);
    /// Return the current style value.
    double styleValue(void) { return elmStyleValue; }
    /// Set the line thickness.
    void lineThickness(int newThickness) { elmThickness=newThickness; }
    /// Return the line thickness.
    int lineThickness(void) { return elmThickness; }

    /// The available line styles as defined in the fig format (3.2)
    enum lineStyleType {
      solid,
      dashed,
      dotted,
      dash_dotted,
      dash_double_dotted,
      dash_triple_dotted
    };

  
  protected:
    /// The line style (as defined by fig format).
    int elmLineStyle;
    /// The line style value (length of lines, as defined by fig format).
    double elmStyleValue;
    /// Thickness of line, as defined by fig format.
    int elmThickness;
  };


  inline bool YaVecLine::lineStyle(int newLineStyle) {
    if (newLineStyle>=0 && newLineStyle<=5) {
      elmLineStyle = newLineStyle;
      return true;
    } else {
      return false;
    }
  }

  inline bool YaVecLine::styleValue(double newStyleValue) {
    if (newStyleValue>0.0) {
      elmStyleValue = newStyleValue;
      return true;
    } else {
      return false;
    }
  }

}

#endif /* _YAVECLINE_H */
