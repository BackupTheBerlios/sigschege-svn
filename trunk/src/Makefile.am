bin_PROGRAMS = TimingMain
TimingMain_SOURCES = Handle.t config.h Event.h EventList.cpp Layout.cpp LayoutList.h Object.cpp ObjectList.cpp TimingDiagram.cpp TimingMain.cpp Event.cpp EventList.h Layout.h LayoutList.cpp Object.h ObjectList.h TimingDiagram.h TimLabel.h TimLabel.cpp
TimingMain_LDADD = ../EasyVec/src/lib_easyvec.la
TimingMain_CXXFLAGS = $(shell freetype-config --cflags) -Wall -g
TimingMain_LDFLAGS  = $(shell freetype-config --libs)

AM_CPPFLAGS = -I ../EasyVec/src
