// -*- c++ -*-
// TimSignalManger.cpp
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


#include "TimSignalManager.h"
#include "TimEvent.h"
#include "TimEventTool.h"
#include "TimEventToolHigh.h"
#include "TimEventToolLow.h"
#include "TimEventToolInvert.h"

TimSignalManager::TimSignalManager(QObject * parent) : QObject(parent) {

  p_high = new TimEventPainterHigh();
  p_low  = new TimEventPainterLow();

  m_current = NULL;
  m_high    = new TimEventToolHigh(p_high);
  m_low     = new TimEventToolLow(p_low);
  m_invert  = new TimEventToolInvert(p_high, p_low);

}

TimSignalManager::~TimSignalManager() {
  if(m_high)   delete m_high;
  if(m_low)    delete m_low;
  if(m_invert) delete m_invert;

  delete p_high;
  delete p_low;
}

TimEventTool* TimSignalManager::getCurrent() {
  return m_current;
}

void TimSignalManager::selectNone(bool checked) {
  if(checked)
    m_current = NULL;
}

void TimSignalManager::selectHigh(bool checked) {
  if(checked)
    m_current = m_high;
}

void TimSignalManager::selectLow(bool checked) {
  if(checked)
    m_current = m_low;
}

void TimSignalManager::selectInvert(bool checked) {
  if(checked)
    m_current = m_invert;
}

TimEventPainter * TimSignalManager::getTimEventPainter(const QString & name) {
  if(name == "low")
    return p_low;
  else if(name == "high")
    return p_high;

  qDebug() << name;
  return NULL;
}
