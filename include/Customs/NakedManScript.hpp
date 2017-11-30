/**
    @file NakedManScript.hpp
    @brief Manages the functions of the player in the game.
    @copyright LGPL. MIT License.
*/

#ifndef __NAKED_MAN_SCRIPT__
#define __NAKED_MAN_SCRIPT__

#include "Engine/InputSystem.hpp"
#include "Engine/SceneManager.hpp"
#include "Engine/Timer.hpp"
#include "Engine/CameraSystem.hpp"
#include "Engine/GameController.hpp"

#include "Components/Animator.hpp"
#include "Components/Script.hpp"
#include "Components/UIText.hpp"
#include "Components/RectangleCollider.hpp"
#include "Customs/PlayerAttackScript.hpp"
#include "Customs/HitScript.hpp"
#include "Customs/Exception.hpp"

class NakedManScript : public Script {

    public:

        NakedManScript(GameObject *owner);
        ~NakedManScript();

        // Initicial values of the player informations in the game
        bool lockplayerMovements = false;
        bool gameControllerActivated = false;
        bool activated = true;
        int bulletNumber = 10;
        int life = 100;
        float gameControllerAngle = 0;

    private:

        // Replace the component name and return it.
        std::string GetComponentName() override {
            return "NakedManScript";
        };

        void FixedComponentUpdate() override;

        void Start() throw (Exception);

        char GetMovement() {
            return movements;
        };

        bool zoom = true;

        bool bossFight = false;

        // Player's walk
        bool walking = false;

        unsigned int bulletController = 0;

        unsigned int dashController = 0;

        InputSystem *input = nullptr;
        GameController *game_controller = nullptr;
        Animator *animator = nullptr;
        Vector *position = nullptr;

        // Player's speeds
        float walkSpeed = 15;
        float fixedWalkSpeed = 15;

        unsigned int movements = 0;

        // X and Y positions of dead zone
        unsigned int deadzoneX = EngineGlobals::screen_width / 2;
        unsigned int deadzoneY = EngineGlobals::screen_height / 2;

        unsigned int lastDirection = 1;
        RectangleCollider *nakedManCollider = nullptr;

        unsigned int m_hitFrames = 0;
        bool m_hit = false;

        bool cameraLock = true;
        bool isMovingLooking = true;

        bool endBossFight = false;

        // Map's zoom requests.
        static bool isZooming;

        std::pair<int, int> mousePosition;

        Timer timerReload;
        Timer lifeRecover;
        Timer timerHit;

        void SetDirection();
        void KeyBoardUpdate();
        void DetectMoovimentForward();
        void DetectMoovimentBack();
        void GameControllerUpdate();
        void CreateAnimations();
        void WallCollisionResolution();
        void GameCollisionCheck();
        void StartFirstBoss();

        //Player Movements
        void Movements();

        void Animations();

        void Shoot();
        void ReloadGun();
        void PlayerLife();

        void MovementsSounds();

        void ComponentUpdate() override;

};
#endif
