// -*- c++ -*-
// \file  
// Copyright 2005 by Ulf Klaperski
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

#include "YaVecArc.h"
#include "YaVecFigure.h"
#include <fstream>
#include <iostream>

using namespace std;

namespace YaVec {

  FArc::FArc(FCompound* parent_compound, FFigure* figure_compound,
                     PosInt p1, PosInt p2, PosInt p3, bool isPieWedge)
    : YaVecElm(parent_compound, figure_compound), YaVecLine(), YaVecArrow() {
    elmIsPieWedge = isPieWedge;
    setPoints(p1, p2, p3);
  };

  FArc::FArc(FCompound* parent_compound, FFigure* figure_compound, PosInt center,
                     double radius, bool clockwise, double angle1, double angle3, bool isPieWedge)
    : YaVecElm(parent_compound, figure_compound), YaVecLine(), YaVecArrow() {
    elmIsPieWedge = isPieWedge;
    setArc(center, radius, clockwise, angle1, angle3);
  };


  static int quadrant(double angle) {
    if (angle<0) angle += 2*M_PI;
    if (angle<M_PI_2) {
      return 0;
    } else if (angle<M_PI) {
      return 1;
    } else if (angle<M_PI_2*3) {
      return 2;
    } else return 3;
  }

  static double asinq(double x, double y, double r) {
  
    double phi = asin(fabs(y)/r);
  
    if (x<0 && y>=0) phi = M_PI-phi;
    else if (x<0 && y<0) phi = M_PI+phi;
    else if (x>0 && y<0) phi = 2*M_PI-phi;
    return phi;
  }

  void FArc::getBoundingBox(PosInt &upper_left, PosInt &lower_right) {
    int qs, qe;
    upper_left = lower_right = elmPoint1;
    upper_left.minValues(elmPoint2);
    lower_right.maxValues(elmPoint2);
    upper_left.minValues(elmPoint3);
    lower_right.maxValues(elmPoint3);
  

    qs = elmClockwise? quadrant(elmPhi3) : quadrant(elmPhi1);
    qe = elmClockwise? quadrant(elmPhi1) : quadrant(elmPhi3);

    while (qs!=qe) {
      if (qs==3) {
        lower_right.setx(static_cast<int>(elmXCenter+elmRadius));
        qs = 0;
      } else {
        if (qs==0) upper_left.sety(static_cast<int>(elmYCenter+elmRadius));
        else if (qs==1) upper_left.setx(static_cast<int>(elmXCenter-elmRadius));
        else if (qs==2) lower_right.sety(static_cast<int>(elmYCenter-elmRadius));
        qs++;
      }
    }
  }

  void FArc::computeArc(void) {
    PosInt p1, p2, p3, ptmp;
    double y0, x0, x1, y1, x2, y2, x3, y3;
    p1 = elmPoint1;
    p2 = elmPoint2;
    p3 = elmPoint3;
    if ((p1.xpos()-p2.xpos())==0) {
      ptmp = p1;
      p1 = p3;
      p3 = ptmp;
    } else if ((p3.xpos()-p1.xpos())==0) {
      ptmp = p1;
      p1 = p2;
      p2 = ptmp;
    }

    x1 = p1.xpos(); y1 = p1.ypos();
    x2 = p2.xpos(); y2 = p2.ypos();
    x3 = p3.xpos(); y3 = p3.ypos();

    y0 = 0.5 * ((x3-x1)*(x2*x2-x1*x1+y2*y2-y1*y1)-(x2-x1)*(x3*x3-x1*x1+y3*y3-y1*y1)) / ((y1-y3)*(x2-x1)-(x3-x1)*(y1-y2));
    x0 = (0.5 * (x3*x3-x1*x1+y3*y3-y1*y1) + y0*(y1-y3)) / (x3-x1);
    elmXCenter = x0;
    elmYCenter = y0;
    elmRadius = sqrt((x1-x0)*(x1-x0)+(y1-y0)*(y1-y0));
    elmPhi1 = asinq(x1-x0, y1-y0, elmRadius);
    elmPhi2 = asinq(x2-x0, y2-y0, elmRadius);
    elmPhi3 = asinq(x3-x0, y3-y0, elmRadius);
    elmClockwise = !((elmPhi2>elmPhi1 && (elmPhi3<elmPhi1 || elmPhi3>elmPhi2)) || (elmPhi2<elmPhi1 && (elmPhi3<elmPhi1 && elmPhi3>elmPhi2))); 
    //cout << "X Center: " << x0 << " Y Center: " << y0 << " elmClockwise:" << elmClockwise << endl;
  }

