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
#include "EasyVec.h"
#include "EasyVecElmPolyline.h"
#include "EasyVecElmText.h"
#include <iostream>
#include <vector>

using namespace std;

void test_a(void) {
  EasyVec pic1, pic2;

  EasyVecElmBox *framebox1 = pic1.box(EVPosInt(120, 120), EVPosInt(6000-120, 6000-120));
  EasyVecElmBox *framebox2 = pic1.box(EVPosInt(240, 240), EVPosInt(6000-240, 6000-240));

  //EasyVecElmText *ctxt = pic1.text(EVPosInt(0, 0), "A centered Text");
  EasyVecElmText *ctxt = pic1.text();
  ctxt->setText("A centered Text");
  ctxt->setSize(16);
  int width = ctxt->getWidth();
  ctxt->setOrigin(EVPosInt(3000-width/2, 2000));


  pic2 = pic1;

  vector<EasyVecElm*> texts = pic2.flatList();

  vector<EasyVecElm*>::iterator fiter = texts.begin(); 
  while (fiter!=texts.end()) {
    if ((*fiter)->type() != EasyVecElm::Text) {
      fiter = texts.erase(fiter);
    } else fiter++;
  }

  EasyVecElm *text_g;
  EasyVecElmText *text;
  if (texts.size()==1) {
    cout << "OK, 1 text found..." << endl;
    text = dynamic_cast<EasyVecElmText*>(texts[0]);
    text->setText("A new text for figure 2");
  }

  
  pic1.export_fig2dev("eps", "test_a_pic1_a.eps");
  pic2.export_fig2dev("eps", "test_a_pic2_a.eps");
  
}



int main(void) {

  EasyVecElmText::fig2dev_fontfix(true);
  
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

  EasyVec mypic;

  EasyVecElmPolyline *line1 =  mypic.polyline();
  
  line1->add_point(Schortens);
  line1->add_point(1000, 500);
  line1->add_point(500, 1000);
  line1->add_point(1000, 1000);
  
  EasyVecElmCompound *cmp1 =  mypic.compound();
  EasyVecElmCompound *cmp1a =  cmp1->compound();
  
  EasyVecElmPolyline *line2 =  cmp1a->polyline();
  
  line2->add_points(points1);
  EasyVecElmCompound *cmp2 =  mypic.compound();
  EasyVecElmPolyline *line3 =  cmp2->polyline();
  line3->add_point(Schortens+Prag);
  line3->add_point(Prag);
  line3->add_point(Schortens);
  line3->add_point(Dortmund);
  line3->pen_color(4);
  line3->forward_arrow(true);

  mypic.save("example.fig");
  
  EasyVecElmText *txt = mypic.text();
  txt->setText("Moin");
  EVPosInt text_ul, text_lr;
  txt->setOrigin(EVPosInt(500, 3000));
  txt->setSize(22);
  txt->setText("Use intermediate files");
  txt->getBoundingBox(text_ul, text_lr);

  EasyVecElmBox *textbox =  mypic.box(text_ul-EVPosInt(50, 50), text_lr+EVPosInt(50, 50));


  EasyVecElmText *txt2 = mypic.text();
  txt2->setOrigin(EVPosInt(500, 5000));
  txt2->setSize(22);
  txt2->setFont(15);
  txt2->setText("Use intermediate files");
  txt2->getBoundingBox(text_ul, text_lr);

  EasyVecElmBox *textbox2 =  mypic.box(text_ul-EVPosInt(50, 50), text_lr+EVPosInt(50, 50));

  // EasyVecElmPolyline *line4 =  mypic.polyline();
  // line4->add_point(text_lr);
  // line4->add_point(text_lr-EVPosInt(0, 500));

  cout << "Lower Right is " << text_lr << endl;
  mypic.save("example_text.fig");


  mypic.export_fig2dev("eps", "example_text.eps");
  
}
