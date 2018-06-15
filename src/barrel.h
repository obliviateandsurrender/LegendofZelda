    #include "main.h"

#ifndef Barrel_H
#define Barrel_H

class Barrel {
public:
    Barrel() {}
    Barrel(float x, float y, float z, float size);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    float size;
    float rotation;
    int ngift;
    int ingift;
    int lives;
    int radius;
    bounding_box_t bounding_box();

  private:
    VAO *object1;
    VAO *object2;
};

#endif // Barrel_H
