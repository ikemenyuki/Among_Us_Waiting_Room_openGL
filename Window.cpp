#include "Window.h"
#include <string>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <cstdlib>

// Window Properties
int Window::width;
int Window::height;
const char* Window::windowTitle = "GLFW Starter Project";
std::string path = "shaders/";

Geometry* astronaut_red;
Geometry* astronaut_blue;
Geometry* astronaut_brown;
Geometry* astronaut_cyan;
Geometry* astronaut_darkGreen;
Geometry* astronaut_lime;
Geometry* astronaut_orange;
Geometry* astronaut_pink;
Geometry* astronaut_purple;
Geometry* astronaut_black;
Geometry* astronaut_white;
Geometry* astronaut_yellow;
Geometry* lobby;
Geometry* s;
// static boundings
BoundingSphere* sphere1;
BoundingSphere* sphere2;
BoundingPlane* leftWall;
BoundingPlane* rightWall;
BoundingPlane* top;
BoundingPlane* bottom;
BoundingPlane* leftDiog;
BoundingPlane* rightDiog;

ParticleSystem *particleSystem;
ParticleSystem *particleSystem2;
vector<ParticleSystem*> particles;
vector<ParticleSystem*> particles_black;
vector<ParticleSystem*> particles_blue;
vector<ParticleSystem*> particles_brown;
vector<ParticleSystem*> particles_cyan;

vector<ParticleSystem*> particles_disappear;
vector<ParticleSystem*> particles_black_disappear;
vector<ParticleSystem*> particles_blue_disappear;
vector<ParticleSystem*> particles_brown_disappear;
vector<ParticleSystem*> particles_cyan_disappear;

// particles
//PointCloud* particles;
//Cube* cube;
//ParticleGenerator* Particles;
// vectors to store the boundings
vector<BoundingSphere*> spheres;
vector<BoundingPlane*> planes;
BoundingSphere* tmpSphere;

// player
Geometry *player;

// current time
double curr_time;
// brown player
double brown_occur;
double brown_disappear;
// black player
double black_occur;
double black_disappear;
// blue player
double blue_occur;
double blue_disappear;
// cyan player
double cyan_occur;
double cyan_disappear;

double prev_black_dis = 10000000000000000, prev_blue_dis = 10000000000000000, prev_brown_dis = 10000000000000000, prev_cyan_dis = 10000000000000000;
double mark_black, mark_blue, mark_brown, mark_cyan;

double Window::xprev = 0, Window::xcur;
double Window::yprev = 0, Window::ycur;
bool Window::enabled = false;

//int sphereSize = 10;
// Camera Matrices 
// Projection matrix:
glm::mat4 Window::projection;
// View Matrix:
glm::vec3 Window::eyePos(0, 40, 20);            // Camera position.
glm::vec3 Window::lookAtPoint(0, 0, 0);        // The point we are looking at.
glm::vec3 Window::upVector(0, 1, 0);    	// The up direction of the camera.
glm::mat4 Window::view = glm::lookAt(Window::eyePos, Window::lookAtPoint, Window::upVector);

// Shader Program ID
GLuint Window::shaderProgram;
GLuint Window::lobbyShader;
GLuint Window::particleShader;

bool Window::initializeProgram() {
	// Create a shader program with a vertex shader and a fragment shader.
	shaderProgram = LoadShaders("shaders/shader.vert", "shaders/shader.frag");
    lobbyShader = LoadShaders("shaders/lobbyShader.vert", "shaders/lobbyShader.frag");
    particleShader = LoadShaders("shaders/particleShader.vert", "shaders/particleShader.frag");
//    skyboxShader = LoadShaders("shaders/skybox.vert", "shaders/skybox.frag");
//    sphereShader  = LoadShaders("shaders/containerShader.vert", "shaders/containerShader.frag");

	// Check the shader program.
	if (!shaderProgram)
	{
		std::cerr << "Failed to initialize shader program" << std::endl;
		return false;
	}

	return true;
}

