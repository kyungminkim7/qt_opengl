qt_add_executable(l4_textures
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.ui
    src/glwidget.cpp
)

target_include_directories(l4_textures PRIVATE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>"
)

qt_add_resources(l4_textures shader
    PREFIX "/"
    FILES
        assets/shader/default.frag
        assets/shader/default.vert
)

qt_add_resources(l4_textures image
    PREFIX "/"
    FILES
        assets/image/awesomeface.png
        assets/image/container.png
)