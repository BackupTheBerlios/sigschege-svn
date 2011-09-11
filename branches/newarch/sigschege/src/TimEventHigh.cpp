// -*- c++ -*-
// TimEventHigh.cpp
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

#include "TimEventHigh.h"
#include "TimEvent.h"
#include "TimWave.h"

TimEventHigh::TimEventHigh(TimEvent *parent) :
  TimEventType(parent) {
  setLevel(High);
}

void TimEventHigh::paint(TimEvent *event, QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
// TODO
//  if (event->getPrev() != NULL) {
//    EventLevel level = event->getPrev()->getEventType()->getLevel();
//    switch (level) {
//    case (High):
//      painter->drawLine(0, 20, 0, 15);
//      break;
//    case (Low):
//      painter->drawLine(0, 35, 0, 15);
//      break;
//    }
//  }
//
//  // draw signal
//  unsigned int signal_length;
//  if (event->getNext() == NULL || event->getNext()->getTime()>event->getWave()->getLayoutData()->get_end_time()) {
//    signal_length = event->getWave()->getLayoutData()->get_col_1_width()
//        - event->pos().x();
//  } else {
//    signal_length = event->getNext()->x() - event->x();
//  }
//
//  QRectF rct(0, 0, signal_length, 50);
//
//  // painter->fillRect(rct, QColor(255,100,100,100)); // fill the whole boundary rect
//  painter->drawLine(0, 15, signal_length, 15);
}
