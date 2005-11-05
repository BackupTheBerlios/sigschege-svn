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

using namespace std;

#include "Event.h"
#include <stdio.h>


Event::Event(const State &setNewState, double setEventDelay, const Handle<Event> *setReference_p,
             double setSlopeTime) : refCount(0) {
  eventDelay = setEventDelay;
  newState = setNewState;
  refLevel = 50;
  if (setReference_p!=0) reference = *setReference_p;
  slopeTime = setSlopeTime;
  updateTime();
}


Event::~Event(){
}

void Event::incrementRefcount() {
  refCount++; 
}

void Event::decrementRefcount() {
  refCount--;
}

bool Event::registerReferrer(Handle<Event> &newReferrer) {
  vector< Handle<Event> >::iterator referrersIter;
    for ( referrersIter = referrers.begin(); referrersIter != referrers.end(); ++referrersIter ) {
      if (referrersIter->Object()==newReferrer.Object()) return false;
    }
    referrers.push_back(newReferrer);
    return true;
}

bool Event::unregisterReferrer(Handle<Event> &obsoleteReferrer) {
  vector< Handle<Event> >::iterator referrersIter;
    for ( referrersIter = referrers.begin(); referrersIter != referrers.end(); ++referrersIter ) {
      if (referrersIter->Object()==obsoleteReferrer.Object()) {
        referrers.erase(referrersIter);
        return true;
      }
    }
    return false;
}


Handle<Event> Event::getReference() {
  return reference;
}


bool Event::setReference(Handle<Event> &new_reference) {
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
  Handle<Event> thisEvent(this);
  if (reference.Object()!=0) { // unregister from an old reference, if one existed
    reference.Object()->unregisterReferrer(thisEvent);
  }
  reference = new_reference;
  if (reference.Object()!=0) { // make sure the event this refers to knows, unless it's a NULL pointer
    reference.Object()->registerReferrer(thisEvent); 
  }
  updateTime();
  return true;
}

void Event::delReference() {
  Handle<Event> event;
  setReference(event);
}


void Event::setDelay(double delay) {
  if(eventDelay != delay){
    eventDelay = delay;
  }
  updateTime();
}

double Event::getDelay() {
  return(eventDelay);
}


void Event::setSlope(double slope) {
  if(slopeTime != slope){
    slopeTime = slope;
  }
  updateTime();
}


double Event::getSlope() {
  return(slopeTime);
}

void Event::setRefLevel(int rlevel) {
  if(refLevel != rlevel){
    refLevel = rlevel;
  }
  updateTime();
}


int Event::getRefLevel() {
  return(refLevel);
}


void  Event::updateTime() {
  double oldTime;
  oldTime = eventTime;
  vector< Handle<Event> >::iterator referrersIter;

  // Calculate the new absolute Time of the Event
  if (reference.Object()!=0) {
    eventTime = reference.Object()->getTime()+eventDelay;
  } else {
    eventTime = eventDelay;
  }

  // update all referrers if the absolute Time has changed
  if (oldTime != eventTime) {
    for ( referrersIter = referrers.begin(); referrersIter != referrers.end(); ++referrersIter ) {
      referrersIter->Object()->updateTime();
    }
  }
}

double Event::getTime(int level_percent) {
  return(eventTime+slopeTime/100.0*level_percent);
}

double Event::getPercentAtTime(double time) {
  return(100.0*(eventTime+slopeTime-time)/slopeTime);
}
