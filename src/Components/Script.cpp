/**
    @file Script.cpp
    @brief Class responsible for starting the game, creating an owner.
    @copyright LGPL. MIT License.
*/
#include "Components/Script.hpp"
#include <cassert>

Script::Script(GameObject *owner) : Component(owner, C_COMMON) {
    assert((owner != NULL) && "The owner must be equal to NULL");
}
