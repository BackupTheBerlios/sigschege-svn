// -*- c++ -*-
// \file  
// Copyright 2004 by Ulf Klaperski
//
// This file is part of EasyVec - Vector Figure Creation Library.
// 
// #############################################################################
//
// EasyVec is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2, or (at your option)
// any later version.
// 
// EasyVec is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with the EasyVec sources; see the file COPYING.  
//
// #############################################################################
//
// $Id$

#include "EVPosInt.h"
#include "EasyVecFigure.h"
#include "EasyVecBox.h"
#include "EasyVecPolyline.h"
#include "EasyVecText.h"
#include <iostream>
#include <vector>
#include <typeinfo>

using namespace std;

void test_a(void) {
  EasyVecFigure pic1, pic2;

  EasyVecBox *framebox1 = pic1.box(EVPosInt(120, 120), EVPosInt(6000-120, 6000-120));
  EasyVecBox *framebox2 = pic1.box(EVPosInt(240, 240), EVPosInt(6000-240, 6000-240));

  //EasyVecText *ctxt = pic1.text(EVPosInt(0, 0), "A centered Text");
  EasyVecText *ctxt = pic1.text();
  ctxt->setText("A centered Text");
  ctxt->setSize(16);
  int width = ctxt->getWidth();
  ctxt->setOrigin(EVPosInt(3000-width/2, 2000));


  pic2 = pic1;

  framebox2->styleValue(10.0);
  framebox2->lineStyle(EasyVecLine::dash_double_dotted);

  // get the text in picture 2 in order to change it
  vector<EasyVecElm*> texts = pic2.flatList();
  vector<EasyVecElm*>::iterator fiter = texts.begin(); 
  while (fiter!=texts.end()) {
    if (typeid(**fiter) != typeid(EasyVecText)) {
      fiter = texts.erase(fiter);
    } else fiter++;
  }

  EasyVecElm *text_g;
  EasyVecText *text;
  if (texts.size()==1) {
    cout << "OK, 1 text found..." << endl;
    text = dynamic_cast<EasyVecText*>(texts[0]);
    text->setText("A new text for figure 2");
  } else cout << "Error, expected 1 text!" << endl;

  int i;
  EasyVecPolyline *cplines[10];
  for (i=0; i<10; i++) {
    cplines[i] = pic2.polyline();
    cplines[i]->lineStyle(EasyVecLine::dashed);
    cplines[i]->addPoint(5700-150*i, 400); cplines[i]->addPoint(5700-150*i, 5600);

  }
  cplines[1]->styleValue(5.0);
  cplines[2]->styleValue(6.0);
  cplines[3]->styleValue(7.0);
  cplines[4]->styleValue(8.0);
  cplines[5]->lineStyle(EasyVecLine::dotted);
  cplines[6]->lineStyle(EasyVecLine::solid);
  cplines[7]->lineStyle(EasyVecLine::dash_dotted);
  cplines[8]->lineStyle(EasyVecLine::dash_double_dotted);
  cplines[9]->lineStyle(EasyVecLine::dash_triple_dotted);

  pic1.export_fig2dev("eps", "test_a_pic1_a.eps");
  pic2.export_fig2dev("eps", "test_a_pic2_a.eps");
  
}