bool Window::initializeObjects()
{
    srand ( time(NULL) );
////    cube = new Cube(1.f);
//    particles = new PointCloud("foo", 10);
    lobby= new Geometry("shaders/lobby/amongus_lobby.obj", lobbyShader);
    lobby->setColor(glm::vec3(0.9f,0.9f,0.9f));
    lobby->setMatrix(glm::scale(glm::mat4(1), glm::vec3(0.9f)));
    
    // set static boundings
    sphere1 = new BoundingSphere(2.0f, glm::vec3(-9.00f, 0.0f, 10.5f), "sphere1");
    sphere2 = new BoundingSphere(2.0f, glm::vec3(9.7f, 0.0f, 8.0f), "sphere2");
    spheres.push_back(sphere1);
    spheres.push_back(sphere2);
    
    float leftX = -16.132122 * 0.9;
    leftWall = new BoundingPlane(glm::vec3(leftX, 1, 1), glm::vec3(1.f, 0.f, 0.f), "leftWall");
    
    float rightX = 16.132122 * 0.9;
    rightWall = new BoundingPlane(glm::vec3(rightX, 1, 1), glm::vec3(-1.f, 0.f, 0.f), "rightWall");
    
    top = new BoundingPlane(glm::vec3(0.0f, 0.0f, 3.1f), glm::vec3(0.f, 0.f, 1.f), "top");
    bottom = new BoundingPlane(glm::vec3(0.0f, 0.0f, 19.f), glm::vec3(0.f, 0.f, -1.f), "bottom");
    rightDiog = new BoundingPlane(glm::vec3(13.0f, 0.0f, 17.7f), glm::normalize(glm::vec3(-1.f, 0.f, -1.f)), "rightDiog");
    leftDiog = new BoundingPlane(glm::vec3(-13.0f, 0.0f, 17.7f), glm::normalize(glm::vec3(1.f, 0.f, -1.f)), "leftDiog");
    
    planes.push_back(leftWall);
    planes.push_back(rightWall);
    planes.push_back(top);
    planes.push_back(bottom);
    planes.push_back(leftDiog);
    planes.push_back(rightDiog);
    
    cout << glm::to_string(glm::rotate(glm::radians(90.f), glm::vec3(0, 0, 1))) << endl;
    
    // astronauts
    astronaut_red = new Geometry("shaders/astronauts/amongus_astro_still.obj", shaderProgram);
    astronaut_red->setColor(glm::vec3(197.0f/255.0f, 18.0f/255.0f, 17.0f/255.0f));
    float x_ = static_cast<float>(rand()%30 - 16.132122 * 0.9);
    float z_ = static_cast<float>(rand()%13 + 3.3);
    BoundingSphere* tmp = new BoundingSphere(1.f, glm::vec3(x_, 0.f, z_), " ");
    while (true) {
        srand ( time(NULL) );
        tmp->center = glm::vec3(x_, 0.f, z_);
        if (!all_collision(tmp))
            break;
        else {
            x_ = static_cast<float>(rand()%30 - 16.132122 * 0.9);
            z_ = static_cast<float>(rand()%13 + 3.3);
        }
    }
    glm::vec3 pos(x_, 0.f, z_);
    astronaut_red->modelM *= glm::translate(pos);
    astronaut_red->setSphere(new BoundingSphere(1.f, glm::vec3(x_, 0, z_), "red"));
    spheres.push_back(astronaut_red->boundingSphere);
//    particleSystem = new ParticleSystem(astronaut_red->boundingSphere->center);
//    particleSystem2 = new ParticleSystem(astronaut_red->boundingSphere->center);
    for (int i = 0; i < 50; i++){
        ParticleSystem* p = new ParticleSystem(astronaut_red->boundingSphere->center);
        p->model = glm::mat4(1);
        p->model *= glm::scale(glm::vec3(.5f));
        p->model *= glm::translate(p->center);
        p->model *= glm::translate(glm::vec3(0.f,5.f, 0.f));
        particles.push_back(p);
//        cout << i << endl;
    }
//    cout << glm::to_string(particleSystem->model) << endl;
//    particleSystem->model = glm::mat4(1);
//    particleSystem->model *= glm::translate(particleSystem->center);
//    particleSystem->model *= glm::translate(glm::vec3(0.f, 5.f, 0.f));
//    particleSystem->model *= glm::scale(glm::vec3(.2f));
//
//    particleSystem2->model = glm::mat4(1);
//    particleSystem2->model *= glm::translate(particleSystem2->center);
//    particleSystem2->model *= glm::translate(glm::vec3(0.f, 5.f, 0.f));
//    particleSystem2->model *= glm::scale(glm::vec3(.2f));
//    particleSystem->model *= glm::translate(glm::vec3(0.f, 5.f, 0.f));
//    particleSystem->model *= glm::scale(glm::vec3(.1));
//    Particles = new ParticleGenerator(particleShader, 500);
    
    astronaut_black = new Geometry("shaders/astronauts/amongus_astro_still.obj", shaderProgram);
    astronaut_black->setColor(glm::vec3(62.0f/255.0f, 71.0f/255.0f, 78.0f/255.0f));
    while (true) {
        x_ = static_cast<float>(rand()%30 - 16.132122 * 0.9);
        z_ = static_cast<float>(rand()%13 + 3.3);
        tmp->center = glm::vec3(x_, 0.f, z_);
        if (!all_collision(tmp))
            break;
        else {
            x_ = static_cast<float>(rand()%30 - 16.132122 * 0.9);
            z_ = static_cast<float>(rand()%13 + 3.3);
        }
    }
    glm::vec3 pos1(x_, 0.f, z_);
    astronaut_black->modelM *= glm::translate(pos1);
    // set bounding sphere for cyan astronaut
    astronaut_black->setSphere(new BoundingSphere(1.f, glm::vec3(x_, 0, z_), "black"));
    spheres.push_back(astronaut_black->boundingSphere);;
    astronaut_black->npc_dir = glm::radians(static_cast<float>(rand() % 360));
    astronaut_black->modelM *= glm::rotate(glm::radians(90.f), glm::vec3(0.0f,1.0f,0.0f));
    astronaut_black->modelM *= glm::rotate(astronaut_black->npc_dir, glm::vec3(0.0f,1.0f,0.0f));
    astronaut_black->boundingSphere->direction = astronaut_black->npc_dir;
    black_occur = static_cast<double>(rand() % 10);
    while (black_disappear < black_occur + 10)
        black_disappear = rand();
    vector<ParticleSystem*> tmp1;
    particles_black = tmp1;
    for (int i = 0; i < 50; i++){
        ParticleSystem* p = new ParticleSystem(astronaut_black->boundingSphere->center);
        p->model = glm::mat4(1);
        p->model *= glm::scale(glm::vec3(.5f));
        p->model *= glm::translate(p->center);
        p->model *= glm::translate(glm::vec3(0.f,5.f, 0.f));
        particles_black.push_back(p);
//        cout << i << endl;
    }
    // set bounding sphere for black astronaut
    astronaut_blue = new Geometry("shaders/astronauts/amongus_astro_still.obj", shaderProgram);
    astronaut_blue->setColor(glm::vec3(19.0f/255.0f, 46.0f/255.0f, 209.0f/255.0f));
    while (true) {
        x_ = static_cast<float>(rand()%30 - 16.132122 * 0.9);
        z_ = static_cast<float>(rand()%13 + 3.3);
        tmp->center = glm::vec3(x_, 0.f, z_);
        if (!all_collision(tmp))
            break;
        else {
            x_ = static_cast<float>(rand()%30 - 16.132122 * 0.9);
            z_ = static_cast<float>(rand()%13 + 3.3);
        }
    }
    glm::vec3 pos2(x_, 0.f, z_);
    astronaut_blue->modelM *= glm::translate(pos2);
    // set bounding sphere for blue astronaut
    astronaut_blue->setSphere(new BoundingSphere(1.f, glm::vec3(x_, 0, z_), "blue"));
    spheres.push_back(astronaut_blue->boundingSphere);
    astronaut_blue->npc_dir = glm::radians(static_cast<float>(rand() % 360));
    astronaut_blue->modelM *= glm::rotate(glm::radians(90.f), glm::vec3(0.0f,1.0f,0.0f));
    astronaut_blue->modelM *= glm::rotate(astronaut_blue->npc_dir, glm::vec3(0.0f,1.0f,0.0f));
    astronaut_blue->boundingSphere->direction = astronaut_blue->npc_dir;
    blue_occur = static_cast<double>(rand() % 10);
    while (blue_disappear < blue_occur + 10)
        blue_disappear = rand();
    vector<ParticleSystem*> tmp2;
    particles_blue = tmp2;
    for (int i = 0; i < 50; i++){
        ParticleSystem* p = new ParticleSystem(astronaut_blue->boundingSphere->center);
        p->model = glm::mat4(1);
        p->model *= glm::scale(glm::vec3(.5f));
        p->model *= glm::translate(p->center);
        p->model *= glm::translate(glm::vec3(0.f,5.f, 0.f));
        particles_blue.push_back(p);
//        cout << i << endl;
    }
    
    astronaut_brown = new Geometry("shaders/astronauts/amongus_astro_still.obj", shaderProgram);
    astronaut_brown->setColor(glm::vec3(113.0f/255.0f, 73.0f/255.0f, 29.0f/255.0f));
    while (true) {
        x_ = static_cast<float>(rand()%30 - 16.132122 * 0.9);
        z_ = static_cast<float>(rand()%13 + 3.3);
        tmp->center = glm::vec3(x_, 0.f, z_);
        if (!all_collision(tmp))
            break;
        else {
            x_ = static_cast<float>(rand()%30 - 16.132122 * 0.9);
            z_ = static_cast<float>(rand()%13 + 3.3);
        }
    }
    glm::vec3 pos3(x_, 0.f, z_);
    astronaut_brown->modelM *= glm::translate(pos3);
    // set bounding sphere for brown astronaut
    astronaut_brown->setSphere(new BoundingSphere(1.f, glm::vec3(x_, 0, z_), "brown"));
    spheres.push_back(astronaut_brown->boundingSphere);
    astronaut_brown->npc_dir = glm::radians(static_cast<float>(rand() % 360));
    astronaut_brown->modelM *= glm::rotate(glm::radians(90.f), glm::vec3(0.0f,1.0f,0.0f));
    astronaut_brown->modelM *= glm::rotate(astronaut_brown->npc_dir, glm::vec3(0.0f,1.0f,0.0f));
    astronaut_brown->boundingSphere->direction = astronaut_brown->npc_dir;
    brown_occur = static_cast<double>(rand() % 10);
    while (brown_disappear < brown_occur + 10)
        brown_disappear = rand();
    vector<ParticleSystem*> tmp3;
    particles_brown = tmp3;
    for (int i = 0; i < 50; i++){
        ParticleSystem* p = new ParticleSystem(astronaut_brown->boundingSphere->center);
        p->model = glm::mat4(1);
        p->model *= glm::scale(glm::vec3(.5f));
        p->model *= glm::translate(p->center);
        p->model *= glm::translate(glm::vec3(0.f,5.f, 0.f));
        particles_brown.push_back(p);
    //        cout << i << endl;
    }
    
    astronaut_cyan = new Geometry("shaders/astronauts/amongus_astro_still.obj", shaderProgram);
    astronaut_cyan->setColor(glm::vec3(57.0f/255.0f, 254.0f/255.0f, 221.0f/255.0f));
    while (true) {
        x_ = static_cast<float>(rand()%30 - 16.132122 * 0.9);
        z_ = static_cast<float>(rand()%13 + 3.3);
        tmp->center = glm::vec3(x_, 0.f, z_);
        if (!all_collision(tmp))
            break;
        else {
            x_ = static_cast<float>(rand()%30 - 16.132122 * 0.9);
            z_ = static_cast<float>(rand()%13 + 3.3);
        }
    }
    glm::vec3 pos4(x_, 0.f, z_);
    astronaut_cyan->modelM *= glm::translate(pos4);
    // set bounding sphere for cyan astronaut
    astronaut_cyan->setSphere(new BoundingSphere(1.f, glm::vec3(x_, 0, z_), "cyan"));
    spheres.push_back(astronaut_cyan->boundingSphere);
    astronaut_cyan->npc_dir = glm::radians(static_cast<float>(rand() % 360));
    astronaut_cyan->modelM *= glm::rotate(glm::radians(90.f), glm::vec3(0.0f,1.0f,0.0f));
    astronaut_cyan->modelM *= glm::rotate(astronaut_cyan->npc_dir, glm::vec3(0.0f,1.0f,0.0f));
    astronaut_cyan->boundingSphere->direction = astronaut_cyan->npc_dir;
    cyan_occur = static_cast<double>(rand() % 10);
    while (cyan_disappear < cyan_occur + 10)
        cyan_disappear = rand();
    vector<ParticleSystem*> tmp4;
    particles_cyan = tmp4;
    for (int i = 0; i < 50; i++){
        ParticleSystem* p = new ParticleSystem(astronaut_cyan->boundingSphere->center);
        p->model = glm::mat4(1);
        p->model *= glm::scale(glm::vec3(.5f));
        p->model *= glm::translate(p->center);
        p->model *= glm::translate(glm::vec3(0.f,5.f, 0.f));
        particles_cyan.push_back(p);
//        cout << i << endl;
    }
    
    s = new Geometry("shaders/sphere.obj", shaderProgram);
    s->modelM =  glm::translate(glm::vec3(13.0f, 0.0f, 15.5f)) * glm::scale(glm::vec3(1));
    s->setColor(glm::vec3(57.0f/255.0f, 254.0f/255.0f, 221.0f/255.0f));
    // set player to red astronaut
    player = astronaut_red;
    player->boundingSphere->isMoving = false;
    
//    cout  << "black time is " << black_occur << " " << black_disappear << endl;
//    cout  << "blue time is " << blue_occur << " " << blue_disappear << endl;
//    cout  << "brown time is " << brown_occur << " " << brown_disappear << endl;
//    cout  << "cyan time is " << cyan_occur << " " << cyan_disappear << endl;
    
	return true;
}

