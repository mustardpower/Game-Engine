#pragma once
#include "glm\glm.hpp"

class PhysicsHandler
{
private:
	static const glm::vec3 gravity;	// in N/kg
public:
	void updateFrame();
};