cmake_minimum_required(VERSION 3.15)
project(qt_opengl CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 CONFIG REQUIRED COMPONENTS
    OpenGLWidgets
    Widgets
)

qt_standard_project_setup()

link_libraries(
    Qt6::Widgets
    Qt6::OpenGLWidgets
)

add_subdirectory(l1_hello_window)