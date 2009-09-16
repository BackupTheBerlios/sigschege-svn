// -*- c++ -*-
// TimEventHigh.h
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



#ifndef TIMEVENTHIGH_H_
#define TIMEVENTHIGH_H_

#include "TimEventType.h"

class TimEvent;

class TimEventHigh : public TimEventType {

public:
	TimEventHigh(TimEvent *parent = 0);

	virtual void paint(TimEvent *event, QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

};
#endif /* TIMEVENTHIGH_H_ */
