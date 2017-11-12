/**
	@file CentralLightScript1.cpp
	@brief Responsible for the light animation during the menu screen.
	@copyright MIT License.
*/
#include "Customs/CentralLightScript1.hpp"
#include "Globals/EngineGlobals.hpp"

/**
    @brief Constructor for the classe CentralLightScript1.
*/
CentralLightScript1::CentralLightScript1(GameObject *owner) : Script(owner) {
    INFO("CentralLightScript1 CentralLightScript1() - initializing");
    INFO("CentralLightScript1 CentralLightScript1() - completed");
}

/**
    @brief Sets the initial definitions when starting the animation.
*/
void CentralLightScript1::Start() {
    INFO("CentralLightScript1 Start() - initializing");
    // Creates the animations and the animator for the script.
    CreateAnimations();
    m_position = GetOwner()->GetPosition();
    m_animator = (Animator *)GetOwner()->GetComponent("Animator");
    // Get the inputs.
    m_input = InputSystem::GetInstance();
    // Index of the controller.
    const int gameControllerIndex = 0;
    m_gameController = m_input->GetGameController(gameControllerIndex);
    // Set the zoom and get the map of the scene.
    GetOwner()->SetZoomProportion(Vector(0,0));
    auto map = SceneManager::GetInstance()->GetScene("Gameplay")->GetGameObject("Map");
    // Check if the map from the scene exists.
    if (map) {
        // Set the zoom for the map.
        GetOwner()->SetZoomProportion(Vector(map->originalWidth/GetOwner()->
               originalWidth,map->originalHeight / GetOwner()->originalHeight));
    } else {
        // Do nothing.
    }
    INFO("CentralLightScript1 Start() - completed");
}

/**
    @brief Generates the animations on the screen.
*/
void CentralLightScript1::CreateAnimations() {
    INFO("CentralLightScript1 CreateAnimations() - initializing");
    // Create the animation.
    auto centrallightSprite = new Image("assets/centro4.png", 0, 0, 832, 64);
    auto centrallightAnimation = new Animation(GetOwner(), centrallightSprite);
    centrallightAnimation->AddFrame(new Frame(0, 0, 64, 64));

    // Create the animator.
    auto centrallightAnimator = new Animator(GetOwner());
    // Number of frames to add per second.
    const int numberFramesPerSecond = 9;
    centrallightAnimation->SetFramesPerSecond(numberFramesPerSecond);
    centrallightAnimator->AddAnimation("CENTRAL LIGHT ANIMATION",
                                       centrallightAnimation);
    INFO("CentralLightScript1 CreateAnimations() - completed");
}

/**
    @brief Handles with changes on the component.
*/
void CentralLightScript1::ComponentUpdate() {
    INFO("CentralLightScript1 ComponentUpdate() - initializing");
    // Play the CENTRAL LIGHT ANIMATION if isn't being played and is active.
    if (!m_animator->IsPlaying("CENTRAL LIGHT ANIMATION") && m_active) {
        // Play the animation CENTRAL LIGHT ANIMATION
        m_animator->PlayAnimation("CENTRAL LIGHT ANIMATION");
    } else {
        // Do nothing.
    }
    INFO("CentralLightScript1 ComponentUpdate() - completed");
}

void CentralLightScript1::FixedComponentUpdate() {
    INFO("CentralLightScript1 FixedComponentUpdate() - completed");
}
