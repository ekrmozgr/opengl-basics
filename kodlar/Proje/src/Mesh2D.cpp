#include "Mesh2D.hpp"
#include "ShaderProgram.hpp"

#include <glm/gtx/matrix_transform_2d.hpp>
#include<glm/mat3x3.hpp>

Mesh2D::Mesh2D()
{
    float x = (rand()%256)/256.0f;
    x-=0.5f;
    float y = (rand()%256)/256.0f;
    y-=0.5f;
    position=glm::vec2(x,y);
    scale = glm::vec2(1.0f,1.0f);
    angle= 0.0f;
    color = glm::vec4(1.0f,0.0f,1.0f,1.0f);
    colorActive = false;
    update();
}
bool Mesh2D::getColorActive()
{
    return colorActive;
}
void Mesh2D::setColorActive(bool active)
{
    colorActive = active;
}
void Mesh2D::setColor(const glm::vec4& color)
{
    this->color = color;
}
void Mesh2D::setPosition(const glm::vec2& pos)
{
    this->position = pos;
    update();
}
void Mesh2D::setScale(const glm::vec2& scale)
{
    this->scale = scale;
     update();
}
void Mesh2D::setAngle(float angle)
{
    this->angle = angle;
     update();
}
void Mesh2D::update()
{
    glm::mat3 mtxRotate = glm::rotate(glm::mat3(1),glm::radians(angle));
    glm::mat3 mtxTranslate = glm::translate(glm::mat3(1),position);
    glm::mat3 mtxScale = glm::scale(glm::mat3(1),scale/2.0f);
    mtxWorld = mtxTranslate*mtxRotate*mtxScale;

}
void Mesh2D::rotate(float angle)
{
    if(this->angle>360)
    {
        this->angle=360-this->angle;
    }
    this->angle+=angle;
    update();
}
void Mesh2D::draw(ShaderProgram& program)
{
    program.setMat3("uMtxTransform",mtxWorld);
    if(colorActive)
    {
        program.setVec4("uColor",color);
        program.setInt("uTextureFlag",0);
    }
    else
    {
        program.setVec4("uColor",glm::vec4(0.0,0.0,0.0,0.0));
        program.setInt("uTextureFlag",1);
    }
    vertexArrayObject.use();
    vertexArrayObject.draw();
    vertexArrayObject.unuse();
}

glm::vec2* Mesh2D::getPosition()
{
    return &this->position;
}

glm::vec2* Mesh2D::getScale()
{
    return &this->scale;
}

glm::vec4* Mesh2D::getColor()
{
    return &this->color;
}

float* Mesh2D::getAngle()
{
    return &angle;
}