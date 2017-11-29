#include "Customs/CentralLightScript1.hpp"
#include "Customs/ForestActivatorScript2.hpp"
#include "Log/log.hpp"
#include "Globals/EngineGlobals.hpp"

#include <cassert>

const int quantityFrame = 13;
const int framePerSecond = 9;


ForestActivatorScript2::ForestActivatorScript2(GameObject *owner) : Script(owner) {
    assert((owner != NULL) and "the owner must be equal to NULL");
}

/**
    @brief that function starts the activion of the forest 2. Create the animation,
    position, animator, controller, input and the map.
*/
void ForestActivatorScript2::Start() {
    INFO("ForestActivatorScript - Start");
    /*
        Create animations, define position, animator through gameobject.
        Defines map and sets its zoom proportion vector using width and height.
        Sets the joystick.
    */
    CreateAnimations();
    position = GetOwner()->GetPosition();
    animator = (Animator *)GetOwner()->GetComponent("Animator");
    input = InputSystem::GetInstance();
    gamecontroller = input->GetGameController(0);
    GetOwner()->SetZoomProportion(Vector(0, 0));
    auto m_map = SceneManager::GetInstance()->GetScene("Gameplay")->GetGameObject("Map");
    // Check for map, and if exists, sets its map on a vector.
    if (m_map) {
        GetOwner()->SetZoomProportion(Vector(m_map->originalWidth/GetOwner()->originalWidth,m_map->originalHeight/GetOwner()->originalHeight));
    } else {
        // Do nothing
    }
}

/**
    @brief that function create the animations for the forest. Create the image of
    the forest and the animation of the forest.
*/
void ForestActivatorScript2::CreateAnimations(){
    INFO("ForestActivatorScript - Create Animations");

    // Instantiating forest activator Sprite image and its position.
    auto m_forestactivatorSprite = new Image("assets/Forest_activator.png", 0, 0,832, 64);

    // Instantiating forest activator animation by gameobject components, and setting its image and frame.
    auto m_forestactivatorAnimation = new Animation(GetOwner(), m_forestactivatorSprite);
    for (int counter = 0; counter < quantityFrame; counter++) {
        m_forestactivatorAnimation->AddFrame(new Frame(counter * 64, 0, 64, 64));
    }

    // Instantiating forest activator animation2, by gameobject, and setting its image and animation.
    auto m_forestactivatorAnimation2 = new Animation(GetOwner(), m_forestactivatorSprite);
    m_forestactivatorAnimation2->AddFrame(new Frame(12 * 64, 0, 64, 64));

    // Instantiating animator, setting its animation and frames per second.
    auto m_forestactivatorAnimator = new Animator(GetOwner());
    m_forestactivatorAnimation->SetFramesPerSecond(framePerSecond);
    //forestactivatorAnimation2->SetFramesPerSecond(1);
    m_forestactivatorAnimator->AddAnimation("FOREST ACTIVATOR ANIMATION", m_forestactivatorAnimation);
    m_forestactivatorAnimator->AddAnimation("FOREST ACTIVATOR ANIMATION2", m_forestactivatorAnimation2);
}

/**
    @brief that function updates the components of the forest two.
*/
void ForestActivatorScript2::ComponentUpdate() {
    INFO("ForestActivatorScript - Component Update");
    // Check the animator's state, and ifs true, play animation and activate it.
    if (!animator->IsPlaying("FOREST ACTIVATOR ANIMATION") and activate==0 and runned==false) {
        animator->PlayAnimation("FOREST ACTIVATOR ANIMATION");
        activate=1;
        runned = true;
    } else {
        // Do nothing
    }

    // Check if runned and something diferent of animator is playing and active the animattion of the forest.
    if (runned and !animator->IsPlaying("FOREST ACTIVATOR ANIMATION")) {
        animator->PlayAnimation("FOREST ACTIVATOR ANIMATION2");
    } else {
        // Do nothing
    }

    // Checking script running state, and ifs true, activate the script.
    if (runned) {
        auto script = (CentralLightScript1*)SceneManager::GetInstance()->
                       GetCurrentScene()->GetGameObject("CENTRAL LIGHT 1")->
                       GetComponent("CentralLightScript1");
        script->Activate();
    } else {
        // Do nothung
    }
}

/**
    @brief that function fixs the components updates of the forest two.
*/
void ForestActivatorScript2::FixedComponentUpdate() {
    INFO("ForestActivatorScript - Fixed Component Update");
}
