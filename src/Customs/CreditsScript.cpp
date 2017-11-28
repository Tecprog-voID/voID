/**
    @file CreditsScript.cpp
    @brief Manages the credits script of the game.
    @copyright LGPL. MIT License.
*/

#include "Customs/CreditsScript.hpp"
#include "Customs/Exception.hpp"

#include "Globals/EngineGlobals.hpp"

#include <cassert>

/**
    @brief Constructor of the class CreditsScript.
    @param[in] GameObject *owner - Owns the component.
*/
CreditsScript::CreditsScript(GameObject *owner) : Script(owner) {
    assert((owner != NULL) and "the owner must be equal to NULL");
}

/**
    @brief Start the credit position.
*/
void CreditsScript::Start() {
    INFO("CreditsScript - initializing");
    position = GetOwner()->GetPosition();
    GetOwner()->SetZoomProportion(Vector(0, 0));
    INFO("CreditsScript - completed");
}

/**
    @brief Do nothing.
*/
void CreditsScript::ComponentUpdate() {

}

/**
    @brief Set the credits x and y positions to zero.
*/
void CreditsScript::FixedComponentUpdate() {
    position->m_x = 0;
    position->m_y = 0;
}
