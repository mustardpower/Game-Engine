#include "GeoModel3D.h"

GeoModel3D::GeoModel3D(std::string file_name)
{
	std::string err = tinyobj::LoadObj(shapes, materials, (file_name+".obj").c_str());
	std::cout<<err<<std::endl;

	for(size_t i = 0;i<shapes.size();i++ )
	{
		tinyobj::mesh_t current_mesh = shapes[i].mesh;

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

void GeoModel3D::retrieveData(std::vector<tinyobj::shape_t> &model_shapes,std::vector<tinyobj::material_t> &mat,std::map<unsigned int,unsigned int> &tex)
{
	model_shapes = shapes;
	mat = materials;
	tex = textures;
}

GLuint GeoModel3D::loadTexture (std::string file_name)
{
  
  GLuint tex_id = SOIL_load_OGL_texture(
					file_name.c_str(),
					SOIL_LOAD_AUTO,
					SOIL_CREATE_NEW_ID,
					SOIL_FLAG_POWER_OF_TWO
					| SOIL_FLAG_MIPMAPS
					| SOIL_FLAG_DDS_LOAD_DIRECT
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