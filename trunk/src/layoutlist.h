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

#ifndef _H_LAYOUTLIST
#define _H_LAYOUTLIST

using namespace std;

#include <vector>
#include "layout.h"
#include "objectlist.h"

//! LayoutList class for handling Layout Objects
/*!
 * This class provide function to create, access and delete layout objects.
 */
class CLayoutList : private CObjectList {
public:
  //! This constructor will create a empty LayoutList
  CLayoutList();

  //! This destructor will destroy the LayoutList ann all stored layout objects.
  ~CLayoutList();

  //! Return a Pointer to the Layout Object at position index
  /*!
   * This function will return a Pointer to the layout object stored at position index.
   * \return Return a pointer to the layout object at position index.
   */
  CLayout* getLayout(size_t index);

  //! Create a new Layout Object
  /*!
   * This function creates a new Layout Object.
   * \return the position of the layout object that was created.
   * \sa deleteLayout isEmpty
   */
  size_t createLayout();
  
  //! Delete a Layout Object
  /*! 
   * This function will destroy the layout object at position index and delete it
   * \param index position of the layout object to delete
   * \return true in any case (for now)
   */
  bool   deleteLayout(size_t index);

  //! true if the LayoutList is empty
  /*!
   * This function will check is the LayoutList is empty. If so, true will be returned and false otherwise.
   * \return Ture if no event is stored in the layoutlist
   * \sa createLayout deleteLayout
   */
  CObjectList::isEmpty;

};

#endif
