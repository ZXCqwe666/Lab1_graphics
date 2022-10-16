#include "gui_controls.h"

#include <glm\gtc\type_ptr.hpp>

#include "Scene.h"
#include "Time.h"
#include "GUI.h"

void GUI_Controls::DrawGUI()
{
    ImVec2 windowSize = { 350, 350 };
    ImGui::SetNextWindowSize(windowSize);
    ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x - windowSize.x, windowSize.y), ImGuiCond_Always, ImVec2(0.0f, 1.0f));

    ImGui::Begin("Debug");
    ImGui::Text("FPS : %i ", Time::displayFps);
    ImGui::Spacing();

    #pragma region add_remove_select

    ImGui::Text("Triangles created %i", Scene::trianglePool.size());

    if (ImGui::Button("AddTriangle"))
    {
        Triangle triangle;
        triangle.origin = glm::vec2(0.0f);
        triangle.verts[0] = { {0, 0}, {1, 1, 1}};
        triangle.verts[1] = { {100, 0}, {1, 1, 1} };
        triangle.verts[2] = { {0, 100}, {1, 1, 1} };
        Scene::AddTriangle(triangle);
    }

    if (ImGui::Button("RemoveTriangle"))
    {
        Scene::RemoveTriangle();
    }

    int max = Scene::trianglePool.size() - 1;
    max = max < 0 ? 0 : max;
    ImGui::SliderInt("Selected triangle", &Scene::selected_tringle_id, 0, max);

    ImGui::Text("Circles created %i", Scene::circlePool.size());

    if (ImGui::Button("AddCircle"))
    {
        Circle circle;
        circle.origin = glm::vec2(0.0f);
        circle.color = glm::vec3(0.0f);
        circle.radius = 1.0f;
        Scene::AddCircle(circle);
    }

    if (ImGui::Button("RemoveCircle"))
    {
        Scene::RemoveCircle();
    }

    max = Scene::circlePool.size() - 1;
    max = max < 0 ? 0 : max;
    ImGui::SliderInt("Selected circle", &Scene::selected_circle_id, 0, max);

    ImGui::Text("Quads created %i", Scene::quadPool.size());

    if (ImGui::Button("AddQuad"))
    {
        Quad quad;
        quad.origin = glm::vec2(0.0f);
        quad.color = glm::vec3(0.0f);
        quad.verts[0] = glm::vec2(0.0f, 0.0f);
        quad.verts[1] = glm::vec2(0.5f, 0.0f);
        quad.verts[2] = glm::vec2(0.5f, 0.5f);
        quad.verts[3] = glm::vec2(0.0f, 0.5f);
        Scene::AddQuad(quad);
    }

    if (ImGui::Button("RemoveQuad"))
    {
        Scene::RemoveQuad();
    }

    max = Scene::quadPool.size() - 1;
    max = max < 0 ? 0 : max;
    ImGui::SliderInt("Selected quad", &Scene::selected_quad_id, 0, max);

    ImGui::End();

    #pragma endregion
    #pragma region edit

    ImGui::Begin("Edit");
    ImGui::Text("EDIT SHAPES :");

    if (Scene::trianglePool.size() > 0)
    {
        ImGui::Spacing();
        ImGui::Text("TRIANGLE :");
        ImGui::Spacing();

        ImGui::SliderFloat2("Origin", glm::value_ptr(Scene::trianglePool[Scene::selected_tringle_id].origin), -2000.0f, 2000.0f);
        ImGui::SliderFloat2("VertPos 0", glm::value_ptr(Scene::trianglePool[Scene::selected_tringle_id].verts[0].position), -500.f, 500);
        ImGui::ColorEdit3("VertColor 0", glm::value_ptr(Scene::trianglePool[Scene::selected_tringle_id].verts[0].color));
        ImGui::SliderFloat2("VertPos 1", glm::value_ptr(Scene::trianglePool[Scene::selected_tringle_id].verts[1].position), -500.f, 500);
        ImGui::ColorEdit3("VertColor 1", glm::value_ptr(Scene::trianglePool[Scene::selected_tringle_id].verts[1].color));
        ImGui::SliderFloat2("VertPos 2", glm::value_ptr(Scene::trianglePool[Scene::selected_tringle_id].verts[2].position), -500.f, 500);
        ImGui::ColorEdit3("VertColor 2", glm::value_ptr(Scene::trianglePool[Scene::selected_tringle_id].verts[2].color));
    }

    if (Scene::circlePool.size() > 0)
    {
        ImGui::Spacing();
        ImGui::Text("CIRCLE :");
        ImGui::Spacing();

        ImGui::SliderFloat2("Origin ", glm::value_ptr(Scene::circlePool[Scene::selected_circle_id].origin), -2000.0f, 2000.0f);
        ImGui::SliderFloat("Radius", &Scene::circlePool[Scene::selected_circle_id].radius, 0, 1000);
        ImGui::ColorEdit3("Color", glm::value_ptr(Scene::circlePool[Scene::selected_circle_id].color));
    }

    if (Scene::quadPool.size() > 0)
    {
        ImGui::Spacing();
        ImGui::Text("QUAD :");
        ImGui::Spacing();

        ImGui::SliderFloat2("Origin  ", glm::value_ptr(Scene::quadPool[Scene::selected_quad_id].origin), -2000.0f, 2000.0f);
        ImGui::ColorEdit3("Color ", glm::value_ptr(Scene::quadPool[Scene::selected_quad_id].color));
        ImGui::SliderFloat2("VertPos 0 ", glm::value_ptr(Scene::quadPool[Scene::selected_quad_id].verts[0]), -500.f, 500);
        ImGui::SliderFloat2("VertPos 1 ", glm::value_ptr(Scene::quadPool[Scene::selected_quad_id].verts[1]), -500.f, 500);
        ImGui::SliderFloat2("VertPos 2 ", glm::value_ptr(Scene::quadPool[Scene::selected_quad_id].verts[2]), -500.f, 500);
        ImGui::SliderFloat2("VertPos 3 ", glm::value_ptr(Scene::quadPool[Scene::selected_quad_id].verts[3]), -500.f, 500);
    }

    ImGui::End();

    #pragma endregion
}
