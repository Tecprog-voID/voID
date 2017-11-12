#include "Engine/GameObject.hpp"
#include "Engine/SDLSystem.hpp"

#include "Components/UIButton.hpp"
#include "Globals/ComponentTypes.hpp"
#include "Globals/InputGlobals.hpp"
#include "Log/log.hpp"

/**
    @file UIButton.cpp
    @brief Methods that manages all game's buttons as 'quit' and 'start'.
    @copyright LGPL. MIT License.
*/

UIButton::UIButton(GameObject *owner) : Component(owner, C_DRAW) {}

/**
    @brief Creates a button.
*/
void UIButton::Start() {
    INFO("UIButton - initializing");

    // Case exists
    m_position = GetOwner()->GetPosition();

    INFO("UIButton - initialized");
}

/**
    @brief Checking if mouse is over button and clicked.
    @return Boolean.
*/
bool UIButton::IsClicked() {
    INFO("UIButton - checking if the button is clicked");
    if (IsOver() && InputSystem::GetInstance()->GetMouseButtonDown(M_INPUT_LEFT)) {
        INFO("UIButton - the button is clicked");
        return true;
    } else {
        // Do nothing
    }

    INFO("UIButton - the button is not clicked");
    return false;
  }

/**
    @brief Gets button and mouse positions, and check if mouse is still there.
    @return Boolean.
*/
bool UIButton::IsOver() {
    INFO("UIButton - getting the mouse position");
    // Getting button and mouse position
    m_position = GetOwner()->GetPosition();

    // responsible for rendering width
    int rendererWidth = GetOwner()->GetWidth();

    // responsible for rendering height
    int rendererHeight = GetOwner()->GetHeight();

    // sets mouse's position
    std::pair<int, int> mousePos = InputSystem::GetInstance()->GetMousePosition();

    INFO("UIButton - checking if the mouse is over");
    // Checking if mouse is over
    if (mousePos.first > m_position->m_x &&
        mousePos.first < m_position->m_x + rendererWidth &&
        mousePos.second > m_position->m_y &&
        mousePos.second < m_position->m_y + rendererHeight) {
            INFO("UIButton - mouse is over");
            return true;
    } else {
        // Do nothing
    }

    INFO("UIButton - mouse is not over");
    return false;
}
