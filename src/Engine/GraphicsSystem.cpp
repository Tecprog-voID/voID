/**
    @file GraphicsSystem.cpp
    @brief Manage the draw of texts and diferent types of images in the game.
	@copyright MIT License.
*/

#include "Engine/GraphicsSystem.hpp"
#include "Engine/SDLSystem.hpp"
#include "Engine/sdl2include.hpp"
#include "Log/log.hpp"

#include <iostream>

GraphicsSystem *GraphicsSystem::m_instance = 0;

/**
    @brief Constructor of the GraphicsSystem class.
*/
GraphicsSystem::GraphicsSystem() {
    INFO("GraphicsSystem GraphicsSystem() - completed");
}

/**
 @brief Destructor of the GraphicsSystem class.
 */
GraphicsSystem::~GraphicsSystem() {
    m_instance = nullptr;
    INFO("GraphicsSystem ~GraphicsSystem() - completed");
}

/**
 @brief Get a instance of the GraphicsSystem class.
 */
GraphicsSystem *GraphicsSystem::GetInstance() {
    INFO("GraphicsSystem GetInstance() - initializing");
    // Create a new instance if it does't exist.
    if (!m_instance) {
        m_instance = new GraphicsSystem();
    } else {
        // Do nothing.
    }

    return m_instance;
    INFO("GraphicsSystem GetInstance() - completed");
}

/**
 @brief Draw a image in the game.
 */
void GraphicsSystem::Draw(Image *img, Vector *position,
    std::pair<int, int> sizes) {
    INFO("GraphicsSystem Draw() - initializing");
    SDL_Rect dest;
    dest.w = sizes.first;
    dest.h = sizes.second;
    dest.x = position->m_x;
    dest.y = position->m_y;

    int result;
    // Copy a portion of the texture to the current rendering target.
    result = SDL_RenderCopyEx(SDLSystem::GetInstance()->GetRenderer(),
                              img->GetTexture(), img->GetRect(), &dest,
                              img->GetRotationAngle(), img->GetSDLPivot(),
                              img->GetSDLFlip());
    // Check if the SDL_RenderCopyEx returned a error.
    if (result < noErrorReturnValue) {
        // Show a error message.
        ERROR(SDL_GetError());
    } else {
        // Do nothing.
    }
    INFO("GraphicsSystem Draw() - completed");
}

/**
 @brief Draw a frame in the game.
 */
void GraphicsSystem::DrawFrame(Image *img, Frame *frame, Vector *position,
                               int destWidth, int destHeight) {
    INFO("GraphicsSystem DrawFrame() - initializing");
    SDL_Rect dest;
    dest.w = destWidth;
    dest.h = destHeight;
    dest.x = position->m_x;
    dest.y = position->m_y;


    int result;
    // Copy a portion of the texture to the current rendering target.
    result = SDL_RenderCopyEx(SDLSystem::GetInstance()->GetRenderer(),
                              img->GetTexture(), frame->GetRect(), &dest,
                              img->GetRotationAngle(), img->GetSDLPivot(),
                              img->GetSDLFlip());

    // Check if the SDL_RenderCopyEx returned a error.
    if (result < noErrorReturnValue) {
        // Show a error message.
        ERROR(SDL_GetError());
    } else {
        // Do nothing.
    }
    INFO("GraphicsSystem DrawFrame() - completed");
}

/**
    @brief Draw a text in the game.
*/
void GraphicsSystem::DrawText(SDL_Texture *texture, SDL_Rect *destRect) {
    // Copy a portion of the texture to the current rendering target.
    SDL_RenderCopy(SDLSystem::GetInstance()->GetRenderer(), texture, NULL,
    destRect);
    INFO("GraphicsSystem DrawText() - completed");
}

/**
 @brief Draw a point in the game.
 */
void GraphicsSystem::DrawPoint(Vector point) {
    INFO("GraphicsSystem DrawPoint() - initializing");
    // Draw a point on the current rendering target.
    int result = SDL_RenderDrawPoint(SDLSystem::GetInstance()->GetRenderer(),
    point.m_x, point.m_y);

    // Check if the SDL_RenderDrawPoint returned a error.
    if (result < noErrorReturnValue) {
        // Show a error message.
        SDL_ERROR("Drawing point error");
    } else {
        // Do nothing.
    }
    INFO("GraphicsSystem DrawPoint() - completed");
}

