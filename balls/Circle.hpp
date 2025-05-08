#ifndef CIRCLE_H
#define CIRCLE_H

#include "glm/glm.hpp"

#include <vector>

#include "Shader.hpp"

class Circle {
  public:
    Circle(
        const glm::vec2 pos, const float radius, const glm::vec2 vel,
        const glm::vec3 color, const float mass
    );

    float radius();
    glm::vec2 pos();
    glm::vec2 velocity();
    glm::vec3 color();
    float mass();

    void setVelocity(glm::vec2 vel);
    void addVelocity(glm::vec2 add);

    void update(float deltaTime);
    void move(glm::vec2 movement);
    void wallCollision(int width, int height);
    void collidesWith(Circle &other);

    static std::vector<float> vertices;
    static std::vector<unsigned int> indices;
    static unsigned int VAO, VBO, EBO;

    static void render(Circle circle, Shader &shader);
    static void initCircleClass(const unsigned int points);

  private:
    float m_radius;
    glm::vec2 m_pos;
    glm::vec2 m_velocity;
    glm::vec3 m_color;
    float m_mass;
};

#endif // CIRCLE_H
