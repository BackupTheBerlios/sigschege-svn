// -*- c++ -*-
// TimCmdRmEvent.h
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

#ifndef TIMCMDRMEVENT_H_
#define TIMCMDRMEVENT_H_

#include <QtGui>

#include "TimingScene.h"
#include "TimEvent.h"


/** @brief @c TimCmdRmEvent removes one item from the waveform.
 *
 * The @c TimCmdRmItem removes one item from the timing list. It supports undo and redo operations.
 *
 */
class TimCmdRmEvent : public QUndoCommand {
public:
  /** @brief CTor
   *
   * Creates a new @c TimCmdRmEvent object.
   *
   */
  TimCmdRmEvent(TimEvent *event);

  /** @brief DTor
   * Destroys the @c TimCmdRmEvent object and every item object which is owned as well.
   */
  virtual ~TimCmdRmEvent();

  /** @brief Undo the command.
   *
   * Undo the rmItem command.
   *
   */
  virtual void undo();

  /** @brief Redo the command.
   *
   * Redo the rmItem command.
   */
  virtual void redo();

private:
  TimEvent *m_event;
  TimEvent *m_prev;
  bool m_owning;
  bool m_first;
};

#endif /* TIMCMDRMEVENT_H_ */
