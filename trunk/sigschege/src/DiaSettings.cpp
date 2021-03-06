// -*- c++ -*-
// Copyright 2009 by ulf
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


#include <QtGui>

#include "DiaSettings.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include "TimingScene.h"

//! [0]
DiaSettings::DiaSettings(QWidget *parent, TimingScene *scene)
  : QDialog(parent)
{

  setWindowTitle(tr("Document Properties"));
  m_scene = scene;

  TimeRangeGroupBox = new QGroupBox(tr("Time Range"));
  TimeRangeGroupBox->setCheckable(false);

  startTimeLabel = new QLabel(tr("Start Time"));

  startTimeEdit = new QDoubleSpinBox(TimeRangeGroupBox);
  startTimeEdit->setValue(scene->getLayoutData()->get_start_time());

  startTimeEdit->setDecimals(5);
  startTimeEdit->setMinimum(-100000.0);
  startTimeEdit->setMaximum(+100000.0);

  endTimeLabel = new QLabel(tr("End Time"));
    
  endTimeEdit = new QDoubleSpinBox(TimeRangeGroupBox);

  endTimeEdit->setDecimals(5);
  endTimeEdit->setMinimum(-100000.0);
  endTimeEdit->setMaximum(+100000.0);
  endTimeEdit->setValue(scene->getLayoutData()->get_end_time());

  snapDeltaTimeLabel = new QLabel(tr("Snap Distance"));

  snapDeltaTimeEdit = new QDoubleSpinBox(TimeRangeGroupBox);
  snapDeltaTimeEdit->setValue(scene->getLayoutData()->get_snap_delta_time());

  snapDeltaTimeEdit->setDecimals(5);
  snapDeltaTimeEdit->setMinimum(-100000.0);
  snapDeltaTimeEdit->setMaximum(+100000.0);

  buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
				   | QDialogButtonBox::Cancel);

  connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
  connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

  QGridLayout *layout = new QGridLayout;
  layout->addWidget(startTimeLabel, 0, 0);
  layout->addWidget(startTimeEdit, 0, 1);
  layout->addWidget(endTimeLabel, 1, 0);
  layout->addWidget(endTimeEdit, 1, 1);
  layout->addWidget(snapDeltaTimeLabel, 2, 0);
  layout->addWidget(snapDeltaTimeEdit, 2, 1);
  layout->addWidget(buttonBox,3, 0, 1, 2);
  TimeRangeGroupBox->setLayout(layout);

  connect(this, SIGNAL(accepted()), m_scene, SLOT(update()) );

  QGridLayout *mainLayout = new QGridLayout;
  mainLayout->addWidget(TimeRangeGroupBox, 0, 0);

  setLayout(mainLayout);
}

void DiaSettings::accept()  {
  m_scene->getLayoutData()->set_start_time(startTimeEdit->value());
  m_scene->getLayoutData()->set_end_time(endTimeEdit->value());
  m_scene->getLayoutData()->set_snap_delta_time(snapDeltaTimeEdit->value());
  m_scene->settingChange();
  QDialog::accept();
}

void DiaSettings::reject()  {
  QDialog::reject();
}
