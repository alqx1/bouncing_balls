#include "Shader.hpp"

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "glm/gtc/type_ptr.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

Shader::Shader(const char *vertFile, const char *fragFile) {
    this->id = createShaderProgram(vertFile, fragFile);
}

void Shader::use() {
    glUseProgram(this->id);
}

void Shader::remove() {
    glDeleteProgram(this->id);
}

void Shader::setVec3(const char *name, const glm::vec3 vec) {
    this->use();
    glUniform3f(glGetUniformLocation(this->id, name), vec.r, vec.g, vec.b);
}

void Shader::setMat4(const char *name, const glm::mat4 matrix) {
    this->use();
    glUniformMatrix4fv(
        glGetUniformLocation(this->id, name), 1, GL_FALSE,
        glm::value_ptr(matrix)
    );
}

unsigned int
Shader::createShaderProgram(const char *vertFile, const char *fragFile) {
    std::stringstream vertStream, fragStream;
    std::ifstream vertIn, fragIn;

    vertIn.open(vertFile);
    if (!vertIn.good()) {
        std::cerr << "Cannot open vertex file\n";
        return 0;
    }

    fragIn.open(fragFile);
    if (!fragIn.good()) {
        std::cerr << "Cannot open vertex file\n";
        return 0;
    }

    vertStream << vertIn.rdbuf();
    fragStream << fragIn.rdbuf();

    std::string vertBuf, fragBuf;
    vertBuf = vertStream.str();
    fragBuf = fragStream.str();
    const char *vertSource = vertBuf.c_str();
    const char *fragSource = fragBuf.c_str();

    unsigned int vert, frag;
    vert = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert, 1, &vertSource, NULL);
    glCompileShader(vert);

    int success;
    char infoLog[512];
    glGetShaderiv(vert, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vert, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n";
        std::cout << infoLog << '\n';
    }

    frag = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag, 1, &fragSource, NULL);
    glCompileShader(frag);

    glGetShaderiv(frag, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(frag, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n";
        std::cout << infoLog << '\n';
    }

    unsigned int program = glCreateProgram();
    glAttachShader(program, vert);
    glAttachShader(program, frag);
    glLinkProgram(program);

    glDeleteShader(vert);
    glDeleteShader(frag);

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKAGE_FAILED\n";
        std::cout << infoLog << '\n';
    }

    return program;
}
