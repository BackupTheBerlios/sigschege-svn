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

#include "objectlist.h"

CObjectList::CObjectList() {

}

CObjectList::~CObjectList() {
  for(size_t walk=0;walk<vec_ObjectList.size();walk++){
    delete vec_ObjectList.at(walk);
  }
}

CObject* CObjectList::getObject(size_t index) {
  return(vec_ObjectList.at(index));
}

size_t CObjectList::createObject(CObject* newObject) {
  vec_ObjectList.push_back(newObject);
  return(vec_ObjectList.size()-1);
}

bool CObjectList::deleteObject(size_t index) {
  delete vec_ObjectList.at(index);
  vec_ObjectList.erase(vec_ObjectList.begin()+index);
  return(true);
}

bool CObjectList::isEmpty() {
  return(vec_ObjectList.empty());
}
