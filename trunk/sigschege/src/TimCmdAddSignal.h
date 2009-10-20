// -*- c++ -*-
// TimCmdAddSignal.h
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

#ifndef TIMCMDADDSIGNAL_H_
#define TIMCMDADDSIGNAL_H_

#include <QtGui>
#include "TimingScene.h"
#include "TimSignal.h"

/** @brief @c TimCmdAddSignal class implements the AddSignal command.
 *
 * The @c TimCmdAddSignal class implements the Add Signal command. It supports undo and redo operations.
 *
 */
class TimCmdAddSignal : public QUndoCommand {

public:

  /** @brief CTOR
   *
   * Creates a new @c TimCmdAddSignal object.
   *
   * @param tscene Pointer to the scene where the signal should be added
   */
  TimCmdAddSignal(TimingScene *tscene);

  /** @brief DTOR
   * Destroys the @c TimCmdAddSignal object and every owning TimSignal object.
   */
  virtual ~TimCmdAddSignal();

  /** @brief Undo the command.
   *
   * Undo the addSignal command.
   *
   */
  virtual void undo();

  /** @brief Redo the command.
   *
   * Redo the addSignal command.
   */
  virtual void redo();

private:
  TimingScene *m_timingScene;
  TimSignal   *m_timSignal;
};

#endif /* TIMCMDADDSIGNAL_H_ */
