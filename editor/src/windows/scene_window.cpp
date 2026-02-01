#include "windows/scene_window.hpp"
#include "gui/imgui_utilities.hpp"
#include "utilities/fonts/IconsFontAwesome5.hpp"

#include "core/events/event_dispatcher.hpp"
#include "core/events/event_types.hpp"

#include "core/ecs/main_registry.hpp"

#include "logger/logger.hpp"

namespace Jadeite
{
SceneWindow::SceneWindow( Core::MainRegistry& mainRegistry )
    : m_MainRegistry{ mainRegistry }
{

}

SceneWindow::~SceneWindow()
{
}

void SceneWindow::Draw()
{
    if ( !ImGui::Begin( ICON_FA_IMAGE " Scene" ) )
    {
        ImGui::End();
        return;
    }

    DrawToolbar();

    if ( ImGui::BeginChild( "##SceneChild", ImVec2{ 0.f, 0.f }, ImGuiChildFlags_None,
                            ImGuiWindowFlags_NoScrollWithMouse ) )
    {
        ImGui::EndChild();
    }

    ImGui::End();
}

void SceneWindow::DrawToolbar()
{

}

} // namespace Jadeite