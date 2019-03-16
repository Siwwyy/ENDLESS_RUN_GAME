#ifndef _VERTEX_ARRAY_H_
#define _VERTEX_ARRAY_H_
#pragma once

//#include "Includes.h"
//#include "libs.h"
#include "VertexBufferLayout.h"

class VertexBufferLayout;

class VertexArray
{
private:
	unsigned int m_RendererID;

public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

	void Bind() const;
	void Unbind() const;
};

#endif /*_VERTEX_ARRAY_H_ */