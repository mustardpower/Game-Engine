#include "Renderable.h"

Renderable::Renderable(char* file_name, glm::vec3 position)
{
	model = new GeoModel3D(file_name);
	model->setPosition(position);
}

void Renderable::render(cwc::glShader *shader, Camera camera)
{
	model->render(shader, camera);
}