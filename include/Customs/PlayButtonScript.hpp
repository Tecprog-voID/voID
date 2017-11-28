/**
    @file PlayButtonScript.hpp
    @brief Manages the Play button functions.
    @copyright LGPL. MIT License.
*/

#ifndef __PLAY_BUTTON_SCRIPT__
#define __PLAY_BUTTON_SCRIPT__

#include "Engine/GameObject.hpp"

#include "Components/Script.hpp"
#include "Components/UIButton.hpp"
#include "Components/UIText.hpp"
#include "Components/UISound.hpp"
#include "Customs/Exception.hpp"

using namespace std;

class PlayButtonScript : public Script {
public:
    PlayButtonScript(GameObject *owner);
    ~PlayButtonScript();

private:

    // Replace the component name and return it.
    string GetComponentName() override {
        return "PlayButtonScript";
    };

    void ComponentUpdate() throw (Exception);

    void Start() override;

    // Set the Play button as a UIButton
    UIButton *m_interactive_button = nullptr;
};
#endif
