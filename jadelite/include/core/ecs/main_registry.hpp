#pragma once
#include <entt/entt.hpp>

namespace Jadeite
{

namespace Events
{
class EventDispatcher;
}

namespace Core
{
class MainRegistry
{
public:
    MainRegistry();
    ~MainRegistry();

    Events::EventDispatcher* GetEventDispatcher();

private:
    void Initialize();

private:
    std::unique_ptr<entt::registry> m_pRegistry;
};

} // namespace Core
} // namespace Jadeite
