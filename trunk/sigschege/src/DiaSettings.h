// -*- c++ -*-
// Copyright 2009-2010 by ulf
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


#ifndef DIASETTINGS_H_
#define DIASETTINGS_H_

#include <QDialog>

QT_BEGIN_NAMESPACE
class QGroupBox;
class QDialogButtonBox;
class QLabel;
class QLineEdit;
class QDoubleSpinBox;
class TimingScene;

QT_END_NAMESPACE

class DiaSettings : public QDialog
{
  Q_OBJECT
    
public:
  DiaSettings(QWidget *parent, TimingScene *scene);

protected slots:

  virtual void accept();
  virtual void reject();

private:

  QGroupBox *TimeRangeGroupBox;
  QLineEdit *unitsEdit;
  QDoubleSpinBox *startTimeEdit;
  QDoubleSpinBox *endTimeEdit;

  QDialogButtonBox *buttonBox;

  TimingScene *m_scene;


};


#endif
