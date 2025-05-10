#define MAX_MASS 10
#define W_WIDTH 1080
#define W_HEIGHT 720

#define COLS 7
#define ROWS 6

#define RADIUS 50

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "glm/gtc/matrix_transform.hpp"

#include <cstdlib>
#include <filesystem>
#include <vector>

#include "Circle.hpp"
#include "Shader.hpp"
#include "Window.hpp"

std::vector<Circle> genCircles();

int main() {
    srand(time(NULL));
    Window window(W_WIDTH, W_HEIGHT);
    Circle::initCircleClass(40);
    Shader shader(
        std::filesystem::absolute("./simple.vert").c_str(),
        std::filesystem::absolute("./simple.frag").c_str()
    );

    std::vector<Circle> circles = genCircles();

    glClear(GL_COLOR_BUFFER_BIT);
    window.updateOrthoProjection(shader);
    float deltaTime = 0, previous = glfwGetTime();
    while (!window.closed()) {
        deltaTime = glfwGetTime() - previous;
        previous = glfwGetTime();

        for (auto &c : circles) {
            c.update(deltaTime);
            c.wallCollision(1080, 720);
        }

        for (unsigned int i = 0; i < circles.size(); i++) {
            for (unsigned int j = i + 1; j < circles.size(); j++) {
                circles[i].collidesWith(circles[j]);
            }
        }

        for (auto c : circles) {
            Circle::render(c, shader);
        }

        window.update();
        glClear(GL_COLOR_BUFFER_BIT);
        window.updateOrthoProjection(shader);
    }

    Circle::cleanCircleClass();
    shader.remove();
    window.clean();
}

std::vector<Circle> genCircles() {
    std::vector<Circle> circles;

    int x_box = W_WIDTH * 0.9f;
    int y_box = W_HEIGHT * 0.9f;

    int x_space = x_box / COLS;
    int y_space = y_box / ROWS;

    int x_padding = W_WIDTH * 0.1f;
    int y_padding = W_HEIGHT * 0.1f;

    for (unsigned int i = 0; i < ROWS; i++) {
        for (unsigned int j = 0; j < COLS; j++) {
            float mass_decimal =
                ((rand() % (MAX_MASS - 1) + 1) / (float)MAX_MASS);
            float mass = mass_decimal * (rand() % (MAX_MASS - 1) + 1);

            circles.push_back(Circle(
                glm::vec2(x_padding + x_space * j, y_padding + y_space * i),
                RADIUS,
                glm::vec2(
                    ((bool)(rand() % 2) ? 1 : -1) * rand() % 100 + 50,
                    ((bool)(rand() % 2) ? 1 : -1) * rand() % 100 + 50
                ),
                glm::vec3((1.f - mass_decimal) + 0.1f), mass
            ));
        }
    }

    return circles;
}
