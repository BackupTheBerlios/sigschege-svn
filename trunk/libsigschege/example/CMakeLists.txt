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

include_directories(. ${XERCESC_INCLUDE_DIR} ${FREETYPE_INCLUDE_DIR_freetype2} ${libsigschege_SOURCE_DIR}/src ${YaVec_SOURCE_DIR}/src)

add_executable(TimingMain TimingMain.cpp)

target_link_libraries(TimingMain yavec sigschege ${XERCESC_LIBRARIES})