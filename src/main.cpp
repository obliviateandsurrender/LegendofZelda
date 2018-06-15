#include "main.h"
#include "timer.h"
#include "boat.h"
#include "water.h"
#include "barrel.h"
#include "waves.h"
#include "canon.h"
#include "gifts.h"
#include "rocks.h"
#include "boss.h"
#include "monster.h"
using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Boat boat;
Water sea;
Barrel barrel[100];
Waves wave[2000];
bool sound = true;
pid_t pid = 0;
Canon canon;
Gifts gift[40];
Timer t60(1.0 / 40);
Rocks rock[100];
Monster enemy[20];
Boss boss;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0, camera_x=0, camera_y=90, camera_z=100, target_x=0, target_y=90, target_z=0;
//int view = 1, i, ran_x, ran_z, n=100, m=50, g=30, r=100, e = 10;
int level = 1, game_time = 0;

const int wavy = 2000, barry = 100, gif = 30, emo = 20 ;
int rand_x, rand_z, view = 1;   
const float pi = 4*atan(1);

int wind_effect = 0;
int windshift_x, windshift_z;
int duration = 300, start_time = 500;
int boost_duration = 300; 
double wind_accelx = 0.005, wind_accelz = 0.005, wind_speedz = 1, wind_speedx = 1;
double booster_accelx = 0.5f, booster_accelz = 0.5f, boost_speedx = 1, boost_speedz = 1; 

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    //glm::vec3 eye (5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f));
    glm::vec3 eye(camera_x, camera_y, camera_z);
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (target_x, target_y, target_z);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    sea.draw(VP);

    for(int i = 0; i < wavy; i++)
        wave[i].draw(VP);
    
    for(int i = 0; i < barry; i++) {
        
        rock[i].draw(VP); 
        if(barrel[i].lives) {
            barrel[i].draw(VP);
        }
    }

    for(int i = 0; i < emo; i++) {
        if(enemy[i].lives) {
            enemy[i].draw(VP);
        }
    }
    
    for(int i = 0; i < gif; i++)
        if(gift[i].lives) {
            gift[i].draw(VP);
        }
    

    if(boat.points>1013 && boss.lives) {
        boss.draw(VP);
    }

    if(canon.release)
        canon.draw(VP);
    
    if(boat.lives > 0) {
        boat.draw(VP);
    }

}

void tick_input(GLFWwindow *window) {

    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int jump = glfwGetKey(window, GLFW_KEY_SPACE);
    int fire = glfwGetKey(window, GLFW_KEY_F);
    
    if (left) {
        boat.left();
    }
    if (right) {
        boat.right();
    }
    if (up) {
        boat.forward((boat.rotation-90)*(pi/180));
    }
    if (down) {
        boat.backward((boat.rotation-90)*(pi/180));
    }
    if (jump) {
        if(boat.position.y - 63 < 0 )
            boat.jump();
    }
    if(fire && !canon.release){
        canon.release = 1;
        canon.fire((boat.rotation-90)*(pi/180));
    }
}

