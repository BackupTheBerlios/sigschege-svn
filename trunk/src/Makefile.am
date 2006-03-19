INCLUDES = $(shell wx-config --cxxflags) $(shell freetype-config --cflags)

bin_PROGRAMS = TimingMain sigschege
TimingMain_SOURCES = Handle.t config.h Event.h Event.cpp EventList.h EventList.cpp TimingDiagram.cpp \
    TimingMain.cpp TimingDiagram.h TimLabel.h TimLabel.cpp LayoutObject.h LayoutObject.cpp \
    TimingObject.h TimingObject.cpp TimSignal.h TimSignal.cpp TimList.cpp TimList.h TimTime.h \
    TimTime.cpp TimeMarker.h TimeMarker.cpp State.h State.cpp TimText.h TimText.cpp
TimingMain_LDADD = ../YaVec/src/lib_yavec.la
TimingMain_CPPFLAGS = -Wall -g
TimingMain_LDFLAGS  = $(shell freetype-config --libs)

sigschege_SOURCES = Handle.t config.h Event.h Event.cpp EventList.h EventList.cpp TimingDiagram.cpp \
    Sigschege.cpp TimingDiagram.h TimLabel.h TimLabel.cpp LayoutObject.h LayoutObject.cpp TimingObject.h \
    TimingObject.cpp TimSignal.h TimSignal.cpp TimList.cpp TimList.h TimTime.h TimeMarker.h TimeMarker.cpp \
    TimTime.cpp State.h State.cpp PyTimingDiagram.cpp PyTimingDiagram.h TimText.h TimText.cpp
sigschege_LDADD = ../YaVec/src/lib_yavec.la
sigschege_CPPFLAGS = -Wall -g
sigschege_LDFLAGS  = $(shell freetype-config --libs) -lpython2.4

AM_CPPFLAGS = -I ../YaVec/src -I @INC_PYTHON@
