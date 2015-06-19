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

void GeoModel3D::render(cwc::glShader *shader)
{
	GLint vertex_index = 0;	
	GLint normal_index = 1;	
	GLint sampler_index;	
	GLint texture_coords_index = 2;

	// each mesh is made up of a number of shapes
	for(size_t i = 0;i<shapes.size();i++ )
	{
		tinyobj::mesh_t current_mesh = shapes[i].mesh;

		shader->BindAttribLocation(normal_index,"normal");
		glBufferData(GL_ARRAY_BUFFER,sizeof(float)*current_mesh.normals.size(), &current_mesh.normals[0],GL_STATIC_DRAW);
		glVertexAttribPointer(normal_index, 3, GL_FLOAT, GL_FALSE, 0, 0); 
		glEnableVertexAttribArray(normal_index);

		shader->BindAttribLocation(vertex_index,"position");
		glBufferData(GL_ARRAY_BUFFER,sizeof(float)*current_mesh.positions.size(), &current_mesh.positions[0], GL_STATIC_DRAW);
		glVertexAttribPointer(vertex_index, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(vertex_index);	

		if(!current_mesh.texcoords.empty())
		{
			shader->BindAttribLocation(texture_coords_index,"texCoord");	
			glBufferData(GL_ARRAY_BUFFER,sizeof(float)*current_mesh.texcoords.size(), &current_mesh.texcoords[0], GL_STATIC_DRAW);
			glVertexAttribPointer(texture_coords_index, 2, GL_FLOAT, GL_FALSE, 0, 0); 
			glEnableVertexAttribArray(texture_coords_index);
		}

		sampler_index = shader->GetUniformLocation("sampler");

		if(current_mesh.material_ids[0]>=0) 
		{
            tinyobj::material_t& material = materials[current_mesh.material_ids[0]];
			unsigned int texture_id = textures.at(current_mesh.material_ids[0]);
			glActiveTexture(GL_TEXTURE0 + texture_id); 
			glBindTexture(GL_TEXTURE_2D, texture_id);
			glUniform1i(sampler_index, texture_id);
        }

		glDrawElements(GL_TRIANGLES, shapes[i].mesh.indices.size(), GL_UNSIGNED_INT, &current_mesh.indices[0] );
		
		glDisableVertexAttribArray(vertex_index);
		glDisableVertexAttribArray(normal_index);	
		glDisableVertexAttribArray(texture_coords_index);
	}
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

void GeoModel3D::setPosition(glm::vec3 pos)
{
	position = pos;
}