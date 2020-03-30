#pragma once
#include "../Helpers/Singleton.h"

namespace MyEngine
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
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
