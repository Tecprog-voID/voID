/**
	@file CentralLightScript3.cpp
	@brief Responsible for the light animation during the menu
    screen in center os screen.
	@copyright MIT License.
*/
#include "Customs/CentralLightScript3.hpp"
#include "Globals/EngineGlobals.hpp"

/**
    @brief Constructor for the classe CentralLightScript3.
*/
CentralLightScript3::CentralLightScript3(GameObject *owner) : Script(owner) {

}

/**
    @brief Sets the initial definitions when starting the animation.
*/
void CentralLightScript3::Start() {

    // Creates the animations and the animator for the script.
    CreateAnimations();

    m_position = GetOwner()->GetPosition();

    m_animator = (Animator *)GetOwner()->GetComponent("Animator");

    // Get the inputs.
    m_input = InputSystem::GetInstance();

    m_gamecontroller = m_input->GetGameController(0);

    GetOwner()->SetZoomProportion(Vector(0,0));

    auto map = SceneManager::GetInstance()->GetScene("Gameplay")->GetGameObject("Map");

    if(map) GetOwner()->SetZoomProportion(Vector(map->originalWidth / 
                                                 GetOwner()->originalWidth, 
                                                 map->originalHeight / 
                                                 GetOwner()->originalHeight));

}

/**
    @brief Generates the animations on the screen.
*/
void CentralLightScript3::CreateAnimations(){

    // Create the animation.
    auto centrallightSprite = new Image("assets/centro3.png", 0, 0,832, 64);
    auto centrallightAnimation = new Animation(GetOwner(), centrallightSprite);
    centrallightAnimation->AddFrame(new Frame(0, 0, 64, 64));

    // Create the animator.
    auto centrallightAnimator = new Animator(GetOwner());

    // Number of frames to add per second.
    centrallightAnimation->SetFramesPerSecond(9);
    centrallightAnimator->AddAnimation("CENTRAL LIGHT ANIMATION", centrallightAnimation);


}

/**
    @brief Handles with changes on the component.
*/
void CentralLightScript3::ComponentUpdate() {

    if(!m_animator->IsPlaying("CENTRAL LIGHT ANIMATION") && m_active){
        m_animator->PlayAnimation("CENTRAL LIGHT ANIMATION");
    }
}


void CentralLightScript3::FixedComponentUpdate() {

}
