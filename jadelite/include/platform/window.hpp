#pragma once
#include "utilities/sdl_utilities.hpp"

namespace Jadeite::Windowing
{
class Window
{
public:
    Window();
    Window( const std::string& title, int width, int height, int x_pos, int y_pos,
            bool v_sync = true,
            Uint32 flags = ( SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
                             | SDL_WINDOW_MOUSE_CAPTURE ) );
    ~Window();

    void SetPosition( int x, int y );
    void SetSize( int width, int height );
    void SetWindowTitle( const std::string& name );

    inline void SetGLContext( SDL_GLContext gl_context )
    {
        m_GLContext = gl_context;
    }
    inline SDL_GLContext& GetGLContext()
    {
        return m_GLContext;
    }

    inline WindowPtr& GetWindow()
    {
        return m_pWindow;
    }

    inline const std::string& GetWindowTitle() const
    {
        return m_sTitle;
    }

    inline const int GetXPos() const
    {
        return m_XPos;
    }

    inline const int GetYPos() const
    {
        return m_YPos;
    }

    inline const int GetWidth() const
    {
        return m_Width;
    }
    inline const int GetHeight() const
    {
        return m_Height;
    }

private:
    void CreateNewWindow( Uint32 flags );

private:
    WindowPtr m_pWindow;
    SDL_GLContext m_GLContext;
    Uint32 m_WindowFlags;
    std::string m_sTitle;
    int m_Width;
    int m_Height;
    int m_XPos;
    int m_YPos;
};
} // namespace Jadeite::Windowing