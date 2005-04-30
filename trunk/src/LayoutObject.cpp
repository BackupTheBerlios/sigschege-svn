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

#include "LayoutObject.h"
#include <iostream>

LayoutObject::LayoutObject(): cReference(), cReferrers(), cCompound() {
  refCount = 0;
  cDrawBorder = false;
  cPadding    = 50;
  cOrigin.set(0,0);
}

LayoutObject::LayoutObject( Handle<LayoutObject> newReference ) {
  refCount = 0;
  cDrawBorder = false;
  cPadding    = 50;
  cOrigin.set(0,0);
  setReference(newReference);
}

LayoutObject::~LayoutObject() {
}

/*!
 * Set the Compound which is used to draw this Event.
 * \param newCompound The Compound to use.
 */
void LayoutObject::setCompound(YaVecCompound *newCompound) {
  cCompound = newCompound;
}

YaVecCompound* LayoutObject::getCompound() {
  return cCompound;
}

/*!
 * Paint this Layout Object
 */
void LayoutObject::paint(void) {
  // first we have to clear out compound
  getCompound()->clear();

  // and then we can draw out new stuff
  if(cDrawBorder){
    getCompound()->box(cOrigin, cOrigin+cSize);
  }
}


/*!
 * Set the Origin of this Layout Object
 * \param newOrigin The new Origin for this Layout Object
 */
void LayoutObject::setOrigin(YVPosInt newOrigin) {
  cOrigin = newOrigin;
}

/*!
 * Set the Origin of this Layout Object
 * \param x The new horizontal Origin for this Layout Object
 * \param y The new vertical Origin for this Layout Object
 */
void LayoutObject::setOrigin(int x, int y) {
  cOrigin.set(x,y);
}

/*!
 * Get the Origin of this Layout Object
 * \return The current origin of this Laout Object
 */
YVPosInt LayoutObject::getOrigin() {
  return(cOrigin);
}

/*!
 * Set the Size of this Layout Object
 * \param newSize The new Size for this Layout Object
 */
void LayoutObject::setSize(YVPosInt newSize) {
  cSize = newSize;
}

/*!
 * Set the Size of this Layout Object
 * \param width The new width for this Layout Object
 * \param height The new height for this Layout Object
 */
void LayoutObject::setSize(int width, int height) {
  cSize.set(width,height);
}

/*!
 * Get the Size of this Layout Object
 * \return The current Size of this Laout Object
 */
YVPosInt LayoutObject::getSize() {
  return(cSize);
}

void LayoutObject::setWidth(int width) {
  cSize.setx(width);
}

void LayoutObject::setHeight(int height) {
  cSize.sety(height);
}

/*!
 * Get the height of this Layout Object
 * This is importent for all container objects like lists
 * For these container objects the height of all sub objects
 * should be accumulated.
 * \return The total height of this Layout Object
 */
int LayoutObject::getHeight() {
  return(cSize.ypos());
}


int LayoutObject::getUpperPos() {
  return cOrigin.ypos();
}
int LayoutObject::getLeftPos() {
  return cOrigin.xpos();
}
int LayoutObject::getBottomPos() {
  return cOrigin.ypos()+cSize.ypos();
}
int LayoutObject::getRightPos() {
  return cOrigin.xpos()+cSize.xpos();
}

/*!
 * Enable/Disable the Border
 * \param enable true: Draw the Border; false: Don't draw the Border
 */
void LayoutObject::enableBorder(bool enable) {
  cDrawBorder = enable;
}

void LayoutObject::setPadding(int newPadding) {
  cPadding = newPadding;
}


bool LayoutObject::registerReferrer(Handle<LayoutObject> newReferrer) {
  vector< Handle<LayoutObject> >::iterator referrersIter;
    for ( referrersIter = cReferrers.begin(); referrersIter != cReferrers.end(); ++referrersIter ) {
      if (referrersIter->Object()==newReferrer.Object()) return false;
    }
    cReferrers.push_back(newReferrer);
    refCount++;
    return true;
}

bool LayoutObject::unregisterReferrer(Handle<LayoutObject> obsoleteReferrer) {
  vector< Handle<LayoutObject> >::iterator referrersIter;
    for ( referrersIter = cReferrers.begin(); referrersIter != cReferrers.end(); ++referrersIter ) {
      if (referrersIter->Object()==obsoleteReferrer.Object()) {
        cReferrers.erase(referrersIter);
        return true;
      }
    }
    refCount--;
    return false;
}

Handle<LayoutObject> LayoutObject::getReference() {
  return cReference;
}

bool LayoutObject::setReference(Handle<LayoutObject> new_reference) {
  LayoutObject* referenceWalk = new_reference.Object();
  // make sure that no circle of events is created which would lead to an infinite loop
  if (referenceWalk!=0) {
    do {
      if (referenceWalk==this) {
        return false;
      }
      referenceWalk = referenceWalk->cReference.Object();
    } while (referenceWalk);
  }
  
  if (cReference.Object()!=0) { // unregister from an old reference, if one existed
    cReference.Object()->unregisterReferrer(this);
  }
  cReference = new_reference;
  if (cReference.Object()!=0) { // make sure the event this refers to knows, unless it's a NULL pointer
    cReference.Object()->registerReferrer(this); 
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
