#ifndef ShaderProgram_hpp
#define ShaderProgram_hpp
#include<string>
#include<map>
#include<glm/vec3.hpp>
#include<glm/vec4.hpp>
#include<glm/mat3x3.hpp>
class ShaderProgram
{
public:
    ShaderProgram();
    void attachShader(const std::string& fileName,
                        unsigned int shaderType);
    void link();
    void use();
    void addUniform(const std::string& varName);
    void setFloat(const std::string& varName, float value);
    void setVec3(const std::string& varName, const glm::vec3& value);
    void setVec4(const std::string& varName, const glm::vec4& value);
    void setMat3(const std::string& varName, const glm::mat3& value);
    void setInt(const std::string& varName, const int& value);
private:
    std::map<std::string, unsigned int> m_uniforms;
    unsigned int m_programId;
    unsigned int m_vertexShaderId;
    unsigned int m_fragmentShaderId;
};

#endif