void Window::cleanUp()
{
	// Deallcoate the objects.
//    delete cube;
//    delete cubePoints;
//    delete skybox;
//    delete sphere;
//    delete astronaut_red;
//    delete astronaut_blue;
//    delete astronaut_brown;
//    delete astronaut_cyan;
//    delete astronaut_black;
//    delete lobby;
//    delete s;
//    // static boundings
//    delete sphere1;
//    delete sphere2;
//    delete leftWall;
//    delete rightWall;
//    delete top;
//    delete bottom;
//    delete leftDiog;
//    delete rightDiog;
//
//    // dynamic boundings
//    delete sphere_red;
//    delete sphere_black;
//    delete sphere_blue;
//    delete sphere_brown;
//    delete sphere_cyan;
//
//    delete tmpSphere;
//
//    // player
//    delete player;
	// Delete the shader program.
	glDeleteProgram(shaderProgram);
    
//    glDeleteProgram(skyboxShader);
//    glDeleteProgram(sphereShader);
}

GLFWwindow* Window::createWindow(int width, int height)
{
	// Initialize GLFW.
	if (!glfwInit())
	{
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return NULL;
	}

	// 4x antialiasing.
	glfwWindowHint(GLFW_SAMPLES, 4);

#ifdef __APPLE__ 
	// Apple implements its own version of OpenGL and requires special treatments
	// to make it uses modern OpenGL.

	// Ensure that minimum OpenGL version is 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Enable forward compatibility and allow a modern OpenGL context
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// Create the GLFW window.
	GLFWwindow* window = glfwCreateWindow(width, height, windowTitle, NULL, NULL);

	// Check if the window could not be created.
	if (!window)
	{
		std::cerr << "Failed to open GLFW window." << std::endl;
		glfwTerminate();
		return NULL;
	}

	// Make the context of the window.
	glfwMakeContextCurrent(window);

#ifndef __APPLE__
	// On Windows and Linux, we need GLEW to provide modern OpenGL functionality.

	// Initialize GLEW.
	if (glewInit())
	{
		std::cerr << "Failed to initialize GLEW" << std::endl;
		return NULL;
	}
#endif

	// Set swap interval to 1.
	glfwSwapInterval(0);

	// Call the resize callback to make sure things get drawn immediately.
	Window::resizeCallback(window, width, height);

	return window;
}

