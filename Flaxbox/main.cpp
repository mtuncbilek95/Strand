#include <Runtime/Window/BasicWindow.h>
#include <Runtime/Renderer/Context.h>

using namespace Flax;

int main()
{
    WindowProps w11Props = 
    {
        .windowName = "Flax",
        .windowSize = { 1280, 720 },
        .windowMode = WindowMode::Windowed
    };
    Ref<BasicWindow> window = NewRef<BasicWindow>(w11Props);

    Context::Get().CreateContext(window.get());

    window->Show();
    while(window->IsActive())
    {
        window->ProcessEvents();

        Context::Get().PrepareFrame();
        Context::Get().SubmitFrame();
    }
    Context::Get().DestroyContext();

    window->Hide();
}