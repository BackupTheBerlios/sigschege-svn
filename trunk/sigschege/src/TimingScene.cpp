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

#include "TimUtil.h"
#include "TimingScene.h"
#include "TimMember.h"
#include "TimScale.h"
#include "TimSignal.h"
#include <cassert>
#include <iostream>
using namespace std;

TimingScene::TimingScene(QObject *parent) :
  QGraphicsScene(parent) {

  m_layout = new QGraphicsLinearLayout(Qt::Vertical);
  m_layout->setMinimumWidth(width());
  m_layout->setSpacing(5.0);

  updateRect();

  QGraphicsWidget *form = new QGraphicsWidget;
  form->setLayout(m_layout);
  addItem(form);

  m_signalManager = new TimSignalManager(this);
  m_posLine = 0;
}

void TimingScene::clear(void) {
  
  int cnt = 0;
  int index;
  QGraphicsLayoutItem *item;

  if (m_layout != 0) {
      cnt = m_layout->count();
    }

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

  return addTimSignal(new TimSignal(0, this));
}

TimSignal* TimingScene::addTimSignal(TimSignal* signal) {

  qDebug() << "addTS " << signal;
  // add signal to graphic scene
  addItem(signal);

  // add signal to layout manager
  m_layout->addItem(signal);  

  return signal;

}

TimSignal* TimingScene::addTimSignal(int index, TimSignal* signal) {

  qDebug() << "addTS " << signal << " @" << index;
  // add signal to graphic scene
  addItem(signal);

  // add signal to layout manager
  m_layout->insertItem(index, signal);

  return signal;

}

void TimingScene::addTimListItem(int index, TimMember *item) {

  qDebug() << "addTLI " << item << " @" << index;
  // add item to graphic scene
  addItem(item);

  // add item to layout manager
  m_layout->insertItem(index, item);
  
  updateRect();
}

int TimingScene::rmTimListItem(TimMember *item) {

  qDebug() << "rmTLI " << item;
  // indexOf is missing in Qt < 4.6 :-(
  int cnt = m_layout->count();
  int index;
  for (index = 0; index < cnt; ++index) {
    if (item == m_layout->itemAt(index)) {
      break;
    }
    assert(index<cnt);
  }

  // First remove the signal from the layout
  m_layout->removeItem(item);
  m_layout->setMaximumSize(0, 0); // adapt the size

  // then remove it from the scene
  removeItem(item);

  updateRect();

  return index;
}


int TimingScene::removeTimListItem(TimMember *item) {

  // indexOf is missing in Qt < 4.6 :-(
  int cnt = m_layout->count();
  int index;
  for (index = 0; index < cnt; ++index) {
    if (item == m_layout->itemAt(index)) {
      break;
    }
  }

  // First remove the signal from the layout
  m_layout->removeItem(item);
  m_layout->setMaximumSize(0, 0); // adapt the size

  // then remove it from the scene
  removeItem(item);
  update();
  return index;
}

TimLayoutData* TimingScene::getLayoutData() {
  return &m_LayoutData;
}

