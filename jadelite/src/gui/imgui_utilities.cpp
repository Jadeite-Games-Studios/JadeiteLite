#include "gui/imgui_utilities.hpp"
#include "logger/logger.hpp"

namespace ImGui
{
void InitDefaultStyles()
{
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    // Base dark theme
    colors[ ImGuiCol_Text ] = ImVec4( 0.86f, 0.86f, 0.86f, 1.00f );
    colors[ ImGuiCol_WindowBg ] = ImVec4( 0.13f, 0.14f, 0.17f, 1.00f );
    colors[ ImGuiCol_ChildBg ] = ImVec4( 0.10f, 0.11f, 0.13f, 1.00f );
    colors[ ImGuiCol_PopupBg ] = ImVec4( 0.12f, 0.12f, 0.14f, 1.00f );
    colors[ ImGuiCol_Border ] = ImVec4( 0.43f, 0.43f, 0.50f, 0.50f );
    colors[ ImGuiCol_FrameBg ] = ImVec4( 0.20f, 0.21f, 0.24f, 1.00f );
    colors[ ImGuiCol_FrameBgHovered ] = ImVec4( 0.28f, 0.30f, 0.33f, 1.00f );
    colors[ ImGuiCol_FrameBgActive ] = ImVec4( 0.33f, 0.36f, 0.39f, 1.00f );
    colors[ ImGuiCol_TitleBg ] = ImVec4( 0.10f, 0.11f, 0.13f, 1.00f );
    colors[ ImGuiCol_TitleBgActive ] = ImVec4( 0.12f, 0.14f, 0.16f, 1.00f );
    colors[ ImGuiCol_TitleBgCollapsed ] = ImVec4( 0.08f, 0.09f, 0.10f, 1.00f );
    colors[ ImGuiCol_MenuBarBg ] = ImVec4( 0.14f, 0.14f, 0.17f, 1.00f );
    colors[ ImGuiCol_ScrollbarBg ] = ImVec4( 0.05f, 0.05f, 0.10f, 0.53f );
    colors[ ImGuiCol_ScrollbarGrab ] = ImVec4( 0.21f, 0.22f, 0.23f, 1.00f );
    colors[ ImGuiCol_ScrollbarGrabHovered ] = ImVec4( 0.31f, 0.32f, 0.33f, 1.00f );
    colors[ ImGuiCol_ScrollbarGrabActive ] = ImVec4( 0.41f, 0.43f, 0.44f, 1.00f );
    colors[ ImGuiCol_CheckMark ] = ImVec4( 0.21f, 0.49f, 0.76f, 1.00f );
    colors[ ImGuiCol_SliderGrab ] = ImVec4( 0.21f, 0.49f, 0.76f, 1.00f );
    colors[ ImGuiCol_SliderGrabActive ] = ImVec4( 0.21f, 0.56f, 0.86f, 1.00f );
    colors[ ImGuiCol_Button ] = ImVec4( 0.16f, 0.18f, 0.20f, 1.00f );
    colors[ ImGuiCol_ButtonHovered ] = ImVec4( 0.21f, 0.25f, 0.29f, 1.00f );
    colors[ ImGuiCol_ButtonActive ] = ImVec4( 0.24f, 0.27f, 0.31f, 1.00f );
    colors[ ImGuiCol_Header ] = ImVec4( 0.18f, 0.20f, 0.22f, 1.00f );
    colors[ ImGuiCol_HeaderHovered ] = ImVec4( 0.22f, 0.25f, 0.29f, 1.00f );
    colors[ ImGuiCol_HeaderActive ] = ImVec4( 0.25f, 0.28f, 0.32f, 1.00f );
    colors[ ImGuiCol_Separator ] = ImVec4( 0.28f, 0.28f, 0.28f, 1.00f );
    colors[ ImGuiCol_ResizeGrip ] = ImVec4( 0.21f, 0.49f, 0.76f, 0.25f );
    colors[ ImGuiCol_ResizeGripHovered ] = ImVec4( 0.21f, 0.49f, 0.76f, 0.67f );
    colors[ ImGuiCol_ResizeGripActive ] = ImVec4( 0.21f, 0.49f, 0.76f, 0.95f );
    colors[ ImGuiCol_Tab ] = ImVec4( 0.10f, 0.13f, 0.15f, 1.00f );
    colors[ ImGuiCol_TabHovered ] = ImVec4( 0.21f, 0.49f, 0.76f, 1.00f );
    colors[ ImGuiCol_TabActive ] = ImVec4( 0.16f, 0.30f, 0.48f, 1.00f );
    colors[ ImGuiCol_TabUnfocused ] = ImVec4( 0.12f, 0.12f, 0.13f, 1.0f );
    colors[ ImGuiCol_TabUnfocusedActive ] = ImVec4( 0.18f, 0.18f, 0.20f, 1.0f );

    // Style tweaks
    style.WindowRounding = 5.0f;
    style.FrameRounding = 4.0f;
    style.ScrollbarRounding = 6.0f;
    style.GrabRounding = 3.0f;
    style.TabRounding = 4.0f;

    style.WindowPadding = ImVec2( 10, 10 );
    style.FramePadding = ImVec2( 6, 4 );
    style.ItemSpacing = ImVec2( 6, 6 );
    style.ItemInnerSpacing = ImVec2( 4, 4 );
    style.TouchExtraPadding = ImVec2( 0, 0 );
    style.ScaleAllSizes( 1.f );
}

void AddSpaces( int numSpaces )
{
    JADE_ASSERT( numSpaces > 0 && "Number of spaces must be a positive number!" );
    for ( int i = 0; i < numSpaces; ++i )
    {
        ImGui::Spacing();
    }
}

void InlineLabel( const std::string& label, float spaceSize )
{
    ImGui::Text( label.c_str() );
    ImGui::SameLine();
    ImGui::SetCursorPosX( spaceSize );
}

void ActiveButton( const char* label, ImVec2 size )
{
    ImGui::PushStyleColor( ImGuiCol_Button, BUTTON_HELD );
    ImGui::PushStyleColor( ImGuiCol_ButtonHovered, BUTTON_HELD );
    ImGui::PushStyleColor( ImGuiCol_ButtonActive, BUTTON_HELD );
    ImGui::Button( label, size );
    ImGui::PopStyleColor( 3 );
}

static std::unordered_map<std::string, ImFont*> g_mapImGuiFonts;

ImFont* GetFont( const std::string& sFontName )
{
    auto fontItr = g_mapImGuiFonts.find( sFontName );
    if ( fontItr == g_mapImGuiFonts.end() )
    {
        JADE_ERROR( "Failed to get font [{}] - Does not exist.", sFontName );
        ImFont* pFont = ImGui::GetIO().Fonts->Fonts[ 0 ];
        return pFont;
    }

    return fontItr->second;
}

bool AddFont( const std::string& sFontName, ImFont* pFont, float fontSize )
{
    if ( g_mapImGuiFonts.contains( sFontName ) )
    {
        JADE_ERROR( "Failed to add font [{}] to imgui fonts. Already exists.", sFontName );
        return false;
    }

    if ( !pFont )
    {
        JADE_ERROR( "Failed to add font [{}] to imgui fonts.", sFontName );
        return false;
    }

    return g_mapImGuiFonts.emplace( sFontName, pFont ).second;
}

bool AddFontFromFile( const std::string sFontName, const std::string& sFontFile, float fontSize )
{
    if ( g_mapImGuiFonts.contains( sFontName ) )
    {
        JADE_ERROR( "Failed to add font [{}] to imgui fonts. Already exists.", sFontName );
        return false;
    }

    ImGuiIO& io = ImGui::GetIO();
    ImFont* pFont = io.Fonts->AddFontFromFileTTF( sFontFile.c_str(), fontSize, nullptr,
                                                  io.Fonts->GetGlyphRangesDefault() );

    if ( !pFont )
    {
        JADE_ERROR( "Failed to add font [{}] to imgui fonts.", sFontName );
        return false;
    }

    return g_mapImGuiFonts.emplace( sFontName, pFont ).second;
}

bool AddFontFromMemory( const std::string& sFontName, void* fontData, float dataSize,
                        float fontSize )
{
    if ( g_mapImGuiFonts.contains( sFontName ) )
    {
        JADE_ERROR( "Failed to add font [{}] to imgui fonts. Already exists.", sFontName );
        return false;
    }

    ImGuiIO& io = ImGui::GetIO();
    ImFont* pFont = io.Fonts->AddFontFromMemoryTTF( fontData, dataSize, fontSize, nullptr,
                                                    io.Fonts->GetGlyphRangesDefault() );

    if ( !pFont )
    {
        JADE_ERROR( "Failed to add font [{}] to imgui fonts.", sFontName );
        return false;
    }

    return g_mapImGuiFonts.emplace( sFontName, pFont ).second;
}

} // namespace ImGui