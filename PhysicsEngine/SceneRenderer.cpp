#include "SceneRenderer.h"

SceneRenderer::SceneRenderer()
{
	glClearColor(0.5f, 0.5f, 1.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	glClearDepth( 1.0f );
	glDepthFunc( GL_LEQUAL );	

	shader = SM.loadfromFile("vert_shader.vs","frag_shader.fs"); // load (and compile, link) shaders from file
		if (shader==0) 
			std::cout << "Error Loading, compiling or linking shader\n";

	/* Allocate and assign two Vertex Buffer Objects to our handle */
    glGenBuffers(1, &vertex_index);
	glGenBuffers(1, &normal_index);
}
SceneRenderer::~SceneRenderer()
{
	glDeleteBuffers(1, &vertex_index);
	glDeleteBuffers(1, &normal_index);
}
void SceneRenderer::renderScene(Camera glCamera,std::vector<GeoModel3D*> models)
{
	std::vector<GeoModel3D*>::iterator object;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (shader) shader->begin();

	for(object = models.begin(); object != models.end(); object++)
	{
		renderObject(glCamera,*object);
	}

	if (shader) shader->end();
    glutSwapBuffers();
}
void SceneRenderer::renderObject(Camera glCamera,GeoModel3D* model)
{
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::map<unsigned int,unsigned int> textures;
	glm::mat4 mvp_matrix;

	GLuint program = shader->GetProgramObject();
	glm::mat4 view_matrix = glCamera.getViewMatrix();
	glm::mat4 projection_matrix = glCamera.getProjectionMatrix();

	glm::mat4 model_matrix = glCamera.getModelMatrix() * model->getModelMatrix();
	mvp_matrix = projection_matrix * view_matrix * model_matrix;
	shader->setUniformMatrix4fv("mvp_matrix",1,GL_FALSE,&mvp_matrix[0][0]);

	model->retrieveData(shapes,materials,textures);
	
	// each mesh is made up of a number of shapes
	for(size_t i = 0;i<shapes.size();i++ )
	{
		tinyobj::mesh_t current_mesh = shapes[i].mesh;

		/* Bind our first VBO as being the active buffer and storing vertex attributes */
		glBindBuffer(GL_ARRAY_BUFFER, vertex_index);
		glBufferData(GL_ARRAY_BUFFER,sizeof(float)*current_mesh.positions.size(), &current_mesh.positions[0], GL_STATIC_DRAW);
		glVertexAttribPointer(vertex_index, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(vertex_index);

		/* Bind our second VBO as being the active buffer and storing normal attributes */
		glBindBuffer(GL_ARRAY_BUFFER,normal_index);
		glBufferData(GL_ARRAY_BUFFER,sizeof(float)*current_mesh.normals.size(), &current_mesh.normals[0], GL_STATIC_DRAW);
		glVertexAttribPointer(normal_index, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(normal_index);

		glDrawElements(GL_TRIANGLES, shapes[i].mesh.indices.size(), GL_UNSIGNED_INT, &current_mesh.indices[0] );
	}

	// these attributes are no longer used in the shader
	glDisableVertexAttribArray(vertex_index);
	glDisableVertexAttribArray(normal_index);
}