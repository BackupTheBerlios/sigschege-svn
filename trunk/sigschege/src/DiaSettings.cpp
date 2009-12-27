

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

  startTimeEdit = new QDoubleSpinBox(TimeRangeGroupBox);
  //startTimeEdit->setValue(0.0);
  startTimeEdit->setValue(scene->getLayoutData()->get_start_time());

  startTimeEdit->setDecimals(5);
  startTimeEdit->setMinimum(-100000.0);
  startTimeEdit->setMaximum(+100000.0);

  endTimeEdit = new QDoubleSpinBox(TimeRangeGroupBox);
//  endTimeEdit->setValue(100.0);
  endTimeEdit->setValue(scene->getLayoutData()->get_end_time());

  endTimeEdit->setDecimals(5);
  endTimeEdit->setMinimum(-100000.0);
  endTimeEdit->setMaximum(+100000.0);

  buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
				   | QDialogButtonBox::Cancel);

  connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
  connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(startTimeEdit);
  layout->addWidget(endTimeEdit);
  layout->addWidget(buttonBox);
  TimeRangeGroupBox->setLayout(layout);

  connect(this, SIGNAL(accepted()), );

  QGridLayout *mainLayout = new QGridLayout;
  mainLayout->addWidget(TimeRangeGroupBox, 0, 0);

  setLayout(mainLayout);
}

void DiaSettings::accept()  {
  m_scene->getLayoutData()->set_start_time(startTimeEdit->value());
  m_scene->getLayoutData()->set_end_time(endTimeEdit->value());
  QDialog::accept();
}

void DiaSettings::reject()  {
  QDialog::reject();
}
