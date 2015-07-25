#include <Windows.h>
#include <WinGDI.h>
#include "SceneRenderer.h"

SceneRenderer::SceneRenderer()
{
}
SceneRenderer::~SceneRenderer()
{
	for(int i = 0; i < sizeof(vboID); i++)
	{
		glDeleteBuffers(1, &vboID[i]);
	}
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
void SceneRenderer::renderScene(Camera glCamera,std::vector<GeoModel3D*> models)
{
	std::vector<GeoModel3D*>::iterator object;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (shader) shader->begin();

	for(object = models.begin(); object != models.end(); object++)
	{
		createObject(*object);
		renderObject(glCamera, *object);
	}

	if (shader) shader->end();
    glutSwapBuffers();
}
void SceneRenderer::createObject(GeoModel3D* model)
{
	std::vector<float> vertices;
	std::vector<int> indices;
	std::vector<tinyobj::material_t> materials;
	std::map<unsigned int,unsigned int> textures;
	model->retrieveData(vertices,indices,materials,textures);

	glGenVertexArrays(1, &vaoID[0]); // Create our Vertex Array Object  
	glBindVertexArray(vaoID[0]); // Bind our Vertex Array Object so we can use it  
  
	glGenBuffers(1, vboID); // Generate our Vertex Buffer Object
	
	glBindBuffer(GL_ARRAY_BUFFER, vboID[0]); // Bind our Vertex Buffer Object
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices.size(), &vertices[0], GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW 
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer
	
	glEnableVertexAttribArray(0); // Disable our Vertex Array Object
	glBindVertexArray(0); // Disable our Vertex Buffer Object
}

void SceneRenderer::renderObject(Camera glCamera,GeoModel3D* model)
{
	glm::mat4 mvp_matrix = glCamera.getMVPMatrix() * model->getModelMatrix();
	shader->setUniformMatrix4fv("mvp_matrix",1,GL_FALSE,&mvp_matrix[0][0]);

	std::vector<float> vertices;
	std::vector<int> indices;
	std::vector<tinyobj::material_t> materials;
	std::map<unsigned int,unsigned int> textures;
	model->retrieveData(vertices, indices, materials,textures);

	glBindVertexArray(vaoID[0]); // Bind our Vertex Array Object
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, &indices[0] );
	glBindVertexArray(0); // Unbind our Vertex Array Object
}