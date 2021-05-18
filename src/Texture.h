#pragma once
#include "Renderer.h"
class Texture
{
public:
	Texture(std::string path);
	~Texture();
	inline unsigned int GetWidth() const { return m_Width; }
	inline unsigned int GetHeight() const { return m_Height; }
	void Bind(unsigned int slot = 0) const ;
	void Unbind() const ;
private:
	unsigned int m_RendererID;
	int m_Width, m_Height, m_BPP;
	unsigned char* m_LocalBuffer;
	std::string m_FilePath;
};


