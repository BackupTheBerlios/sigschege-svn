bin_PROGRAMS = TimingMain sigschege
TimingMain_SOURCES = Handle.t config.h Event.h EventList.cpp TimingDiagram.cpp TimingMain.cpp Event.cpp EventList.h TimingDiagram.h TimLabel.h TimLabel.cpp LayoutObject.h LayoutObject.cpp TimSignal.h TimSignal.cpp TimList.cpp TimList.h TimTime.h TimTime.cpp State.h State.cpp
TimingMain_LDADD = ../EasyVec/src/lib_easyvec.la
TimingMain_CXXFLAGS = $(shell freetype-config --cflags) -Wall -g
TimingMain_LDFLAGS  = $(shell freetype-config --libs)

sigschege_SOURCES = Handle.t config.h Event.h EventList.cpp TimingDiagram.cpp Sigschege.cpp Event.cpp EventList.h TimingDiagram.h TimLabel.h TimLabel.cpp LayoutObject.h LayoutObject.cpp TimSignal.h TimSignal.cpp TimList.cpp TimList.h TimTime.h TimTime.cpp State.h State.cpp
sigschege_LDADD = ../EasyVec/src/lib_easyvec.la
sigschege_CXXFLAGS = $(shell freetype-config --cflags) -Wall -g
sigschege_LDFLAGS  = $(shell freetype-config --libs) -lpython2.3

AM_CPPFLAGS = -I ../EasyVec/src -I @INC_PYTHON@
