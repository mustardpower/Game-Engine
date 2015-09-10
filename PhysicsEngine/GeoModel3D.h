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
		GLuint meshID;
		static GLuint NUMBER_OF_MESHES;
		tinyobj::mesh_t mesh;
		std::vector<tinyobj::material_t> materials;
		GLuint texture;
		GLuint getMeshID() { return meshID; }
		tinyobj::mesh_t getMeshData() { return mesh;  }
		GLModel3DData() { meshID = ++NUMBER_OF_MESHES; }
		void addMeshData(tinyobj::mesh_t new_mesh) { mesh = new_mesh; }
		void addTexture(GLuint tex_id) { texture = tex_id; }
	};
class GeoModel3D
{
private:
	std::vector<GLModel3DData> meshes;
	int model_id;			//this is unique to an instance of the object
	static GLuint NUMBER_OF_MODELS;
public:
	GLuint getModelID();
	GeoModel3D(std::string file_name);
	std::vector<GLModel3DData> retrieveMeshes();
	GLuint loadTexture(std::string file_name);
};