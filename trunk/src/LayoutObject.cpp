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
// $Id:$

using namespace std;

#include "LayoutObject.h"
#include <iostream>

LayoutObject::LayoutObject() {
}
  
LayoutObject::~LayoutObject() {
}

/*!
 * Set the Compound which is used to draw this Event.
 * \param newCompound The Compound to use.
 */
void LayoutObject::setCompound(EasyVecCompound *newCompound) {
  evListCompound = newCompound;
}

/*!
 * Paint this Layout Object
 */
void LayoutObject::paint(void) {
  cout << "Paint" << endl;
}

bool LayoutObject::registerReferrer(Handle<LayoutObject> newReferrer) {
  vector< Handle<LayoutObject> >::iterator referrersIter;
    for ( referrersIter = referrers.begin(); referrersIter != referrers.end(); ++referrersIter ) {
      if (referrersIter->Object()==newReferrer.Object()) return false;
    }
    referrers.push_back(newReferrer);
    refCount++;
    return true;
}

bool LayoutObject::unregisterReferrer(Handle<LayoutObject> obsoleteReferrer) {
  vector< Handle<LayoutObject> >::iterator referrersIter;
    for ( referrersIter = referrers.begin(); referrersIter != referrers.end(); ++referrersIter ) {
      if (referrersIter->Object()==obsoleteReferrer.Object()) {
        referrers.erase(referrersIter);
        return true;
      }
    }
    refCount--;
    return false;
}

Handle<LayoutObject> LayoutObject::getReference() {
  return reference;
}

bool LayoutObject::setReference(Handle<LayoutObject> new_reference) {
  LayoutObject* referenceWalk = new_reference.Object();
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
  return true;
}

void LayoutObject::delReference() {
  setReference(NULL);
}

void LayoutObject::incrementRefcount() {
  refCount++; 
}

void LayoutObject::decrementRefcount() {
  refCount--;
}
