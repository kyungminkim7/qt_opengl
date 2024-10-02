#include "glwidget.h"

#include <vector>

#include <openge/GLShader.hpp>

namespace {

const std::vector<float> vertices {
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left
};

const std::vector<unsigned int> indices {
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};

constexpr auto attributePosition = "position";

} // namespace

GLWidget::GLWidget(QWidget *parent, Qt::WindowFlags flags) : 
    QOpenGLWidget(parent, flags),
    shaderProgram(), vao(),
    vbo(ge::GLBuffer::Type::VertexBuffer),
    ebo(ge::GLBuffer::Type::IndexBuffer) { }

void GLWidget::initializeGL() {
    initializeOpenGLFunctions();

    shaderProgram.create();
    shaderProgram.addShaderFromSourceFile(ge::GLShader::ShaderTypeBit::Vertex,
                                          "shader/default.vert");
    shaderProgram.addShaderFromSourceFile(ge::GLShader::ShaderTypeBit::Fragment,
                                          "shader/default.frag");
    shaderProgram.link();
    shaderProgram.bind();

    vao.create();
    vao.bind();

    vbo.create();
    vbo.setUsagePattern(ge::GLBuffer::UsagePattern::StaticDraw);
    vbo.bind();
    vbo.allocate(vertices.data(), vertices.size() * sizeof(GLfloat));

    shaderProgram.enableAttributeArray(attributePosition);
    shaderProgram.setAttributeBuffer(attributePosition, GL_FLOAT, 0, 3);

    ebo.create();
    ebo.setUsagePattern(ge::GLBuffer::UsagePattern::StaticDraw);
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

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    vao.release();
    shaderProgram.release();
}