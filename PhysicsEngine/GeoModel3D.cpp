#include <Windows.h>
#include <WinGDI.h>
#include "GeoModel3D.h"

GLuint GeoModel3D::NUMBER_OF_MODELS = 0;
GeoModel3D::GeoModel3D(std::string file_name)
{
	model_id = ++NUMBER_OF_MODELS;
	std::vector<tinyobj::shape_t> shapes;

	std::string err = tinyobj::LoadObj(shapes, data.materials, (file_name+".obj").c_str());
	std::cout<<err<<std::endl;

	for(size_t i = 0;i<shapes.size();i++ )
	{
		// each mesh is made up of a number of shapes	
		tinyobj::mesh_t current_mesh = shapes[i].mesh;

		// collect the vertex information of each shape
		data.vertices.insert(data.vertices.end(),current_mesh.positions.begin(),current_mesh.positions.end());
		data.indices.insert(data.indices.end(),current_mesh.indices.begin(),current_mesh.indices.end());
		data.normals.insert(data.normals.end(),current_mesh.normals.begin(),current_mesh.normals.end());
		data.tex_coords.insert(data.tex_coords.end(),current_mesh.texcoords.begin(),current_mesh.texcoords.end());

		if(current_mesh.material_ids[0]>=0) // no texture = -1 in material ids
		{
            tinyobj::material_t& material = data.materials[current_mesh.material_ids[0]];
			std::string color_map = material.diffuse_texname;
			if (!color_map.empty()) 
			{
				std::cout<<"Loading texture: "<<color_map<<std::endl;
				data.texture = loadTexture(color_map);
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
		std::cout << "# of materials : " << data.materials.size() << std::endl;
	}
}

GLuint GeoModel3D::getModelID()
{
	return model_id;
}
GLModel3DData GeoModel3D::retrieveData()
{
	return data;
}

GLuint GeoModel3D::loadTexture (std::string file_name)
{
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

    if( 0 == tex_id )
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result());
    }

	return tex_id;
}