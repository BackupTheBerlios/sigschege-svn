// -*- c++ -*-
// \file 
// Copyright 2005 by Ulf Klaperski
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

#include "TimingObject.h"

using namespace YaVec;

TimingObject::TimingObject(LayoutObject *newReference, YaVec::PosInt origin,
		YaVec::PosInt size, int sigOffset, TimSchedule *schedulePtr) :
	LayoutObject(newReference, origin, size) {
	cSigOffset = sigOffset;
	cSchedulePtr = schedulePtr;
	updatetimArea();
}

void TimingObject::updatetimArea(void) {
	timXLeft = cOrigin.xpos() + cSigOffset + cPadding;
	timXRight = cOrigin.xpos() + cSize.xpos() - cPadding;
	timWidth = timXRight - timXLeft;
	timYTop = cOrigin.ypos() + cPadding;
	timYBottom = cOrigin.ypos() + cSize.ypos() - cPadding;
	timHeight = timYBottom - timYTop;
	labelXLeft = cOrigin.xpos() + cPadding;
	labelXRight = cOrigin.xpos() + cSigOffset - cPadding;
}

void TimingObject::setSigOffset(int sigOffset) {
	cSigOffset = sigOffset;
	updatetimArea();
}

void TimingObject::setSize(YaVec::PosInt newSize) {
	LayoutObject::setSize(newSize);
	updatetimArea();
}

void TimingObject::setWidth(int width) {
	LayoutObject::setWidth(width);
	updatetimArea();
}

void TimingObject::setHeight(int height) {
	LayoutObject::setHeight(height);
	updatetimArea();
}

void TimingObject::setOrigin(YaVec::PosInt newOrigin) {
	LayoutObject::setOrigin(newOrigin);
	updatetimArea();
}

void TimingObject::setPadding(int newPadding) {
	LayoutObject::setPadding(newPadding);
	updatetimArea();
}

void TimingObject::setSchedule(TimSchedule *schedulePtr) {
	cSchedulePtr = schedulePtr;
	updatetimArea();

}
