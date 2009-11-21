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
  
  // iterate through the QGraphicsLinearLayout, which contains the timing diagram
  // Each member must have SSGWrite() implemented to write its content itself (using
  // a backpointer here)
  int index;
  for (index = 0; index < m_layout->count(); ++index) {
    dynamic_cast<TimMember*>(m_layout->itemAt(index))->SSGWrite(this);
  }

  writeEndDocument();
  return true;
}

