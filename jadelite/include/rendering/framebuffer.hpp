#pragma once
#include <glad/glad.h>

namespace Jadeite::Rendering
{
class Texture;

class Framebuffer
{
public:
    Framebuffer();
    Framebuffer( int width, int height, bool bUseRbo );
    ~Framebuffer();

    void Bind();
    void Unbind();

    // Resizing
    void Resize( int width, int height );
    void CheckResize();
    const GLuint GetTextureID() const;
    const bool IsActive() const;

    inline const GLuint GetID() const
    {
        return m_FboID;
    }

    inline const int Width() const
    {
        return m_Width;
    }

    inline const int Height() const
    {
        return m_Height;
    }

private:
    bool Initialize();
    void CleanUp();

private:
    GLuint m_FboID;
    GLuint m_RboID;
    std::shared_ptr<Texture> m_pTexture;
    int m_Width;
    int m_Height;
    bool m_bShouldResize;
    bool m_bUseRbo;
};

} // namespace Jadeite::Rendering