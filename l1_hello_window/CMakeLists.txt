qt_add_executable(l1_hello_window
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.ui
    src/glwidget.cpp
)

target_include_directories(l1_hello_window PRIVATE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>"
)
