// -*- c++ -*-
// \file 
// Copyright 2004 by Ingo Hinrichs, Ulf Klaperski
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

State::drawStateType State::string2state(const string stateString) {
  if (stateString=="0") {
    return Zero;
  } else if (stateString=="1") {
    return One;
  } else if (stateString=="Z") {
    return Z;
  } else if (stateString=="X") {
    return X;
  } else if (stateString=="Named") {
    return Named;
  } else {
    return Illegal;
  }
}

/*!
  Rules: If one string is given, it can be one of the simple state names (0,1,X,Z) or
  a bus value. If two strings are given, the first one must be a state name as a string
  ("Named" for the Named state, actually every unknown string is mapped to Named now)
  and the second contains the name.
 */
bool State::setStateByString(string stateString1, string stateString2) {
  drawStateType newDrawState = string2state(stateString1);
  string newStateName;
  
  if (stateString2=="") {
    if (newDrawState==Illegal) {
      newDrawState = Named;
      newStateName = stateString1;
    } else {
      newStateName = "";
    }
  } else {
    if (newDrawState==Illegal) {
      newDrawState = Named;
    }
    newStateName = stateString2;
  }
  drawState = newDrawState;
  stateName = newStateName;
  return true;
}

bool State::isDrawState(string drawStateString) {
  return string2state(drawStateString)==drawState;
}

