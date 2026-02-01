#include "utilities/sdl_utilities.hpp"
#include "logger/logger.hpp"

namespace Jadeite::Utilities
{
void SDL_Destroyer::operator()( SDL_Window* window ) const
{
    SDL_DestroyWindow( window );
    JADE_LOG( "Destroyed SDL WINDOW" );
}
} // namespace Jadeite::Utilities