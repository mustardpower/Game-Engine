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

struct GLModel3DData		// this is model data to be uploaded to the graphics card - we do not need multiple versions for objects that share data
	{
		std::vector<GLfloat> vertices, normals, tex_coords;
		std::vector<GLint> indices;
		std::vector<tinyobj::material_t> materials;
		GLuint texture;
	};
class GeoModel3D
{
private:
	GLModel3DData data;
	int model_id;			//this is unique to an instance of the object
	static GLuint NUMBER_OF_MODELS;
public:
	GLuint getModelID();
	GeoModel3D(std::string file_name);
	GLModel3DData retrieveData();
	GLuint loadTexture(std::string file_name);
};