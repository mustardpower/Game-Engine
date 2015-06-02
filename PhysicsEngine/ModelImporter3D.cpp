#include "ModelImporter3D.h"

//-----------------------------------------------------------------------------
// Name:	extractModelData
// Parms:	filePath - the path to the .obj file storing the model data
// Returns:	Model3D - the model to be rendered
// Desc:	Reads the model file and stores each vertex, normal, texture coordinate, colour etc.
//-----------------------------------------------------------------------------
Model3D ModelImporter3D::extractModelData(string fp)
{
	filePath = fp;
 
    // Open OBJ file
    ifstream inOBJ;
	stringstream ss;
    inOBJ.open(filePath);

	std::vector<glm::vec2> temp_texels;
	std::vector<glm::vec3> temp_vertices, temp_normals;
	std::vector<int> vertexIndices, normalIndices, texelIndices;

    if(!inOBJ.good())
    {
        cout << "ERROR OPENING OBJ FILE" << endl;
        exit(1);
    }

    // Read OBJ file
    while(!inOBJ.eof())
    {
        // 5
        string line;
        getline(inOBJ, line);	
		std::replace(line.begin(), line.end(), '/', ' ');
		ss.str(line);

        string type = line.substr(0,2);
 
        // 6
        if(type.compare("v ") == 0)
		{
			// read contents to vector and add vector to vertices
			glm::vec3 vertex;
			ss>>type>>vertex.x>>vertex.y>>vertex.z;
			temp_vertices.push_back(vertex);
		}
        else if(type.compare("vt") == 0)
		{
			// read contents to vector and add vector to texels
			glm::vec2 texel;
			ss>>type>>texel.x>>texel.y;
			temp_texels.push_back(texel);
		}
        else if(type.compare("vn") == 0)
		{
			// read contents to vector and add vector to normals
			glm::vec3 normal;
			ss>>type>>normal.x>>normal.y>>normal.z;
			temp_normals.push_back(normal);
		}
		else if(type.compare("f ") == 0)
		{
			// read contents to vector and add vector to vertex, texel and normal indices
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];

			ss>>type;

			// read values into the array positions
			ss>>vertexIndex[0]>>uvIndex[0]>>normalIndex[0];
			ss>>vertexIndex[1]>>uvIndex[1]>>normalIndex[1];
			ss>>vertexIndex[2]>>uvIndex[2]>>normalIndex[2];


			//store the array values in the model
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			texelIndices.push_back(uvIndex[0]);
			texelIndices.push_back(uvIndex[1]);
			texelIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
		ss.clear();
    }

	for( unsigned int i=0; i < vertexIndices.size(); i++ )
	{
		unsigned int vertexIndex = vertexIndices[i];
		glm::vec3 vertex = temp_vertices[ vertexIndex-1 ];
		model.vertices.push_back(vertex);
	}

	for( unsigned int i=0; i < texelIndices.size(); i++ )
	{
		unsigned int texelIndex = texelIndices[i];
		glm::vec2 texel = temp_texels[ texelIndex-1 ];
		model.texels.push_back(texel);
	}

	for( unsigned int i=0; i < normalIndices.size(); i++ )
	{
		unsigned int normalIndex = normalIndices[i];
		glm::vec3 vertex = temp_normals[ normalIndex-1 ];
		model.normals.push_back(vertex);
	}

    inOBJ.close();
    return model;
	
}