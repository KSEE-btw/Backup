#include "Renderer.h"

void glClearError()
{
    while (glGetError() != GL_NO_ERROR);
}
bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "GL ERROR = " << "(" << error << ")" << "\noccoured" << " at line = "
            << line << "\n file location is = " << file << "\nin function = " << function << std::endl;
        return false;
    }
    return true;
}

void Renderer::Draw(const ShaderParser& shader, const VertexArray& va, const IndexBuffer& ib) const
{
    shader.Bind();
    va.BindVertexArray();
    ib.Bind();//Index buffer binding
    GLCall(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clear() const
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}