QGraphicsLinearLayout* TimingScene::getLayout() {
  return m_layout;
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

void TimingScene::beginMacro(const QString& text) {
  m_undoStack.beginMacro(text);
}

void TimingScene::endMacro() {
  m_undoStack.endMacro();
}

QAction* TimingScene::getActionArrow() {
  QAction *sigArrow = new QAction(tr("Select mode"), this);
  sigArrow->setCheckable(true);
  sigArrow->setChecked(true);
  sigArrow->setStatusTip(tr("Select mode"));
  connect(sigArrow, SIGNAL(toggled ( bool  )), m_signalManager, SLOT(selectNone(bool )));

  return sigArrow;
}

QAction* TimingScene::getActionSigH() {
  QAction *sigH = new QAction(tr("High signal"), this);
  sigH->setCheckable(true);
  sigH->setStatusTip(tr("High signal"));
  connect(sigH, SIGNAL(toggled ( bool  )), m_signalManager, SLOT(selectHigh(bool )));

  return sigH;
}

QAction* TimingScene::getActionSigL() {
  QAction *sigL = new QAction(tr("Low signal"), this);
  sigL->setCheckable(true);
  sigL->setStatusTip(tr("Low signal"));
  connect(sigL, SIGNAL(toggled ( bool  )), m_signalManager, SLOT(selectLow(bool )));

  return sigL;
}

QAction* TimingScene::getActionSigLH() {
  QAction *sigLH = new QAction(tr("Invert signal"), this);
  sigLH->setCheckable(true);
  sigLH->setStatusTip(tr("Invert signal"));
  connect(sigLH, SIGNAL(toggled ( bool  )), m_signalManager, SLOT(selectInvert(bool )));

  return sigLH;
}

QAction* TimingScene::getActionRemoveItems() {
  QAction *rmAct = new QAction(tr("Remove Item(s)"), this);
  rmAct->setEnabled(false);
  rmAct->setIcon(QIcon(":/images/rm.png"));
  rmAct->setStatusTip(tr("Removes one or more items(s) from the timing diagram"));
  connect(rmAct, SIGNAL(triggered()), this, SLOT(removeItems()));
  return rmAct;
}

void TimingScene::removeItems() {
  beginMacro("Delete Item(s)");
  QList<QGraphicsItem*> m_items = selectedItems();

  if(m_items.isEmpty()) {
    return;
  }

  for(QList<QGraphicsItem*>::Iterator it = m_items.begin(); it != m_items.end(); ++it) {
    TimMember *tm = (TimMember*)*it;
    if(tm != NULL) {
      QUndoCommand *cmd = tm->createDeleteCmd();
      if(cmd != NULL) {
        pushCmd(cmd);
      }
    }
  }

  endMacro();
}

void TimingScene::updateRect(void) {
  int cnt = m_layout->count();
  QGraphicsLayoutItem *item;
  int index;
  int height = 0;

  for (index = cnt-1; index >= 0; --index) {
    item = m_layout->itemAt(index);
    height += dynamic_cast<TimMember*>(item)->boundingRect().height() + m_layout->spacing();
  }

  if (height < 50) height = 50;

  setSceneRect(0, 0, m_LayoutData.get_col_0_width()
      + m_LayoutData.get_col_1_width() + 4, height);
}

void TimingScene::settingChange(void) {
  int cnt = m_layout->count();
  TimMember *item;
  int index;

  for (index = cnt-1; index >= 0; --index) {
    item = dynamic_cast<TimMember*>(m_layout->itemAt(index));
    item->timeRangeChange();
  }
  updateRect();
  invalidate();
 }

void TimingScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
  int cnt = m_layout->count();
  QGraphicsLayoutItem *item;
  int index;
  TimMember* curMember;
  TimMember* pointerVictim = 0;
  qreal time;

  for (index = cnt-1; index >= 0; --index) {
    item = m_layout->itemAt(index);
    curMember = dynamic_cast<TimMember*>(item);
    if (curMember->isUnderMouse())
      pointerVictim = curMember;
  }
  
  if (m_posLine != 0) {
    removeItem(m_posLine);
    m_posLine = 0;
  }
  if (pointerVictim) {
    Range<double> timeRange(m_LayoutData.get_start_time(), m_LayoutData.get_end_time());
    QPointF ppos = pointerVictim->mapFromScene( mouseEvent->scenePos());

    time = pointerVictim->calcSnapTime(ppos.x());

    qreal tpos = time / timeRange.distance() * m_LayoutData.get_col_1_width() + m_LayoutData.get_col_0_width()
      - pointerVictim->mapFromScene( QPointF(0.0,0.0)).x();

    if (timeRange.contains(time + m_LayoutData.get_start_time())) {
      QPen myPen = QPen(QColor(128,0,64,255.0*(1.0-0.7*fabs(pointerVictim->getSnapDeviation()))), 2);
      m_posLine = addLine(QLineF(QPointF(tpos,pointerVictim->y()), QPointF(tpos,pointerVictim->y()+pointerVictim->boundingRect().height())), myPen);
    }

  }
  
}
