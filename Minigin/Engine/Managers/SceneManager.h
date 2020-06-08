#pragma once
#include "../Helpers/Singleton.h"

namespace MyEngine
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		//Instead of createscene, have addscene
		//Setactivescene that passes a name
		//removescene to remove a scene by name and deletes
		//removescene a vector of names to remove and delete with failchecks
		//FixedUpdate, Update and Render only on the active scene
		//Active Scene Member variable
		SceneManager() = default;
		~SceneManager();
		Scene& CreateScene(const std::string& name);

		void FixedUpdate(const float fixedDeltaTime);
		void Update(const float deltaTime);
		void Render();
	private:
		//friend class Singleton<SceneManager>;
		std::vector<Scene*> m_Scenes;
	};
}
