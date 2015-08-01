#include <Windows.h>
#include <WinGDI.h>
#include "SceneRenderer.h"

GLuint SceneRenderer::NUMBER_OF_VAOS = 0;

SceneRenderer::SceneRenderer()
{
}
SceneRenderer::~SceneRenderer()
{
}
void SceneRenderer::onInit()
{
	glClearColor(0.5f, 0.5f, 1.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	glClearDepth( 1.0f );
	glDepthFunc( GL_LEQUAL );	

	shader = SM.loadfromFile("vert_shader.vs","frag_shader.fs"); // load (and compile, link) shaders from file
		if (shader==0) 
			std::cout << "Error Loading, compiling or linking shader\n";
}
void SceneRenderer::createVAO(GeoModel3D* model)
{
	GLuint vao_new_id;

	glGenVertexArrays(1,&vao_new_id); // Create our Vertex Array Object
	glBindVertexArray(vao_new_id); // Bind our Vertex Array Object so we can use it  

	glGenBuffers(1, &IBO);
	glGenBuffers(3,vbos);
	GLModel3DData modelData = model->retrieveData();
	GLuint model_id = model->getModelID();
	std::pair<GLuint,GLuint> mapping(model_id,vao_new_id);
	object_vao_map.insert(mapping);
	createVertexBuffer(modelData);
	/*createNormalsBuffer(modelData);*/
	createTexCoordsBuffer(modelData);
	createIndexBuffer(modelData);
	
	glEnableVertexAttribArray(0); // Disable our Vertex Array Object
	glBindVertexArray(0); // Disable our Vertex Buffer Object
}
void SceneRenderer::renderScene(Camera glCamera,std::vector<Renderable> objects)
{
	glm::mat4 object_model_matrix;
	glm::mat4 mvp_matrix;
	glm::mat4 camera_mvp_matrix = glCamera.getMVPMatrix();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (shader) shader->begin();

	for(std::vector<Renderable>::iterator object = objects.begin(); object != objects.end(); object++)
	{
		object_model_matrix = object->getModelMatrix();
		mvp_matrix = camera_mvp_matrix * object_model_matrix;
		shader->setUniformMatrix4fv("mvp_matrix",1,GL_FALSE,&mvp_matrix[0][0]);
		renderModel(object->getModel());
	}
	if (shader) shader->end();
    glutSwapBuffers();
}
void SceneRenderer::createVertexBuffer(GLModel3DData data)
{
	glBindBuffer(GL_ARRAY_BUFFER, vbos[0]); // Bind our Vertex Buffer Object
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * data.vertices.size(), &data.vertices[0], GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW

	GLint posAttrib = glGetAttribLocation(shader->GetProgramObject(), "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
}
void SceneRenderer::createNormalsBuffer(GLModel3DData data)
{
	glBindBuffer(GL_ARRAY_BUFFER, vbos[1]); // Bind our Vertex Buffer Object
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * data.normals.size(), &data.normals[0], GL_STATIC_DRAW); 

	GLint normalAttrib = glGetAttribLocation(shader->GetProgramObject(), "position");
    glEnableVertexAttribArray(normalAttrib);
    glVertexAttribPointer(normalAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
}
void SceneRenderer::createTexCoordsBuffer(GLModel3DData data)
{
	glBindBuffer(GL_ARRAY_BUFFER, vbos[2]); // Bind our Vertex Buffer Object
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * data.tex_coords.size(), &data.tex_coords[0], GL_STATIC_DRAW); 

	GLint textureAttrib = glGetAttribLocation(shader->GetProgramObject(), "TexCoord");
    glEnableVertexAttribArray(textureAttrib);
    glVertexAttribPointer(textureAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
}
void SceneRenderer::createIndexBuffer(GLModel3DData data)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * data.indices.size(), &data.indices[0], GL_STATIC_DRAW);
}

void SceneRenderer::renderModel(GeoModel3D* model)
{
	GLuint sampler_loc = 4;
	GLModel3DData modelData = model->retrieveData();
	GLuint vaoID = object_vao_map.at(model->getModelID());
	glBindVertexArray(vaoID); // Bind our Vertex Array Object

	glActiveTexture(GL_TEXTURE0);
	shader->BindAttribLocation(sampler_loc,"texture1");
	glBindTexture(GL_TEXTURE_2D,modelData.texture);

	glDrawElements(GL_TRIANGLES, modelData.indices.size(), GL_UNSIGNED_INT, 0);
}