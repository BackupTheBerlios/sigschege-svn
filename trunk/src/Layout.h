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

#ifndef _H_LAYOUT
#define _H_LAYOUT

using namespace std;

#include "Object.h"

enum LayoutID {BASIC};

//! A Layout Class
/*!
 * Tthe Layout Class
 */
class Layout : public Object {
public:
  //! The standard constructor
  /*!
   * This constructor will create an layout object without a parent.
   */
  Layout();
  
  //! The standard destructor
  ~Layout();

  //! Return the ID of this layout object
  /*!
   * Each sort of a layout object has a unique ID to identify the sort of layout object
   * \return Layout Object ID
   */
  virtual LayoutID getID();

  //! Add a new child layout object
  /*!
   * Adds a new child layout object to the end of the child list
   * \param newChild pointer to Layout Object that should be added to the child list
   * \sa hasChilds popChild insertChild moveChild getChild getChildCount
   */
  void pushChild(Layout* newChild);

  //! Insert a layout object into the child list
  /*!
   * Insert a layout object into the child list at define position
   * \param newChild pointer to the layout object that should be added to the child list
   * \param index position where to add the layout object in the child list
   * \sa hasChilds pushChild popChild moveChild getChild getChildCount
   */
  void insertChild(Layout* newChild, size_t index);

  //! Return a pointer of the child layout object at position index
  /*!
   * This function will return a pointer to the child layout object at position index
   * \param index position of the child obejct
   * \return pointer to the child layout object at position index
   * \sa hasChilds pushChild popChild insertChild moveChild getChildCount
   */
  Layout* getChild(size_t index);

  //! Get the pointer of the parent layout object
  /*!
   * This function returns the pointer of the parent function or NULL if it has no parent layout object
   * \return A Pointer the the parent layout object
   * \sa hasParent setParent delParent
   */
  Layout* getParent();

  //! Set the parent layout object
  /*!
   * The the parent layout object of the layout object to parent.
   * \param parent The pointer to the parent layout object
   * \sa hasParent getParent delParent
   */
  void setParent(Layout* parent);

  //! Delete the parent of this layout object
  /*!
   * Delete the parent layout object. The parent layout object will NOT be destroyed due this function
   * \sa hasParent getParent setParent
   */
  void delParent();

};
 

#endif // _H_LAYOUT
