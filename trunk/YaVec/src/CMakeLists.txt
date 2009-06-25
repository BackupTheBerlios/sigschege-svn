include(FindFreetype)

find_package(Freetype REQUIRED)

include_directories(${FREETYPE_INCLUDE_DIR_freetype2})

include(FindwxWidgets)

find_package(wxWidgets)

set(YAVEC_SRC
  YVPosInt.cpp YVPosInt.h YaVecLine.cpp YaVecLine.h
  YaVecArrow.cpp YaVecArrow.h YaVecPolyline.cpp
  YaVecPolyline.h  YaVecText.cpp YaVecText.h
  YaVecCompound.cpp YaVecCompound.h YaVecFigure.cpp
  YaVecFigure.h YaVecElm.cpp YaVecElm.h YaVecBox.cpp
  YaVecBox.h YaVecArc.cpp YaVecArc.h
  YaVecView.cpp YaVecView.h YaVecUtil.h)

add_library(yavec SHARED ${YAVEC_SRC})
target_link_libraries(yavec ${FREETYPE_LIBRARIES})

add_executable(Example Example.cpp)
target_link_libraries(Example yavec)

if(wxWidgets_FOUND)
        add_executable(GUIExample GUIExample.cpp GUIExample.h YaVecVwx.cpp YaVecVwx.h)
    include(${wxWidgets_USE_FILE})
    target_link_libraries(GUIExample yavec ${wxWidgets_LIBRARIES})
endif(wxWidgets_FOUND)

