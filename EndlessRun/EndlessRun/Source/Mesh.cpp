#include "../HEADERS/Mesh.h"

using namespace std;

//void Mesh::initVertexData(Vertex * vertexArray, const unsigned & nrOfVertices, GLuint * indexArray, const unsigned & nrOfIndices)
//{
//	for (size_t i = 0; i < nrOfVertices; i++)
//	{
//		this->vertices.push_back(vertexArray[i]);
//	}
//
//	for (size_t i = 0; i < nrOfIndices; i++)
//	{
//		this->indices.push_back(indexArray[i]);
//	}
//}

void Mesh::initVAO(Vertex * vertexArray, const unsigned & nrOfVertices, GLuint * indexArray, const unsigned & nrOfIndices)
{
	//SetVariables
	this->nrOfVertices = nrOfVertices;
	this->nrOfIndices = nrOfIndices;


	//Create VAO
	glCreateVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);

	//GENERATE VAO AND BIND AND SEND DATA
	glGenBuffers(1, &this->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);	//if u want change it dynamically
	glBufferData(GL_ARRAY_BUFFER, this->nrOfVertices * sizeof(Vertex), vertexArray, GL_STATIC_DRAW);

	//GENERATE EBO AND BIND AND SEND DATA
	glGenBuffers(1, &this->EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);  //if u want change it dynamically
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->nrOfIndices * sizeof(GLuint), indexArray, GL_STATIC_DRAW);


	//SET VERTEXATTRIBPOINTERS AND ENABLE (INPUT ASSEMBLY)
	//[0][0.5][0][1][0][0][1][0][]
	//POSITION
	//GLuint attribLoc = glGetAttribLocation(core_program, "vertex_position");  if u dont have a shader location put where are zeros this attrib location
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
	//[][][][][][][][][][][] ->VERTEX
	glEnableVertexAttribArray(0);

	//COLOR
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);

	//Texcoord
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
	glEnableVertexAttribArray(2);

	//Normal
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(3);

	//BIND VAO 0
	glBindVertexArray(0);
}

void Mesh::initModelMatrix()
{
	this->position = glm::vec3(0.f);
	this->rotation = glm::vec3(0.f);
	this->scale = glm::vec3(1.f);

	this->ModelMatrix = glm::mat4(1.f);
	this->ModelMatrix = glm::translate(this->ModelMatrix, this->position);
	this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.x), glm::vec3(1.f, 0.f, 0.f));
	this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.y), glm::vec3(0.f, 1.f, 0.f));
	this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.z), glm::vec3(0.f, 0.f, 1.f));
	this->ModelMatrix = glm::scale(this->ModelMatrix, this->scale);
}

void Mesh::updateUniforms(Shader * shader)
{
	shader->setMat4fv(this->ModelMatrix, "ModelMatrix");
}

void Mesh::updateModelMatrix()
{
	this->ModelMatrix = glm::mat4(1.f);
	this->ModelMatrix = glm::translate(this->ModelMatrix, this->position);
	this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.x), glm::vec3(1.f, 0.f, 0.f));
	this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.y), glm::vec3(0.f, 1.f, 0.f));
	this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.z), glm::vec3(0.f, 0.f, 1.f));
	this->ModelMatrix = glm::scale(this->ModelMatrix, this->scale);
}

Mesh::Mesh()
{
	//nothing here
}

Mesh::Mesh(Vertex * vertexArray, const unsigned & nrOfVertices, GLuint * indexArray, const unsigned & nrOfIndices)
{
	//this->initVertexData(vertexArray, nrOfVertices, indexArray, nrOfIndices);
	this->initVAO(vertexArray, nrOfVertices, indexArray, nrOfIndices);
	this->initModelMatrix();
	this->initModelMatrix();
}

void Mesh::update()
{

}

void Mesh::render(Shader * shader)
{
	//Update uniforms
	this->updateUniforms(shader);
	this->updateModelMatrix();

	shader->use();

	//Bind VAO
	glBindVertexArray(this->VAO);

	//Render
	/*if (this->indices.empty())
	{
		glDrawArrays(GL_TRIANGLES, 0, this->vertices.size());
	}*/
	glDrawElements(GL_TRIANGLES, this->nrOfIndices, GL_UNSIGNED_INT, 0);	//drawing by indices
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);
	glDeleteBuffers(1, &this->EBO);
}