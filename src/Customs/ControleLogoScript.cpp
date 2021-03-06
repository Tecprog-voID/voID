/**
    @file ControleLogoScript.cpp
    @brief Manage the animations of the control logo, at the start of the game.
    @copyright MIT License.
*/

#include "Customs/ControleLogoScript.hpp"
#include "Log/log.hpp"
#include "Globals/EngineGlobals.hpp"

#include <stdio.h>

#include <cassert>

const int logoWidth = 5115;
const int logoHeight = 512;
const int framesCounter = 15;
const int frameWidth = 341;
const int frameHeight = 256;
const int framesPerSecond = 9;
const int timePlayAnimation = 390;
const int timeStopAnimation = 490;
const int timeUpdateAnimation = 530;

/**
    @brief Constructor for the ControleLogoScript class.
*/
ControleLogoScript::ControleLogoScript(GameObject *owner) : Script(owner) {
    assert((owner != NULL) and "the owner must be equal to NULL");
}

/**
    @brief Start the animation of the controle logo.
*/
void ControleLogoScript::Start() {
    INFO("ControleLogoScript - initializing");
    /*
        Creates the animations defining position the place to insert
        and the scene that will be inserted.
    */
    CreateAnimations();
    m_position = GetOwner()->GetPosition();
    m_animator = (Animator *)GetOwner()->GetComponent("Animator");
    m_input = InputSystem::GetInstance();
    GetOwner()->SetZoomProportion(Vector(0,0));
    INFO("ControleLogoScript - initialized");
}

/**
    @brief Create the animations for controle logo.
*/
void ControleLogoScript::CreateAnimations() {
    INFO("ControleLogoScript - Creating Animations");
    // Image logo sprite.
    auto controle_LogoSprite = new Image("assets/image/introjoystick.png", 0, 0, logoWidth, logoHeight);
    // Aniamtion logo sprite.
    auto controleAnimation = new Animation(GetOwner(), controle_LogoSprite);

    // Sets the frames for the controle animation.
    for (int i = 0; i < framesCounter; i++) {
        controleAnimation -> AddFrame(new Frame(i * frameWidth, 0, frameWidth, frameHeight));
    }

    // Sets the frames for the controle animation.
    for (int i = 0; i < framesCounter; i++) {
        controleAnimation -> AddFrame(new Frame(i * frameWidth, frameHeight, frameWidth, frameHeight));
    }

    auto controleAnimator = new Animator(GetOwner());
    controleAnimation -> SetFramesPerSecond(framesPerSecond);
    controleAnimator -> AddAnimation("CONTROLE ANIMATION", controleAnimation);
    INFO("ControleLogoScript - Animations Created");
}

/**
    @brief Do nothing.
*/
void ControleLogoScript::ComponentUpdate() {}

/**
    @brief Control the duration of the controle logo's animation.
*/
void ControleLogoScript::FixedComponentUpdate() {

    // Update time and set play animator.
    time.Update(1);

    // Compares time to play the animation.
    if (time.GetTime() >= timePlayAnimation) {
        m_animator->PlayAnimation("CONTROLE ANIMATION");
    } else {
        // Do nothing
    }

    // Compares time to stop the animation.
    if (time.GetTime() >= timeStopAnimation) {
        m_animator->StopAllAnimations();
    } else {
        // Do nothing
    }

    // Compares time to update the animation.
    if (time.GetTime() >= timeUpdateAnimation) {
        SceneManager::GetInstance()->SetCurrentScene("Main");
    } else {
        // Do nothing
    }
}
