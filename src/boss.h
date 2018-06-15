#include "main.h"

#ifndef Boss_H
#define Boss_H

class Boss
{
  public:
    Boss() {}
    Boss(float x, float y, float z, float size);
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
    VAO *object1;
    VAO *object2;
};

#endif // Boss_H
