#pragma once
#include "Singleton.h"
namespace MyEngine
{
	class GameObject;
	//This enum has 25 Events use them as you want
	enum class Event
	{
		e0,
		e1,
		e2,
		e3,
		e4,
		e5,
		e6,
		e7,
		e8,
		e9,
		e10,
		e11,
		e12,
		e13,
		e14,
		e15,
		e16,
		e17,
		e18,
		e19,
		e20,
		e21,
		e22,
		e23,
		e24
	};

	template <class T>
	class Observer : public Singleton<T>
	{
	public:
		virtual ~Observer() = default;
		virtual void Notify(const Event event, const int value = 0, const GameObject* gameObject = nullptr) = 0;
	};
}