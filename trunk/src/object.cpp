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

#include "object.h"
#include <stdio.h>


CObject::CObject(){
  b_hasParent  = false;
  Parent     = NULL;
}

CObject::~CObject(){
}

bool CObject::hasChilds() {
  return(vec_ChildList.empty());
}

void CObject::pushChild(CObject* newChild) {
  vec_ChildList.push_back(newChild);
  newChild->setParent(this);
}

CObject* CObject::popChild() {
  CObject *temp = vec_ChildList.back();
  vec_ChildList.pop_back();
  return(temp);
}

void CObject::insertChild(CObject* newChild, size_t index) {
  vec_ChildList.insert(vec_ChildList.begin()+index, newChild);
}

void CObject::moveChild(size_t index1, size_t index2){
  CObject* temp;
  temp = vec_ChildList.at(index1);
  vec_ChildList.at(index1) = vec_ChildList.at(index2);
  vec_ChildList.at(index2) = temp;
}

CObject* CObject::getChild(size_t index) {
  return(vec_ChildList.at(index));
}

const size_t CObject::getChildCount() {
  return(vec_ChildList.size());
}
bool CObject::hasParent(){
  return(b_hasParent);
}
CObject* CObject::getParent() {
  if(b_hasParent){
    return(Parent);
  } else {
    return (NULL);
  }
}
void CObject::setParent(CObject* parent) {
  Parent    = parent;
  b_hasParent = true;
}
void CObject::delParent() {
  Parent    = NULL;
  b_hasParent = false;
}
