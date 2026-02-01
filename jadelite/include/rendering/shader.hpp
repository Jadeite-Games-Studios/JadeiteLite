#pragma once
#include <glm/glm.hpp>
#include <glad/glad.h>

namespace Jadeite::Rendering
{
class Shader
{
public:
    Shader();
    Shader( GLuint program, const std::string vertexPath, const std::string& fragmentPath );
    ~Shader();

    void SetUniformInt( const std::string& name, int value );
    void SetUniformFloat( const std::string& name, float value );

    void SetUniformVec2( const std::string& name, float x, float y );
    void SetUniformVec2( const std::string& name, const glm::vec2& value );

    void SetUniformVec3( const std::string& name, float x, float y, float z );
    void SetUniformVec3( const std::string& name, const glm::vec3& value );

    void SetUniformVec4( const std::string& name, float x, float y, float z, float w );
    void SetUniformVec4( const std::string& name, const glm::vec4& value );

    void SetUniformMat2( const std::string& name, const glm::mat2& mat );
    void SetUniformMat3( const std::string& name, const glm::mat3& mat );
    void SetUniformMat4( const std::string& name, const glm::mat4& mat );

    void Enable() const;
    void Disable() const;

    inline const GLuint ShaderProgramID() const
    {
        return m_ShaderProgramID;
    }

    inline const std::string& GetVertPath() const
    {
        return m_sVertexPath;
    }

    inline const std::string& GetFragPath() const
    {
        return m_sFragmentPath;
    }

private:
    GLuint GetUniformLocation( const std::string& uniformName );

private:
    GLuint m_ShaderProgramID;
    std::string m_sVertexPath;
    std::string m_sFragmentPath;

    std::unordered_map<std::string, GLuint> m_UniformLocationMap;
};
} // namespace Jadeite::Rendering
