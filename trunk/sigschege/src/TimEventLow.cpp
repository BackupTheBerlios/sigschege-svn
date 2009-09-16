// -*- c++ -*-
// TimEventLow.cpp
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

#include "TimEventLow.h"
#include "TimEvent.h"
#include "TimWave.h"

TimEventLow::TimEventLow(TimEvent *parent) : TimEventType(parent) {
	setLevel(Low);
}

void TimEventLow::paint(TimEvent *event, QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

	// draw edge
	if(m_parent->getPrev() != NULL) {
		EventLevel level = m_parent->getPrev()->getEventType()->getLevel();
		switch(level) {
		case(High):
			painter->drawLine(0, 15, 0, 35);
			break;
		}
	}

	// draw signal
	unsigned int signal_length;
	if(m_parent->getNext() == NULL) {
		signal_length= m_parent->getWave()->getLayoutData()->get_col_1_width() - m_parent->pos().x();
	} else {
		signal_length= m_parent->getNext()->pos().x()-1;
	}

	painter->drawLine(0, 35, signal_length, 35);
}

