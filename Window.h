#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "main.h"
#include "shader.h"
#include "Node.h"
#include "Cube.h"
#include "Skybox.hpp"
#include "Sphere.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "Geometry.hpp"
#include "Transform.hpp"
#include "BoundSphere.hpp"
#include "BoundingPlane.hpp"
//#include "Particle.hpp"
#include "Object.h"
#include "Points.h"
#include "Particlez.hpp"

class Window
{
public:

	// Window Properties
	static int width;
	static int height;
	static const char* windowTitle;
    
    static bool mode4;
    static bool mode5;
    static bool mode6;

	// Objects to Render
    static Skybox *skybox;
    static Sphere *sphere;

	// Camera Matrices
	static glm::mat4 projection;
	static glm::mat4 view;
	static glm::vec3 eyePos, lookAtPoint, upVector;
    static glm::mat4 global_model_s;
	// Shader Program ID
	static GLuint shaderProgram;
    static GLuint particleShader;
    static GLuint lobbyShader;
    static GLuint skyboxShader;
    static GLuint sphereShader;
    static double xprev, yprev, xcur, ycur;
    static bool enabled;

	// Constructors and Destructors
	static bool initializeProgram();
	static bool initializeObjects();
	static void cleanUp();

	// Window functions
	static GLFWwindow* createWindow(int width, int height);
	static void resizeCallback(GLFWwindow* window, int width, int height);

	// Draw and Update functions
	static void idleCallback();
	static void displayCallback(GLFWwindow*);

    static glm::vec3 mapping(double xpos, double ypos);
	// Callbacks
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    // mouse callbacks
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    // cursor_position_callbacks
    static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
    // scroll callbacks
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    static bool sphere_collision(BoundingSphere* s1, BoundingSphere* s2);
    static bool plane_collision(BoundingSphere* s, BoundingPlane* p);
    static bool all_collision(BoundingSphere* player_sphere);
    static void move_black();
    static void move_blue();
    static void move_brown();
    static void move_cyan();
//    static void minus_delta(BoundingSphere* b, float del_x, float del_z);
};

#endif
