/**
    @file GamePlayScene.cpp
    @brief Class responsible for creating and
    activating the information needed for game scenes.
    @copyright LGPL. MIT License.
*/

#include "Globals/EngineGlobals.hpp"

#include "Customs/GamePlayScene.hpp"
#include "Customs/CutScene1Script.hpp"
#include "Customs/AudioController.hpp"

const float vectorMapTreeAxisX = -3500;
const float vectorMapTreeAxisY = -3800;

const int gameObjectCreateMapWigth = 8034;
const int gameObjectCreateMapHeight = 8034;
const Uint8 gameObjectCreateMapMapLayer = 0;
const Uint8 gameObjectCreateMapTreeLayer = 1;

const int imageScenePositionX = 0;
const int imageScenePositionY = 0;
const int imageSceneWidth = 2678;
const int imageSceneHeight = 2678;

const int soundLoops = -1;

const float vectorScene1AxisX = 0;
const float vectorScene1AxisY = 0;
const int gameObjectScene1Wigth = 1024;
const int gameObjectScene1Height = 800;
const Uint8 gameObjectScene1Layer = 0;

const float vectorForestActivatorAxisX = 1720;
const float vectorForestActivatorAxisY = -3463;

const float vectorForestActivator2AxisX = 701;
const float vectorForestActivator2AxisY = -578;

const float vectorForestActivator3AxisX = -579;
const float vectorForestActivator3AxisY = -1546;

const int gameObjectForestActivatorWigth = 192;
const int gameObjectForestActivatorHeight = 192;
const Uint8 gameObjectForestActivatorLayer = 1;

const float vectorSnowActivatorAxisX = -1044;
const float vectorSnowActivatorAxisY = 2446;
const int gameObjectSnowActivatorWigth = 192;
const int gameObjectSnowActivatorHeight = 192;
const Uint8 gameObjectSnowActivatorLayer = 1;

// CreateCentralLights
const float vectorBottomCenterLightAxisX = 424;
const float vectorBottomCentralLightAxisY = 422;

const float vectorLeftCenterLightAxisX = 309;
const float vectorLeftCentralLightAxisY = 308;

const float vectorRightCenterLightAxisX = 542;
const float vectorRightCentralLightAxisY = 308;

const float vectorTopCenterLightAxisX = 424;
const float vectorTopCentralLightAxisY = 197;

const int gameObjectCenterLightWigth = 192;
const int gameObjectCenterLightHeight = 192;
const Uint8 gameObjectCenterLightLayer = 1;

// Create Naked Man
const int gameObjectNackedManWigth = 96;
const int gameObjectNackedManHeight = 96;
const Uint8 gameObjectNackedManLayer = 2;

// First Boss Center Effect
const float vectorFirstBossEffectAxisX = 0;
const float vectorFirstBossEffectAxisY = 0;
const int gameObjectFirstBossEffectWigth = 211.86;
const int gameObjectFirstBossEffectHeight = 211.86;
const Uint8 gameObjectFirstBossEffectLayer = 1;

// First Boss
const float vectorFirstBossAxisX = -3350;
const float vectorFirstBossAxisY = -1600;
const int gameObjectFirstBossWigth = 690;
const int gameObjectFirstBossHeight = 930;
const Uint8 gameObjectFirstBossLayer = 2;

// First Boss Attack
const int maxTentacle = 5;
const float vectorFirstBossAttackAxisX = -4750;
const float vectorFirstBossAttackAxisY = -1700;
const int gameObjectFirstBossAttackWigth = 100;
const int gameObjectFirstBossAttackHeight = 377;
const Uint8 gameObjectFirstBossAttackLayer = 2;

// First Boss Life Border
const float vectorFirstBossLifeBorderAxisX = 0;
const float vectorFirstBossLifeBorderAxisY = 0;
const int gameObjectFirstBossLifeBorderWigth = 344;
const int gameObjectFirstBossLifeBorderHeight = 25;
const Uint8 gameObjectFirstBossLifeBorderLayer = 3;

