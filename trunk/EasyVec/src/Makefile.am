lib_LTLIBRARIES = lib_easyvec.la
lib_easyvec_la_SOURCES = EVPosInt.cpp EVPosInt.h EasyVecLine.cpp EasyVecLine.h EasyVecArrow.cpp EasyVecArrow.h EasyVecPolyline.cpp EasyVecPolyline.h  EasyVecText.cpp EasyVecText.h EasyVecCompound.cpp EasyVecCompound.h EasyVecFigure.cpp EasyVecFigure.h EasyVecElm.cpp EasyVecElm.h EasyVecBox.cpp EasyVecBox.h EasyVecView.cpp EasyVecView.h
lib_easyvec_la_CXXFLAGS = $(shell wx-config --cxxflags) $(shell freetype-config --cflags) -Wall -g
lib_easyvec_la_LDFLAGS = $(shell freetype-config --libs)

bin_PROGRAMS = Example GUIExample
Example_SOURCES =  Example.cpp
Example_LDADD = lib_easyvec.la
Example_CXXFLAGS = $(shell wx-config --cxxflags) $(shell freetype-config --cflags) -Wall -g

GUIExample_SOURCES =  GUIExample.cpp GUIExample.h EasyVecVwx.cpp EasyVecVwx.h 
GUIExample_LDADD = lib_easyvec.la
GUIExample_CXXFLAGS = $(shell wx-config --cxxflags) $(shell freetype-config --cflags) -Wall -g
GUIExample_LDFLAGS = $(shell wx-config --libs)
