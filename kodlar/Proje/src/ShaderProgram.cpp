#include "ShaderProgram.hpp"
#include "FileLoader.hpp"
#include <glad/glad.h>
#include <iostream>

ShaderProgram::ShaderProgram()
{
    m_programId = 0;
    m_vertexShaderId = 0;
    m_fragmentShaderId = 0;
}

void ShaderProgram::addUniform(const std::string& varName)                     
{
    m_uniforms[varName] = glGetUniformLocation(m_programId ,varName.c_str());
}

void ShaderProgram::setFloat(const std::string& varName, float value)           
{
    glUniform1f(m_uniforms[varName],value);
}

void ShaderProgram::setVec3(const std::string& varName, const glm::vec3& value) 
{
    glUniform3f(m_uniforms[varName], value.x, value.y, value.z);
}

void ShaderProgram::setVec4(const std::string& varName, const glm::vec4& value) 
{
    glUniform4f(m_uniforms[varName], value.r, value.g, value.b, value.a);
}
void ShaderProgram::setMat3(const std::string& varName, const glm::mat3& value) 
{
    glUniformMatrix3fv(m_uniforms[varName], 1, false, &value[0][0]);
}
void ShaderProgram::setInt(const std::string& varName, const int& value)
{
    glUniform1i(m_uniforms[varName],value);
}
void ShaderProgram::attachShader(const std::string& fileName, unsigned int type) 
{
    std::string strSource = FileLoader::getRawData(fileName); 
    const char* Source = &strSource[0];                

    unsigned int shaderId = glCreateShader(type);
    glShaderSource(shaderId,1,&Source,0);
    glCompileShader(shaderId);

    int isCompiled;
    char message[512];
    glGetShaderiv(shaderId,GL_COMPILE_STATUS,&isCompiled);  

    std::string strShaderType;
    switch(type)                
    {
        case GL_VERTEX_SHADER:
            strShaderType = "VertexShader";
            m_vertexShaderId = shaderId;
        break;

        case GL_FRAGMENT_SHADER:
            strShaderType = "FragmentShader";
            m_fragmentShaderId = shaderId;
        break;
    }

    if(!isCompiled)     
    {
        glGetShaderInfoLog(shaderId,512,0,message);
        std::cout<<strShaderType<<" :"<<message<<std::endl;
    }
    else
    {
        if(m_programId==0)
            m_programId = glCreateProgram();
        
        glAttachShader(m_programId, shaderId);
    }
}

void ShaderProgram::link()
{
    glLinkProgram(m_programId);

    int isLinked;
    char programMessage[1024];

    glGetProgramiv(m_programId,GL_LINK_STATUS,&isLinked);   
    if(!isLinked)
    {
        glGetProgramInfoLog(m_programId,1024,0,programMessage); 
        std::cout<<"Program: "<<programMessage<<std::endl;
    }
}

void ShaderProgram::use()
{
    glUseProgram(m_programId);
}
