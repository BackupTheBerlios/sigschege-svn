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


#include "TimingDiagram.h"
#include <stdio.h>
#include <fstream>
#include <iostream>

using namespace std;
using namespace YaVec;

TimingDiagram::TimingDiagram(double startTime, double endTime) : TimList(), cYaVec() {
  setCompound(cYaVec.compound());
  setTimeRange(startTime, endTime);
}

TimingDiagram::~TimingDiagram() {
}


/*!
 * Export the Timingdiagram to a xfig-format
 * \param file XFig File Name
 */
void TimingDiagram::exportFig(string file) {
  paint();
  cYaVec.save(file);
}

/*!
 * Export the Timingdiagram to an encapsulated postscript
 * \param file EPS File Name
 */
void TimingDiagram::exportEPS(string file) {
  paint();
  cYaVec.exportFig2dev("eps", file);
}

/*!
 * Export the Timingdiagram to any format
 * \param file Picture file name.
 * \param format Format of the file, must be supported by fig2dev.
 */
void TimingDiagram::exportAny(string file, string format) {
  paint();
  cYaVec.exportFig2dev(format, file);
}

bool TimingDiagram::save(std::string filename, bool overwrite) {
  ofstream ssg_file;
  vector< Handle<TimingObject> >::iterator TimingObjectIter;
  
  ssg_file.open(filename.c_str(), ios::out);
  //if (!ssg_file) return false;
  ssg_file << "<?xml version=\"1.0\"?>" << endl;
  ssg_file << "<!DOCTYPE sigschege SYSTEM \"sigschege.dtd\">" << endl;
  ssg_file << "<sigschege>" << endl;
  for (TimingObjectIter = cLayoutList.begin(); TimingObjectIter != cLayoutList.end(); TimingObjectIter++){
    TimingObjectIter->Object()->save(ssg_file);
  }
  ssg_file << "</sigschege>" << endl;
  ssg_file.close();
  return true;
}

string TimingDiagram::xml_gettext(DOMNode *parent) {
  string result;
  DOMNode *child;
  for (child = parent->getFirstChild(); child != 0; child=child->getNextSibling()) {
    cout << "XGT:" << XMLString::transcode(child->getNodeName()) <<  endl;
    if (string(XMLString::transcode(child->getNodeName()))=="#cdata-section" || string((XMLString::transcode(child->getNodeName())))=="#text")
      {
	result = XMLString::transcode(child->getNodeValue());
	cout << "STRING=" << result <<  endl;
      }
  }
  return result;
}

