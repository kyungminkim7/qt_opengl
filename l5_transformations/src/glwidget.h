#pragma once

#include <memory>

#include <openge/GLBuffer.hpp>
#include <openge/GLFunctions.hpp>
#include <openge/GLShaderProgram.hpp>
#include <openge/GLTexture.hpp>
#include <openge/GLVertexArrayObject.hpp>

#include <QOpenGLWidget>
#include <QElapsedTimer>
#include <QTimer>

class GLWidget : public QOpenGLWidget, protected ge::GLFunctions {
public:
    GLWidget(QWidget *parent=nullptr,
             Qt::WindowFlags flags=Qt::WindowFlags());

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;

private slots:
    void onTimerTimeout();

private:
    ge::GLShaderProgram shaderProgram;
    ge::GLVertexArrayObject vao;
    ge::GLBuffer vbo;
    ge::GLBuffer ebo;
    std::unique_ptr<ge::GLTexture> containerTexture;
    std::unique_ptr<ge::GLTexture> faceTexture;

    std::unique_ptr<QTimer> timer;
    QElapsedTimer elapsedTimer;
};