void Window::resizeCallback(GLFWwindow* window, int width, int height)
{
#ifdef __APPLE__
	// In case your Mac has a retina display.
	glfwGetFramebufferSize(window, &width, &height); 
#endif
	Window::width = width;
	Window::height = height;
	// Set the viewport size.
	glViewport(0, 0, width, height);

	// Set the projection matrix.
	Window::projection = glm::perspective(glm::radians(60.0), 
								double(width) / (double)height, 1.0, 1000.0);
}

void Window::idleCallback()
{
	// Perform any necessary updates here
//    astronaut_red->draw(glm::mat4(1));
    double ti = glfwGetTime();
    for (int i = 0; i < particles.size(); i++){
        particles[i]->update(abs(ti - curr_time));
    }
    if (curr_time >= blue_occur && curr_time <= blue_disappear){
        for (int i = 0; i < particles_blue.size(); i++){
            particles_blue[i]->update(abs(ti - curr_time));
        }
    }
    if (curr_time >= black_occur && curr_time <= black_disappear){
        for (int i = 0; i < particles_black.size(); i++){
            particles_black[i]->update(abs(ti - curr_time));
        }
    }
    if (curr_time >= brown_occur && curr_time <= brown_disappear){
        for (int i = 0; i < particles_brown.size(); i++){
            particles_brown[i]->update(abs(ti - curr_time));
        }
    }
    if (curr_time >= cyan_occur && curr_time <= cyan_disappear){
        for (int i = 0; i < particles_cyan.size(); i++){
            particles_cyan[i]->update(abs(ti - curr_time));
        }
    }
    if (prev_black_dis < curr_time){
        if (prev_black_dis < mark_black + 3){
            for (int i = 0; i < particles_black_disappear.size(); i++){
                particles_black_disappear[i]->update(abs(ti - curr_time));
            }
            prev_black_dis += 0.05;
        }
        else {
            prev_black_dis = 1000000000000;
            vector<ParticleSystem*> tmp2;
            particles_black = tmp2;
            for (int i = 0; i < 50; i++){
                ParticleSystem* p = new ParticleSystem(astronaut_black->boundingSphere->center);
                p->model = glm::mat4(1);
                p->model *= glm::scale(glm::vec3(.5f));
                p->model *= glm::translate(p->center);
                p->model *= glm::translate(glm::vec3(0.f,5.f, 0.f));
                particles_black.push_back(p);
        //        cout << i << endl;
            }
        }
    }
    if (prev_blue_dis < curr_time){
        if (prev_blue_dis < mark_blue + 3){
            for (int i = 0; i < particles_blue_disappear.size(); i++){
                particles_blue_disappear[i]->update(abs(ti - curr_time));
            }
            prev_blue_dis += 0.05;
        }
        else {
            prev_blue_dis = 1000000000000;
            vector<ParticleSystem*> tmp2;
            particles_blue = tmp2;
            for (int i = 0; i < 50; i++){
                ParticleSystem* p = new ParticleSystem(astronaut_blue->boundingSphere->center);
                p->model = glm::mat4(1);
                p->model *= glm::scale(glm::vec3(.5f));
                p->model *= glm::translate(p->center);
                p->model *= glm::translate(glm::vec3(0.f,5.f, 0.f));
                particles_blue.push_back(p);
        //        cout << i << endl;
            }
        }
    }
    if (prev_brown_dis < curr_time){
        if (prev_brown_dis < mark_brown + 3){
            for (int i = 0; i < particles_brown_disappear.size(); i++){
                particles_brown_disappear[i]->update(abs(ti - curr_time));
            }
            prev_brown_dis += 0.05;
        }
        else {
            prev_brown_dis = 1000000000000;
            vector<ParticleSystem*> tmp2;
            particles_brown = tmp2;
            for (int i = 0; i < 50; i++){
                ParticleSystem* p = new ParticleSystem(astronaut_brown->boundingSphere->center);
                p->model = glm::mat4(1);
                p->model *= glm::scale(glm::vec3(.5f));
                p->model *= glm::translate(p->center);
                p->model *= glm::translate(glm::vec3(0.f,5.f, 0.f));
                particles_brown.push_back(p);
        //        cout << i << endl;
            }
        }
    }
    if (prev_cyan_dis < curr_time){
        if (prev_cyan_dis < mark_cyan + 3){
            for (int i = 0; i < particles_cyan_disappear.size(); i++){
                particles_cyan_disappear[i]->update(abs(ti - curr_time));
            }
            prev_cyan_dis += 0.05;
        }
        else {
            prev_cyan_dis = 1000000000000;
            vector<ParticleSystem*> tmp2;
            particles_cyan = tmp2;
            for (int i = 0; i < 50; i++){
                ParticleSystem* p = new ParticleSystem(astronaut_cyan->boundingSphere->center);
                p->model = glm::mat4(1);
                p->model *= glm::scale(glm::vec3(.5f));
                p->model *= glm::translate(p->center);
                p->model *= glm::translate(glm::vec3(0.f,5.f, 0.f));
                particles_cyan.push_back(p);
        //        cout << i << endl;
            }
        }
    }
    
//    particleSystem->update(abs(ti - curr_time));
//    particleSystem2->update(abs(ti - curr_time));
}

