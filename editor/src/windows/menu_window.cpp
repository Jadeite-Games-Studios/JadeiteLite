#include "windows/menu_window.hpp"

#include "gui/imgui_utilities.hpp"
#include "utilities/fonts/IconsFontAwesome5.hpp"

#include "core/events/event_dispatcher.hpp"
#include "core/events/event_types.hpp"

#include "core/ecs/main_registry.hpp"

#include "logger/logger.hpp"

#include <ImGuiFileDialog.h>

namespace Jadeite
{
MenuWindow::MenuWindow( Core::MainRegistry& mainRegistry )
    : m_MainRegistry{ mainRegistry }
{

}

void MenuWindow::Draw()
{
    if ( ImGui::BeginMainMenuBar() )
    {
        if ( ImGui::BeginMenu( ICON_FA_FILE " File" ) )
        {
            ImGui::SeparatorText( "Project" );
            ImGui::InlineLabel( ICON_FA_FILE_ALT, 32.f );
            if ( ImGui::MenuItem( "New", "Ctrl + N" ) )
            {
                JADE_ERROR( "New -- Not Implemented" );
            }

            ImGui::InlineLabel( ICON_FA_FOLDER_OPEN, 32.f );
            if ( ImGui::MenuItem( "Open", "Ctrl + O" ) )
            {
                //JADE_ERROR( "Open -- Not Implemented" );
                ImGuiIO& io = ImGui::GetIO();
                IGFD::FileDialogConfig config;
                config.path = ".";
                config.countSelectionMax = 1;
                config.flags = ImGuiFileDialogFlags_Modal;
                ImGui::SetNextWindowPos( ImVec2( io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f ),
                                         ImGuiCond_Always, ImVec2( 0.5f, 0.5f ) );
                ImGuiFileDialog::Instance()->OpenDialog( "OpenFileExample", "Select File",
                                                         ".cpp,.h,.hpp", config );
            }
            ImGui::InlineLabel( ICON_FA_SAVE, 32.f );
            if ( ImGui::MenuItem( "Save All", "Ctrl + S" ) )
            {
                JADE_ERROR( "Save All -- Not Implemented" );
            }

            ImGui::SeparatorText( "Exit" );
            ImGui::InlineLabel( ICON_FA_WINDOW_CLOSE, 32.f );
            if ( ImGui::MenuItem( "Exit" ) )
            {
                m_MainRegistry.GetEventDispatcher()->EmitEvent( Events::CloseAppEvent{} );
            }

            ImGui::EndMenu();
        }

        if ( ImGui::BeginMenu( ICON_FA_EDIT " Edit" ) )
        {
            ImGui::EndMenu();
        }

        if ( ImGui::BeginMenu( ICON_FA_WINDOW_MAXIMIZE " Panels" ) )
        {
            ImGui::EndMenu();
        }

        if ( ImGui::BeginMenu( ICON_FA_QUESTION_CIRCLE " Help" ) )
        {
            if ( ImGui::TreeNode( "About Jadeite Lite" ) )
            {
                ImGui::Separator();
                ImGui::Text(
                    "Jadeite Lite is a simple SDL2 and ImGui application written in C++." );
                ImGui::Text(
                    "The goal of this is to handle basic boiler plater code for applications to "
                    "expand as needed to teach new topics and learn more about C++ "
                    "Programming." );
                ImGui::Text( "By Dustin Clark and all contributors." );
                ImGui::AddSpaces( 2 );

                ImGui::SeparatorText( "Helpful Links: " );
                ImGui::TextLinkOpenURL( "Github", "TODO: Provide Link" );
                ImGui::TextLinkOpenURL( "YouTube", "https://www.youtube.com/@JADE-iteGames" );
                ImGui::Separator();
                ImGui::TreePop();
            }
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }

    if ( ImGuiFileDialog::Instance()->Display( "OpenFileExample" ) )
    {
        if ( ImGuiFileDialog::Instance()->IsOk() )
        {
            std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
            JADE_LOG( "Open File: {}", filePathName );
        }

        ImGuiFileDialog::Instance()->Close();
    }
}

} // namespace Jadeite