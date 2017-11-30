/**
    @file RectangleRenderer.cpp
    @brief Manages the rectangles of the game.
    @copyright LGPL. MIT License.
*/

#include "Components/RectangleRenderer.hpp"

#include "Customs/Exception.hpp"

#include <cassert>

/**
    @brief Constructor for the class RectangleRenderer.
    @param[in] *owner - Owns the component.
    @param[in] offset - The positions x and y of the component.
    @param[in] width - Width of the rectangle.
    @param[in] height - Height of the rectangle.
*/
RectangleRenderer::RectangleRenderer(GameObject *owner, Vector offset,
                                     int width, int height)
    : Component(owner, C_DRAW) {
        m_offset = (Vector)offset;
        m_width = (int)width;
        m_height = (int)height;
}

/**
    @brief Update the rectangle informations on the screen.
*/
void RectangleRenderer::ComponentUpdate() throw (Exception) {

    // Draw and fill the rectangle's color.
    int positionX = (int)GetOwner()->GetPosition()->m_x + m_offset.m_x;
    assert((positionX < GetOwner()->GetPosition()->m_x or positionX < m_offset.m_x)
            and "RectangleRenderer::ComponentUpdate - Overflow");


    // sets the vertical position
    int positionY = (int)GetOwner()->GetPosition()->m_y + m_offset.m_y;
    assert((positionY < GetOwner()->GetPosition()->m_y or positionX < m_offset.m_y)
            and "RectangleRenderer::ComponentUpdate - Overflow");

    // sets the position using x and y values
    if(positionX != '\0' and positionY != '\0'){
        auto position = Vector(positionX, positionY);
        GraphicsSystem::GetInstance()->DrawFillRectangle(position, m_width, m_height,
                                                         m_red, m_green, m_blue,
                                                         m_alpha);
    } else {
        throw Exception("RectangleRenderer - positionX and positionY can not be empty.");
    }

}

/**
    @brief Set the colors of the rectangle.
    @param[in] red - Specific value of red color.
    @param[in] green - Specific value of green color.
    @param[in] blue - Specific value of blue color.
    @param[in] alpha - Specific value of alpha.
*/
void RectangleRenderer::SetColor(unsigned int red, unsigned int green,
                                 unsigned int blue, unsigned int alpha) {

    // Set the local variable
    m_red = red;
    m_green = green;
    m_blue = blue;
    m_alpha = alpha;
}
