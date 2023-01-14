#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 texCoord;

out vec3 v_TexCoord;

uniform mat4 u_MVP;
uniform float u_Value;
uniform float u_Value2;

void main()
{
   gl_Position = vec4(u_Value + position.x, u_Value2 + position.y, position.z, 1.0f);
   v_TexCoord = texCoord;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec3 v_TexCoord;

uniform vec4 u_Color;
uniform sampler2D u_Texture;
uniform float u_Value3;

void main()
{
	vec4 texColor = vec4(0.83f  + u_Value3,  0.81f * u_Value3, 0.27f * u_Value3, 1.0f);
	color = texColor;
};