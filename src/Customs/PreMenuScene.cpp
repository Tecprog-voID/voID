/**
    @file PreMenuScene.cpp
    @brief Reunites the animations that are shown before the main menu appears.
    @copyright MIT License.
*/
#include "Customs/PreMenuScene.hpp"
#include "Customs/SdlLogoScript.hpp"
#include "Customs/UnbLogoScript.hpp"
#include "Customs/ZebraLogoScript.hpp"
#include "Customs/ControleLogoScript.hpp"
#include "Log/log.hpp"

#include <cassert>

/**
    @brief Tells what happens when the PreMenuScene is activated.
*/
void PreMenuScene::OnActivation() {
    // Create logos on activation.
    CreateLogoSdl();
    CreateLogoUnb();
    CreateLogoControle();
    CreateLogoZebra();
}

void  PreMenuScene::OnDeactivation() {}

void  PreMenuScene::OnShown() {}

void  PreMenuScene::OnHidden() {}

/**
    @brief Shows the Sdl Logo.
*/
void PreMenuScene::CreateLogoSdl() {
    INFO("PreMenuScene CreateLogoSdl() - initializing");
    // Creates the SDL LOGO gameobject.
    auto sdl_Logo = new GameObject("SDL LOGO", new Vector(0,0),1024,800,1);

    // Renderer.
    new SdlLogoScript(sdl_Logo);

    //Appends the SDL LOGO gameobject to the end of the vector of gameobjects.
    AddGameObject(sdl_Logo);
    INFO("PreMenuScene CreateLogoSdl() - completed");
}

/**
    @brief Shows the UnB Logo.
*/
void PreMenuScene::CreateLogoUnb() {
    INFO("PreMenuScene CreateLogoUnb() - initializing");
    // Creates the UNB LOGO gameobject.
    auto unb_Logo = new GameObject("UNB LOGO", new Vector(0,0),1024,800,1);
    // Renderer.
    new UnbLogoScript(unb_Logo);

    //Appends the UNB LOGO gameobject to the end of the vector of gameobjects.
    AddGameObject(unb_Logo);
    INFO("PreMenuScene CreateLogoUnb() - completed");
}

/**
    @brief Shows the video game controller animation.
*/
void PreMenuScene::CreateLogoControle() {
    INFO("PreMenuScene CreateLogoControle() - initializing");
    // Creates the CONTROLE LOGO gameobject.
    auto controle_Logo = new GameObject("CONTROLE     LOGO",
                                        new Vector(0,0),1024,800,1);
    // Renderer.
    new ControleLogoScript(controle_Logo);

    /*
    Appends the CONTROLE LOGO gameobject to the end of the vector of
    gameobjects.
    */
    AddGameObject(controle_Logo);
    INFO("PreMenuScene CreateLogoControle() - completed");
}

/**
    @brief Shows the Zebra Logo.
*/
void PreMenuScene::CreateLogoZebra() {
    INFO("PreMenuScene CreateLogoZebra() - initializing");
    // Creates the ZEBRA LOGO gameobject.
    auto zebra_Logo = new GameObject("ZEBRA LOGO", new Vector(0,0),1024,800,1);
    // Renderer.
    new ZebraLogoScript(zebra_Logo);

    //Appends the ZEBRA LOGO gameobject to the end of the vector of gameobjects.
    AddGameObject(zebra_Logo);
    INFO("PreMenuScene CreateLogoZebra() - completed");
}
