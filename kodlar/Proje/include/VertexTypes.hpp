#ifndef VertexTypes_hpp
#define VertexTypes_hpp
#include<glm/vec3.hpp>
#include<glm/vec4.hpp>
#include<glm/vec2.hpp>
#include<vector>

class TexturedVertex
{
public:
    glm::vec3 pos;
    glm::vec2 tex;
};

typedef std::vector<TexturedVertex> TexturedVertexList;
typedef std::vector<unsigned int> IndexList;
#endif