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

class TimCmdAddSignal : public QUndoCommand {

public:

  TimCmdAddSignal(TimingScene *tscene);

  virtual void undo();

  virtual void redo();

private:
  TimingScene *m_timingScene;
  TimSignal   *m_timSignal;
};

#endif /* TIMCMDADDSIGNAL_H_ */