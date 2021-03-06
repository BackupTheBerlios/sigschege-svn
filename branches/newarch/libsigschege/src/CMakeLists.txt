
include(FindFreetype)

find_package(Freetype REQUIRED)

IF (XERCESC_INCLUDE_DIR)
  # Already in cache, be silent.
  SET(XERCESC_FIND_QUIETLY TRUE)
ENDIF (XERCESC_INCLUDE_DIR)

FIND_PATH(XERCESC_INCLUDE_DIR xercesc/util/XercesVersion.hpp)

SET(XERCESC_NAMES xerces-c xerces-c_2)
FIND_LIBRARY(XERCESC_LIBRARY NAMES ${XERCESC_NAMES})

# Handle the QUIETLY and REQUIRED arguments and set XERCESC_FOUND to
# TRUE if all listed variables are TRUE.
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(
  XERCESC DEFAULT_MSG
  XERCESC_LIBRARY XERCESC_INCLUDE_DIR
)

IF(XERCESC_FOUND)
  SET( XERCESC_LIBRARIES ${XERCESC_LIBRARY} )
ELSE(XERCESC_FOUND)
  SET( XERCESC_LIBRARIES )
ENDIF(XERCESC_FOUND)

set(LIBSIGSCHEGE_SRC
SigschegeCommon.h
Handle.h
EventList.h EventList.cpp
LayoutObject.h LayoutObject.cpp
State.h State.cpp
Event.h Event.cpp
TimeMarker.h TimeMarker.cpp
TimingObject.h TimingObject.cpp
TimLabel.h TimLabel.cpp
TimSchedule.h TimSchedule.cpp
TimSignal.h TimSignal.cpp
TimTime.h TimTime.cpp
TimingDiagram.h TimingDiagram.cpp
TimList.h TimList.cpp
TimText.h TimText.cpp
)

include_directories(. ${YaVec_SOURCE_DIR}/src ${FREETYPE_INCLUDE_DIR_freetype2} ${XERCESC_INCLUDE_DIR})

add_library(sigschege SHARED ${LIBSIGSCHEGE_SRC})

