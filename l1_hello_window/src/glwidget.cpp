#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent, Qt::WindowFlags flags) : 
    QOpenGLWidget(parent, flags) { }

void GLWidget::initializeGL() {
    initializeOpenGLFunctions();
}

void GLWidget::resizeGL(int width, int height) {
    glViewport(0, 0, width, height);
    this->update();
}

void GLWidget::paintGL() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}