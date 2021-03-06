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

    void SetColor(int red, int green, int blue, int alpha);

    inline void SetWidth(int width) {
        this->m_width = width;
    };
    inline int GetWidth() {
        return m_width;
    };

private:

    // Replace the component name and return it.
    virtual string GetComponentName() override {
        return "RectangleRenderer";
    };

    virtual void ComponentUpdate() throw (Exception);

    // Width and height of the rectangle
    int m_width = 0;
    int m_height = 0;

    // Specifics values of the colors of the rectangle
    int m_red = 0;
    int m_green = 0;
    int m_blue = 255;
    int m_alpha = 255;

    // Vector position of the rectangle
    Vector m_offset = Vector(0, 0);
};
#endif
