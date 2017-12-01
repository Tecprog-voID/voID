/**
    @file SnowScript.cpp
    @brief This class contains all attributes and methods that manages the
    snow in the game.
    @copyright LGPL. MIT License.
*/

#include "Customs/SnowScript.hpp"
#include "Log/log.hpp"

// Start snow script, zoom proportion
const float vectorZoomProportionAxisX = 0;
const float vectorZoomProportionAxisY = 0;

// Image snow script
const std::string snowImagePath = "assets/image/game_effects/snow.png";
const int snowImagePositionX = 0;
const int snowImagePositionY = 0;
const int snowImageWidth = 6820;
const int snowImageHeight = 256;

// Create animations
const int maxSnowFlakes = 20;

// Create animation snow
const int snowAnimationPositionAxisX = 341;
const int snowAnimationPositionAxisY = 0;
const int snowAnimationWigth = 341;
const int snowAnimationHeight = 256;

const int soundLoops = -1;

/**
    @brief Initializes the script of snow instance.
    @param[in] GameObject *owner - owns the component.
*/
SnowScript::SnowScript(GameObject *owner) : Script(owner) {

}

/**
    @brief Start the snow animation by setting the starting position.
*/
void SnowScript::Start() {
    INFO("SnowScript - Initializing");
    // Creates the animations.
    CreateAnimations();

    // Get the position.
    position = GetOwner()->GetPosition();

    // Get the animator.
    animator = (Animator *)GetOwner()->GetComponent("Animator");
    input = InputSystem::GetInstance();
    GetOwner()->SetZoomProportion(Vector(vectorZoomProportionAxisX,
                                         vectorZoomProportionAxisY));
    INFO("SnowScript - Completed");
}

/**
    @brief Create the snow animation by setting the frames of snow.
*/
void SnowScript::CreateAnimations() {
    INFO("SnowScript - Creating animations");
    // Creates the show image.
    auto snowImage = new Image(snowImagePath, snowImagePositionX, snowImagePositionY,
                               snowImageWidth, snowImageHeight);

    // Creates the snow animation.
    auto snowAnimation= new Animation(GetOwner(), snowImage);

    // Create the animations by adding the snowflakes in the frames.
    for (int i = 0; i < maxSnowFlakes; i++) {
        snowAnimation->AddFrame(new Frame(i * snowAnimationPositionAxisX,
                                snowAnimationPositionAxisY, snowAnimationWigth,
                                snowAnimationHeight));
    } // for -- Create the animations snow.

    // Creates the animator.
    auto weatherAnimator = new Animator(GetOwner());
    weatherAnimator->AddAnimation("snowAnimation", snowAnimation);
    INFO("SnowScript - Animations created");
}

/**
    @brief Update the components of snow.
*/
void SnowScript::ComponentUpdate() {

    // Start the snow animation.
    if (play == 1) {
        animator->PlayAnimation("snowAnimation");
    } else {
        // Nothing to do
    }

    // Update the play variable and the sound effect.
    if (input->GetKeyDown(INPUT_T) and play == 0) {
        AudioController::GetInstance()->PlayAudio("snowSound", soundLoops);
        play = 1;
    } else if (input->GetKeyDown(INPUT_T) and play == 1) {
        play = 0;
        AudioController::GetInstance()->StopAudio("snowSound");
        animator->StopAllAnimations();
    } else {
        // Nothing to do
    }
}

/**
    @brief Updates the initial position of the beginning snow.
*/
void SnowScript::FixedComponentUpdate() {

    // Sets the x position.
    position->m_x = 0;

    // Sets the y position.
    position->m_y = 0;
}
