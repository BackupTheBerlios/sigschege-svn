// -*- c++ -*-
// TimSignal.h
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


#ifndef TIMSIGNAL_H_
#define TIMSIGNAL_H_

#include <QtGui>

#include "TimingScene.h"
#include "TimLayoutData.h"

class TimWave;
class TimLabel;

class TimSignal: public QGraphicsItem, public QGraphicsLayoutItem {

public:
	TimSignal(TimLayoutData *layout, QGraphicsItem *parent = 0);
	~TimSignal();

	virtual QRectF boundingRect() const;

	virtual void
			paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

	virtual void setGeometry(const QRectF & rect);

protected:
	virtual QSizeF sizeHint(Qt::SizeHint which, const QSizeF & constraint =
			QSizeF()) const;

	TimLabel *m_label;
	TimWave *m_wave;
	TimLayoutData *m_LayoutData;
};

#endif /* TIMSIGNAL_H_ */
