// -*- c++ -*-
// \file 
// Copyright 2004, 2005 by Ulf Klaperski
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

#include <fstream>
#include <iostream>
#include <cstdlib>
#include "YaVecText.h"
#include "YaVecFigure.h"
#include <cmath>

using namespace std;

namespace YaVec {

  // TODO: Add dirty flag to avoid excessive updating of geometry information
  //       (so far updateDimensions() is called on each setFont(), setAngle().
  //        mark dirty and update on first call to paint(), getBoundingBox(), etc)
  //       This would probably give some speedup.


  FT_Library  FText::freetype_lib;
  bool FText::freetype_already_initialized = false;
  bool FText::fix_fig2dev_quirk = false;
  bool FText::use_kerning = false; // it seems transfig does not do kerning

  //string FText::gs_fontpath = "/var/lib/defoma/gs.d/dirs/fonts/";
  string FText::gs_fontpath = "/usr/share/fonts/type1/gsfonts/";

  const char* yavec_font_files[] = {
    "n021003l.pfb", // 0 = NimbusRomNo9L-Regu = Times-Roman
    "n021023l.pfb", // 1 = NimbusRomNo9L-ReguItal = Times-Italic
    "n021004l.pfb", //  2 = NimbusRomNo9L-Medi = Times Bold
    "n021024l.pfb", //  3 = NimbusRomNo9L-MediItal = Times Bold Italic
    "a010013l.pfb", //  4 = URWGothicL-Book = AvantGarde Book
    "a010033l.pfb", //  5 = URWGothicL-BookObli = AvantGarde Book Oblique
    "a010015l.pfb", //  6 = URWGothicL-Demi = AvantGarde Demi
    "a010035l.pfb", //  7 = URWGothicL-DemiObli = AvantGarde Demi Oblique
    "b018012l.pfb", //  8 = URWBookmanL-Ligh = Bookman Light
    "b018032l.pfb", //  9 = URWBookmanL-LighItal = Bookman Light Italic
    "b018015l.pfb", // 10 = URWBookmanL-DemiBold = Bookman Demi
    "b018035l.pfb", // 11 = URWBookmanL-DemiBoldItal = Bookman Demi Italic
    "n022003l.pfb", // 12 = NimbusMonL-Regu = Courier
    "n022023l.pfb", // 13 = NimbusMonL-ReguObli = Courier Oblique
    "n022004l.pfb", // 14 = NimbusMonL-Bold = Courier Bold
    "n022024l.pfb", // 15 = NimbusMonL-BoldObli = Courier Bold Oblique
    "n019003l.pfb", // 16 = NimbusSanL-Regu = Helvetica
    "n019023l.pfb", // 17 = NimbusSanL-ReguItal = Helvetica Oblique
    "n019004l.pfb", // 18 = NimbusSanL-Bold = Helvetica Bold
    "n019024l.pfb", // 19 = NimbusSanL-BoldItal = Helvetica Bold Oblique
    "n019043l.pfb", // 20 = NimbusSanL-ReguCond = Helvetica Narrow
    "n019063l.pfb", // 21 = NimbusSanL-ReguCondItal = Helvetica Narrow Oblique
    "n019044l.pfb", // 22 = NimbusSanL-BoldCond = Helvetica Narrow Bold
    "n019064l.pfb", // 23 = NimbusSanL-BoldCondItal = Helvetica Narrow Bold Oblique
    "c059013l.pfb", // 24 = New Century Schoolbook Roman
    "c059033l.pfb", // 25 = New Century Schoolbook Italic
    "c059016l.pfb", // 26 = New Century Schoolbook Bold
    "c059036l.pfb", // 27 = New Century Schoolbook Bold Italic
    "p052003l.pfb", // 28 = URWPalladioL-Roma = Palatino Roman
    "p052023l.pfb", // 29 = URWPalladioL-Ital = Palatino Italic
    "p052004l.pfb", // 30 = URWPalladioL-Bold = Palatino Bold
    "p052024l.pfb", // 31 = URWPalladioL-BoldItal = Palatino Bold Italic
    "s050000l.pfb", // 32 = StandardSymL = Symbol
    "z003034l.pfb", // 33 = URWChanceryL-MediItal = Zapf Chancery Medium Italic
    "d050000l.pfb" // 34 = Zapf Dingbats
  };

