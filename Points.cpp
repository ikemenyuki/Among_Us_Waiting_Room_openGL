//#include "Points.h"
//#include <iostream>
//#include <fstream>
//#include <string>
//#include <sstream>
//#include <limits>
//#include <cmath>
//
//PointCloud::PointCloud(std::string objFilename, GLfloat pointSize, PointCloud* sphere)
//	: pointSize(pointSize)
//{
//	/*
//	 * TODO: Section 2: Currently, all the points are hard coded below.
//	 * Modify this to read points from an obj file.
//	 */
//
//    // initialie max & min coornidates
//    if (objFilename.find("bunny.obj") != std::string::npos)
//        objType = 0;
//    else if (objFilename.find("bear.obj") != std::string::npos)
//        objType = 1;
//    else if (objFilename.find("SandalF20.obj") != std::string::npos)
//        objType = 2;
//    else if (objFilename.find("sphere.obj") != std::string::npos)
//        islight = 1;
//
//    int x_max = std::numeric_limits<int>::min();
//    int y_max = std::numeric_limits<int>::min();
//    int z_max = std::numeric_limits<int>::min();
//    // initialize min coordinates
//    int x_min = std::numeric_limits<int>::max();
//    int y_min = std::numeric_limits<int>::max();
//    int z_min = std::numeric_limits<int>::max();
//
//    std::ifstream objFile(objFilename); // The obj file we are reading.
//    //std::vector<glm::vec3> *points = new vector<glm::vec3>;
//
//    if (objFile.is_open())
//    {
//        std::string line; // A line in the file.
//
//        // Read lines from the file.
//        while (std::getline(objFile, line))
//        {
//            // Turn the line into a string stream for processing.
//            std::stringstream ss;
//            ss << line;
//
//            // Read the first word of the line.
//            std::string label;
//            ss >> label;
//
//            // If the line is about vertex (starting with a "v").
//            if (label == "v")
//            {
//                // Read the later three float numbers and use them as the
//                // coordinates.
//                glm::vec3 point;
//                ss >> point.x >> point.y >> point.z;
//                if (point.x > x_max) x_max = point.x;
//                if (point.y > y_max) y_max = point.y;
//                if (point.z > z_max) z_max = point.z;
//
//                if (point.x < x_min) x_min = point.x;
//                if (point.y < y_min) y_min = point.y;
//                if (point.z < z_min) z_min = point.z;
//                // Process the point. For example, you can save it to a.
//                points.push_back(point);
//            }
//            if (label == "vn") {
//                glm::vec3 normal;
//                ss >> normal.x >> normal.y >> normal.z;
//                normals.push_back(normal);
//            }
//            if (label == "f") {
//                glm::ivec3 index;
//                string faces[3];
//                ss >> faces[0] >> faces[1] >> faces[2];
//                for (int i = 0; i < 3; i++){
//                    faces[i] = faces[i].substr(0, faces[i].find("//"));
//                }
//                index.x = stoi(faces[0]) - 1;
//                index.y = stoi(faces[1]) - 1;
//                index.z = stoi(faces[2]) - 1;
//                indices.push_back(index);
//
//            }
//        }
//    }
//    else
//    {
//        std::cerr << "Can't open the file " << objFilename << std::endl;
//    }
//
//    objFile.close();
//
//    if (!islight && sphere){
//        // cout << sphere->points.size() << endl;
//        indices_sph = sphere->indices;
//        // model_s = sphere->getModel();
//        points_s = sphere->points;
//        int ctrX = x_min + (x_max - x_min)/2;
//        int ctrY = y_min + (y_max - y_min)/2;
//        int ctrZ = z_min + (z_max - z_min)/2;
//
//        for (int i = 0; i < points.size(); i++){
//            points[i].x -= ctrX;
//            points[i].y -= ctrY;
//            points[i].z -= ctrZ;
//        }
//        float max_dis = std::numeric_limits<float>::min();
//        for (int i = 0; i < points.size(); i++){
//            float dis = sqrt(pow(points[i].x - ctrX, 2) + pow(points[i].y - ctrY, 2) + pow(points[i].z - ctrZ, 2));
//            if (dis > max_dis) max_dis = dis;
//        }
//
//        /*
//         * TODO: Section 4, you will need to normalize the object to fit in the
//         * screen.
//         */
//
//        // Set the model matrix to an identity matrix.
//        model = glm::mat4(1);
//        model_s = glm::mat4(1);
//        model_s = glm::translate(lightPos) * model_s;
//        if (max_dis < 19){
//
//            model = model * glm::scale(glm::mat4(1.0f), glm::vec3(10/max_dis, 10/max_dis, 10/max_dis));
//        }
//        // Set the color.
//            // Generate a vertex array (VAO) and vertex buffer object (VBO).
//            glGenVertexArrays(1, &VAO);
//            glGenBuffers(1, &VBO);
//            glBindVertexArray(VAO);
//            glBindBuffer(GL_ARRAY_BUFFER, VBO);
//            glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * points.size(), points.data(), GL_STATIC_DRAW);
//            glEnableVertexAttribArray(0);
//            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *)0);
//            glGenBuffers(1, &VBO2);
//            glBindBuffer(GL_ARRAY_BUFFER, VBO2);
//            glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * normals.size(), normals.data(), GL_STATIC_DRAW);
//            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
//            glEnableVertexAttribArray(1);
//            glGenBuffers(1, &EBO);
//            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(glm::ivec3) * indices.size(), indices.data(), GL_STATIC_DRAW);
//
//            // Unbind the VBO/VAO
//            //glBindBuffer(GL_ARRAY_BUFFER, 0);
//            //glBindVertexArray(0);
//
//            //repeat for sphere
//        glGenVertexArrays(1, &VAO_s);
//        glGenBuffers(1, &VBO_s);
//        // Bind to the new sphere VAO.
//        glBindVertexArray(VAO_s);
//        // Bind VBO to the bound VAO, and store the vertex data
//        glBindBuffer(GL_ARRAY_BUFFER, VBO_s);
//        glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * sphere->points.size(), sphere->points.data(), GL_STATIC_DRAW);
//        // Enable Vertex Attribute 0 to pass the vertex data through to the shader
//        glEnableVertexAttribArray(0);
//        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *)0);
//        //buffer normal data
//        glGenBuffers(1, &VBO_s2);
//        glBindBuffer(GL_ARRAY_BUFFER, VBO_s2);
//        glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * sphere->normals.size(), sphere->normals.data(), GL_STATIC_DRAW);
//        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
//        glEnableVertexAttribArray(1);
//        // Generate EBO, bind the EBO to the bound VAO, and send the index data
//        glGenBuffers(1, &EBO_s);
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_s);
//        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(glm::ivec3) * sphere->indices.size(), sphere->indices.data(), GL_STATIC_DRAW);
//
//        // Unbind the VBO/VAO
//        glBindBuffer(GL_ARRAY_BUFFER, 0);
//        glBindVertexArray(0);
//    }
//
//}
//
//PointCloud::~PointCloud()
//{
//	// Delete the VBO and the VAO.
//	glDeleteBuffers(1, &VBO);
//	glDeleteVertexArrays(1, &VAO);
//}
//
//void PointCloud::draw(const glm::mat4& view, const glm::mat4& projection, GLuint shader)
//{
//	// Actiavte the shader program
//	glUseProgram(shader);
//
//	// Get the shader variable locations and send the uniform data to the shader
//	glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, false, glm::value_ptr(view));
//	glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, false, glm::value_ptr(projection));
//	glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(model));
//	glUniform3fv(glGetUniformLocation(shader, "color"), 1, glm::value_ptr(color));
//    glUniform3fv(glGetUniformLocation(shader, "lightPos"), 1, glm::value_ptr(lightPos));
//    glUniform3fv(glGetUniformLocation(shader, "lightColor"), 1, glm::value_ptr(lightColor));
//    glUniform1i(glGetUniformLocation(shader, "objType"), objType);
//    glUniform3fv(glGetUniformLocation(shader, "viewpos"), 1, glm::value_ptr(eyePos));
//    glUniform1i(glGetUniformLocation(shader, "isphong"), isPhong);
//    glUniform1i(glGetUniformLocation(shader, "islight"), 0);
//	// Bind the VAO
//	glBindVertexArray(VAO);
//	// Set point size
//	glPointSize(pointSize);
//
//	// Draw the points
//	// glDrawArrays(GL_POINTS, 0, points.size());
//    // Draw the points using triangles, indexed with the EBO
//    glDrawElements(GL_TRIANGLES, sizeof(glm::ivec3) * indices.size(), GL_UNSIGNED_INT, 0);
//    glBindVertexArray(VAO_s);
////    model_s = glm::mat4(1);
////    model_s = glm::translate(lightPos) * model_s;
//    glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(model_s));
//    // cout << glm::length(points_s[0]) << "fengle " << endl;
//    glUniform1i(glGetUniformLocation(shader, "islight"), 1.0f);
//    glUniform1i(glGetUniformLocation(shader, "objType"), 3.0f);
//    glDrawElements(GL_TRIANGLES, sizeof(glm::ivec3) * indices_sph.size(), GL_UNSIGNED_INT, 0);
//	// Unbind the VAO and shader program
//	glBindVertexArray(0);
//	glUseProgram(0);
//}
//
//void PointCloud::update()
//{
//	// Spin the cube by 1 degree
//	spin(0.1f);
//}
//
//void PointCloud::updatePointSize(GLfloat size)
//{
//	/*
//	 * TODO: Section 3: Implement this function to adjust the point size.
//	 */
//    pointSize = size;
//    glPointSize(pointSize);
//}
//
//void PointCloud::spin(float deg)
//{
//	// Update the model matrix by multiplying a rotation matrix
//	// model = model * glm::rotate(glm::radians(deg), glm::vec3(0.0f, 1.0f, 0.0f));
//}
//#include "Points.h"
//
//
//PointCloud::PointCloud(std::string objFilename, GLfloat pointSize)
//    : pointSize(pointSize)
//{
//    /*
//     * TODO: Section 2: Currently, all the points are hard coded below.
//     * Modify this to read points from an obj file.
//     */
//
//    points = {
//        glm::vec3(-2.5, 2.5, 2.5),
//        glm::vec3(-2.5, -2.5, 2.5),
//        glm::vec3(2.5, -2.5, 2.5),
//        glm::vec3(2.5, 2.5, 2.5),
//        glm::vec3(-2.5, 2.5, -2.5),
//        glm::vec3(-2.5, -2.5, -2.5),
//        glm::vec3(2.5, -2.5, -2.5),
//        glm::vec3(2.5, 2.5, -2.5)
//    };
//
//    /*
//     * TODO: Section 4, you will need to normalize the object to fit in the
//     * screen.
//     */
//
//    // Set the model matrix to an identity matrix.
//    model = glm::mat4(1);
//
//    // Set the color.
//    color = glm::vec3(1, 0, 0);
//
//    // Generate a Vertex Array (VAO) and Vertex Buffer Object (VBO)
//    glGenVertexArrays(1, &VAO);
//    glGenBuffers(1, &VBO);
//
//    // Bind VAO
//    glBindVertexArray(VAO);
//
//    // Bind VBO to the bound VAO, and store the point data
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * points.size(), points.data(), GL_STATIC_DRAW);
//    // Enable Vertex Attribute 0 to pass point data through to the shader
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
//
//    // Unbind the VBO/VAO
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    glBindVertexArray(0);
//}
//
//PointCloud::~PointCloud()
//{
//    // Delete the VBO and the VAO.
//    glDeleteBuffers(1, &VBO);
//    glDeleteVertexArrays(1, &VAO);
//}
//
//void PointCloud::draw(const glm::mat4& view, const glm::mat4& projection, GLuint shader)
//{
//    // Actiavte the shader program
//    glUseProgram(shader);
//
//    // Get the shader variable locations and send the uniform data to the shader
//    glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, false, glm::value_ptr(view));
//    glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, false, glm::value_ptr(projection));
//    glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(model));
//    glUniform3fv(glGetUniformLocation(shader, "color"), 1, glm::value_ptr(color));
//
//    // Bind the VAO
//    glBindVertexArray(VAO);
//
//    // Set point size
//    glPointSize(pointSize);
//
//    // Draw the points
//    glDrawArrays(GL_POINTS, 0, points.size());
//
//    // Unbind the VAO and shader program
//    glBindVertexArray(0);
//    glUseProgram(0);
//}
//
//void PointCloud::update()
//{
//    // Spin the cube by 1 degree
//    spin(0.1f);
//}
//
//void PointCloud::updatePointSize(GLfloat size)
//{
//    /*
//     * TODO: Section 3: Implement this function to adjust the point size.
//     */
//}
//
//void PointCloud::spin(float deg)
//{
//    // Update the model matrix by multiplying a rotation matrix
//    model = model * glm::rotate(glm::radians(deg), glm::vec3(0.0f, 1.0f, 0.0f));
//}
