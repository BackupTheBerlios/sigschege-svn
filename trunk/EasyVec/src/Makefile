# \file 

# Copyright 2004 by 
#
# This file is part of EasyVec - Vector Figure Creation Library.
# 
# #############################################################################
#
# EasyVec is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2, or (at your option)
# any later version.
# 
# EasyVec is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with the EasyVec sources; see the file COPYING.  
#
# #############################################################################
#
# $Id: $


CXX = $(shell wx-config --cxx) $(shell freetype-config --cflags) -Wall -g 

LDFLAGS = $(shell freetype-config --libs)

PROGRAM = Example
GUI=GUIExample

OBJECTS = EVPosInt.o EasyVecElmPolyline.o EasyVecElmText.o EasyVecElmCompound.o  EasyVec.o EasyVecElm.o
OBJECTS_GUI = $(OBJECTS) GUIExample.o EasyVecVwx.o EasyVecView.o

.SUFFIXES:	.o .cpp .h 

.cpp.o :
	$(CXX) -c `wx-config --cxxflags` -o $@ $<

all:    $(PROGRAM) $(GUI)

$(PROGRAM):	$(OBJECTS) $(PROGRAM).o
	$(CXX) -o $(PROGRAM) $(PROGRAM).o $(OBJECTS) $(LDFLAGS)

$(GUI):	$(OBJECTS_GUI)
	$(CXX) -o $(GUI) $(OBJECTS_GUI) `wx-config --libs`  $(LDFLAGS)

.depend:
	makedepend -f- *.cpp *.h >.depend 2>/dev/null

tags: TAGS

TAGS:
	etags -l c++ *.cpp *.h

clean: 
	rm -f *.o $(PROGRAM) $(GUI) example.fig demogui_result.fig

distclean: clean
	rm -f .depend

sinclude .depend

