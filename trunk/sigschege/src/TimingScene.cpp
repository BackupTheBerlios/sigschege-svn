// -*- c++ -*-
// TimingScene.cpp
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

#include "TimingScene.h"
#include "TimSignal.h"

TimingScene::TimingScene(QObject *parent) :
  QGraphicsScene(parent) {

  setSceneRect(0, 0, m_LayoutData.get_col_0_width()
      + m_LayoutData.get_col_1_width(), 100);

  m_layout = new QGraphicsLinearLayout(Qt::Vertical);
  m_layout->setMinimumWidth(width());

  QGraphicsWidget *form = new QGraphicsWidget;
  form->setLayout(m_layout);
  addItem(form);

}

TimSignal* TimingScene::addTimSignal() {

  // create the new signal
  TimSignal *ts1 = new TimSignal(&m_LayoutData);

  // add signal to graphic scene
  addItem(ts1);

  // add signal to layout manager
  m_layout->addItem(ts1);

  return ts1;
}

TimLayoutData* TimingScene::getLayoutData() {
  return &m_LayoutData;
}

void TimingScene::setLabelWidth(unsigned int width) {
  long scene_width = getLayoutData()->get_col_0_width()
      + getLayoutData()->get_col_1_width();

  if (width > scene_width) {
    width = scene_width;
  }
  getLayoutData()->set_col_0_width(width);
  setSceneWidth(scene_width);
}

void TimingScene::setSceneWidth(unsigned int width) {
  long w = (int) width - (int) getLayoutData()->get_col_0_width();
  if (w >= 0) {
    getLayoutData()->set_col_1_width(w);
  } else {
    getLayoutData()->set_col_1_width(0);
  }
  setSceneRect(0, 0, m_LayoutData.get_col_0_width()
      + m_LayoutData.get_col_1_width(), 100);
}

void TimingScene::setStartTime(double stime) {
  getLayoutData()->set_start_time(stime);
}

void TimingScene::setEndTime(double etime) {
  getLayoutData()->set_end_time(etime);
}

QAction* TimingScene::createRedoAction() {
  return m_undoStack.createRedoAction(this);
}

QAction* TimingScene::createUndoAction() {
  return m_undoStack.createUndoAction(this);
}

void TimingScene::pushCmd(QUndoCommand* cmd) {
  m_undoStack.push(cmd);
}
