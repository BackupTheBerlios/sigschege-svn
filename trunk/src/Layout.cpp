// -*- c++ -*-
/// \file 
 
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

#include "Layout.h"
#include <stdio.h>

/*!
 * This constructor will create an layout object without a parent.
 */
Layout::Layout():Object(){
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
 * Set the boundary box of the layout object
 * \param newUL upper left corner of the boundary box
 * \param newBR bottom right corner of the boundary box
 */
void Layout::setBox(const EVPosInt &newUL, const EVPosInt &newBR) {
  
}

/*! 
 * Set the boundary box of the layout object
 * \param l left boundary
 * \param u upper boundary
 * \param r right boundary
 * \param b bottom boundary
 */
void Layout::setBox(int l, int u, int r, int b) {
  cUL.sety(l);
  cUL.setx(u);
  cBR.sety(r);
  cBR.setx(b);
}

/*! 
 * Return the Upper Left corner of the layout object
 * \return The Upper Left Point
 */
const EVPosInt &Layout::getUL() {
  return(cUL);
}

/*!
 * Retrun the Bottom Right corner of the layout object
 * \return The Bottom Right Point
 */
const EVPosInt &Layout::getBR() {
  return(cBR);
}

/*!
 * Paint this layout object
 */
void Layout::paint() {
  printf("Boundary Box: (%i,%i)(%i,%i)\n",cUL.xpos(), cUL.ypos(),cBR.xpos(), cBR.ypos());
}
