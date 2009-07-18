// -*- c++ -*-
// \file 
// Copyright 2005 - 2008 by Ulf Klaperski
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

#include "TimText.h"
#include "YaVecText.h"

using namespace YaVec;
using namespace std;

void TimText::setText(std::string newText){
  cText1 = newText;
}

void TimText::setText1(std::string newText1){
  cText1 = newText1;
}

void TimText::setText2(std::string newText2) {
  cText2 = newText2;
}

TimText::TimText(string text1, string text2, hAlignment align1, hAlignment align2) {
  cText1 = text1;
  cText2 = text2;
  cFontType = 14;
  if (text2=="") {
    cFontSize = 14;
  } else {
    cFontSize = 20;
  }
  cFontSize2 = 0;
  cHAlign1 = align1;
  cHAlign2 = align2;
}



void TimText::paint(YaVec::FCompound *cCompound) {
  FText *text;
  PosInt cLowerRight;
  PosInt cUpperLeft;
  getTextGeometry(cUpperLeft, cLowerRight);
  int height = cLowerRight.ypos()-cUpperLeft.ypos();
  int width = cLowerRight.xpos()-cUpperLeft.xpos();
  int xpos, twidth;
  
  text = cCompound->text();
  text->setText(cText1);
  text->setFont(cFontType);
  text->setSize(cFontSize);

  twidth = text->getWidth();
  switch (cHAlign1) {
  case left:
    xpos = cUpperLeft.xpos();
    break;
  case right:
    xpos = cLowerRight.xpos()-twidth;
    break;
  case follow:
  case hcenter:
    xpos = cUpperLeft.xpos()+width/2-twidth/2;
  }    
  text->setOrigin(PosInt(xpos, cUpperLeft.ypos()+height/2+(cText2==""? text->getHeight()/2 : 0)));
  
  if (cText2!="") {
    hAlignment align = cHAlign2==follow ? cHAlign1 : cHAlign2;
    
    text = cCompound->text();
    text->setText(cText2);
    text->setFont(cFontType);
    text->setSize(cFontSize2==0 ? cFontSize: cFontSize2);
    twidth = text->getWidth();
    switch (align) {
    case left:
      xpos = cUpperLeft.xpos();
      break;
    case right:
      xpos = cLowerRight.xpos()-twidth;
      break;
    case follow:
    case hcenter:
      xpos = cUpperLeft.xpos()+width/2-twidth/2;
    }    
    text->setOrigin(PosInt(xpos, cLowerRight.ypos()));
  }
}

void TimText::save(std::ofstream &ssg_file) {
  ssg_file << "<primarytext>";
  ssg_file << "<![CDATA[" << cText1 << "]]>";
  ssg_file << "</primarytext>" << endl;
}
