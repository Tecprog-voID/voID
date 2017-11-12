#include "Customs/MenuAnimationScript.hpp"
#include "Log/log.hpp"

#include <stdio.h>
#include <cassert>

const int quantityFrame = 16;
const int framePerSecond = 10;

// Constructor
MenuAnimationScript::MenuAnimationScript(GameObject *owner) : Script(owner) {
     assert((owner != NULL) && "the owner must be equal to NULL");
}

/**
    @brief that function starts the menu animation. Create the animation,
    position and the animator.
*/
void MenuAnimationScript::Start() {
    INFO("MenuAnimationsScript - Create Player Hit");
    // Create animations.
    CreateAnimations();
    position = GetOwner()->GetPosition();
    animator = (Animator *)GetOwner()->GetComponent("Animator");
}


/**
    @brief that function creates the animation of the menu animstion. Create the MenuAnimationScriptAnimator
    as an animator, the mainSprite image, the main animation one and two.
    Set the frame and add the animations to the game.
*/
void MenuAnimationScript::CreateAnimations() {
    INFO("MenuAnimationsScript - Create Animations");
    // Instantiating the menu script animator.
    auto m_MenuAnimationScriptAnimator = new Animator(GetOwner());

    // Instantiating the menu image and its position.
    auto m_mainSprite = new Image("assets/menu_animation.png", 0, 0, 5456, 256);

    /*
        Instantiating the main animation and its position.
        A for loop defines the frames in the main animation and in the second main animation.
    */
    auto m_mainAnimation = new Animation(GetOwner(), m_mainSprite);
    for (int counter = 0; counter < quantityFrame; counter++) {
        m_mainAnimation->AddFrame(new Frame(counter * 341, 0, 341, 256));
    }

    auto m_mainAnimation2 = new Animation(GetOwner(), m_mainSprite);
    for (int counter = 0; counter < quantityFrame; counter++) {
        m_mainAnimation2->AddFrame(new Frame(counter * 341, 256, 341, 256));
    }

    m_mainAnimation->SetFramesPerSecond(framePerSecond);
    m_mainAnimation2->SetFramesPerSecond(framePerSecond);

    m_MenuAnimationScriptAnimator->AddAnimation("mainAnimation", m_mainAnimation);
    m_MenuAnimationScriptAnimator->AddAnimation("mainAnimation2", m_mainAnimation2);
}

/**
    @brief that function updates the components of the menu animation.
*/
void MenuAnimationScript::ComponentUpdate() {
    INFO("MenuAnimationsScript - Component Update");
    // Check the current state of the initial animation and animator, if false, plays it.
    if (!animator->IsPlaying("mainAnimation") && !initialAnimation) {
        initialAnimation = true;
        animator->PlayAnimation("mainAnimation");
    } else {
        // Do nothing
    }

    // Check the current state of the initial animation, if true, checks the animator state. If false, plays the animator.
    if (initialAnimation) {
        if (!animator->IsPlaying("mainAnimation")) {
            if (!animator->IsPlaying("mainAnimation2") && initialAnimation) {
                animator->PlayAnimation("mainAnimation2");
            } else {
                // Do nothing
            }
        }
    } else {
        // Do nothing
    }
}

/**
    @brief that function fixs the components update of the menu animation.
*/
void MenuAnimationScript::FixedComponentUpdate() {
    INFO("MenuAnimationsScript - Fixed Component Update");
}
