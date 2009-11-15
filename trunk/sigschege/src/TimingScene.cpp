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
#include "TimScale.h"
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

void TimingScene::clear(void) {
  
  int cnt = m_layout->count();
  int index;
  QGraphicsLayoutItem *item;

  for (index = cnt-1; index >= 0; --index) {
    item = m_layout->itemAt(index);
    m_layout->removeAt(index);
    // then remove it from the scene
    removeItem(dynamic_cast<QGraphicsItem*>(item));
  }

  m_layout->setMaximumSize(0, 0); // adapt the size
  m_undoStack.clear();
}


TimSignal* TimingScene::addTimSignal() {

  return addTimSignal(new TimSignal(&m_LayoutData));
}

TimSignal* TimingScene::addTimSignal(TimSignal* signal) {

  // add signal to graphic scene
  addItem(signal);

  // add signal to layout manager
  m_layout->addItem(signal);  

  return signal;

}

TimSignal* TimingScene::addTimSignal(int index, TimSignal* signal) {

  // add signal to graphic scene
  addItem(signal);

  // add signal to layout manager
  m_layout->insertItem(index, signal);

  return signal;

}

int TimingScene::removeTimSignal(TimSignal *signal) {

  // First remove the signal from the layout

  // indexOf is missing in Qt < 4.6 :-(
  int cnt = m_layout->count();
  int index;
  for (index = 0; index < cnt; ++index) {
    if (signal == m_layout->itemAt(index)) {
      break;
    }
  }

  m_layout->removeItem(signal);
  m_layout->setMaximumSize(0, 0); // adapt the size

  // then remove it from the scene
  removeItem(signal);
  return index;
}


TimScale* TimingScene::addTimScale() {
  return addTimScale(new TimScale(&m_LayoutData));
}

TimScale* TimingScene::addTimScale(TimScale* timescale) {

  // add timescale to graphic scene
  addItem(timescale);

  // add timescale to layout manager
  m_layout->addItem(timescale);  

  return timescale;

}

TimScale* TimingScene::addTimScale(int index, TimScale* timescale) {

  // add timescale to graphic scene
  addItem(timescale);

  // add timescale to layout manager
  m_layout->insertItem(index, timescale);

  return timescale;

}

int TimingScene::removeTimScale(TimScale *timescale) {

  // First remove the timescale from the layout

  // indexOf is missing in Qt < 4.6 :-(
  int cnt = m_layout->count();
  int index;
  for (index = 0; index < cnt; ++index) {
    if (timescale == m_layout->itemAt(index)) {
      break;
    }
  }

  m_layout->removeItem(timescale);
  m_layout->setMaximumSize(0, 0); // adapt the size

  // then remove it from the scene
  removeItem(timescale);
  return index;
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
