/**
    @file BulletCounterScript.cpp
    @brief Manages the bullet counting.
    @copyright LGPL. MIT License.
*/

#include "Customs/BulletCounterScript.hpp"
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
    counter_position = GetOwner()->GetPosition();
    GetOwner()->SetZoomProportion(Vector(0, 0));
    INFO("PlayButtonScript - completed");
}

/**
    @brief Updates the Bullet Counter informations.
*/
void BulletCounterScript::ComponentUpdate() {
    // Get player's component number of bullets.
    auto nakedManScript = (NakedManScript *)SceneManager::GetInstance()
                          ->GetCurrentScene()
                          ->GetGameObject("NakedMan")
                          ->GetComponent("NakedManScript");

    if(nakedManScript != NULL){
        m_numberBullet = nakedManScript->bulletNumber;

        // Update the text of the left number of bullets.
        auto counterText = (UIText *)GetOwner()->GetComponent("UIText");
        counterText->SetText(std::to_string(m_numberBullet));
    } else {
        throw Exception("BulletCounterScript - nakedManScript must be different of null.");
    }

}

/**
    @brief Set the Bullet Counter's x and y positions.
*/
void BulletCounterScript::FixedComponentUpdate() {
    counter_position->m_x = 900;
    counter_position->m_y = 700;
}
