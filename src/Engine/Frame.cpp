/**
    @file Frame.cpp
    @brief Manages the frame of the game.
    @copyright LGPL. MIT License.
*/

#include "Engine/Frame.hpp"

#include "Customs/Exception.hpp"

#include <cassert>

/**
    @brief Set start coordinates and frame size.
    @param[in] positionX - Horizontal coordinate of the frame.
    @param[in] positionY - Vertical coordinate of the frame.
    @param[in] width - Horizontal frame size
    @param[in] height - Vertical frame size.
*/
Frame::Frame(unsigned int positionX, unsigned int positionY,
             unsigned int width, unsigned int height) {

/* Comparison of unsigned expression> = 0 is always true,
    with the use of assertions unnecessary here. */

    // Assignment of Values
    originOfRectangle.x = positionX;
    originOfRectangle.y = positionY;
    originOfRectangle.w = width;
    originOfRectangle.h = height;
}

/**
    @brief Get informations about the frame.
    @return - The rectangular area of the frame
*/
SDL_Rect *Frame::GetRect() {
    return &originOfRectangle;
    assert((&originOfRectangle != NULL) and "the return must be different to NULL");
}
