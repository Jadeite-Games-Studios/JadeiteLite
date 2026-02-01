#pragma once
#include "window_interface.hpp"

namespace Jadeite
{

namespace Core
{
class MainRegistry;
}

class SceneWindow : public IDockableWindow
{
public:
    SceneWindow( Core::MainRegistry& mainRegistry );

    virtual ~SceneWindow();
    virtual void Draw() override;

protected:
    virtual void DrawToolbar() override;

private:
    Core::MainRegistry& m_MainRegistry;
};

} // namespace Jadeite