/**
    @file Frame.cpp
    @brief Manages the frame of the game.
    @copyright LGPL. MIT License.
*/

#include "Engine/Frame.hpp"

#include <cassert>

/**
    @brief Set start coordinates and frame size.
    @param[in] positionX - Horizontal coordinate of the frame.
    @param[in] positionY - Vertical coordinate of the frame.
    @param[in] width - Horizontal frame size
    @param[in] height - Vertical frame size.
*/
Frame::Frame(int positionX, int positionY, int width, int height) {

    assert((positionX >= 0) and "the positionX must be greater than zero");
    assert((positionY >= 0) and "the positionY must be greater than zero");
    assert((width >= 0) and "the width must be greater than zero");
    assert((height >= 0) and "the height must be greater than zero");

    sourceRectangle.x = positionX;
    sourceRectangle.y = positionY;
    sourceRectangle.w = width;
    sourceRectangle.h = height;
}

/**
    @brief Get informations about the frame.
    @return - The rectangular area of the frame
*/
SDL_Rect *Frame::GetRect() {
    return &originOfRectangle;
}
