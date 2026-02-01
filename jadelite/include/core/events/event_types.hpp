#pragma once

namespace Jadeite::Events
{
enum class EKeyEventType
{
    Pressed,
    Released,
    NoType
};

struct KeyEvent
{
    int key{ -1 };
    EKeyEventType eType{ EKeyEventType::NoType };
};

struct CloseAppEvent
{

};

// TODO: Add more events

} // namespace Jadeite::Events