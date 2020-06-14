#pragma once
#include "../Managers/SceneManager.h"

namespace MyEngine
{
	class GameObject;
	class Scene final
	{
		friend Scene& SceneManager::CreateScene(const std::string& name, bool setactive);
	public:
		void Add(GameObject* pObject);

		const std::string& GetName() { return m_Name; }

		void FixedUpdate(const float fixedDeltaTime);
		void Update(const float deltaTime);
		void Render() const;

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		explicit Scene(const std::string& name);
		std::string m_Name;
		std::vector<GameObject*> m_Objects{};

	};

}
