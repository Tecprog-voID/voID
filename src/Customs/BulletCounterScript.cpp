/**
    @file BulletCounterScript.cpp
    @brief Manages the bullet counting.
    @copyright LGPL. MIT License.
*/

#include "Customs/BulletCounterScript.hpp"

// include class Exception for appropriate error handling.
#include "Customs/Exception.hpp"

#include "Globals/EngineGlobals.hpp"

/**
    @brief Constructor of the class BulletCounterScript.
    @param[in] GameObject *owner - Owns the component.
*/
BulletCounterScript::BulletCounterScript(GameObject *owner) : Script(owner) {

}

/**
    @brief Starts the Bullet Counter position.
*/
void BulletCounterScript::Start() {
    INFO("PlayButtonScript - initializing");
    counter_position = (Vector *)GetOwner()->GetPosition();
    GetOwner()->SetZoomProportion(Vector(0, 0));
    INFO("PlayButtonScript - completed");
}

/**
    @brief Updates the Bullet Counter informations.
*/
void BulletCounterScript::ComponentUpdate() {
    // Get player's component number of bullets.
    auto aloneWalkerScript = (AloneWalkerScript *)SceneManager::GetInstance()
                          ->GetCurrentScene()
                          ->GetGameObject("NakedMan")
                          ->GetComponent("AloneWalkerScript");

    if(aloneWalkerScript != NULL){
        m_numberBullet = (unsigned int)aloneWalkerScript->bulletNumber;

        // Update the text of the left number of bullets.
        auto counterText = (UIText *)GetOwner()->GetComponent("UIText");
        counterText->SetText(std::to_string(m_numberBullet));
    } else {
        throw Exception("BulletCounterScript - AloneWalkerScript must be different of null.");
    }

}

/**
    @brief Set the Bullet Counter's x and y positions.
*/
void BulletCounterScript::FixedComponentUpdate() {
    // Set the values.
    counter_position->m_x = 900;
    counter_position->m_y = 700;
}
