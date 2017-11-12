/**
    @file Scene.cpp
    @brief Methods that manages all scenes in the game.
    @copyright LGPL. MIT License.
*/

#include "Engine/Scene.hpp"

#include "Log/log.hpp"

// Constructor.
Scene::Scene() {

}

Scene::~Scene() {

}

/**
    @brief That function is for start the scene of the game.
*/
void Scene::Start() {
    INFO("Scene - Start");
    // Run through the vector of game objects, starting them.
    for (auto object : m_gameObjects) {
        object->Start();
    }
}

/**
    @brief That function is for update the scene of the game.
    Compare the game objects, the begin and end objects. Checks if is
    active and update it.
*/
void Scene::Update() {
    INFO("Scene - Update");
    // Sort and compares the gameobjects by the first element in its vector, and the last one, for update them.
    std::sort(m_gameObjects.begin(), m_gameObjects.end(), CompareGameObjects);
    for (auto it : m_gameObjects) {
        // Check if is active and them update it.
        if (it->active) {
            it->Update();
        } else {
            // Do nothing
        }
    }
}

/**
    @brief That function is for update the draws of the game.
    Compare the game objects, the begin and end objects. Checks if is
    active and update the draws.
*/
void Scene::DrawUpdate() {
    INFO("Scene - Draw Update");
    // Sort and compares the gameobjects by the first element in its vector, and the last one, for update the object's draw.
    std::sort(m_gameObjects.begin(), m_gameObjects.end(), CompareGameObjects);
    for (auto it : m_gameObjects) {
        // Check if is active and them update it.
        if (it->active) {
            it->DrawUpdate();
        } else {
            // Do nothing
        }
    }
}

/**
    @brief that function is for add the gameobjects to the game
    @param[in] GameObject pointer that points to the current gameobject
*/
void Scene::AddGameObject(GameObject *gameObject) {
    INFO("Scene - Add game object");
    //Appends a gameobject to the end of the vector of gameobjects.
    m_gameObjects.push_back(gameObject);
}

void Scene::AddGameObject(std::vector<GameObject *> gameObjects) {
    //Inserts gameobjects in the end-position of the vector of gameobjects.
    m_gameObjects.insert(std::end(m_gameObjects), std::begin(gameObjects),
    std::end(gameObjects));
}

/**
    @brief That function is for fix the updates made before.
    Checks if gameObjects are active and fix the update.
*/
void Scene::FixedUpdate() {
    INFO("Scene - Fix update");
    //Run through the gameobjects vector, and updates the active gameObjects.
    for (auto it : m_gameObjects) {
        // Check if is active and them update it.
        if (it->active) {
            it->FixedUpdate();
        } else {
            // Do nothing
        }
    }
}

/**
    @brief set the state of the scene. Check the states of the scene,
    if is activated, deactivated, hidden and shown and change the state according
    to the state.
    @param[in] state = is the state of the scene.
*/
void Scene::SetState(SceneStates state) {
    INFO("Scene - Set states");
    // Sets the current state scene according to the int constants defined on the SceneStates enum.
    m_currentState = state;
    INFO("[SCENE] " << m_name << " state: " << m_currentState);

    // Check if the state is scene activated and call for Activation.
    if (state == SCENE_ACTIVATED) {
        Activation();
    // Check if the state is scene deactivated and call for Deactivation.
    } else if (state == SCENE_DEACTIVATED) {
        Deactivation();
    // Check if the state is scene hidden and call for Hidden.
    } else if (state == SCENE_HIDDEN) {
        Hidden();
    // Check if the state is scene shown and call for shown.
    } else if (state == SCENE_SHOWN) {
        Shown();
    }
}

/**
    @brief That function is for when the state is activated. So the Scene
    starts.
*/
void Scene::Activation() {
    INFO("Scene - State of Activation");
    OnActivation();
    Start();
}

/**
    @brief That function is for when the state isn't activated.
*/
void Scene::Deactivation() {
    INFO("Scene - State of Deactivation");
    OnDeactivation();
}

/**
    @brief That function is for when the state is shown.
*/
void Scene::Shown() {
    INFO("Scene - State of Shown");
    OnShown();
}

/**
    @brief That function is for when the state is shown.
*/
void Scene::Hidden() {
    INFO("Scene - State of Hidden");
    OnHidden();
}

/**
    @brief Get the name of a scene gameobject.
    @param[in] name - the name of the searched scene.
    @return nullptr if the name doesn't match any gameobject, or the scene name found.
*/
GameObject *Scene::GetGameObject(std::string name) {
    //Run through the gameobjects vector, and get one gameobject by the given name.
    for (auto it : m_gameObjects) {
        if (it->GetName() == name) {
            return it;
        } else {
            // Do nothing
        }
    }
    return nullptr;
}
