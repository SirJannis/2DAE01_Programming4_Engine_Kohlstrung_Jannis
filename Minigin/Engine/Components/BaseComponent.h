#pragma once
namespace MyEngine
{
	class GameObject;
	class BaseComponent
	{
	public:
		virtual ~BaseComponent() = default;
		virtual void Update(const float deltaTime) = 0;
		virtual void Render() const = 0;
		void SetGameObject(GameObject* pParent) { m_pGameObject = pParent; }

	protected:
		GameObject* m_pGameObject = nullptr;
	};
}

