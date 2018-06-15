#include "main.h"

#ifndef Gifts_H
#define Gifts_H


class Gifts {
public:
    Gifts() {}
    Gifts(float x, float y, float z, color_t color);
    void set_position(float x, float y, float z);
    void draw(glm::mat4 VP);
    void tick();
    glm::vec3 position;
    float rotation;
    float radius;
    int lives;
    int type;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // Gifts_H
