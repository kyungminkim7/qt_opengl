#include "glwidget.h"

#include <array>

#include <openge/GLShader.hpp>

namespace {

constexpr std::array<float, 12> vertices {
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left
};

constexpr std::array<unsigned int, 6> indices {
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};

} // namespace

GLWidget::GLWidget(QWidget *parent, Qt::WindowFlags flags) : 
    QOpenGLWidget(parent, flags),
    shaderProgram(), vao(),
    vbo(ge::GLBuffer::VertexBuffer),
    ebo(ge::GLBuffer::IndexBuffer) { }

void GLWidget::initializeGL() {
    initializeOpenGLFunctions();

    shaderProgram.addShaderFromSourceFile(ge::GLShader::Vertex,
                                          ":/shaders/default.vert");
    shaderProgram.addShaderFromSourceFile(ge::GLShader::Fragment,
                                          ":/shaders/default.frag");
    shaderProgram.link();
    shaderProgram.bind();

    vao.create();
    vao.bind();

    vbo.create();
    vbo.setUsagePattern(ge::GLBuffer::StaticDraw);
    vbo.bind();
    vbo.allocate(vertices.data(), vertices.size() * sizeof(GLfloat));

    shaderProgram.enableAttributeArray(0);
    shaderProgram.setAttributeBuffer(0, GL_FLOAT, 0, 3);

    ebo.create();
    ebo.setUsagePattern(ge::GLBuffer::StaticDraw);
    ebo.bind();
    ebo.allocate(indices.data(), indices.size() * sizeof(GLuint));

    vao.release();
    shaderProgram.release();
}

void GLWidget::resizeGL(int width, int height) {
    glViewport(0, 0, width, height);
    this->update();
}

void GLWidget::paintGL() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shaderProgram.bind();
    vao.bind();

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    vao.release();
    shaderProgram.release();
}