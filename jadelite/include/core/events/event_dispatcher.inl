#include "event_dispatcher.hpp"

namespace Jadeite::Events
{
template <typename TEventType, auto Func, typename THandlerType>
auto EventDispatcher::AddHandler( THandlerType& handler )
{
    return m_pDispatcher->sink<TEventType>().template connect<Func>( handler );
}

template <typename TEventType, auto Func, typename THandlerType>
void EventDispatcher::RemoveHandler( THandlerType& handler )
{
    m_pDispatcher->sink<TEventType>().template disconnect<Func>( handler );
}

template <typename TEventType>
void EventDispatcher::ClearHandlers()
{
    m_pDispatcher->sink<TEventType>().disconnect();
}

template <typename TEventType>
inline bool EventDispatcher::HasHandlers()
{
    return !m_pDispatcher->sink<TEventType>().empty();
}

template <typename TEventType, auto Func>
void EventDispatcher::AddFreeFunc()
{
    m_pDispatcher->sink<TEventType>().template connect<Func>();
}

template <typename TEventType>
void EventDispatcher::EmitEvent( TEventType& ev )
{
    m_pDispatcher->trigger( ev );
}

template <typename TEventType>
void EventDispatcher::EmitEvent( TEventType&& ev )
{
    m_pDispatcher->trigger( ev );
}

template <typename TEventType>
void EventDispatcher::EnqueueEvent( TEventType& ev )
{
    m_pDispatcher->enqueue<TEventType>( ev );
}

template <typename TEventType>
void EventDispatcher::EnqueueEvent( TEventType&& ev )
{
    m_pDispatcher->enqueue<TEventType>( ev );
}

template <typename TEventType>
void EventDispatcher::UpdateEvent()
{
    m_pDispatcher->update<TEventType>();
}

} // namespace Jadeite::Events