#include "main.h"

#ifndef Monster_H
#define Monster_H


class Monster {
public:
    Monster() {}
    Monster(float x, float y, float z, float size, color_t color);
    glm::vec3 position;
    glm::vec3 start;
    void draw(glm::mat4 VP);
    void tick();
    void set_position(float x, float y, float z);
    int health;
    int points;
    int lives;
    float size;
    float rotation;
    float radius;
    float r_angle;
    bounding_box_t bounding_box();

  private:
    VAO *object;
};

#endif // Monster_H
