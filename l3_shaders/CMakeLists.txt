qt_add_executable(l3_shaders
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.ui
    src/glwidget.cpp
)

target_include_directories(l3_shaders PRIVATE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>"
)

qt_add_resources(l3_shaders shaders
    PREFIX "/"
    FILES
        assets/shader/default.frag
        assets/shader/default.vert
)