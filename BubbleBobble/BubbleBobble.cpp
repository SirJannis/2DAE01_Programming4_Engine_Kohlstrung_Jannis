#include "Engine/Core/MiniginPCH.h"
#include "Engine/Core/Minigin.h"
#include "Engine/Managers/SceneManager.h"
#include "Engine/Managers/ResourceManager.h"
#include "Engine/Components/Components.h"
#include "Engine/Scene/GameObject.h"
#include "Engine/Scene/Scene.h"
#include "Engine/Helpers/Logger.h"
#include "LevelParser.h"
#include "Level.h"
#include "Engine/Managers/InputManager.h"
#include "Engine/Managers/SoundManager.h"
#include "Engine/Helpers/SoundEffect.h"
#include "Engine/Managers/PhysicsManager.h"
#include "Box2D.h"

void LoadTestScene()
{
	using namespace MyEngine;
	Scene& scene = SceneManager::GetInstance()->CreateScene("Demo");

	GameObject* go = new GameObject();
	go->AddComponent(new TransformComponent({ 0.f , 500.f }));
	go->AddComponent(new RenderComponent(1));
	go->GetComponent<RenderComponent>()->AddTexture(ResourceManager::GetInstance()->LoadTexture("background.jpg"));
	scene.Add(go);

	go = new GameObject();
	go->AddComponent(new TransformComponent({ 216.f, 320.f }));
	RenderComponent* pRenderComp = new RenderComponent(1);
	pRenderComp->AddTexture(ResourceManager::GetInstance()->LoadTexture("logo.png"));
	go->AddComponent(pRenderComp);
	scene.Add(go);

	//Make this a gameobject with proper Components
	go = new GameObject();
	go->AddComponent(new TransformComponent({ 80.f, 480.f }));
	go->AddComponent(new RenderComponent(1));
	go->AddComponent(new TextComponent("Programming 4 Assignment", ResourceManager::GetInstance()->LoadFont("Lingua.otf", 36), { 255,255,255 }));
	go->GetComponent<RenderComponent>()->AddTexture(go->GetComponent<TextComponent>()->GetTexture());
	//auto to = std::make_shared<TextObject>("Programming 4 Assignment", font);
	//to->SetPosition(80, 20);
	scene.Add(go);

	go = new GameObject();
	go->AddComponent(new TransformComponent({ 0.f, 500.f }));
	go->AddComponent(new RenderComponent(1));
	go->AddComponent(new TextComponent(" ", ResourceManager::GetInstance()->LoadFont("Lingua.otf", 18), { 255, 255,0 }));
	go->GetComponent<RenderComponent>()->AddTexture(go->GetComponent<TextComponent>()->GetTexture());
	go->AddComponent(new FPSComponent());
	scene.Add(go);

	go = new GameObject();
	go->AddComponent(new TransformComponent());
	RenderComponent* pSecondRenderComp = new RenderComponent(1);
	pSecondRenderComp->AddTexture(ResourceManager::GetInstance()->LoadTexture("logo.png"));
	go->AddComponent(pSecondRenderComp);
	go->AddComponent(new PhysicsComponent(PhysicsType::Dynamic,320.f, 250.f, 0.f , 104.f, 32.5f, 10.f));
	scene.Add(go);

	Logger::GetInstance()->LogInfo("testInfo");
	Logger::GetInstance()->LogWarning("testWarning");
	Logger::GetInstance()->LogError("testError");

	SoundEffect* sound = SoundManager::GetInstance()->LoadSoundEffect("ButtonClick.ogg");

	Command* test = new Command({ [sound]() { Logger::GetInstance()->LogInfo("Executet Test Command!"); sound->Play(0); }, ButtonState::Released });
	InputManager::GetInstance()->AddCommand(VK_LBUTTON, Hardware::Mouse, test);

	PhysicsManager::GetInstance()->SetShouldDebugDraw(true);
	PhysicsManager::GetInstance()->SetDebugDrawColor({255,0,255,255});

}


int main(int, char* []) {
	MyEngine::Minigin engine;
	engine.Initialize("../Data/", "BubbleBobble", 640, 500, 20.f);
	std::vector<level> levels;
	LevelParser::ParseFile("../Data/Resources/FixedLevelData.dat", levels);

	////Box2D test

	//b2Vec2 testgravity{ 0.f, -9.81f };
	//b2World world(testgravity);

	//b2BodyDef groundBodyDef;
	//groundBodyDef.position.Set(320.f, -10.f);
	//b2Body* pGroundBody = world.CreateBody(&groundBodyDef);

	//b2PolygonShape groundBox;
	//groundBox.SetAsBox(320.f, 10.f);

	//pGroundBody->CreateFixture(&groundBox, .0f);

	//b2BodyDef bodyDef;
	//bodyDef.type = b2_dynamicBody;
	//bodyDef.position.Set(0.0f, 4.0f);
	//b2Body* body = world.CreateBody(&bodyDef);

	//b2PolygonShape dynamicBox;
	//dynamicBox.SetAsBox(1.0f, 1.0f);

	//b2FixtureDef fixtureDef;
	//fixtureDef.shape = &dynamicBox;
	//fixtureDef.density = 1.0f;
	//fixtureDef.friction = 0.3f;

	//body->CreateFixture(&fixtureDef);

	//int32 velocityIterations = 6;
	//int32 positionIterations = 2;

	//for (int32 i = 0; i < 60; ++i)
	//{
	//	world.Step(engine.SecondsPerFrame, velocityIterations, positionIterations);
	//	b2Vec2 position = body->GetPosition();
	//	float angle = body->GetAngle();
	//	printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
	//}

	LoadTestScene();
	engine.Run();
	return 0;
}
