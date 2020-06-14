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
	go->AddComponent(new PhysicsComponent(PhysicsType::Dynamic, { 320.f, 250.f }, 0.f, 104.f, 32.5f, 10.f));
	scene.Add(go);

	Logger::GetInstance()->LogInfo("testInfo");
	Logger::GetInstance()->LogWarning("testWarning");
	Logger::GetInstance()->LogError("testError");

	SoundManager::GetInstance()->LoadSoundEffect("ButtonClick.ogg", Event(1));

	Command* testCommand = new Command({ []() { Logger::GetInstance()->LogInfo("Executet Test Command!"); SoundManager::GetInstance()->Notify(Event(1)); }, ButtonState::Released, "Demo" });
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
