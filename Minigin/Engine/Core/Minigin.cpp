#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "../Managers/InputManager.h"
#include "../Managers/SceneManager.h"
#include "../Graphics/Renderer.h"
#include "../Managers/ResourceManager.h"
#include <SDL.h>
#include "../Scene/GameObject.h"
#include "../Scene/Scene.h"
#include "../Components/Components.h"

using namespace std;
using namespace std::chrono;

void MyEngine::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance()->Init(m_Window);
}

/**
 * Code constructing the scene world starts here
 */
void MyEngine::Minigin::LoadGame() const
{
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
}

void MyEngine::Minigin::Cleanup()
{
	Renderer::GetInstance()->Destroy();
	Renderer::Release();
	SceneManager::Release();
	InputManager::Release();
	ResourceManager::Release();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void MyEngine::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance()->Init("../Data/");

	LoadGame();

	{
		Renderer* renderer = Renderer::GetInstance();
		SceneManager* sceneManager = SceneManager::GetInstance();
		InputManager* input = InputManager::GetInstance();

		bool doContinue = true;
		auto lastTime = high_resolution_clock::now();
		while (doContinue)
		{
			const auto currentTime = high_resolution_clock::now();
			float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
			doContinue = input->ProcessInput();
			sceneManager->Update(deltaTime);
			renderer->Render();
			lastTime = currentTime;
		}
	}

	Cleanup();
}
