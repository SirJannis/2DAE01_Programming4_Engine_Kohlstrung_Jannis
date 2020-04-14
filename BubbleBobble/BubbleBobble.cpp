#include "Engine/Core/MiniginPCH.h"
#include "Engine/Core/Minigin.h"
#include "Engine/Managers/SceneManager.h"
#include "Engine/Managers/ResourceManager.h"
#include "Engine/Components/Components.h"
#include "Engine/Scene/GameObject.h"
#include "Engine/Scene/Scene.h"
#include "Engine/Helpers/Logger.h"

void LoadTestScene()
{
	using namespace MyEngine;
	Scene& scene = SceneManager::GetInstance()->CreateScene("Demo");

	GameObject* go = new GameObject();
	go->AddComponent(new TransformComponent());
	go->AddComponent(new RenderComponent(1));
	go->GetComponent<RenderComponent>()->AddTexture(ResourceManager::GetInstance()->LoadTexture("background.jpg"));
	scene.Add(go);

	go = new GameObject();
	go->AddComponent(new TransformComponent({ 216.f, 180.f }));
	RenderComponent* pRenderComp = new RenderComponent(1);
	pRenderComp->AddTexture(ResourceManager::GetInstance()->LoadTexture("logo.png"));
	go->AddComponent(pRenderComp);
	scene.Add(go);

	//Make this a gameobject with proper Components
	go = new GameObject();
	go->AddComponent(new TransformComponent({ 80.f, 20.f }));
	go->AddComponent(new RenderComponent(1));
	go->AddComponent(new TextComponent("Programming 4 Assignment", ResourceManager::GetInstance()->LoadFont("Lingua.otf", 36), { 255,255,255 }));
	go->GetComponent<RenderComponent>()->AddTexture(go->GetComponent<TextComponent>()->GetTexture());
	//auto to = std::make_shared<TextObject>("Programming 4 Assignment", font);
	//to->SetPosition(80, 20);
	scene.Add(go);

	go = new GameObject();
	go->AddComponent(new TransformComponent());
	go->AddComponent(new RenderComponent(1));
	go->AddComponent(new TextComponent(" ", ResourceManager::GetInstance()->LoadFont("Lingua.otf", 18), { 255, 255,0 }));
	go->GetComponent<RenderComponent>()->AddTexture(go->GetComponent<TextComponent>()->GetTexture());
	go->AddComponent(new FPSComponent());
	scene.Add(go);

	Logger::GetInstance()->LogInfo("testInfo");
	Logger::GetInstance()->LogWarning("testWarning");
	Logger::GetInstance()->LogError("testError");
}


int main(int, char* []) {
	MyEngine::Minigin engine;
	engine.Initialize();
	LoadTestScene();
	engine.Run();
	return 0;
}
