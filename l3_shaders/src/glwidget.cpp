#include "glwidget.h"

#include <array>
#include <chrono>
#include <cmath>

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

float getElapsedTimeSeconds() {
    using namespace std::chrono;
    using secondsF = duration<float>;

    static const auto startTime = steady_clock::now();
    const auto currentTime = steady_clock::now();

    const auto elapsedTime = currentTime - startTime;

    return duration_cast<secondsF>(elapsedTime).count();
}

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

    shaderProgram.enableAttributeArray(0);
    shaderProgram.setAttributeBuffer(0, GL_FLOAT, 0, 3);

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

    const auto green = std::sin(getElapsedTimeSeconds()) * 0.5f + 0.5f;
    shaderProgram.setUniformValue("ourColor", 0.0f, green, 0.0f, 1.0f);

    vao.bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    vao.release();

    shaderProgram.release();
}