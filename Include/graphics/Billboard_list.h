#pragma once

#include <iostream>
#include <string>
#include "glinc.h"
#include "RendererObjects.h"
#include "glm/ext.hpp"
#include "Billboard_Technique.h"
class BillboardList
{

public:
	BillboardList();
	~BillboardList();

	bool Init(const std::string& TexFileName);

	void Render(const glm::mat4& VP, const glm::vec3& CamPos);

private:
	void CreatePositionBuffer();

	GLuint m_VP;
	Texture* m_pTexture;
	BillboardTechnique m_technique;

};

