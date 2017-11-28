/**
    @file GameOverScript.cpp
    @brief Methods that manages the game over script of the game.
    @copyright LGPL. MIT License.
*/

#include "Customs/GameOverScript.hpp"
#include "Log/log.hpp"

#include <cassert>

const int quantityFrameLine = 22;
const int quantityFrameColumn = 12;

GameOverScript::GameOverScript(GameObject *owner) : Script(owner) {
     assert((owner != NULL) && "the owner must be equal to NULL");
}

/**
    @brief that function starts the game over script. Create the animation,
    position, the animator and the input.
*/
void GameOverScript::Start() {
    INFO("GameOverScript - Start");
    // Starts game-over animations by setting its positions and animator.Sets gameobject's vector zoom proportion.
    position = GetOwner()->GetPosition();
    animator = (Animator *)GetOwner()->GetComponent("Animator");
    input = InputSystem::GetInstance();
    GetOwner()->SetZoomProportion(Vector(0, 0));
}

/**
    @brief that function creates the animations. Create the snow image, the game
    over animation and animator.
*/
void GameOverScript::CreateAnimations() {
    INFO("GameOverScript - Create Animations");
    /*
        Creates game-over animation by setting a image and a animation with
        defined frames positions over it.
    */
    auto m_snowImage = new Image("assets/image/Ending_show_image.png",0,0,4096, 2048);

    auto m_gameOverAnimation= new Animation(GetOwner(), m_snowImage );
    for (int  line = 0; line < quantityFrameLine; line++) {
        for (int column = 0 ; column < quantityFrameColumn ; column++) {
            m_gameOverAnimation->AddFrame(new Frame(column * 341,line* 256, 341, 256));
            m_gameOverAnimation->AddFrame(new Frame(column * 341,line* 256, 341, 256));
        }
    }

    // animator.
    auto m_gameOverAnimator = new Animator(GetOwner());
    m_gameOverAnimator->AddAnimation("snowAnimation", m_gameOverAnimation);
}

/**
    @brief that function updates the components of the game over.
*/
void GameOverScript::ComponentUpdate() {
    INFO("GameOverScript - Component Update");
    /*
        Updates the game-over component and sets the state of played audios.
    */
    animator->PlayAnimation("snowAnimation");
    // Check for the player and its animator and input state.
    if (play==1) {
        animator->PlayAnimation("snowAnimation");
    } else {
        // Do nothing
    }

    if (input->GetKeyDown(INPUT_T) && play==0) {
        // animator->StopAllAnimations();
        AudioController::GetInstance()->PlayAudio("snowSound", -1);
        play=1;
    }
    else if (input->GetKeyDown(INPUT_T) && play==1) {
        play=0;
        AudioController::GetInstance()->StopAudio("snowSound");
        animator->StopAllAnimations();
    }
}

/**
    @brief that function fixs the component upddate of the game over Script.
    They set the position x and y to zero.
*/
void GameOverScript::FixedComponentUpdate() {
    INFO("GameOverScript - Fixed Component Update");
    // Check the components positions, and end them by setting it to zero.
    position->m_x = 0;
    position->m_y = 0;

}
