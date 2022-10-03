#ifndef GUIControl_hpp
#define GUIControl_hpp
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <functional>
class GLFWwindow;

enum SHAPETYPE
{
    SHAPE_SQUARE = 0,
    SHAPE_CIRCLE = 1,
    SHAPE_HEXAGON = 2,
    SHAPE_TRIANGLE = 3
};

typedef std::function<void(SHAPETYPE)> CreateShapeFunction;
typedef std::function<void()> DeleteShapeFunction;
typedef std::function<void()> TextureToColorFunction;
typedef std::function<void()> ColorToTextureFunction;
class GUIControl
{
public:
    void init(GLFWwindow* window);
    void createWindow();
    void createWindowItems();
    void draw();
    void setAngle(float* angle);
    void setPos(glm::vec2* vecPos);
    void setScale(glm::vec2* vecScale);
    void setColor(glm::vec4* vecColor);
    CreateShapeFunction  clickCreateShape;
    DeleteShapeFunction  clickDeleteShape;
    TextureToColorFunction clickChangeTextureToColor;
    ColorToTextureFunction clickChangeColorToTexture;
private:
    float* angle;
    glm::vec2* vecPos;
    glm::vec2* vecScale;
    glm::vec4* vecColor;
    int selectedShape;
};

#endif