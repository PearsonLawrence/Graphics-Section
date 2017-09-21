#pragma once

#include "RendererObjects.h"


#include <cstdio>
#include <vector>

Texture loadTexture(const char* path);

Shader loadShader(const char* vpath, const char* fpath);

Geometry loadGeometry(const char* path);


Shader loadUpdateShader(const char* vert_path);
//#include <vector>
//#include <string>
//std::vector<std::string> paths = {"../../resources/cubemaps/","",""};


Skybox loadCubemap(std::vector<std::string> faces);