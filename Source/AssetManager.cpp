#include "..\Include\graphics\AssetManager.h"
#include "graphics\Load.h"

Skybox AssetLoader::loadSkybox(std::string name)
{

	return Skybox();
}

Geometry AssetLoader::loadGeo(std::string name)
{
	std::string asset = "../../resources/models/";

	 asset += name;
	return loadGeometry(asset.c_str());
}

Texture AssetLoader::loadTexture(std::string name)
{

	const char* asset = "../../resources/textures/";
	name += asset;
	return loadTexture(name);
}

Shader AssetLoader::loadShaderAsset(std::string name, std::string name2)
{

	std::string asset = "../../resources/shaders/";

	std::string asset2 = "../../resources/shaders/";

	asset += name;
	asset2 += name2;

	return loadShader(asset.c_str(), asset2.c_str());
}
