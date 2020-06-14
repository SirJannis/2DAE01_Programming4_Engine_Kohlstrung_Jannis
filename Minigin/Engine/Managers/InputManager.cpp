#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>
#include "../Scene/GameObject.h"
#include "../Helpers/Logger.h"



MyEngine::InputManager::~InputManager()
{
	DeleteMappings(m_ControllerMappings);
	DeleteMappings(m_KeyBoardMappings);
	DeleteMappings(m_MouseMappings);

	m_ControllerMappings.clear();
	m_KeyBoardMappings.clear();
	m_MouseMappings.clear();
}

void MyEngine::InputManager::Init(SDL_Window* pWindow)
{
	m_pWindow = pWindow;
}

void MyEngine::InputManager::AddCommand(const int buttonCode, const Hardware hardware, Command* command, int id)
{
	switch (hardware)
	{
	case MyEngine::Hardware::Keyboard:
		AddCommand(buttonCode, command, m_KeyBoardMappings, id);
		m_KeyBoardStates[{buttonCode, id}] = ButtonState::None;
		break;
	case MyEngine::Hardware::Controller:
		AddCommand(buttonCode, command, m_ControllerMappings, id);
		m_ControllerStates[{buttonCode, id}] = ButtonState::None;
		break;
	case MyEngine::Hardware::Mouse:
		AddCommand(buttonCode, command, m_MouseMappings, id);
		m_MouseStates[{buttonCode, id}] = ButtonState::None;
		break;
	default:
		break;
	}
}

void MyEngine::InputManager::RemoveCommandsByScene(const std::string& sceneName)
{
	ClearCommandsByScene(sceneName, m_KeyBoardMappings);
	ClearCommandsByScene(sceneName, m_ControllerMappings);
	ClearCommandsByScene(sceneName, m_MouseMappings);
}

void MyEngine::InputManager::ProcessInput()
{
	if (!(SDL_GetWindowFlags(m_pWindow) & (SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS)))
		return;
	UpdateStates(Hardware::Keyboard);
	UpdateStates(Hardware::Controller);
	UpdateStates(Hardware::Mouse);

	ExecuteCommand(Hardware::Keyboard, m_KeyBoardMappings);
	ExecuteCommand(Hardware::Controller, m_ControllerMappings);
	ExecuteCommand(Hardware::Mouse, m_MouseMappings);

	m_PrevMousePos = m_MousePos;
	SDL_GetMouseState(&m_MousePos.x, &m_MousePos.y);
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
bool MyEngine::InputManager::IsPressed(const int buttonCode, Hardware hardWare, int id)
{
	return IsButtonState(buttonCode, hardWare, ButtonState::Pressed, id);
}

bool MyEngine::InputManager::IsReleased(const int buttonCode, const Hardware hardWare, int id)
{
	return IsButtonState(buttonCode, hardWare, ButtonState::Released, id);
}

bool MyEngine::InputManager::IsDown(const int buttonCode, const Hardware hardWare, int id)
{
	return IsButtonState(buttonCode, hardWare, ButtonState::Down, id);
}

bool MyEngine::InputManager::IsButtonState(const int buttonCode, const Hardware hardware, const ButtonState state, int id)
{
	switch (hardware)
	{
	case MyEngine::Hardware::Keyboard:
		return m_KeyBoardStates[{buttonCode, id}] == state;
	case MyEngine::Hardware::Controller:
		return m_ControllerStates[{buttonCode, id}] == state;
	case MyEngine::Hardware::Mouse:
		return m_MouseStates[{buttonCode, id}] == state;
	default:
		return false;
	}
}

const SDL_Point MyEngine::InputManager::GetMousePos()
{
	int h;
	SDL_GetWindowSize(m_pWindow, nullptr, &h);
	return { m_MousePos.x, h - m_MousePos.y };
}

const SDL_Point MyEngine::InputManager::GetMouseMovement()
{
	return { m_MousePos.x - m_PrevMousePos.x, m_PrevMousePos.y - m_MousePos.y };
}

void MyEngine::InputManager::AddCommand(const int buttonCode, Command* command, std::map<std::pair<const int, const int>, std::vector<Command*>>& mappings, int id)
{
	for (Command* pCommand : mappings[{buttonCode, id}])
	{
		if (pCommand == command)
		{
			Logger::LogWarning("Command already added to button(created memory leak).");
			return;
		}
	}
	mappings[{buttonCode, id}].push_back(command);
}

void MyEngine::InputManager::ExecuteCommand(const Hardware hardware, const std::map<std::pair<const int, const int>, std::vector<Command*>>& mappings)
{
	for (const std::pair<std::pair<const int, const int>, std::vector<Command*>>& pair : mappings)
	{
		for (Command* pCommand : pair.second)
		{
			if (IsButtonState(pair.first.first, hardware, pCommand->State, pair.first.second))
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
		for (std::pair< const std::pair<const int, const int>, ButtonState>& pair : m_KeyBoardStates)
		{
			UpdateState(GetKeyState(pair.first.first) & 0x8000, pair);
		}
		break;
	case MyEngine::Hardware::Controller:
		for (std::pair< const std::pair<const int, const int>, ButtonState>& pair : m_ControllerStates)
		{
			pState = new XINPUT_STATE();
			XInputGetState(pair.first.second, pState);
			buttons = pState->Gamepad.wButtons;
			SafeDelete(pState);
			UpdateState(buttons & WORD(pair.first.first), pair);
		}
		break;
	case MyEngine::Hardware::Mouse:
		for (std::pair< const std::pair<const int, const int>, ButtonState>& pair : m_MouseStates)
		{
			UpdateState(GetKeyState(pair.first.first) & 0x80, pair);
		}
		break;
	default:
		break;
	}

}

void MyEngine::InputManager::UpdateState(const bool down, std::pair< const std::pair<const int, const int>, ButtonState>& pair)
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

void MyEngine::InputManager::DeleteMappings(const std::map<std::pair<const int, const int>, std::vector<Command*>>& mapping)
{
	for (const std::pair<std::pair<const int, const int>, std::vector<Command*>>& pair : mapping)
	{
		for (Command* pCommand : pair.second)
		{
			if (!pCommand->IsDeleted)
			{
				pCommand->IsDeleted = true;
				SafeDelete(pCommand);
			}
		}
	}
}

void MyEngine::InputManager::ClearCommandsByScene(const std::string& sceneName, std::map<std::pair<const int, const int>, std::vector<Command*>>& mapping)
{
	for (std::pair<const std::pair<const int, const int>, std::vector<Command*>>& pair : mapping)
	{
		for (size_t commandCounter{}; commandCounter < pair.second.size(); commandCounter++)
		{
			if (pair.second[commandCounter]->SceneName == sceneName)
			{
				SafeDelete(pair.second[commandCounter]);
				pair.second[commandCounter] = pair.second.back();
				pair.second.pop_back();
				commandCounter--;
			}
		}
	}
}

