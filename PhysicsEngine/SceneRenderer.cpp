#include <Windows.h>
#include <WinGDI.h>
#include "SceneRenderer.h"

GLuint SceneRenderer::NUMBER_OF_VAOS = 0;

SceneRenderer::SceneRenderer()
{
}
SceneRenderer::~SceneRenderer()
{
	DisableOpenGL();
}

void SceneRenderer::onInit(HWND hWnd)
{
	hwnd = hWnd;
	EnableOpenGL(hwnd);
	glClearColor(0.5f, 0.5f, 1.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);

	shader = SM.loadfromFile("vert_shader.vs","frag_shader.fs"); // load (and compile, link) shaders from file
		if (shader==0) 
			std::cout << "Error Loading, compiling or linking shader\n";
}

void SceneRenderer::createVAO(GeoModel3D* model)
{
	GLuint vao_new_id;

	std::vector<GLModel3DData> modelData = model->retrieveMeshes();

	for (std::vector<GLModel3DData>::iterator mesh = modelData.begin(); mesh != modelData.end(); mesh++)
	{ 
		glGenVertexArrays(1, &vao_new_id); // Create our Vertex Array Object
		glBindVertexArray(vao_new_id); // Bind our Vertex Array Object so we can use it  

		glGenBuffers(1, &IBO);
		glGenBuffers(3, vbos);

		GLuint mesh_id = mesh->getMeshID();
		tinyobj::mesh_t mesh_data = mesh->getMeshData();
		std::pair<GLuint, GLuint> mapping(mesh_id, vao_new_id);
		object_vao_map.insert(mapping);
		createVertexBuffer(mesh_data.positions);
		/*createNormalsBuffer(mesh_data.normals);*/
		createTexCoordsBuffer(mesh_data.texcoords);
		createIndexBuffer(mesh_data.indices);

		glEnableVertexAttribArray(0); // Disable our Vertex Array Object
		glBindVertexArray(0); // Disable our Vertex Buffer Object
	}
}
void SceneRenderer::renderScene(HDC hDc,Camera glCamera,std::vector<Renderable> objects)
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
	SwapBuffers(hDc);
}
void SceneRenderer::createVertexBuffer(std::vector<GLfloat> vertices)
{
	glBindBuffer(GL_ARRAY_BUFFER, vbos[0]); // Bind our Vertex Buffer Object
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices.size(), &vertices[0], GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW

	GLint posAttrib = glGetAttribLocation(shader->GetProgramObject(), "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
}
void SceneRenderer::createNormalsBuffer(std::vector<GLfloat> normals)
{
	glBindBuffer(GL_ARRAY_BUFFER, vbos[1]); // Bind our Vertex Buffer Object
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * normals.size(), &normals[0], GL_STATIC_DRAW); 

	GLint normalAttrib = glGetAttribLocation(shader->GetProgramObject(), "position");
    glEnableVertexAttribArray(normalAttrib);
    glVertexAttribPointer(normalAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
}
void SceneRenderer::createTexCoordsBuffer(std::vector<GLfloat> tex_coords)
{
	if (tex_coords.empty())
	{
		printf("No texture coordinates - will not show object until alternative shader is defined");
		return;
	}
	glBindBuffer(GL_ARRAY_BUFFER, vbos[2]); // Bind our Vertex Buffer Object
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * tex_coords.size(), &tex_coords[0], GL_STATIC_DRAW); 

	GLint textureAttrib = glGetAttribLocation(shader->GetProgramObject(), "TexCoord");
    glEnableVertexAttribArray(textureAttrib);
    glVertexAttribPointer(textureAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
}
void SceneRenderer::createIndexBuffer(std::vector<unsigned int> indices)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), &indices[0], GL_STATIC_DRAW);
}

void SceneRenderer::renderModel(GeoModel3D* model)
{
	GLuint sampler_loc = 4;
	std::vector<GLModel3DData> modelData = model->retrieveMeshes();
	for (std::vector<GLModel3DData>::iterator m = modelData.begin(); m != modelData.end(); m++)
	{
		// if errors here ensure to create VAOs
		GLuint vaoID = object_vao_map.at(m->getMeshID());
		glBindVertexArray(vaoID); // Bind our Vertex Array Object

		glActiveTexture(GL_TEXTURE0);
		shader->BindAttribLocation(sampler_loc, "texture1");
		glBindTexture(GL_TEXTURE_2D, m->texture);

		tinyobj::mesh_t mesh = m->getMeshData();
		glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, 0);
	}
}

void SceneRenderer::EnableOpenGL(HWND hWnd)
{
	// get the device context (DC)
	hwnd = hWnd;
	hDC = GetDC(hwnd);

	// set the pixel format for the DC
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(pfd));
	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 16;
	pfd.iLayerType = PFD_MAIN_PLANE;
	int format = ChoosePixelFormat(hDC, &pfd);
	SetPixelFormat(hDC, format, &pfd);

	// create the render context (RC)
	HGLRC mhRC = wglCreateContext(hDC);

	// make it the current render context
	wglMakeCurrent(hDC, mhRC);
}

void SceneRenderer::DisableOpenGL()
{
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(hRC);
	ReleaseDC(hwnd, hDC);
}