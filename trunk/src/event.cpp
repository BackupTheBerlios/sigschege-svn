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

#include "event.h"
#include <stdio.h>

CEvent::CEvent():CObject(){
  EventDelay = 0;
  EventTime  = 0;
}

CEvent::~CEvent(){
}

void CEvent::pushChild(CEvent* newChild) {
  CObject::pushChild((CObject*) newChild);
}

void CEvent::insertChild(CEvent* newChild, size_t index) {
  CObject::insertChild((CObject*) newChild,index);
}

CEvent* CEvent::getChild(size_t index) {
  return((CEvent*) CObject::getChild(index));
}

CEvent* CEvent::getParent() {
  return((CEvent*) CObject::getParent());
}

void CEvent::setParent(CEvent* parent) {
  CObject::setParent((CObject*) parent);
  updateTime();
}

void CEvent::delParent() {
  CObject::delParent();
  updateTime();
}

void CEvent::setDelay(const float delay) {
  if(EventDelay != delay){
    EventDelay = delay;
    updateTime();
  }
}

const float CEvent::getDelay() {
  return(EventDelay);
}

void  CEvent::updateTime() {
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

const float CEvent::getTime() {
  return(EventTime);
}
