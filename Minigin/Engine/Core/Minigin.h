#pragma once
struct SDL_Window;
namespace MyEngine
{
	class Minigin
	{
	public:
		void Initialize(const std::string& dataPath, const std::string& windowTitle, int windowWidth, int windowHeigth, const float ppm);
		void LoadGame() const;
		void Cleanup();
		void Run();
		static const float SecondsPerFrame; //16 for 60 fps, 33 for 30 fps
	private:
		SDL_Window* m_pWindow{};
	};
}