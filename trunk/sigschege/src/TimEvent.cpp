// -*- c++ -*-
// TimEvent.cpp
// Copyright 2009 by ingo
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


#include "TimEvent.h"
#include "SSGWriter.h"

TimEvent::TimEvent(double event, TimEventPainter *painter) {
  setEventPainter(painter);
  setEventTime(event);

  setSetupTime(0.0);
  setHoldTime(0.0);
}

TimEvent::TimEvent(double event, TimEventPainter *painter, double setup, double hold) {
  setEventPainter(painter);
  setEventTime(event);

  setSetupTime(setup);
  setHoldTime(hold);
}

TimEvent::~TimEvent() {

}

double TimEvent::getSetupTime() const {
  return m_setup_time;
}

void TimEvent::setSetupTime(double time) {
  m_setup_time = time;
}

double TimEvent::getHoldTime() const {
  return m_hold_time;
}

void TimEvent::setHoldTime(double time) {
  m_hold_time = time;
}

double TimEvent::getEventTime() const {
  return m_event_time;
}

void TimEvent::setEventTime(double time) {
  m_event_time = time;
}

TimEventPainter* TimEvent::getEventPainter() const {
  return m_event_painter;
}

void TimEvent::setEventPainter(TimEventPainter * painter) {
  m_event_painter = painter;
}

bool TimEvent::operator < (const TimEvent & rhs) const {
  return getAbsSetupTime() < rhs.getAbsSetupTime();
}

double TimEvent::getAbsSetupTime() const {
  return getEventTime() - getSetupTime();
}

double TimEvent::getAbsHoldTime() const {
  return getEventTime() + getHoldTime();
}
void TimEvent::SSGWrite(SSGWriter *writer) const {

  writer->writeStartElement("event");

  writer->writeStartElement("setup_time");
  writer->writeCharacters(QString::number(m_setup_time));
  writer->writeEndElement();

  writer->writeStartElement("hold_time");
  writer->writeCharacters(QString::number(m_hold_time));
  writer->writeEndElement();

  writer->writeStartElement("event_time");
  writer->writeCharacters(QString::number(m_event_time));
  writer->writeEndElement();

  m_event_painter->SSGWrite(writer);

  writer->writeEndElement();


  TimEventPainter  *m_event_painter;

}
