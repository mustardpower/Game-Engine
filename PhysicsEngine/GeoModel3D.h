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
#include "tinyxml2\tinyxml2.h"

//-----------------------------------------------------------------------------
// Name:		GLModel3DData
// Variables:	meshID - a unique id for the mesh
//				NUMBER_OF_MESHES - stores the number of meshes that are active
//				mesh - stores the mesh position data, normals, texture coordinates, texture name
//				texture - the value allocated for a texture passed to the shaders
// Desc:		This class manages the data for a single mesh
//-----------------------------------------------------------------------------

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
		~GLModel3DData();
		void addMeshData(tinyobj::mesh_t new_mesh) { mesh = new_mesh; }
		void addTexture(GLuint tex_id) { texture = tex_id; }
	};

//-----------------------------------------------------------------------------
// Name:		GeoModel3D
// Variables:	modelDirectory - the location of the model files the data is loaded from
//				textureDirectory - the location of the texture files used for the models
//				meshes - stores all of the meshes that make up the 3d model
//				NUMBER_OF_MODELS - the number of models active
//				geo_file_name - the file that the data is loaded from
// Desc:		This class manages the data for a single 3d model with functionality to load and save
//-----------------------------------------------------------------------------

class GeoModel3D
{
private:
	static std::string modelDirectory;
	static std::string texturesDirectory;
	std::vector<GLModel3DData> meshes;
	int model_id;			//this is unique to an instance of the object
	static GLuint NUMBER_OF_MODELS;
	std::string geo_file_name;
public:

	static void setModelDirectory(std::string directoryPath);
	static void setTexturesDirectory(std::string directoryPath);

	GeoModel3D();
	~GeoModel3D();
	GeoModel3D(const GeoModel3D& model);

	void print();

	GLuint getModelID();
	std::string getFileName() const;
	void loadFromFile(std::string file_name);
	std::vector<GLModel3DData> retrieveMeshes() const;
	GLuint loadTexture(std::string file_name);

	void serialize(tinyxml2::XMLDocument &xmlDocument, tinyxml2::XMLNode* parent);
	static tinyxml2::XMLError deserialize(tinyxml2::XMLNode* parent, GeoModel3D& model);
};