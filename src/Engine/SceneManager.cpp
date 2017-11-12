/**
    @file SceneManager.cpp
    @brief Methods manage game objects.
    @copyright LGPL. MIT License.
*/
#include "Engine/SceneManager.hpp"

#include "Log/log.hpp"

#include <iostream>

SceneManager *SceneManager::m_instance = 0;

SceneManager::SceneManager() {

}

SceneManager::~SceneManager() {
    m_instance = nullptr;
}

SceneManager *SceneManager::GetInstance() {
    INFO("SceneManager - Get Instance");
    // Check for something diferent of instace and instace a new Scene Manager.
    if (!m_instance) {
        m_instance = new SceneManager();
    } else {
        // Do nothing
    }
    return m_instance;
}

void SceneManager::SetCurrentScene(std::string sceneName) {
    INFO("SceneManager - Set currante scene");
    auto found = m_scenes.find(sceneName);
    // Check for found diferent of scenes and set the current state.
    if (found != m_scenes.end()) {
        if (m_currentScene.second != nullptr) {
            m_currentScene.second->SetState(SCENE_HIDDEN);
        } else {
            // Do nothing
        }

        m_currentScene = std::make_pair(found->first, found->second);
        // Check for found diferent of scenes and set current the state.
        if (m_currentScene.second->GetState() == SCENE_DEACTIVATED) {
            m_currentScene.second->SetState(SCENE_ACTIVATED);
        } else {
            // Do nothing
        }
        m_currentScene.second->SetState(SCENE_SHOWN);
    }
}

// Get the current scene name.
std::string SceneManager::GetCurrentSceneName() {
    INFO("SceneManager - Get currante scene name");
    return m_currentScene.second->GetName();
}

void SceneManager::AddScene(std::pair<std::string, Scene *> scenePair) {
    INFO("SceneManager - Add scene");
    scenePair.second->SetName(scenePair.first);
    m_scenes.insert(scenePair);
}

void SceneManager::Start() {
    INFO("SceneManager - Start");
    for (auto scene : m_scenes) {
        // Check for the state equal to deactivated and active it.
        if (scene.second->GetState() == SCENE_DEACTIVATED) {
            scene.second->SetState(SCENE_ACTIVATED);
        } else {
            // Do nothing
        }
    }
}

void SceneManager::Update() {
    INFO("SceneManager - Update");
    // Check the current scene and update.
    if (m_currentScene.second) {
        m_currentScene.second->Update();
    } else {
        // Do nothing
    }
}

void SceneManager::DrawUpdate() {
    INFO("SceneManager - Draw Update");
    // Check the current scene and update the draw.
    if (m_currentScene.second) {
        m_currentScene.second->DrawUpdate();
    } else {
        // Do nothing
    }
}

void SceneManager::FixedUpdate() {
    INFO("SceneManager - Fixed update");
    // Check the current scene and fix the update.
    if (m_currentScene.second) {
        m_currentScene.second->FixedUpdate();
    } else {
        // Do nothing
    }
}

Scene *SceneManager::GetScene(std::string name) {
    INFO("SceneManager - Get Scene");
    for (auto pair : m_scenes) {
        if (pair.first == name) {
            return pair.second;
        } else {
            // Do nothing
        }
    }
    ERROR("Looking for " << name << " scene which does not exist");
    return nullptr;
}
