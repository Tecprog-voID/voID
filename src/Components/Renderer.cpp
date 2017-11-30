/**
    @file Renderer.cpp
    @brief Manages renderings of images on the screen.
    @copyright LGPL. MIT License.
*/

#include "Engine/GameObject.hpp"
#include "Engine/GraphicsSystem.hpp"

#include "Components/Renderer.hpp"

#include "Customs/Exception.hpp"

#include "Globals/ComponentTypes.hpp"
#include "Log/log.hpp"

#include <math.h>

const double pi = 3.1415;
const unsigned int fullAngle = 360;
const unsigned int straightAngle = 180;

/**
    @brief Update the images informations on the screen.
*/
void Renderer::ComponentUpdate() {
    // Draw the component.
    std::pair<int, int> sizes =
        std::make_pair(GetOwner()->GetWidth(), GetOwner()->GetHeight());
        GraphicsSystem::GetInstance()->Draw(m_image, m_position, sizes);
}

/**
    @brief  Constructor for the class Renderer.
    @param[in] owner - Owns the component.
    @param[in] img
*/
Renderer::Renderer(GameObject *owner, Image *image) : Component(owner, C_DRAW) {

    // Set the local variable
    m_image = image;

    m_position = GetOwner()->GetPosition();

    // Detect if the arrival image is empty
    if (!m_image) {
        ERROR("Null image on renderer");
    } else {
        // nothing to do.
    }
}

/**
    @brief Destructor for the class Renderer.
*/
Renderer::~Renderer() {
    // Destructor
    delete m_image;
}

/**
    @brief Do nothing.
*/
void Renderer::Start() {
    INFO("Renderer - start");
}

/**
    @brief Rotate the image towards the calculated angle.
    @param[in] point
*/
void Renderer::RotateTowards(Vector *point) throw (Exception) {
    INFO("Renderer - Initializing rotate towards");
    // Calculate arc tangent in degrees.
    double angles = 0.0;
    angles = atan2(point->m_y - m_position->m_y, point->m_x - m_position->m_x);

    if(angles != '\0'){
        angles = angles * straightAngle / pi;

        // Keep angles in 0 to 360 range
        if (angles < 0) {
            angles = fullAngle - (-angles);
        }

        Rotate(angles);
        INFO("Renderer - rotate towards initialized");
    } else {
        throw Exception("Renderer - angles must be different of null.");
    }

}

/**
    @brief Rotate the image.
    @param[in] angles - Angles of the image.
*/
void Renderer::Rotate(double angles) {
    GetImage()->Rotate(angles);
}
