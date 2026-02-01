#pragma once
#include <glm/glm.hpp>

namespace Jadeite::Rendering
{
struct Color
{
    std::uint8_t r{ 255 };
    std::uint8_t g{ 255 };
    std::uint8_t b{ 255 };
    std::uint8_t a{ 255 };
};

struct Vertex
{
    glm::vec2 position{ 0.f };
    glm::vec2 uvs{ 0.f };
    Color color{ .r = 255, .g = 255, .b = 255, .a = 255 };

    void set_color( std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a )
    {
        color.r = r;
        color.g = g;
        color.b = b;
        color.a = a;
    }

    void set_color( std::uint32_t newColor )
    {
        color.r = ( newColor >> 24 ) & 0xFF;
        color.g = ( newColor >> 16 ) & 0xFF;
        color.b = ( newColor >> 8 ) & 0xFF;
        color.a = ( newColor >> 0 ) & 0xFF;
    }
};
} // namespace Jadeite::Rendering