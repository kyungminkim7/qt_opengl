#pragma once

#include <memory>

#include <openge/GLBuffer.hpp>
#include <openge/GLFunctions.hpp>
#include <openge/GLShaderProgram.hpp>
#include <openge/GLVertexArrayObject.hpp>

#include <QOpenGLWidget>

class GLWidget : public QOpenGLWidget, protected ge::GLFunctions {
public:
    GLWidget(QWidget *parent=nullptr,
             Qt::WindowFlags flags=Qt::WindowFlags());

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;

private:
    ge::GLShaderProgram shaderProgram;
    ge::GLVertexArrayObject vao;
    ge::GLBuffer vbo;
    ge::GLBuffer ebo;
};