  bool FText::initFreetype(void) {
    // just a hack for now - if we need a config it should be read somewhere else
    // otoh the font path should be configured in a global config file
    string confFile = getenv("HOME");
    if (confFile[confFile.length()-1] != '/') confFile += "/";
    confFile += ".YaVec";
    ifstream confFileStream;
    char buf[999];
    string line, var, val;
    int eq_pos;
    confFileStream.open(confFile.c_str(), ios::in);
    while (confFileStream.getline(buf, 999)) {
      line = buf;
      eq_pos = line.find('=');
      if (!eq_pos) continue;
      val = line.substr(eq_pos+1);
      var = line.substr(0, eq_pos);
      if (var == "FONTPATH") {
        gs_fontpath = val;
        cout << "SETTING FP=" << gs_fontpath << endl; 
      }
    }
    confFileStream.close();
    confFileStream.clear();

    if (freetype_already_initialized) return true;
    int freetype_fail = FT_Init_FreeType( &freetype_lib );
    if (freetype_fail==0) {
      freetype_already_initialized = true;
      return true;
    } else {
      return false;
    }
  }



  PosInt FText::drawOrCalc(FigView* view, bool noUpdate) {
    string::iterator text_iter;
    char cur_char;
    FT_UInt glyph_index, old_glyph_i; // index of current and previous glyph - previous is needed for kerning
    int ft_fail; // indicator that the previous freetype operation failed
    FT_GlyphSlot  glyphSlot;
    FT_Glyph  glyph;
    int resolution;
    PosInt char_origin;
    PosInt char_originPrec; // char_origin in full precision to avoid rounding errors
    PosInt upperLeft; // corner of the (freshly calculated) bounding box
    PosInt lowerRight;
    FT_Vector kerning; // the kerning information from freetype - only used if use_kerning is true
    int xKerning, yKerning; // x and y portion of kerning for rotated text
    int newHeight, newWidth;
    double angleRad = cAngle*M_PI/180; 

    newWidth = newHeight = 0;
  
    if (view) {
      resolution = figure->getScreenDpi();    
    } else {
      resolution = figure->getFileDPi();
      if (fix_fig2dev_quirk) {
        resolution *= 9;
        resolution /= 10;
      }
    }
  
    ft_fail = FT_Set_Char_Size(face,    /* handle to face object */
                               elmSize*64,   /* char_width in 1/64th of points  */
                               elmSize*64,   /* char_height in 1/64th of points */
                               resolution,     /* horizontal device resolution    */
                               resolution);    /* vertical device resolution      */
    if (ft_fail!=0) cerr << "Setting face size failed" << endl;

    if (view==0 && !noUpdate) textWidth = textHeight = 0;

    old_glyph_i = 0;
    kerning.x = kerning.y = 0;
    xKerning = yKerning = 0;
  
    char_origin = view ? elmOrigin/figure->scale() : elmOrigin;
    char_originPrec = char_origin << 6;
    BBoxUpperleft = char_origin;
    BBoxLowerRight = char_origin;
  
    FT_Matrix mat;
    FT_BBox   bbox;
    if (cAngle!=0) {
      mat.xx = static_cast<int>(65536*cos(angleRad));
      mat.xy = static_cast<int>(-65336*sin(angleRad));
      mat.yx = static_cast<int>(65336*sin(angleRad));
      mat.yy = static_cast<int>(65536*cos(angleRad));
      FT_Set_Transform(face, &mat, 0);
    }

    for ( text_iter = elmText.begin(); text_iter != elmText.end(); ++text_iter ) {
      cur_char = *text_iter;
      glyph_index = FT_Get_Char_Index(face, cur_char);
      ft_fail = FT_Load_Glyph( face, glyph_index, FT_LOAD_NO_HINTING );
      if (view) ft_fail |= FT_Render_Glyph( face->glyph, FT_RENDER_MODE_MONO );
      if (ft_fail!=0) cerr << "Glyph loading failed for char " << *text_iter << glyph_index<< endl;
      glyphSlot = face->glyph;
      ft_fail = FT_Get_Glyph( face->glyph, &glyph );
    
      if (old_glyph_i && glyph_index && use_kerning) {
        FT_Get_Kerning(face, old_glyph_i, glyph_index, FT_KERNING_DEFAULT, &kerning);
        xKerning = static_cast<int>(kerning.x*cos(angleRad));
        yKerning = static_cast<int>(kerning.x*sin(angleRad));
      }
      FT_Glyph_Get_CBox(  glyph, ft_glyph_bbox_pixels, &bbox );
      upperLeft = char_origin + PosInt(xKerning>>6, -yKerning>>6) + PosInt(static_cast<int>(bbox.xMin), static_cast<int>(-bbox.yMax));
      lowerRight = char_origin + PosInt(xKerning>>6, -yKerning>>6) + PosInt(static_cast<int>(bbox.xMax), static_cast<int>(-bbox.yMin));
#if 0
      // debug
      cout << cur_char << ":ORIGIN=" << char_origin << " UL=" << upperLeft << " LR=" << lowerRight << endl;
#endif
      // adapt bounding box to include this character
      BBoxUpperleft = min_coords(BBoxUpperleft, upperLeft);
      BBoxLowerRight = max_coords(BBoxLowerRight, lowerRight);
      Array <int, 3> color;
      getPenColorRGB(color);
#if 0
      if (view) { //debug: draw bounding boxes around characters

        view->drawLine(upperLeft, lowerRight, 1, color, 0, 8); 
        view->drawLine(upperLeft, PosInt(lowerRight.xpos(), upperLeft.ypos()), 1, color, 0, 8); 
        view->drawLine(PosInt(lowerRight.xpos(), upperLeft.ypos()), lowerRight, 1, color, 0, 8); 
        view->drawLine(upperLeft, PosInt(upperLeft.xpos(), lowerRight.ypos()), 1, color, 0, 8); 
        view->drawLine(PosInt(upperLeft.xpos(), lowerRight.ypos()), lowerRight, 1, color, 0, 8);
      }
#endif
      if (view) {
        FT_Bitmap cbitmap;
        cbitmap = glyphSlot->bitmap;
        view->drawChar(char_origin+PosInt(glyphSlot->bitmap_left+(xKerning>>6), -glyphSlot->bitmap_top-(yKerning>>6)),
                       cbitmap.rows, cbitmap.width, cbitmap.pitch, cbitmap.buffer, color);
#if 0
        // debug output
        cout << ">" << cur_char << ": adv=" << xAdvance << " bitmap_top=" << glyphSlot->bitmap_top << " cbitmap.width=" << cbitmap.width << endl;
        cout << cur_char << ">" << xKerning << ":" << yKerning << endl;
#endif
      }
#if 0
      // debug output
      cout << cur_char << ": glyphSlot->bitmap_top=" << glyphSlot->bitmap_top << " glyphSlot->metrics.height=" << glyphSlot->metrics.height 
           << " bbox.yMax=" << bbox.yMax << " bbox.yMin=" << bbox.yMin << endl;
#endif
      char_originPrec += PosInt(static_cast<int>(glyphSlot->advance.x+xKerning), -static_cast<int>(glyphSlot->advance.y+yKerning));
      char_origin = char_originPrec >> 6;
      newWidth += (glyphSlot->metrics.horiAdvance+kerning.x) >> 6; 
      if (glyphSlot->metrics.height/64>newHeight) newHeight = glyphSlot->metrics.height/64;
      old_glyph_i = glyph_index;
    }

#if 0
    // debug output
    cout << "ANGLE:" << cAngle << " newWidth=" << newWidth << " newHeight=" << newHeight << endl;
#endif
  
    if (!noUpdate) {
      textWidth = newWidth;
      textHeight = newHeight;
    }

    return (PosInt(newWidth, newHeight));
  }

