/**
    @file UIText.cpp
    @brief Methods that sets UI messages, its positions and colors.
    @copyright LGPL. MIT License.
*/

#include "Components/UIText.hpp"

#include "Log/log.hpp"

#include <cassert>


/**
    @brief Initializes UIText instance.
    @param[in] GameObject *owner - owns the component.
    @param[in] C_DRAW - physics component.
    @param[in] message - A string of the message that will be displayed.
    @param[in] fontPath - The path of the font that will be used.
    @param[in] size - The size of the character's sequence of the message.
    @param[in] red - The red component of the pixel in the range 0-255, type unsigned 8-bit integer.
    @param[in] green - The green component of the pixel in the range 0-255, type unsigned 8-bit integer.
    @param[in] blue - The blue component of the pixel in the range 0-255, type unsigned 8-bit integer.
    @param[in] alpha - The alpha component of the pixel in the range 0-255, type unsigned 8-bit integer.
    @param[in] mode - The surface mode.
*/
UIText::UIText(GameObject *owner, string message, string fontPath, int size,
               Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha, Uint8 mode)
    : Component(owner, C_DRAW) {
    m_message = message;

    // Sets the x, y, width and height positions in a rectangle with the origin at the upper left.
    m_rect.x = owner->GetPosition()->m_x;
    m_rect.y = owner->GetPosition()->m_y;
    m_rect.w = owner->GetWidth();
    m_rect.h = owner->GetHeight();

    /*
        Sets the font based on a font file and create a font of the specified point size.
        Sets its color and background color.
    */
    m_font = TTF_OpenFont(fontPath.c_str(), size);

    // Check if there is something diferent of the font and if is diferent print a error message.
    assert((m_font != nullptr) and "m_font cant be null");

    m_color = {red, green, blue, alpha};

    m_background = {0, 0, 0, 0};

    m_mode = mode;

    OnPropertyChange();
}


void UIText::Start() {
    INFO("UIText - start");
}

/**
    @brief Sets the UIText offset. Offset is the mean value of a wave,
    that creates periodic effect.
    @param[in] offset vector reference.
*/
void UIText::SetOffset(Vector &offset){
    INFO("UIText - set the offset");
    m_offset = offset;
}


/**
    @brief Updates the position of the component that holds the text.
*/
void UIText::ComponentUpdate() {
    INFO("UIText - update the component");

    /*
        Sets the x, y, width and height positions of the rectangle component.
        Positions x and y are updated with the offset values.
        The new positions are used with the texture value to render the draw.
    */
    m_rect.x = GetOwner()->GetPosition()->m_x + m_offset.m_x;
    m_rect.y = GetOwner()->GetPosition()->m_y + m_offset.m_y;
    m_rect.w = GetOwner()->GetWidth();
    m_rect.h = GetOwner()->GetHeight();

    GraphicsSystem::GetInstance()->DrawText(m_texture, &m_rect);
}


/**
    @brief Updates the position of a fixed component.
*/
void UIText::FixedComponentUpdate() {
    INFO("UIText - Fix the component update");
}


/**
    @brief Sets the type of the surface of the UIText, and creates a texture from it.
*/
void UIText::OnPropertyChange() {
    INFO("On property Change");
    m_surface = nullptr;

    // Sets the surface type based on the mode, to render the appropriated texture.
    switch (m_mode) {
    case 0:
        m_surface = TTF_RenderText_Solid(m_font, m_message.c_str(), m_color);
        break;
    case 1:
        m_surface = TTF_RenderText_Blended(m_font, m_message.c_str(), m_color);
        break;
    case 2:
        m_surface =
              TTF_RenderText_Shaded(m_font, m_message.c_str(), m_color, m_background);
  }

    m_texture = SDL_CreateTextureFromSurface(
        SDLSystem::GetInstance()->GetRenderer(), m_surface);

    SDL_FreeSurface(m_surface);
}


/**
    @brief Sets the text of the message that will be displayed.
    @param[in] text - A string of the message.
*/
void UIText::SetText(string text) {
    INFO("UIText - set the text");
    m_message = text;
    OnPropertyChange();
}


/**
    @brief Sets the color of the text.
    @param[in] red - The red component of the pixel in the range 0-255, type unsigned 8-bit integer.
    @param[in] green- The green component of the pixel in the range 0-255, type unsigned 8-bit integer.
    @param[in] blue - The blue component of the pixel in the range 0-255, type unsigned 8-bit integer.
    @param[in] alpha - The alpha component of the pixel in the range 0-255, type unsigned 8-bit integer.

*/
void UIText::SetColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha) {
    INFO("UIText - set the color");
    m_color = {red, green, blue, alpha};
    OnPropertyChange();
}
