/**
    @file PlayButtonScript.cpp
    @brief Manages the Play button functions.
    @copyright LGPL. MIT License.
*/

#include "Customs/PlayButtonScript.hpp"
#include "Customs/AudioController.hpp"
#include "Customs/Exception.hpp"

// Library for assets
#include <cassert>

// Constants
const unsigned int grayTone = 160;
const unsigned int whiteTone = 255;

/**
    @brief Constructor of the class PlayButtonScript.
    @param[in] GameObject *owner - Owns the component.
*/
PlayButtonScript::PlayButtonScript(GameObject *owner) : Script(owner) {

}

/**
    @brief Start the Play button.
*/
void PlayButtonScript::Start() {
    INFO("PlayButtonScript - initializing");
    m_interactive_button = (UIButton *)GetOwner()->GetComponent("UIButton");
    INFO("PlayButtonScript - completed");
}

/**
    @brief Update the text, sound and menu of the Play button.
*/
void PlayButtonScript::ComponentUpdate() throw (Exception) {
    // Sound component to updates the sound of the Play Button
    auto soundButton = (UISound *)GetOwner()->GetComponent("UISound");


    // Sound component to turn off the sound of the menu
    auto menuSound = (UISound *)SceneManager::GetInstance()->GetCurrentScene()
                                ->GetGameObject("Music")->GetComponent("UISound");

    // Change sound and scene when mouse is clicked
    if(soundButton != NULL and menuSound != NULL){
        if (m_interactive_button->IsClicked()) {
            soundButton->Play(0, -1);
            menuSound->Stop();
            AudioController::GetInstance()->PlayAudio("mainSound", -1);
            SceneManager::GetInstance()->SetCurrentScene("Gameplay");
        } else {
            // nothing to do.
        }
    } else {
        throw Exception("PlayButtonScript - soundButton and menuSound nust be different of null.");
    }


    // Text component to updates the colors of the Play Button
    auto textButton = (UIText *)GetOwner()->GetComponent("UIText");

    // Verify the variables
    if(textButton != NULL){
        if (m_interactive_button->IsOver()) {
            textButton->SetColor(grayTone, grayTone, grayTone, whiteTone);
        } else {
            textButton->SetColor(whiteTone, whiteTone, whiteTone, whiteTone);
        }
    } else {
        throw Exception("PlayButtonScript - textButton and menuSound nust be different of null.");
    }
    // Set PlayButton color depending if mouse is over the button or not

}
