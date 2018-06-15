#include "main.h"

#ifndef BOAT_H
#define BOAT_H

class Boat
{
  public:
  Boat()  {}
  glm::vec3 position;
  float rotation;
  void right();
  Boat(float x, float y, float z);
  float level_angle;
  float angular_speed;
  float acceleration_y;
  float speed_y;
  int health;
  int lives;
  int points;
  int booster;
  int score;
  void sail();
  void left();
  void forward(float angle);
  void backward(float angle);
  void jump();
  void draw(glm::mat4 VP);
  void set_position(float x, float y, float z);
  void tick();
  float speed;
  float speedy;
  float gravity;
  bounding_box_t bounding_box();

private:
  VAO *object;
  VAO *object1;
  VAO *object2;
  VAO *object3;
  VAO *object4;
  VAO *object5;
  VAO *object6;
  VAO *object7;
  VAO *object8;
  VAO *object9;
  VAO *object10;
};

#endif // BOAT_H
