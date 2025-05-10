#include "Window.hpp"

#include <iostream>

#include "glm/gtc/matrix_transform.hpp"

Window::Window(const int width, const int height)
    : m_width{width}, m_height{height} {
    initWindow(width, height);
}

void Window::initWindow(const int width, const int height) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(width, height, "balls", NULL, NULL);
    if (!m_window) {
        std::cerr << "ERROR::WINDOW::CREATION::FAILED\n";
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(m_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        glfwTerminate();
        std::cerr << "Failed to initialize GLAD\n";
        exit(-1);
    }
    glfwSetFramebufferSizeCallback(m_window, framebufferSizeCallback);
    glViewport(0, 0, width, height);
    glClearColor(0, 0, 0, 1.f);
    glfwSetWindowAspectRatio(m_window, width, height);
}

void Window::framebufferSizeCallback(
    GLFWwindow *window, int width, int height
) {
    glViewport(0, 0, width, height);
}

void Window::update() {
    glfwSwapBuffers(m_window);
    glfwPollEvents();
}

void Window::clean() {
    glfwTerminate();
}

bool Window::closed() {
    return glfwWindowShouldClose(this->m_window);
}

int Window::width() {
    return m_width;
}

int Window::height() {
    return m_height;
}

void Window::updateOrthoProjection(Shader &shader) {
    glm::mat4 projection =
        glm::ortho(0.f, (float)m_width, (float)m_height, 0.f, -1.f, 1.f);
    shader.setMat4("projection", projection);
}
