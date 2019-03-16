#ifndef _SHADER_H_
#define _SHADER_H_
#pragma once

#include "libs.h"

#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <fstream>


class Shader
{
private:
	/*
		VARIABLES PRIVATE
	*/
	GLuint id;


	//////////////////////////////////////////////////////////////////////////////
	/*
		FUNKCJE PRIVATE
	*/
	std::string loadShaderSource(const char* filename);
	GLuint loadShader(GLenum type, const char* filename);
	void linkProgram(GLuint vertexShader, GLuint geometryShader, GLuint fragmentShader);
	//////////////////////////////////////////////////////////////////////////////
protected:

public:
	/*
		KONSTRUKTORY PUBLIC
	*/
	Shader(const char* vertexFile, const char* fragmentFile, const char* geometryFile = "");
	//////////////////////////////////////////////////////////////////////////////
	/*
		FUNKCJE PUBLIC
	*/
	void use();
	void unuse();
	//////////////////////////////////////////////////////////////////////////////
	/*
		SETTERY PUBLIC
	*/
	void setVec1f(GLfloat value, const GLchar* name);
	void set1i(GLint value, const GLchar* name);
	void setVec2f(glm::fvec2 value, const GLchar* name);
	void setVec3f(glm::fvec3 value, const GLchar* name);
	void setVec4f(glm::fvec4 value, const GLchar* name);
	void setMat3fv(glm::mat3 value, const GLchar* name, GLboolean transpose = GL_FALSE);
	void setMat4fv(glm::mat4 value, const GLchar* name, GLboolean transpose = GL_FALSE);
	//////////////////////////////////////////////////////////////////////////////
	/*
		GETTERY PUBLIC
	*/

	//////////////////////////////////////////////////////////////////////////////
	/*
			DESTRUKTOR
		*/
	~Shader();
	//////////////////////////////////////////////////////////////////////////////

};

#endif /* _SHADER_H_ */