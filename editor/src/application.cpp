#include "application.hpp"

#include "platform/window.hpp"
#include "logger/logger.hpp"
#include "gui/imgui_wrapper.hpp"

// Dockable Windows
#include "windows/menu_window.hpp"
#include "windows/logging_window.hpp"
#include "windows/scene_window.hpp"

#include "utilities/fonts/IconsFontAwesome5.hpp"

// Events
#include "core/events/event_dispatcher.hpp"
#include "core/events/event_types.hpp"

// ECS
#include "core/ecs/main_registry.hpp"

#include <glad/glad.h>
#include <imgui.h>
#include <imgui_internal.h>

namespace Jadeite
{
Application& Application::GetInstance()
{
    static Application instance{};
    return instance;
}

void Application::Run()
{
    m_bRunning = Initialize();
    while ( m_bRunning )
    {
        ProcessEvents();
        Update();
        Render();
    }

    CleanUp();
}

Application::Application()
    : m_bRunning{ false }
    , m_Event{}
    , m_pWindow{ nullptr }
    , m_pRegistry{ std::make_unique<entt::registry>() }
    , m_pMainRegistry{ std::make_unique<Core::MainRegistry>() }
{
}

Application::~Application()
{
}

bool Application::Initialize()
{
    bool bConsoleLog{ false };
#ifdef _DEBUG
    bConsoleLog = true;
#endif

    JADE_INIT_LOGS( bConsoleLog, true );

    // Init SDL
    if ( !SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) )
    {
        std::string error = SDL_GetError();
        JADE_ERROR( "Failed to initialize SDL: {}", error );
        return false;
    }

    // Set up OpenGL
    if ( !SDL_GL_LoadLibrary( NULL ) )
    {
        std::string error = SDL_GetError();
        JADE_ERROR( "Failed to Open GL Library: {0}", error );
        return false;
    }

    // Set the OpenGL attributes
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 4 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 5 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

    // Set the number of bits per channel
    SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 24 );
    SDL_GL_SetAttribute( SDL_GL_STENCIL_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
    SDL_GL_SetAttribute( SDL_GL_ACCELERATED_VISUAL, 1 );

    m_pWindow = std::make_unique<Windowing::Window>( "Jadeite Lite", 1920, 1080, true,
                                                     SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE );

    if ( !m_pWindow->GetWindow() )
    {
        JADE_ERROR( "Failed to create the window!" );
        return false;
    }

    // Create the openGL context
    m_pWindow->SetGLContext( SDL_GL_CreateContext( m_pWindow->GetWindow().get() ) );

    // Initialize Glad
    if ( !gladLoadGLLoader( (GLADloadproc) SDL_GL_GetProcAddress ) )
    {
        JADE_ERROR( "Failed to initialize GLAD" );
        return 1;
    }

    if ( !m_pWindow->GetGLContext() )
    {
        std::string error = SDL_GetError();
        JADE_ERROR( "Failed to create OpenGL context: {0}", error );
        return false;
    }

    if ( ( !SDL_GL_MakeCurrent( m_pWindow->GetWindow().get(), m_pWindow->GetGLContext() ) ) )
    {
        std::string error = SDL_GetError();
        JADE_ERROR( "Failed to make OpenGL context current: {0}", error );
        return false;
    }

    if ( !SDL_GL_SetSwapInterval( 1 ) )
    {
        JADE_WARN( "Unable to set VSync. SDL ERROR: {}", SDL_GetError() );
    }

    if ( !Gui::InitImGui( m_pWindow.get() ) )
    {
        JADE_ERROR( "Failed to initialize ImGui!" );
        return false;
    }

    m_pRegistry->ctx().emplace<SharedDockableWindowHolder>(
        std::make_shared<DockableWindowHolder>() );

    if ( !CreateImGuiWindows() )
    {
        JADE_ERROR( "Failed to create imgui windows" );
        return false;
    }

    InitAppEventHandlers();

    return true;
}

void Application::InitAppEventHandlers()
{
    auto* pDispatcher = m_pMainRegistry->GetEventDispatcher();
    JADE_ASSERT( pDispatcher && "Dispatcher must be valid" );
    ADD_EVENT_HANDLER( pDispatcher, Events::CloseAppEvent, &Application::OnCloseAppEvent, *this );
}

