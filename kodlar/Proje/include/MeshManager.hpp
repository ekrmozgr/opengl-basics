#ifndef MeshManager_hpp
#define MeshManager_hpp
#include<map>
#include<string>
#include "VertexTypes.hpp"
class Mesh2D;
class VertexArrayObject;

class MeshManager
{
public:
    Mesh2D* createCircle();
    Mesh2D* createSquare();
    Mesh2D* createTriangle();
    Mesh2D* createHexagon();
private:
    VertexArrayObject createTextureBuffers(const TexturedVertexList& vertices, const IndexList& indices);
    std::map<std::string,VertexArrayObject> vaoMap;
};


#endif