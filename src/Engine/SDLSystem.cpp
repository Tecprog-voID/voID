/**
    @file SDLSystem.cpp
    @brief Manages the SDL functions.
    @copyright LGPL. MIT License.
*/

#include "Engine/SDLSystem.hpp"

#include "Customs/FirstBossScene.hpp"
#include "Customs/MainScene.hpp"
#include "Customs/GamePlayScene.hpp"
#include "Customs/PreMenuScene.hpp"
#include "Customs/EndScene1.hpp"
#include "Customs/EndScene2.hpp"
#include "Customs/Exception.hpp"

#include <cassert>

const int red = 0;
const int green = 0;
const int blue = 0;
const int alpha = 255;
const int frequency = 44100;
const int channels = 2;
const int chunksize = 2048;
const int ticksLimit = 1000;

// Static variables initialization
SDLSystem *SDLSystem::m_instance = nullptr;

/**
    @brief Initialize the frame counter and the frame ticks counter.
*/
SDLSystem::SDLSystem() {
    m_frameCounter = 0;
    m_lastFrameTicks = 0;
}

/**
    @brief Initialize the instance, window and renderer pointers.
*/
SDLSystem::~SDLSystem() {
    m_instance = nullptr;
    m_window = nullptr;
    m_renderer = nullptr;
}

/**
    @brief Initialize all systems.
*/
void SDLSystem::Init() {
    INFO("SDLSystem - initializing");

    // Check initialization fails
    assert((InitSDL() != '\0') and "InitSDL() must be equal to zero");
    assert((InitIMG() != '\0') and "InitIMG() must be equal to zero");
    assert((InitMixer() != '\0') and "InitMixer() must be equal to zero");
    assert((InitTTF() != '\0') and "InitTTF() must be equal to zero");

    // Check creation fails
    assert((CreateWindow() != '\0') and "CreateWindow() must be equal to zero");
    assert((CreateRenderer() != '\0') and "CreateRenderer() must be equal to zero");

    INFO("SDLSystem - completed");
}

/**
    @brief Runs the SDL library.
*/
void SDLSystem::Run() {
    INFO("SDLSystem - Run() initialized");

    m_isRunning = true;

    LoadCommons();
    SceneManager::GetInstance()->SetCurrentScene("Pre Menu");

    SceneManager::GetInstance()->Start();

    // Update utilities while SDL System is running
    while (m_isRunning) {
        if (!FixFramerate()) {
            continue;
        } else {
            //nothing to do.
        }

        // Clear front buffer.
        SDL_SetRenderDrawColor(m_renderer, red, green, blue, alpha);
        SDL_RenderClear(m_renderer);

        // Draw update changing the back buffer.
        SceneManager::GetInstance()->DrawUpdate();

        CalculateFramerate();
        InputSystem::GetInstance()->UpdateStates();

        // All updates but draw are called here.
        SceneManager::GetInstance()->Update();

        /*
            Update scene manager and collision system based on
            fixed interval of ticks.
        */
        if (SDL_GetTicks() - m_lastFixedUpdate >
            EngineGlobals::fixed_update_interval) {
            SceneManager::GetInstance()->FixedUpdate();
            CollisionSystem::GetInstance()->Update();
            m_lastFixedUpdate = SDL_GetTicks();
        } else {
            //nothing to do.
        }

        // Getting back buffer and sending to front buffer.
        SDL_RenderPresent(m_renderer);
    } // while -- Update utilities while SDL System is nunning

    INFO("SDLSystem - Run() Ending");
}

/**
    @brief Shut down SDL library and its subsystems used in the game.
*/
void SDLSystem::Shutdown() {
    INFO("SDLSystem - Shutdown() Initialized.")

    /*
        Get number of milliseconds since the SDL library initialization
        when it is being shutdown.
    */
    m_gameEndTicks = SDL_GetTicks();

    IMG_Quit();
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();

    INFO("SDLSystem - Shutdown() completed.")
}

/**
    @brief Get the singleton instance of the game.
    @return The singleton instance of the game
*/
SDLSystem *SDLSystem::GetInstance() {
    // Create if there is no instance
    if (!m_instance) {
        m_instance = new SDLSystem();
    } else {
        // nothing to do.
    }

    return m_instance;
}

/**
    @brief Initialize the SDL library and starts its subsystems used in the game.
    @return False if the system initialization fails and true if it's succeed.
*/
bool SDLSystem::InitSDL() {
    INFO("Initializing SDL");

    // Receives 0 if the chosen flags are initialized.
    int initialize = SDL_Init(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO |
               SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER | SDL_INIT_EVENTS);

    // Check initialization fail
    assert((initialize == 0) and "initialize must be equal to zero");

    INFO("SDL Initialized.")
    return true;
}

/**
    @brief Initialize image support.
    @return False if the initialization fails and true if it's succeed.
*/
bool SDLSystem::InitIMG() throw (Exception) {
    INFO("SDLSystem - Initializing IMG");

    // Receives 0 if the chosen flags are initialized
    int flags = IMG_INIT_PNG | IMG_INIT_JPG;
    int initialize = IMG_Init(flags);

    // Check image initialization fail
    assert(((initialize & flags) == flags) and "initialize and flags must have the same status");
    if(initialize != '\0'){
        INFO("SDLSystem - IMG Initialized.");
        return true;
    } else {
        throw Exception("SDLSystem - Initialized nust be different of null.");
    }

}

