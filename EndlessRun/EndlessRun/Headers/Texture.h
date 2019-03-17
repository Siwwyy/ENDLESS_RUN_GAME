#ifndef _TEXTURE_H_
#define _TEXTURE_H_
#pragma once

/*
OPENGL AND CONNECTED LIBRARIES
*/
//GLEW
#include <GL/glew.h>
//GLFW
#include <GLFW/glfw3.h>

//GLM
#include <glm.hpp>
#include <vec2.hpp>
#include <vec3.hpp>
#include <vec4.hpp>
#include <mat4x4.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

//SOIL2
#include<SOIL2.h>

// imgui
//#include <imgui\imgui.h> // todo
//#include <imgui\imgui_impl_glfw_gl3.h>

#include <iostream>
#include <string>
#include <windows.h>
#include <vector>
#include <fstream>

class Texture
{
private:
	/*unsigned int m_RendererID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;*/
	int m_BPP;

	GLuint id;
	int width;
	int height;
	unsigned int type;
	GLint texture_unit;
public:
	Texture(const std::string& path);
	Texture( const char*path , GLenum type, GLint texture_unit);
	~Texture();

	void Bind();
	void loadfromfile(const std::string& path);
	void Unbind();

	inline int GetWidth() const { return width; }
	inline int GetHeight() const { return height; }
	inline GLuint GetTextureID() const { return id; }
	inline GLint GetTextureUnit() const { return texture_unit; }
};

#endif /* _TEXTURE_H_ */