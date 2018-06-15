#include "canon.h"
#include "main.h"

Canon::Canon(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->release = 0;
    this->lives = 1;
    this->speed_x = 0;
    this->speed_y = 0;
    this->gravity = 0;
    this->angle = 0;

    const int n = 360;
    const int reqd = n * 100;
    GLfloat vertex_buffer_data[1000000] = {};

    double angle1 = 0;
    double angle2 = 0;
    const double pi = 4 * atan(1);
    double diff1 = (2 * pi) / (double)n;
    double diff2 = (pi) / (double)n;
    int cur = 0;
    int radius = 4;

    for (int i = 0; i < n / 2; i++)
    {
        angle1 = 0;
        for (int j = 0; j < n; j++)
        {
            //Origin
            vertex_buffer_data[cur++] = 0.0;
            vertex_buffer_data[cur++] = 0.0;
            vertex_buffer_data[cur++] = 0.0f;

            //Point with lower angle
            vertex_buffer_data[cur++] = radius * cos(angle1) * sin(angle2);
            vertex_buffer_data[cur++] = radius * sin(angle1) * sin(angle2);
            vertex_buffer_data[cur++] = radius * cos(angle2);

            //Point with higher angle
            angle1 += diff1;
            vertex_buffer_data[cur++] = radius * cos(angle1) * sin(angle2);
            vertex_buffer_data[cur++] = radius * sin(angle1) * sin(angle2);
            vertex_buffer_data[cur++] = radius * cos(angle2);
        }
        angle2 += diff1;
        //angle2 += diff1;
    }

    this->object = create3DObject(GL_TRIANGLES, (9 * n) * n / (2 * 1.75), vertex_buffer_data, COLOR_GREY, GL_FILL);
}

void Canon::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Canon::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Canon::tick() {
    if (this->position.y - 40 < 0){
        this->release = 0, this->gravity = 0;
        this->speed_x = 0, this->speed_y = 0;
        return;
    }
    this->speed_y += gravity;
    this->position.x -= speed_x*sin(angle);
    this->position.y += speed_y;
    this->position.z -= speed_x*cos(angle);
    //std::cout << position.x << " " << position.y << " " << position.z << " " << speed_x << " " << speed_y << std::endl;
}

void Canon::fire(float theta){
    angle = theta;
    speed_x = 10, speed_y = 10;
    gravity = -0.5;
}

bounding_box_t Canon::bounding_box() {

    bounding_box_t bbox = {this->position.x, this->position.y, this->position.z, 20, 20, 20};
    return bbox;
}
