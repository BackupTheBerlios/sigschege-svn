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
// $Id: TimLabel.cpp 59 2004-11-14 21:32:23Z suupkopp $

using namespace std;

#include "TimSignal.h"
#include <EasyVecText.h>
#include <iostream>

/*!
 * Construct a Timing Diagram Signal Object
 */
TimSignal::TimSignal():LayoutObject() {
  cFontType  = 14;
  cFontSize  = 20;
  cSigOffset = 0;
}

/*!
 * Construct a Timing Diagram Signal Object with a Text Label
 * \param signalLabel Signal Label
 */
TimSignal::TimSignal(string signalLabel):LayoutObject() {
  cText      = signalLabel;
  cFontType  = 14;
  cFontSize  = 20;
  cSigOffset = 0;
}

TimSignal::~TimSignal() {

}

/*!
 * Set a new Text
 * \param newText the new text
 */
void TimSignal::setText(string newText) {
  cText = newText;
}

//! Set the xoffset for the signal
void TimSignal::setSigOffset(int sigOffset) {
  cSigOffset = sigOffset;
}

/*!
 * Paint this Signal object
 */
void TimSignal::paint(void) {
  EasyVecText *text;
  int height,width;

  // check if a compound is available
  if(getCompound()==0) return;

  // first we have to clear out compound
  getCompound()->clear();

  height = (getBottomPos()-getUpperPos())-2*cPadding;
  width  = (getRightPos()-getLeftPos())-2*cPadding;

  // Draw the border
  LayoutObject::paint();

  // Draw the Text
  text = getCompound()->text();
  text->setText(cText);
  text->setFont(cFontType);
  text->setSize(cFontSize);
  text->setOrigin(EVPosInt(getLeftPos()+cPadding,getBottomPos()-cPadding-((height-text->getHeight())/2)));

  cEventList.setCompound(getCompound()->compound(),getLeftPos()+cSigOffset+cPadding,getUpperPos()+cPadding,width-cSigOffset-cPadding,height,0,222.0);
  cEventList.paint();

}

/*!
 * This function creates a new Event.
 * \return A pointer to the new event.
 * \sa deleteEvent 
 */
Handle<Event> TimSignal::createEvent() {
  return cEventList.createEvent();
}

/*!
 * This function creates a new Event.
 * \param refEvent A Handle to the referenced event. If it is a 0 pointer the delay is the absolute time.
 * \param eventDelay The delay to the reference event, or the absolute time if there is no reference event.
 * \param eventNewState The new state created by the event.
 * \return A pointer to the new event.
 * \sa deleteEvent 
 */
Handle<Event> TimSignal::createEvent(const string &eventNewState, double eventDelay, const Handle<Event> *refEvent) {
  return cEventList.createEvent(eventNewState, eventDelay, refEvent);
}
  

/*! 
 * This function will destroy the given event 
 * \param obsoleteEvent A pointer to the Event.
 * \return False if Event did not exist in that list.
 */
bool TimSignal::deleteEvent(Handle<Event> obsoleteEvent) {
  return cEventList.deleteEvent(obsoleteEvent);
}
