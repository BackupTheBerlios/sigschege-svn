include(FindQt4)

find_package(Qt4 REQUIRED)

set(QT_USE_QTXML 1)
include(${QT_USE_FILE})

QT4_ADD_RESOURCES(res 
sigschege.qrc)

QT4_WRAP_CPP(sources_moc 
mainwindow.h
TimingScene.h
TimSignal.h
TimScale.h
TimWave.h
TimLabel.h
TimEvent.h
TimSignalManager.h
TimCmdAddEvent.h
TimCmdAddListItem.h
TimCmdRmListItem.h
SSGReader.h
SSGWriter.h
DiaSettings.h
)

set(sources
mainwindow.cpp
TimingScene.cpp
TimMember.cpp
TimSignal.cpp
TimScale.cpp
TimWave.cpp
TimLabel.cpp
TimLayoutData.cpp
TimEvent.cpp
TimEventType.cpp
TimEventLow.cpp
TimEventHigh.cpp
TimSignalManager.cpp
TimCmdAddEvent.cpp
TimCmdAddListItem.cpp
TimCmdRmListItem.cpp
TimCmdRmEvent.cpp
SSGReader.cpp
SSGWriter.cpp
DiaSettings.cpp
)

# QT4_WRAP_UI(sources_ui Sigschege.ui)

# QT4_ADD_RESOURCES(sources_rcc )

include_directories(${sigschege_BINARY_DIR}/src)

add_executable(sigschege_gui main.cpp ${sources} ${sources_ui} ${sources_moc} ${res})

set_target_properties(sigschege_gui PROPERTIES OUTPUT_NAME sigschege)

target_link_libraries(sigschege_gui ${QT_LIBRARIES})
