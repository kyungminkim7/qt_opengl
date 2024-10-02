qt_add_executable(l2_hello_triangle
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.ui
    src/glwidget.cpp
)

target_include_directories(l2_hello_triangle PRIVATE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>"
)

qt_add_resources(l2_hello_triangle shaders
    PREFIX "/"
    FILES
        assets/shader/default.frag
        assets/shader/default.vert
)