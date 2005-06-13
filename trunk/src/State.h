// -*- c++ -*-
// \file 
// Copyright 2004, 2005 by Ingo Hinrichs, Ulf Klaperski
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

//! Class that holds the state of a signal and maps it to drawing functions.
/*!
  A state can be a random string. Special values are "0" and "1", which are mapped
  to the drawing states Zero and One. All other states are mapped to X, which means
  draw both top and bottom lines.
 */
class State {
 public:

  //! The possible states which can be drawn: top line, bottom line and both lines.
  enum drawStateType {
    Zero,
    One,
    X,
    Z,
    Named,
    Illegal
  };

  //! General and standard constructor.
  State(drawStateType newDrawState=Zero, std::string newStateName="") {
    drawState = newDrawState;
    stateName = newStateName;
  };

  //! General constructor from string
  State(std::string stateString1, std::string stateString2="") {
    setStateByString(stateString1, stateString2);
  };

  
  //! Set the new state
  void setState(const drawStateType newDrawState=Zero, const std::string newStateName="") {
    drawState = newDrawState;
    stateName = newStateName;
  };

  //! Set the new state by two strings.
  bool setStateByString(const std::string &stateString1, const std::string &stateString2);

  //! Return the state to be drawn, will be Zero, One or X.
  drawStateType getDrawState(void);

  //! Return just the state name.
  std::string getStateName(void);
  
  //! Check if drawStateString is the draw state from this object.
  bool isDrawState(const std::string &drawStateString);

  //! Check if this state requires a top line to be drawn.
  bool hasTopLine(void) { return drawState==X || drawState==1 ||drawState == Named; }
  
  //! Check if this state requires a middle line to be drawn.
  bool hasMiddleLine(void) { return drawState==Z; }

  //! Check if this state requires a bottom line to be drawn.
  bool hasBottomLine(void) { return drawState==X || drawState==0 ||drawState == Named; }

  //! Check if drawStateChar is the draw state from this object.
  /*!
   * This function maps \c Named to \c X, since both are represented by top and bottom line.
   */
  bool isRealDrawState(char drawStateChar);


  //! Comparison for equality  between two states.
  bool operator==(const State otherState);
  
  //! Comparison for unequality  between two states.
  bool operator!=(const State otherState);
  
  //! Check if the draw state of this object is identical to the given one.
  bool operator==(const State::drawStateType state); 
  
 private:
  std::string stateName;
  drawStateType  drawState;

  drawStateType string2state(const std::string stateString);
  

};

inline std::ostream &operator<<(std::ostream& ostr, State outState) {
  //  ostr << outState.getstate();
  return ostr;
}

inline State::drawStateType State::getDrawState(void) {
  return drawState;
}

inline bool State::operator==(const State otherState) {
  return drawState==otherState.drawState && stateName==otherState.stateName;
}

inline bool State::operator!=(const State otherState) {
  return ! (*this==otherState);
}

inline bool State::operator==(const State::drawStateType state) {
  return state==drawState;
}


#endif /* _H_EVENTLIST */
