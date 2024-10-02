qt_add_executable(l5_transformations
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.ui
    src/glwidget.cpp
)

target_include_directories(l5_transformations PRIVATE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>"
)

qt_add_resources(l5_transformations shader
    PREFIX "/"
    FILES
        assets/shader/default.frag
        assets/shader/default.vert
)

qt_add_resources(l5_transformations image
    PREFIX "/"
    FILES
        assets/image/awesomeface.png
        assets/image/container.png
)