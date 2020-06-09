#pragma once
#include <XInput.h>
#include "../Helpers/Singleton.h"
#include <map>
#include <functional>

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
	struct Command
	{
		std::function<void()> Action;
		ButtonState State;
	};


	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager() = default;
		~InputManager();
		void Init(SDL_Window* pWindow);
		void AddCommand(const int buttonCode,const Hardware hardware,const Command* command, int id = 0);
		bool ProcessSDLEvents() const;
		void ProcessInput();
		bool IsPressed(const int buttonCode,const Hardware hardWare, int id = 0);
		bool IsDown(const int buttonCode,const Hardware hardWare, int id = 0);
		bool IsReleased(const int buttonCode,const Hardware hardWare, int id = 0);
		bool IsButtonState(const int buttonCode, const Hardware hardware, const ButtonState state, int id = 0);
	private:
		std::map<std::pair<const int, const int>, std::vector<const Command*>> m_ControllerMappings;
		std::map<std::pair<const int, const int>, std::vector<const Command*>> m_KeyBoardMappings;
		std::map<std::pair<const int, const int>, std::vector<const Command*>> m_MouseMappings;

		std::map<std::pair<const int, const int>, ButtonState> m_ControllerStates;
		std::map<std::pair<const int, const int>, ButtonState> m_KeyBoardStates;
		std::map<std::pair<const int, const int>, ButtonState> m_MouseStates;

		void AddCommand(const int buttonCode, const Command* command, std::map<std::pair<const int, const int>, std::vector<const Command*>>& mappings, int id);
		void ExecuteCommand(const Hardware hardware, const std::map<std::pair<const int, const int>, std::vector<const Command*>>& mappings);
		void UpdateStates(const Hardware hardware);

		void UpdateState(const bool down,std::pair<const std::pair<const int, const int>, ButtonState>& pair);

		SDL_Window* m_pWindow;
	};
}
