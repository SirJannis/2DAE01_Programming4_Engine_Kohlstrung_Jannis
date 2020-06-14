#pragma once
#include <XInput.h>
#include "../Helpers/Singleton.h"
#include <map>
#include <functional>
#include "SDL.h"

struct SDL_Window;
namespace MyEngine
{
	enum class ButtonState
	{
		None,
		Pressed,
		Down,
		Released
	};
	enum class Hardware
	{
		Keyboard,
		Controller,
		Mouse
	};

	class GameObject;
	//With this you need to add a different command for each scene
	struct Command final
	{
		std::function<void()> Action;
		ButtonState State;
		std::string SceneName;
		bool IsDeleted = false;
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager() = default;
		~InputManager();
		void Init(SDL_Window* pWindow);
		void AddCommand(const int buttonCode, const Hardware hardware, Command* command, int id = 0);
		void RemoveCommandsByScene(const std::string& sceneName);
		bool ProcessSDLEvents() const;
		void ProcessInput();
		bool IsPressed(const int buttonCode, const Hardware hardWare, int id = 0);
		bool IsDown(const int buttonCode, const Hardware hardWare, int id = 0);
		bool IsReleased(const int buttonCode, const Hardware hardWare, int id = 0);
		bool IsButtonState(const int buttonCode, const Hardware hardware, const ButtonState state, int id = 0);
		const SDL_Point GetMousePos();
		const SDL_Point GetMouseMovement();

	private:
		std::map<std::pair<const int, const int>, std::vector<Command*>> m_ControllerMappings;
		std::map<std::pair<const int, const int>, std::vector<Command*>> m_KeyBoardMappings;
		std::map<std::pair<const int, const int>, std::vector<Command*>> m_MouseMappings;

		std::map<std::pair<const int, const int>, ButtonState> m_ControllerStates;
		std::map<std::pair<const int, const int>, ButtonState> m_KeyBoardStates;
		std::map<std::pair<const int, const int>, ButtonState> m_MouseStates;

		void AddCommand(const int buttonCode, Command* command, std::map<std::pair<const int, const int>, std::vector<Command*>>& mappings, int id);
		void ExecuteCommand(const Hardware hardware, const std::map<std::pair<const int, const int>, std::vector<Command*>>& mappings);
		void UpdateStates(const Hardware hardware);

		void UpdateState(const bool down, std::pair<const std::pair<const int, const int>, ButtonState>& pair);

		void DeleteMappings(const std::map<std::pair<const int, const int>, std::vector<Command*>>& mapping);

		void ClearCommandsByScene(const std::string& sceneName, std::map<std::pair<const int, const int>, std::vector<Command*>>& mapping);

		SDL_Window* m_pWindow;

		SDL_Point m_MousePos;
		SDL_Point m_PrevMousePos;
	};
}
