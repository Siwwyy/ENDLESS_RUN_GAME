#ifndef _VERTEX_BUFFER_H_
#define _VERTEX_BUFFER_H_
#pragma once

#include "libs.h"

class VertexBuffer
{
private:
	unsigned int m_RendererID;
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
};

#endif // _VERTEX_BUFFER_H_