// First Boss Life
const float vectorFirstBossLifeAxisX = 0;
const float vectorFirstBossLifeAxisY = 0;
const int gameObjectFirstBossLifeWigth = 337;
const int gameObjectFirstBossLifeHeight = 25;
const Uint8 gameObjectFirstBossLifeLayer = 2;

// Rectangle Render
const float vectorFisrtBossRectangleRenderAxisX = 0;
const float vectorFisrtBossRectangleRenderAxisY = 0;
const int fisrtBossRectangleRenderWidth = 337;
const int fisrtBossRectangleRenderHeight = 25;

// Set color rectangle
const int rectangleRenderRed = 255;
const int rectangleRenderGreen = 48;
const int rectangleRenderBlue = 48;
const int rectangleRenderAlpha = 255;

// Create play attack, bullet name
const int maxBullet = 11;
const float vectorBulletNameAxisX = 100;
const float vectorBulletNameAxisY = 0;
const int gameObjectBulletNameWigth = 15;
const int gameObjectBulletNameHeight = 15;
const Uint8 gameObjectBulletNameLayer = 2;

// Create play attack, bullet counter
const float vectorBulletCounterAxisX = 0;
const float vectorBulletCounterAxisY = 0;
const int gameObjectBulletCounterWigth = 75;
const int gameObjectBulletCounterHeight = 75;
const Uint8 gameObjectBulletCounterLayer = 2;

// Create play attack, bullet counter text
const string bulletCounterMessage = "10";
const int bulletCounterSize = 150;
const Uint8 bulletCounterRed = 0;
const Uint8 bulletCounterGreen = 0;
const Uint8 bulletCounterBlue = 0;
const Uint8 bulletCounterAlpha = 0;
const Uint8 bulletCountermode = 1;



/**
    @brief Responsible for creating the inputs
    needed to run the game scene that are defined further down.
*/
void GamePlayScene::OnActivation() {

    //This must be the first function to be called.
    CreateMap();
    CreateCreditAnimation();
    CreateNakedMan();
    CreateFirstBoss();
    CreateFirstBossAttack();
    CreateFirstBossLife();
    CreateLight();
    CreateRain();
    CreateSnow();
    CreateThunder();
    CreatePlayerAttack();Scene  CreatePlayerHit();
    CreateForestActivator();
    CreateSnowActivator();
    CreateCentralLights();
    CreateCutScenes();
    FirstBossController::GetInstance()->StartBossFight();

}

void GamePlayScene::OnDeactivation() {

}

void GamePlayScene::OnShown() {

}

void GamePlayScene::OnHidden() {

}

/**
    @brief Create the game map by adding the
    trees and correcting the screen rendering.
*/
void GamePlayScene::CreateMap() {


    //Original resolution is 2048/2048.
    //6144,6144 = 3x.
    auto m_map = new GameObject("Map", new Vector(vectorMapTreeAxisX, vectorMapTreeAxisY),
                                gameObjectCreateMapWigth, gameObjectCreateMapHeight, gameObjectCreateMapMapLayer);

    // Renderer the map image.
    auto m_mapImage = new Image("assets/mapa2.png", imageScenePositionX, 
                              imageScenePositionY, imageSceneWidth, imageSceneHeight);
    //auto mapImage = new Image("assets/transitavel.png", 0, 0, 2678, 2678);
    new Renderer(m_map, m_mapImage);


    auto m_trees = new GameObject("Tree", new Vector(vectorMapTreeAxisX ,vectorMapTreeAxisY),
                                gameObjectCreateMapWigth,gameObjectCreateMapHeight,gameObjectCreateMapTreeLayer);

    // Renderer the trees image.
    auto m_treesImage = new Image("assets/trees.png", imageScenePositionX, 
                                imageScenePositionY, imageSceneWidth, imageSceneHeight);

    new Renderer(m_trees, m_treesImage);

    // Script.
    new MapScript(m_map);



    auto bossBattleSound = new UISound(m_map, "bossBattleSound",
                                       "assets/Audio/Boss/heartfinal.ogg",
                                       false, false);

    AudioController::GetInstance()->AddAudio(bossBattleSound);

    auto mainSound = new UISound(m_map, "mainSound",
                                 "assets/Audio/florestafinal.ogg",
                                 false, false);

    // Add the audio in the scene.
    AudioController::GetInstance()->AddAudio(mainSound);

    // Play the audio that was added before.
    AudioController::GetInstance()->PlayAudio("mainSound", soundLoops);

    // Add the map.
    AddGameObject(m_map);

    FirstBossController::GetInstance()->AddMap(m_map);

    // Add the trees.
    AddGameObject(m_trees);

}