void tick_elements() {
    
    boat.tick();
    boat.sail();

    for (int i = 0; i < wavy; i++) {
        wave[i].tick();
    }

    for (int i = 0; i < barry; i++) {
        if (barrel[i].lives) {
            if (detect_collision(boat.bounding_box(), barrel[i].bounding_box())) {
                if (boat.position.y <= 62) {
                    boat.backward((boat.rotation - 90) * (pi / 180));
                    boat.backward((boat.rotation - 90) * (pi / 180));
                    boat.jump();
                }
                boat.points += 50;
            }
            else {
                if (detect_collision(canon.bounding_box(), barrel[i].bounding_box()) && canon.release) {
                    barrel[i].lives = 0;
                    boat.points += 50;
                }
            }
        }
    }

    for(int i = 0; i < gif; i++) {
        if (gift[i].lives){
            if (detect_collision_pole(boat.bounding_box(), gift[i].bounding_box())) {
                if (!gift[i].type) {
                    boat.points += 10;
                }
                else {
                    if (gift[i].type == 1) {
                        if (boat.lives < 3) {
                            boat.lives += 1;
                        }
                        else {
                            boat.health += 10;
                        }
                    }
                    else if (gift[i].type == 2) {
                        boat.booster = 1;
                    }
                }
                gift[i].lives = 0;
            }
            gift[i].tick();
        }
    }
    
    
    for(int i = 0; i < emo; i++) {
        
        if (enemy[i].lives){
            
            if (detect_collision(boat.bounding_box(), enemy[i].bounding_box())) {
                boat.backward((boat.rotation - 90) * (pi / 180));
                boat.backward((boat.rotation - 90) * (pi / 180));
                printf("collide\n");
                boat.health -= 100;
                if (boat.health < 0) {
                    boat.lives--;
                    boat.health = 500;
                }
            }
            else {
                if (detect_collision(canon.bounding_box(), enemy[i].bounding_box()) && canon.release) {
                    printf("dead\n");
                    enemy[i].lives = 0;
                    boat.points += enemy[i].points*10;
                }
            }
            for (int j = 0; j < barry; j++) {
                if (detect_collision(rock[j].bounding_box(), enemy[i].bounding_box())) {
                    enemy[i].position.x -= 1.0f;
                    enemy[i].position.z -= 1.0f;
                }
            }
            enemy[i].tick();
        }
    }

    if (boss.lives) {
        if (detect_collision(boat.bounding_box(), boss.bounding_box())) {
            boat.backward((boat.rotation - 90) * (pi / 180));
            boat.backward((boat.rotation - 90) * (pi / 180));
            boat.backward((boat.rotation - 90) * (pi / 180));
            boat.backward((boat.rotation - 90) * (pi / 180));
            boat.backward((boat.rotation - 90) * (pi / 180));
            boat.health -= 100;
            if (boat.health < 0)
            {
                boat.lives--;
                boat.health = 500;
            }
        }
        if (detect_collision(canon.bounding_box(), boss.bounding_box()) && canon.release) {
            boss.lives -= 1;
            if (boss.lives < 0) {
                boss.lives = 0;
            }
            boat.points += 500;
        }
        for (int j = 0; j < barry; j++)
        {
            if (detect_collision(rock[j].bounding_box(), boss.bounding_box())) {
                boss.position.x -= 1.0f;
                boss.position.z -= 1.0f;
            }
        }
        boss.tick();
    }

    if(!canon.release){
       canon.set_position(boat.position.x, boat.position.y, boat.position.z);
    }
    else{
        canon.tick();
    }


    for(int i = 0; i < barry; i++){
        if (detect_collision(boat.bounding_box(), rock[i].bounding_box())) {
            //printf("collide\n");
            int choice = rand()%2;
            if (choice) {
                boat.right();
            }
            else {
                boat.left();
            }
            boat.backward((boat.rotation - 90) * (pi / 180));
            boat.backward((boat.rotation - 90) * (pi / 180));
            boat.backward((boat.rotation - 90) * (pi / 180));
            boat.backward((boat.rotation - 90) * (pi / 180));
            boat.health -= 10;
            //boat.health -= 100;
            if (boat.health < 0)
            {
                boat.lives--;
                boat.health = 500;
            }
        }
    }

    do {
        if (wind_effect)
        {
            duration = duration - 1;
            wind_speedx += wind_accelx;
            wind_speedz += wind_accelz;
            int radius = 1.0f;
            boat.position.x += radius*sin(wind_speedx);
            boat.position.z += radius*cos(wind_speedz);
            if (duration < 0) {
                duration = 300;
                wind_effect = 0;
            }
        }
        else
        {
            start_time--;;
            if (start_time < 0) {
                start_time = 700;
                wind_effect = 1, wind_speedx = 1, wind_speedz = 1;
                wind_accelx = 100 * rand() / RAND_MAX; 
                wind_accelz = 100 * rand() / RAND_MAX;   
            }
        }
    } while("life"=="happiness");

    do
    {   
       // std::cout<<boat.booster<<std::endl;
        if (boat.booster){   
            //std::cout<<"I came"<<std::endl;
            boost_duration--;
            boost_speedx += booster_accelx;
            boost_speedz += booster_accelz;
            int radius = 4.0f;
            boat.forward((boat.rotation - 90) * (pi / 180));
            boat.forward((boat.rotation - 90) * (pi / 180));
            boat.forward((boat.rotation - 90) * (pi / 180));
            //boat.position.x += radius * abs(sin(wind_speedx));
            //boat.position.z += radius * abs(cos(wind_speedz));
            if (boost_duration < 0)
            {
                boost_duration = 300;
                boat.booster = 0;
            }
        }
    } while ("iiit" == "happiness");
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    int randx = 0;
    int randz = 0;
    int ran_x = 0;
    int ran_z = 0;
    sea  =  Water(0, 40, 0, COLOR_BLUE);

    for(int i = 0; i < wavy; i++){
        randx = rand() % 6000;
        randz = rand() % 6000;
        wave[i] = Waves(randx - 1000, 60 , randz - 4000, COLOR_WAVE);
    }

    for(int i = 0; i < barry; i++){
        randx = rand() % 10000; 
        
        ran_x = randx-5000;
        
        if(ran_x + 500 > 0 && ran_x < 0)
            ran_x -= 5500;
        else if(ran_x - 500 < 0 && ran_x > 0)
            ran_x += 500;
        
        randz = rand() % 10000;
        ran_z = randz-5000;
        
        if(ran_z + 560 > 0 && ran_z - 60 < 0)
            ran_z-=500;
        else if(ran_z - 560 < 0 && ran_z - 60 > 0)
            ran_x+=500;

        barrel[i] = Barrel(ran_x, 60 , ran_z, 6);
    }

    for(int i = 0; i < barry; i++){

        randx = rand() % 10000;

        ran_x = randx - 5000;

        if(ran_x + 100 > 0 && ran_x < 0)
            ran_x -= 100;
        if(ran_x - 100 < 0 && ran_x > 0)
            ran_x += 100;

        randz = rand() % 10000;
        ran_z = randz - 5000;

        if(ran_z + 260 > 0 && ran_z - 60 < 0)
            ran_z -= 160;
        if(ran_z - 260 < 0 && ran_z - 60 > 0)
            ran_x += 160;

        rock[i] = Rocks(ran_x, 60 , ran_z, COLOR_GREY);
    }
    canon = Canon(0, 62, 40);

    for(int i = 0; i < gif; i++) {

        int g_barrel = rand() % 50;

        if ((barrel[g_barrel].ingift + i) % 4 != 0){

            gift[i++] = Gifts(barrel[g_barrel].position.x + 10, barrel[g_barrel].position.y, barrel[g_barrel].position.z - 20, COLOR_BALL5);
        }
        
        while(barrel[g_barrel].ngift!=-1) {
            g_barrel = rand() % 50;
        }
        
        gift[i] = Gifts(barrel[g_barrel].position.x + 10, barrel[g_barrel].position.y + 40, barrel[g_barrel].position.z - 20, COLOR_BALL5);
    }

    for(int i = 0; i < emo; i++) {

        randx = rand() % 10000;

        ran_x = randx - 3000;

        if(ran_x + 100 > 0 && ran_x < 0)
            ran_x -= 100;
        if(ran_x - 100 < 0 && ran_x > 0)
            ran_x += 100;

        randz = rand() % 10000;
        ran_z = randz - 3000;

        if(ran_z + 260 > 0 && ran_z - 60 < 0)
            ran_z -= 160;
        if(ran_z - 260 < 0 && ran_z - 60 > 0)
            ran_z += 160;

        enemy[i] = Monster(ran_x, 68, ran_z, 2, COLOR_BALL3);
    }

    boat = Boat(0, 60, 40);
    boat.rotation = 90;
    boss = Boss(boat.position.x, 68, boat.position.z+500, 2);
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;
    level = 1;

    window = initGLFW(width, height);

    initGL (window, width, height);

    pid = fork();
    if (pid == 0)
    {
        while (sound)
        {
            audio_init();
            audio_play();
            audio_close();
        }
        _exit(0);
    }
    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {


            if (t60.processTick()) {
                // 60 fps
                // OpenGL Draw commands
                level = (boat.points) / 40 + 1;
                draw();
                // Swap Frame Buffer in double buffering
                glfwSwapBuffers(window);
                tick_elements();
                tick_input(window);
                speed_camera();

                char str1[30];
                sprintf(str1, "%d", boat.points);
                char final_str[120] = "Score : ";
                strcat(final_str, str1);

                char str2[10];
                sprintf(str2, "%d", boat.lives);
                strcat(final_str, "      Lives : ");
                strcat(final_str, str2);

                char str3[10];
                sprintf(str3, "%d", boat.health);
                strcat(final_str, "      Health : ");
                strcat(final_str, str3);

                char str4[10];
                sprintf(str4, "%d", level);
                strcat(final_str, "      Level : ");
                strcat(final_str, str4);

                char str5[10];
                sprintf(str5, "%d", game_time);
                strcat(final_str, "   Game Time:");
                strcat(final_str, str5);
                glfwSetWindowTitle(window, final_str);
                game_time +=1;

                if (boat.lives <= 0) {
                    system("clear");
                    cout << "Game Over!" << endl;
                    cout << "Score: " << boat.points << " Level: " << level << endl;
                    quit(window);
                }

                tick_elements();
                tick_input(window);
                
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision_pole(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) < (a.length + b.length) / 2) && (abs(a.z - b.z) < (a.width + b.width) / 2) && (abs(a.y - b.y) < (a.height + b.height + 30.0f) / 2);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) < (a.length + b.length)/2) && (abs(a.z - b.z) < (a.width + b.width)/2) && (abs(a.y - b.y) < (a.height + b.height)/2);
}


