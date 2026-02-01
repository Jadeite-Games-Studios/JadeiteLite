#include "core/events/event_dispatcher.hpp"

namespace Jadeite::Events
{
EventDispatcher::EventDispatcher()
    : m_pDispatcher{ std::make_shared<entt::dispatcher>() }
{
}

EventDispatcher::~EventDispatcher()
{
}

void EventDispatcher::UpdateAll()
{
    m_pDispatcher->update();
}

void EventDispatcher::ClearQueue()
{
    m_pDispatcher->clear();
}

} // namespace Jadeite::Events