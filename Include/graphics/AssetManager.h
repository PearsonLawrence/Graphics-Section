#pragma once
#include "RendererObjects.h"
#include <iostream>
#include <string>
class AssetLoader
{
public:

	Skybox loadSkybox(std::string name);
	Geometry loadGeo(std::string name);
	Texture loadTexture(std::string name);
	Shader loadShaderAsset(std::string name, std::string name2);


};