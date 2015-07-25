#include <Windows.h>
#include <WinGDI.h>
#include "GeoModel3D.h"

GeoModel3D::GeoModel3D(std::string file_name)
{
	std::vector<tinyobj::shape_t> shapes;
	std::string err = tinyobj::LoadObj(shapes, materials, (file_name+".obj").c_str());
	std::cout<<err<<std::endl;

	for(size_t i = 0;i<shapes.size();i++ )
	{
		// each mesh is made up of a number of shapes	
		tinyobj::mesh_t current_mesh = shapes[i].mesh;

		// collect the vertex information of each shape
		vertices.insert(vertices.end(),current_mesh.positions.begin(),current_mesh.positions.end());
		indices.insert(indices.end(),current_mesh.indices.begin(),current_mesh.indices.end());

		if(current_mesh.material_ids[0]>=0) // no texture = -1 in material ids
		{
            tinyobj::material_t& material = materials[current_mesh.material_ids[0]];
			std::string color_map = material.diffuse_texname;
			if (!color_map.empty()) 
			{
				std::cout<<"Loading texture: "<<color_map<<std::endl;
				GLuint texture_id = loadTexture(color_map);
				textures.insert(std::map<unsigned int,unsigned int>::value_type(current_mesh.material_ids[0],texture_id));
			}
			else
			{
				std::cout<<"Could not find a diffuse texture!"<<std::endl;
			}
        }
	}

	if(err.empty())
	{
		std::cout << "# of shapes    : " << shapes.size() << std::endl;
		std::cout << "# of materials : " << materials.size() << std::endl;
	}
}

AABB* GeoModel3D::getAABB()
{
	return boundingBox;
}

void GeoModel3D::retrieveData(std::vector<float> &model_vertices,std::vector<int> &model_indices,std::vector<tinyobj::material_t> &mat,std::map<GLuint,GLuint> &tex)
{
	model_vertices = vertices;
	model_indices = indices;
	mat = materials;
	tex = textures;
}

GLuint GeoModel3D::loadTexture (std::string file_name)
{
	printf("loadTexture");
	if(!wglGetCurrentContext())
	{
		printf("No OpenGL context\n");
	}

	glEnable(GL_TEXTURE_2D);
	GLuint tex_id = SOIL_load_OGL_texture(
					file_name.c_str(),
					SOIL_LOAD_AUTO,
					SOIL_CREATE_NEW_ID,
					NULL
					);

	return tex_id;
}

void GeoModel3D::translate(glm::vec3 pos)
{
	model_matrix = glm::translate(model_matrix,pos);
}

glm::mat4 GeoModel3D::getModelMatrix()
{
	return model_matrix;
}