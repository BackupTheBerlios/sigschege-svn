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


#ifndef _EASYVECELMLINE_H
#define _EASYVECELMLINE_H _EASYVECELMLINE_H 

/// An EasyVecFigure polyline element - corresponds to fig element polyline (not box)
class EasyVecLine {
public:
  EasyVecLine();
  /// Set the line style for this polyline - allowed values are 0 - 5 
  bool lineStyle(int newLineStyle);
  /// Return the current line style.
  int lineStyle(void) { return elmLineStyle; }
  /// Set the style value for this polyline - multiples of 1/80 inch
  bool styleValue(double newStyleValue);
  /// Return the current style value.
  double styleValue(void) { return elmStyleValue; }

  enum lineStyleType {
    solid,
    dashed,
    dotted,
    dash_dotted,
    dash_double_dotted,
    dash_triple_dotted
  };

  friend class EasyVecPolyline;
  
private:
  int elmLineStyle;
  double elmStyleValue;
};


inline bool EasyVecLine::lineStyle(int newLineStyle) {
  if (newLineStyle>=0 && newLineStyle<=5) {
    elmLineStyle = newLineStyle;
    return true;
  } else {
    return false;
  }
}

inline bool EasyVecLine::styleValue(double newStyleValue) {
  if (newStyleValue>0.0) {
    elmStyleValue = newStyleValue;
    return true;
  } else {
    return false;
  }
}


#endif /* _EASYVECELMLINE_H */
