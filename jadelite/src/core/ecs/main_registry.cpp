#include "core/ecs/main_registry.hpp"
#include "core/events/event_dispatcher.hpp"

namespace Jadeite
{
namespace Core
{

MainRegistry::MainRegistry()
    : m_pRegistry{ std::make_unique<entt::registry>() }
{
    Initialize();
}

MainRegistry::~MainRegistry()
{
}

Events::EventDispatcher* MainRegistry::GetEventDispatcher()
{
    auto* ppEventDispatcher = m_pRegistry->ctx().find<std::shared_ptr<Events::EventDispatcher>>();
    return ppEventDispatcher ? ( *ppEventDispatcher ).get() : nullptr;
}

void MainRegistry::Initialize()
{
    // Add all necessary items to the context
    m_pRegistry->ctx().emplace<std::shared_ptr<Events::EventDispatcher>>(
        std::make_shared<Events::EventDispatcher>() );
}

} // namespace Core
} // namespace Jadeite