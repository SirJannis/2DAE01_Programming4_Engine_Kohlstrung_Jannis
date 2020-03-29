#pragma once
#include "Observer.h"
namespace MyEngine
{
	class AchievmentSystem final : public Observer
	{
		virtual void Notify(const GameObject& gameObject, const Event event, const int value = 0) override
		{
			switch (event)
			{
			default:
				break;
			}
		}
	};
}