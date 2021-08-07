//#ifndef _POINT_CLOUD_H_
//#define _POINT_CLOUD_H_
//
//#include "Object.h"
//
//#include <vector>
//#include <string>
//
//using namespace std;
//
//class PointCloud : public Object
//{
//private:
//	GLuint VAO, VBO, EBO;
//    GLuint VBO2;
//    GLuint VAO_s, VBO_s, VBO_s2, EBO_s;
//	GLfloat pointSize;
//
//public:
//	PointCloud(std::string objFilename, GLfloat pointSize, PointCloud* sphere = nullptr);
//	~PointCloud();
//
//    std::vector<glm::vec3> points;
//    std::vector<glm::vec3> normals;
//    std::vector<glm::ivec3> indices;
//    std::vector<glm::ivec3> indices_sph;
//    // glm::mat4 model_s;
//    std::vector<glm::vec3> points_s;
//
//
//	void draw(const glm::mat4& view, const glm::mat4& projection, GLuint shader);
//	void update();
//
//	void updatePointSize(GLfloat size);
//	void spin(float deg);
//};
//
//#endif
//#ifndef _POINTS_H_
//#define _POINTS_H_
//
//#ifdef __APPLE__
//#include <OpenGL/gl3.h>
//#else
//#include <GL/glew.h>
//#endif
//
//#include "shader.h"
//#include "Object.h"
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtx/transform.hpp>
//
//#include <vector>
//#include <string>
//
//using namespace std;
//
//class PointCloud : public Object
//{
//private:
//    std::vector<glm::vec3> points;
//
//    GLuint VAO, VBO;
//    GLfloat pointSize;
//
//public:
//    glm::mat4 model = glm::mat4(1.f);
//    PointCloud(std::string objFilename, GLfloat pointSize);
//    ~PointCloud();
//
//    void draw(const glm::mat4& view, const glm::mat4& projection, GLuint shader);
//    void update();
//
//    void updatePointSize(GLfloat size);
//    void spin(float deg);
//};
//
//#endif
