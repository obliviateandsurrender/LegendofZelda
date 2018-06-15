#include "rocks.h"
#include "main.h"

Rocks::Rocks(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->radius = 6;

    const int n = 180;
    const int reqd = n * 9;
    GLfloat vertex_buffer_data[reqd] = {};

    double angle = 0;
    const double pi = 4 * atan(1);
    double diff = (2 * pi) / (double)n;
    int cur = 0;

    for (int i = 0; i < n; i++)
    {
        double dist1 = this->radius * sin(angle) * 2;
        double dist2 = this->radius * cos(angle) * 2;
        //Origin
        vertex_buffer_data[cur++] = 0.0f;
        vertex_buffer_data[cur++] = this->radius * 1.5;
        vertex_buffer_data[cur++] = 0.0f;

        //Point with lower angle
        vertex_buffer_data[cur++] = this->radius * sin(angle) * 2;
        vertex_buffer_data[cur++] = 2*this->radius * sin(angle) + 2*this->radius * cos(angle) - (dist1 + dist2);
        vertex_buffer_data[cur++] = this->radius * cos(angle) * 2;

        //Point with higher angle
        angle += diff;
        dist1 = this->radius * sin(angle) * 2;
        dist2 = this->radius * cos(angle) * 2;
        vertex_buffer_data[cur++] = this->radius * sin(angle) * 2;
        vertex_buffer_data[cur++] = 2*this->radius * sin(angle) + 2*this->radius * cos(angle) - (dist2 + dist1);
        vertex_buffer_data[cur++] = this->radius * cos(angle) * 2;
    }

    this->object = create3DObject(GL_TRIANGLES, reqd / 3, vertex_buffer_data, color, GL_FILL);
}

void Rocks::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Rocks::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

bounding_box_t Rocks::bounding_box() {
    bounding_box_t bbox = {this->position.x, this->position.y, this->position.z, 2 * this->radius, float(this->radius * 1.50), 2 * this->radius};
    return bbox;
}
