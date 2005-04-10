lib_LTLIBRARIES = lib_yavec.la
lib_yavec_la_SOURCES = EVPosInt.cpp EVPosInt.h YaVecLine.cpp YaVecLine.h YaVecArrow.cpp YaVecArrow.h YaVecPolyline.cpp YaVecPolyline.h  YaVecText.cpp YaVecText.h YaVecCompound.cpp YaVecCompound.h YaVecFigure.cpp YaVecFigure.h YaVecElm.cpp YaVecElm.h YaVecBox.cpp YaVecBox.h YaVecArc.cpp YaVecArc.h YaVecView.cpp YaVecView.h
lib_yavec_la_CXXFLAGS = $(shell wx-config --cxxflags) $(shell freetype-config --cflags) -Wall -g
lib_yavec_la_LDFLAGS = $(shell freetype-config --libs)

bin_PROGRAMS = Example GUIExample
Example_SOURCES =  Example.cpp
Example_LDADD = lib_yavec.la
Example_CXXFLAGS = $(shell wx-config --cxxflags) $(shell freetype-config --cflags) -Wall -g

GUIExample_SOURCES =  GUIExample.cpp GUIExample.h YaVecVwx.cpp YaVecVwx.h 
GUIExample_LDADD = lib_yavec.la
GUIExample_CXXFLAGS = $(shell wx-config --cxxflags) $(shell freetype-config --cflags) -Wall -g
GUIExample_LDFLAGS = $(shell wx-config --libs)
