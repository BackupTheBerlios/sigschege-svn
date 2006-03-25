// -*- c++ -*-
// \file 
// Copyright 2004, 2005, 2006 by Ingo Hinrichs, Ulf Klaperski
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

#ifndef _H_STATE
#define _H_STATE

#include <string>
#include <map>



class StateVisual {
public:

  enum visualType {
    Zero,
    One,
    X,
    Z
  };
  
  StateVisual(visualType visualization, bool showLabel);
  StateVisual() {
    cVisualization = X;
    cShowLabel = false;
  }

  visualType visualization() { return cVisualization; }
  bool showLabel() { return cShowLabel; }
  
private:
  visualType cVisualization;
  bool cShowLabel;
  
};
  
inline StateVisual::StateVisual(visualType visualization, bool showLabel) {
  cVisualization = visualization;
  cShowLabel = showLabel;
}

/// This class maps states, defined by strings, to visuals
class StateMap {
 public:

  StateMap(bool isBool = false);
  
  void setVisual(std::string value, StateVisual::visualType visual, bool showLabel);

  StateVisual& operator[](std::string state);
 private:
  std::map<std::string,StateVisual> visuals;
};
  
inline StateVisual& StateMap::operator[](std::string state) {
  return visuals[state];
}



#endif /* _H_STATE */
