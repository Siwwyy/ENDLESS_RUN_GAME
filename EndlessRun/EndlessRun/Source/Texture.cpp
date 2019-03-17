#include "../Headers/Texture.h"
#include "../Headers/Renderer.h"
#include "../Headers/libs.h"

//#include "vendor/stb_image/stb_image.h"


//Texture::Texture(const std::string& path)
//	: m_RendererID(0), m_FilePath(path), m_LocalBuffer(nullptr),
//	m_Width(0), m_Height(0), m_BPP(0)
//{
//	// load image
//	stbi_set_flip_vertically_on_load(1);
//	m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);
//
//	GLCall(glGenTextures(1, &this->id));
//	GLCall(glBindTexture(type, this->id));
//
//	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
//	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
//	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
//	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
//
//	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
//	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
//
//	if (m_LocalBuffer) {
//		stbi_image_free(m_LocalBuffer);
//	}
//}

Texture::Texture(const char* path, GLenum type, GLint texture_unit):	//SIWY WAS HERE
	type(type),
	texture_unit(texture_unit)
	//m_RendererID(0), 
	/*m_FilePath(path),
	m_LocalBuffer(nullptr),
	m_Width(0),
	m_Height(0),
	m_BPP(0)*/
{
	//stbi_set_flip_vertically_on_load(1);
	//unsigned char * m_LocalBuffer = stbi_load(path.c_str(), &this->width, &this->height, &m_BPP, 4);

	////GLuint texture;
	//GLCall(glGenTextures(1, &this->id));
	//GLCall(glBindTexture(type, this->id));
	//		
	//GLCall(glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR));		//minimalize pixels
	//GLCall(glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR));		//magnify pixels 
	//GLCall(glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));		//S -> two coordinate, T -> one coordinate
	//GLCall(glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));		//S -> two coordinate, T -> one coordinate

	//if (m_LocalBuffer)
	//{
	//	std::cerr << "TEXTURE_LOADED" << '\n';
	//	/*	std::cerr << image << '\n';
	//		std::cerr << image_width << '\n';
	//		std::cerr << image_height << '\n';*/
	//	assert(m_LocalBuffer != NULL);
	//	assert(width != NULL);
	//	assert(height != NULL);
	//	GLCall(glTexImage2D(type, 0, GL_RGB, this->width, this->height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_LocalBuffer));
	//	GLCall(glBindTexture(type, 0));
	//	//glTexImage2D(type, 0, GL_RGB, this->width, this->height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_LocalBuffer);	//char is also a byte
	//	//glGenerateMipmap(type);
	//	//glDisable(GL_CULL_FACE);	//both sides photo
	//}
	//else
	//{
	//	std::cerr << "ERROR::TEXTURE::TEXTURE_LOADING_FAILED" << path << '\n';
	//}

	//glActiveTexture(0);
	//glBindTexture(type, 0);	//0 means 0 no active binde texture, 0 texture in there
	//stbi_image_free(m_LocalBuffer);
	//	// load image
	//stbi_set_flip_vertically_on_load(1);
	//unsigned char * m_LocalBuffer = stbi_load(path.c_str(), &this->width, &this->height, &m_BPP, 4);

	//GLCall(glGenTextures(1, &this->id));
	//GLCall(glBindTexture(type, this->id));

	//GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	//GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	//GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	//GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	//GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
	//GLCall(glBindTexture(GL_TEXTURE_2D, 0));

	//if (m_LocalBuffer) {
	//	stbi_image_free(m_LocalBuffer);
	//}
	this->type = type;
	this->texture_unit = texture_unit;
	unsigned char* image = SOIL_load_image(path, &this->width, &this->height, nullptr, SOIL_LOAD_RGB);
	//unsigned char* image = SOIL_load_image("IMAGES/sunset.png", &image_width, &image_height, NULL, SOIL_LOAD_RGB);

	GLuint texture; //0 means ID oh the image
	glGenTextures(1, &this->id);
	glBindTexture(type, this->id);

	glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);	//S -> two coordinate, T -> one coordinate
	glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);	//S -> two coordinate, T -> one coordinate
	glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);		//magnify pixels 
	glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);					//minimalize pixels

	if (image)
	{
		std::cerr << "TEXTURE_LOADED" << '\n';
		/*	std::cerr << image << '\n';
			std::cerr << image_width << '\n';
			std::cerr << image_height << '\n';*/
		assert(image != NULL);
		assert(width != NULL);
		assert(height != NULL);
		glTexImage2D(type, 0, GL_RGB, this->width, this->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);	//char is also a byte
		glGenerateMipmap(type);
		glDisable(GL_CULL_FACE);	//both sides photo
	}
	else
	{
		std::cerr << "ERROR::TEXTURE::TEXTURE_LOADING_FAILED" << path << '\n';
	}

	glActiveTexture(0);
	glBindTexture(type, 0);	//0 means 0 no active binde texture, 0 texture in there
	SOIL_free_image_data(image);
}

Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &this->id));
}

void Texture::Bind()	//SIWY WAS HERE
{
	GLCall(glActiveTexture(GL_TEXTURE0 + this->texture_unit));
	GLCall(glBindTexture(this->type, this->id));

}

void Texture::loadfromfile(const std::string & path)
{
	//currently empty, but it will have the same code as constructor
}

void Texture::Unbind()	//SIWY WAS HERE
{
	GLCall(glActiveTexture(0));
	GLCall(glBindTexture(this->type, 0));
}