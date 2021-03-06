// -*- c++ -*-
// \file  
// Copyright 2004 by Ulf Klaperski
//
// This file is part of YaVec - Vector Figure Creation Library.
// 
// #############################################################################
//
// YaVec is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2, or (at your option)
// any later version.
// 
// YaVec is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with the YaVec sources; see the file COPYING.  
//
// #############################################################################
//
// $Id$

#include "YVPosInt.h"
#include "YaVecUtil.h"
#include "YaVecFigure.h"
#include "YaVecBox.h"
#include "YaVecPolyline.h"
#include "YaVecText.h"
#include <iostream>
#include <vector>
#include <typeinfo>

using namespace std;
using namespace YaVec;

void test_a(void) {
  FFigure pic1, pic2;

  FBox *framebox1 = pic1.box(PosInt(120, 120), PosInt(6000-120, 6000-120));
  FBox *framebox2 = pic1.box(PosInt(240, 240), PosInt(6000-240, 6000-240));

  //FText *ctxt = pic1.text(PosInt(0, 0), "A centered Text");
  FText *ctxt = pic1.text();
  ctxt->setText("A centered Text");
  ctxt->setSize(16);
  int width = ctxt->getWidth();
  ctxt->setOrigin(PosInt(3000-width/2, 2000));


  pic2 = pic1;

  framebox2->styleValue(10.0);
  framebox2->lineStyle(YaVecLine::dash_double_dotted);

  // get the text in picture 2 in order to change it
  vector<YaVecElm*> texts = pic2.flatList();
  vector<YaVecElm*>::iterator fiter = texts.begin(); 
  while (fiter!=texts.end()) {
    if (typeid(**fiter) != typeid(FText)) {
      fiter = texts.erase(fiter);
    } else fiter++;
  }

  YaVecElm *text_g;
  FText *text;
  if (texts.size()==1) {
    cout << "OK, 1 text found..." << endl;
    text = dynamic_cast<FText*>(texts[0]);
    text->setText("A new text for figure 2");
  } else cout << "Error, expected 1 text!" << endl;

  int i;
  FPolyline *cplines[10];
  FPolyline *arlines[10];
  for (i=0; i<10; i++) {
    cplines[i] = pic2.polyline();
    arlines[i] = pic1.polyline();
    cplines[i]->lineStyle(YaVecLine::dashed);
    cplines[i]->addPoint(5700-150*i, 400); cplines[i]->addPoint(5700-150*i, 5600);
    arlines[i]->addPoint(3700-150*i, 400); arlines[i]->addPoint(3700-150*i, 5600);
    if (i<5) {
      arlines[i]->forwardArrow(true);
      arlines[i]->forwardArrowType(i%4);
    } else {
      arlines[i]->backwardArrow(true);
      arlines[i]->backwardArrowType((i/2)%3+1);
      arlines[i]->backwardArrowStyle(i%2);
    }
  }
  cplines[1]->styleValue(5.0);
  cplines[2]->styleValue(6.0);
  cplines[3]->styleValue(7.0);
  cplines[4]->styleValue(8.0);
  cplines[5]->lineStyle(YaVecLine::dotted);
  cplines[6]->lineStyle(YaVecLine::solid);
  cplines[7]->lineStyle(YaVecLine::dash_dotted);
  cplines[8]->lineStyle(YaVecLine::dash_double_dotted);
  cplines[9]->lineStyle(YaVecLine::dash_triple_dotted);

  pic2.save("test_a_pic2_a.fig");
  pic1.exportFig2dev("eps", "test_a_pic1_a.eps");
  pic2.exportFig2dev("eps", "test_a_pic2_a.eps");
  
}



