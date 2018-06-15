#include "waves.h"
#include "main.h"

Waves::Waves(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->init_position = this->position;
    this->rotation = 0;
    this->radius = 300;
    this->r_angle = 0;
    float a[] = { 0.0f };
    static const GLfloat vertex_buffer_data[] = {
        a[0], a[0], a[0],
        a[0], a[0],-3.0,
       -15.0, a[0], 6.0,

        a[0], a[0], a[0],
        a[0], a[0],-3.0,
        15.0, a[0], 6.0,
    };

    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color, GL_FILL);
}

void Waves::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Waves::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Waves::tick() {
    const double pi = 4 * atan(1);
    double distraction = this->radius * sin(r_angle * pi / 180) + this->radius * cos(r_angle * pi / 180);
    this->r_angle += 0.4;
    this->position.x = this->init_position.x + distraction;
    this->position.z = this->init_position.z + distraction;
}

bounding_box_t Waves::bounding_box() {
    bounding_box_t bbox = {this->position.x, this->position.y, this->position.z, 4, 4, 4};
    return bbox;
}
