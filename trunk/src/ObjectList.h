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

#ifndef _H_OBJECTLIST
#define _H_OBJECTLIST

using namespace std;

#include <vector>
#include "Object.h"

//! Simple Class to handle object
/*!
 * This class provide basic functions to handle object.
 */
class ObjectList {
 public:
  
  //! Create a empty object list
  ObjectList();

  //! Delete the object list
  /*!
   * Delete all object in the list and the object list
   */
  virtual ~ObjectList();

  //! Return a pointer the the object at position index
  /*!
   * Return the pointer of the object at position index.
   * \param index Position of the object
   * \return Pointer of the object at position index
   * \sa createObject deleteObject isEmpty
   */
  virtual Object* getObject(size_t index);

  //! Create a new Object
  /*!
   * Create a new object at the end of the list and return it's position 
   * \param newObject pointer to the new object
   * \return position of the new object
   * \sa getObject deleteObject isEmpty
   */
  virtual size_t createObject(Object* newObject);
  
  //! Delete the object at position index
  /*!
   * Delete the object at position index from the list and destroy the object
   * \param index Position of the object to destroy
   * \sa getObject createObject isEmpty
   */
  virtual bool deleteObject(size_t index);

  //! Check if the object list is empty
  /*!
   * Check if the object list is empty and return the result.
   * \return true = List is empty, false = list is not empty
   * \sa getObject createObject deleteObject
   */
  virtual bool isEmpty();
  
 private:
  vector <Object*> vec_ObjectList;
};

#endif
