// -*- c++ -*-
// \file  
// Copyright 2004 by Ingo Hinrichs
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
// $Id$

using namespace std;

#include "TimingDiagram.h"
#include <stdio.h>

TimingDiagram::TimingDiagram(double startTime, double endTime) : TimList(), cYaVec() {
  setCompound(cYaVec.compound());
  setTimeRange(startTime, endTime);
}

TimingDiagram::~TimingDiagram() {
}


/*!
 * Export the Timingdiagram to a xfig-format
 * \param file XFig File Name
 */
void TimingDiagram::exportFig(string file) {
  paint();
  cYaVec.save(file);
}

/*!
 * Export the Timingdiagram to an encapsulated postscript
 * \param file EPS File Name
 */
void TimingDiagram::exportEPS(string file) {
  paint();
  cYaVec.exportFig2dev("eps", file);
}

/*!
 * Export the Timingdiagram to any format
 * \param file Picture file name.
 * \param format Format of the file, must be supported by fig2dev.
 */
void TimingDiagram::exportAny(string file, string format) {
  paint();
  cYaVec.exportFig2dev(format, file);
}