void Window::displayCallback(GLFWwindow* window)
{	
	// Clear the color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    for (int i = 0; i < particleSystem->MAX_PARTICLES; i++)
//    particleSystem->draw(view, projection, particleShader);
//    particleSystem2->draw(view, projection, particleShader);
//    cout << particles[10]->particles[0].life << endl;
    for (int i = 0; i < particles.size(); i++){
//        cout << particles[i]->scale << endl;
        particles[i]->draw(view, projection, particleShader);
    }
	// Render the objects
//    cout << "i am going to print sth" << endl;
//    cout << astronaut_cyan->boundingSphere->direction << endl;
    lobby->draw(glm::mat4(1));
    //lobby->draw(glm::scale(glm::mat4(1.0f), glm::vec3(5.0f)));
//    particles->draw(view, projection, particleShader);
    curr_time = glfwGetTime();
    if (black_disappear < curr_time){
        prev_black_dis = black_disappear;
        mark_black = prev_black_dis;
        vector<ParticleSystem*> tmp5;
        particles_black_disappear = tmp5;
        for (int i = 0; i < 50; i++){
            ParticleSystem* p = new ParticleSystem(astronaut_black->boundingSphere->center);
            p->model = glm::mat4(1);
            p->model *= glm::scale(glm::vec3(.5f));
            p->model *= glm::translate(p->center);
            p->model *= glm::translate(glm::vec3(0.f,5.f, 0.f));
            p->color = glm::vec3(1, 0, 0);
            particles_black_disappear.push_back(p);
    //        cout << i << endl;
        }
        black_occur = static_cast<double>(rand() % 10) + curr_time;
        while (black_disappear < black_occur + 10)
            black_disappear = rand();
    }
    if (blue_disappear < curr_time){
        prev_blue_dis = blue_disappear;
        mark_blue = prev_blue_dis;
        vector<ParticleSystem*> tmp5;
        particles_blue_disappear = tmp5;
        for (int i = 0; i < 50; i++){
            ParticleSystem* p = new ParticleSystem(astronaut_blue->boundingSphere->center);
            p->model = glm::mat4(1);
            p->model *= glm::scale(glm::vec3(.5f));
            p->model *= glm::translate(p->center);
            p->model *= glm::translate(glm::vec3(0.f,5.f, 0.f));
            p->color = glm::vec3(1, 0, 0);
            particles_blue_disappear.push_back(p);
    //        cout << i << endl;
        }
        blue_occur = static_cast<double>(rand() % 10) + curr_time;
        while (blue_disappear < blue_occur + 10)
            blue_disappear = rand();
    }
    if (brown_disappear < curr_time){
        prev_brown_dis = brown_disappear;
        mark_brown = prev_brown_dis;
        vector<ParticleSystem*> tmp5;
        particles_brown_disappear = tmp5;
        for (int i = 0; i < 50; i++){
            ParticleSystem* p = new ParticleSystem(astronaut_brown->boundingSphere->center);
            p->model = glm::mat4(1);
            p->model *= glm::scale(glm::vec3(.5f));
            p->model *= glm::translate(p->center);
            p->model *= glm::translate(glm::vec3(0.f,5.f, 0.f));
            p->color = glm::vec3(1, 0, 0);
            particles_brown_disappear.push_back(p);
    //        cout << i << endl;
        }
        brown_occur = static_cast<double>(rand() % 10) + curr_time;
        while (brown_disappear < brown_occur + 10)
            brown_disappear = rand();
    }
    if (cyan_disappear < curr_time){
        prev_cyan_dis = cyan_disappear;
        mark_cyan = prev_cyan_dis;
        vector<ParticleSystem*> tmp5;
        particles_cyan_disappear = tmp5;
        for (int i = 0; i < 50; i++){
            ParticleSystem* p = new ParticleSystem(astronaut_cyan->boundingSphere->center);
            p->model = glm::mat4(1);
            p->model *= glm::scale(glm::vec3(.5f));
            p->model *= glm::translate(p->center);
            p->model *= glm::translate(glm::vec3(0.f,5.f, 0.f));
            p->color = glm::vec3(1, 0, 0);
            particles_cyan_disappear.push_back(p);
    //        cout << i << endl;
        }
        cyan_occur = static_cast<double>(rand() % 10) + curr_time;
        while (cyan_disappear < cyan_occur + 10)
            cyan_disappear = rand();
    }
//    cube->draw(view, projection, particleShader);
    astronaut_red->draw(glm::mat4(1));
    if (curr_time >= blue_occur && curr_time <= blue_disappear){
        if (astronaut_blue->npc_dir != astronaut_blue->boundingSphere->direction){
            astronaut_blue->modelM *= glm::rotate(astronaut_blue->boundingSphere->direction - astronaut_blue->npc_dir, glm::vec3(0.0f,1.0f,0.0f));
            astronaut_blue->npc_dir = astronaut_blue->boundingSphere->direction;
        }
        astronaut_blue->draw(glm::mat4(1));
        for (int i = 0; i < particles_blue.size(); i++){
            particles_blue[i]->draw(view, projection, particleShader);
        }
        move_blue();
    }
    else{
        if (prev_blue_dis < mark_blue + 3){
            for (int i = 0; i < particles_blue_disappear.size(); i++){
                particles_blue_disappear[i]->draw(view, projection, particleShader);
            }
        }
    }
    if (curr_time >= black_occur && curr_time <= black_disappear){
//        cout << astronaut_black->npc_dir << " " << astronaut_black->boundingSphere->direction << endl;
        if (astronaut_black->npc_dir != astronaut_black->boundingSphere->direction){
            astronaut_black->modelM *= glm::rotate(astronaut_black->boundingSphere->direction - astronaut_black->npc_dir, glm::vec3(0.0f,1.0f,0.0f));
            astronaut_black->npc_dir = astronaut_black->boundingSphere->direction;
        }
//        cout << "iamhere" << endl;
        astronaut_black->draw(glm::mat4(1));
        for (int i = 0; i < particles_black.size(); i++){
            particles_black[i]->draw(view, projection, particleShader);
        }
        move_black();
    }
    else{
        if (prev_black_dis < mark_black + 3){
            for (int i = 0; i < particles_black_disappear.size(); i++){
                particles_black_disappear[i]->draw(view, projection, particleShader);
            }
        }
    }
    if (curr_time >= brown_occur && curr_time <= brown_disappear){
        if (astronaut_brown->npc_dir != astronaut_brown->boundingSphere->direction){
            astronaut_brown->modelM *= glm::rotate(astronaut_brown->boundingSphere->direction - astronaut_brown->npc_dir, glm::vec3(0.0f,1.0f,0.0f));
            astronaut_brown->npc_dir = astronaut_brown->boundingSphere->direction;
        }
        astronaut_brown->draw(glm::mat4(1));
        for (int i = 0; i < particles_brown.size(); i++){
            particles_brown[i]->draw(view, projection, particleShader);
        }
        move_brown();
    }
    else{
        if (prev_brown_dis < mark_brown + 3){
            for (int i = 0; i < particles_brown_disappear.size(); i++){
                particles_brown_disappear[i]->draw(view, projection, particleShader);
            }
        }
    }
    if (curr_time >= cyan_occur && curr_time <= cyan_disappear){
//        cout << astronaut_cyan->npc_dir << " " << astronaut_cyan->boundingSphere->direction << endl;
        if (astronaut_cyan->npc_dir != astronaut_cyan->boundingSphere->direction){
            astronaut_cyan->modelM *= glm::rotate(astronaut_cyan->boundingSphere->direction - astronaut_cyan->npc_dir, glm::vec3(0.0f,1.0f,0.0f));
            astronaut_cyan->npc_dir = astronaut_cyan->boundingSphere->direction;
        }
//        cout << "iamhere" << endl;
        astronaut_cyan->draw(glm::mat4(1));
        for (int i = 0; i < particles_cyan.size(); i++){
            particles_cyan[i]->draw(view, projection, particleShader);
        }
        move_cyan();
    }
    else{
        if (prev_cyan_dis < mark_cyan + 3){
            for (int i = 0; i < particles_cyan_disappear.size(); i++){
                particles_cyan_disappear[i]->draw(view, projection, particleShader);
            }
        }
    }
    
    // draw particles
//    Particles->Update(0.1f, astronaut_red->boundingSphere, 2);
//    Particles->Draw();
//    Particles->Update(dt, *Ball, 2, glm::vec2(Ball->Radius / 2.0f));
	glfwPollEvents();
//    cout << astronaut_black->npc_dir << " " << astronaut_black->boundingSphere->direction << endl;
	// Swap buffers.
	glfwSwapBuffers(window);
}

void Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	/*
	 * TODO: Modify below to add your key callbacks.
	 */
	
	// Check for a key press.
	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			// Close the window. This causes the program to also terminate.
			glfwSetWindowShouldClose(window, GL_TRUE);				
			break;
        case GLFW_KEY_UP:
            switch (player->direction) {
                case 2:
                    player->modelM *= glm::rotate(glm::radians(180.f), glm::vec3(0.0f,1.0f,0.0f));
                    break;
                case 3:
                    player->modelM *= glm::rotate(glm::radians(-90.f), glm::vec3(0.0f,1.0f,0.0f));
                    break;
                case 1:
                    player->modelM *= glm::rotate(glm::radians(90.f), glm::vec3(0.0f,1.0f,0.0f));
                    break;
                default:
                    break;
            }
            player->direction = 0;
            tmpSphere = new BoundingSphere(player->boundingSphere->radius, player->boundingSphere->center, "red");
//                cout << glm::to_string(tmpSphere->center) << endl;
            tmpSphere->center.z -= 0.4;
                if (! all_collision(tmpSphere)){
                    player->boundingSphere->center.z -= 0.4;
        //            std::cout << glm::to_string(player->boundingSphere->center) << std::endl;
                    player->modelM *= glm::translate(glm::vec3(0, 0, 0.4));
                }
            break;
        
        case GLFW_KEY_DOWN:
            switch (player->direction) {
                case 0:
                    player->modelM *= glm::rotate(glm::radians(180.f), glm::vec3(0.0f,1.0f,0.0f));
                    break;
                case 3:
                    player->modelM *= glm::rotate(glm::radians(90.f), glm::vec3(0.0f,1.0f,0.0f));
                    break;
                case 1:
                    player->modelM *= glm::rotate(glm::radians(-90.f), glm::vec3(0.0f,1.0f,0.0f));
                    break;
                default:
                    break;
            }
            player->direction = 2;
            tmpSphere = new BoundingSphere(player->boundingSphere->radius, player->boundingSphere->center, "red");
            tmpSphere->center.z += 0.4;
            if (! all_collision(tmpSphere)){
            player->boundingSphere->center.z += 0.4;
//            std::cout << glm::to_string(player->boundingSphere->center) << std::endl;
            player->modelM *= glm::translate(glm::vec3(0, 0, 0.4));
            }
            break;
        
        case GLFW_KEY_RIGHT:
            switch (player->direction) {
                case 0:
                    player->modelM *= glm::rotate(glm::radians(-90.f), glm::vec3(0.0f,1.0f,0.0f));
                    break;
                case 2:
                    player->modelM *= glm::rotate(glm::radians(90.f), glm::vec3(0.0f,1.0f,0.0f));
                    break;
                case 3:
                    player->modelM *= glm::rotate(glm::radians(180.f), glm::vec3(0.0f,1.0f,0.0f));
                    break;
                default:
                    break;
            }
