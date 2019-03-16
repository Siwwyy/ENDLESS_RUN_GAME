#ifndef _RENDERER_H_
#define _RENDERER_H_
#pragma once

#include "../Headers/IndexBuffer.h"
#include "../Headers/VertexArray.h"
#include "../Headers/Shader.h"

class Renderer
{
public:
	void Clear() const;
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
};

#endif /* _RENDERER_H_ */