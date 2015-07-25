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
	unsigned int vaoID[1]; // Our Vertex Array Object
	unsigned int vboID[1]; // Our Vertex Buffer Object
public:
	SceneRenderer();
	~SceneRenderer();
	void onInit();
	void renderScene(Camera camera,std::vector<GeoModel3D*> models);
	void createObject(GeoModel3D* model);
	void renderObject(Camera glCamera,GeoModel3D* model);
	void setTextureUnit(int unit);
};