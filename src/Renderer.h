#pragma once
#include<GL/glew.h>
#include <iostream>
#include"ShaderParser.h"
#include"IndexBuffer.h"
#include "VertexArray.h"
#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) glClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

class Renderer
{
public:
    void Draw(const ShaderParser& shader, const VertexArray& va, const IndexBuffer& ib) const ;
    void Clear() const;
private:
    

};

void glClearError();
bool GLLogCall(const char* function, const char* file, int line);



