#pragma once

struct Geometry;
struct Shader;
struct Framebuffer;
struct Texture;
#include "glm\fwd.hpp"

void s0_draw(const Framebuffer &f, const Shader &s, const Geometry &g);

void setUniform(const Shader &s, int location, float value);

void setUniform(const Shader & s, int location, int value);

void setUniform(const Shader & s, int location, const glm::vec4 &value);

void setUniform(const Shader &s, int location, const Texture &value, unsigned slot);

void clearFramebuffer(const Framebuffer &fb);
