cmake_minimum_required(VERSION 3.16)
project(FilmLibraryManager VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)
find_package(cryptopp CONFIG REQUIRED)
find_package(unofficial-sqlite3 CONFIG REQUIRED)

set(PROJECT_SOURCES
  src/main.cpp
  src/mainwindow.cpp
  src/LoginView.cpp
  src/loginview.ui
  include/mainwindow.h
  include/LoginView.h
)

add_executable(FilmLibraryManager
  ${PROJECT_SOURCES}
)

target_include_directories(FilmLibraryManager PRIVATE include)

target_link_libraries(FilmLibraryManager PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets cryptopp::cryptopp unofficial::sqlite3::sqlite3)
