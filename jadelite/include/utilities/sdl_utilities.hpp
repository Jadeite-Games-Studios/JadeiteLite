#pragma once
#include <SDL.h>

namespace Jadeite::Utilities
{
struct SDL_Destroyer
{
    void operator()( SDL_Window* window ) const;
    // TODO: Add other wrappers as needed
};

} // namespace Jadeite::Utilities

// Useful Aliases
using WindowPtr = std::unique_ptr<SDL_Window, Jadeite::Utilities::SDL_Destroyer>;
