#version 450

layout(location = 0) in vec4 position;
layout(location = 2) in vec2 cord;
layout(location = 1) uniform int idx;
layout(location = 2) uniform vec2 RowCol;
 int rows; 
 int col;
 vec2 uv;
out vec2 fUV;

void main ()
{
	rows = int(RowCol.x);
	col = int(RowCol.y);
	
    int c = idx/col;
	int r = idx % col;

	gl_Position = position;
	fUV = (vec2(r,c) + cord) / vec2(rows,col);
}