  void FArc::setPoint(int num, PosInt newPosition) {
    switch (num) {
    case 0:
      elmPoint1 = newPosition;
      break;
    case 1:
      elmPoint2 = newPosition;
      break;
    case 2:
      elmPoint3 = newPosition;
      break;
    default:
      throw string("Illegal value for point in arc");
    }
    computeArc();
    parent->handleChange(this);
  }

  void FArc::setPoints(PosInt newPoint1, PosInt newPoint2, PosInt newPoint3) {
    elmPoint1 = newPoint1;
    elmPoint2 = newPoint2;
    elmPoint3 = newPoint3;
    computeArc();
    parent->handleChange(this);
  }

  void FArc::setArc(PosInt center, double radius, bool clockwise, double angle1, double angle3) {
    elmXCenter = center.xpos();
    elmYCenter = center.ypos();
    elmRadius = radius;
    elmPhi1 = angle1;
    elmPhi3 = angle3;
    elmClockwise = clockwise;
    if (clockwise) {
      elmPhi2 = (((elmPhi3<elmPhi1)? elmPhi3 : elmPhi3+2*M_PI) + elmPhi1) / 2;
      cout << "PHI2=" << elmPhi2 << " from PHI1=" << elmPhi1 << " PHI3=" << elmPhi3 << endl ;
    } else {
      elmPhi2 = ((elmPhi3>elmPhi1? elmPhi3 : elmPhi3-2*M_PI) + elmPhi1) / 2;
    }
    elmPoint1 = PosInt(static_cast<int>(elmXCenter+radius*cos(elmPhi1)), static_cast<int>(elmYCenter+radius*sin(elmPhi1)));
    elmPoint2 = PosInt(static_cast<int>(elmXCenter+radius*cos(elmPhi2)), static_cast<int>(elmYCenter+radius*sin(elmPhi2)));
    elmPoint3 = PosInt(static_cast<int>(elmXCenter+radius*cos(elmPhi3)), static_cast<int>(elmYCenter+radius*sin(elmPhi3)));
    debugPrint(cout, true, 4); 
  }


  void FArc::draw(FigView* view) {
    double styleLength = elmStyleValue*15;
    double styleLengthScreen = styleLength/scale();
    view->setPaintBuffer(elmPenColor, elmThickness);
    debugPrint(cout, true, 4);
    Array <int, 3> color;
    getPenColorRGB(color);
    int xCenterScreen = static_cast<int>(elmXCenter/scale());
    int yCenterScreen = static_cast<int>(elmYCenter/scale());
    int radiusScreen = static_cast<int>(elmRadius/scale());

    if (elmLineStyle==YaVecLine::solid) {
      view->drawArc(xCenterScreen, yCenterScreen, radiusScreen, elmPhi1, elmPhi3, elmThickness);
    } else {
      double gapPhi, dotPhi, diffPhi, phi1, phi2, phiEnd;
      int activeCnt = 0;
      gapPhi = styleLength/elmRadius;
      dotPhi = 2*M_PI/elmRadius;
      phi1 = elmPhi1;
      // make sure that comparisons work (2*pi wraparound)
      if (elmClockwise) {
        if (elmPhi3>elmPhi1) phi1+=2*M_PI;
      } else {
        if (elmPhi3<elmPhi1) phi1-=2*M_PI;
      }
     
      cout << "1=" << elmPhi1 << ":3=" << elmPhi3 << ":gapPhi=" << gapPhi << endl;

      // if neither dashed nor dotted the following will be overwritten anyway!
      diffPhi = elmLineStyle==YaVecLine::dashed ? gapPhi : dotPhi; 
      while (elmClockwise? phi1>elmPhi3 : phi1<elmPhi3) {
        if ( elmLineStyle!=YaVecLine::dashed && elmLineStyle!=YaVecLine::dotted) {
          if (elmLineStyle==YaVecLine::dash_dotted) {
            diffPhi = activeCnt==0 ? gapPhi : dotPhi;
            if (++activeCnt > 1) activeCnt=0;
          } else if (elmLineStyle==YaVecLine::dash_double_dotted) {
            diffPhi = activeCnt==0 ? gapPhi : dotPhi;
            if (++activeCnt > 2) activeCnt=0;
          } else if (elmLineStyle==YaVecLine::dash_triple_dotted) {
            diffPhi = activeCnt==0 ? gapPhi : dotPhi;
            if (++activeCnt > 3) activeCnt=0;
          }
        }
        phi2 = phi1 + (elmClockwise? (-diffPhi) : diffPhi);
        view->drawArc(xCenterScreen, yCenterScreen, radiusScreen, phi1, phi2, elmThickness);
        phi1 = phi2 + (elmClockwise? (-gapPhi) : gapPhi);;
      }
    }
    if (elmIsPieWedge) {
      view->drawLine(PosInt(xCenterScreen, yCenterScreen), elmPoint1/scale(), elmThickness, color, elmLineStyle, styleLengthScreen);
      view->drawLine(PosInt(xCenterScreen, yCenterScreen), elmPoint3/scale(), elmThickness, color, elmLineStyle, styleLengthScreen);
    }
    view->clrPaintBuffer();
  }


