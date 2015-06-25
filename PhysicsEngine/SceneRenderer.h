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
	cwc::glShaderManager SM;
	cwc::glShader *shader;
	GLuint vao;
	GLuint vertex_index, normal_index;	//vbos
public:
	SceneRenderer();
	~SceneRenderer();
	void renderScene(Camera camera,std::vector<GeoModel3D*> models);
	void renderObject(Camera glCamera,GeoModel3D* model);
};