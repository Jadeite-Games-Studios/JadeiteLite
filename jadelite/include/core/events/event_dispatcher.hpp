#pragma once
#include <entt/entt.hpp>

#define ADD_EVENT_HANDLER( pDispatcher, type, func, handler ) \
    pDispatcher->AddHandler<type, func>( handler )


namespace Jadeite::Events
{
/*
 * EventDispatcher
 * Simple wrapper around entt::dispatcher.
 * Not all functionality has been wrapped, only what is currently used.
 * May add more to this later as needed.
 */
class EventDispatcher
{
public:
    EventDispatcher();
    ~EventDispatcher();

    /*
     * @brief Add an event handler with specified function.
     * The function must take in the event type as an argument.
     * @tparam TEventType - The type of event.
     * @tparam Func - Function to be used.
     * @tparam THandlerType - The actual handler object passed in.
     * @param A valid handler object for the function provided.
     */
    template <typename TEventType, auto Func, typename THandlerType>
    auto AddHandler( THandlerType& handler );

    /*
     * @brief Remove an event handler with specified function.
     * The function must take in the event type as an argument.
     * @tparam TEventType - The type of event.
     * @tparam Func - Function to be used.
     * @tparam THandlerType - The actual handler object passed in.
     * @param A valid handler object to be removed.
     */
    template <typename TEventType, auto Func, typename THandlerType>
    void RemoveHandler( THandlerType& handler );

    /*
     * @brief Clear all handlers of specified event type.
     * @tparam The type of event to clear handlers.
     */
    template <typename TEventType>
    void ClearHandlers();

    /*
     * @brief Checks to see if there are any handlers of the type connected.
     * @tparam The type of event to check for handlers.
     * @return Returns true if there are at least one handler, false otherwise.
     */
    template <typename TEventType>
    bool HasHandlers();

    /*
     * @brief Add free function to receive events.
     * The function must take in the event type as an argument.
     * @tparam TEventType - The type of event.
     * @tparam Func - Function to be used.
     */
    template <typename TEventType, auto Func>
    void AddFreeFunc();

    template <typename TEventType>
    void EmitEvent( TEventType& ev );

    template <typename TEventType>
    void EmitEvent( TEventType&& ev );

    template <typename TEventType>
    void EnqueueEvent( TEventType& ev );

    template <typename TEventType>
    void EnqueueEvent( TEventType&& ev );

    /*
     * @brief Update or deliver all pending events of a given queue.
     * @tparam TEventType The type of event to update/send.
     */
    template <typename TEventType>
    void UpdateEvent();

    /*
     * @brief Update or deliver all pending events that have been queued.
     */
    void UpdateAll();

    /*
     * @brief Clears all events that have been queued.
     */
    void ClearQueue();

private:
    std::shared_ptr<entt::dispatcher> m_pDispatcher;
};
} // namespace Jadeite::Events

#include "event_dispatcher.inl"