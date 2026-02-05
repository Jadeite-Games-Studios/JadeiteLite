#include "platform/window.hpp"
#include "logger/logger.hpp"

namespace Jadeite::Windowing
{
Window::Window()
    : Window( "default_window", 640, 480, true, NULL )
{
}

Window::Window( const std::string& title, int width, int height, bool v_sync, Uint32 flags )
    : m_pWindow{ nullptr }
    , m_GLContext{}
    , m_sTitle{ title }
    , m_Width{ width }
    , m_Height{ height }
    , m_XPos{ 0 }
    , m_YPos{ 0 }
    , m_WindowFlags{ flags }
{
    CreateNewWindow( flags );

    // Enable v-sync
    if ( v_sync )
    {
        if ( !SDL_SetHint( SDL_HINT_RENDER_VSYNC, "1" ) )
            JADE_ERROR( "Failed to enable VSYNC!" );
    }

    JADE_LOG( "Window Created Successfully!" );
    SDL_GetWindowPosition( m_pWindow.get(), &m_XPos, &m_YPos );
}

Window::~Window()
{
}

void Window::SetPosition( int x, int y )
{
    SDL_SetWindowPosition( m_pWindow.get(), x, y );
    m_XPos = x;
    m_YPos = y;
}

void Window::SetSize( int width, int height )
{
    m_Width = width;
    m_Height = height;
    SDL_SetWindowSize( m_pWindow.get(), width, height );
}

void Window::SetWindowTitle( const std::string& name )
{
    m_sTitle = name;
    SDL_SetWindowTitle( m_pWindow.get(), name.c_str() );
}

void Window::CreateNewWindow( Uint32 flags )
{
    m_pWindow = WindowPtr( SDL_CreateWindow( m_sTitle.c_str(), m_Width, m_Height, flags ) );

    // Check to see if the window was created correctly
    if ( !m_pWindow )
    {
        std::string error = SDL_GetError();
        JADE_ERROR( "Failed to create the Window: {}", error );
    }
}

} // namespace Jadeite::Windowing