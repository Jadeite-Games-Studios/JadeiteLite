#pragma once
#include "window_interface.hpp"

namespace Jadeite
{

namespace Core
{
class MainRegistry;
}

class MenuWindow : public IDockableWindow
{
public:
    MenuWindow( Core::MainRegistry& mainRegistry );

    virtual ~MenuWindow() = default;
    virtual void Draw() override;

private:
    Core::MainRegistry& m_MainRegistry;
};

} // namespace Jadeite