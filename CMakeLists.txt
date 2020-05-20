# cmake_minimum_required(VERSION <specify CMake version here>)
project(editor)

cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH "/usr/share/SFML/cmake/Modules;${CMAKE_MODULE_PATH}")
find_package(SFML 2.4.2 COMPONENTS system window graphics network audio  REQUIRED)

add_executable(editor main.cpp
               EnterText/EnterText.cpp EnterText/EnterText.h
               Button/Button.cpp Button/Button.h
               Menu/Menu.cpp Menu/Menu.h
               InteractionWindows/QuestionWindow.cpp InteractionWindows/QuestionWindow.h
               InteractionWindows/NotificationWindow.cpp InteractionWindows/NotificationWindow.h ObjectsPalette/ObjectsPalette.cpp ObjectsPalette/ObjectsPalette.h DrawingField/DrawingField.cpp DrawingField/DrawingField.h)


target_link_libraries(editor pthread sfml-system sfml-window sfml-graphics sfml-audio)
