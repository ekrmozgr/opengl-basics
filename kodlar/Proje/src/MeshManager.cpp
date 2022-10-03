#include "MeshManager.hpp"
#include "Mesh2D.hpp"
#include "VertexTypes.hpp"
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <iostream>


VertexArrayObject MeshManager::createTextureBuffers(const TexturedVertexList& vertices, const IndexList& indices)
{
    unsigned int vertexBufferId;
    unsigned int vertexArrayObjectId;
    unsigned int indexBufferId;

    glGenVertexArrays(1,&vertexArrayObjectId);
    glBindVertexArray(vertexArrayObjectId);

    glGenBuffers(1,&vertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER,vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER,sizeof(TexturedVertex)*vertices.size(),&vertices[0],GL_STATIC_DRAW);

    glGenBuffers(1,&indexBufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,indexBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(unsigned int)*indices.size(),&indices[0],GL_STATIC_DRAW);


    glVertexAttribPointer(0,3,GL_FLOAT,false,sizeof(TexturedVertex),0);
    glVertexAttribPointer(1,2,GL_FLOAT,false,sizeof(TexturedVertex),(const void*)(sizeof(float)*3));
    glEnableVertexAttribArray(0);  
    glEnableVertexAttribArray(1); 


    VertexArrayObject vao;
    vao.indexCount = indices.size();
    vao.id= vertexArrayObjectId;
    return vao;
}

Mesh2D* MeshManager::createCircle()
{
    VertexArrayObject vao;

    if(vaoMap.count("circle") == 0)
    {
        float angle = 10.0f;
        int vertexCount = 360.0/angle;            
        int triangleCount = vertexCount-2;        
        int circleIndexCount = triangleCount*3;      

        TexturedVertexList vertices(vertexCount);    
        IndexList           indices(circleIndexCount);  

        glm::vec3 pos;                          
        glm::vec2 tex;

        for(int i=0; i<vertexCount; i++)        
        {
            float nextAngle = glm::radians(i*angle);

            
            pos.x = glm::cos(nextAngle);         
            pos.y = glm::sin(nextAngle);        
            pos.z = 1.0f;                        

            tex.x = glm::cos(nextAngle)*0.5+0.5;
            tex.y = glm::sin(nextAngle)*0.5+0.5;

            vertices[i] = {pos, tex};
        }

        for(int i=0; i<triangleCount; i++)
        {   
            indices[i*3] = 0;
            indices[i*3+1] = i+1;
            indices[i*3+2] = i+2;
        }

        vao = createTextureBuffers(vertices, indices);
        vaoMap["circle"] = vao;
    }
    else
    {
        vao = vaoMap["circle"];
    }
    
    Mesh2D* mesh = new Mesh2D();
    mesh->vertexArrayObject = vao;
    return mesh;
}

Mesh2D* MeshManager::createSquare()
{
    VertexArrayObject vao;
    if(vaoMap.count("square") == 0)
    {
        TexturedVertexList vertices(4);
        IndexList           indices(6); 

        vertices[0].pos = glm::vec3(-0.5f, -0.5f, 1.0f);
        vertices[1].pos = glm::vec3(0.5f, -0.5f, 1.0f);
        vertices[2].pos = glm::vec3(0.5f, 0.5f, 1.0f);
        vertices[3].pos = glm::vec3(-0.5f, 0.5f, 1.0f);

        vertices[0].tex = glm::vec2(0.0f, 0.0f);
        vertices[1].tex = glm::vec2(1.0f, 0.0f);
        vertices[2].tex = glm::vec2(1.0f, 1.0f);
        vertices[3].tex = glm::vec2(0.0f, 1.0f);

        indices[0] = 0; indices[1] = 1; indices[2] = 2;
        indices[3] = 0; indices[4] = 2; indices[5] = 3; 

        vao = createTextureBuffers(vertices, indices);
        vaoMap["square"] = vao;
    }
    else
    {
        vao = vaoMap["square"];
    }

    Mesh2D* mesh = new Mesh2D();
    mesh->vertexArrayObject = vao;
    return mesh;
}

Mesh2D* MeshManager::createTriangle()
{
    VertexArrayObject vao;

    if(vaoMap.count("triangle") == 0)
    {
        TexturedVertexList vertices(3);

        vertices[0].pos = glm::vec3(-0.5f,0.0f,1.0f);
        vertices[1].pos = glm::vec3(0.5f,0.0f,1.0f);
        vertices[2].pos = glm::vec3(0.0f,1.0f,1.0f);

        vertices[0].tex = glm::vec2(0.0f, 0.0f);
        vertices[1].tex = glm::vec2(1.0f, 0.0f);
        vertices[2].tex = glm::vec2(0.5f, 1.0f);

        vao = createTextureBuffers(vertices, (IndexList){0,1,2});
        vaoMap["triangle"] = vao;
    }
    else
    {
        vao = vaoMap["triangle"];
    }
    Mesh2D* mesh = new Mesh2D();
    mesh->vertexArrayObject = vao;
    return mesh;
}

Mesh2D* MeshManager::createHexagon()
{
    VertexArrayObject vao;

    if(vaoMap.count("hexagon") == 0)
    {
        TexturedVertexList vertices(6);
        IndexList           indices(12); 

        float x_coord = 0.25f;
        float y_coord = 0.5f*glm::pow(3,1/2.0f);
        
        vertices[0].pos = glm::vec3(0.5f,0.0f,1.0f);
        vertices[1].pos = glm::vec3(x_coord,0.5f,1.0f);
        vertices[2].pos = glm::vec3(-x_coord,0.5f,1.0f);
        vertices[3].pos = glm::vec3(-0.5f,0.0f,1.0f);
        vertices[4].pos = glm::vec3(-x_coord,-0.5f,1.0f);
        vertices[5].pos = glm::vec3(x_coord,-0.5f,1.0f);

        
        vertices[0].tex = glm::vec2(1.0f, y_coord/2);
        vertices[1].tex = glm::vec2(0.75f, y_coord);
        vertices[2].tex = glm::vec2(0.25f, y_coord);
        vertices[3].tex = glm::vec2(0.0f, y_coord/2);
        vertices[4].tex = glm::vec2(0.25f, 0.0f);
        vertices[5].tex = glm::vec2(0.75f, 0.0f);

        for(int i = 0; i<4; i++)
        {
            indices[i*3] = 0;
            indices[i*3+1] = i+1;
            indices[i*3+2] = i+2;
        }

        vao = createTextureBuffers(vertices, indices);
        vaoMap["hexagon"] = vao;
    }
    else
    {
        vao = vaoMap["hexagon"];
    }
    Mesh2D* mesh = new Mesh2D();
    mesh->vertexArrayObject = vao;
    return mesh;
}