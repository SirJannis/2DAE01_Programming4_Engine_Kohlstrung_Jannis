#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

using namespace MyEngine;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() 
{
	for (SceneObject* pObject : m_Objects)
	{
		delete pObject;
		pObject = nullptr;
	}
}

void Scene::Add(SceneObject* pObject)
{
	m_Objects.push_back(pObject);
}

void Scene::Update(const float deltaTime)
{
	for(SceneObject* pObject : m_Objects)
	{
		pObject->Update(deltaTime);
	}
}

void Scene::Render() const
{
	for (const SceneObject* pObject : m_Objects)
	{
		pObject->Render();
	}
}

