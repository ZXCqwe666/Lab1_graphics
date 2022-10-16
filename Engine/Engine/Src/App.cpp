#include "Application.h"
#include "AssetRegistry.h"

int main() 
{
    rendering::AssetRegistry::RegisterSprite({ 0, 0 }, { 150, 150 }, { 1200, 300 });

    Aplication app;
    app.Run();
    return 0;
}
