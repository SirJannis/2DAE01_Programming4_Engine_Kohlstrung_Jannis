#pragma once
#include "Singleton.h"
namespace MyEngine
{
	class GameObject;
	enum class Event
	{

	};
	class Observer : public Singleton<Observer>
	{
	public:
		virtual ~Observer() = default;
		virtual void Notify(const GameObject& gameObject, const Event event, const int value = 0) = 0;
	};
}