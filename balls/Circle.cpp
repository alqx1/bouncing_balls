#include "Circle.hpp"

#include "glm/gtc/matrix_transform.hpp"

unsigned int Circle::VAO = 0, Circle::VBO = 0, Circle::EBO = 0;
std::vector<float> Circle::vertices = std::vector<float>();
std::vector<unsigned int> Circle::indices = std::vector<unsigned int>();

Circle::Circle(
    const glm::vec2 pos, const float radius, const glm::vec2 vel,
    const glm::vec3 color, const float mass
)
    : m_pos{pos}, m_radius{radius}, m_velocity{vel}, m_color{color},
      m_mass{mass} {
}

float Circle::radius() {
    return m_radius;
}

glm::vec2 Circle::pos() {
    return m_pos;
}

glm::vec2 Circle::velocity() {
    return m_velocity;
}

glm::vec3 Circle::color() {
    return m_color;
}

float Circle::mass() {
    return m_mass;
}

void Circle::setVelocity(glm::vec2 vel) {
    m_velocity = vel;
}

void Circle::addVelocity(glm::vec2 add) {
    m_velocity += add;
}

void Circle::update(float deltaTime) {
    move(deltaTime * m_velocity);
}

void Circle::move(glm::vec2 movement) {
    m_pos += movement;
}

void Circle::collidesWith(Circle &other) {
    glm::vec2 dist_vec = other.pos() - this->pos();
    float dist = glm::length(dist_vec);

    if (dist >= this->radius() + other.radius()) {
        return;
    }
    // get normal and tangent
    glm::vec2 normal = glm::normalize(dist_vec);
    glm::vec2 tangent(normal.y, -normal.x);

    // take care of overlap
    float overlap = (this->radius() + other.radius()) - dist;
    this->move(-(overlap / 2) * normal);
    other.move((overlap / 2) * normal);

    // update distance vector
    dist_vec = other.pos() - this->pos();

    // get velocities
    glm::vec2 aVel = this->velocity();
    glm::vec2 bVel = other.velocity();

    // get projections
    float aNormal = glm::dot(normal, aVel);
    float aTangent = glm::dot(tangent, aVel);
    float bNormal = glm::dot(normal, bVel);
    float bTangent = glm::dot(tangent, bVel);

    // get tangent velocities
    glm::vec2 aTangentVel(aTangent * tangent);
    glm::vec2 bTangentVel(bTangent * tangent);

    /* uncomment this and comment other for mass == 1
    // get normal velocities (mass == 1)
    glm::vec2 aNormalVel(bNormal * normal);
    glm::vec2 bNormalVel(aNormal * normal);
    */

    // get normal velocities (different mass)
    // full formula https://www.vobarian.com/collisions/2dcollisions2.pdf
    float over_mass = 1 / (this->mass() + other.mass());
    float one_minus_two = this->mass() - other.mass();

    float aNormal_f =
        (aNormal * one_minus_two + 2 * other.mass() * bNormal) * over_mass;
    float bNormal_f =
        (bNormal * -one_minus_two + 2 * this->mass() * aNormal) * over_mass;

    glm::vec2 aNormalVel(aNormal_f * normal);
    glm::vec2 bNormalVel(bNormal_f * normal);

    // add them together and set them to right object
    aVel = aTangentVel + aNormalVel;
    bVel = bTangentVel + bNormalVel;

    this->setVelocity(aVel);
    other.setVelocity(bVel);
}

void Circle::wallCollision(int width, int height) {
    if (m_pos.x - m_radius < 0) {
        m_pos.x = m_radius;
        m_velocity.x = -m_velocity.x;
    }

    else if (m_pos.x + m_radius > width) {
        m_pos.x = width - m_radius;
        m_velocity.x = -m_velocity.x;
    }

    else if (m_pos.y - m_radius < 0) {
        m_pos.y = m_radius;
        m_velocity.y = -m_velocity.y;
    }

    else if (m_pos.y + m_radius > height) {
        m_pos.y = height - m_radius;
        m_velocity.y = -m_velocity.y;
    }
}

void Circle::render(Circle circle, Shader &shader) {
    glm::mat4 model(1.f);
    model = glm::translate(model, glm::vec3(circle.pos(), 0.f));
    model = glm::scale(model, glm::vec3(circle.radius(), circle.radius(), 0.f));
    shader.setMat4("model", model);
    shader.setVec3("color", circle.color());

    shader.use();
    glBindVertexArray(Circle::VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Circle::EBO);
    glDrawElements(GL_TRIANGLES, Circle::indices.size(), GL_UNSIGNED_INT, 0);
}

void Circle::initCircleClass(const unsigned int points) {
    vertices.clear();
    indices.clear();

    float angleChange = 360.f / points;
    unsigned int nTriangles = points - 2;

    for (unsigned int i = 0; i < points; i++) {
        float angle = i * angleChange;
        Circle::vertices.push_back(std::cos(glm::radians(angle)));
        Circle::vertices.push_back(std::sin(glm::radians(angle)));
    }

    for (unsigned int i = 0; i < nTriangles; i++) {
        Circle::indices.push_back(0);
        Circle::indices.push_back(i + 1);
        Circle::indices.push_back(i + 2);
    }

    glGenVertexArrays(1, &Circle::VAO);
    glGenBuffers(1, &Circle::VBO);
    glGenBuffers(1, &Circle::EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(
        GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(),
        GL_STATIC_DRAW
    );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
        indices.data(), GL_STATIC_DRAW
    );

    glVertexAttribPointer(
        0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0
    );
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
}

static void cleanCircleClass() {
    glDeleteVertexArrays(1, &Circle::VAO);
    glDeleteBuffers(1, &Circle::VBO);
    glDeleteBuffers(1, &Circle::EBO);
}
