/**
    @file QuitButtonScript.hpp
    @brief Manages the Quit button functions.
    @copyright LGPL. MIT License.
*/

#ifndef __QUIT_BUTTON_SCRIPT__
#define __QUIT_BUTTON_SCRIPT__

#include "Engine/GameObject.hpp"
#include "Engine/SDLSystem.hpp"

#include "Components/Script.hpp"
#include "Components/UIButton.hpp"
#include "Components/UIText.hpp"
#include "Components/UISound.hpp"

#include "Customs/Exception.hpp"

using namespace std;

class QuitButtonScript : public Script {
public:
    QuitButtonScript(GameObject *owner);
    ~QuitButtonScript();
    
private:

    // Replace the component name and return it.
    string GetComponentName() override {
        return "QuitButtonScript";
    };

    void ComponentUpdate() override;

    void Start() override;

    // Sets the QuitButton as a UIButton
    UIButton *m_interactiveButton = nullptr;
};
#endif
