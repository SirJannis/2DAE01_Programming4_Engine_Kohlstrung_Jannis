#include "MiniginPCH.h"
#include "SceneManager.h"
#include "../Scene/Scene.h"

void MyEngine::SceneManager::FixedUpdate(const float fixedDeltaTime)
{
	for (auto& scene : m_Scenes)
	{
		scene->FixedUpdate(fixedDeltaTime);
	}
}

void MyEngine::SceneManager::Update(const float deltaTime)
{
	for(auto& scene : m_Scenes)
	{
		scene->Update(deltaTime);
	}
}

void MyEngine::SceneManager::Render()
{
	for (const Scene* pScene : m_Scenes)
	{
		pScene->Render();
	}
}

MyEngine::SceneManager::~SceneManager()
{
	for (Scene* pScene : m_Scenes)
	{
		SafeDelete(pScene);
	}
}

MyEngine::Scene& MyEngine::SceneManager::CreateScene(const std::string& name)
{
	Scene* pScene = new Scene(name);
	m_Scenes.push_back(pScene);
	return *pScene;
}
