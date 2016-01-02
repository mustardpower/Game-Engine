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
	glm::vec3 totalMomentum(float mass1, glm::vec3 velocity1, float mass2, glm::vec3 velocity2);
};