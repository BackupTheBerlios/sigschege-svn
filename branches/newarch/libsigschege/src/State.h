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


/// The \c StateVisual class describes the visualization of a state.
/*!
 * The \c StateVisual class describes how a state is mapped to a visualization
 * in the timing diagram. This comprises the drawing of the line and if a label 
 * should be printed.
 */
  
class StateVisual {
public:

  /// The allowed visuals that can be drawn.
  /*!
   * The visuals that can be drawn are represented by the \c visualType.
   * Allowed values are Zero for bottom line, One for top line, X for top
   * and bottom line and Z for middle line. Note: Usually for bus values X
   * will be used.
   */
  enum visualType {
    Zero,
    One,
    X,
    Z
  };

  /// General constructor.
  StateVisual(visualType visualization, bool showLabel);

  /// Standard constructor.
  StateVisual() {
    cVisualization = X;
    cShowLabel = true;
  }

  /// Return the visualization of this State. 
  visualType visualization() { return cVisualization; }
  /// Return if a label should be drawn for this state.
  bool showLabel() { return cShowLabel; }
  
private:
  /// Visualization of this state.
  visualType cVisualization;
  /// If true, the state name should be drawn as a label. 
  bool cShowLabel;
  
};
  
inline StateVisual::StateVisual(visualType visualization, bool showLabel) {
  cVisualization = visualization;
  cShowLabel = showLabel;
}

/// This class maps states, defined by strings, to visuals.
/*
 * States are simply defined by a string. The state map stores a hash with the state
 * as the key and the corresponding \c StateVisual as the value. If a state is not
 * defined, the default visual is returned, which consists of the 'X' visual with the
 * value drawn as a label.
 */
class StateMap {
 public:

	/// TODO
  StateMap(bool isBool = false);
  
  /// TODO
  void setVisual(std::string value, StateVisual::visualType visual, bool showLabel);

  /// TODO
  StateVisual& operator[](std::string state);
 private:
  std::map<std::string,StateVisual> visuals;
};


inline StateVisual& StateMap::operator[](std::string state) {
  // note: this implementation causes each element that is accessed to be created
  // this is required for assignments to this operator to work - and it shouldn't be
  // a problem since not many values will occur in a realistic timing diagram.
  return visuals[state];
}



#endif /* _H_STATE */