int main(void) {

  FText::fig2dev_fontfix(true);
  
  test_a();

  PosInt Schortens, Dortmund;
  PosInt Prag(8700, 8000);

  Schortens.set(3000, 0);
  Dortmund.set(2000, 2500);

  vector<PosInt> points1;
  points1.push_back(PosInt(1200, 800));
  points1.push_back(PosInt(1200, 2000));
  points1.push_back(PosInt(5000, 2000));
  points1.push_back(PosInt(3000, 3000));
  points1.push_back(PosInt(1200, 1000));
  
  cout << "Prag ist bei " << Prag << endl;
  cout << "Entfernung Schortens-Prag: " << Schortens.distance(Prag) << endl;

  ////////////////////////////////////////////////////////////////////////////////

  FFigure mypic;

  FPolyline *line1 =  mypic.polyline();
  
  line1->addPoint(Schortens);
  line1->addPoint(1000, 500);
  line1->addPoint(500, 1000);
  line1->addPoint(1000, 1000);
  
  FCompound *cmp1 =  mypic.compound();
  FCompound *cmp1a =  cmp1->compound();
  
  FPolyline *line2 =  cmp1a->polyline();
  
  line2->addPoints(points1);
  FCompound *cmp2 =  mypic.compound();
  FPolyline *line3 =  cmp2->polyline();
  line3->addPoint(Schortens+Prag);
  line3->addPoint(Prag);
  line3->addPoint(Schortens);
  line3->addPoint(Dortmund);
  line3->penColor(4);
  line3->forwardArrow(true);
  line3->forwardArrowType(YaVecArrow::closed_pointed_butt);

  mypic.save("example.fig");
  
  FText *txt = mypic.text();
  txt->setText("Moin");
  PosInt text_ul, text_lr;
  txt->setOrigin(PosInt(500, 3000));
  txt->setSize(22);
  txt->setText("Use intermediate files");
  txt->getBoundingBox(text_ul, text_lr);

  cout << "upper left: " << text_ul << endl;
  cout << "lower right: " << text_lr << endl;

  FBox *textbox =  mypic.box(text_ul-PosInt(50, 50), text_lr+PosInt(50, 50));


  FText *txt2 = mypic.text();
  txt2->setOrigin(PosInt(500, 5000));
  txt2->setSize(22);
  txt2->setFont(15);
  txt2->setText("Use intermediate files");
  txt2->getBoundingBox(text_ul, text_lr);

  FBox *textbox2 =  mypic.box(text_ul-PosInt(50, 50), text_lr+PosInt(50, 50));


  FText *txt3 = mypic.text();
  txt3->setOrigin(PosInt(500, 6000));
  txt3->setSize(22);
  txt3->setFont(11);
  txt3->setText("////////////////");
  txt3->getBoundingBox(text_ul, text_lr);

  FBox *textbox3 =  mypic.box(text_ul-PosInt(50, 50), text_lr+PosInt(50, 50));

  FText *txt4 = mypic.text();
  txt4->setOrigin(PosInt(500, 6500));
  txt4->setSize(22);
  txt4->setFont(11);
  txt4->setText("M/M/M/M/M/M/M/M/");
  txt4->getBoundingBox(text_ul, text_lr);

  FBox *textbox4 =  mypic.box(text_ul-PosInt(50, 50), text_lr+PosInt(50, 50));

  FBox *textbox5 =  mypic.box(PosInt(500, 7000), PosInt(5000, 7500));
  FText *txt5 = mypic.text();
  txt5->setOrigin(PosInt(550, 7450));
  txt5->setSize(40);
  txt5->setFont(11);
  txt5->setText("A text to fit in the box.");
  int recSize5=txt5->sizeForBox(400, 4400);
  cout << "Text size is now: " << recSize5 << endl;
  txt5->setSize(recSize5);
  
  FBox *thickBox;
  for (int i=1; i<=5; i++) {
    thickBox=mypic.box(PosInt(1000+100*i, 1000+100*i), text_lr+PosInt(4000-100*i, 4000-100*i));
    thickBox->lineThickness(i);
  }
  
  // FPolyline *line4 =  mypic.polyline();
  // line4->addPoint(text_lr);
  // line4->addPoint(text_lr-PosInt(0, 500));
  FArc *arc1 = mypic.arc(PosInt(1000, 500), PosInt(0, 450), PosInt(2000, 400));

  cout << "Lower Right is " << text_lr << endl;
  mypic.save("example_text.fig");
  
  mypic.exportFig2dev("eps", "example_text.eps");

  
}
