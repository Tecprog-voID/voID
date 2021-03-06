#include "Engine/GameController.hpp"
#include "Log/log.hpp"

/**
    @file GameController.cpp
    @brief Methods that initializes all buttons actions from game controllers .
    @copyright LGPL. MIT License.
*/


/**
    @brief Initializes GameController instance, to use game controllers.
    @param[in] gc - game controller inputs.
*/
GameController::GameController(SDL_GameController *gc) {
    INFO("GameController - initializing game controller");
    /*
    If the game controller was detected, shows it is working, else, shows an
    error.
    */
    if (gc) {
        INFO("    " << SDL_GameControllerName(gc) << " opened");
        m_gameController = gc;
    } else {
        ERROR("    Could not open game controller " << SDL_GameControllerName(gc));
    }

    m_oldButtonsStates.resize(GC_INPUT_MAX, 0);
    m_currentButtonsStates.resize(GC_INPUT_MAX, 0);

    INFO("GameController - initialized game controller");
}

/**
    @brief Game controller constructor.
    @param[in] m_gameController - the game controller.

*/
GameController::~GameController() {
    INFO("GameController - destroying game controller");

    m_gameController = nullptr;
    INFO("GameController - destroyed game controller");
}

/**
    @brief Updates the state of a button in a game controller.
*/
void GameController::Update() {
    INFO("GameController - updating game controller");

    m_oldButtonsStates = m_currentButtonsStates;

    for (int i = 0; i < GC_INPUT_MAX; i++) {
        m_currentButtonsStates[i] = SDL_GameControllerGetButton(m_gameController,
                                                                (SDL_GameControllerButton)i);
    }

    INFO("GameController - updated game controller");
}

/**
    @brief Get the current state of a button down on a game controller.
    @param[in] button - status of the button down.
    @return bool.
*/
bool GameController::GetButtonDown(GameControllerButton button) {
    INFO("GameController - getting button's state");
    /*
    If respective button has changed its state from false to true, returns
    true.
    */
    if (m_currentButtonsStates[button] and !m_oldButtonsStates[button]){
        INFO("GameController - button's state changed");
        return true;
    } else {
        // Do nothing
    }
    INFO("GameController - button's state did not change");
    return false;
}

/**
    @brief Get the current state of a button up on a game controller.
    @param[in] button - status of the button up.
    @return bool.
*/
bool GameController::GetButtonUp(GameControllerButton button) {
    INFO("GameController - getting button's state");
    /*
    If respective button has changed its state from true to false, returns
    true.
    */
    if (!m_currentButtonsStates[button] and m_oldButtonsStates[button]){
        INFO("GameController - button's state changed");
        return true;
    } else {
        // Do nothing
    }
    INFO("GameController - button's state did not change");
    return false;
}

/**
    @brief Get the current button pressed of a button on a game controller.
    @param[in] button - status of a button of the game controller.
    @return bool.
*/
bool GameController::GetButtonPressed(GameControllerButton button) {
    INFO("GameController - getting actual pressed button");
    return SDL_GameControllerGetButton(m_gameController,
                                     (SDL_GameControllerButton)button);
}

/**
    @brief Get the current state of an axis control on a game controller.
    @param[in] axis - current axis of a controller.
    @return int.
*/
int GameController::GetAxis(GameControllerAxis axis) {
    INFO("GameController - getting axis");
    return SDL_GameControllerGetAxis(m_gameController,
                                   (SDL_GameControllerAxis)axis);
}
