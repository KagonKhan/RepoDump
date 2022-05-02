#pragma once
#include "Action.h"

#include <unordered_map>

template<typename T = int>
class ActionMap
{
	std::unordered_map<T, Action> m_Map;

public:
	ActionMap(const ActionMap<T>&) = delete;
	ActionMap<T>& operator= (const ActionMap<T>&) = delete;

	ActionMap() = default;
	void Map(const T& key, const Action& action);
	const Action& Get(const T& key)const;
};

template<typename T>
void ActionMap<T>::Map(const T& key, const Action& action)
{
	m_Map.emplace(key, action);
}

template<typename T>
const Action& ActionMap<T>::Get(const T& key) const
{
	return m_Map.at(key);
}