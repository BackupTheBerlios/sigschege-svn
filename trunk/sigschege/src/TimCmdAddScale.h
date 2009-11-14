// -*- c++ -*-
// Copyright 2009 by ingo & ulf
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

#ifndef TIMCMDADDSCALE_H_
#define TIMCMDADDSCALE_H_

#include <QtGui>
#include "TimingScene.h"
#include "TimScale.h"

/** @brief @c TimCmdAddScale class implements the AddScale command.
 *
 * The @c TimCmdAddScale class implements the Add Scale command. It supports undo and redo operations.
 *
 */
class TimCmdAddScale : public QUndoCommand {

public:

  /** @brief CTOR
   *
   * Creates a new @c TimCmdAddScale object.
   *
   * @param tscene Pointer to the scene where the scale should be added
   */
  TimCmdAddScale(TimingScene *tscene);

  /** @brief DTOR
   * Destroys the @c TimCmdAddScale object and every owning TimScale object.
   */
  virtual ~TimCmdAddScale();

  /** @brief Undo the command.
   *
   * Undo the addScale command.
   *
   */
  virtual void undo();

  /** @brief Redo the command.
   *
   * Redo the addScale command.
   */
  virtual void redo();

private:
  TimingScene *m_timingScene;
  TimScale   *m_timScale;
  bool        m_owned;
};

#endif /* TIMCMDADDSCALE_H_ */
