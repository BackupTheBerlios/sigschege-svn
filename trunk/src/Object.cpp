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

#include "Object.h"
#include <stdio.h>


Object::Object(){
  b_hasParent  = false;
  Parent     = NULL;
}

Object::~Object(){
}

bool Object::hasChilds() {
  return(vec_ChildList.empty());
}

void Object::pushChild(Object* newChild) {
  vec_ChildList.push_back(newChild);
  newChild->setParent(this);
}

Object* Object::popChild() {
  Object *temp = vec_ChildList.back();
  vec_ChildList.pop_back();
  return(temp);
}

void Object::insertChild(Object* newChild, size_t index) {
  vec_ChildList.insert(vec_ChildList.begin()+index, newChild);
}

void Object::moveChild(size_t index1, size_t index2){
  Object* temp;
  temp = vec_ChildList.at(index1);
  vec_ChildList.at(index1) = vec_ChildList.at(index2);
  vec_ChildList.at(index2) = temp;
}

Object* Object::getChild(size_t index) {
  return(vec_ChildList.at(index));
}

const size_t Object::getChildCount() {
  return(vec_ChildList.size());
}

bool Object::hasParent(){
  return(b_hasParent);
}

Object* Object::getParent() {
  if(b_hasParent){
    return(Parent);
  } else {
    return (NULL);
  }
}

void Object::setParent(Object* parent) {
  Parent    = parent;
  b_hasParent = true;
}

void Object::delParent() {
  Parent    = NULL;
  b_hasParent = false;
}
