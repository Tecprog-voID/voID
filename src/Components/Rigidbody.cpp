/**
    @file Rigidbody.cpp
    @brief Methods that manages non-passing through elements in game.
    @copyright LGPL. MIT License.
*/

#include "Components/Rigidbody.hpp"
#include "Globals/ComponentTypes.hpp"
#include "Math/Vector.hpp"

#include "Log/log.hpp"

#include <cassert>


/**
    @brief Initializes RectangleCollider instance.
    @param[in] GameObject *owner - owns the component.
    @param[in] C_PHYSICS - physics component.
*/
Rigidbody::Rigidbody(GameObject *owner) : Component(owner, C_PHYSICS) {
    assert((owner != NULL) and "the owner must be equal to NULL");
}

/**
    @brief Updates the position of a fixed component, based on it velocity.
*/
void Rigidbody::FixedComponentUpdate() {
    // Check for gravity, and if exists, sets its force on a vector.
    if (m_gravity) {
        GetOwner()->AddVelocity(Vector(0, m_gravityForce));
    }
    else {
       // Do nothing
    }

    // Sets the x,y positions in the owner component of the gameobject, according to its velocity.
    auto velocity  = GetOwner()->GetVelocity();
    GetOwner()->GetPosition()->m_x += velocity.m_x;
    GetOwner()->GetPosition()->m_y += velocity.m_y;
}
