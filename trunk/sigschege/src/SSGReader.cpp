// -*- c++ -*-
// Copyright 2009 by Ulf Klaperski
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

#include "TimSignal.h"
#include "TimScale.h"
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
    TimScale *new_scale = new TimScale(0, scene);
    new_scale->setText(title);
    scene->addTimListItem(-1, new_scale);

    //scene->addTimTimeScale();
}
