/**
    @file GameObject.cpp
    @brief Methods manage game objects.
    @copyright LGPL. MIT License.
*/

#include "Engine/GameObject.hpp"

#include "Log/log.hpp"

/**
    @brief Initializes GameObject instance.
    @param[in] name - gameobject name.
    @param[in] position - the position of a gameobject.
    @param[in] width - width of the gameobject, type int.
    @param[in] height - height of the gameobject, type int.
    @param[in] layer - The layer of the component, type unsigned 8-bit integer.
*/
GameObject::GameObject(std::string name, Vector *position,
    int width, int height, Uint8 layer) {
    m_name = name;
    m_position = position;
    m_width = width;
    m_height = height;
    m_componentLayer = layer;
    m_velocity = new Vector(0, 0);
    originalWidth = width;
    originalHeight = height;
}

// Destructor.
GameObject::~GameObject() {
    delete m_position;
    delete m_position;
}

/**
    @brief that function starts the game. Checks if the key is on begins and
    if the key is different of the end.
*/
void GameObject::Start() {
     INFO("GameObject - Start");
    // Run through the map of components, starting each one of them.
    for (auto m_key = m_components.begin(); m_key != m_components.end(); m_key++) {
        for (auto component : m_key->second) {
            component->Start();
    }
  }
}

/**
    @brief that function updates all the components of the game objects.
*/
void GameObject::Update() {
    INFO("GameObject - Update");
    ComponentsUpdate();
}

/**
    @brief that function updates all the draw components. Find the draws, check
    if is active and update the component.
*/
void GameObject::DrawUpdate() {
    INFO("GameObject - Update the Draw");
    // Search for the component type(DRAW) on the components vector, and set it.
    auto m_it = m_components.find(C_DRAW);

    // If the component type wasn't found on the vector, updates the component.
    if (m_it != m_components.end()) {
        for (auto component : m_it->second) {
            if (component->m_active) {
                component->Update();
            } else {
                // Do nothing
            }
        }
    } else {
        // Do nothing
    }
}

/**
    @brief that function updates all the physics components. Find the pyhsics
    components, check if is active and update the component.
*/
void GameObject::PhysicsUpdate() {
    INFO("GameObject - Physics Update");
    // Search for the component type(PHYSICS) on the components vector, and set it.
    auto m_it = m_components.find(C_PHYSICS);

    // If the component type wasn't found on the vector, updates the component.
    if (m_it != m_components.end()) {
        for (auto component : m_it->second) {
            if (component->m_active) {
                component->Update();
            } else {
                // Do nothing
            }
        }
    } else {
        // Do nothing
    }
}

/**
    @brief that function updates all the general components. Find the common, check
    if is active and update the component.
*/
void GameObject::ComponentsUpdate() {
    INFO("GameObject - Components Update");
    // Search for the component type(COMMON) on the components vector, and set it.
    auto m_it = m_components.find(C_COMMON);

    // If the component type wasn't found on the vector, updates the component.
    if (m_it != m_components.end()) {
        for (auto m_component : m_it->second) {
            if (m_component->m_active) {
                m_component->Update();
            } else {
                // Do nothing
            }
         }
    } else {
        // Do nothing
    }
}

/**
    @brief that function is for add the components to the game
    @param[in] Component pointer that points to the current component.
*/
void GameObject::AddComponent(Component *component) {
    INFO("GameObject - Add component");
    // Set variable 'type' according to the type of the current component.
    auto m_type = component->GetType();
    auto m_it = m_components.find(m_type);

    // Check and insert the component type in the end of the components vector.
    if (m_it != m_components.end()) {
        m_it->second.push_back(component);
    } else {
        /*
            Extends the components vector size by one, by inserting a new element at type's position.
            Then inserts type's position in the end of components vector.
        */
        m_components.emplace(m_type, std::vector<Component *>());
        m_components.at(m_type).push_back(component);
    }
}

/**
    @brief that function is for add a component to the game
    @param[in] Component pointer that points to the current component.
*/
void GameObject::AddComponent(std::vector<Component *> components) {
    // Inserts the current component type in the end of the components vector by calling AddComponent.
    for (auto m_it : components) {
        AddComponent(m_it);
    }
}


/**
    @brief Get the name of a gameobject component.
    @param[in] name - the name of the searched scene.
    @return nullptr if the name doesn't match any gameobject, or the component name.
*/
Component *GameObject::GetComponent(std::string name) {
    INFO("GameObject - Update");
    // Run through the map of components, searching for the current given name.
    for (auto m_key = m_components.begin(); m_key != m_components.end(); m_key++) {
        for (auto m_value : m_key->second) {
            if (m_value->GetComponentName() == name) {
                return m_value;
            } else {
                // Do nothing
            }
        }
    }
 // INFO("Looking for null component " << name);
    return nullptr;
}
/**
    @brief that function is for fix the updates that were done before.
*/
void GameObject::FixedUpdate() {
    INFO("GameObject - Fix the Update");
    /*
        Run through the map of components, and puts them in a struct that holds
        two objects of arbitrary type. Then updates it with the FixedComponent and PhysicsUpdate();.
    */
    for (auto m_key = m_components.begin(); m_key != m_components.end(); m_key++) {
        for (auto m_value : m_key->second) {
            m_value->FixedComponentUpdate();
        }
    }
  PhysicsUpdate();
}

/**
    @brief that function is for set the size based on width and height.
    @param[in] width and height in centimeters.
*/
void GameObject::SetSize(int width, int height) {
    INFO("GameObject - Set the size");
    // Sets the gameobject width and height with the given values.
    m_width = width;
    m_height = height;
}

bool GameObject::operator<(const GameObject &go) const {
    return m_componentLayer < go.m_componentLayer;
}

/**
    @brief that function is for add velocity to the game.
    @param[in] Vector velocity points for the variables x and y (horizontal and
    vertical)
*/
void GameObject::AddVelocity(Vector velocity) {
    INFO("GameObject - Add velocity");
    // Sets the gameobject velocity vector with the given values.
    m_velocity->m_x += velocity.m_x;
    m_velocity->m_y += velocity.m_y;
}

/**
    @brief Get the velocity of a gameobject.
    @return the vector of gameobject's velocity.
*/
Vector GameObject::GetVelocity() {
    INFO("GameObject - Get the velocity");
    return *m_velocity;
}

/**
    @brief that function is for add collisions to the game.
    @param[in] GameObject pointer that points to the current gameobject.
*/
void GameObject::AddCollision(GameObject *gameobject) {
    INFO("GameObject - Add collision");
    // Inserts the current gameobject collision in the end of the gameobject's collisions vector.
    m_colliding.push_back(gameobject);
}

/**
    @brief that function is for clear the collisions tha were made before.
*/
void GameObject::ClearCollisions() {
    INFO("GameObject - Clear the collisions");
    m_colliding.clear();
 }

/**
    @brief Get the gameobject's collisions.
    @return the vector of gameobject's collisions.
*/
std::vector<GameObject *> GameObject::GetCollisions() {
    INFO("GameObject - Get collisions");
    return m_colliding;
}
