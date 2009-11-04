#include <QtGui>

#include "TimSignal.h"
#include "TimingScene.h"
#include "SSGReader.h"

SSGReader::SSGReader(TimingScene *tscene)
{

  scene = tscene;
}

bool SSGReader::read(QIODevice *device)
{
    setDevice(device);

    while (!atEnd()) {
      readNext();

      if (isStartElement()) {
	if (name() == "sigschege" && attributes().value("version") == "0.1")
	  readSigschege();
	else
	  raiseError(QObject::tr("The file is not a Sigschege version 0.1 file."));
      }
    }

    return !error();
}

void SSGReader::readSigschege()
{
    Q_ASSERT(isStartElement() && name() == "sigschege");

    while (!atEnd()) {
        readNext();

        if (isEndElement())
            break;

        if (isStartElement()) {
            if (name() == "signal")
                readSignal();
            else if (name() == "timescale")
                readTimeScale();
//            else
//              readUnknownElement();
        }
    }
}

void SSGReader::readSignal()
{
    Q_ASSERT(isStartElement() && name() == "signal");

    QString title = "";
    while (!atEnd()) {
        readNext();

        if (isEndElement())
            break;

        if (isStartElement()) {
            if (name() == "primarytext")
                title = readElementText();
	}
    }
    TimSignal *new_signal = scene->addTimSignal();
    new_signal->setText(title);
}

void SSGReader::readTimeScale()
{
    Q_ASSERT(isStartElement() && name() == "timescale");

    QString title = readElementText();
    //scene->addTimTimeScale();
}
