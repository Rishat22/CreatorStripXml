cmake_minimum_required(VERSION 3.5)

project(CreatorStripXml LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt5 COMPONENTS Widgets LinguistTools REQUIRED)

set(TS_FILES CreatorStripXml_ru_RU.ts)

if(ANDROID)
  add_library(CreatorStripXml SHARED
    CGraphicsItem.h
    CMainWidget.h
    CWdgScene.h
    CWdgSelectionMenu.h
    GlobalSettings.h
    Galaxy/CItemInfoGetter.h
    Galaxy/CStripItem.h
    Galaxy/CBaseFieldItem.h
    Galaxy/CActionItem.h
    cmainwidget.ui
    ${TS_FILES}
  )
else()
  add_executable(CreatorStripXml
    main.cpp
    CGraphicsItem.cpp
    CMainWidget.cpp
    CWdgScene.cpp
    CWdgSelectionMenu.cpp
    GlobalSettings.cpp
    Galaxy/CItemInfoGetter.cpp
    Galaxy/CStripItem.cpp
    Galaxy/CBaseFieldItem.cpp
    Galaxy/CActionItem.cpp
    cmainwidget.ui
    ${TS_FILES}
  )
endif()

target_link_libraries(CreatorStripXml PRIVATE Qt5::Widgets)

qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
