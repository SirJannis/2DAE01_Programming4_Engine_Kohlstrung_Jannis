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
#include "../Helpers/Logger.h"
#include "../Managers/SoundManager.h"
#include "../Managers/PhysicsManager.h"

#if _DEBUG
#include <vld.h>
#endif

using namespace std;
using namespace std::chrono;

const float MyEngine::Minigin::SecondsPerFrame = .016f;

void MyEngine::Minigin::Initialize(const std::string& dataPath, const std::string& windowTitle, int windowWidth, int windowHeigth, const float ppm)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}
	Logger::Init();

	m_pWindow = SDL_CreateWindow(
		windowTitle.c_str(),
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		windowWidth,
		windowHeigth,
		SDL_WINDOW_OPENGL
	);
	if (m_pWindow == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	InputManager::GetInstance()->Init(m_pWindow);
	Renderer::GetInstance()->Init(m_pWindow, { 0,0,0,255 });
	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance()->Init(dataPath + "Resources/");
	SoundManager::GetInstance()->Init(dataPath + "Sounds/");
	b2Vec2 gravity{ 0.f, -9.81f };
	PhysicsManager::GetInstance()->Init(gravity, 8, 3, ppm);
}

/**
 * Code constructing the scene world starts here
 */
void MyEngine::Minigin::LoadGame() const
{
	Scene& scene = SceneManager::GetInstance()->CreateScene("Demo");

	GameObject* go = new GameObject();
	go->AddComponent(new TransformComponent());
	go->AddComponent(new RenderComponent());
	go->GetComponent<RenderComponent>()->AddTexture(ResourceManager::GetInstance()->LoadTexture("background.jpg"));
	scene.Add(go);

	go = new GameObject();
	go->AddComponent(new TransformComponent({ 216.f, 180.f }));
	RenderComponent* pRenderComp = new RenderComponent();
	pRenderComp->AddTexture(ResourceManager::GetInstance()->LoadTexture("logo.png"));
	go->AddComponent(pRenderComp);
	scene.Add(go);

	//Make this a gameobject with proper Components
	go = new GameObject();
	go->AddComponent(new TransformComponent({ 80.f, 20.f }));
	go->AddComponent(new RenderComponent());
	go->AddComponent(new TextComponent("Programming 4 Assignment", ResourceManager::GetInstance()->LoadFont("Lingua.otf", 36), { 255,255,255 }));
	go->GetComponent<RenderComponent>()->AddTexture(go->GetComponent<TextComponent>()->GetTexture());
	scene.Add(go);

	go = new GameObject();
	go->AddComponent(new TransformComponent());
	go->AddComponent(new RenderComponent());
	go->AddComponent(new TextComponent(" ", ResourceManager::GetInstance()->LoadFont("Lingua.otf", 18), { 255, 255,0 }));
	go->GetComponent<RenderComponent>()->AddTexture(go->GetComponent<TextComponent>()->GetTexture());
	go->AddComponent(new FPSComponent());
	scene.Add(go);

	Logger::LogInfo("testInfo");
	Logger::LogWarning("testWarning");
	Logger::LogError("testError");
}

void MyEngine::Minigin::Cleanup()
{
	Renderer::GetInstance()->Destroy();
	Renderer::Release();
	SceneManager::Release();
	InputManager::Release();
	ResourceManager::Release();
	SoundManager::Release();
	PhysicsManager::Release();
	SDL_DestroyWindow(m_pWindow);
	m_pWindow = nullptr;
	SDL_Quit();
}

void MyEngine::Minigin::Run()
{
	{
		Renderer* renderer = Renderer::GetInstance();
		SceneManager* sceneManager = SceneManager::GetInstance();
		InputManager* input = InputManager::GetInstance();
		PhysicsManager* physics = PhysicsManager::GetInstance();

		bool doContinue = true;
		auto lastTime = high_resolution_clock::now();
		float lag = 0.f;
		while (doContinue)
		{
			const auto currentTime = high_resolution_clock::now();
			float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
			lastTime = currentTime;
			lag += deltaTime;
			doContinue = input->ProcessSDLEvents();
			input->ProcessInput();
			sceneManager->Update(deltaTime);
			while (lag >= SecondsPerFrame)
			{
				sceneManager->FixedUpdate(SecondsPerFrame);
				physics->FixedUpdate(SecondsPerFrame);
				lag -= SecondsPerFrame;
			}
			renderer->Render();
		}
	}

	Cleanup();
}
