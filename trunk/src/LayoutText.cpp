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

#include "LayoutText.h"
#include <iostream>
#include <EasyVecElmText.h>

/*!
 * This constructor will create an layout object without a parent.
 */
LayoutText::LayoutText():Layout(){
  cFontType = 14;
  cFontSize = 20;
}

/*!
 * This constructor will create an layout object without a parent.
 * newText will be set as Text
 */
LayoutText::LayoutText(string newText):Layout(){
  cText = newText;
  cFontType = 14;
  cFontSize = 20;
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
 * Set a new Text
 * \param newText the new text
 */
void LayoutText::setText(string newText) {
  cText = newText;
}

/*!
 * Paint this text layout object
 */
unsigned int LayoutText::paint(EasyVec& cEasyVec, unsigned int xOffset, unsigned int yOffset) {
  int text_width  = 0;
  int text_height = 0;
  int width;
  int height;

  if(!cText.empty()){
    EasyVecElmText *txt = cEasyVec.text();
    // set font and text
    txt->setFont(cFontType);
    txt->setSize(cFontSize);
    txt->setText(cText.c_str());

    // calculate and set the origin
    text_width  = txt->getWidth();
    text_height = txt->getHeight();
    txt->setOrigin(EVPosInt(xOffset, text_height+yOffset));
  }
  
  height = getBoundaryHeight()<text_height?text_height:getBoundaryHeight();
  width  = getBoundaryWidth()<text_width?text_width:getBoundaryWidth();

  setBoundaryHeight(height);
  setBoundaryWidth(width-xOffset);

  Layout::paint(cEasyVec,xOffset,yOffset);

  return(height);
}

/// Set the Font Type
void LayoutText::setFontType(int new_font) {
  cFontType = new_font;
}

/// Set the Font Size
void LayoutText::setFontSize(int new_size) {
  cFontSize = new_size;
}
