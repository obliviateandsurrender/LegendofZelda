#include "boat.h"
#include "main.h"

Boat::Boat(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->health = 500;
    this->score = 0;
    this->points = 0;
    this->booster = 0;
    this->lives = 3;
    this->level_angle = 0;
    this->angular_speed = 0.25;
    this->speed = 5;
    this->speedy = 0;
    this->speed_y = 0.02;
    this->gravity = 0;
    this->acceleration_y = -0.0001;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces withCOLOR_BALL2 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

    float a[] = { 13.0f, 3.9f, 8.0f, 2.0f, 11.5f, 12.25f, 10.0f, 5.0f, 35.0f, 20.0f, 1.25f };
    static const GLfloat vertex_buffer_data[] = {

        //right
        -a[0], -a[1], a[2],
        a[0], a[1], a[3],
        -a[0], a[1], a[2],
        -a[0], -a[1], a[2],
        a[0], a[1], a[3],
        a[0], -a[1], a[3],
        //back
        a[0], a[1], a[3],
        a[0], -a[1], -a[3],
        a[0], -a[1], a[3],
        a[0], a[1], a[3],
        a[0], -a[1], -a[3],
        a[0], a[1], -a[3],
        //left
        a[0], a[1], -a[3],
        -a[0], -a[1], -a[2],
        a[0], -a[1], -a[3],
        a[0], a[1], -a[3],
        -a[0], -a[1], -a[2],
        -a[0], a[1], -a[2],
        //front
        -a[0], -a[1], -a[2],
        -a[0], a[1], a[2],
        -a[0], a[1], -a[2],
        -a[0], -a[1], -a[2],
        -a[0], a[1], a[2],
        -a[0], -a[1], a[2],
        //center
        -a[0], 0.1f, a[2],
        a[0], 0.1f, -a[3],
        a[0], 0.1f, a[3],
        -a[0], 0.1f, a[2],
        a[0], 0.1f, -a[3],
        -a[0], 0.1f, -a[2],
        //Beak
        a[0], 5.9f, a[3],
        a[0], -5.9f, a[3],
        a[9], 5.9f, 0.0f,

        a[0], -5.9f, a[3],
        a[0], -5.9f, -a[3],
        a[9], 5.9f, 0.0f,

        a[0], -5.9f, -a[3],
        a[0], 5.9f, -a[3],
        a[9], 5.9f, 0.0f,

        a[0], 5.9f, -a[3],
        a[0], 5.9f, a[3],
        a[9], 5.9f, 0.0f,
        //Pole
        9.5f, -3.0f, a[10],
        a[4], -3.0f, a[10],
        10.5f, a[8], 0.0f,

        a[4], -3.0f, a[10],
        a[4], -3.0f, -a[10],
        10.5f, a[8], 0.0f,

        a[4], -3.0f, -a[10],
        9.5f, -3.0f, -a[10],
        10.5f, a[8], 0.0f,

        a[4], -3.0f, -a[10],
        a[4], -3.0f, a[10],
        10.5f, a[8], 0.0f,

        //Sails Big
        2.5, 24.9f, a[6],
        a[4], 13.9f, 0.0f,
        2.5, 13.9f, a[6],
        2.5, 24.9f, a[6],
        a[4], 13.9f, 0.0f,
        a[4], 24.9f, 0.0f,

        2.5, 24.9f, -a[6],
        a[4], 13.9f, 0.0f,
        2.5, 13.9f, -a[6],
        2.5, 24.9f, -a[6],
        a[4], 13.9f, 0.0f,
        a[4], 24.9f, 0.0f,

        //Sails Small
        6.5, 12.9f, a[7],
        a[5], 5.9f, 0.0f,
        6.5, 5.9f, a[7],
        6.5, 12.9f, a[7],
        a[5], 5.9f, 0.0f,
        a[5], 12.9f, 0.0f,

        6.5, 12.9f, -a[7],
        a[5], 5.9f, 0.0f,
        6.5, 5.9f, -a[7],
        6.5, 12.9f, -a[7],
        a[5], 5.9f, 0.0f,
        a[5], 12.9f, 0.0f,
        //*/
    };

    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, COLOR_DBROWN, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data + 3*6, COLOR_FBROWN, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data + 3*12, COLOR_DBROWN, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data + 3*18, COLOR_BBROWN, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data + 3*24, COLOR_BLACK, GL_FILL);
    this->object5 = create3DObject(GL_TRIANGLES, 12, vertex_buffer_data + 3*30, COLOR_DBROWN, GL_FILL);
    this->object6 = create3DObject(GL_TRIANGLES, 12, vertex_buffer_data + 3*42, COLOR_BBROWN, GL_FILL);
    this->object7 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data + 3*54, COLOR_BALL1, GL_FILL);
    this->object8 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data + 3*60, COLOR_BALL1, GL_FILL);
    this->object9 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data + 3*66, COLOR_BALL2, GL_FILL);
    this->object10 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data + 3*72, COLOR_BALL2, GL_FILL);
}

void Boat::draw(glm::mat4 VP) {

    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    glm::mat4 rotate1 = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 rotate2 = glm::rotate((float)(this->level_angle * M_PI / 180.0f), glm::vec3(this->position.x, this->position.y, this->position.z - 2));
    glm::mat4 rotate = rotate1 * rotate2;
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    
    draw3DObject(this->object);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
    draw3DObject(this->object4);
    draw3DObject(this->object5);
    draw3DObject(this->object6);
    draw3DObject(this->object7);
    draw3DObject(this->object8);
    draw3DObject(this->object9);
    draw3DObject(this->object10);
}

void Boat::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Boat::tick() {

    this->position.y = this->position.y + this->speedy + this->gravity;
    if (this->position.y - 60 < 0) {
        this->speedy = this->gravity = 0;
        this->position.y = 60;
    }
    this->speedy += this->gravity;
}

void Boat::right() {
    
    this->rotation = this->rotation - this->speed * 0.8f;
}

void Boat::left() {
    this->rotation = this->rotation + this->speed * 0.8f;
}

void Boat::sail() {

    if (this->acceleration_y > 0)
    {
        if (this->position.y > 60.9 - this->speed_y) {
            this->acceleration_y = -1*this->acceleration_y;
            this->speed_y = 0.02;
        }
        else {
            this->position.y = this->position.y + this->speed_y;
            this->speed_y = this->speed_y - this->acceleration_y;
        }
    }
    else if (this->acceleration_y == 0) {
        this->acceleration_y = this->acceleration_y + 0.001;
    }
    else {
        if (this->position.y < 60.1 + speed_y)
        {
            this->acceleration_y = -1 * this->acceleration_y;
            this->speed_y = 0.02;
        }
        else
        {
            this->position.y = this->position.y - this->speed_y;
            this->speed_y = this->speed_y + this->acceleration_y;
        }
    }

    if (abs(level_angle)) {
        this->angular_speed = -1*this->angular_speed;
    }
    this->level_angle += this->angular_speed;
}

void Boat::forward(float angle) {
    this->position.z -= this->speed * cos(angle);
    this->position.x -= this->speed * sin(angle);
}

void Boat::backward(float angle) {
    this->position.z += this->speed * cos(angle);
    this->position.x += this->speed * sin(angle);
}

void Boat::jump() {
    this->speedy = 1.5;
    this->gravity = -0.05;
}


bounding_box_t Boat::bounding_box() {
    bounding_box_t bbox = {this->position.x, this->position.y, this->position.z, 12, 8, 30};
    return bbox;
}
