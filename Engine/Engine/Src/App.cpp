#include "Application.h"
#include "AssetRegistry.h"

#include "gui_controls.h"

int main() 
{
    Aplication app;

    app.Set_RenderGUI_Function(GUI_Controls::DrawGUI);

    app.Run();
    return 0;
}
