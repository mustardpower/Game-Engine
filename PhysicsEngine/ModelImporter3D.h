#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

#include "glm\glm.hpp"

using namespace std;

//-----------------------------------------------------------------------------
// Name:		Model
// Variables:	vertices - the number of vertices for the object i.e. a cube has 8 vertices
//				texels - number of points defining edges of textures
//				normals - number of normal vectors - i.e. cube has 6 normal vectors on each face of the cube
// Desc:		Holds data for number of variables to be read by the model importer
//-----------------------------------------------------------------------------

typedef struct Model3D
{
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texels;
}
Model3D;

//-----------------------------------------------------------------------------
// Name:		ModelImporter3D
// Variables:	filePath - the file path to the model that the object is importing
//				model - the model that will be formed from the imported data file
// Desc:		Handles all importing of 3D models from various file formats (currently only Blender .obj files)
//-----------------------------------------------------------------------------
class ModelImporter3D
{
private:
	Model3D model;
	string filePath;
public:
	Model3D extractModelData(string filePath);
};