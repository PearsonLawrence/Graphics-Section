#version 450

out vec4 outColor;


in vec2 fUV;

layout(location = 0) uniform sampler2D map;

void main ()
{
	outColor = texture(map, fUV.xy);
}