#pragma once
#include <qstring.h>
#include <QVector>
#include "tiny_obj_loader.h"
#include "tinyxml2\tinyxml2.h"

//-----------------------------------------------------------------------------
// Name:		GLModel3DData
// Variables:	meshID - a unique id for the mesh
//				NUMBER_OF_MESHES - stores the number of meshes that are active
//				mesh - stores the mesh position data, normals, texture coordinates, texture name
//				texture - the value allocated for a texture passed to the shaders
// Desc:		This class manages the data for a single mesh
//-----------------------------------------------------------------------------

class GLModel3DData		// this is model data to be uploaded to the graphics card - we do not need multiple versions for objects that share data
	{
		private:
		int meshID;
		static int NUMBER_OF_MESHES;
		tinyobj::mesh_t mesh;
		std::vector<tinyobj::material_t> materials;
		QString texture;

	public:
		int getMeshID() { return meshID; }
		tinyobj::mesh_t getMeshData() { return mesh;  }
		GLModel3DData() { meshID = ++NUMBER_OF_MESHES; }
		~GLModel3DData();
		void addMeshData(tinyobj::mesh_t new_mesh) { mesh = new_mesh; }
		void addTexture(QString aTexture) { texture = aTexture; }
		QString getTexture() { return texture; }
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
	QVector<GLModel3DData> meshes;
	int model_id;			//this is unique to an instance of the object
	static int NUMBER_OF_MODELS;
	QString geo_file_name;
public:

	GeoModel3D();
	~GeoModel3D();
	GeoModel3D(const GeoModel3D& model);

	void print();

	int getModelID();
	QString getFileName() const;
	void loadFromFile(QString file_name);
	QVector<GLModel3DData> retrieveMeshes() const;

	void serialize(tinyxml2::XMLDocument &xmlDocument, tinyxml2::XMLNode* parent);
	static tinyxml2::XMLError deserialize(tinyxml2::XMLNode* parent, GeoModel3D& model);
};