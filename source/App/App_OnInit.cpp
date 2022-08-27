#include <cstdint>
#include <stdexcept>
#include <unordered_map>
#include <utility>

#include <SDL.h>
#include <SDL_video.h>
#include <SDL_events.h>
#include <SDL_joystick.h>

#ifdef HW_RVL
    #include <iostream>
    #include <ogc/consol.h>
    #include <ogc/video_types.h>
	#include <fat.h>
#endif

#include "../../include/App.hpp"
#include "../../include/Surface.hpp"
#include "../../include/players/Player.hpp"
#include "../../include/players/Human.hpp"


/**
 * @brief Handles the initial loading of data
 */
void App::OnInit()
{
    #ifdef HW_RVL
        fatInitDefault();   // SDL-wii needs to initialise libFAT first
    #endif

    uint32_t uiInitFlags = SDL_INIT_EVERYTHING;

    #ifdef SDL_CDROM_DISABLED
        uiInitFlags &= ~SDL_INIT_CDROM; // SDL-wii does not support CDROMs
    #endif

    if(SDL_Init(uiInitFlags) == -1) throw std::runtime_error(SDL_GetError());

    if ((_surfaceDisplay._pSdlSurface = SDL_SetVideoMode(App::SCurWindowWidth, App::SCurWindowHeight,
        16, SDL_HWSURFACE | SDL_DOUBLEBUF)) == nullptr) throw std::runtime_error(SDL_GetError());

    _eventManager.AttachListener(this);

    #ifdef HW_RVL
		// Initialise console
        bool bMustLock = SDL_MUSTLOCK(_surfaceDisplay._pSdlSurface);
        if (bMustLock) SDL_LockSurface(_surfaceDisplay._pSdlSurface);
        CON_Init(_surfaceDisplay._pSdlSurface->pixels, 20, 20, _surfaceDisplay._pSdlSurface->w,
            _surfaceDisplay._pSdlSurface->h, _surfaceDisplay._pSdlSurface->w * VI_DISPLAY_PIX_SZ);
        std::cout << "\x1b[2;0H";
        if (bMustLock) SDL_UnlockSurface(_surfaceDisplay._pSdlSurface);

        // Create the main human player
        _umapPlayers.insert(std::make_pair(Grid::EPlayerMark::GRID_TYPE_RED, new Human()));
	#endif

    SDL_JoystickEventState(SDL_ENABLE);

    // Retrieve resources from the filesystem
    _surfaceStart = Surface("/apps/test/resources/gfx/start.bmp");
    _surfaceGrid = Surface("/apps/test/resources/gfx/grid.bmp");
    _surfaceRed = Surface("/apps/test/resources/gfx/red.bmp");
    _surfaceYellow = Surface("/apps/test/resources/gfx/yellow.bmp");
    _surfaceWinRed = Surface("/apps/test/resources/gfx/winRed.bmp");
    _surfaceWinYellow = Surface("/apps/test/resources/gfx/winYellow.bmp");

    // Take the background out of the marker pictures
    _surfaceRed.Transparent(255, 0, 255);
    _surfaceYellow.Transparent(255, 0, 255);
}
