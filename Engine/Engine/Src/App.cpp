#include "Application.h"

#include "gui_controls.h"
#include "Scene.h"

int main() 
{
    Aplication app;

    app.Set_RenderGUI_Function(GUI_Controls::DrawGUI);
    app.Set_Render_Function(Scene::RenderScene);

    app.Run();
    return 0;
}
