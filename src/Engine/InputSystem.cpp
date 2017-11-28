#include <algorithm>

#include "Engine/InputSystem.hpp"
#include "Log/log.hpp"

/**
    @file InputSystem.cpp
    @brief Methods for the actions of the buttons needed for playing the game.
    @copyright LGPL. MIT License.
*/


// Static variables initialization
InputSystem *InputSystem::m_instance = 0;

/**
    @brief Initializes InputSystem instance.
*/
InputSystem::InputSystem() {
    INFO("InputSystem - initializing input system");
    SDL_PumpEvents();
    SDL_GameControllerEventState(SDL_IGNORE);

    LoadGameControllers();

    m_states = SDL_GetKeyboardState(&m_statesSize);
    m_oldStates = new Uint8[m_statesSize];
    m_mouseStates = SDL_GetMouseState(&m_mouseHorizontal, &m_mouseVertical);
    INFO("InputSystem - initialized input system");
}

// Destructor
InputSystem::~InputSystem() {
    INFO("InputSystem - destroying input system");
    m_states = nullptr;
    delete[] m_oldStates;
    m_oldStates = nullptr;
    INFO("InputSystem - destroyed input system");
}

/**
    @brief Get the current instance of input system.
    @return m_instance.
*/
InputSystem *InputSystem::GetInstance() {
    INFO("InputSystem - initializing instance");
    // If the m_instance is not initialized, intializes it.
    if (!m_instance) {
        m_instance = new InputSystem();
    } else {
        // Do nothing
    }
    INFO("InputSystem - initialized instance");
    return m_instance;
}

/**
    @brief Update the state of the input.
*/
void InputSystem::UpdateStates() {
    INFO("InputSystem - updating states");
    // Update old states to be equal to actual.
    for (int i = 0; i < m_statesSize; i++) {
        m_oldStates[i] = m_states[i];
    }
    m_oldMouseStates = m_mouseStates;

    SDL_PumpEvents();
    SDL_GameControllerUpdate();

    UpdateGameControllers();

    m_mouseStates = SDL_GetMouseState(&m_mouseHorizontal, &m_mouseVertical);
    INFO("InputSystem - updated states");
}

/**
    @brief Get the current state of a down button on a keyboard.
    @param[in] key - state of a button from the keyboard.
    @return bool.
*/
bool InputSystem::GetKeyDown(KeyboardInputGlobal key) {
    INFO("InputSystem - getting key beying pressed");
    /*
    If respective button is being pressed but was not pressed previously,
    returns true.
    */
    if (m_states[key] and !m_oldStates[key]) {
        return true;
    } else {
        // Do nothing
    }
    return false;
}

/**
    @brief Get the current state of a button up on a keyboard.
    @param[in] key - state of a button from the keyboard.
    @return bool.
*/
bool InputSystem::GetKeyUp(KeyboardInputGlobal key) {
    INFO("InputSystem - getting key beying pressed");
    /*
    If respective button is being pressed but was not pressed previously,
    returns true.
    */
    if (!m_states[key] and m_oldStates[key]) {
        return true;
    } else {
        // Do nothing
    }
    return false;
}

/**
    @brief Get the current state of a pressed button up on a keyboard.
    @param[in] key - state of a button from the keyboard.
    @return bool.
*/
bool InputSystem::GetKeyPressed(KeyboardInputGlobal key) {
    INFO("InputSystem - getting key beying pressed");
    // If the respective key is being pressed, returns true.
    if (m_states[key]) {
        return true;
    } else {
        // Do nothing
    }
    return false;
}

/**
    @brief Get the current state of a mouse pressed button, and returns the current button status
    pressed down.
    @param[in] button - state of a button from the mouse.
    @return bool.
*/
bool InputSystem::GetMouseButtonDown(MouseInputGlobal button) {
    INFO("InputSystem - getting mouse button beying pressed");
    // Defines if the mouse is being pressed right at the moment
    bool isPressed = m_mouseStates & SDL_BUTTON(button);
    bool wasPressed = m_oldMouseStates & SDL_BUTTON(button);
    /*
    If respective button is being pressed but was not pressed previously,
    returns true.
    */
    if (isPressed and !wasPressed) {
        return true;
    } else {
        // Do nothing
    }
    return false;
}

/**
    @brief Get the current state of a mouse pressed button, and returns the current button status
    pressed up.
    @param[in] button - state of a button from the mouse.
    @return bool.
*/
bool InputSystem::GetMouseButtonUp(MouseInputGlobal button) {
    INFO("InputSystem - getting mouse button beying pressed");
    // Defines if the mouse was pressed, but is not being pressed anymore
    bool isPressed = m_mouseStates & SDL_BUTTON(button);
    bool wasPressed = m_oldMouseStates & SDL_BUTTON(button);
    /*
    If respective button is being pressed but was not pressed previously,
    returns true.
    */
    if (!isPressed and wasPressed) {
        return true;
    } else {
        // Do nothing
    }
    return false;
}

/**
    @brief Check if a mouse button was pressed.
    @param[in] button - state of a button from the mouse.
    @return bool.
*/
bool InputSystem::GetMouseButtonPressed(MouseInputGlobal button) {
    INFO("InputSystem - getting mouse button beying pressed");
    /*
    If respective button is being pressed but was not pressed previously,
    returns true.
    */
    if (m_mouseStates & SDL_BUTTON(button)) {
        return true;
    } else {
        // Do nothing
    }
    return false;
}

/**
    @brief Defines the mouse position.
    @return position.
*/
std::pair<int, int> InputSystem::GetMousePosition() {
    INFO("InputSystem - getting mouse position");
    std::pair<int, int> position;
    position = std::make_pair(m_mouseHorizontal, m_mouseVertical);
    INFO("InputSystem - got mouse position");
    return position;
}

/**
    @brief Count connected joysticks, and load them.
*/
void InputSystem::LoadGameControllers() {
    INFO("InputSystem - loading game controllers");
    int quantity = SDL_NumJoysticks();

    // Count available game controllers.
    for (int i = 0; i < quantity; i++) {
        // Checking if it's a joystick.
        if (SDL_IsGameController(i)) {
            SDL_GameController *sdl_gc = SDL_GameControllerOpen(i);
            GameController *gc = new GameController(sdl_gc);
            if (sdl_gc) {
                m_gameControllers.push_back(gc);
            } else {
                // Do nothing
            }
        } else {
            // Do nothing
        }
    }
    INFO("InputSystem - loaded game controllers");
}

/**
    @brief Update status of current joystick.
*/
void InputSystem::UpdateGameControllers() {
    INFO("InputSystem - updating game controllers");
    CheckGameControllersConnections();
    for (auto gc : m_gameControllers) {
        gc->Update();
    }
    INFO("InputSystem - updated game controllers");
}

/**
    @brief Check connection status of current joystick.
*/
void InputSystem::CheckGameControllersConnections() {}

/**
    @brief Defines the N'th game controller on the system.
    @param[in] index - the controller identifier.
    @return GameController.
*/
GameController *InputSystem::GetGameController(int index) {
    INFO("InputSystem - getting game controllers");
    // Returns NULL if an error occurred.
    if (m_gameControllers.size() < (unsigned)index + 1) {
        return nullptr;
    } else {
        // Do nothing
    }
    // Returns a controller identifier.
    return m_gameControllers.at(index);
}