//                cout << player->direction << endl;
            player->direction = 1;
            tmpSphere = new BoundingSphere(player->boundingSphere->radius, player->boundingSphere->center, "red");
            tmpSphere->center.x += 0.4;
            if (! all_collision(tmpSphere)){
            player->boundingSphere->center.x += 0.4;
//            std::cout << glm::to_string(player->boundingSphere->center) << std::endl;
            player->modelM *= glm::translate(glm::vec3(0, 0, 0.4));
            }
            break;
        
        case GLFW_KEY_LEFT:
            switch (player->direction) {
                case 0:
                    player->modelM *= glm::rotate(glm::radians(90.f), glm::vec3(0.0f,1.0f,0.0f));
                    break;
                case 2:
                    player->modelM *= glm::rotate(glm::radians(-90.f), glm::vec3(0.0f,1.0f,0.0f));
                    break;
                case 1:
                    player->modelM *= glm::rotate(glm::radians(-180.f), glm::vec3(0.0f,1.0f,0.0f));
                    break;
                default:
                    break;
            }
//                cout << player->direction << endl;
            player->direction = 3;
            tmpSphere = new BoundingSphere(player->boundingSphere->radius, player->boundingSphere->center, "red");
            tmpSphere->center.x -= 0.4;
            if (! all_collision(tmpSphere)){
            player->boundingSphere->center.x -= 0.4;
//            std::cout << glm::to_string(player->boundingSphere->center) << std::endl;
            player->modelM *= glm::translate(glm::vec3(0, 0, 0.4));
            }
            break;
                
		default:
			break;
		}
	}
}

glm::vec3 Window::mapping(double xpos, double ypos){
    glm::vec3 v;
    float d;
    v.x = (2.0 * xpos - Window::width)/ Window::width;
    v.y = (Window::height - 2.0 * ypos)/ Window::height;
    v.z = 0.0;
    d = sqrt(v.x * v.x + v.y * v.y);
    d = (d < 1.0) ? d: 1.0;
    v.z = sqrt(1.001 - d * d);
    return glm::normalize(v);
    
}

void Window::mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
        if (button == GLFW_MOUSE_BUTTON_LEFT) {
            if(GLFW_PRESS == action){
                if (!xprev && !yprev) glfwGetCursorPos(window, &xprev, &yprev);
                enabled = true;
            }
            else if(GLFW_RELEASE == action){
                enabled = false;
                xprev = 0; yprev = 0;
            }
        }
    }

void Window::cursor_position_callback(GLFWwindow* window, double xpos, double ypos){
        if (enabled){
            glm::vec3 vec_prev = mapping(xprev, yprev);
            glm::vec3 vec_cur = mapping(xpos, ypos);
            glm::vec3 direction = vec_cur - vec_prev;
//            float velocity = glm::length(direction);
            if (direction.y > 0.0001){
                if (eyePos.z > 0)
                    eyePos.y += 1;
                else eyePos.y -= 1;
                if (eyePos.y > 0)
                    eyePos.z -= 1;
                else eyePos.z += 1;
                xprev = xpos;
                yprev = ypos;
                view = glm::lookAt(Window::eyePos, Window::lookAtPoint, Window::upVector);
            }
            else if (direction.y < 0.0001){
                if (eyePos.z > 0)
                    eyePos.y -= 1;
                else eyePos.y += 1;
                if (eyePos.y > 0)
                    eyePos.z += 1;
                else eyePos.z -= 1;
                xprev = xpos;
                yprev = ypos;
                view = glm::lookAt(Window::eyePos, Window::lookAtPoint, Window::upVector);
            }
        }
}

