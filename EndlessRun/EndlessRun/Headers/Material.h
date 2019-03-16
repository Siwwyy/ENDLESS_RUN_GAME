#ifndef _MATERIAL_H_
#define _MATERIAL_H_
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

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

//#include "Texture.h"
#include "Shader.h"

/*
	BASIC LIBRARIES
*/
#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <fstream>

class Material
{
private:
	/*
		VARIABLES PRIVATE
	*/
	glm::vec3 ambient;		//the same variables as in structure in fragment core, cause we are sending it there from that class
	glm::vec3 diffuse;
	glm::vec3 specular;
	GLint diffuseTex;	//real color data
	GLint specularTex;
	//////////////////////////////////////////////////////////////////////////////
	/*
		FUNKCJE PRIVATE
	*/

	//////////////////////////////////////////////////////////////////////////////
protected:

public:
	/*
		KONSTRUKTORY PUBLIC
	*/
	Material();
	Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, GLint diffuseTex, GLint specularTex);
	//////////////////////////////////////////////////////////////////////////////
	/*
		FUNKCJE PUBLIC
	*/
	void sendToShader(Shader &  program);
	//////////////////////////////////////////////////////////////////////////////
	/*
		SETTERY PUBLIC
	*/

	//////////////////////////////////////////////////////////////////////////////
	/*
		GETTERY PUBLIC
	*/

	//////////////////////////////////////////////////////////////////////////////
	/*
		DESTRUKTOR
	*/
	~Material();
	//////////////////////////////////////////////////////////////////////////////
};

#endif /* _MATERIAL_H_ */