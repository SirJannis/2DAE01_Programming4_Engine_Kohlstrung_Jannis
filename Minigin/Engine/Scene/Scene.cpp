#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "../Managers/InputManager.h"

using namespace MyEngine;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() 
{
	for (GameObject* pObject : m_Objects)
	{
		SafeDelete(pObject);
	}
	InputManager::GetInstance()->RemoveCommandsByScene(m_Name);
}

void Scene::Add(GameObject* pObject)
{
	m_Objects.push_back(pObject);
}

void MyEngine::Scene::FixedUpdate(const float fixedDeltaTime)
{
	for (GameObject* pObject : m_Objects)
	{
		pObject->RootFixedUpdate(fixedDeltaTime);
	}
}

void Scene::Update(const float deltaTime)
{
	for(GameObject* pObject : m_Objects)
	{
		pObject->RootUpdate(deltaTime);
	}
}

void Scene::Render() const
{
	for (const GameObject* pObject : m_Objects)
	{
		pObject->Render();
	}
}

