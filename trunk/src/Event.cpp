// -*- c++ -*-
/// \file 
 
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
// $Id: $

using namespace std;

#include "Event.h"
#include <stdio.h>

Event::Event():Object(){
  EventDelay = 0;
  EventTime  = 0;
}

Event::~Event(){
}

void Event::pushChild(Event* newChild) {
  Object::pushChild((Object*) newChild);
}

void Event::insertChild(Event* newChild, size_t index) {
  Object::insertChild((Object*) newChild,index);
}

Event* Event::getChild(size_t index) {
  return((Event*) Object::getChild(index));
}

Event* Event::getParent() {
  return((Event*) Object::getParent());
}

void Event::setParent(Event* parent) {
  Object::setParent((Object*) parent);
  updateTime();
}

void Event::delParent() {
  Object::delParent();
  updateTime();
}

void Event::setDelay(const float delay) {
  if(EventDelay != delay){
    EventDelay = delay;
    updateTime();
  }
}

const float Event::getDelay() {
  return(EventDelay);
}

void  Event::updateTime() {
  float oldTime;
  oldTime = EventTime;

  // Calculate the new absolute Time of the Event
  if(hasParent()){
    EventTime = getParent()->getTime()+EventDelay;
  } else {
    EventTime = EventDelay;
  }

  // update all childs is the absolute Time has changed
  if(oldTime != EventTime){
    for(size_t walk=0; walk < getChildCount(); walk++){
      getChild(walk)->updateTime();
    }
  }
}

const float Event::getTime() {
  return(EventTime);
}
