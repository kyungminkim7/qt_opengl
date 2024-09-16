#include "glwidget.h"

#include <vector>

namespace {

const std::vector<float> vertices {
    // positions         // colors
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top   
};

const std::vector<unsigned int> indices { 0, 1, 2 };

constexpr auto attributePosition = "position";
constexpr auto attributeColor = "color";

} // namespace

GLWidget::GLWidget(QWidget *parent, Qt::WindowFlags flags) : 
    QOpenGLWidget(parent, flags),
    shaderProgram(), vao(),
    vbo(QOpenGLBuffer::VertexBuffer),
    ebo(QOpenGLBuffer::IndexBuffer) { }

void GLWidget::initializeGL() {
    initializeOpenGLFunctions();

    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                          ":/shaders/default.vert");
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                          ":/shaders/default.frag");
    shaderProgram.link();
    shaderProgram.bind();

    vao.create();
    vao.bind();

    vbo.create();
    vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    vbo.bind();
    vbo.allocate(vertices.data(), vertices.size() * sizeof(GLfloat));

    constexpr auto stride = 6 * sizeof(float);

    shaderProgram.enableAttributeArray(attributePosition);
    shaderProgram.setAttributeBuffer(attributePosition, GL_FLOAT, 0, 3, stride);

    shaderProgram.enableAttributeArray(attributeColor);
    shaderProgram.setAttributeBuffer(attributeColor, GL_FLOAT, 3 * sizeof(float), 3, stride);

    ebo.create();
    ebo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    ebo.bind();
    ebo.allocate(indices.data(), indices.size() * sizeof(GLuint));

    vao.release();
    shaderProgram.release();

    timer = std::make_unique<QTimer>(this);
    connect(timer.get(), &QTimer::timeout, this, &GLWidget::onTimerTimeout);
    timer->start(16);
}

void GLWidget::resizeGL(int width, int height) {
    glViewport(0, 0, width, height);
    this->update();
}

void GLWidget::onTimerTimeout() {
    update();
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