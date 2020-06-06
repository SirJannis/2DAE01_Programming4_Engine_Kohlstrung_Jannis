#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>
#include "../Scene/GameObject.h"
#include "../Helpers/Logger.h"


MyEngine::InputManager::~InputManager()
{
	for (std::pair<const int, std::vector<const Command*>>& pair : m_ControllerMappings)
	{
		for (const Command* pCommand : pair.second)
		{
			delete pCommand;
		}
	}
	for (std::pair<const int, std::vector<const Command*>>& pair : m_KeyBoardMappings)
	{
		for (const Command* pCommand : pair.second)
		{
			delete pCommand;
		}
	}
	for (std::pair<const int, std::vector<const Command*>>& pair : m_MouseMappings)
	{
		for (const Command* pCommand : pair.second)
		{
			delete pCommand;
		}
	}
}

void MyEngine::InputManager::AddCommand(const int buttonCode, const Hardware hardware, const Command* command)
{
	switch (hardware)
	{
	case MyEngine::Hardware::Keyboard:
		AddCommand(buttonCode, command, m_KeyBoardMappings);
		m_KeyBoardStates[buttonCode] = ButtonState::None;
		break;
	case MyEngine::Hardware::Controller:
		AddCommand(buttonCode, command, m_ControllerMappings);
		m_ControllerStates[buttonCode] = ButtonState::None;
		break;
	case MyEngine::Hardware::Mouse:
		AddCommand(buttonCode, command, m_MouseMappings);
		m_MouseStates[buttonCode] = ButtonState::None;
		break;
	default:
		break;
	}
}

void MyEngine::InputManager::ProcessInput()
{
	UpdateStates(Hardware::Keyboard);
	UpdateStates(Hardware::Controller);
	UpdateStates(Hardware::Mouse);

	ExecuteCommand(Hardware::Keyboard, m_KeyBoardMappings);
	ExecuteCommand(Hardware::Controller, m_ControllerMappings);
	ExecuteCommand(Hardware::Mouse, m_MouseMappings);
}

bool MyEngine::InputManager::ProcessSDLEvents() const
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
	}
	return true;
}
bool MyEngine::InputManager::IsPressed(const int buttonCode, const Hardware hardWare)
{
	return IsButtonState(buttonCode, hardWare, ButtonState::Pressed);
}

bool MyEngine::InputManager::IsReleased(const int buttonCode, const Hardware hardWare)
{
	return IsButtonState(buttonCode, hardWare, ButtonState::Released);
}

bool MyEngine::InputManager::IsDown(const int buttonCode, const Hardware hardWare)
{
	return IsButtonState(buttonCode, hardWare, ButtonState::Down);
}

bool MyEngine::InputManager::IsButtonState(const int buttonCode, const Hardware hardware, const ButtonState state)
{
	switch (hardware)
	{
	case MyEngine::Hardware::Keyboard:
		return m_KeyBoardStates[buttonCode] == state;
	case MyEngine::Hardware::Controller:
		return m_ControllerStates[buttonCode] == state;
	case MyEngine::Hardware::Mouse:
		return m_MouseStates[buttonCode] == state;
	default:
		return false;
	}
}

void MyEngine::InputManager::AddCommand(const int buttonCode, const Command* command, std::map<const int, std::vector<const Command*>>& mappings)
{
	for (const Command* pCommand : mappings[buttonCode])
	{
		if (pCommand == command)
		{
			Logger::GetInstance()->LogWarning("Command already added to button(created memory leak).");
			return;
		}
	}
	mappings[buttonCode].push_back(command);
}

void MyEngine::InputManager::ExecuteCommand(const Hardware hardware, const std::map<const int, std::vector<const Command*>>& mappings)
{
	for (const std::pair<const int, std::vector<const Command*>>& pair : mappings)
	{
		for (const Command* pCommand : pair.second)
		{
			if (IsButtonState(pair.first, hardware, pCommand->State))
			{
				pCommand->Action();
			}
		}
	}
}

void MyEngine::InputManager::UpdateStates(const Hardware hardware)
{
	XINPUT_STATE* pState{};
	WORD buttons{};
	switch (hardware)
	{
	case MyEngine::Hardware::Keyboard:
		for (std::pair<const int, ButtonState>& pair : m_KeyBoardStates)
		{
			UpdateState(GetKeyState(pair.first) & 0x8000, pair);
		}
		break;
	case MyEngine::Hardware::Controller:
		pState = new XINPUT_STATE();
		XInputGetState(1, pState);
		buttons = pState->Gamepad.wButtons;
		delete pState;
		for (std::pair<const int, ButtonState>& pair : m_ControllerStates)
		{
			UpdateState(buttons & WORD(pair.first), pair);
		}
		break;
	case MyEngine::Hardware::Mouse:
		for (std::pair<const int, ButtonState>& pair : m_MouseStates)
		{
			UpdateState(GetKeyState(pair.first) & 0x80, pair);
		}
		break;
	default:
		break;
	}

}

void MyEngine::InputManager::UpdateState(const bool down, std::pair<const int, ButtonState>& pair)
{
	if (down)
	{
		if (pair.second == ButtonState::None || pair.second == ButtonState::Pressed)
		{
			pair.second = ButtonState(int(pair.second) + 1);
		}
		if (pair.second == ButtonState::Released)
		{
			pair.second = ButtonState::Pressed;
		}
	}
	else
	{
		if (pair.second == ButtonState::Down || pair.second == ButtonState::Released)
		{
			pair.second = ButtonState((int(pair.second) + 1) % 4);
		}
	}
}

