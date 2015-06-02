#pragma once
#include <vector>
#include <map>
#include <GL/glew.h>
#include <GL/glut.h>

#include "tiny_obj_loader.h"
#include "glsl.h"
#include "AABB.h"
#include "Camera.h"
#include "lodepng.h"
#include <map>
#include "SOIL\SOIL.h"

class GeoModel3D
{
private:
	AABB* boundingBox;
	std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
	std::map<unsigned int,unsigned int> textures;
	glm::vec3 rotation_vec;
	float rotation_angle;
	glm::vec3 position;
public:
	GeoModel3D(std::string file_name);
	AABB* getAABB();
	void render(cwc::glShader *shader, Camera camera);
	GLuint loadTexture(std::string file_name);
	void setPosition(glm::vec3 pos);
	void rotate(float angle, glm::vec3 rotation_vec);
};