// -*- c++ -*-
// TimEvent.h
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


#ifndef TIMEVENT_H_
#define TIMEVENT_H_

#include <QtGui>
#include "TimEventType.h"

class TimWave;

class TimEvent: public QGraphicsItem, public QGraphicsLayoutItem {

public:
	TimEvent(TimWave *parent);
	TimEvent(TimWave *parent, TimEventType *type);
	TimEvent(TimWave *parent, TimEventType *type, double time);

	~TimEvent();

	virtual void setEventType(TimEventType *type);
	virtual TimEventType* getEventType();
	TimWave* getWave();
	unsigned int calcXPos(double time);
	void insertEvent(TimEvent *node);

	virtual QRectF boundingRect() const;
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	virtual void setGeometry(const QRectF & rect);

	TimEvent* getNext();
	TimEvent* getPrev();

protected:
	void setNext(TimEvent *next);
	void setPrev(TimEvent *prev);
	virtual QSizeF sizeHint(Qt::SizeHint which, const QSizeF & constraint =	QSizeF()) const;

private:

	TimWave  *m_Wave;
	TimEvent *m_prev;
	TimEvent *m_next;

	TimEventType *m_EventType;

	double m_EventTime;
};

#endif /* TIMEVENT_H_ */
