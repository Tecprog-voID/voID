/**
    @file CatchAllButtonScript.cpp
    @brief Manages the Catch All button functions.
    @copyright LGPL. MIT License.
*/

#include "Customs/CatchAllButtonScript.hpp"

// include class Exception for appropriate error handling.
#include "Customs/Exception.hpp"

// Library for asserts.
#include <cassert>

const unsigned int gameMode = 0x02;

/**
    @brief Constructor of the class CatchAllButtonScript.
    @param[in] GameObject *owner - Owns the component.
*/
CatchAllButtonScript::CatchAllButtonScript(GameObject *owner) : Script(owner) {
    assert((owner != NULL) and "the owner must be equal to NULL");
}

/**
    @brief Start the Catch All button.
*/
void CatchAllButtonScript::Start() throw (Exception) {
    INFO("CatchAllButtonScript - initializing");
    m_interactiveButton = (UIButton *)GetOwner()->GetComponent("UIButton");
    m_checkbox = (GameObject *)SceneManager::GetInstance()->GetScene("Main")->GetGameObject(
                 "CatchAll_CB");
    if(m_interactiveButton != NULL and m_checkbox != NULL) {
        INFO("CatchAllButtonScript - completed");
    } else {
        throw Exception("CatchAllButtonScript - Initim_interactive_button and m_checkbox must be different of null.");
    }

}

/**
    @brief Update the Quit button informations.
*/
void CatchAllButtonScript::ComponentUpdate() {

    // Select game mode when mouse is clicked
    if (m_interactiveButton->IsClicked()) {
        MenuController::GetInstance()->SelectGamemode(gameMode);
    } else {
        // nothing to do.
    }

    // Change checkbox value comparing the selected game mode
    if (MenuController::GetInstance()->GetGamemode() & gameMode) {
        m_checkbox->active = true;
    } else {
        m_checkbox->active = false;
    }
}
