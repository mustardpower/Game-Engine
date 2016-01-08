#include "Camera.h"
#include "glsl.h"
#include "Renderable.h"

//-----------------------------------------------------------------------------
// Name:		SceneRenderer
// Variables:	None
// Desc:		This class communicates with shaders drawing all the objects in the scene
//-----------------------------------------------------------------------------
class SceneRenderer
{
private:
	HDC hDC;
	HGLRC hRC;
	HWND hwnd;
	cwc::glShaderManager SM;
	cwc::glShader *shader;
	static GLuint NUMBER_OF_VAOS;
	GLuint vbos[3];	// 1 - positions 2 - normals 3 - texture coords
	GLuint IBO;
	std::map<GLuint,GLuint> object_vao_map;
public:
	SceneRenderer();
	~SceneRenderer();
	void onInit(HWND hWnd);

	void EnableOpenGL(HWND hWnd);
	void DisableOpenGL();

	void createVAO(GeoModel3D model);
	void renderScene(HDC hDC, Camera glCamera,std::vector<Renderable> objects);
	void createVertexBuffer(std::vector<GLfloat> vertices);
	void createIndexBuffer(std::vector<unsigned int> indices);
	void createNormalsBuffer(std::vector<GLfloat> normals);
	void createTexCoordsBuffer(std::vector<GLfloat> tex_coords);
	void renderModel(GeoModel3D model);
	void setTextureUnit(int unit);
};