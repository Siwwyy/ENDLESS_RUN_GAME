#ifndef _ASSERT_H_
#define _ASSERT_H_
#pragma once

#include "Includes.h"	

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError(); x; ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << ") " << function << ' ' << file << ' ' << line << std::endl;
		return false;
	}
	return true;
}

#endif /* _ASSERT_H_ */