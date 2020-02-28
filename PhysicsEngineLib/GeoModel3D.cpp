#include "GeoModel3D.h"
#include "QtPhysicsEngine.h"
#include <QOpenGLFunctions>
#include <iostream>
#include "SOIL\SOIL.h"
#include <filesystem>

int GeoModel3D::NUMBER_OF_MODELS = 0;
int GLModel3DData::NUMBER_OF_MESHES = 0;
QString GeoModel3D::modelDirectory = QtPhysicsEngine::getApplicationDirectory() + "\\models\\";
QString GeoModel3D::texturesDirectory = QtPhysicsEngine::getApplicationDirectory() + "\\textures\\";

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

void GeoModel3D::setModelDirectory(QString directoryPath)
{
	modelDirectory = directoryPath;
}

void GeoModel3D::setTexturesDirectory(QString directoryPath)
{
	texturesDirectory = directoryPath;
}

void GeoModel3D::print()
{
	std::cout << "Model ID: " << model_id << std::endl;
}

void GeoModel3D::loadFromFile(QString file_name)
{
	geo_file_name = file_name;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string fileName = file_name.toUtf8().constData();
	std::string modelDir = modelDirectory.toUtf8().constData();
	std::string absPath = modelDir + fileName;
	std::string err = tinyobj::LoadObj(shapes, materials, absPath.c_str(), modelDir.c_str());
	GLModel3DData new_mesh;

	for (size_t i = 0; i<shapes.size(); i++)
	{
		int texture;

		// each mesh is made up of a number of shapes	
		tinyobj::mesh_t current_mesh = shapes[i].mesh;

		if (current_mesh.material_ids[0] >= 0) // no texture = -1 in material ids
		{
			tinyobj::material_t& material = materials[current_mesh.material_ids[0]];
			QString color_map = texturesDirectory + QString::fromStdString(material.diffuse_texname);
			if (!color_map.isEmpty() && filesystem::exists(color_map.toStdString()))
			{
				new_mesh.addTexture(color_map);
			}
			else
			{
				std::cout << "Could not find a diffuse texture!" << std::endl;
			}
		}

		new_mesh.addMeshData(current_mesh);
		meshes.push_back(new_mesh);
	}

	std::cout << "# of shapes    : " << shapes.size() << std::endl;
	std::cout << "# of materials : " << materials.size() << std::endl;
}

int GeoModel3D::getModelID()
{
	return model_id;
}

QString GeoModel3D::getFileName() const
{
	return geo_file_name;
}
QVector<GLModel3DData> GeoModel3D::retrieveMeshes() const
{
	return meshes;
}

void GeoModel3D::serialize(tinyxml2::XMLDocument &xmlDocument, tinyxml2::XMLNode* parent)
{
	tinyxml2::XMLElement* objElement = xmlDocument.NewElement("GEOModel");

	// --------------------- GEOModel3D file name  ----------------------------//
	tinyxml2::XMLElement* fileElement = xmlDocument.NewElement("file_name");
	std::string geoFile = geo_file_name.toUtf8().constData();
	tinyxml2::XMLText* fileNameText = xmlDocument.NewText(geoFile.c_str());
	fileElement->LinkEndChild(fileNameText);
	objElement->LinkEndChild(fileElement);

	parent->LinkEndChild(objElement);
}

tinyxml2::XMLError GeoModel3D::deserialize(tinyxml2::XMLNode* parent, GeoModel3D &model)
{
	const char* elementText = parent->FirstChildElement("file_name")->GetText();
	std::string file_name(elementText);
	std::string modelDir = modelDirectory.toUtf8().constData();
	if (!std::filesystem::exists(modelDir + file_name))
	{
		return tinyxml2::XML_ERROR_FILE_COULD_NOT_BE_OPENED;
	}
	
	QString fileName(file_name.c_str());
	model.loadFromFile(fileName);

	return tinyxml2::XML_SUCCESS;
}