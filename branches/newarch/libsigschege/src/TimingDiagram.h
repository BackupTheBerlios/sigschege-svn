// -*- c++ -*-
// \file 
// Copyright 2004 - 2008 by Ingo Hinrichs, Ulf Klaperski
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

#ifndef _H_TIMING
#define _H_TIMING

#include "SigschegeCommon.h"
#include "TimList.h"
#include "TimLabel.h"
#include "TimSignal.h"
#include "TimTime.h"
#include "Handle.h"
#include <string>
#include <YaVecFigure.h>
#include "EventList.h"
#include <vector>
#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/sax/ErrorHandler.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>
#include <xercesc/dom/DOMWriter.hpp>

#include <xercesc/framework/StdOutFormatTarget.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/util/XMLUni.hpp>
#include <iostream>
#include <xercesc/util/OutOfMemoryException.hpp>

// The XERCES_CPP_NAMESPACE_USE macro causes parsing errors in eclipse CDT
using namespace XERCES_CPP_NAMESPACE;

//! The TimingDiagram Class is the toplevel class that contains the layout and the objects of a timing diagram.
/*!
 * This class implements a timing diagram. It is derived from the \c TimList class which
 * implements a vertical list of elements (like signal, time scale, ...).
 * This class additionally holds the \c FFigure object and implements functions for saving and exporting.
 */

class TimingDiagram : public TimList {
public:
  /// The standard constructor
  TimingDiagram(double newStartTime=0.0, double newEndTime=100.0);

  /// The standard destructor
  ~TimingDiagram();

  /// Export the Timing Diagram to an xfig file
  void exportFig(std::string file);

  /// Export the Timing Diagram to an encapsulated postscript (EPS)
  void exportEPS(std::string file);

  /// Export the Timing Diagram to any picture format (supported by fig2dev)
  void exportAny(std::string file, std::string format);

  /// Save the timing diagram in native sigschege format (XML).
  bool save(std::string filename, bool overwrite=false);

  /// Load a timing diagram in native sigschege format.
  bool load(std::string filename);

  /// TODO
  YaVec::FFigure cYaVec;

private:

  std::string xml_gettext(DOMNode *parent);

};
#endif // _H_TIMING
