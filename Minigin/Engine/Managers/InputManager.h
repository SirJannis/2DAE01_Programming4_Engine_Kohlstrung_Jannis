#pragma once
#include <XInput.h>
#include "../Helpers/Singleton.h"

namespace MyEngine
{
	enum class ControllerButton
	{
		ButtonA,
		ButtonB,
		ButtonX,
		ButtonY
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		bool IsPressed(ControllerButton button) const;
	private:
		XINPUT_STATE m_CurrentState{};
	};

}