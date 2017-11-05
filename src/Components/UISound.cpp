/**
    @file UISound.cpp
    @brief Creates and plays sounds during the game.
    @copyright MIT License.
*/

#include "Components/UISound.hpp"
#include "Log/log.hpp"


UISound::UISound(GameObject *owner, string message, string audioPath,
                 bool isMusic, bool playOnStart)
                 : Component (owner, C_COMMON) {
    INFO("UISound UISound() - initializing")
    m_message = message;
    m_audioPath = audioPath;
    m_isMusic = isMusic;
    m_playOnStart = playOnStart;
    OnPropertyChange();
    INFO("UISound UISound() - completed")
}


void UISound::Start() {
    INFO("UISound Start() - completed")
}

/**
 @brief Avoids the sound to play on start while updating a component.
 */
void UISound::ComponentUpdate() {
    INFO("UISound ComponentUpdate() - initializing")
    // Check if the sound should play in the start.
    if (m_playOnStart) {
        // Play the sound and disable the play on the start.
        Play(playForever, emptyChannel);
        m_playOnStart = false;
    } else {
        // Do nothing
    }
    INFO("UISound ComponentUpdate() - completed")
}

/**
 @brief Do nothing.
 */
void UISound::FixedComponentUpdate() {
    INFO("UISound FixedComponentUpdate() - completed")
}

/**
 @brief Handles what happens whenever a property changes.
 @details If the audio file is found, it plays, else, an error message is
 shown.
 */
void UISound::OnPropertyChange() {
    INFO("UISound OnPropertyChange() - initializing")
    // Check if the audio file is a music or a sound.
    switch (m_isMusic) {
        // Loads the music file.
        case true:
        m_music = Mix_LoadMUS(m_audioPath.c_str());
        // Verify if the music exists.
        if( m_music == NULL) {
            printf("Failed to load music! SDL_mixer Error: %s\n",
            Mix_GetError());
        } else {
            // Do nothing
        }
        break;

        // Loads the sound effect file.
        case false:
        m_sound = Mix_LoadWAV(m_audioPath.c_str());
        // Verify if the sound exists.
        if (m_sound == NULL) {
            printf("Failed to load sound effect! SDL_mixer Error: %s\n",
            Mix_GetError());
        } else {
            // Do nothing
        }
        break;
    }
    INFO("UISound OnPropertyChange() - completed")
}

/**
 @brief Play a audio file, with or without loop.
 @param loops.
 @param channel.
 */
void UISound::Play(int loops, int channel) {
    INFO("UISound Play() - initializing")
    // Plays the file if is a music.
    if (m_isMusic) {
        Mix_PlayMusic(m_music, loops);
        // Plays the file if is a sound effect.
    } else {
        Mix_PlayChannel(channel, m_sound, loops);
    }
    INFO("UISound Play() - completed")
}

/**
 @brief Stops the sound either if it's a music or not.
 @param channel.
 */
void UISound::Stop(int channel) {
    INFO("UISound Stop() - initializing")
    // Stops the music.
    if (m_isMusic) {
        Mix_HaltMusic();
        // Stops the sound effect.
    } else {
        Mix_HaltChannel(channel);
    }
    INFO("UISound Stop() - completed")
}

/**
 @brief Pauses the sound either if it's a music or not.
 @param channel.
 */
void UISound::Pause(int channel) {
    INFO("UISound Pause() - initializing")
    // Pauses the music.
    if (m_isMusic) {
        Mix_PauseMusic();
        // Pauses the sound effect.
    } else {
        Mix_Pause(channel);
    }
    INFO("UISound Pause() - completed")
}
