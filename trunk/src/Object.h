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

#ifndef _H_OBJECT
#define _H_OBJECT

using namespace std;

#include <vector>

//! This class is a basic object that can be handled by the ObjectList class
/*!
 * This class provied some basic function that are needed to build a tree of objects.
 * Each object can have no or one parent object and can have none or many child objects.
 */
class Object {
public:
  //! The standard constructor
  Object();

  //! The standard destructor
  virtual ~Object();
  
  //! Check if the object has no childs
  /*!
   * This function checks if the object has child and return the result
   * \return true = if the obejct has childs, false = if the object has no childs
   * \sa pushChild popChild insertChild moveChild getChild getChildCount
   */
  virtual bool hasChilds();

  //! Add a new child object
  /*!
   * Adds a new child object to the end of the child list
   * \param newChild pointer to Object that should be added to the child list
   * \sa hasChilds popChild insertChild moveChild getChild getChildCount
   */
  virtual void pushChild(Object* newChild);

  //! Remove the last child from the child list
  /*!
   * This function remove the lase child from the list and return it's pointer
   * \return A pointer to the remove child.
   * \sa hasChilds pushChild insertChild moveChild getChild getChildCount
   */
  virtual Object* popChild();

  //! Insert a object into the child list
  /*!
   * Insert a object into the child list at define position
   * \param newChild pointer to the object that should be added to the child list
   * \param index position where to add the object in the child list
   * \sa hasChilds pushChild popChild moveChild getChild getChildCount
   */
  virtual void insertChild(Object* newChild, size_t index);

  //! interchange two child objects
  /*!
   * interchange the object a position index1 with the object at position index2
   * \param index1 position of child object 1
   * \param index2 position of child object 2
   * \sa hasChilds pushChild popChild insertChild getChild getChildCount
   */
  virtual void moveChild(size_t index1, size_t index2);
  
  //! Return a pointer of the child object at position index
  /*!
   * This function will return a pointer to the child object at position index
   * \param index position of the child obejct
   * \return pointer to the child object at position index
   * \sa hasChilds pushChild popChild insertChild moveChild getChildCount
   */
  virtual Object* getChild(size_t index);

  //! Return the number of child in the child list
  /*!
   * \return The Number of childs in the child list
   * \sa hasChilds pushChild popChild insertChild moveChild getChild
   */
  virtual const size_t getChildCount();

  //! Check if this object has a parent object
  /*!
   * This function checks if it has a parent object and return the result
   * \return true = has parent object, false = has no parent object
   * \sa getParent setParent delParent
   */
  virtual bool hasParent();

  //! Get the pointer of the parent object
  /*!
   * This function returns the pointer of the parent function or NULL if it has no parent object
   * \return A Pointer the the parent object
   * \sa hasParent setParent delParent
   */
  virtual Object* getParent();

  //! Set the parent object
  /*!
   * The the parent object of the object to parent.
   * \param parent The pointer to the parent object
   * \sa hasParent getParent delParent
   */
  virtual void setParent(Object* parent);

  //! Delete the parent of this object
  /*!
   * Delete the parent object. The parent object will NOT be destroyed due this function
   * \sa hasParent getParent setParent
   */
  virtual void delParent();

private:
  bool b_hasParent;
  Object *Parent;
  vector <Object*> vec_ChildList;

};

#endif
