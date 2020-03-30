#pragma once

namespace MyEngine
{
	class BaseComponent;
	class GameObject
	{
	public:
		void FixedUpdate(const float fixedDeltaTime);
		void Update(const float deltaTime);
		void Render() const;
		

		GameObject() = default;
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void AddComponent(BaseComponent* component);

		template <class T>
		T* GetComponent()
		{
			const type_info& ti = typeid(T);
			for (BaseComponent* pComp : m_Components)
			{
				if (pComp && typeid(*pComp) == ti)
					return static_cast<T*>(pComp);
			}
			return nullptr;
		}
	private:
		std::vector<BaseComponent*> m_Components;

	};
}
