#pragma once
#include <imgui.h>

constexpr ImVec4 BUTTON_HELD = ImVec4{ 0.f, 0.9f, 0.f, 0.3f };

namespace ImGui
{
/**
 * @brief Initializes a dark-themed default style for ImGui.
 *
 * Sets base colors, rounding, padding, spacing, and scaling for the ImGui interface.
 */
void InitDefaultStyles();

void AddSpaces( int numSpaces );
void InlineLabel( const std::string& label, float spaceSize = 156.f );

void ActiveButton( const char* label, ImVec2 size = ImVec2{ 32.f, 32.f } );

ImFont* GetFont( const std::string& sFontName );
bool AddFont( const std::string& sFontName, ImFont* pFont, float fontSize );
bool AddFontFromFile( const std::string sFontName, const std::string& sFontFile, float fontSize );
bool AddFontFromMemory( const std::string& sFontName, void* fontData, float dataSize,
                        float fontSize );
} // namespace ImGui