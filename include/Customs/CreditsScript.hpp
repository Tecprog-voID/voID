/**
    @file CreditsScript.hpp
    @brief Manages the credits script of the game.
    @copyright LGPL. MIT License.
*/

#ifndef __CREDITS_SCRIPT__
#define __CREDITS_SCRIPT__

#include "Engine/InputSystem.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/SceneManager.hpp"
#include "Engine/CameraSystem.hpp"


#include "Components/Animator.hpp"
#include "Components/RectangleRenderer.hpp"
#include "Components/UIText.hpp"
#include "Components/Script.hpp"
#include "Customs/Exception.hpp"

#include "Customs/NakedManScript.hpp"
#include "Customs/FirstBossController.hpp"
#include "Math/Vector.hpp"

#include <string>

class CreditsScript : public Script {

public:
    CreditsScript(GameObject *owner);
    ~CreditsScript();

protected:


private:

    void ComponentUpdate() override;

    // Replace the component name and return it.
    std::string GetComponentName() override {
        return "CreditsScript";
    };

    void FixedComponentUpdate() override;

    void Start() override;
    // Sets the CreditsScript position as a vector
    Vector *position = nullptr;

};

#endif