void reset_screen() {
    Matrices.projection = glm::perspective(45.0f, 1.0f, 50.0f, 10000.0f);
}

void change_camera(){
    //std::cout<<view<<std::endl;
    view = (view+1)%5;
}

void speed_camera(){
    float theta = (boat.rotation-90)*(pi/180);
    float pip = 10.0f;
    float sins = pip*sin(theta);
    float coss = pip*cos(theta);  

    if (!view) {
            camera_x = boat.position.x + 3 * sins;
            camera_y = boat.position.y + pip;
            camera_z = boat.position.z + 3 * coss;

            target_x = boat.position.x - 4 * sins;
            target_y = boat.position.y + pip;
            target_z = boat.position.z - 4 * coss;
//            break;

    }
    else {
        if (view == 1) {
            camera_x = boat.position.x + 8 * sins;
            camera_y = 9*pip;
            camera_z = boat.position.z + 8 * coss;

            target_x = boat.position.x - sins;
            target_y = 9*pip;
            target_z = boat.position.z - coss;
  //          break;

        }
        else if(view == 2) {
            camera_y = 100;
  //          break;
//
        }
        else if(view == 3) {
            camera_x = boat.position.x;
            camera_y = 20*pip;
            camera_z = boat.position.z;

            target_x = boat.position.x - cos(pi);
            target_y = boat.position.y;
            target_z = boat.position.z;
    //        break;

        }
        else if(view == 4) {
            camera_x = boat.position.x + pip*pip;
            camera_y = pip*pip;
            camera_z = boat.position.z;

            target_x = boat.position.x + sin(pi);
            target_y = boat.position.y + sin(2*pi);
            target_z = boat.position.z + sin(pi);
      //      break;

        }
    }
}

void heli_camera(float x, float y){
    if (view != 2)
    {
        return;
    }
    if (view%2 == 0) {
        if(view - 2 == 0){
            target_x = boat.position.x + x - 400;
            if(y - 400 <= 0 ){
                target_y = boat.position.y+ (400-y)/2;
            }
        }
    }
}

void zoom_camera(int type){
    if(view!=2){
        return;
    }
    else {

        float n = target_z-camera_z;
        if(type==1){
            if(camera_z - target_z > 10)
                camera_z-=10;
        }
        else if(type==-1){
            camera_z+=10;
        }
        camera_x = (target_x - camera_x) * (camera_z - target_z) / n + target_x;
        camera_y = (target_y - camera_y) * (camera_z - target_z) / n + target_y;
    }
}
