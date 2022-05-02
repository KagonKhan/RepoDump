#pragma once
#include "ActionMap.h"

#include <functional>
#include <utility>
#include <list>

template<typename T = int>
class ActionTarget
{
	//more explicit typedef
public: 	using FuncType = std::function<void(const sf::Event&)>;

private:

	std::list<std::pair<T, FuncType>> m_EventsRealTime;
	std::list<std::pair<T, FuncType>> m_EventsPoll;
	const ActionMap<T>& m_ActionMap;

public:
	ActionTarget(const ActionTarget<T>&) = delete;
	ActionTarget<T>& operator= (const ActionTarget<T>&) = delete;

	ActionTarget(const ActionMap<T>& map);

	bool ProcessEvent(const sf::Event& event) const;
	void ProcessEvents() const;

	void Bind(const T& key, const FuncType& callback);
	void Unbind(const T& key);



};

template<typename T>
ActionTarget<T>::ActionTarget(const ActionMap<T>& map)
	: m_ActionMap(map)
{

}

template<typename T>
bool ActionTarget<T>::ProcessEvent(const sf::Event& event) const
{
	bool result = false;

	for (auto& pair : m_EventsPoll)
		if (m_ActionMap.Get(pair.first) == event) {
			pair.second(event);
			result = true;
			break;
		}

	return result;
}

template<typename T>
void ActionTarget<T>::ProcessEvents() const
{
	for (auto& pair : m_EventsRealTime) {
		const Action& action = m_ActionMap.Get(pair.first);

		if (action.test())
			pair.second(action.m_Event);
	}

}

template<typename T>
void ActionTarget<T>::Bind(const T& key, const FuncType& callback)
{
	const Action& action = m_ActionMap.Get(key);

	if (action.m_Type & Action::Type::RealTime)
		m_EventsRealTime.emplace_back(key, callback);
	else
		m_EventsPoll.emplace_back(key, callback);
}

template<typename T>
void ActionTarget<T>::Unbind(const T& key)
{

	auto remove_function = [&key](const std::pair<T, FuncType>& pair) -> bool
	{
		return pair.first == key;
	};

	const Action& action = m_ActionMap.Get(key);

	//if (action.m_Type & Action::Type::RealTime)
	//	m_EventsRealTime.remove_if(remove_function);
	//else
	//	m_EventsPoll.remove_if(remove_function);
}