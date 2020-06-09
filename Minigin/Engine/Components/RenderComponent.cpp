#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "../Graphics/Texture2D.h"
#include <exception>
#include "../Graphics/Renderer.h"
#include "../Scene/GameObject.h"
MyEngine::RenderComponent::RenderComponent(const size_t maxTextures)
	:m_Textures{ maxTextures }
	, m_NrTextures{ 0 }
{
}
MyEngine::RenderComponent::~RenderComponent()
{
	for (Texture2D* pTexture : m_Textures)
	{
		SafeDelete(pTexture);
	}
}
void MyEngine::RenderComponent::FixedUpdate(const float fixedDeltaTime)
{
	UNREFERENCED_PARAMETER(fixedDeltaTime);
}
void MyEngine::RenderComponent::Update(const float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

void MyEngine::RenderComponent::Render() const
{
	for (size_t i{}; i < m_NrTextures; i++)
	{
		glm::fvec2 pos = m_pGameObject->GetComponent<TransformComponent>()->GetPosition();
		Renderer::GetInstance()->RenderTexture(*m_Textures[i], pos.x,pos.y);
	}
}

void MyEngine::RenderComponent::AddTexture(Texture2D* texture)
{
	if (m_NrTextures == m_Textures.size()) throw std::exception("Max Nr of Textures Reached.");
	m_Textures[m_NrTextures] = texture;
	m_NrTextures++;
}

