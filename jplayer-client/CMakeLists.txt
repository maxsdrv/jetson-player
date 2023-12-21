cmake_minimum_required(VERSION 3.16)

project(media-dashboard VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Quick ShaderTools)

find_program(QSB_EXECUTABLE NAMES qsb)

message(STATUS "QSB_EXECUTABLE: ${QSB_EXECUTABLE}")

qt_standard_project_setup()

set(SOURCES
    networkmanager.cpp
    networkmanager.h
    playerworker.cpp
    playerworker.h
    runner.cpp
    runner.h
    playersender.h
    playersender.cpp
    playerreceiver.h
    playerreceiver.cpp
    main.cpp
)

qt_add_executable(${PROJECT_NAME}
    ${SOURCES}
)

qt_add_resources(${PROJECT_NAME} "${PROJECT_NAME}"
    PREFIX "/"
    FILES
        "Main.qml"
        "resource/images/play_01.png"
        "resource/images/play02.png"
        "resource/images/stop01.png"
        "resource/images/pause01.png"
)

qt6_add_shaders(${PROJECT_NAME} "${PROJECT_NAME}_shaders"
    PREFIX "/"
    FILES
    "resource/shaders/button_direction.vert"
    "resource/shaders/button_font.frag"
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    Qt6::Quick
    Qt6::ShaderTools
)

install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
