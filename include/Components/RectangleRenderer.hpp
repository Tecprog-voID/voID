/**
    @file RectangleRenderer.hpp
    @brief Manages the rectangles of the game.
    @copyright LGPL. MIT License.
*/

#ifndef __RECTANGLE_RENDERER__
#define __RECTANGLE_RENDERER__

#include "Engine/Component.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/GraphicsSystem.hpp"

#include "Customs/Exception.hpp"

#include "Math/Vector.hpp"

#include <string>

using namespace std;

class RectangleRenderer : public Component {
public:

    RectangleRenderer(GameObject *owner, Vector offset, int width, int height);
    ~RectangleRenderer();

    void SetColor(unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha);

    inline void SetWidth(unsigned int width) {
        this->m_width = width;
    };
    inline unsigned int GetWidth() {
        return m_width;
    };

private:

    // Replace the component name and return it.
    virtual string GetComponentName() override {
        return "RectangleRenderer";
    };

    virtual void ComponentUpdate() throw (Exception);

    // Width and height of the rectangle
    unsigned int m_width = 0;
    unsigned int m_height = 0;

    // Specifics values of the colors of the rectangle
    unsigned int m_red = 0;
    unsigned int m_green = 0;
    unsigned int m_blue = 255;
    unsigned int m_alpha = 255;

    // Vector position of the rectangle
    Vector m_offset = Vector(0, 0);
};
#endif
