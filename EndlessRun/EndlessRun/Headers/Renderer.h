#ifndef _RENDERER_H_
#define _RENDERER_H_
#pragma once

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{
public:
	void Clear() const;
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};

#endif /* _RENDERER_H_ */