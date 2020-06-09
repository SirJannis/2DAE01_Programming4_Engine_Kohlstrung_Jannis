#include "MiniginPCH.h"
#include "GameObject.h"
#include "../Managers/ResourceManager.h"
#include "../Graphics/Renderer.h"
#include "../Components/BaseComponent.h"

#include <exception>

MyEngine::GameObject::~GameObject()
{
	for (BaseComponent* pComp : m_Components)
	{
		SafeDelete(pComp);
	}
}

void MyEngine::GameObject::RootFixedUpdate(const float fixedDeltaTime)
{
	for (BaseComponent* pComp : m_Components)
	{
			pComp->FixedUpdate(fixedDeltaTime);
	}
	FixedUpdate(fixedDeltaTime);
}

void MyEngine::GameObject::RootUpdate(const float deltaTime)
{
	for (BaseComponent* pComp : m_Components)
	{
			pComp->Update(deltaTime);
	}
	Update(deltaTime);
}

void MyEngine::GameObject::Render() const
{
	for (BaseComponent* pComp : m_Components)
	{
			pComp->Render();
	}
}

void MyEngine::GameObject::AddComponent(BaseComponent* pComponent)
{
	for (BaseComponent* pComp : m_Components)
	{
		if (typeid(*pComp) == typeid(*pComponent))
		{
			throw std::exception("The Gameobject already has a component of this type.");
			return;
		}
	}
	m_Components.push_back(pComponent);
	pComponent->SetGameObject(this);
}

//template <class T>
//T* MyEngine::GameObject::GetComponent()
//{
//	const type_info& ti = typeid(T);
//	for (BaseComponent* pComp : m_Components)
//	{
//		if (pComp && typeid(*pComp) == ti)
//			return static_cast<T*>(pComp);
//	}
//	return nullptr;
//}
