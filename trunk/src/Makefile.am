bin_PROGRAMS = TimingMain
TimingMain_SOURCES = Handle.t config.h Event.h EventList.cpp TimingDiagram.cpp TimingMain.cpp Event.cpp EventList.h TimingDiagram.h TimLabel.h TimLabel.cpp LayoutObject.h LayoutObject.cpp TimSignal.h TimSignal.cpp
TimingMain_LDADD = ../EasyVec/src/lib_easyvec.la
TimingMain_CXXFLAGS = $(shell freetype-config --cflags) -Wall -g
TimingMain_LDFLAGS  = $(shell freetype-config --libs)

AM_CPPFLAGS = -I ../EasyVec/src