void GamePlayScene::CreateCutScenes() {

    auto scene1 = new GameObject("SCENE1", new Vector(vectorScene1AxisX,vectorScene1AxisY),
                                 gameObjectScene1Wigth,gameObjectScene1Height,
                                 gameObjectScene1Layer);

    auto  scene1Script = new CutScene1Script(scene1);

    scene1Script->Activate();
    AddGameObject(scene1);
}


/**
    @brief Responsible for creating three forest-activating objects.
*/
void  GamePlayScene::CreateForestActivator() {
    //left
    auto m_forestActivator = new GameObject("FOREST ACTIVATOR",
                                          new Vector(vectorForestActivatorAxisX, vectorForestActivatorAxisY), 
                                          gameObjectForestActivatorWigth, gameObjectForestActivatorHeight,
                                          gameObjectForestActivatorLayer);
    new ForestActivatorScript(m_forestActivator);
    AddGameObject(m_forestActivator);

    //blue
    auto m_forestActivator2 = new GameObject("FOREST ACTIVATOR2",
                                           new Vector(vectorForestActivator2AxisX,vectorForestActivator2AxisY),
                                           gameObjectForestActivatorWigth, gameObjectForestActivatorHeight,
                                           gameObjectForestActivatorLayer);
    new ForestActivatorScript2(m_forestActivator2);
    AddGameObject(m_forestActivator2);

    //central
    auto m_forestActivator3 = new GameObject("FOREST ACTIVATOR3",
                                           new Vector(vectorForestActivator3AxisX, vectorForestActivator3AxisY),
                                           gameObjectForestActivatorWigth, gameObjectForestActivatorHeight,
                                           gameObjectForestActivatorLayer);
    new ForestActivatorScript3(m_forestActivator3);
    AddGameObject(m_forestActivator3);

}

/**
    @brief responsible for creating the snow activator at
    the end it sends to the class that treats the objects of the game.
*/
void GamePlayScene::CreateSnowActivator(){

    auto m_snowActivator = new GameObject("SNOW ACTIVATOR",
                                        new Vector(vectorSnowActivatorAxisX,vectorSnowActivatorAxisY),
                                        gameObjectSnowActivatorWigth,gameObjectSnowActivatorHeight,
                                        gameObjectSnowActivatorLayer);

    new SnowActivatorScript(m_snowActivator);
    AddGameObject(m_snowActivator);

}

