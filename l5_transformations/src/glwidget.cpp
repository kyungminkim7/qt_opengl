#include "glwidget.h"

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace {

const std::vector<float> vertices {
    // positions          // texture coords
     0.5f,  0.5f, 0.0f,   1.0f, 1.0f,   // top right
     0.5f, -0.5f, 0.0f,   1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f,   // bottom left
    -0.5f,  0.5f, 0.0f,   0.0f, 1.0f    // top left 
};

const std::vector<unsigned int> indices {
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};

constexpr auto attributePosition = "position";
constexpr auto attributeTextureCoordinate = "textureCoordinate";

constexpr auto uniformTransform = "transform";
constexpr auto uniformTextureContainer = "texture0";
constexpr auto uniformTextureFace = "texture1";

} // namespace

GLWidget::GLWidget(QWidget *parent, Qt::WindowFlags flags) : 
    QOpenGLWidget(parent, flags),
    shaderProgram(), vao(),
    vbo(ge::GLBuffer::Type::VertexBuffer),
    ebo(ge::GLBuffer::Type::IndexBuffer) {
    elapsedTimer.start();
}

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

    constexpr auto stride = 5 * sizeof(float);

    shaderProgram.enableAttributeArray(attributePosition);
    shaderProgram.setAttributeBuffer(attributePosition, GL_FLOAT, 0, 3, stride);

    shaderProgram.enableAttributeArray(attributeTextureCoordinate);
    shaderProgram.setAttributeBuffer(attributeTextureCoordinate, GL_FLOAT, 3 * sizeof(float), 2, stride);

    ebo.create();
    ebo.setUsagePattern(ge::GLBuffer::UsagePattern::StaticDraw);
    ebo.bind();
    ebo.allocate(indices.data(), indices.size() * sizeof(GLuint));

    vao.release();

    containerTexture = std::make_unique<ge::GLTexture>("image/container.png");
    containerTexture->setWrapMode(ge::GLTexture::WrapMode::Repeat);
    containerTexture->setMinificationFilter(ge::GLTexture::Filter::LinearMipMapLinear);
    containerTexture->setMagnificationFilter(ge::GLTexture::Filter::Linear);
    shaderProgram.setUniformValue(uniformTextureContainer, 0);


    faceTexture = std::make_unique<ge::GLTexture>("image/awesomeface.png");
    faceTexture->setWrapMode(ge::GLTexture::WrapMode::Repeat);
    faceTexture->setMinificationFilter(ge::GLTexture::Filter::LinearMipMapLinear);
    faceTexture->setMagnificationFilter(ge::GLTexture::Filter::Linear);
    shaderProgram.setUniformValue(uniformTextureFace, 1);

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

    glm::mat4 transform(1.0f);
    transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
    transform = glm::rotate(transform, elapsedTimer.elapsed() / 1000.0f,
                            glm::vec3(0.0f, 0.0f, 1.0f));
    shaderProgram.setUniformValue(uniformTransform, transform);

    containerTexture->bind(0);
    faceTexture->bind(1);

    vao.bind();
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    vao.release();

    shaderProgram.release();
}
