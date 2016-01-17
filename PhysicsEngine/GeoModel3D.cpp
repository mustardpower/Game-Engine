#include <Windows.h>
#include <WinGDI.h>
#include "GeoModel3D.h"
#include "GameEngine.h"

GLuint GeoModel3D::NUMBER_OF_MODELS = 0;
GLuint GLModel3DData::NUMBER_OF_MESHES = 0;
std::string GeoModel3D::modelDirectory = GameEngine::getApplicationDirectory() + "\\models\\";
std::string GeoModel3D::texturesDirectory = GameEngine::getApplicationDirectory() + "\\textures\\";

GLModel3DData::~GLModel3DData()
{
}

GeoModel3D::GeoModel3D()
{
	geo_file_name = "";
	model_id = ++NUMBER_OF_MODELS;
}

GeoModel3D::~GeoModel3D()
{
}

GeoModel3D::GeoModel3D(const GeoModel3D& model)
{
	geo_file_name = model.getFileName();
	model_id = ++NUMBER_OF_MODELS;
	meshes = model.retrieveMeshes();
}

void GeoModel3D::setModelDirectory(std::string directoryPath)
{
	modelDirectory = directoryPath;
}

void GeoModel3D::setTexturesDirectory(std::string directoryPath)
{
	texturesDirectory = directoryPath;
}

void GeoModel3D::loadFromFile(std::string file_name)
{
	geo_file_name = file_name;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string absolutePath = modelDirectory + file_name;
	
	std::string err = tinyobj::LoadObj(shapes, materials, absolutePath.c_str(), modelDirectory.c_str());

	GLModel3DData new_mesh;

	for (size_t i = 0; i<shapes.size(); i++)
	{
		GLuint texture;

		// each mesh is made up of a number of shapes	
		tinyobj::mesh_t current_mesh = shapes[i].mesh;

		if (current_mesh.material_ids[0] >= 0) // no texture = -1 in material ids
		{
			tinyobj::material_t& material = materials[current_mesh.material_ids[0]];
			std::string color_map = material.diffuse_texname;
			if (!color_map.empty())
			{
				std::cout << "Loading texture: " << color_map << std::endl;
				texture = loadTexture(color_map);
				new_mesh.addTexture(texture);
			}
			else
			{
				std::cout << "Could not find a diffuse texture!" << std::endl;
			}
		}

		new_mesh.addMeshData(current_mesh);
		meshes.push_back(new_mesh);
	}

	if (err.empty())
	{
		std::cout << "# of shapes    : " << shapes.size() << std::endl;
		std::cout << "# of materials : " << materials.size() << std::endl;
	}
}

GLuint GeoModel3D::getModelID()
{
	return model_id;
}

std::string GeoModel3D::getFileName() const
{
	return geo_file_name;
}
std::vector<GLModel3DData> GeoModel3D::retrieveMeshes() const
{
	return meshes;
}

GLuint GeoModel3D::loadTexture (std::string file_name)
{
	if(!wglGetCurrentContext())
	{
		printf("No OpenGL context\n");
	}

	std::string absolutePath = texturesDirectory + file_name;
	glEnable(GL_TEXTURE_2D);
	GLuint tex_id = SOIL_load_OGL_texture(
					absolutePath.c_str(),
					SOIL_LOAD_AUTO,
					SOIL_CREATE_NEW_ID,
					NULL
					);

    if( 0 == tex_id )
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result());
    }

	return tex_id;
}

void GeoModel3D::serialize(tinyxml2::XMLDocument &xmlDocument, tinyxml2::XMLNode* parent)
{
	tinyxml2::XMLElement* objElement = xmlDocument.NewElement("GEOModel");

	// --------------------- GEOModel3D file name  ----------------------------//
	tinyxml2::XMLElement* fileElement = xmlDocument.NewElement("file_name");
	tinyxml2::XMLText* fileNameText = xmlDocument.NewText(geo_file_name.c_str());
	fileElement->LinkEndChild(fileNameText);
	objElement->LinkEndChild(fileElement);

	parent->LinkEndChild(objElement);
}

GeoModel3D GeoModel3D::deserialize(tinyxml2::XMLNode* parent)
{
	GeoModel3D cube;
	const char* elementText = parent->FirstChildElement("file_name")->GetText();
	std::string file_name(elementText);
	cube.loadFromFile(file_name);
	return cube;
}