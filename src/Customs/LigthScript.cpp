#include "Customs/LightScript.hpp"
#include "Globals/EngineGlobals.hpp"
#include "Log/log.hpp"

#include <cassert>

const int middlePosition = 2;

LightScript::LightScript(GameObject *owner) : Script(owner) {
     assert((owner != NULL) and "the owner must be equal to NULL");
}

/**
    @brief that function starts the light script. Create the animation,
    position, the animator and the input.
*/
void LightScript::Start() {
    INFO("LightScript - Start");
    // Create animations, define position and animator by gameobject.
    CreateAnimations();
    position = GetOwner()->GetPosition();
    animator = (Animator *)GetOwner()->GetComponent("Animator");
    input = InputSystem::GetInstance();
    // Not affected by zoom.
    GetOwner()->SetZoomProportion(Vector(0, 0));
}

/**
    @brief that function creates the animations of the light script. Create the
    light image, the light animation and animator.
*/
void LightScript::CreateAnimations(){
    INFO("LightScript - Create Animations");
    // Instantiating lightimage by image file and define its positons.
    auto m_lightImage = new Image("assets/light.png",0,0,682, 512);

    // Instantiating light animation by gameobject components, image and play state.
    auto m_lightAnimation = new Animation(GetOwner(),m_lightImage );

    // Setting frames of light animation.
    m_lightAnimation->AddFrame(new Frame(0,0, 682, 512));

    // Instantiating animator, and setting its animation.
    auto m_lightAnimator = new Animator(GetOwner());
    m_lightAnimator->AddAnimation("lightAnimation", m_lightAnimation);
}

/**
    @brief that function updates the components of the light script. Create the player
    and get his instance, currante scene and object ("NakedMan")
*/
void LightScript::ComponentUpdate() {
    INFO("LightScript - Component Update");
    // Defining player.
    player = SceneManager::GetInstance()->GetCurrentScene()->GetGameObject("NakedMan");
    // Check for the player and its animator and input state.
    if (player) {
        if (play==1) {
            animator->PlayAnimation("lightAnimation");
        } else {
            // Do nothing
        }

        if (input->GetKeyDown(INPUT_Y) and play==0) {
            play=1;
        } else if (input->GetKeyDown(INPUT_Y) and play==1) {
            play=0;
        }
    } else {
        // Do nothing
    }
}

/**
    @brief that function fixs the components update of the light script. Check if
    there is a player and get his position x and y.
*/
void LightScript::FixedComponentUpdate() {
    INFO("LightScript - Fixed Component Update");
    // Check for the player's state, and if is true, sets its x and y positions.
    if (player) {
        position->m_x = player->GetPosition()->m_x - GetOwner()->GetWidth() / middlePosition + 40;
        position->m_y = player->GetPosition()->m_y - GetOwner()->GetHeight() / middlePosition + 40;
    } else {
        // Do nothing
    }
}
