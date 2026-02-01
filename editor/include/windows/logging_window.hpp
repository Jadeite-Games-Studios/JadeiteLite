#pragma once
#include "window_interface.hpp"
#include <imgui.h>

namespace Jadeite
{

class LogWindow : public IDockableWindow
{
public:
    LogWindow( );
    ~LogWindow() = default;

    void Clear();
    virtual void Draw() override;

protected:
    virtual void DrawToolbar() override;

private:
    void GetLogs();

private:
    ImGuiTextBuffer m_TextBuffer;
    ImVector<int> m_TextOffsets;
    std::string m_sSearchQuery;
    bool m_bAutoScroll;
    bool m_bShowInfo;
    bool m_bShowWarn;
    bool m_bShowError;
    int m_LogIndex;
};

} // namespace Jadeite