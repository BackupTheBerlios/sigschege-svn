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
// $Id: $

using namespace std;

#include "Timing.h"

Timing::Timing() {
  TopLayout = myLayoutList.createLayout();
  myLayoutList.getLayout(TopLayout)->setBox(0,0,1000,1000);
}

Timing::~Timing() {
}

void Timing::paint() {
  myLayoutList.getLayout(TopLayout)->paint(myEasyVec);
}

void Timing::save(string filename) {
  myEasyVec.save(filename);
}