void Application::InitImGuiWindows()
{
    const auto dockSpaceId = ImGui::DockSpaceOverViewport( 0, ImGui::GetMainViewport() );

    if ( static bool firstTime = true; firstTime )
    {
        firstTime = false;

        ImGui::DockBuilderRemoveNode( dockSpaceId );
        ImGui::DockBuilderAddNode( dockSpaceId );

        auto centerNodeId = dockSpaceId;
        const auto LogNodeId = ImGui::DockBuilderSplitNode( centerNodeId, ImGuiDir_Down, 0.25f,
                                                            nullptr, &centerNodeId );

        ImGui::DockBuilderDockWindow( ICON_FA_IMAGE " Scene", centerNodeId );
        ImGui::DockBuilderDockWindow( ICON_FA_TERMINAL " Logs", LogNodeId );

        ImGui::DockBuilderFinish( dockSpaceId );
    }
}

bool Application::CreateImGuiWindows()
{
    auto& pDockableWindows = m_pRegistry->ctx().get<SharedDockableWindowHolder>();
    pDockableWindows->windows.emplace_back( std::make_unique<MenuWindow>( *m_pMainRegistry ) );
    pDockableWindows->windows.emplace_back( std::make_unique<SceneWindow>( *m_pMainRegistry ) );
    pDockableWindows->windows.emplace_back( std::make_unique<LogWindow>() );

    return true;
}

void Application::RenderImGuiWindows()
{
    InitImGuiWindows();

    auto& pDockableWindows = m_pRegistry->ctx().get<SharedDockableWindowHolder>();

    for ( const auto& pDockWindow : pDockableWindows->windows )
    {
        pDockWindow->Draw();
    }

    // Uncomment to see ImGui Demo
    // Gui::ShowImGuiDemo();
}

void Application::ProcessEvents()
{
    // Process Events
    while ( SDL_PollEvent( &m_Event ) )
    {
        switch ( m_Event.type )
        {
        case SDL_EVENT_QUIT:
            m_bRunning = false;
            break;
        case SDL_EVENT_KEY_DOWN:
            break;
        case SDL_EVENT_KEY_UP:
            break;
        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            break;
        case SDL_EVENT_MOUSE_BUTTON_UP:
            break;
        case SDL_EVENT_MOUSE_WHEEL:
            break;
        case SDL_EVENT_MOUSE_MOTION:
            break;
        case SDL_EVENT_GAMEPAD_BUTTON_DOWN:
            break;
        case SDL_EVENT_GAMEPAD_BUTTON_UP:
            break;
        case SDL_EVENT_GAMEPAD_ADDED:
            break;
        case SDL_EVENT_GAMEPAD_REMOVED:
            break;
        case SDL_EVENT_JOYSTICK_AXIS_MOTION:
            break;
        case SDL_EVENT_JOYSTICK_HAT_MOTION:
            break;

        case SDL_EVENT_WINDOW_RESIZED:
            if ( SDL_GetWindowID( m_pWindow->GetWindow().get() ) == m_Event.window.windowID )
            {
                m_pWindow->SetSize( m_Event.window.data1, m_Event.window.data2 );
            }
            break;

        case SDL_EVENT_DROP_FILE: {
            break;
        }
        default:
            break;
        }

        // Process ImGui events after other events
        Gui::ProcessEvent( &m_Event );
    }
}

void Application::Update()
{
}

void Application::Render()
{
    Gui::Begin();
    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT );
    RenderImGuiWindows();
    Gui::End( m_pWindow.get() );

    SDL_GL_SwapWindow( m_pWindow->GetWindow().get() );
}

void Application::CleanUp()
{
    // TODO: Fonts are destroyed after global fonts map destroyed
    // Gui::CleanUp();

    SDL_GL_DestroyContext( m_pWindow->GetGLContext() );
    SDL_DestroyWindow( m_pWindow->GetWindow().get() );
    SDL_Quit();
}

void Application::OnCloseAppEvent( const Events::CloseAppEvent& )
{
    m_bRunning = false;
    // TODO: Add other close actions.
    // Maybe check if things need to be saved?
}

} // namespace Jadeite