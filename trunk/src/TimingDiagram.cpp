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

TimingDiagram::TimingDiagram() {
  cWidth        = 0;
  cBorderTop    = 0;
  cBorderLeft   = 0;
  cBorderRight  = 0;
  cBorderBottom = 0;
}

TimingDiagram::~TimingDiagram() {
}

/// Create a empyt Layout Text Object
/*!
 * This Function will return a pointer to a Text Layout Object without a text
 */
TimLabel* TimingDiagram::createTimLabel() {
  return(new TimLabel());
}

/*!
 * This Function will return a pointer to a Text Layout Object with the text newText
 */
TimLabel* TimingDiagram::createTimLabel(string newText) {
  return(new TimLabel(newText));
}


/// Set the width of the whole Timing Diagram
void TimingDiagram::setWidth(int new_width) {
  cWidth = new_width;
}


/*!
 * add the newLayout at the end of the Layout Object List
 */
void TimingDiagram::addLast(Layout *newLayout) {
  cLayoutList.createLayout(newLayout);
}

/*!
 * paint Every Layput Object in the Layout List
 */
void TimingDiagram::paint() {
  unsigned int yOffset = cBorderTop;
  unsigned int xOffset = cBorderLeft;
  for(size_t walk=0;walk<cLayoutList.size();walk++){
    cLayoutList.getLayout(walk)->setBoundaryWidth(cWidth-cBorderRight);
    yOffset += (cLayoutList.getLayout(walk)->paint(cEasyVec,xOffset, yOffset));
  }
  cEasyVec.box(EVPosInt(0,0),EVPosInt(cWidth,yOffset+cBorderBottom));
}

void TimingDiagram::save(string filename) {
  paint();
  cEasyVec.save(filename);
}

/*!
 * Set the top border to newBorder
 * \param newBorder new border to set
 * \sa setBorderLeft setBorderRight setBorderBottom getBorderTop getBorderLeft getBorderRight getBorderBottom
 */
void TimingDiagram::setBorderTop(int newBorder) {
  cBorderTop = newBorder;
}

/*!
 * Set the left border to newBorder
 * \param newBorder new border to set
 * \sa setBorderTop setBorderRight setBorderBottom getBorderTop getBorderLeft getBorderRight getBorderBottom
 */
void TimingDiagram::setBorderLeft(int newBorder) {
  cBorderLeft = newBorder;
}

/*!
 * Set the right border to newBorder
 * \param newBorder new border to set
 * \sa setBorderTop setBorderLeft setBorderBottom getBorderTop getBorderLeft getBorderRight getBorderBottom
 */
void TimingDiagram::setBorderRight(int newBorder) {
  cBorderRight = newBorder;
}

/*!
 * Set the bottom border to newBorder
 * \param newBorder new border to set
 * \sa setBorderTop setBorderLeft setBorderRight getBorderTop getBorderLeft getBorderRight getBorderBottom
 */
void TimingDiagram::setBorderBottom(int newBorder) {
  cBorderBottom = newBorder;
}

/*!
 * Return the top border
 * \return the top border
 * \sa setBorderTop setBorderLeft setBorderRight setBorderBottom getBorderLeft getBorderRight getBorderBottom
 */
int TimingDiagram::getBorderTop() {
  return(cBorderTop);
}

/*!
 * Return the left border
 * \return the left border
 * \sa setBorderTop setBorderLeft setBorderRight setBorderBottom getBorderTop getBorderRight getBorderBottom
 */
int TimingDiagram::getBorderLeft() {
  return(cBorderLeft);
}

/*!
 * Return the right border
 * \return the right border
 * \sa setBorderTop setBorderLeft setBorderRight setBorderBottom getBorderTop getBorderLeft getBorderBottom
 */
int TimingDiagram::getBorderRight() {
  return(cBorderRight);
}

/*!
 * Return the bottom border
 * \return the bottom border
 * \sa setBorderTop setBorderLeft setBorderRight setBorderBottom getBorderTop getBorderLeft getBorderRight
 */
int TimingDiagram::getBorderBottom() {
  return(cBorderBottom);
}
