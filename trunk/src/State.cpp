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

using namespace std;

#include <State.h>

void StateMap::setVisual(string value, StateVisual::visualType visual, bool showLabel) {
  //cVisualization = visual;
  //cShowLabel = showLabel;

  visuals[value] = StateVisual(visual, showLabel);
}

StateMap::StateMap(bool isBool) : visuals() {

  if (isBool) {
      visuals[ "1" ] = StateVisual(StateVisual::One, false);
      visuals[ "0" ] = StateVisual(StateVisual::Zero, false);
      visuals[ "X" ] = StateVisual(StateVisual::X, false);
      visuals[ "Z" ] = StateVisual(StateVisual::Z, false);
    };
  
}


