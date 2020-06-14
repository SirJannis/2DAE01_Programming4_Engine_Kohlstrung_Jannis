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
	go->AddComponent(new TransformComponent({ 320.f , 250.f }));
	go->AddComponent(new RenderComponent());
	go->GetComponent<RenderComponent>()->AddTexture(ResourceManager::GetInstance()->LoadTexture("background.jpg"));
	scene.Add(go);

	go = new GameObject();
	go->AddComponent(new TransformComponent({ 320.f, 250.f }));
	RenderComponent* pRenderComp = new RenderComponent();
	pRenderComp->AddTexture(ResourceManager::GetInstance()->LoadTexture("logo.png"));
	go->AddComponent(pRenderComp);
	scene.Add(go);

	go = new GameObject();
	go->AddComponent(new TransformComponent({ 320.f, 480.f }));
	go->AddComponent(new TextComponent("Programming 4 Assignment", ResourceManager::GetInstance()->LoadFont("Lingua.otf", 36), { 255,255,255 }, 0.f, {.5f, .5f}));
	scene.Add(go);

	go = new GameObject();
	go->AddComponent(new TransformComponent({ 0.f, 500.f }));
	go->AddComponent(new TextComponent(" ", ResourceManager::GetInstance()->LoadFont("Lingua.otf", 18), { 255, 255,0 }, 0.f, {0.f, 0.f}));
	go->AddComponent(new FPSComponent());
	scene.Add(go);

	go = new GameObject();
	go->AddComponent(new TransformComponent());
	RenderComponent* pSecondRenderComp = new RenderComponent();
	pSecondRenderComp->AddTexture(ResourceManager::GetInstance()->LoadTexture("logo.png"));
	go->AddComponent(pSecondRenderComp);
	go->AddComponent(new PhysicsComponent(PhysicsType::Dynamic, { 320.f, 250.f }, 45.f, 104.f, 32.5f, 10.f, 0.3f, 0.0f));
	scene.Add(go);

	go = new GameObject();
	go->AddComponent(new TransformComponent());
	RenderComponent* pThirdRenderComp = new RenderComponent();
	pThirdRenderComp->AddTexture(ResourceManager::GetInstance()->LoadTexture("logo.png"));
	go->AddComponent(pThirdRenderComp);
	go->AddComponent(new PhysicsComponent(PhysicsType::Kinematic, { 320.f, 10.f }, 0.f, 104.f, 32.5f, 10.f, 0.3f, 0.0f));
	scene.Add(go);

	Logger::LogInfo("testInfo");
	Logger::LogWarning("testWarning");
	Logger::LogError("testError");

	SoundManager::GetInstance()->LoadSoundEffect("ButtonClick.ogg", Event(1));

	Command* testCommand = new Command({ []() { Logger::LogInfo("Executet Test Command!"); SoundManager::GetInstance()->Notify(Event(1)); }, ButtonState::Released, "Demo" });
	InputManager::GetInstance()->AddCommand(XINPUT_GAMEPAD_A, Hardware::Controller, testCommand, 0);
	InputManager::GetInstance()->AddCommand(VK_LBUTTON, Hardware::Mouse, testCommand, 0);


	PhysicsManager::GetInstance()->SetShouldDebugDraw(true);
	PhysicsManager::GetInstance()->SetDebugDrawColor({255,0,255,255});

}


int main(int, char* []) {
	MyEngine::Minigin engine;
	engine.Initialize("../Data/", "BubbleBobble", 640, 500, 20.f);
	std::vector<level> levels;
	LevelParser::ParseFile("../Data/Resources/SeperatedLevelData.dat", "../Data/Resources/SeperatedEnemyData.dat", levels);

	LoadTestScene();
	engine.Run();
	return 0;
}
