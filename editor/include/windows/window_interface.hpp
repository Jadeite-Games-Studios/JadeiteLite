#pragma once

namespace Jadeite
{
class IDockableWindow
{
public:
    virtual ~IDockableWindow() = default;
    virtual void Draw() = 0;
    virtual void Update()
    {
    }

protected:
    virtual void DrawToolbar()
    {
    }
};

struct DockableWindowHolder
{
    std::vector<std::unique_ptr<IDockableWindow>> windows;
};

using SharedDockableWindowHolder = std::shared_ptr<DockableWindowHolder>;

} // namespace Jadeite