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

#ifndef _H_TIMSIGNAL
#define _H_TIMSIGNAL

#include "TimingObject.h"
#include "TimText.h"
#include "EventList.h"
#include <string>

//! Signal Call
class TimSignal : public TimingObject, public EventList, public TimText {
public:
  //! The standard constructor
  TimSignal(double defaultSlope=0.0);

  //! Create a Signal with Text
  TimSignal(std::string signalLabel, double startTime, double endTime, YaVec::PosInt origin, YaVec::PosInt size,
            int sigOffset = 0, double defaultSlope=0.0);

  //! The standard destructor
  ~TimSignal();

  //! Paint the Signal.
  void paint(void);

  /// Function needed by the TimText base class to query the text area.
  virtual void getTextGeometry(YaVec::PosInt &upperLeft, YaVec::PosInt &lowerRight);

  // internal helper function: calculate the position from the state (0, 1, Z)
  int vertPosFromState(State::drawStateType state, State::drawStateType newState=State::Illegal, double percentageNew=0.0);

};

#endif
