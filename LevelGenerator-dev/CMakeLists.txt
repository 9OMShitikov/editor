cmake_minimum_required(VERSION 3.15)
project(LevelGenerator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH "/usr/share/SFML/cmake/Modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2.4.2 COMPONENTS graphics audio REQUIRED)

find_package(PkgConfig)
pkg_check_modules(YAMLCPP REQUIRED yaml-cpp>=0.5)
include_directories(${YAMLCPP_INCLUDE_DIRS})

add_executable(LevelGenerator main.cpp WindowObjects/LevelGenerator.h
        Managers/EventManager.h Managers/LayoutManager.h  GeomObjects/Button.cpp GeomObjects/Button.h GeomObjects/Minimap.h
        GeomObjects/Palette.h GeomObjects/TileMap.h Managers/MouseStatus.h Managers/MouseStatus.cpp GeomObjects/TileMap.cpp
        WindowObjects/LevelGenerator.cpp WindowObjects/DialogWindow.cpp WindowObjects/DialogWindow.h GeomObjects/InputBox.h
        Managers/EventManager.cpp GeomObjects/InputBox.cpp GeomObjects/Minimap.cpp GeomObjects/Palette.cpp Managers/LayoutManager.cpp
        Managers/TextureManager.cpp  WindowObjects/NotificationWindow.cpp WindowObjects/NotificationWindow.h GeomObjects/WindowObj.h
        Managers/DialogLayoutForm.cpp Managers/DialogLayoutForm.h WindowObjects/DialogForm.cpp WindowObjects/DialogForm.h "YAML API/Specialized Classes.h" "YAML API/DefiningYAMLFormat.h")

target_link_libraries(LevelGenerator sfml-graphics sfml-window sfml-system ${YAMLCPP_LIBRARIES} -I/usr/local/include
        -L/usr/local/lib ${catkin_LIBRARIES} -Wl,-rpath,/usr/local/lib)