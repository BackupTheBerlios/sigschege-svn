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

#include "LayoutText.h"
#include <iostream>
#include <EasyVecElmText.h>

/*!
 * This constructor will create an layout object without a parent.
 */
LayoutText::LayoutText():Layout(){
  cText = "Hello World";
}

LayoutText::~LayoutText(){
}

/*!
 * Return a TEXT Id
 * \return Layout Object ID of this object (TEXT)
 */
LayoutID LayoutText::getID() {
  return(TEXT);
}

/*!
 * Paint this text layout object
 */
void LayoutText::paint(EasyVec& cEasyVec) {
  
  cEasyVec.box(getUL(),getBR());


  EasyVecElmText *txt2 = cEasyVec.text();

  txt2->setOrigin(EVPosInt(getUL().xpos(), getBR().ypos()));
  txt2->setSize(22);
  txt2->setFont(15);
  txt2->setText(cText.c_str());
  txt2->getBoundingBox(getUL(), getBR());

}
