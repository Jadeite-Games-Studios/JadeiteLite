#include "gui/imgui_wrapper.hpp"
#include "gui/imgui_utilities.hpp"

#include "logger/logger.hpp"
#include "platform/window.hpp"

#include "utilities/fonts/default_fonts.hpp"
#include "utilities/fonts/IconsFontAwesome5.hpp"


#include <SDL.h>
#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>
#include <SDL_opengl.h>
// ===================================

namespace Jadeite
{

bool Gui::InitImGui( Windowing::Window* pWindow )
{
    if ( m_bInitialized )
        return false;

    const char* glslVersion = "#version 450";
    IMGUI_CHECKVERSION();

    if ( !ImGui::CreateContext() )
    {
        JADE_ERROR( "Failed to create ImGui Context" );
        return false;
    }

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    io.ConfigWindowsMoveFromTitleBarOnly = true;

    ImFont* pDefaultFont = io.Fonts->AddFontDefault();
    ImGui::AddFont( "default", pDefaultFont, 13.f );

    float baseFontSize = 16.0f;
    float iconFontSize = baseFontSize * 2.0f / 3.0f;

    // merge in icons from Font Awesome
    static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_16_FA, 0 };
    ImFontConfig icons_config;
    icons_config.MergeMode = true;
    icons_config.PixelSnapH = true;
    icons_config.GlyphMinAdvanceX = iconFontSize;
    icons_config.GlyphOffset = ImVec2{ 0.f, 2.f };
    io.Fonts->AddFontFromMemoryTTF( Fonts::g_FaSolid900, Fonts::g_FaSolid900Size, baseFontSize,
                                    &icons_config, icons_ranges );

    if ( !ImGui_ImplSDL2_InitForOpenGL( pWindow->GetWindow().get(), pWindow->GetGLContext() ) )
    {
        JADE_ERROR( "Failed to intialize ImGui SDL2 for OpenGL!" );
        return false;
    }

    if ( !ImGui_ImplOpenGL3_Init( glslVersion ) )
    {
        JADE_ERROR( "Failed to intialize ImGui OpenGL3!" );
        return false;
    }

    ImGui::InitDefaultStyles();
    return true;
}

void Gui::Begin()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
}

void Gui::End( Windowing::Window* pWindow )
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData( ImGui::GetDrawData() );

    ImGuiIO& io = ImGui::GetIO();
    if ( io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable )
    {
        SDL_Window* backupCurrentWindow = SDL_GL_GetCurrentWindow();
        SDL_GLContext backupCurrentContext = SDL_GL_GetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        SDL_GL_MakeCurrent( backupCurrentWindow, backupCurrentContext );
    }
}

void Gui::ProcessEvent( const SDL_Event* event )
{
    ImGui_ImplSDL2_ProcessEvent( event );
}

void Gui::ShowImGuiDemo()
{
    ImGui::ShowDemoWindow();
}

void Gui::CleanUp()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

} // namespace Jadeite