#pragma once
#include <vector>
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"

class PhysicsHandler
{
private:
	static const glm::vec3 gravity;	// in N/kg
public:
	void calculatePosition(glm::mat4 &modelmat, glm::vec3 velocity, float dt);
};