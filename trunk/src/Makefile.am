INCLUDES = $(shell wx-config --cxxflags) $(shell freetype-config --cflags)

AM_CPPFLAGS = -I ../YaVec/src -I @INC_PYTHON@
AM_CXXFLAGS = -I ../YaVec/src -I @INC_PYTHON@

bin_PROGRAMS = TimingMain sigschege gsigschege
TimingMain_SOURCES = Handle.t config.h Event.h Event.cpp EventList.h EventList.cpp TimingDiagram.cpp \
    TimingMain.cpp TimingDiagram.h TimLabel.h TimLabel.cpp LayoutObject.h LayoutObject.cpp \
    TimingObject.h TimingObject.cpp TimSignal.h TimSignal.cpp TimList.cpp TimList.h TimTime.h \
    TimTime.cpp TimeMarker.h TimeMarker.cpp State.h State.cpp TimText.h TimText.cpp TimSchedule.h TimSchedule.cpp
TimingMain_LDADD = ../YaVec/src/lib_yavec.la
TimingMain_CPPFLAGS = -Wall -g -DwxUSE_STD_STRING=1 -DwxUSE_UNICODE=0
TimingMain_LDFLAGS  = $(shell freetype-config --libs)

general_sources = Handle.t config.h Event.h Event.cpp EventList.h EventList.cpp TimingDiagram.cpp \
    TimingDiagram.h TimLabel.h TimLabel.cpp LayoutObject.h LayoutObject.cpp TimingObject.h \
    TimingObject.cpp TimSignal.h TimSignal.cpp TimList.cpp TimList.h TimTime.h TimeMarker.h TimeMarker.cpp \
    TimTime.cpp State.h State.cpp TimText.h TimText.cpp TimSchedule.h TimSchedule.cpp

sigschege_SOURCES = Sigschege.cpp PyTimingDiagram.cpp PyTimingDiagram.h $(general_sources)
sigschege_LDADD = ../YaVec/src/lib_yavec.la
sigschege_CPPFLAGS = -Wall -g
sigschege_LDFLAGS  = $(shell freetype-config --libs) -lpython2.5

gsigschege_SOURCES = GSigschege.cpp $(general_sources) ../YaVec/src/YaVecVwx.cpp ../YaVec/src/YaVecVwx.h
gsigschege_LDADD = ../YaVec/src/lib_yavec.la
gsigschege_CPPFLAGS = -Wall -g
gsigschege_LDFLAGS  = $(shell freetype-config --libs)  $(shell wx-config --libs)
