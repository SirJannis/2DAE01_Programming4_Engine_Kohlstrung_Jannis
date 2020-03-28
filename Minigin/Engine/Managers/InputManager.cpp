#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>
#include "../Scene/GameObject.h"
#include "../Helpers/Logger.h"


MyEngine::InputManager::~InputManager()
{
	for (std::pair<ControllerButton, std::vector<Command*>> pair : m_ControllerMappings)
	{
		for (Command* pCommand : pair.second)
		{
			delete pCommand;
		}
	}
	for (std::pair<KeyboardKey, std::vector<Command*>> pair : m_KeyBoardMappings)
	{
		for (Command* pCommand : pair.second)
		{
			delete pCommand;
		}
	}
}

void MyEngine::InputManager::ProcessInput(GameObject* object)
{
	for (std::pair<ControllerButton, std::vector<Command*>> pair : m_ControllerMappings)
	{
		if (IsPressed(pair.first))
		{
			for (Command* pCommand : pair.second)
			{
				pCommand->Execute(object);
			}
		}
	}
	for (std::pair<KeyboardKey, std::vector<Command*>> pair : m_KeyBoardMappings)
	{
		if (IsPressed(pair.first))
		{
			for (Command* pCommand : pair.second)
			{
				pCommand->Execute(object);

			}
		}
	}
}

void MyEngine::InputManager::AddCommand(ControllerButton button, Command* command)
{
	for (Command* pCommand : m_ControllerMappings[button])
	{
		if (typeid(*pCommand) == typeid(*command))
		{
			Logger::GetInstance()->LogWarning("Command already added to button(created memory leak).");
			return;
		}
	}
	m_ControllerMappings[button].push_back(command);
}

void MyEngine::InputManager::AddCommand(KeyboardKey key, Command* command)
{
	for (Command* pCommand : m_KeyBoardMappings[key])
	{
		if (typeid(*pCommand) == typeid(*command))
		{
			Logger::GetInstance()->LogWarning("Command already added to key.");
			return;
		}
	}
	m_KeyBoardMappings[key].push_back(command);
}

bool MyEngine::InputManager::ProcessSDLEvents()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
	}
	return true;
}

bool MyEngine::InputManager::IsPressed(ControllerButton button) const
{
	XINPUT_STATE* pState = new XINPUT_STATE();
	XInputGetState(0, pState);
	bool ret = pState->Gamepad.wButtons & DWORD(button);
	delete pState;
	return ret;
}

bool MyEngine::InputManager::IsPressed(KeyboardKey key) const
{
	return GetKeyState((int)key) & 0x8000;
}

