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

#include "Layout.h"
#include <stdio.h>
#include <EasyVecPolyline.h>

/*!
 * This constructor will create an layout object without a parent.
 */
Layout::Layout():Object(){
  cDrawBoundaryBox = false;
  cPadding         = 0;
  cBoundaryWidth   = 0;
  cBoundaryHeight  = 0;
}

Layout::~Layout(){
}

/*!
 * Adds a new child layout object to the end of the child list
 * \param newChild pointer to Layout Object that should be added to the child list
 * \sa hasChilds popChild insertChild moveChild getChild getChildCount
 */
void Layout::pushChild(Layout* newChild) {
  Object::pushChild((Object*) newChild);
}

/*!
 * Insert a layout object into the child list at define position
 * \param newChild pointer to the layout object that should be added to the child list
 * \param index position where to add the layout object in the child list
 * \sa hasChilds pushChild popChild moveChild getChild getChildCount
 */
void Layout::insertChild(Layout* newChild, size_t index) {
  Object::insertChild((Object*) newChild,index);
}

/*!
 * This function will return a pointer to the child layout object at position index
 * \param index position of the child obejct
 * \return pointer to the child layout object at position index
 * \sa hasChilds pushChild popChild insertChild moveChild getChildCount
 */
Layout* Layout::getChild(size_t index) {
  return((Layout*) Object::getChild(index));
}

/*!
 * This function returns the pointer of the parent function or NULL if it has no parent layout object
 * \return A Pointer the the parent layout object
 * \sa hasParent setParent delParent
 */
Layout* Layout::getParent() {
  return((Layout*) Object::getParent());
}

/*!
 * The the parent layout object of the layout object to parent.
 * \param parent The pointer to the parent layout object
 * \sa hasParent getParent delParent
 */
void Layout::setParent(Layout* parent) {
  Object::setParent((Object*) parent);
}

/*!
 * Delete the parent layout object. The parent layout object will NOT be destroyed due this function
 * \sa hasParent getParent setParent
 */
void Layout::delParent() {
  Object::delParent();
}

/*!
 * Each sort of a layout object has a unique ID to identify the sort of layout object
 * \return Layout Object ID
 */
LayoutID Layout::getID() {
  return(BASIC);
}

/*!
 * Paint this layout object
 */
unsigned int Layout::paint(EasyVecFigure& cEasyVec,unsigned int xOffset, unsigned int yOffset) {
  if(cDrawBoundaryBox) {
    cEasyVec.box(EVPosInt(xOffset, yOffset),EVPosInt(getBoundaryWidth()+xOffset,getBoundaryHeight()+yOffset));
  }
  return (0);
}

/*!
 * Set the boundary width for this Layout Object
 * \param newWidth new boundary width 
 * \sa setBoundaryHeight getBoundaryWidth getBoundaryHeight
 */
void Layout::setBoundaryWidth(int newWidth) {
  cBoundaryWidth = newWidth;
}

/*!
 * Set the boundary height for this Layout Object
 * \param newHeight new boundary height 
 * \sa setBoundaryWidth getBoundaryWidth getBoundaryHeight
 */
void Layout::setBoundaryHeight(int newHeight) {
  cBoundaryHeight = newHeight;
}

/*!
 * Get the boundary width for this Layout Object
 * \return the boundary width for this Layout Object
 * \sa setBoundaryWidth setBoundaryHeight getBoundaryHeight
 */
int Layout::getBoundaryWidth() {
  return(cBoundaryWidth);
}

/*!
 * Get the boundary height for this Layout Object
 * \return the boundary height for this Layout Object
 * \sa setBoundaryWidth setBoundaryHeight getBoundaryWidth
 */
int Layout::getBoundaryHeight() {
  return(cBoundaryHeight);
}

/*!
 * Set to true paint() will draw a boundary box
 * \param draw_box set to true to draw a boundary box at paint event
 * \sa paint
 */
void Layout::drawBoundaryBox(bool draw_box) {
  cDrawBoundaryBox = draw_box;
}

/*!
 * This function the the inner padding of this layout object
 * The inner padding is the distance between the boundary box and the graphic objects (eg: text)
 * \param newPadding the new padding value
 */
void Layout::setPadding(int newPadding) {
  cPadding = newPadding;
}

/*!
 * return the padding
 * \return padding of this Layout object
 */
int Layout::getPadding() {
  return(cPadding);
}