/**
    @brief Draw a circle in the game.
*/
void GraphicsSystem::DrawCircle(Vector &center, float radius, Uint8 redValue,
                                Uint8 greenValue, Uint8 blueValue,
                                Uint8 alphaValue) {
    INFO("GraphicsSystem DrawCircle() - initializing");
    // Set the color used for drawing operations.
    SDL_SetRenderDrawColor(SDLSystem::GetInstance()->GetRenderer(), redValue,
                           greenValue, blueValue, alphaValue);
    Vector point;
    // Calculates a circle's perimeter.
    for (int angle = 0; angle < 360; angle++) {
        point.m_x = center.m_x + cos(angle) * radius;
        point.m_y = center.m_y - sin(angle) * radius;

        // Draw a point on the current rendering target.
        int result = SDL_RenderDrawPoint(SDLSystem::GetInstance()->GetRenderer(),
        point.m_x, point.m_y);
        // Check if the SDL_RenderDrawPoint returned a error.
        if (result < noErrorReturnValue) {
            // Show a error message.
            ERROR(SDL_GetError());
        } else {
            // Do nothing.
        }
    }
    INFO("GraphicsSystem DrawCircle() - completed");
}

/**
    @brief Draw and fill a circle in the game.
*/
void GraphicsSystem::DrawFillCircle(Vector &center, float radius,
                                    Uint8 redValue, Uint8 greenValue,
                                    Uint8 blueValue, Uint8 alphaValue) {
    INFO("GraphicsSystem DrawFillCircle() - initializing");
    // Set the color used for drawing operations.
    SDL_SetRenderDrawColor(SDLSystem::GetInstance()->GetRenderer(), redValue,
                           greenValue, blueValue, alphaValue);
    Vector point;

    // Calculates a circle's perimeter.
    for (float angle = 0; angle < 360; angle += 0.01) {
        point.m_x = center.m_x + cos(angle) * radius;
        point.m_y = center.m_y - sin(angle) * radius;

        // Draw a line on the current rendering target.
        int result = SDL_RenderDrawLine(SDLSystem::GetInstance()->GetRenderer(),
        center.m_x, center.m_y, point.m_x,
        point.m_y);

        // Check if the SDL_RenderDrawLine returned a error.
        if (result < noErrorReturnValue) {
            // Show a error message.
            ERROR(SDL_GetError());
        } else {
        // Do nothing.
        }
    }
    INFO("GraphicsSystem DrawFillCircle() - completed");
}

/**
    @brief Draw and fill a rectangle in the game.
*/
void GraphicsSystem::DrawFillRectangle(Vector &position, int width, int height,
                                       Uint8 redValue, Uint8 greenValue,
                                       Uint8 blueValue, Uint8 alphaValue) {
    INFO("GraphicsSystem DrawFillRectangle() - initializing");
    // Set the color used for drawing operations.
    SDL_SetRenderDrawColor(SDLSystem::GetInstance()->GetRenderer(), redValue,
                           greenValue, blueValue, alphaValue);

    // Create a rectangle.
    SDL_Rect rect;
    rect.x = position.m_x;
    rect.y = position.m_y;
    rect.w = width;
    rect.h = height;

    // Fill a rectangle on the current rendering target with the drawing color.
    int result = SDL_RenderFillRect(SDLSystem::GetInstance()->GetRenderer(),
    &rect);

    // Check if the SDL_RenderFillRect returned a error.
    if (result < noErrorReturnValue) {
        // Show a error message.
        ERROR(SDL_GetError());
    } else {
        // Do nothing.
    }
    INFO("GraphicsSystem DrawFillRectangle() - completed");
}

/**
    @brief Draw and fill a rectangle in the game.
*/
void GraphicsSystem::DrawFillRectangle(SDL_Rect* source, int /*width*/, int /*height*/,
                                       Uint8 redValue, Uint8 greenValue,
                                       Uint8 blueValue, Uint8 alphaValue) {
    INFO("GraphicsSystem DrawFillRectangle() - initializing");
    // Set the color used for drawing operations.
    SDL_SetRenderDrawColor(SDLSystem::GetInstance()->GetRenderer(), redValue,
                           greenValue, blueValue, alphaValue);

    // Create a rectangle.
    SDL_Rect rect;
    rect.x = source->x;
    rect.y = source->y;
    rect.w = source->w;
    rect.h = source->h;

    // Fill a rectangle on the current rendering target with the drawing color.
    int result = SDL_RenderFillRect(SDLSystem::GetInstance()->GetRenderer(),
                                    &rect);
    // Check if the SDL_RenderFillRect returned a error.
    if (result < noErrorReturnValue) {
        // Show a error message.
        ERROR(SDL_GetError());
    } else {
        // Do nothing.
    }
    INFO("GraphicsSystem DrawFillRectangle() - completed");
}
