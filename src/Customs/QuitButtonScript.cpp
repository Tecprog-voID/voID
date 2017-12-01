/**
    @file QuitButtonScript.cpp
    @brief Manages the Quit button functions.
    @copyright LGPL. MIT License.
*/

#include "Customs/QuitButtonScript.hpp"

// include class Exception for appropriate error handling.
#include "Customs/Exception.hpp"

#include "Log/log.hpp"

// Library for asserts.
#include <cassert>

const int grayTone = 160;
const int whiteTone = 255;

/**
    @brief Constructor of the class QuitButtonScript.
    @param[in] GameObject *owner - Owns the component.
*/
QuitButtonScript::QuitButtonScript(GameObject *owner) : Script(owner) {
    assert((owner != NULL) and "the owner must be equal to NULL");
}

/**
    @brief Starts the Quit button.
*/
void QuitButtonScript::Start() {
    INFO("QuitButtonScript - initializing");
    m_interactiveButton = (UIButton *)GetOwner()->GetComponent("UIButton");
    assert((m_interactiveButton != NULL) and "the m_interactive_button must be equal to NULL");
    INFO("QuitButtonScript - completed");
}

/**
    @brief Updates the text and sound of the Quit button.
*/
void QuitButtonScript::ComponentUpdate() {
    // Sound component to play the sound of the Play Button
    auto soundButton = (UISound *)GetOwner()->GetComponent("UISound");
    assert((soundButton != NULL) and "the soundButton must be equal to NULL");

    // Change sound and running status when mouse is clicked
    if (m_interactiveButton->IsClicked()) {
        soundButton->Play(0, -1);
        SDLSystem::GetInstance()->SetRunning(false);
    } else {
        // nothing to do.
    }

    // Text component to set the colors of the Quit Button
    auto textButton = (UIText *)GetOwner()->GetComponent("UIText");
    assert((textButton != NULL) and "the textButton must be equal to NULL");

    // Set QuitButton color depending if mouse is over the button or not
    if (m_interactiveButton->IsOver()) {
        textButton->SetColor(grayTone, grayTone, grayTone, whiteTone);
    } else {
        textButton->SetColor(whiteTone, whiteTone, whiteTone, whiteTone);
    }
}
