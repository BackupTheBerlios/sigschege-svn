// -*- c++ -*-
// \file 
// Copyright 2004 by Ingo Hinrichs
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

#include "Event.h"
#include <stdio.h>

Event::Event() {
  reference = 0;
  EventDelay = 0;
  EventTime  = 0;
}

Event::~Event(){
}

bool Event::registerReferrer(Event* newReferrer) {
  vector<Event*>::iterator referrersIter;
    for ( referrersIter = referrers.begin(); referrersIter != referrers.end(); ++referrersIter ) {
      if (*referrersIter==newReferrer) return false;
    }
    referrers.push_back(newReferrer);
    return true;
}

bool Event::unregisterReferrer(Event* obsoleteReferrer) {
  vector<Event*>::iterator referrersIter;
    for ( referrersIter = referrers.begin(); referrersIter != referrers.end(); ++referrersIter ) {
      if (*referrersIter==obsoleteReferrer) {
        referrers.erase(referrersIter);
        return true;
      }
    }
    return false;
}


Event* Event::getReference() {
  return reference;
}

void Event::setReference(Event* new_reference) {
  if (reference!=0) { // unregister from an old reference, if one existed
    reference->unregisterReferrer(this);
  }
  reference = new_reference;
  if (reference!=0) { // make sure the event this refers to knows, unless it's a NULL pointer
    reference->registerReferrer(this); 
  }
  updateTime();
}

void Event::delReference() {
  setReference(NULL);
}

void Event::setDelay(const double delay) {
  if(EventDelay != delay){
    EventDelay = delay;
  }
  updateTime();
}

const double Event::getDelay() {
  return(EventDelay);
}

void  Event::updateTime() {
  double oldTime;
  oldTime = EventTime;
  vector<Event*>::iterator referrersIter;

  // Calculate the new absolute Time of the Event
  if (reference!=0) {
    EventTime = reference->getTime()+EventDelay;
  } else {
    EventTime = EventDelay;
  }

  // update all referrers if the absolute Time has changed
  if(oldTime != EventTime) {
    for ( referrersIter = referrers.begin(); referrersIter != referrers.end(); ++referrersIter ) {
      (*referrersIter)->updateTime();
    }
  }
}

const double Event::getTime() {
  return(EventTime);
}
