#include "MiniginPCH.h"
#include "SceneManager.h"
#include "../Scene/Scene.h"
#include "../Helpers/Logger.h"
#include "InputManager.h"

void MyEngine::SceneManager::FixedUpdate(const float fixedDeltaTime)
{
	m_pActiveScene->FixedUpdate(fixedDeltaTime);
}

void MyEngine::SceneManager::Update(const float deltaTime)
{
	m_pActiveScene->Update(deltaTime);
}

void MyEngine::SceneManager::Render()
{
	m_pActiveScene->Render();
}

MyEngine::SceneManager::~SceneManager()
{
	for (Scene* pScene : m_Scenes)
	{
		SafeDelete(pScene);
	}
}

MyEngine::Scene& MyEngine::SceneManager::CreateScene(const std::string& name, bool setactive)
{
	Scene* pScene = new Scene(name);
	m_Scenes.push_back(pScene);
	if(setactive)
	{
		m_pActiveScene = m_Scenes.back();
	}
	return *pScene;
}

void MyEngine::SceneManager::AddScene(Scene* pScene, bool setactive)
{
	m_Scenes.push_back(pScene);
	if (setactive)
	{
		m_pActiveScene = m_Scenes.back();
	}
}

void MyEngine::SceneManager::SetActiveScene(const std::string& name)
{
	for (Scene* pScene : m_Scenes)
	{
		if (pScene->GetName() == name)
		{
			m_pActiveScene = pScene;
			return;
		}
	}
}

void MyEngine::SceneManager::SetActiveScene(const Scene* pScene)
{
	for (Scene* pSceneMember : m_Scenes)
	{
		if (pSceneMember == pScene)
		{
			m_pActiveScene = pSceneMember;
			return;
		}
		else
		{
			Logger::LogError("Scene you wanted to set active is not a valid Scene, please add it to the Manager first\n");
		}
	}
}

void MyEngine::SceneManager::RemoveScene(const std::string& name)
{
	for (size_t idx{}; idx < m_Scenes.size(); idx++)
	{
		if (m_Scenes[idx]->GetName() == name)
		{
			if (m_pActiveScene == m_Scenes[idx])
			{
				m_pActiveScene = m_Scenes[(idx + 1) % m_Scenes.size()];
			}
			InputManager::GetInstance()->RemoveCommandsByScene(name);
			SafeDelete(m_Scenes[idx]);
			m_Scenes[idx] = m_Scenes.back();
			m_Scenes.pop_back();
			idx--;
		}
	}
}

void MyEngine::SceneManager::RemoveScene(const Scene* pScene)
{
	for (size_t idx{}; idx < m_Scenes.size(); idx++)
	{
		if (m_Scenes[idx] == pScene)
		{
			if (m_pActiveScene == m_Scenes[idx])
			{
				m_pActiveScene = m_Scenes[(idx + 1) % m_Scenes.size()];
			}
			InputManager::GetInstance()->RemoveCommandsByScene(m_Scenes[idx]->GetName());
			SafeDelete(m_Scenes[idx]);
			m_Scenes[idx] = m_Scenes.back();
			m_Scenes.pop_back();
			idx--;
		}
	}
}
