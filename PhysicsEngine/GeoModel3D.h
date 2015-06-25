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
	glm::mat4 model_matrix;
public:
	GeoModel3D(std::string file_name);
	AABB* getAABB();
	void retrieveData(std::vector<tinyobj::shape_t> &model_shapes,std::vector<tinyobj::material_t> &mat,std::map<unsigned int,unsigned int> &tex);
	GLuint loadTexture(std::string file_name);
	void translate(glm::vec3 pos);
	glm::mat4 getModelMatrix();
};