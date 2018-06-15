#include "barrel.h"
#include "main.h"

Barrel::Barrel(float x, float y, float z, float size) {
    this->position = glm::vec3(x, y, z);
    this->size = size;
    this->lives = 1;
    this->ingift = 0;
    const int n = 100;
    const int reqd = n * 360 + 18;
    static GLfloat vertex_buffer_data[98018] = {};

    double angle = 0;
    const double pi = 4 * atan(1);
    double diff = (2 * pi) / (double)n;
    int cur = 0;
    float radius = this->size + 3.5;
    float i=0;
    this->radius = radius;

    for (float i = 0; i < 4; i+=0.15) {
        for (int j = 0; j < n; j++, angle-=diff) {

            vertex_buffer_data[cur++] = 14*i;
            vertex_buffer_data[cur++] = 0.0f;
            vertex_buffer_data[cur++] = 0.0f;

            for (int k = 0; k < 2; k++, angle+=diff) {
                vertex_buffer_data[cur++] = 14*i;
                vertex_buffer_data[cur++] = radius * cos(angle);
                vertex_buffer_data[cur++] = radius * sin(angle);
            }
        }
    }

    this->object1 = create3DObject(GL_TRIANGLES, 60 * n, vertex_buffer_data, COLOR_DBROWN, GL_FILL);

    this->ngift = -1;
    static GLfloat fill_vertex_buffer_data[10000];
    cur = 0;
    angle = -pi;
    for (int i = 0; i < 90; i++, angle += diff)
    {
        fill_vertex_buffer_data[cur++] = 0.0;
        fill_vertex_buffer_data[cur++] = -radius * cos(angle);
        fill_vertex_buffer_data[cur++] = -radius * sin(angle);

        fill_vertex_buffer_data[cur++] = 40.0;
        fill_vertex_buffer_data[cur++] = radius * cos(angle);
        fill_vertex_buffer_data[cur++] = radius * sin(angle);

        fill_vertex_buffer_data[cur++] = 40.0;
        fill_vertex_buffer_data[cur++] = -radius * cos(angle);
        fill_vertex_buffer_data[cur++] = -radius * sin(angle);

        fill_vertex_buffer_data[cur++] = 0.0;
        fill_vertex_buffer_data[cur++] = -radius * cos(angle);
        fill_vertex_buffer_data[cur++] = -radius * sin(angle);

        fill_vertex_buffer_data[cur++] = 40.0;
        fill_vertex_buffer_data[cur++] = radius * cos(angle);
        fill_vertex_buffer_data[cur++] = radius * sin(angle);

        fill_vertex_buffer_data[cur++] = 0.0;
        fill_vertex_buffer_data[cur++] = radius * cos(angle);
        fill_vertex_buffer_data[cur++] = radius * sin(angle);
        };

    this->object2 = create3DObject(GL_TRIANGLES, 540, fill_vertex_buffer_data, COLOR_FBROWN, GL_FILL);

}

void Barrel::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
}

void Barrel::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

bounding_box_t Barrel::bounding_box() {
    //float x = , y = , z = ;
    bounding_box_t bbox = {this->position.x + 10, this->position.y, this->position.z - 20, 35, float(this->radius), float(this->radius)};
    return bbox;
}