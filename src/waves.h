#include "main.h"

#ifndef Waves_H
#define Waves_H


class Waves {
public:
    Waves() {}
    Waves(float x, float y, float z, color_t color);
    glm::vec3 position;
    glm::vec3 init_position;
    void set_position(float x, float y, float z);
    void draw(glm::mat4 VP);
    void tick();
    float rotation;
    float radius;
    float r_angle;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // Waves_H