  void FArc::saveElm(ofstream &fig_file) {
    vector<PosInt>::iterator points_iter;
  
    fig_file << "5 " << (elmIsPieWedge? "2 " : "1 ") << elmLineStyle << " " << elmThickness << " "
             << elmPenColor << " " << elmFillColor << " " << elmDepth
             << " -1 " << elmAreaFill << " " << elmStyleValue << " 0 0 " << (forwardArrow()? 1 : 0) << " "
             << (backwardArrow()? 1 : 0) << " " << elmXCenter << " " << elmYCenter;
    fig_file << " " << elmPoint1.xpos() << " " << elmPoint1.ypos() << " " << elmPoint2.xpos() << " "
             << elmPoint2.ypos() << " " << elmPoint3.xpos() << " " << elmPoint3.ypos() << endl;

    if (forwardArrow()) {
      fig_file << forwardArrowString() << endl;
    }
    if (backwardArrow()) {
      fig_file << backwardArrowString() << endl;
    }
  }

  void FArc::getPoints(vector<PosInt> &points, bool hierarchical, bool withCompounds) {
    points.push_back(elmPoint1);
    points.push_back(elmPoint2);
    points.push_back(elmPoint3);
  }

  void FArc::getElmNearPos(PosInt pos, int fuzzyFact, bool hierarchical, bool withCompounds,
                               list<YaVecElmHit> &hits) {
    vector<PosInt> allPoints;
    getPoints(allPoints, false, false);
  
    int fuzzyRes;
    unsigned int i;
    for (i=0; i<allPoints.size(); i++) {
      if (checkProximity(pos, allPoints[i], fuzzyFact, fuzzyRes)) {
        YaVecElmHit newHit;
        newHit.elmP = this;
        newHit.distance = fuzzyRes;
        newHit.idx = i;
        hits.push_back(newHit);
      }
    }
  }

  void FArc::debugPrint(ostream &dest, bool verbose, int depth) {
    dest << string(depth, ' ') << "Arc " << endl;
    if (verbose) {
      dest << string(depth+4, ' ') << elmPoint1 << " -> " << elmPoint2 << " -> " << elmPoint3 << endl;
      dest << string(depth+4, ' ') << "Center: " << elmXCenter << ":" << elmYCenter << "Radius: " << elmRadius
           << " Direction: " << (elmClockwise? "" : "counter") << "clockwise " << endl << string(depth+4, ' ')
           << " PHI1=" << elmPhi1 << " PHI2=" << elmPhi2  << " PHI3=" << elmPhi3 << endl; 
    }
  }

}
