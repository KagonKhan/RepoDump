#include <unordered_map>
#include <memory>
#include "SFML/Graphics.hpp"
#include <cassert>

template<class RESOURCE, typename ID = int>
class ResourceManager
{
private:
	std::unordered_map<ID, std::unique_ptr<RESOURCE>> m_ResourceMap;

public:
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager() = default;

	template<typename ... Args>
	void load(const ID& id, Args&& ... args);
	RESOURCE& get(const ID& id) const;
};



template <typename IDENTIFIER>
class ResourceManager<sf::Music, IDENTIFIER>
{
private:
	std::unordered_map<IDENTIFIER, std::unique_ptr<sf::Music>> m_ResourceMap;

public:
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager() = default;

	template<typename ... Args>
	void load(const IDENTIFIER& id, Args&& ... args);
	sf::Music& get(const IDENTIFIER& id) const;

};

#include "ResourceManager.inl"