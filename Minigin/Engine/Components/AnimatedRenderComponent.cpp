#include "MiniginPCH.h"
#include "AnimatedRenderComponent.h"
#include "TransformComponent.h"
#include "../Graphics/Texture2D.h"
#include <exception>
#include "../Graphics/Renderer.h"
#include "../Scene/GameObject.h"
MyEngine::AnimatedRenderComponent::AnimatedRenderComponent(const size_t maxTextures)
	:m_Textures{ maxTextures }
	, m_NrTextures{ 0 }
{
}
MyEngine::AnimatedRenderComponent::~AnimatedRenderComponent()
{
	for (Texture2D* pTexture : m_Textures)
	{
		if (pTexture)
		{
			delete pTexture;
			pTexture = nullptr;
		}
	}
}
void MyEngine::AnimatedRenderComponent::FixedUpdate(const float fixedDeltaTime)
{
	UNREFERENCED_PARAMETER(fixedDeltaTime);
}
void MyEngine::AnimatedRenderComponent::Update(const float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

void MyEngine::AnimatedRenderComponent::Render() const
{
	for (size_t i{}; i < m_NrTextures; i++)
	{
		glm::fvec2 pos = m_pGameObject->GetComponent<TransformComponent>()->GetPosition();
		Renderer::GetInstance()->RenderTexture(*m_Textures[i], pos.x, pos.y);
	}
}

void MyEngine::AnimatedRenderComponent::AddTexture(Texture2D* texture)
{
	if (m_NrTextures == m_Textures.size()) throw std::exception("Max Nr of Textures Reached.");
	m_Textures[m_NrTextures] = texture;
	m_NrTextures++;
}
