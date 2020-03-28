#pragma once
#include <XInput.h>
#include "../Helpers/Singleton.h"
#include "../Helpers/Command.h"
#include <map>

namespace MyEngine
{
	enum class ControllerButton
	{
		ButtonA = XINPUT_GAMEPAD_A,
		ButtonB = XINPUT_GAMEPAD_B,
		ButtonX = XINPUT_GAMEPAD_X,
		ButtonY = XINPUT_GAMEPAD_Y,
	};

	enum class KeyboardKey
	{
		KeyUp = VK_UP,
		KeyDown = VK_DOWN,
		KeyLeft = VK_LEFT,
		KeyRight = VK_RIGHT,
		KeyW = 'W',
		KeyS = 'S',
		KeyA = 'A',
		KeyD = 'D',
		KeyShift = VK_SHIFT,
		KeyControl = VK_CONTROL,
		KeySpace = VK_SPACE
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		~InputManager();
		void AddCommand(ControllerButton button, Command* command);
		void AddCommand(KeyboardKey key, Command* command);
		bool ProcessSDLEvents();
		void ProcessInput(GameObject* object);
		bool IsPressed(ControllerButton button) const;
		bool IsPressed(KeyboardKey key) const;
	private:
		std::map<ControllerButton, std::vector<Command*>> m_ControllerMappings;
		std::map<KeyboardKey, std::vector<Command*>> m_KeyBoardMappings;
	};
}
