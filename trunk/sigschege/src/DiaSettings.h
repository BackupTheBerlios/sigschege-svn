
#ifndef FINDDIALOG_H
#define FINDDIALOG_H

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
