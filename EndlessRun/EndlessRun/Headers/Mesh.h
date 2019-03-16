#ifndef _MESH_H_
#define _MESH_H_
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

/*
	BASIC LIBRARIES
*/
#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <fstream>

#include "Vertex.h"
#include "Shader.h"


class Mesh
{
private:
	/*
		VARIABLES PRIVATE
	*/
	//std::vector<Vertex> vertices;
	//std::vector<GLuint> indices;

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	glm::mat4 ModelMatrix;

	unsigned nrOfVertices;
	unsigned nrOfIndices;
	//////////////////////////////////////////////////////////////////////////////
	/*
		FUNKCJE PRIVATE
	*/
	//	void initVertexData(Vertex * vertexArray, const unsigned & nrOfVertices, GLuint * indexArray, const unsigned & nrOfIndices);
	void initVAO(Vertex * vertexArray, const unsigned & nrOfVertices, GLuint * indexArray, const unsigned & nrOfIndices);
	void initModelMatrix();
	void updateUniforms(Shader* shader);
	void updateModelMatrix();
	//////////////////////////////////////////////////////////////////////////////
protected:

public:
	/*
		KONSTRUKTORY PUBLIC
	*/
	Mesh();
	Mesh(Vertex * vertexArray, const unsigned & nrOfVertices, GLuint * indexArray, const unsigned & nrOfIndicies);
	//////////////////////////////////////////////////////////////////////////////
	/*
		FUNKCJE PUBLIC
	*/
	void update();
	void render(Shader * shader);
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
	~Mesh();
	//////////////////////////////////////////////////////////////////////////////
};


#endif /* _MESH_H_ */