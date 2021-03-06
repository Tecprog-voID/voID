/**
    @file FirstBossLifeScript.cpp
    @brief Manage the first boss life.
    @copyright MIT License.
*/

#include "Customs/FirstBossLifeScript.hpp"

#include "Globals/EngineGlobals.hpp"

#include <cassert>

const int lifePosition = 10;
const int lifeComparer = 0;
const int bossLifeX = 650;
const int bossLifeY = 10;

/**
    @brief Constructor of the FirstBossLifeScript class.
*/
FirstBossLifeScript::FirstBossLifeScript(GameObject *owner) : Script(owner) {
    assert((owner != NULL) and "the owner must be equal to NULL");
    INFO("FirstBossLifeScript - initialized");
}

/**
    @brief Start the script that control the life of the first boss.
*/
void FirstBossLifeScript::Start() {
    INFO("FirstBossLifeScript - Start initializing");
    // Define the position of life bar.
    position = GetOwner()->GetPosition();
    GetOwner()->SetZoomProportion(Vector(0,0));
}

/**
    @brief Control the lifebar of the first boss.
*/
void FirstBossLifeScript::ComponentUpdate() {
    // Update the life bar of the boss with every attack he takes.

    auto firstBossLifeRenderer = (RectangleRenderer*)GetOwner()->
                                  GetComponent("RectangleRenderer");
    int actualLife = firstBossLifeRenderer->GetWidth();

    // Compares the hit status with the actual life. 
    if (hit and actualLife > lifeComparer) {
        cout << "hit" << endl;
        cout << actualLife << endl;
        firstBossLifeRenderer->SetWidth(actualLife - lifePosition);
        hit = false;
    } else {
        // Do nothing
    }

    // Compares the actual life. 
    if (actualLife <= lifeComparer) {
        FirstBossController::GetInstance()->ActivateCreditsAnimation();
        FirstBossController::GetInstance()->DeactivateLifeBars();
    } else {
        // Do nothing
    }
}

/**
    @brief Set the position of the first boss's lifebar.
*/
void FirstBossLifeScript::FixedComponentUpdate() {
    position->m_x = bossLifeX;
    position->m_y = bossLifeY;
}
