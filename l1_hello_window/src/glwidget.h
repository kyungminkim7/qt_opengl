#pragma once

#include <memory>

#include <QOpenGLFunctions>
#include <QOpenGLWidget>

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
public:
    GLWidget(QWidget *parent=nullptr,
             Qt::WindowFlags flags=Qt::WindowFlags());

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;
};
