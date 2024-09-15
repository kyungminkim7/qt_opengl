#pragma once

#include <memory>

#include <openge/GLFunctions.hpp>
#include <QOpenGLWidget>

class GLWidget : public QOpenGLWidget, protected ge::GLFunctions {
public:
    GLWidget(QWidget *parent=nullptr,
             Qt::WindowFlags flags=Qt::WindowFlags());

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;
};
