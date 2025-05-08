#ifndef WINDOW_H
#define WINDOW_H

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"

#include "Shader.hpp"

class Window {
  public:
    Window(const int width, const int height);

    bool closed();
    void update();
    int width();
    int height();


    void updateOrthoProjection(Shader &shader);

  private:
    GLFWwindow *m_window;
    int m_width, m_height;

    void initWindow(const int width, const int height);

    static void
    framebufferSizeCallback(GLFWwindow *window, int width, int height);
};

#endif // WINDOW_H
