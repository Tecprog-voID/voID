#include "Customs/ForestActivatorScript.hpp"
#include "Globals/EngineGlobals.hpp"
#include "Customs/CentralLightScript3.hpp"
#include "Log/log.hpp"

/**
    @file UIButton.cpp
    @brief Methods that manages(create and update) the forest script.
    @copyright LGPL. MIT License.
*/

const int animationFrames = 12;
const int framesPerSecond = 9;
const int imagePlacing = 64;

// Constructor
ForestActivatorScript::ForestActivatorScript(GameObject *owner) : Script(owner) {}

/**
    @brief Initializes the forest script.
*/
void ForestActivatorScript::Start() {
    INFO("ForestActivatorScript - initializing");

    CreateAnimations();
    position = GetOwner()->GetPosition();
    animator = (Animator *)GetOwner()->GetComponent("Animator");
    input = InputSystem::GetInstance();
    gamecontroller = input->GetGameController(0);
    GetOwner()->SetZoomProportion(Vector(0,0));
    auto map = SceneManager::GetInstance()->GetScene("Gameplay")->GetGameObject("Map");
    // If map is showing, sets the map's vision configs.
    if (map) {
        GetOwner()->SetZoomProportion(Vector(map->originalWidth/GetOwner()->originalWidth,
                                             map->originalHeight/GetOwner()->originalHeight));
    } else {
        // Do nothing
    }

    INFO("ForestActivatorScript - initialized");
}

/**
    @brief Creates animations.
*/
void ForestActivatorScript::CreateAnimations() {
    INFO("ForestActivatorScript - creating animations");

    // Sets the animations' image and its frames.
    auto forestactivatorSprite = new Image("assets/image/Forest_activator.png",
                                            0, 0, 832, 64);
    auto forestactivatorAnimation = new Animation(GetOwner(),
                                                    forestactivatorSprite);
    for (int i = 0; i <= animationFrames; i++) {
        forestactivatorAnimation->AddFrame(new Frame(i * imagePlacing, 0, imagePlacing, imagePlacing));
    }

    auto forestactivatorAnimation2 = new Animation(GetOwner(), forestactivatorSprite);
    forestactivatorAnimation2->AddFrame(new Frame(animationFrames * imagePlacing, 0, imagePlacing, imagePlacing));

    // Sets forest animations conditions.
    auto forestactivatorAnimator = new Animator(GetOwner());
    forestactivatorAnimation->SetFramesPerSecond(framesPerSecond);
    forestactivatorAnimator->AddAnimation("FOREST ACTIVATOR ANIMATION", forestactivatorAnimation);
    forestactivatorAnimator->AddAnimation("FOREST ACTIVATOR ANIMATION2", forestactivatorAnimation2);

    INFO("ForestActivatorScript - created animations");
}

/**
    @brief Updates the animations components.
*/
void ForestActivatorScript::ComponentUpdate() {
    INFO("ForestActivatorScript - updating components");
    /*
    The animation is not playing, activate equals 0, and it has not runned,
    runs the animation.
    */
    if (!animator->IsPlaying("FOREST ACTIVATOR ANIMATION") && activate == 0 && runned == false) {
        INFO("ForestActivatorScript - playing forest's animation");
        animator->PlayAnimation("FOREST ACTIVATOR ANIMATION");
        activate = 1;
        runned = true;
    } else {
        // Do nothing
    }

    /*
    If the forest animation has already ran and the first animation hasn't
    played, runs the second animation.
    */
    if (runned && !animator->IsPlaying("FOREST ACTIVATOR ANIMATION")) {
        INFO("ForestActivatorScript - playing forest's animation2");

        animator->PlayAnimation("FOREST ACTIVATOR ANIMATION2");
    } else {
        // Do nothing
    }

    // If the animations have already ran activates the CentralLightScript3.
    if (runned) {
        INFO("ForestActivatorScript - activating centrallightscript3");

        auto script = (CentralLightScript3*)SceneManager::GetInstance()
                                        ->GetCurrentScene()
                                        ->GetGameObject("CENTRAL LIGHT 3")
                                        ->GetComponent("CentralLightScript3");
        script->Activate();
    } else {
        // Do nothing
    }

    INFO("ForestActivatorScript - updated components");
}

/**
    @brief Updates the animations components.
*/
void ForestActivatorScript::FixedComponentUpdate() {

}
