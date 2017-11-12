#include "Customs/EndScene2.hpp"
#include "Customs/MenuAnimationScript.hpp"
#include "Log/log.hpp"

/**
    @file EndScene2.cpp
    @brief Methods that manages the end-game animations and a 'quit' button.
    @copyright LGPL. MIT License.
*/

// Constructor
EndScene2::EndScene2() {}

/**
    @brief On activation of the second scene, creates 'quit' button and animation in the middle of the screen.
*/
void EndScene2::OnActivation() {
    INFO("EndScene2 - setting on activation's behavior");

    // defines the current center position (vertical and horizontal)
    m_widthMiddle = EngineGlobals::screen_width / 2;
    m_heightMiddle = EngineGlobals::screen_height / 2;

    CreateQuitButton();
    CreateAnimation();

    INFO("EndScene2 - set on activation's behavior");
}

/**
    @brief Method for handling deactivation state changing.
*/
void EndScene2::OnDeactivation() {}

/**
    @brief Method for handling showing state changing.
*/
void EndScene2::OnShown() {}

/**
    @brief Method for handling on hidden state changing.
*/
void EndScene2::OnHidden() {}

/**
    @brief Method that creates the game over's end scene and its background animation.
*/
void EndScene2::CreateAnimation(){
    INFO("EndScene2 - creating animation");

    // Sets the BackgroundAnimation
    auto BackgroundAnimation = new GameObject("ToBeAnimation", new Vector(0 ,0),
                                                                    1024,800,0);
    AddGameObject(BackgroundAnimation);

    INFO("EndScene2 - created animation");
}

/**
    @brief Method that creates 'quit' button on the middle of the screen, and plays a button sound.
*/
void EndScene2::CreateQuitButton() {
    INFO("EndScene2 - creating quit button");
    // defines the current center position
    int xMiddle = EngineGlobals::screen_width / 2 - 100;
    auto quit = new GameObject("Quit", new Vector(xMiddle, 500), 200, 100,0);

    AddGameObject(quit);

    INFO("EndScene2 - created quit button");
}
