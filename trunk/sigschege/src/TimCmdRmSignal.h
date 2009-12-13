// -*- c++ -*-
// TimCmdRmSignal.h
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


#ifndef TIMCMDRMSIGNAL_H_
#define TIMCMDRMSIGNAL_H_

#include <QtGui>
#include "TimingScene.h"
#include "TimMember.h"

/** @brief The @c TimCmdRmSignal implements the remove signal command
 *
 * The @c TimCmdRmSignal implements the remove signal command. It supports undo and redo operations.
 *
 */
class TimCmdRmSignal: public QUndoCommand {

public:
  /** @brief CTor
   *
   * Creates a new @c TimCmdRmSignal object.
   *
   * @param scene Pointer to Timingscene
   * @param item Pointer to the list item to delete
   */
  TimCmdRmSignal(TimingScene *scene, TimMember *item);

  /** @brief DTor
   * Destroys the @c TimCmdRmSignal object and every owning TimSignal object.
   */
  virtual ~TimCmdRmSignal();

  /** @brief Undo the command.
   *
   * Undo the rmSignal command.
   *
   */
  virtual void undo();

  /** @brief Redo the command.
   *
   * Redo the rmSignal command.
   */
  virtual void redo();

private:
  TimingScene *m_timingScene;
  TimMember *m_item;
  int m_index;
  bool m_owning;
};

#endif /* TIMCMDRMSIGNAL_H_ */
