#pragma once
#include <glad/glad.h>

namespace Jadeite::Rendering
{
class Texture
{
public:
    enum class TextureType
    {
        PIXEL = 0,
        BLENDED,
        FRAMEBUFFER,
        ICON,
        NONE
    };

public:
    Texture();
    Texture( GLuint id, int width, int height, TextureType type = TextureType::PIXEL,
             const std::string& texturePath = "" );
    ~Texture() = default;

    inline const int GetWidth() const
    {
        return m_Width;
    }

    inline const int GetHeight() const
    {
        return m_Height;
    }

    inline const GLuint GetID() const
    {
        return m_TextureID;
    }

    inline TextureType GetType() const
    {
        return m_eType;
    }

    inline const std::string& GetPath() const
    {
        return m_sPath;
    }

    void Bind();
    void Unbind();
    void Destroy();

private:
    GLuint m_TextureID;
    std::string m_sPath;
    TextureType m_eType;
    int m_Width;
    int m_Height;
};
} // namespace Jadeite::Rendering