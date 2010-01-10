// -*- c++ -*-
// TimCmdRmListItem.h
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



#ifndef TIMCMDRMLISTITEM_H_
#define TIMCMDRMLISTITEM_H_

#include <QtGui>

#include "TimingScene.h"
#include "TimMember.h"

/** @brief The @c TimCmdRmItem removes one item from the timing list.
 *
 * The @c TimCmdRmItem removes one item from the timing list. It supports undo and redo operations.
 *
 */
class TimCmdRmListItem: public QUndoCommand {

public:
  /** @brief CTor
   *
   * Creates a new @c TimCmdRmListItem object.
   *
   * @param scene Pointer to the scene where the signal should be added
   * @param item Pointer to the list item to delete
   */
  TimCmdRmListItem(TimingScene *tscene, TimMember *item);

  /** @brief DTor
   * Destroys the @c TimCmdRmListItem object and every owning item object.
   */
  virtual ~TimCmdRmListItem();

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
  TimingScene *m_timingScene;
  TimMember *m_item;
  int m_index;
  bool m_owning;
};


#endif /* TIMCMDRMLISTITEM_H_ */
