//#include "../Headers/Includes.h"
//#include "../Headers/libs.h"
#include "../Headers/Renderer.h"

#include <iostream>

void Renderer::Clear() const
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader)
{
	const_cast<Shader&>(shader).use();
	va.Bind();
	ib.Bind();
	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}
