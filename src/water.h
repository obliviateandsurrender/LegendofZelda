#include "main.h"

#ifndef Water_H
#define Water_H


class Water {
public:
    Water() {}
    Water(float x, float y, float z, color_t color);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    float rotation;
private:
    VAO *object;

};

#endif // Water_H
