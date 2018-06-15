#include "water.h"
#include "main.h"
#include <limits.h>

Water::Water(float x, float y, float z, color_t color)
{
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;

    const int n = 100;
    const int reqd = n * 360;
    GLfloat vertex_buffer_data[reqd] = {};

    double angle = 0;
    const double pi = 4 * atan(1);
    double diff = (2 * pi) / (double)n;
    int cur = 0;
    float a[] = { 0.0f }; 
    for (int i = 0; i < 40; i++)
    {
        for (int j = 0; j < n; j++)
        {
            //Origin
            vertex_buffer_data[cur++] = a[0];
            vertex_buffer_data[cur++] = (float)i-20;
            vertex_buffer_data[cur++] = a[0];

            //Point with lower angle
            vertex_buffer_data[cur++] = INT64_MAX * sin(angle);
            vertex_buffer_data[cur++] = (float)i-20;
            vertex_buffer_data[cur++] = INT64_MAX * cos(angle);

            //Point with higher angle
            angle += diff;
            vertex_buffer_data[cur++] = INT64_MAX * sin(angle);
            vertex_buffer_data[cur++] = (float)i-20;
            vertex_buffer_data[cur++] = INT64_MAX * cos(angle);
        }
    }

    this->object = create3DObject(GL_TRIANGLES, reqd / 4, vertex_buffer_data, color, GL_FILL);
}

void Water::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Water::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}


