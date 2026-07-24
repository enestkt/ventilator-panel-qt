cmake_minimum_required(VERSION 3.16)

project(nefes_panel VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# Kaynaklar katmanlara gore klasorlenmistir. Klasorler asagida include
# yoluna eklendigi icin dosyalardaki #include satirlari degismedi.
set(PROJECT_SOURCES
        src/app/main.cpp
        src/app/mainwindow.cpp
        src/app/mainwindow.h
        src/app/mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(nefes_panel
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}

        # --- veri katmani ---
        src/data/olcumler.h
        src/data/iolcumkaynagi.h
        src/data/solunumsensoru.h      src/data/solunumsensoru.cpp
        src/data/yardimcilar.h         src/data/yardimcilar.cpp

        # --- alarm katmani ---
        src/alarm/hastatipi.h
        src/alarm/alarmkurali.h
        src/alarm/alarmdegerlendirici.h src/alarm/alarmdegerlendirici.cpp
        src/alarm/kuralfabrikasi.h      src/alarm/kuralfabrikasi.cpp

        # --- gorsel katman ---
        src/visual/cizimwidget.h       src/visual/cizimwidget.cpp
        src/visual/arcgosterge.h       src/visual/arcgosterge.cpp
        src/visual/trendgrafik.h       src/visual/trendgrafik.cpp
        src/visual/solunumdalgasi.h    src/visual/solunumdalgasi.cpp
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET nefes_panel APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(nefes_panel SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(nefes_panel
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(nefes_panel PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
# Her katman klasoru include yolunda. Bu sayede kaynaklardaki
# #include "alarmkurali.h" gibi satirlar klasorlemeden etkilenmedi.
target_include_directories(nefes_panel PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/data
    ${CMAKE_CURRENT_SOURCE_DIR}/src/alarm
    ${CMAKE_CURRENT_SOURCE_DIR}/src/visual
    ${CMAKE_CURRENT_SOURCE_DIR}/src/app
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.nefes_panel)
endif()
set_target_properties(nefes_panel PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS nefes_panel
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(nefes_panel)
endif()
