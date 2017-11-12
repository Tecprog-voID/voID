#include "Customs/MenuController.hpp"
#include "Log/log.hpp"

/**
    @file MenuController.cpp
    @brief Methods that manages the selections in the game menu.
    @copyright LGPL. MIT License.
*/

MenuController *MenuController::m_instance = nullptr;

// Constructor
MenuController::MenuController() {}

/**
    @brief Receives the input of the new game mode, if there's no previous one.
    @return m_instance of MenuController
*/
MenuController *MenuController::GetInstance() {
    INFO("MenuController - getting instance");

    // If the m_instance is not initialized, intializes it.
    if (!m_instance){
        m_instance = new MenuController();
    } else {
        // Do nothing
    }
    return m_instance;
    INFO("MenuController - got instance");
}

/**
    @brief Defines the char entered as the selected game mode.
    @param[in] gamemode - a char that define the selected game mode.
*/
void MenuController::SelectGamemode(char gamemode) {
    INFO("MenuController - selecting game mode");

    m_selectedGamemode = gamemode;

    INFO("MenuController - selected game mode");
}

/**
    @brief Gets the selected game mode.
    @return char
*/
char MenuController::GetGamemode() {
    INFO("MenuController - getting game mode");

    return m_selectedGamemode;

    INFO("MenuController - got game mode");
}