  void FText::draw(FigView* view) {
    drawOrCalc(view);
  }


  bool FText::initFText() {
    bool success;
    elmFont = 0;
    elmSize = 18;
    elmOrigin = PosInt(300, 300);
    elmJustification = left;
    cAngle = 0.0;
    success = setFont(0);  
    // updateDimensions(); ... is already done in setFont!
    return success;
  }

  bool FText::setAngle(double angle) {
    cAngle = angle;
    updateDimensions();
    return true;
  }


  FText::FText() {
    initFText();
  }

  FText::FText(FCompound* parent_compound, FFigure* figure_compound)
    : YaVecElm(parent_compound, figure_compound)
  {
    initFText();
  };


  void FText::getBoundingBox(PosInt &upper_left, PosInt &lower_right) {
    upper_left  = BBoxUpperleft;
    lower_right = BBoxLowerRight;
  }

  void FText::getTextBox(PosInt &lowerLeft, PosInt &upperRight) {
    //double angleRad = cAngle*M_PI/180; 

    //TODO: add proper calculation of box
    //   lowerLeft = elmOrigin;
    //   upperRight = elmOrigin+PosInt(static_cast<int>(textWidth*cos(angleRad)-textHeight*sin(angleRad)),
    //                                   static_cast<int>(-textWidth*sin(angleRad)-textHeight*cos(angleRad)));
  }