int main(void) {

  EasyVecText::fig2dev_fontfix(true);
  
  test_a();

  EVPosInt Schortens, Dortmund;
  EVPosInt Prag(8700, 8000);

  Schortens.set(3000, 0);
  Dortmund.set(2000, 2500);

  vector<EVPosInt> points1;
  points1.push_back(EVPosInt(1200, 800));
  points1.push_back(EVPosInt(1200, 2000));
  points1.push_back(EVPosInt(5000, 2000));
  points1.push_back(EVPosInt(3000, 3000));
  points1.push_back(EVPosInt(1200, 1000));
  
  cout << "Prag ist bei " << Prag << endl;
  cout << "Entfernung Schortens-Prag: " << Schortens.distance(Prag) << endl;

  ////////////////////////////////////////////////////////////////////////////////

  EasyVecFigure mypic;

  EasyVecPolyline *line1 =  mypic.polyline();
  
  line1->addPoint(Schortens);
  line1->addPoint(1000, 500);
  line1->addPoint(500, 1000);
  line1->addPoint(1000, 1000);
  
  EasyVecCompound *cmp1 =  mypic.compound();
  EasyVecCompound *cmp1a =  cmp1->compound();
  
  EasyVecPolyline *line2 =  cmp1a->polyline();
  
  line2->addPoints(points1);
  EasyVecCompound *cmp2 =  mypic.compound();
  EasyVecPolyline *line3 =  cmp2->polyline();
  line3->addPoint(Schortens+Prag);
  line3->addPoint(Prag);
  line3->addPoint(Schortens);
  line3->addPoint(Dortmund);
  line3->pen_color(4);
  line3->forwardArrow(true);

  mypic.save("example.fig");
  
  EasyVecText *txt = mypic.text();
  txt->setText("Moin");
  EVPosInt text_ul, text_lr;
  txt->setOrigin(EVPosInt(500, 3000));
  txt->setSize(22);
  txt->setText("Use intermediate files");
  txt->getBoundingBox(text_ul, text_lr);

  cout << "upper left: " << text_ul << endl;
  cout << "lower right: " << text_lr << endl;

  EasyVecBox *textbox =  mypic.box(text_ul-EVPosInt(50, 50), text_lr+EVPosInt(50, 50));


  EasyVecText *txt2 = mypic.text();
  txt2->setOrigin(EVPosInt(500, 5000));
  txt2->setSize(22);
  txt2->setFont(15);
  txt2->setText("Use intermediate files");
  txt2->getBoundingBox(text_ul, text_lr);

  EasyVecBox *textbox2 =  mypic.box(text_ul-EVPosInt(50, 50), text_lr+EVPosInt(50, 50));


  EasyVecText *txt3 = mypic.text();
  txt3->setOrigin(EVPosInt(500, 6000));
  txt3->setSize(22);
  txt3->setFont(11);
  txt3->setText("////////////////");
  txt3->getBoundingBox(text_ul, text_lr);

  EasyVecBox *textbox3 =  mypic.box(text_ul-EVPosInt(50, 50), text_lr+EVPosInt(50, 50));

  EasyVecText *txt4 = mypic.text();
  txt4->setOrigin(EVPosInt(500, 6500));
  txt4->setSize(22);
  txt4->setFont(11);
  txt4->setText("M/M/M/M/M/M/M/M/");
  txt4->getBoundingBox(text_ul, text_lr);

  EasyVecBox *textbox4 =  mypic.box(text_ul-EVPosInt(50, 50), text_lr+EVPosInt(50, 50));

  EasyVecBox *textbox5 =  mypic.box(EVPosInt(500, 7000), EVPosInt(5000, 7500));
  EasyVecText *txt5 = mypic.text();
  txt5->setOrigin(EVPosInt(550, 7450));
  txt5->setSize(40);
  txt5->setFont(11);
  txt5->setText("A text to fit in the box.");
  int recSize5=txt5->sizeForBox(400, 4400);
  cout << "Text size is now: " << recSize5 << endl;
  txt5->setSize(recSize5);
  
  EasyVecBox *thickBox;
  for (int i=1; i<=5; i++) {
    thickBox=mypic.box(EVPosInt(1000+100*i, 1000+100*i), text_lr+EVPosInt(4000-100*i, 4000-100*i));
    thickBox->lineThickness(i);
  }
  
  // EasyVecPolyline *line4 =  mypic.polyline();
  // line4->addPoint(text_lr);
  // line4->addPoint(text_lr-EVPosInt(0, 500));

  cout << "Lower Right is " << text_lr << endl;
  mypic.save("example_text.fig");


  mypic.export_fig2dev("eps", "example_text.eps");
  
}
