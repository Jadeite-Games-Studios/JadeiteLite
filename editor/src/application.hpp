#pragma once
#include <SDL.h>
#include <entt/entt.hpp>

namespace Jadeite
{

namespace Windowing
{
class Window;
}

namespace Events
{
struct CloseAppEvent;
}

namespace Core
{
class MainRegistry;
}

class Application
{
public:
    static Application& GetInstance();

    Application( const Application& ) = delete;
    Application& operator=( const Application& ) = delete;

    void Run();

private:
    Application();
    ~Application();

    bool Initialize();
    void InitAppEventHandlers();
    void InitImGuiWindows();
    bool CreateImGuiWindows();

    void RenderImGuiWindows();

    void ProcessEvents();
    void Update();
    void Render();

    void CleanUp();

    // Event Handling
    void OnCloseAppEvent( const Events::CloseAppEvent& );

private:
    bool m_bRunning;
    SDL_Event m_Event;
    std::unique_ptr<Windowing::Window> m_pWindow;
    std::unique_ptr<entt::registry> m_pRegistry;
    std::unique_ptr<Core::MainRegistry> m_pMainRegistry;
};
} // namespace Jadeite