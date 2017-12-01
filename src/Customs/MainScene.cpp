/**
    @file MainScene.cpp
    @brief Methods that manages the main scene of the game.
    @copyright LGPL. MIT License.
*/

#include "Customs/MainScene.hpp"
#include "Customs/MenuAnimationScript.hpp"
#include "Log/log.hpp"


const int middlePosition = 2;

MainScene::MainScene() {

}

/**
    @brief that function is for when the state is actived, and create the logo,
    playButton, QuitButton, the music and animation.
*/
void MainScene::OnActivation() {
    INFO("MainScene - On Activation");
    // On activation, gets the screen width and height to middle position the basic components of the game.
    m_widthMiddle = EngineGlobals::screen_width / middlePosition;
    m_heightMiddle = EngineGlobals::screen_height / middlePosition;
    CreateLogo();
    CreatePlayButton();
    CreateQuitButton();
    CreateMusic();
    CreateAnimation();

}

/**
    @brief that function is for when the state is deactived and because of that,
    nothing is created.
*/
void MainScene::OnDeactivation() {
    INFO("MainScene - On Deactivation");
}

/**
    @brief that function is for when the state is on show and because of that,
    nothing is created.
*/
void MainScene::OnShown() {
    INFO("MainScene - On Shown");
}

/**
    @brief that function is for when the state is on hidden and because of that,
    nothing is created.
*/
void MainScene::OnHidden() {
    INFO("MainScene - On Hidden");
}


/**
    @brief that function create the logo of the game. Select the place of the logo,
    then create the logo as a game object. After create the logo image and renderer it.
*/
void MainScene::CreateLogo() {
    INFO("MainScene - Create Logo");
    /*
        Setting and render the game logo image in the middle of the screen,
        in a gameobject.
    */
    auto m_logo = new GameObject("Logo", new Vector(-30,0), 1024, 800,1);

    auto logoImage = new Image("assets/image/introduction/logo.png", 0, 0, 311, 256);
    new Renderer(m_logo, logoImage);

    AddGameObject(m_logo);
}

/**
    @brief that function create the play button for the game starts. Set the place of
    the button, create the "Play" as a GameObject, the text of it, the button and the sound.
*/
void MainScene::CreatePlayButton() {
    INFO("MainScene - Create Play Button");
    /*
        Position the play button and its text, by setting the new gameobject in the
        middle position of the screen, and instantiates the sound of the button.
    */
    int xMiddle = EngineGlobals::screen_width / middlePosition - 100;
    auto m_play = new GameObject("Play", new Vector(xMiddle, 400), 200, 100,1);
    new UIText(m_play, "Play", "assets/Fonts/mini-pixel-7/mini-pixel-7.ttf",
                               200, 255, 255, 255, 150, 1);
    new UIButton(m_play);
    new UISound(m_play, "playSound", "assets/Audio/Button/MusicButton1.wav", false, false);
    new PlayButtonScript(m_play);
    AddGameObject(m_play);
}

/**
    @brief that function create the play button for quit the game. Set the place of
    the button, create the "Quit" as a GameObject, the text of it, the button and the sound.
*/
void MainScene::CreateQuitButton() {
    INFO("MainScene - Create Quit Button");
    /*
        Position the quit button and its text, by setting the new gameobject in the    //CreateBackground();
    //CreateGamemodes();
        middle position of the screen, and instantiates the sound of the button.
    */
    int xMiddle = EngineGlobals::screen_width / middlePosition - 100;
    auto m_quit = new GameObject("Quit", new Vector(xMiddle, 500), 200, 100, 1);
    new UIText(m_quit, "Quit", "assets/Fonts/mini-pixel-7/mini-pixel-7.ttf",
                               200, 255, 255, 255, 150, 1);
    new UIButton(m_quit);
    new UISound(m_quit, "playSound", "assets/Audio/Button/MusicButton1.wav", false, false);
    new QuitButtonScript(m_quit);
    AddGameObject(m_quit);
}

/**
    @brief that function create the animation of the main scene of the game. Add
    the backgroundAnimation as a GameObject and the backgroundAnimationScript as a
    MenuAnimationScript.
*/
void MainScene::CreateAnimation() {
    INFO("MainScene - Create Animation");
    // Create a gameobject for the background animation and its script, and a vector with its positions.
    auto m_BackgroundAnimation = new GameObject("BackgroundAnimation", new Vector(0 ,0), 1024, 800, 0);
    new MenuAnimationScript(m_BackgroundAnimation);
    AddGameObject(m_BackgroundAnimation);
}


/**
    @brief that function create the music theme of the game. Add the music as a
    GameObject and the themeMusic as a UISound.
*/
void MainScene::CreateMusic() {
    INFO("MainScene - Create Music");
    // Create a gameobject for the game music, and a vector with its positions.
    auto m_music = new GameObject("Music", new Vector(200, 200), 200, 100);
    // Instantiate the UI sound, and define its states.
    new UISound(m_music, "Music", "assets/Audio/Menu/Menu.ogg", false, true);
    // Add the whole music instantiated in a vector of gameobjects.
    AddGameObject(m_music);
}
