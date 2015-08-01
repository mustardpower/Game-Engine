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
	static GLuint NUMBER_OF_VAOS;
	GLuint vbos[3];	// 1 - positions 2 - normals 3 - texture coords
	GLuint IBO;
	std::map<GLuint,GLuint> object_vao_map;
public:
	SceneRenderer();
	~SceneRenderer();
	void onInit();
	void createVAO(GeoModel3D* model);
	void renderScene(Camera glCamera,std::vector<GeoModel3D*> models);
	void createVertexBuffer(GLModel3DData data);
	void createIndexBuffer(GLModel3DData data);
	void createNormalsBuffer(GLModel3DData data);
	void createTexCoordsBuffer(GLModel3DData data);
	void renderObject(GeoModel3D* model);
	void setTextureUnit(int unit);
};