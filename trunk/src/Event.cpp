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
  EventDelay = 0;
  EventTime  = 0;
}

Event::~Event(){
}

void Event::incrementRefcount() {
  refCount++; 
}

void Event::decrementRefcount() {
  refCount--;
}

bool Event::registerReferrer(Handle<Event> newReferrer) {
  vector< Handle<Event> >::iterator referrersIter;
    for ( referrersIter = referrers.begin(); referrersIter != referrers.end(); ++referrersIter ) {
      if (referrersIter->Object()==newReferrer.Object()) return false;
    }
    referrers.push_back(newReferrer);
    refCount++;
    return true;
}

bool Event::unregisterReferrer(Handle<Event> obsoleteReferrer) {
  vector< Handle<Event> >::iterator referrersIter;
    for ( referrersIter = referrers.begin(); referrersIter != referrers.end(); ++referrersIter ) {
      if (referrersIter->Object()==obsoleteReferrer.Object()) {
        referrers.erase(referrersIter);
        return true;
      }
    }
    refCount--;
    return false;
}


Handle<Event> Event::getReference() {
  return reference;
}


bool Event::setReference(Handle<Event> new_reference) {
  Event* referenceWalk = new_reference.Object();
  // make sure that no circle of events is created which would lead to an infinite loop
  if (referenceWalk!=0) {
    do {
      if (referenceWalk==this) {
        return false;
      }
      referenceWalk = referenceWalk->reference.Object();
    } while (referenceWalk);
  }
  
  if (reference.Object()!=0) { // unregister from an old reference, if one existed
    reference.Object()->unregisterReferrer(this);
  }
  reference = new_reference;
  if (reference.Object()!=0) { // make sure the event this refers to knows, unless it's a NULL pointer
    reference.Object()->registerReferrer(this); 
  }
  updateTime();
  return true;
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
  vector< Handle<Event> >::iterator referrersIter;

  // Calculate the new absolute Time of the Event
  if (reference.Object()!=0) {
    EventTime = reference.Object()->getTime()+EventDelay;
  } else {
    EventTime = EventDelay;
  }

  // update all referrers if the absolute Time has changed
  if(oldTime != EventTime) {
    for ( referrersIter = referrers.begin(); referrersIter != referrers.end(); ++referrersIter ) {
      referrersIter->Object()->updateTime();
    }
  }
}

const double Event::getTime() {
  return(EventTime);
}
