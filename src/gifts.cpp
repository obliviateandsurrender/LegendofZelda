#include "gifts.h"
#include "main.h"

Gifts::Gifts(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->lives = 1;
    this->type = rand()%3;
    //int pos=0,i,k,n=6;
    const int n = 6;
    const int reqd = n * 100;
    GLfloat vertex_buffer_data[reqd] = {};

    double angle1 = 0;
    double angle2 = 0;
    const double pi = 4 * atan(1);
    double diff1 = (2 * pi) / (double)n;
    int cur = 0;
    int radius = 8;
    this->radius = radius;

    for (int j = 0; j < n; j++) {
        //Origin
        vertex_buffer_data[cur++] = 0.0f;
        vertex_buffer_data[cur++] = 0.0f;
        vertex_buffer_data[cur++] = 0.0f;
        //Point with lower angle
        vertex_buffer_data[cur++] = 0.0f;//radius * cos(angle2);
        vertex_buffer_data[cur++] = radius * cos(angle1);
        vertex_buffer_data[cur++] = radius * sin(angle1);
        //Point with higher angle
        angle1 += diff1;
        vertex_buffer_data[cur++] = 0.0f;//radius * cos(angle2);
        vertex_buffer_data[cur++] = radius * cos(angle1);
        vertex_buffer_data[cur++] = radius * sin(angle1);
        //angle2 += diff1*2
    }
    if(!this->type) {
        this->object = create3DObject(GL_TRIANGLES, 9*n, vertex_buffer_data, color, GL_FILL);
    }
    else{
        if(this->type == 1){
            this->object = create3DObject(GL_TRIANGLES, 9 * n, vertex_buffer_data, COLOR_BALL3, GL_FILL);
        }
        else {
            this->object = create3DObject(GL_TRIANGLES, 9 * n, vertex_buffer_data, COLOR_RED, GL_FILL);
        }
    }
}

void Gifts::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    rotate = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Gifts::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Gifts::tick() {
    this->rotation = this->rotation + 1.0;
}

bounding_box_t Gifts::bounding_box() {
    bounding_box_t bbox = {this->position.x, this->position.y, this->position.z, 0.1, 2 * this->radius, 2 * this->radius};
    return bbox;
}
