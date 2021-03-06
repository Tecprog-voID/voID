/**
    @file ForestActivator3.hpp
    @brief Class that defines methods and attributes for activating the forest script.
    @copyright LGPL. MIT License.
*/

#include "Globals/EngineGlobals.hpp"
#include "Log/log.hpp"

#include "Customs/ForestActivatorScript3.hpp"
#include "Customs/TopCenterLightScript.hpp"
#include "Customs/MapScript.hpp"

const int imageActivatorPositionX = 0;
const int imageActivatorPositionY = 0;
const int imageActivatorWidth = 832;
const int imageActivatorHeight = 64;

const int frameActivatorPositionX = 64;
const int frameActivatorPositionY = 0;
const int frameActivatorWidth = 64;
const int frameActivatorHeight = 64;

const int maxCounter = 13;

const int framesPerSecond = 9;


// Constructor
ForestActivatorScript3::ForestActivatorScript3(GameObject *owner) : Script(owner) {

}

/**
    @brief Initializes the forest script three.
    That function starts the activion of the forest 3. Create the animation,
    position, animator, controller, input and the map.
*/
void ForestActivatorScript3::Start() {
    INFO("ForestActivatorScript3 - Starting");
    // Creates the animator.
    CreateAnimations();

    // Gets the position.
    position = GetOwner()->GetPosition();

    // Gets the animator.
    animator = (Animator *)GetOwner()->GetComponent("Animator");

    input = InputSystem::GetInstance();

    // Gets the game controller.
    gamecontroller = input->GetGameController(0);
    GetOwner()->SetZoomProportion(Vector(0, 0));
    auto map = SceneManager::GetInstance()->GetScene("Gameplay")->
                                            GetGameObject("Map");

    // verify if the map variable is instanced and set zoom.
    if (map) {
        GetOwner()->SetZoomProportion(Vector(map->originalWidth / GetOwner()
                                             ->originalWidth,
                                             map->originalHeight / GetOwner()
                                             ->originalHeight));
    } else {
        // Nothing to do
    }
    INFO("ForestActivatorScript3 - Completed");
}

/**
    @brief That function create the image and animation of the forest three.
*/
void ForestActivatorScript3::CreateAnimations() {
    INFO("ForestActivatorScript3 - Creating animations");
    // Creates the image.
    auto forestactivatorSprite = new Image("assets/image/Forest_activator.png",
                                           imageActivatorPositionX, imageActivatorPositionY,
                                           imageActivatorWidth, imageActivatorHeight);

    // Creates and get the animation.
    auto forestactivatorAnimation = new Animation(GetOwner(),
                                                  forestactivatorSprite);


    for (int counter = 0; counter < maxCounter; counter++) {
        forestactivatorAnimation->AddFrame(new Frame(counter * frameActivatorPositionX,
                                                     frameActivatorPositionY,
                                                     frameActivatorWidth,
                                                     frameActivatorHeight));
    }

    auto forestactivatorAnimation2 = new Animation(GetOwner(),
                                                   forestactivatorSprite);
    forestactivatorAnimation2->AddFrame(new Frame(12 * frameActivatorPositionX,
                                                     frameActivatorPositionY,
                                                     frameActivatorWidth,
                                                     frameActivatorHeight));

    auto forestactivatorAnimator = new Animator(GetOwner());
    forestactivatorAnimation->SetFramesPerSecond(framesPerSecond);
    forestactivatorAnimator->AddAnimation("FOREST ACTIVATOR ANIMATION",
                                          forestactivatorAnimation);
    forestactivatorAnimator->AddAnimation("FOREST ACTIVATOR ANIMATION2",
                                          forestactivatorAnimation2);
    INFO("ForestActivatorScript3 - Animations created");
}

/**
    @brief Updates the components of the forest three.
*/
void ForestActivatorScript3::ComponentUpdate() {

    // Checks if the game animation has not started and starts the animator actives and runned.
    if (!animator->IsPlaying("FOREST ACTIVATOR ANIMATION") and activate == 0
        and runned == false) {

        animator->PlayAnimation("FOREST ACTIVATOR ANIMATION");
        activate = 1;
        runned = true;
    } else {
        // Nothing to do
    }

    // Checks if the game is runned and the animator has not started.
    if (runned and !animator->IsPlaying("FOREST ACTIVATOR ANIMATION")) {
        animator->PlayAnimation("FOREST ACTIVATOR ANIMATION2");
    } else {
        // Nothing to do
    }

    // Checks if the game is runned and initialize the script 4
    if (runned) {
        auto script = (TopCenterLightScript*)SceneManager::GetInstance()
                       ->GetCurrentScene()->GetGameObject("CENTRAL LIGHT 4")
                       ->GetComponent("TopCenterLightScript");

        script->Activate();

        auto map = (MapScript *)SceneManager::GetInstance()->GetCurrentScene()
                   ->GetGameObject("Map")->GetComponent("MapScript");
        map->downWalls[48].m_x = 0;
        map->downWalls[48].m_y = 0;
        map->downWalls[48].m_w = 0;
        map->downWalls[48].m_h = 0;
        map->downWallsOriginal[48].m_x = 0;
        map->downWallsOriginal[48].m_y = 0;
        map->downWallsOriginal[48].m_w = 0;
        map->downWallsOriginal[48].m_h = 0;
    } else {
        // Nothing to do
    }

}

/**
    @brief that function fixs the components updates of the forest three.
*/
void ForestActivatorScript3::FixedComponentUpdate() {

}
