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
#include <typeinfo>
#include <iostream>

#include "TimSignal.h"
#include "TimScale.h"
#include "TimingScene.h"
#include "SSGWriter.h"

using namespace std;

SSGWriter::SSGWriter(TimingScene *scene)
{

  m_scene = scene;
  m_layout = scene->getLayout();
}

bool SSGWriter::write(QIODevice *device)
{
  setDevice(device);
  
  writeStartDocument();
  writeDTD("<!DOCTYPE sigschege>");
  writeStartElement("sigschege");
  writeAttribute("version", "0.1");
  
  int index;
  for (index = 0; index < m_layout->count(); ++index) {
    dynamic_cast<TimMember*>(m_layout->itemAt(index))->SSGWrite(this);
//    const std::type_info& info = typeid(m_layout->itemAt(index));
//    if (typeid(m_layout->itemAt(index))==typeid(TimSignal*)) {
//      writeStartElement("signal");
//      writeEndElement();
//    } else {
//      cout << "TYPEID: " << typeid(m_layout->itemAt(index)).name() << endl;
//    }
  }



    writeEndDocument();
    return true;
}

///void SSGWriter::readSigschege()
///{
///    Q_ASSERT(isStartElement() && name() == "sigschege");
///
///    while (!atEnd()) {
///        readNext();
///
///        if (isEndElement())
///            break;
///
///        if (isStartElement()) {
///            if (name() == "signal")
///                readSignal();
///            else if (name() == "timescale")
///                readTimeScale();
/////            else
/////              readUnknownElement();
///        }
///    }
///}
///
///void SSGWriter::readSignal()
///{
///    Q_ASSERT(isStartElement() && name() == "signal");
///
///    QString title = "";
///    while (!atEnd()) {
///        readNext();
///
///        if (isEndElement())
///            break;
///
///        if (isStartElement()) {
///            if (name() == "primarytext")
///                title = readElementText();
///	}
///    }
///    TimSignal *new_signal = scene->addTimSignal();
///    new_signal->setText(title);
///}
///
///void SSGWriter::readTimeScale()
///{
///    Q_ASSERT(isStartElement() && name() == "timescale");
///
///    QString title = "";
///    while (!atEnd()) {
///        readNext();
///
///        if (isEndElement())
///            break;
///
///        if (isStartElement()) {
///            if (name() == "primarytext")
///                title = readElementText();
///	}
///    }
///    TimScale *new_scale = scene->addTimScale();
///    new_scale->setText(title);
///
///    //scene->addTimTimeScale();
///}
