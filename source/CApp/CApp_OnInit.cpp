#include <cstdint>
#include <stdexcept>
#include <ios>

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

#include "../../include/CApp.hpp"
#include "../../include/CSurface.hpp"
#include "../../include/players/Human.hpp"


/**
 * @brief Handles the initial loading of data
 */
void CApp::OnInit()
{
    uint32_t uiInitFlags = SDL_INIT_EVERYTHING;

    #ifdef SDL_CDROM_DISABLED
        uiInitFlags &= ~SDL_INIT_CDROM; // SDL-wii does not support CDROMs
    #endif

    if(SDL_Init(uiInitFlags) == -1) throw std::runtime_error(SDL_GetError());

    if ((_pSdlSurfaceDisplay = SDL_SetVideoMode(CApp::SCurWindowWidth, CApp::SCurWindowHeight, 16,
        SDL_HWSURFACE | SDL_DOUBLEBUF)) == nullptr) throw std::runtime_error(SDL_GetError());

    #ifdef HW_RVL
		fatInitDefault();   // SDL-wii needs to initialise libFAT first

        // Initialise console
        if (SDL_MUSTLOCK(_pSdlSurfaceDisplay)) SDL_LockSurface(_pSdlSurfaceDisplay);
        CON_Init(_pSdlSurfaceDisplay->pixels, 20, 20, _pSdlSurfaceDisplay->w, _pSdlSurfaceDisplay->h, 
        _pSdlSurfaceDisplay->w * VI_DISPLAY_PIX_SZ);
        std::cout << "\x1b[2;0H";
        if (SDL_MUSTLOCK(_pSdlSurfaceDisplay)) SDL_UnlockSurface(_pSdlSurfaceDisplay);
	#endif

    _apPlayer.push_back(new Human());   // Create the main human player
    SDL_JoystickEventState(SDL_ENABLE);

    // Retrieve resources from the filesystem
    try
    {
        _pSdlSurfaceStart = CSurface::OnLoad("/apps/test/resources/gfx/start.bmp");
        _pSdlSurfaceGrid = CSurface::OnLoad("/apps/test/resources/gfx/grid.bmp");
        _pSdlSurfaceRed = CSurface::OnLoad("/apps/test/resources/gfx/red.bmp");
        _pSdlSurfaceYellow = CSurface::OnLoad("/apps/test/resources/gfx/yellow.bmp");
        _pSdlSurfaceWinRed = CSurface::OnLoad("/apps/test/resources/gfx/winRed.bmp");
        _pSdlSurfaceWinYellow = CSurface::OnLoad("/apps/test/resources/gfx/winYellow.bmp");
    }
    catch (const std::ios_base::failure& Ciof) { throw; }

    // Take the background out of the marker pictures
    CSurface::Transparent(_pSdlSurfaceRed, 255, 0, 255);
    CSurface::Transparent(_pSdlSurfaceYellow, 255, 0, 255);

	/*SDL_WM_SetCaption("Joytest", nullptr);
    SDL_ShowCursor(SDL_DISABLE);

    // Make sure SDL cleans up before exit
    atexit(Cleanup);*/
}
