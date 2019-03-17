#version 440 core

in vec3 vs_position;
in vec3 vs_color;
in vec2 vs_texcoord;
in vec3 vs_normal;

out vec4 fs_color;

//uniform vec4 u_Color;
uniform sampler2D texture0;

void main()
{
	//vec3 texColor = texture(texture0, vs_texcoord) * vs_color;
	//fs_color = texture(texture0, vs_texcoord); //ranbowish color
	//vec4(vs_color, 1.f)
	fs_color = texture(texture0, vs_texcoord);	//rainbow color by multiplaying the color
};