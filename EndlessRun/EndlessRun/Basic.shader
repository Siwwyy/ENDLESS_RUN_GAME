#shader vertex
#version 440 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 color;

out vec2 v_TexCoord;
out vec3 v_Color;

uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * position;
	v_TexCoord = texCoord;
	v_Color = color;
};

#shader fragment
#version 440 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in vec3 v_Color;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main()
{
	vec4 texColor = texture(u_Texture, v_TexCoord) * u_Color; 
	color = texColor; 
};