/**
    @brief responsible for creating four central lights at
    the end it sends to the class that treats the objects of the game.
*/
void GamePlayScene::CreateCentralLights(){

    auto m_bottomCenterLight = new GameObject("CENTRAL LIGHT 1",
                                           new Vector(vectorBottomCenterLightAxisX,vectorBottomCentralLightAxisY),
                                           gameObjectCenterLightWigth,gameObjectCenterLightHeight,
                                           gameObjectCenterLightLayer);

    new CentralLightScript1(m_bottomCenterLight);
    AddGameObject(m_bottomCenterLight);

    auto m_leftCenterLight = new GameObject("CENTRAL LIGHT 2",
                                           new Vector(vectorLeftCenterLightAxisX,vectorLeftCentralLightAxisY),
                                           gameObjectCenterLightWigth, gameObjectCenterLightHeight,
                                           gameObjectCenterLightLayer);

    new LeftCenterLightScript(m_leftCenterLight);
    AddGameObject(m_leftCenterLight);

    auto m_rightCenterLight = new GameObject("CENTRAL LIGHT 2",
                                           new Vector(vectorRightCenterLightAxisX,vectorRightCentralLightAxisY),
                                           gameObjectCenterLightWigth, gameObjectCenterLightHeight,
                                           gameObjectCenterLightLayer);

    new CentralLightScript3(m_rightCenterLight);
    AddGameObject(m_rightCenterLight);

    auto m_topCenterLight = new GameObject("CENTER LIGHT 4",
                                       new Vector(vectorTopCenterLightAxisX,vectorTopCentralLightAxisY),
                                       gameObjectCenterLightWigth, gameObjectCenterLightHeight,
                                       gameObjectCenterLightLayer);

    new TopCenterLightScript(m_topCenterLight);
    AddGameObject(m_topCenterLight);
}

void GamePlayScene::CreateNakedMan() {

    int positionX = 0;
    int positionY = 0;
    positionX = EngineGlobals::screen_width / 2 - gameObjectNackedManWigth / 2;
    positionY = EngineGlobals::screen_height / 2 - gameObjectNackedManHeight / 2;

    auto m_nakedMan = new GameObject("NakedMan", new Vector(positionX,positionY),
                                    gameObjectNackedManWigth , gameObjectNackedManHeight, 
                                    gameObjectNackedManLayer);

    // Script.
    new NakedManScript(m_nakedMan);

    auto runSound = new UISound(m_nakedMan, "runSound",
                                "assets/Audio/Player/runcrushed.ogg", false,
                                false);
    AudioController::GetInstance()->AddAudio(runSound);

    AddGameObject(m_nakedMan);
    FirstBossController::GetInstance()->AddPlayer(m_nakedMan);

}

/**
    @brief Responsible for creating and defining
    the location that the first boss will be and which special
    effect he will have when he is found.
*/
void GamePlayScene::CreateFirstBoss() {
    // Boss Inside FX
    auto m_firstBossCentralEffect = new GameObject("FirstBossCentralEffect",
                                                 new Vector(vectorFirstBossEffectAxisX, vectorFirstBossEffectAxisY),
                                                 gameObjectFirstBossEffectWigth, gameObjectFirstBossEffectHeight, 
                                                 gameObjectFirstBossEffectLayer);

    new FirstBossCentralEffectScript(m_firstBossCentralEffect);

    AddGameObject(m_firstBossCentralEffect);
    FirstBossController::GetInstance()->AddInsideBossFx(m_firstBossCentralEffect);
    FirstBossController::GetInstance()->DeactivateInsideBossFx();

    // Boss.
    auto firstBoss = new GameObject("FirstBoss", new Vector(vectorFirstBossAxisX, vectorFirstBossAxisY),
                                    gameObjectFirstBossWigth, gameObjectFirstBossHeight, gameObjectFirstBossLayer);

    // Tag.
    firstBoss->SetTag("FirstBoss");

    // Script.
    new  FirstBossScript(firstBoss);
    AddGameObject(firstBoss);

    FirstBossController::GetInstance()->AddBoss(firstBoss);
    FirstBossController::GetInstance()->DeactivateBoss();
}

