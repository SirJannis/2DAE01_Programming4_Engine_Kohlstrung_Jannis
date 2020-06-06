#pragma once
#include <XInput.h>
#include "../Helpers/Singleton.h"
#include <map>
#include <functional>

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
		~InputManager();
		void AddCommand(const int buttonCode,const Hardware hardware,const Command* command);
		bool ProcessSDLEvents() const;
		void ProcessInput();
		bool IsPressed(const int buttonCode,const Hardware hardWare);
		bool IsDown(const int buttonCode,const Hardware hardWare);
		bool IsReleased(const int buttonCode,const Hardware hardWare);
		bool IsButtonState(const int buttonCode, const Hardware hardware, const ButtonState state);
	private:
		std::map<const int, std::vector<const Command*>> m_ControllerMappings;
		std::map<const int, std::vector<const Command*>> m_KeyBoardMappings;
		std::map<const int, std::vector<const Command*>> m_MouseMappings;

		std::map<const int, ButtonState> m_ControllerStates;
		std::map<const int, ButtonState> m_KeyBoardStates;
		std::map<const int, ButtonState> m_MouseStates;

		void AddCommand(const int buttonCode, const Command* command, std::map<const int, std::vector<const Command*>>& mappings);
		void ExecuteCommand(const Hardware hardware, const std::map<const int, std::vector<const Command*>>& mappings);
		void UpdateStates(const Hardware hardware);

		void UpdateState(const bool down, std::pair<const int, ButtonState>& pair);
	};
}
