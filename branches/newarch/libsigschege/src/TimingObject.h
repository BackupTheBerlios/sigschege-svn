// -*- c++ -*-
// \file 
// Copyright 2005, 2006 by Ulf Klaperski
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

#ifndef _H_TIMINGOBJECT
#define _H_TIMINGOBJECT

#include "LayoutObject.h"
#include "TimSchedule.h"

/// Base class for elements of a TimList.
/*!
 * This class provides common functionality for events of a TimList.
 */
class TimingObject: public LayoutObject {
public:
	/// Standard constructor.
	TimingObject();

	/// General constructor.
			TimingObject(LayoutObject *newReference, YaVec::PosInt origin,
					YaVec::PosInt size, int sigOffset = 0,
					TimSchedule *schedulePtr = 0);

	//! Set the horizontal offset for the signal part.
	virtual void setSigOffset(int sigOffset);

	//! Set the size of this timing object.
	virtual void setSize(YaVec::PosInt newSize);

	//! Set the width.
	virtual void setWidth(int width);

	//! Set the height.
	virtual void setHeight(int height);

	//! Set the Origin of this timing object
	virtual void setOrigin(YaVec::PosInt newOrigin);

	/// From LayoutObject -  adapt the content of this object.
	virtual void setPadding(int newPadding);

	/// TODO
	void setSchedule(TimSchedule *schedulePtr);

protected:
	/// pointer to the TimSchedule (managed by the TimList).
	TimSchedule *cSchedulePtr;
	/// Offset for the visible signal area.
	int cSigOffset;
	/// Horizontal geometry information for the timing area.
	int timXLeft;
	/// TODO
	int timXRight;
	/// TODO
	int timWidth;

	/// Vertical geometry information for the timing area.
	int timYTop;
	/// TODO
	int timYBottom;
	/// TODO
	int timHeight;

	/// Horizontal geometry information for the label area.
	int labelXLeft;
	/// TODO
	int labelXRight;

private:
	//! Update the geometry information for the timing area.
	void updatetimArea(void);
};

inline TimingObject::TimingObject() :
	LayoutObject(), cSigOffset(0) {
}

#endif // _H_TIMINGOBJECT