/**
    @brief Responsible for creating the first attack of the boss
    defining the sound effect of the attacks and
    the cries of the first three attacks.
*/
void GamePlayScene::CreateFirstBossAttack() {

    // Create the tentacle of boss attack and the effects.
    for (int i = 1; i < maxTentacle; i++) {

        std::string tentacleName = "FirstBossAttack" + std::to_string(i);

        auto m_firstBossAttack = new GameObject(tentacleName,
                                              new Vector(vectorFirstBossAttackAxisX, vectorFirstBossAttackAxisY),
                                               gameObjectFirstBossAttackWigth, gameObjectFirstBossAttackHeight,
                                               gameObjectFirstBossAttackLayer);
        // Tag.
        m_firstBossAttack->SetTag("FirstBossAtack");

        // Script.
        new  FirstBossAttackScript(m_firstBossAttack);

        //Sounds.
        auto firstAttackSound = new UISound(m_firstBossAttack, "firstAttackSound",
                                            "assets/Audio/Boss/grito1.ogg",
                                            false, false);
        AudioController::GetInstance()->AddAudio(firstAttackSound);

        auto secondAttackSound = new UISound(m_firstBossAttack, "secondAttackSound",
                                            "assets/Audio/Boss/grito2.ogg",
                                            false, false);
        AudioController::GetInstance()->AddAudio(secondAttackSound);

        auto thirdAttackSound = new UISound(m_firstBossAttack, "thirdAttackSound",
                                            "assets/Audio/Boss/grito3.ogg",
                                            false, false);
        AudioController::GetInstance()->AddAudio(thirdAttackSound);

        auto fourthAttackSound = new UISound(m_firstBossAttack, "fourthAttackSound",
                                            "assets/Audio/Boss/heart_attack.ogg",
                                            false, false);
        AudioController::GetInstance()->AddAudio(fourthAttackSound);



        AddGameObject(m_firstBossAttack);
        FirstBossController::GetInstance()->AddTentacle(m_firstBossAttack);

    } // for -- Create the tentacle of boss attack and the effects.
}

/**
    @brief Responsible for creating the first boss life by setting the
    life bar and sending it to the class that creates the game objects.
*/
void GamePlayScene::CreateFirstBossLife() {

    // Life Border.
    auto m_firstBossLifeBorderSprite = new GameObject("FirstBossBorderLife",
                                                    new Vector(vectorFirstBossLifeBorderAxisX, 
                                                    vectorFirstBossLifeBorderAxisY),
                                                    gameObjectFirstBossLifeBorderWigth, 
                                                    gameObjectFirstBossLifeBorderHeight,
                                                    gameObjectFirstBossLifeBorderLayer);

    new  FirstBossLifeBorderScript(m_firstBossLifeBorderSprite);
    AddGameObject(m_firstBossLifeBorderSprite);
    FirstBossController::GetInstance()->AddLifeBar(m_firstBossLifeBorderSprite);

    // Life.
    auto m_firstBossLife = new GameObject("FirstBossLife",
                                        new Vector(vectorFirstBossLifeAxisX, vectorFirstBossLifeAxisY),
                                        gameObjectFirstBossLifeWigth, gameObjectFirstBossLifeHeight,
                                        gameObjectFirstBossLifeLayer);
    
    auto lifeRectangle = new RectangleRenderer(m_firstBossLife, Vector(vectorFisrtBossRectangleRenderAxisX, 
                                                vectorFisrtBossRectangleRenderAxisY),
                                                fisrtBossRectangleRenderWidth, fisrtBossRectangleRenderHeight);

    lifeRectangle->SetColor(rectangleRenderRed, rectangleRenderGreen, rectangleRenderBlue, rectangleRenderAlpha);

    new  FirstBossLifeScript(m_firstBossLife);
    
    AddGameObject(m_firstBossLife);

    // Add to controller
    FirstBossController::GetInstance()->AddLifeBar(m_firstBossLife);

    // Desable all life bars
    FirstBossController::GetInstance()->DeactivateLifeBars();
}

