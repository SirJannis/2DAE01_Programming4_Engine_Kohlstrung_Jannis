#pragma once
#include "../Managers/SceneManager.h"

namespace MyEngine
{
	class GameObject;
	class Scene
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(GameObject* pObject);
		//Add scene activated and scene deactivated
		//Levels unload all other levels known and main menu as well

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

		static unsigned int m_IdCounter; 
	};

}
