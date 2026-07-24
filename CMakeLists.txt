cmake_minimum_required(VERSION 3.16)

project(nefes_panel VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(nefes_panel
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        solunumsensoru.h solunumsensoru.cpp
        trendgrafik.h trendgrafik.cpp
        solunumdalgasi.h solunumdalgasi.cpp
        yardimcilar.h yardimcilar.cpp
        cizimwidget.h cizimwidget.cpp
        arcgosterge.h arcgosterge.cpp
        olcumler.h
        alarmkurali.h
        alarmdegerlendirici.h alarmdegerlendirici.cpp
        iolcumkaynagi.h
        hastatipi.h
        kuralfabrikasi.h kuralfabrikasi.cpp
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
target_include_directories(nefes_panel PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

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
