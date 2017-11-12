#include "Customs/AudioController.hpp"
#include "Log/log.hpp"

/**
    @file AudioController.cpp
    @brief Methods that manages all game's audio.
    @copyright LGPL. MIT License.
*/

AudioController *AudioController::m_instance = nullptr;

/**
    @brief Checking the current game's audio state.
    @return m_instance.
*/
AudioController *AudioController::GetInstance() {
    // Singleton class
    INFO("AudioController - getting instance");

    // If the m_instance is not initialized, intializes it.
    if (!m_instance){
        m_instance = new AudioController();
    } else {
        // Do nothing
    }

    INFO("AudioController - got instance");
    return m_instance;
}

//Constructor void
AudioController::AudioController() {
}

/**
    @brief Initializes a sound object.
    @param[in] sound - the UI sound component.
*/
void AudioController::AddAudio(UISound *sound) {
    INFO("AudioController - adding sound");

    // Add
    m_sounds.push_back(sound);
    INFO("AudioController - added sound");
}

/**
    @brief Plays pre existent sounds.
    @param[in] sound - the name of the sound component.
    @param[in] loops - the number of times that the audio will play.
*/
void AudioController::PlayAudio(string name, int loops){
    INFO("AudioController - playing sound");

    for (auto sound : m_sounds) {
        /*
        If the message is correspondent to the sound component name, plays
        the sound.
        */
        if(sound->GetMessage() == name) {
            sound->Play(loops, -1);
        }
    }
    INFO("AudioController - played sound");
}

/**
    @brief Stops a current playing sound.
    @param[in] sound - the name of the sound component.
*/
void AudioController::StopAudio(string name){
    INFO("AudioController - stopping sound");

    for (auto sound : m_sounds) {
        /*
        If the message is correspondent to the sound component name, stops
        the sound.
        */
        if(sound->GetMessage() == name) {
            sound->Stop(-1);
        }
    }
    INFO("AudioController - stopped sound");
}

/**
    @brief Pause a current playing sound.
    @param[in] sound - the name of the sound component.
*/
void AudioController::PauseAudio(string name){
    INFO("AudioController - pausing audio");

    for (auto sound : m_sounds) {
        /*
        If the message is correspondent to the sound component name, stops
        the sound.
        */
        if(sound->GetMessage() == name){
            sound->Stop(-1);
        } else {
            // Do nothing
        }
    }
    INFO("AudioController - paused audio");
}
