/**
    @file BulletCounterScript.hpp
    @brief Manages the bullet counting.
    @copyright LGPL. MIT License.
*/

#ifndef __BULLET_COUNTER_SCRIPT__
#define __BULLET_COUNTER_SCRIPT__

#include "Engine/InputSystem.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/SceneManager.hpp"
#include "Engine/CameraSystem.hpp"

#include "Math/Vector.hpp"
#include "Components/UIText.hpp"
#include "Components/Animator.hpp"
#include "Components/Script.hpp"
#include "Customs/NakedManScript.hpp"
#include "Customs/Exception.hpp"

#include <string>

class BulletCounterScript : public Script {

public:
    BulletCounterScript(GameObject *owner);
    ~BulletCounterScript();

private:

    void ComponentUpdate() override;

    // Replace the component name and return it.
    std::string GetComponentName() override {
        return "BulletCounterScript";
    };

    void FixedComponentUpdate() override;

    void Start() override;

    // Position vector of the BulletCounter
    Vector *counter_position = nullptr;

    // Integer number of player's bullets
    int m_numberBullet = 0;
};
#endif
