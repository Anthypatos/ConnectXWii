/*
EventListener.hpp --- App events listener
Copyright (C) 2022  Juan de la Cruz Caravaca Guerrero (Quadraxis_v2)
juan.dlcruzcg@gmail.com

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as published
by the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef _EVENTLISTENER_HPP_
#define _EVENTLISTENER_HPP_


#include <cstdint>
#include <SDL_events.h>
#include <SDL_keysym.h>


/**
 * @brief Event Listener abstract class
 * @details Classes that wish to receive events should inherit this class and register to the event manager
 */
class EventListener
{
public:
    virtual ~EventListener() = default; /**< Destructor */

    /**
     * @brief Handles events where the mouse enters the application window
     */
    virtual void OnMouseFocus() = 0;

    /**
     * @brief Handles events where the mouse exits the application window
     */
    virtual void OnMouseBlur() = 0;

    /**
     * @brief Handles events where the application gains keyboard focus
     */
    virtual void OnInputFocus() = 0;

    /**
     * @brief Handles events where the application loses keyboard focus
     */
    virtual void OnInputBlur() = 0;

    /**
     * @brief Handles events where the window is restored to its size
     */
    virtual void OnRestore() = 0;

    /**
     * @brief Handles events where the window is minimized
     */
    virtual void OnMinimize() = 0;

    /**
     * @brief Handles keyboard press events
     * 
     * @param sdlKeySymbol the key that was pressed
     * @param sdlMod the current state of keyboard modifiers
     * @param urUnicode the Unicode value of the pressed key
     */
    virtual void OnKeyDown(SDLKey sdlKeySymbol, SDLMod sdlMod, uint16_t urUnicode) = 0;

    /**
     * @brief Handles keyboard release events
     * 
     * @param sdlKeySymbol the key that was released
     * @param sdlMod the current state of keyboard modifiers
     * @param urUnicode the Unicode value of the released key
     */
    virtual void OnKeyUp(SDLKey sdlKeySymbol, SDLMod sdlMod, uint16_t urUnicode) = 0;

    /**
     * @brief Handles mouse/IR movement events
     * 
     * @param urMouseX the X coordinate of the mouse
     * @param urMouseY the Y coordinate of the mouse
     * @param rRelX the relative motion in the X direction
     * @param rRelY the relative motion in the Y direction
     * @param bLeft the current state of the left mouse button
     * @param bRight the current state of the right mouse button
     * @param bMiddle the current state of the middle mouse button
     */
    virtual void OnMouseMove(uint16_t urMouseX, uint16_t urMouseY, int16_t rRelX, int16_t rRelY,
        bool bLeft, bool bRight, bool bMiddle) = 0;

    /**
     * @brief Handles mouse wheel movement events
     * 
     * @param bUp true if the mouse wheel is moving upwards
     * @param bDown true if the mouse wheel is moving downwards
     */
    virtual void OnMouseWheel(bool bUp, bool bDown) = 0;

    /**
     * @brief Handles mouse left button press events
     * 
     * @param urMouseX the X coordinate of the mouse
     * @param urMouseY the Y coordinate of the mouse
     */
    virtual void OnLButtonDown(uint16_t urMouseX, uint16_t urMouseY) = 0;

    /**
     * @brief Handles mouse right button press events
     * 
     * @param urMouseX the X coordinate of the mouse
     * @param urMouseY the Y coordinate of the mouse
     */
    virtual void OnRButtonDown(uint16_t urMouseX, uint16_t urMouseY) = 0;

    /**
     * @brief Handles mouse middle button press events
     * 
     * @param urMouseX the X coordinate of the mouse
     * @param urMouseY the Y coordinate of the mouse
     */
    virtual void OnMButtonDown(uint16_t urMouseX, uint16_t urMouseY) = 0;

    /**
     * @brief Handles mouse left button release events
     * 
     * @param urMouseX the X coordinate of the mouse
     * @param urMouseY the Y coordinate of the mouse
     */
    virtual void OnLButtonUp(uint16_t urMouseX, uint16_t urMouseY) = 0;

    /**
     * @brief Handles mouse right button release events
     * 
     * @param urMouseX the X coordinate of the mouse
     * @param urMouseY the Y coordinate of the mouse
     */
    virtual void OnRButtonUp(uint16_t urMouseX, uint16_t urMouseY) = 0;

    /**
     * @brief Handles mouse middle button release events
     * 
     * @param urMouseX the X coordinate of the mouse
     * @param urMouseY the Y coordinate of the mouse
     */
    virtual void OnMButtonUp(uint16_t urMouseX, uint16_t urMouseY) = 0;

    /**
     * @brief Handles joystick axis events
     * 
     * @param uyWhich the joystick device index
     * @param uyAxis the joystick axis index
     * @param rValue the axis value
     */
    virtual void OnJoyAxis(uint8_t uyWhich, uint8_t uyAxis, int16_t rValue) = 0;

    /**
     * @brief Handles joystick trackball motion events
     * 
     * @param uyWhich the joystick device index
     * @param uyBall the joystick ball index
     * @param rRelativeX the relative motion in the X direction
     * @param rRelativeY the relative motion in the Y direction
     */
    virtual void OnJoyBall(uint8_t uyWhich, uint8_t uyBall, int16_t rRelativeX, int16_t rRelativeY) = 0;

    /**
     * @brief Handles joystick button press events
     * 
     * @param uyWhich the joystick device index
     * @param uyButton the joystick button index
     */
    virtual void OnJoyButtonDown(uint8_t uyWhich, uint8_t uyButton) = 0;

    /**
     * @brief Handles joystick button release events
     * 
     * @param uyWhich the joystick device index
     * @param uyButton the joystick button index
     */
    virtual void OnJoyButtonUp(uint8_t uyWhich, uint8_t uyButton) = 0;

    /**
     * @brief Handles joystick hat position events
     * 
     * @param uyWhich the joystick device index
     * @param uyHat the joystick hat index
     * @param uyValue the hat value
     */
    virtual void OnJoyHat(uint8_t uyWhich, uint8_t uyHat, uint8_t uyValue) = 0;

    /**
     * @brief Handles user-requested quits
     */
    virtual void OnExit() = 0;

    /**
     * @brief Handles window resize events
     * 
     * @param iWidth the new width of the window
     * @param iHeight the new height of the window
     */
    virtual void OnResize(int32_t iWidth, int32_t iHeight) = 0;

    /**
     * @brief Handles window redraw events
     */
    virtual void OnExpose() = 0;

    /**
     * @brief Handles user-defined events
     * 
     * @param uyType a user-defined event type
     * @param iCode a user-defined event code
     * @param pData1 a user-defined data pointer
     * @param pData2 a user-defined data pointer
     */
    virtual void OnUser(uint8_t uyType, int32_t iCode, void* pData1, void* pData2) = 0;

};


#endif