/**
    @brief Responsible for creating the bullets that
    the player launches against the boss.
*/
void GamePlayScene::CreatePlayerAttack() {

    // Creating Bullets
    for (int i = 1; i < maxBullet; i++) {
        std::string bulletName = "Bullet" + std::to_string(i);
        auto m_bullet = new GameObject(bulletName, new Vector(vectorBulletNameAxisX * i, vectorBulletNameAxisY),
                                     gameObjectBulletNameWigth, gameObjectBulletNameHeight, gameObjectBulletNameLayer);

        m_bullet->SetTag("Bullet");
        new  PlayerAttackScript(m_bullet);
        AddGameObject(m_bullet);

        auto bulletSound = new UISound(m_bullet, "bulletSound",
                                       "assets/Audio/Player/fireball.ogg",
                                        false, false);

        AudioController::GetInstance()->AddAudio(bulletSound);

        m_bullet->active = false;
    }

    // Bullet Counter
    auto bulletCounter = new GameObject("Score", new Vector(vectorBulletCounterAxisX, vectorBulletCounterAxisY),
                                        gameObjectBulletCounterWigth , gameObjectBulletCounterHeight, gameObjectBulletCounterLayer);
    bulletCounter->SetTag("BulletCounter");
    new UIText(bulletCounter, bulletCounterMessage,
                                 "assets/Fonts/advanced-pixel-7/advanced_pixel-7.ttf",
                                  bulletCounterSize, bulletCounterRed , bulletCounterGreen, bulletCounterBlue,
                                  bulletCounterAlpha, bulletCountermode);

    new BulletCounterScript(bulletCounter);
    AddGameObject(bulletCounter);
}

/**
    @brief Responsible for creating
    raindrops and the sound effect of rain.
*/
void GamePlayScene::CreateRain() {

    auto rain = new GameObject("Rain", new Vector(0,0),1024,800,1);
    new RainScript(rain);
    auto rainSound = new UISound(rain, "rainSound",
                                 "assets/Audio/Boss/chuva.ogg",
                                 false, false);
    AudioController::GetInstance()->AddAudio(rainSound);
    AddGameObject(rain);
}

/**
    @brief Responsible for creating the hit object, which is the game's music.
*/
void GamePlayScene::CreatePlayerHit() {

    auto hit = new GameObject("Hit", new Vector(0,0),1024,800,1);

    new HitScript(hit);
    AddGameObject(hit);
}

/**
    @grief Responsible for creating the visual effects of thunder.
*/
void GamePlayScene::CreateThunder() {

    auto thunder = new GameObject("Rain", new Vector(200,0),113,267,1);
    new ThunderScript(thunder);
    AddGameObject(thunder);
}

/**
    @grief Responsible for creating the visual effects of snow and the effect.
*/
void GamePlayScene::CreateSnow(){

    auto snow = new GameObject("Snow", new Vector(0,0),1024,800,1);
    new SnowScript(snow);
    auto snowSound = new UISound(snow, "snowSound",
                                "assets/Audio/Clima/winteriscomming.ogg",
                                false, false);
    AudioController::GetInstance()->AddAudio(snowSound);
    AddGameObject(snow);
}

/**
    @grief Responsible for creating the visual effect of light.
*/
void GamePlayScene::CreateLight() {

    auto light = new GameObject("Light", new Vector(0,0),2*1024,2*800,2);
    new LightScript(light);
    AddGameObject(light);
}

/**
    @grief Creates the visual effect of game credits.
*/
void GamePlayScene::CreateCreditAnimation() {

    /** Credits Animation **/
    auto creditAnimation = new GameObject("CreditAnimation",
                                          new Vector(0, 0),1200, 800, 3);

    auto creditRectangle = new RectangleRenderer(creditAnimation,
                                                 Vector(0, 0), 1200, 800);
    creditRectangle->SetColor(255, 48, 48, 255);
    new  CreditsScript(creditAnimation);
    AddGameObject(creditAnimation);
    FirstBossController::GetInstance()->AddCreditsAnimation(creditAnimation);
    FirstBossController::GetInstance()->DeactivateCreditsAnimation();
}

/**
    @grief Creates a player monition counter.
*/
void GamePlayScene::CreateAmmoCounter() {

    auto ammo = new GameObject("Ammo", new Vector(2,2),200,200,3);
    new UIText(ammo, "15",
                "assets/UIpack/Font/kenvector_future_thin.ttf",
                100, 255, 255, 255, 255, 1);
    AddGameObject(ammo);
}
