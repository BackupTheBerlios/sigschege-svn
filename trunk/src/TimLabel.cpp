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

#include "TimLabel.h"
#include <iostream>
#include <EasyVecText.h>

/*!
 * This constructor will create an Timing Diagram Label Object
 */
TimLabel::TimLabel():LayoutObject(){
  cFontType = 14;
  cFontSize = 20;
}

/*!
 * This constructor will create an Timing Diagram Label Object
 * newText will be set as Text
 */
TimLabel::TimLabel(string newText):LayoutObject(){
  cText = newText;
  cFontType = 14;
  cFontSize = 20;
}


TimLabel::~TimLabel(){
}


/*!
 * Set a new Text
 * \param newText the new text
 */
void TimLabel::setText(string newText) {
  cText = newText;
}

/*!
 * Paint this text layout object
 */
void TimLabel::paint(void) {
  EasyVecText *text;

  // check if a compound is available
  if(getCompound()==0) return;

  // first we have to clear out compound
  getCompound()->clear();

  // and then we can draw out new stuff
  // Draw the border
  LayoutObject::paint();

  // Draw the Text
  text = getCompound()->text();
  text->setText(cText);
  text->setFont(cFontType);
  text->setSize(cFontSize);
  text->setOrigin(cOrigin+EVPosInt(cPadding,(cSize.ypos()+text->getHeight())/2));
}

/// Set the Font Type
void TimLabel::setFontType(int new_font) {
  cFontType = new_font;
}

/// Set the Font Size
void TimLabel::setFontSize(int new_size) {
  cFontSize = new_size;
}
