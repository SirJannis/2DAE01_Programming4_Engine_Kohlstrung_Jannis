#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "../Graphics/Texture2D.h"
#include "../Graphics/Renderer.h"
#include "../Scene/GameObject.h"
#include "SDL.h"
#include "glm/gtx/rotate_vector.hpp"

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
	for (const RenderTexture& texture : m_Textures)
	{
		const glm::fvec2& pos = m_pGameObject->GetComponent<TransformComponent>()->GetPosition();
		SDL_Rect destRect{ int(pos.x), int(pos.y) };
		SDL_QueryTexture(texture.Texture->GetSDLTexture(), nullptr, nullptr, &destRect.w, &destRect.h);

		SDL_Rect srcRect{ int(texture.SrcPos.x * destRect.w), int(texture.SrcPos.y * destRect.h) , int(texture.SrcDim.x * destRect.w) , int(texture.SrcDim.y * destRect.h) };

		if (texture.DrawWidth != 0 && texture.DrawHeight != 0)
		{
			destRect.w = texture.DrawWidth;
			destRect.h = texture.DrawHeight;
		}

		SDL_Point pivot{int(texture.Pivot.x * destRect.w), int(texture.Pivot.y * destRect.h) };
		glm::fvec2 offset{ texture.Offset.x * destRect.w, texture.Offset.y * destRect.h };

		offset = glm::rotate(offset, -m_pGameObject->GetComponent<TransformComponent>()->GetRotation() * float(M_PI) / 180.f);

		destRect.x += int(offset.x) - pivot.x;
		destRect.y += int(offset.y) + pivot.y;

		Renderer::GetInstance()->RenderTexture(*texture.Texture, &destRect, &srcRect, m_pGameObject->GetComponent<TransformComponent>()->GetRotation() + texture.Angle, pivot, texture.IsMirrored);

	}
}

void MyEngine::RenderComponent::AddTexture(Texture2D* text, const int drawWidth, const int drawHeight, const bool isMirrored, const glm::fvec2& pivot, const glm::fvec2& offset, const glm::fvec2& srcPos, const glm::fvec2& srcDim, const float angle)
{
	m_Textures.push_back({ text, drawWidth, drawHeight, isMirrored, pivot, offset, srcPos, srcDim, angle });
}


