#pragma once

union SDL_Event;

namespace Jadeite
{

namespace Windowing
{
class Window;
}

class Gui
{
public:
    Gui() = delete;

    static bool InitImGui( Windowing::Window* pWindow );

    static void Begin();

    static void End( Windowing::Window* pWindow );

    static void ProcessEvent( const SDL_Event* event );

    static void ShowImGuiDemo();

    static void CleanUp();

private:
    inline static bool m_bInitialized{ false };
};
} // namespace Jadeite