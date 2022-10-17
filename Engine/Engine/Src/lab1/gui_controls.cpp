#include "gui_controls.h"

#include "Scene.h"
#include "Time.h"
#include "GUI.h"

#include <glm\gtc\type_ptr.hpp>

int GUI_Controls::edit_id = 0;

void GUI_Controls::DrawGUI()
{
    ImVec2 windowSize = { 350, 350 };
    ImGui::SetNextWindowSize(windowSize, ImGuiCond_Once);
    ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x - windowSize.x, windowSize.y), ImGuiCond_Once, ImVec2(0.0f, 1.0f));

    ImGui::Begin("Debug");
    ImGui::Text("FPS : %i ", Time::displayFps);
    ImGui::Spacing();

    #pragma region add_remove_select

    ImGui::Text("Triangles created %i", Scene::trianglePool.size());

    if (ImGui::Button("AddTriangle"))
    {
        Triangle triangle;
        triangle.origin = glm::vec2(0.0f);
        triangle.verts[0] = { {0, 0}, glm::vec3(1.0f) };
        triangle.verts[1] = { {200, 0}, glm::vec3(1.0f) };
        triangle.verts[2] = { {0, 200}, glm::vec3(1.0f) };

        Scene::AddTriangle(triangle);
        edit_id = 0;
    }

    if (ImGui::Button("RemoveTriangle"))
    {
        Scene::RemoveTriangle();
    }

    int max = Scene::trianglePool.size() - 1;
    max = max < 0 ? 0 : max;
    ImGui::SliderInt("Selected triangle", &Scene::selected_tringle_id, 0, max);

    ImGui::Text("Quads created %i", Scene::quadPool.size());

    if (ImGui::Button("AddQuad"))
    {
        Quad quad;
        quad.origin = glm::vec2(0.0f);
        quad.color = glm::vec3(1.0f);
        quad.size = 200;

        Scene::AddQuad(quad);
        edit_id = 1;
    }

    if (ImGui::Button("RemoveQuad"))
    {
        Scene::RemoveQuad();
    }

    max = Scene::quadPool.size() - 1;
    max = max < 0 ? 0 : max;
    ImGui::SliderInt("Selected quad", &Scene::selected_quad_id, 0, max);

    ImGui::Text("Circles created %i", Scene::circlePool.size());

    if (ImGui::Button("AddCircle"))
    {
        Circle circle;
        circle.origin = glm::vec2(0.0f);
        circle.color = glm::vec3(1.0f);
        circle.radius = 100.0f;
        circle.fade = 0.005f;

        Scene::AddCircle(circle);
        edit_id = 2;
    }

    if (ImGui::Button("RemoveCircle"))
    {
        Scene::RemoveCircle();
    }

    max = Scene::circlePool.size() - 1;
    max = max < 0 ? 0 : max;
    ImGui::SliderInt("Selected circle", &Scene::selected_circle_id, 0, max);

    if (ImGui::Button("CLEAR ALL"))
    {
        while(Scene::trianglePool.size() > 0)
        {
            Scene::selected_tringle_id = Scene::trianglePool.size() - 1;
            Scene::RemoveTriangle();
        }

        while (Scene::circlePool.size() > 0)
        {
            Scene::selected_circle_id = Scene::circlePool.size() - 1;
            Scene::RemoveCircle();
        }

        while (Scene::quadPool.size() > 0)
        {
            Scene::selected_quad_id = Scene::quadPool.size() - 1;
            Scene::RemoveQuad();
        }
    }

    ImGui::End();

    #pragma endregion
    #pragma region edit

    ImVec2 windowSizeEdit = { 350, 550 };
    ImGui::SetNextWindowSize(windowSizeEdit, ImGuiCond_Once);
    ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x - windowSizeEdit.x, windowSizeEdit.y + windowSize.y), ImGuiCond_Once, ImVec2(0.0f, 1.0f));

    ImGui::Begin("Edit");
    ImGui::Text("EDIT SHAPES :");

    if (ImGui::Button("TRIANGLE")) edit_id = 0;
    if (ImGui::Button("QUAD")) edit_id = 1;
    if (ImGui::Button("CIRCLE")) edit_id = 2;

    if (edit_id == 0 && Scene::trianglePool.size() == 0) ImGui::Text("NO TRIANGLES CREATED");
    if (edit_id == 1 && Scene::trianglePool.size() == 0) ImGui::Text("NO QUADS CREATED");
    if (edit_id == 2 && Scene::trianglePool.size() == 0) ImGui::Text("NO CIRCLES CREATED");

    if (edit_id == 0 && Scene::trianglePool.size() > 0)
    {
        ImGui::Spacing();
        ImGui::Text("TRIANGLE :");
        ImGui::Spacing();

        ImGui::SliderFloat2("Origin", glm::value_ptr(Scene::trianglePool[Scene::selected_tringle_id].origin), -2000.0f, 2000.0f);
        ImGui::SliderFloat2("VertPos 0", glm::value_ptr(Scene::trianglePool[Scene::selected_tringle_id].verts[0].position), -1000.f, 1000.f);
        ImGui::ColorEdit3("VertColor 0", glm::value_ptr(Scene::trianglePool[Scene::selected_tringle_id].verts[0].color));
        ImGui::SliderFloat2("VertPos 1", glm::value_ptr(Scene::trianglePool[Scene::selected_tringle_id].verts[1].position), -1000.f, 1000.f);
        ImGui::ColorEdit3("VertColor 1", glm::value_ptr(Scene::trianglePool[Scene::selected_tringle_id].verts[1].color));
        ImGui::SliderFloat2("VertPos 2", glm::value_ptr(Scene::trianglePool[Scene::selected_tringle_id].verts[2].position), -1000.f, 1000.f);
        ImGui::ColorEdit3("VertColor 2", glm::value_ptr(Scene::trianglePool[Scene::selected_tringle_id].verts[2].color));

        ImGui::Checkbox("AnimateColor", &Scene::trianglePool[Scene::selected_tringle_id].anim.animate_color);

        if (Scene::trianglePool[Scene::selected_tringle_id].anim.animate_color)
        {
            ImGui::ColorEdit3("ColorA", glm::value_ptr(Scene::trianglePool[Scene::selected_tringle_id].anim.color_a));
            ImGui::ColorEdit3("ColorB", glm::value_ptr(Scene::trianglePool[Scene::selected_tringle_id].anim.color_b));
        }

        ImGui::Checkbox("AnimateScale", &Scene::trianglePool[Scene::selected_tringle_id].anim.animate_scale);

        if (Scene::trianglePool[Scene::selected_tringle_id].anim.animate_scale)
        {
            ImGui::SliderFloat("ScaleMin", &Scene::trianglePool[Scene::selected_tringle_id].anim.scale_min, 0.0f, 1.0f);
            ImGui::SliderFloat("ScaleMax", &Scene::trianglePool[Scene::selected_tringle_id].anim.scale_max, 0.0f, 1.0f);
        }

        ImGui::Checkbox("AnimatePosition", &Scene::trianglePool[Scene::selected_tringle_id].anim.animate_position);

        if (Scene::trianglePool[Scene::selected_tringle_id].anim.animate_position)
        {
            ImGui::SliderFloat2("OffsetA", glm::value_ptr(Scene::trianglePool[Scene::selected_tringle_id].anim.offset_a), -1000.f, 1000.f);
            ImGui::SliderFloat2("OffsetB", glm::value_ptr(Scene::trianglePool[Scene::selected_tringle_id].anim.offset_b), -1000.f, 1000.f);
        }
    }

    if (edit_id == 1 && Scene::quadPool.size() > 0)
    {
        ImGui::Spacing();
        ImGui::Text("QUAD :");
        ImGui::Spacing();

        ImGui::SliderFloat2("Origin  ", glm::value_ptr(Scene::quadPool[Scene::selected_quad_id].origin), -2000.0f, 2000.0f);
        ImGui::ColorEdit3("Color ", glm::value_ptr(Scene::quadPool[Scene::selected_quad_id].color));
        ImGui::SliderFloat("Size", &Scene::quadPool[Scene::selected_quad_id].size, 0, 1000);

        ImGui::Checkbox("AnimateColor ", &Scene::quadPool[Scene::selected_quad_id].anim.animate_color);

        if (Scene::quadPool[Scene::selected_quad_id].anim.animate_color)
        {
            ImGui::ColorEdit3("ColorA ", glm::value_ptr(Scene::quadPool[Scene::selected_quad_id].anim.color_a));
            ImGui::ColorEdit3("ColorB ", glm::value_ptr(Scene::quadPool[Scene::selected_quad_id].anim.color_b));
        }

        ImGui::Checkbox("AnimateScale ", &Scene::quadPool[Scene::selected_quad_id].anim.animate_scale);

        if (Scene::quadPool[Scene::selected_quad_id].anim.animate_scale)
        {
            ImGui::SliderFloat("ScaleMin ", &Scene::quadPool[Scene::selected_quad_id].anim.scale_min, 0.0f, 1.0f);
            ImGui::SliderFloat("ScaleMax ", &Scene::quadPool[Scene::selected_quad_id].anim.scale_max, 0.0f, 1.0f);
        }

        ImGui::Checkbox("AnimatePosition ", &Scene::quadPool[Scene::selected_quad_id].anim.animate_position);

        if (Scene::quadPool[Scene::selected_quad_id].anim.animate_position)
        {
            ImGui::SliderFloat2("OffsetA ", glm::value_ptr(Scene::quadPool[Scene::selected_quad_id].anim.offset_a), -1000.f, 1000.f);
            ImGui::SliderFloat2("OffsetB ", glm::value_ptr(Scene::quadPool[Scene::selected_quad_id].anim.offset_b), -1000.f, 1000.f);
        }
    }

    if (edit_id == 2 && Scene::circlePool.size() > 0)
    {
        ImGui::Spacing();
        ImGui::Text("CIRCLE :");
        ImGui::Spacing();

        ImGui::SliderFloat2("Origin ", glm::value_ptr(Scene::circlePool[Scene::selected_circle_id].origin), -2000.0f, 2000.0f);
        ImGui::SliderFloat("Radius", &Scene::circlePool[Scene::selected_circle_id].radius, 0, 1000);
        ImGui::SliderFloat("Fade", &Scene::circlePool[Scene::selected_circle_id].fade, 0, 0.5f);
        ImGui::ColorEdit3("Color", glm::value_ptr(Scene::circlePool[Scene::selected_circle_id].color));

        ImGui::Checkbox("AnimateColor  ", &Scene::circlePool[Scene::selected_circle_id].anim.animate_color);

        if (Scene::circlePool[Scene::selected_circle_id].anim.animate_color)
        {
            ImGui::ColorEdit3("ColorA  ", glm::value_ptr(Scene::circlePool[Scene::selected_circle_id].anim.color_a));
            ImGui::ColorEdit3("ColorB  ", glm::value_ptr(Scene::circlePool[Scene::selected_circle_id].anim.color_b));
        }

        ImGui::Checkbox("AnimateScale  ", &Scene::circlePool[Scene::selected_circle_id].anim.animate_scale);

        if (Scene::circlePool[Scene::selected_circle_id].anim.animate_scale)
        {
            ImGui::SliderFloat("ScaleMin  ", &Scene::circlePool[Scene::selected_circle_id].anim.scale_min, 0.0f, 1.0f);
            ImGui::SliderFloat("ScaleMax  ", &Scene::circlePool[Scene::selected_circle_id].anim.scale_max, 0.0f, 1.0f);
        }

        ImGui::Checkbox("AnimatePosition  ", &Scene::circlePool[Scene::selected_circle_id].anim.animate_position);

        if (Scene::circlePool[Scene::selected_circle_id].anim.animate_position)
        {
            ImGui::SliderFloat2("OffsetA  ", glm::value_ptr(Scene::circlePool[Scene::selected_circle_id].anim.offset_a), -1000.f, 1000.f);
            ImGui::SliderFloat2("OffsetB  ", glm::value_ptr(Scene::circlePool[Scene::selected_circle_id].anim.offset_b), -1000.f, 1000.f);
        }
    }

    ImGui::End();

    #pragma endregion
}
