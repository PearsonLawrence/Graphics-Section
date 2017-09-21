#pragma once
#include <iostream>
#include "glm\ext.hpp"
#include "glinc.h"


class ParticleSystem
{
public:
	ParticleSystem();

	~ParticleSystem();

	bool initParticleSystem(const glm::vec3& Pos);

private:

	bool m_isFirst;

	unsigned int m_currVB; // Vertex buffer
	unsigned int m_currTFB; //Transform buffer

	GLuint m_particleBuffer[2];
	GLuint m_transformFeedback[2];


};