void Window::scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
    if (yoffset > 0){
        eyePos.x *= 1.02;
        eyePos.y *= 1.02;
        eyePos.z *= 1.02;
    }
    else if (yoffset < 0){
        eyePos.x /= 1.02;
        eyePos.y /= 1.02;
        eyePos.z /= 1.02;
    }
    view = glm::lookAt(Window::eyePos, Window::lookAtPoint, Window::upVector);
}

bool Window::sphere_collision(BoundingSphere* s1, BoundingSphere* s2){
    glm::vec3 center1 = s1->center;
    glm::vec3 center2 = s2->center;
    float dist_center = sqrt(pow((center1.x - center2.x), 2.0) + pow((center1.z - center2.z), 2.0));
    return dist_center <= s1->radius + s2->radius;
    
}

bool Window::plane_collision(BoundingSphere* s, BoundingPlane* p){
    float dist = glm::dot(s->center - p->origin, p->normal);
    return dist <= s->radius;
}

bool Window::all_collision(BoundingSphere* player_sphere){
    for (int i = 0; i < planes.size(); i++) {
            if (plane_collision(player_sphere, planes[i])){
                if (player_sphere->isMoving){
                    glm::vec3 normal = planes[i]->normal;
                    normal = glm::normalize(normal);
                    glm::vec3 ori_angle(cos(player_sphere->direction), 0.f, -sin(player_sphere->direction));
    //                    ori_angle = glm::normalize(ori_angle);
                    glm::vec3 ref_angle = ori_angle - 2 * glm::dot(ori_angle, normal) * normal;
                    float new_dir = acos(ref_angle.x);
                    if (planes[i]->name == "top"){
                        if (player_sphere->direction > glm::radians(270.f))
                            new_dir = player_sphere->direction - (player_sphere->direction - glm::radians(270.f)) * 2;
                        else
                            new_dir = player_sphere->direction + (player_sphere->direction - glm::radians(270.f)) * 2;
                    }
                    player_sphere->direction = new_dir;
                }
                return true;
            }
        }
    
    for (int i = 0; i < spheres.size(); i++){
        if (player_sphere->name != spheres[i]->name){
            if (sphere_collision(player_sphere, spheres[i])){
                if (player_sphere->isMoving){
                    glm::vec3 normal = player_sphere->center - spheres[i]->center;
                    normal = glm::normalize(normal);
                    glm::vec3 ori_angle(cos(player_sphere->direction), 0.f, -sin(player_sphere->direction));
//                    ori_angle = glm::normalize(ori_angle);
                    glm::vec3 ref_angle = ori_angle - 2 * glm::dot(ori_angle, normal) * normal;
                    float new_dir = acos(ref_angle.x);
                    player_sphere->direction = new_dir;
                }
                if (spheres[i]->isMoving){
                    glm::vec3 normal = spheres[i]->center - player_sphere->center;
                    normal = glm::normalize(normal);
                    glm::vec3 ori_angle(cos(spheres[i]->direction), 0.f, -sin(spheres[i]->direction));
                    glm::vec3 ref_angle = ori_angle - 2 * glm::dot(ori_angle, normal) * normal;
                    float new_dir = acos(ref_angle.x);
                    spheres[i]->direction = new_dir;
                }
                return true;
            }
        }
    }
    
    return false;
}

void Window::move_black(){
    float det_x = cos(astronaut_black->boundingSphere->direction) * 0.004;
    float det_z = - sin(astronaut_black->boundingSphere->direction) * 0.004;
    astronaut_black->boundingSphere->center.x += det_x;
    astronaut_black->boundingSphere->center.z += det_z;
    if (! all_collision(astronaut_black->boundingSphere)){
        astronaut_black->modelM *= glm::translate(glm::vec3(0, 0, 0.004));
    }
    else{
        astronaut_black->boundingSphere->center.x -= det_x;
        astronaut_black->boundingSphere->center.z -= det_z;
    }
}

void Window::move_brown(){
    float det_x = cos(astronaut_brown->boundingSphere->direction) * 0.004;
    float det_z = - sin(astronaut_brown->boundingSphere->direction) * 0.004;
    astronaut_brown->boundingSphere->center.x += det_x;
    astronaut_brown->boundingSphere->center.z += det_z;
    if (! all_collision(astronaut_brown->boundingSphere)){
        astronaut_brown->modelM *= glm::translate(glm::vec3(0, 0, 0.004));
    }
    else{
        astronaut_brown->boundingSphere->center.x -= det_x;
        astronaut_brown->boundingSphere->center.z -= det_z;
    }
}

void Window::move_blue(){
    float det_x = cos(astronaut_blue->boundingSphere->direction) * 0.004;
    float det_z = - sin(astronaut_blue->boundingSphere->direction) * 0.004;
    astronaut_blue->boundingSphere->center.x += det_x;
    astronaut_blue->boundingSphere->center.z += det_z;
    if (! all_collision(astronaut_blue->boundingSphere)){
        astronaut_blue->modelM *= glm::translate(glm::vec3(0, 0, 0.004));
    }
    else{
        astronaut_blue->boundingSphere->center.x -= det_x;
        astronaut_blue->boundingSphere->center.z -= det_z;
    }
}

void Window::move_cyan(){
    float det_x = cos(astronaut_cyan->boundingSphere->direction) * 0.004;
    float det_z = - sin(astronaut_cyan->boundingSphere->direction) * 0.004;
    astronaut_cyan->boundingSphere->center.x += det_x;
    astronaut_cyan->boundingSphere->center.z += det_z;
    if (! all_collision(astronaut_cyan->boundingSphere)){
        astronaut_cyan->modelM *= glm::translate(glm::vec3(0, 0, 0.004));
    }
    else{
        astronaut_cyan->boundingSphere->center.x -= det_x;
        astronaut_cyan->boundingSphere->center.z -= det_z;
    }
}

