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

#include "ObjectList.h"

ObjectList::ObjectList() {

}

/*!
 * Delete all object in the list and the object list
 */
ObjectList::~ObjectList() {
  for(size_t walk=0;walk<vec_ObjectList.size();walk++){
    delete vec_ObjectList.at(walk);
  }
}

/*!
 * Return the pointer of the object at position index.
 * \param index Position of the object
 * \return Pointer of the object at position index
 * \sa createObject deleteObject isEmpty
 */
Object* ObjectList::getObject(size_t index) {
  return(vec_ObjectList.at(index));
}

/*!
 * Create a new object at the end of the list and return it's position 
 * \param newObject pointer to the new object
 * \return position of the new object
 * \sa getObject deleteObject isEmpty
 */
size_t ObjectList::createObject(Object* newObject) {
  vec_ObjectList.push_back(newObject);
  return(vec_ObjectList.size()-1);
}

/*!
 * Delete the object at position index from the list and destroy the object
 * \param index Position of the object to destroy
 * \sa getObject createObject isEmpty
 */
bool ObjectList::deleteObject(size_t index) {
  delete vec_ObjectList.at(index);
  vec_ObjectList.erase(vec_ObjectList.begin()+index);
  return(true);
}

/*!
 * Check if the object list is empty and return the result.
 * \return true = List is empty, false = list is not empty
 * \sa getObject createObject deleteObject
 */
bool ObjectList::isEmpty() {
  return(vec_ObjectList.empty());
}

/*!
 * \return the size of the object list
 * \sa isEmpty
 */
const size_t ObjectList::size() {
  return(vec_ObjectList.size());
}