bool TimingDiagram::load(std::string filename) {
  ifstream ssg_file;
  try {
    XMLPlatformUtils::Initialize();
  } catch(const XMLException &toCatch) {
    cerr << "Error during Xerces-c Initialization.\n"
	 << "  Exception message:"
	 << XMLString::transcode(toCatch.getMessage()) <<  endl;
    return false;
  }
  
  vector< Handle<TimingObject> >::iterator TimingObjectIter;

  XercesDOMParser *parser = new XercesDOMParser;
  parser->setValidationScheme(XercesDOMParser::Val_Always);
  parser->setDoNamespaces(false);
  parser->setDoSchema(false);
  parser->setValidationSchemaFullChecking(false);
  parser->setCreateEntityReferenceNodes(false);

  try {
    parser->parse(filename.c_str());
  } catch (const OutOfMemoryException&) {
    cerr << "OutOfMemoryException" <<  endl;
    return false;
  } catch (const XMLException& e) {
    cerr << "An error occurred during parsing" << endl <<"Error message: "
	 << XMLString::transcode(e.getMessage()) << endl;
    return false;
  } catch (const DOMException& e) {
    const unsigned int maxChars = 2047;
    XMLCh errText[maxChars + 1];
    
    cerr << "DOM Error during parsing " << filename << endl
	 << "DOMException code:  " << e.code <<  endl;
      
    if (DOMImplementation::loadDOMExceptionMsg(e.code, errText, maxChars))
      cerr << "Error message is: " << XMLString::transcode(errText) <<  endl;
    return false;
  } catch (...) {
    cerr << "An unknown error occurred during parsing" << endl;
    return false;
  }
  
  DOMNode *doc = parser->getDocument();
  
  if (doc) {
    char *name = XMLString::transcode(doc->getNodeName());
    DOMNode *child;
    DOMNode *child2;
    DOMNode *child3;
    DOMNode *child4;
    DOMNode *sigschege = 0;
    string ptext;

    // get the top level node
    for (child = doc->getFirstChild(); child != 0; child=child->getNextSibling()) {
      cout << XMLString::transcode(child->getNodeName()) <<  endl;
      if (child->getNodeType() == DOMNode::ELEMENT_NODE) {
        sigschege = child;
      }
    }
    
    if (sigschege) {
      for (child2 = sigschege->getFirstChild(); child2 != 0; child2=child2->getNextSibling())
	{
	  if (child2->getNodeType() == DOMNode::ELEMENT_NODE) {
            name = XMLString::transcode(child2->getNodeName());
            string nameStr(name);
            if (nameStr=="signal") 
	      {
                Handle<TimSignal> Signal1 = createSignal("0", false);
                for (child3 = child2->getFirstChild(); child3 != 0; child3=child3->getNextSibling()) {
                  if (child3->getNodeType() == DOMNode::ELEMENT_NODE) {
                    if (string(XMLString::transcode(child3->getNodeName()))=="primarytext") {
		      ptext = xml_gettext(child3);
		      Signal1->setText(ptext);
		    } else if (string(XMLString::transcode(child3->getNodeName()))=="initialstate") {
		      Signal1->setInitialState(xml_gettext(child3));
                    } else if (string(XMLString::transcode(child3->getNodeName()))=="event") {
		      double evtime = 0.0;
		      string state = "";
		      for (child4 = child3->getFirstChild(); child4 != 0; child4=child4->getNextSibling()) {
			if (string(XMLString::transcode(child4->getNodeName()))=="time") {
			  ptext = xml_gettext(child4);
			  evtime = atof(ptext.c_str());
			} else if (string(XMLString::transcode(child4->getNodeName()))=="state") {
			  state = ptext = xml_gettext(child4);
			}
		      }
		      Signal1->createEvent(state, evtime);
                    }
                  }
                }
                addLast(Signal1.Object());
              }
            if (nameStr=="timescale") 
	      {
                Handle<TimTime> Time1 = createTime(0.0, 0.0, 0.0);
                for (child3 = child2->getFirstChild(); child3 != 0; child3=child3->getNextSibling()) {
                  if (child3->getNodeType() == DOMNode::ELEMENT_NODE) {
                    if (string(XMLString::transcode(child3->getNodeName()))=="primarytext") {
		      ptext = xml_gettext(child3);
		      Time1->setText(ptext);
		    }
		  }		
		}
                addLast(Time1.Object());
	      }
            if (nameStr=="label") 
	      {
                Handle<TimLabel> Label1 = createLabel();
                for (child3 = child2->getFirstChild(); child3 != 0; child3=child3->getNextSibling()) {
                  if (child3->getNodeType() == DOMNode::ELEMENT_NODE) {
                    if (string(XMLString::transcode(child3->getNodeName()))=="primarytext") {
		      ptext = xml_gettext(child3);
		      Label1->setText(ptext);
		    }
		  }		
		}
                addLast(Label1.Object());
	      }
          }
        }
    }
    
    if (doc->hasAttributes()) {
      DOMNamedNodeMap *pAttributes = doc->getAttributes();
      int nSize = pAttributes->getLength();
      for (int i=0;i<nSize;i++) {
        DOMAttr *pAttributeNode = (DOMAttr*) pAttributes->item(i);
        // get attribute name
        char *name = XMLString::transcode(pAttributeNode->getName());
        cout << "\t" << name << "=";
        XMLString::release(&name);
        
        // get attribute type
        name = XMLString::transcode(pAttributeNode->getValue());
        cout << name <<  endl;
        XMLString::release(&name);
      }
    }
  }

  delete parser;
  XMLPlatformUtils::Terminate();
  return true;
}




