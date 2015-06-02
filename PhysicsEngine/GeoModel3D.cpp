#include "GeoModel3D.h"

GeoModel3D::GeoModel3D(std::string file_name)
{
	rotation_angle = 0.0f;
	rotation_vec.x = 1.0f;

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

void GeoModel3D::render(cwc::glShader *shader, Camera camera)
{
	GLint vertex_index = 0;	//store location of the "position" attribute in shaders
	GLint normal_index = 1;	//store location of the "normal" attribute in shaders
	GLint sampler_index;	
	GLint texture_coords_index = 2;
	GLint model_index;
	GLint view_index;
	GLint projection_index;

	glm::mat4 modelMatrix = camera.getModelMatrix();
	glm::mat4 viewMatrix = camera.getViewMatrix();
	glm::mat4 projectionMatrix = camera.getProjectionMatrix();

	modelMatrix = glm::translate(modelMatrix, position);
	modelMatrix = glm::rotate(modelMatrix, rotation_angle, rotation_vec);

	model_index = shader->GetUniformLocation( "model" );
	glUniformMatrix4fv( model_index, 1, GL_FALSE, &modelMatrix[0][0] );

	view_index = shader->GetUniformLocation( "view" );
	glUniformMatrix4fv( view_index, 1, GL_FALSE, &viewMatrix[0][0] );

	projection_index = shader->GetUniformLocation( "projection" );
	glUniformMatrix4fv(projection_index,1,GL_FALSE,&projectionMatrix[0][0]);

	//for all shapes in the obj file
	for(size_t i = 0;i<shapes.size();i++ )
	{
		tinyobj::mesh_t current_mesh = shapes[i].mesh;

		/*shader->BindAttribLocation(normal_index,"normal");
		glBufferData(GL_ARRAY_BUFFER,sizeof(float)*current_mesh.normals.size(), &current_mesh.normals[0],GL_STATIC_DRAW);
		glVertexAttribPointer(normal_index, 3, GL_FLOAT, GL_FALSE, 0, 0); 
		glEnableVertexAttribArray(normal_index);*/

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

void GeoModel3D::rotate(float angle, glm::vec3 vec)
{
	rotation_angle += angle;
	rotation_vec = vec;
}

void GeoModel3D::setPosition(glm::vec3 pos)
{
	position = pos;
}