/**
    @brief Initialize the SDL's sound mixing library.
    @return False if the initialization fails and true if it's succeed.
*/
bool SDLSystem::InitMixer() {
    INFO("SDLSystem - Initializing Mixer");

    // Choose frequency, Uint16 format, channels and chunksize
    int initialize = Mix_OpenAudio(frequency, MIX_DEFAULT_FORMAT, channels, chunksize);

    // Check mixer initialization fail
    assert((initialize == 0) and "initialize must be equal to zero");

    INFO("SDLSystem - Mixer Initialized.");
    return true;
}

/**
    @brief Initialize the SDL's TrueType font rendering library.
    @return False if the initialization fails and true if it's succeed.
*/
bool SDLSystem::InitTTF() {
    INFO("SDLSystem - Initializing TTF");

    int initialize = TTF_Init();

    // Check TTF initialization fail
    assert((initialize == 0) and "initialize must be equal to zero");

    INFO("SDLSystem - TTF Initialized.");
    return true;
}

/**
    @brief Creates a window with the specified title, position and dimensions.
    @return False if the window creation fails and true if it's succeed.
*/
bool SDLSystem::CreateWindow() {
    INFO("SDLSystem - Creating window.");

    m_window = SDL_CreateWindow(EngineGlobals::window_title.c_str(),
                                SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                EngineGlobals::screen_width,
                                EngineGlobals::screen_height, SDL_WINDOW_SHOWN);

    // Check window creation fail
    assert((m_window != nullptr) and "m_window can not be null");

    INFO("SDLSystem - Created window successfully.");
        return true;
}

/**
    @brief Creates a 2D rendering context for the window.
    @return False if the renderer creation fails and true if it's succeed.
*/
bool SDLSystem::CreateRenderer() throw (Exception) {
    INFO("SDLSystem - Creating renderer.");

    // Use hardware acceleration with first rendering driver that support it.
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

    // Check renderer creation fail
    assert((m_renderer != nullptr) and "m_renderer can not be null");

    SDL_SetRenderDrawBlendMode(m_renderer,SDL_BLENDMODE_BLEND);
    INFO("SDLSystem - Created renderer successfully.");
        return true;
}

/**
    @brief Calculates the frame rate.
*/
void SDLSystem::CalculateFramerate() {
    m_currentTicks = SDL_GetTicks();

    // Adjust frame rate based on limit of ticks
    if (m_currentTicks - m_lastFrameTicks >= ticksLimit) {
        m_frameRate = m_frameCounter;
        m_frameCounter = 0;
        m_lastFrameTicks = m_currentTicks;
    } else {
        // nothing to do.
    }
    m_frameCounter++;
}

/**
    @brief Loads necessary game scenes.
*/
void SDLSystem::LoadCommons() throw (Exception) {
    INFO("SDLSystem - Load common initialized");
    // Instantiate and add multiple scenes to scene manager.
    auto endScene1 = new EndScene1();
    if(endScene1 != NULL){
        SceneManager::GetInstance()->AddScene(std::make_pair("EndScene1",
                                                             endScene1));
    } else {
        throw Exception("SDLSystem - endScene1 must be different of null.");
    }

    auto endScene2 = new EndScene2();
    if(endScene2 != NULL){
        SceneManager::GetInstance()->AddScene(std::make_pair("EndScene2",
                                                             endScene2));
    } else {
        throw Exception("SDLSystem - endScene2 must be different of null.");
    }

    auto preMenuScene = new PreMenuScene();
    if(preMenuScene != NULL){
        SceneManager::GetInstance()->AddScene(std::make_pair("Pre Menu",
                                                             preMenuScene));
    } else {
        throw Exception("SDLSystem - preMenuScene must be different of null.");
    }

    auto mainScene = new MainScene();
    if(mainScene != NULL){
        SceneManager::GetInstance()->AddScene(std::make_pair("Main",
                                                             mainScene));
    } else {
        throw Exception("SDLSystem - mainScene must be different of null.");
    }

    auto gameplayScene = new GamePlayScene();
    if(gameplayScene != NULL){
        SceneManager::GetInstance()->AddScene(std::make_pair("Gameplay",
                                                             gameplayScene));
    } else {
        throw Exception("SDLSystem - gameplayScene must be different of null.");
    }

    auto firstBossScene = new FirstBossScene();
    if(firstBossScene != NULL){
        SceneManager::GetInstance()->AddScene(std::make_pair("FirstBossScene",
                                                             firstBossScene));
    } else {
        throw Exception("SDLSystem - firstBossScene must be different of null.");
    }

    INFO("SDLSystem - load commons completed");
}

/**
    @brief Adjusts the Frame rate based in the update rate interval.
    @return False if the calculated interval is less than the update rate
    interval and true if it's not.
*/
bool SDLSystem::FixFramerate() throw (Exception) {
    m_currentFix = SDL_GetTicks();
    if(m_currentFix != '\0'){
        float fixInterval = m_currentFix - m_lastFix;

        // Compare intervals to check the need to fix frame rate
        if (fixInterval < update_rate_interval){
            return false;
        }

        m_lastFix = SDL_GetTicks();
        return true;
    } else {
        throw Exception("SDLSystem - m_currentFix must be different of null.");
    }

}
