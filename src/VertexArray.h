#pragma once
#include "VertexBuffer.h"

class  VertextBufferLayout;


class VertexArray
{
private:
	unsigned int m_RendererID;
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const VertextBufferLayout& layout);
	void BindVertexArray() const;
	void UnBindVertexArray() const;


};