  bool FText::setText(const string &new_text) {
    elmText = new_text;
    updateDimensions();
    return true;
  }

  bool FText::setFont(int new_font) {
    int ft_fail;
    if (new_font>=0 && new_font<34) {
      elmFont = new_font;
      string font = gs_fontpath + string(yavec_font_files[elmFont]);
      string afm = font;
      afm.replace(afm.length()-3, 3, "afm");
      ft_fail = FT_New_Face(freetype_lib, font.c_str(), 0, &face );
      if (ft_fail!=0) cerr << "Face creation failed. Fontpath correct?" << endl;
      ft_fail = FT_Attach_File(face, afm.c_str() );
      if (ft_fail!=0) cerr << "Reading kerning failed. No AFM? " << afm << endl;
      updateDimensions();
      return ft_fail==0;
    } else return false;
  }


  bool FText::setSize(int new_size) {
    elmSize = new_size;
    updateDimensions();
    return true;
  }

  bool FText::setOrigin(PosInt new_origin) {
    elmOrigin = new_origin;
    return true;
  }

  int FText::sizeForBox(int height, int width, bool allowIncrease) {
    int origSize=elmSize;
    PosInt bBox(textWidth, textHeight);
    int newSize;
  
    while ((bBox.xpos()>width || bBox.ypos()>height) && elmSize>0) {
      elmSize--;
      bBox=drawOrCalc(0, true); // calculate only
    }
    newSize=elmSize;
    elmSize=origSize;
    return newSize;
  }


  void FText::saveElm(ofstream &fig_file) {
    vector<PosInt>::iterator points_iter;

    fig_file << "4 " << elmJustification << " " << elmPenColor << " " << elmDepth
             << " 0 " << elmFont << " " << elmSize << " " << cAngle*M_PI/180 << " 4 " << textHeight << " "
             << textWidth << " " << elmOrigin.xpos() << " " << elmOrigin.ypos() << " "<< elmText
             << "\\001" << endl;
  }

  void FText::getPoints(vector<PosInt> &points, bool hierarchical, bool withCompounds) {
    // TODO: add other corner points
    points.push_back(elmOrigin);
  }


  void FText::debugPrint(ostream &dest, bool verbose, int depth) {
    dest << string(depth, ' ') << "Text " << endl;
    if (verbose) {
      dest << string(depth+4, ' ') << elmText << endl;
    }
  }

}
