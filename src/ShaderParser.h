#pragma once

#include<iostream>
#include <sstream>
#include<fstream>
#include"glm/glm.hpp"

struct ShaderProgram
{
    std::string VertexSource;
    std::string FragmentSource;
};
class ShaderParser
{
private:
    unsigned int m_RendererID;
    unsigned int m_ShaderID;
    unsigned int m_ProgramID;
    unsigned int m_FragmentShaderID;
    unsigned int m_VertexShaderID;
    const std::string m_FilePath;
public:
    ShaderParser(const std::string& filepath);
    ~ShaderParser();
    void SetUnifrom4f(const std::string& name, float v0, float v1, float v2, float v3);
    void SetUnifrom1i(const std::string& name, int slot);
    void SetUniformMat4f(const std::string& name, glm::mat4 MVP);
    void Bind() const;
    void Unbind() const;
private:
    ShaderProgram ParseShader(const std::string& filepath);

    unsigned int CompileShader(const std::string& source, unsigned int type);

    unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
    int GetUniformLocation(const std::string& name);
};