lib_LTLIBRARIES = lib_easyvec.la
lib_easyvec_la_SOURCES = EVPosInt.cpp EVPosInt.h EasyVecElmPolyline.cpp EasyVecElmPolyline.h  EasyVecElmText.cpp EasyVecElmText.h EasyVecElmCompound.cpp EasyVecElmCompound.h EasyVec.cpp EasyVec.h EasyVecElm.cpp EasyVecElm.h
lib_easyvec_la_CXXFLAGS = $(shell wx-config --cxxflags) $(shell freetype-config --cflags) -Wall -g
lib_easyvec_la_LDFLAGS = $(shell freetype-config --libs)

bin_PROGRAMS = Example GUIExample
Example_SOURCES =  Example.cpp
Example_LDADD = lib_easyvec.la
Example_CXXFLAGS = $(shell wx-config --cxxflags) $(shell freetype-config --cflags) -Wall -g

GUIExample_SOURCES =  GUIExample.cpp GUIExample.h EasyVecVwx.cpp EasyVecVwx.h EasyVecView.cpp EasyVecView.h
GUIExample_LDADD = lib_easyvec.la
GUIExample_CXXFLAGS = $(shell wx-config --cxxflags) $(shell freetype-config --cflags) -Wall -g
GUIExample_LDFLAGS = $(shell wx-config --libs)