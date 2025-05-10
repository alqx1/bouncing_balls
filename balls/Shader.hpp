#ifndef SHADER_H
#define SHADER_H

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"

class Shader {
  public:
    Shader(const char *vertFile, const char *fragFile);

    void use();
    void remove();

    void setVec3(const char *name, const glm::vec3 vec);
    void setMat4(const char *name, const glm::mat4 matrix);

  private:
    unsigned int id;
    unsigned int
    createShaderProgram(const char *vertFile, const char *fragFile);
};

#endif // SHADER_H
