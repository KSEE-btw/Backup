#include"ShaderParser.h"
#include"Renderer.h"
ShaderParser::ShaderParser(const std::string& filepath)
    :m_RendererID(0) ,m_FilePath(filepath)
{  
    ShaderProgram source = ParseShader(filepath);
    m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
}

ShaderParser::~ShaderParser()
{
    glDeleteProgram(m_RendererID);
}

void ShaderParser::SetUnifrom4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void ShaderParser::SetUnifrom1i(const std::string& name, int slot)
{
    GLCall(glUniform1i(GetUniformLocation(name), slot));
    
}

ShaderProgram ShaderParser::ParseShader(const std::string& filepath)
{
    std::ifstream stream(filepath);
    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };
    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else
        {
            ss[(int)type] << line << '\n';
        }
    }
    return { ss[0].str(),ss[1].str() };
}
unsigned int ShaderParser::CompileShader(const std::string& source, unsigned int type)
{
    m_ShaderID = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(m_ShaderID, 1, &src, nullptr);
    glCompileShader(m_ShaderID);
    int result;
    glGetShaderiv(m_ShaderID, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(m_ShaderID, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)_malloca(length * sizeof(char));
        glGetShaderInfoLog(m_ShaderID, length, &length, message);
        std::cout << "failed  to compile " <<
            (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader !"
            << std::endl;
        glDeleteShader(m_ShaderID);
        return 0;

        std::cout << message << std::endl;


    }
    return m_ShaderID;
}
unsigned int ShaderParser::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    m_ProgramID = glCreateProgram();
    m_FragmentShaderID = CompileShader(fragmentShader, GL_FRAGMENT_SHADER);
    m_VertexShaderID = CompileShader(vertexShader, GL_VERTEX_SHADER);
    int status;
    glAttachShader(m_ProgramID, m_VertexShaderID);
    glAttachShader(m_ProgramID, m_FragmentShaderID);
    glLinkProgram(m_ProgramID);
    glValidateProgram(m_ProgramID);
    glGetProgramiv(m_ProgramID, GL_VALIDATE_STATUS, &status);
    if (status == GL_FALSE)
    {
        int length;
        glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)_malloca(length * sizeof(char));
        glGetProgramInfoLog(m_ProgramID, length, &length, message);
        std::cout << message;
    }

    glDeleteShader(m_VertexShaderID);
    glDeleteShader(m_FragmentShaderID);

    return m_ProgramID;
}

void ShaderParser::Bind() const
{
    GLCall(glUseProgram(m_RendererID));
}

void ShaderParser::Unbind() const
{
    GLCall(glUseProgram(0));
}
int ShaderParser::GetUniformLocation(const std::string& name)
{
    GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
    if (location == -1)
        std::cout << "Warning uniform : " << name << "doesn't exist" << std::endl;
    return location;
}
