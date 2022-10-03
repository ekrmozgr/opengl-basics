#include "GUIControl.hpp"
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <iostream>

void GUIControl::init(GLFWwindow* window)
{
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window,true);
    ImGui_ImplOpenGL3_Init("#version 130");
    ImGui::StyleColorsClassic();
}

void GUIControl::createWindow()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void GUIControl::createWindowItems()
{
    ImGui::Begin("imgui penceresi");
    ImGui::SliderFloat("dondurme",angle,0,360);
    ImGui::SliderFloat2("oteleme",(float*)vecPos, -1.0f, 1.0f);
    ImGui::SliderFloat2("olcek",(float*)vecScale, 0.0f, 2.0f);
    ImGui::ColorEdit3("color",(float*)vecColor);
    if(ImGui::Button("Kaplama"))
    {
        clickChangeColorToTexture();
    }ImGui::SameLine();
    if(ImGui::Button("Renk"))
    {
        clickChangeTextureToColor();
    }ImGui::SameLine();
    if(ImGui::Button("Sil"))
    {
        clickDeleteShape();
    }
    ImGui::RadioButton("Kare",&selectedShape,0);ImGui::SameLine();
    ImGui::RadioButton("Daire",&selectedShape,1);ImGui::SameLine();
    ImGui::RadioButton("Altigen",&selectedShape,2);ImGui::SameLine();
    ImGui::RadioButton("Ucgen",&selectedShape,3);
    if(ImGui::Button("Sekil Olustur"))
    {
        clickCreateShape((SHAPETYPE)selectedShape);
    }

    ImGui::End();
}

void GUIControl::draw()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GUIControl::setAngle(float* angle)
{
    this->angle = angle;
}

void GUIControl::setPos(glm::vec2* vecPos)
{
    this->vecPos = vecPos;
}

void GUIControl::setScale(glm::vec2* vecScale)
{
    this->vecScale = vecScale;
}

void GUIControl::setColor(glm::vec4* vecColor)
{
    this->vecColor = vecColor;
}